from pathlib import Path
from dataclasses import replace
import json
import unittest

from arknights_probe.data import DataError
from arknights_probe.damage import (DamageRuntime, ordinary_altar_shape,
                                   ordinary_hp_write, pure_damage_value)
from arknights_probe.devices import FixedDamageAction
from arknights_probe.env import UnverifiedMechanism
from arknights_probe.fp import FP
from arknights_probe.frame_runtime import SharedCoroutineSimulator, CoroutineOwner
from arknights_probe.lifecycle import LifecycleRuntime
from arknights_probe.coroutines import fixed_seconds


class DamageArithmeticTests(unittest.TestCase):
    def test_pure_attack_scale_uses_fixedpoint_and_zero_floor(self):
        self.assertEqual(pure_damage_value(FP.from_int32(500), FP.from_int32(1)).raw, 500 << 32)
        self.assertEqual(pure_damage_value(FP.from_int32(-500), FP.from_int32(1)).raw, 0)
        self.assertEqual(pure_damage_value(FP.from_int32(500), FP.from_raw(0)).raw, 0)
        self.assertEqual(pure_damage_value(FP.from_raw(3), FP.from_raw(1 << 31)).raw, 1)

    def test_hp_threshold_is_en5_and_clamp_is_signed(self):
        maximum = FP.from_int32(100)
        for requested in [-1, 0, 1, 42949]:
            with self.subTest(requested=requested):
                self.assertEqual(ordinary_hp_write(FP.from_raw(requested), maximum).raw, 0)
        self.assertEqual(ordinary_hp_write(FP.from_raw(42950), maximum).raw, 42950)
        self.assertEqual(ordinary_hp_write(FP.from_raw(42951), maximum).raw, 42951)
        self.assertEqual(ordinary_hp_write(FP.from_int32(101), maximum).raw, maximum.raw)

    def test_arithmetic_inputs_require_native_fp_and_positive_maximum(self):
        with self.assertRaises(DataError):
            pure_damage_value(500, FP.from_int32(1))
        with self.assertRaises(DataError):
            ordinary_hp_write(FP.from_int32(1), FP.from_raw(0))

    def test_independent_csharp_full_product_and_hp_boundary_vectors(self):
        path = Path(__file__).resolve().parents[1]/"evidence/damage/reference_vectors.json"
        vectors = json.loads(path.read_text("utf8"))["vectors"]
        self.assertEqual(len(vectors), 255)
        for row in vectors:
            case, expected = row["input"], row["expected"]
            with self.subTest(id=case["id"]):
                damage = pure_damage_value(FP.from_raw(case["attack_raw"]), FP.from_raw(case["scale_raw"]))
                before = FP.from_raw(case["hp_raw"])
                after = ordinary_hp_write(before-damage, FP.from_raw(case["max_hp_raw"]))
                self.assertEqual(damage.raw, expected["damage_raw"])
                self.assertEqual(after.raw, expected["written_hp_raw"])
                self.assertEqual((after-before).raw, expected["applied_delta_raw"])
                self.assertEqual(after.raw == 0, expected["killed"])


def component(*, hp=1000, delay=.1, recycle_flag=True, **shape_overrides):
    life = LifecycleRuntime(initial_life=5, initial_temp_life=0, dt=FP.from_raw(143165440),
                            use_recycle_to_finish_scheduler=recycle_flag,
                            context_source="explicit ordinary component fixture")
    actor = life.spawn("target", "enemy_1034_laxe", max_hp=FP.from_int32(hp), birth_delay=0,
                       recycle_delay=delay, life_point_reduce=1, managed=True, wave_block=True,
                       not_count_in_total=False, lifecycle_templates=())
    simulator = SharedCoroutineSimulator(source="explicit component phases", deterministic=True)
    runtime = DamageRuntime(life, simulator, context_source="static ordinary PURE component")
    shape = ordinary_altar_shape(max_hp=FP.from_int32(hp), source_id="altar",
                                 projectile_hit_failed=None, ability_hit_failed=False,
                                 context_source="reviewed laxe/altar shape with no global rules")
    owner = CoroutineOwner(True, True)
    runtime.attach("target", replace(shape, **shape_overrides), recycle_owner=owner)
    return runtime, life, actor, simulator, owner


class DamageRuntimeTests(unittest.TestCase):
    def test_nonlethal_pure_damage_preserves_life_and_native_hook_order(self):
        env, life, actor, simulator, owner = component()
        result = env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1))
        self.assertEqual((result.applied, result.killed, result.applied_delta.raw), (True, False, -(500 << 32)))
        self.assertEqual((actor.hp.raw, life.life, life.temp_life), (500 << 32, 5, 0))
        hooks = [e["callback"] for e in life.events if e["kind"] == "damage_hook"]
        self.assertEqual(hooks, ["OnBeingCalculateDamage", "OnBeforeApplyingModifier", "OnOutputModifier",
                                "OnOutputDamage", "OnApplyingModifier", "OnTakeDamage",
                                "OnBeforeTargetApplyModifier", "OnAppliedModifier", "OnAfterOutputDamage"])
        self.assertEqual(life.wave_ids, {"target"})
        self.assertFalse(simulator.handlers)

    def test_death_releases_wave_before_shared_recycle_and_does_not_charge_exit_life(self):
        env, life, actor, simulator, owner = component(hp=400)
        result = env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1))
        self.assertEqual((result.killed, result.finish_reason, actor.state_id, actor.hp.raw), (True, 2, -1, 0))
        self.assertEqual(result.applied_delta.raw, -(400 << 32))
        self.assertEqual((life.life, life.temp_life), (5, 0))
        self.assertEqual(life.wave_ids, set())
        self.assertEqual(life.final_ids, {"target"})
        self.assertEqual(len(simulator.handlers), 1)
        self.assertEqual(life.recycle_runners, {})
        kinds = [e["kind"] for e in life.events]
        self.assertLess(kinds.index("enemy_killed"), kinds.index("enemy_wave_released"))
        self.assertLess(kinds.index("enemy_wave_released"), kinds.index("enemy_recycle_scheduled"))
        callback_index = next(i for i,e in enumerate(life.events) if e.get("callback") == "OnAppliedModifier")
        self.assertLess(kinds.index("enemy_recycle_scheduled"), callback_index)
        for _ in range(2):
            simulator.tick()
            self.assertFalse(actor.recycled)
        simulator.tick()
        self.assertTrue(actor.recycled)
        self.assertEqual(life.final_ids, set())
        self.assertTrue(life.check_final(schedule_complete=True, branches_active=False))

    def test_immediate_recycle_precedes_after_applied_callbacks(self):
        env, life, actor, simulator, owner = component(hp=100, delay=0)
        env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1))
        self.assertTrue(actor.recycled)
        recycled = next(i for i,e in enumerate(life.events) if e["kind"] == "enemy_recycled")
        applied = next(i for i,e in enumerate(life.events) if e.get("callback") == "OnAppliedModifier")
        self.assertLess(recycled, applied)
        self.assertFalse(simulator.handlers)

    def test_invincible_and_hit_failed_cancel_with_projectile_precedence(self):
        for changes, reason in [({"invincible":True}, 1), ({"ability_hit_failed":True}, 6),
                                ({"invincible":True,"ability_hit_failed":True}, 1),
                                ({"projectile_hit_failed":False,"ability_hit_failed":True}, 0)]:
            with self.subTest(changes=changes):
                env, life, actor, simulator, owner = component(**changes)
                result = env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1))
                self.assertEqual(result.cancel_reason, reason)
                self.assertEqual(actor.hp.raw, (1000 if reason else 500) << 32)
                hooks = [e.get("callback") for e in life.events]
                self.assertEqual("OnAppliedModifier" in hooks, reason == 0)
                self.assertIn("OnTakeDamage", hooks)

    def test_finished_target_calculates_before_rejecting_modifier_without_hp_or_recycle_change(self):
        env, life, actor, simulator, owner = component(hp=100)
        action = FixedDamageAction(FP.from_int32(500))
        env.apply("target", action, atk_scale=FP.from_int32(1))
        count = len(life.events)
        result = env.apply("target", action, atk_scale=FP.from_int32(1))
        self.assertFalse(result.applied)
        self.assertEqual(len(life.events), count + 1)
        self.assertEqual(life.events[-1]["callback"], "OnBeingCalculateDamage")
        self.assertEqual(actor.hp.raw, 0)
        self.assertEqual(len(simulator.handlers), 1)

    def test_en5_remaining_hp_is_not_alive_but_does_not_finish(self):
        env, life, actor, simulator, owner = component(hp=1)
        result = env.apply("target", FixedDamageAction(FP.from_raw((1 << 32)-42950)), atk_scale=FP.from_int32(1))
        self.assertTrue(result.applied)
        self.assertFalse(result.killed)
        self.assertEqual(actor.hp.raw, 42950)
        self.assertFalse(actor.alive)
        self.assertEqual(actor.finish_reason, 0)
        self.assertEqual(life.wave_ids, {"target"})
        self.assertEqual(life.final_ids, {"target"})
        self.assertFalse(simulator.handlers)
        self.assertFalse(life.check_final(schedule_complete=True, branches_active=False))
        hooks = [e.get("callback") for e in life.events]
        self.assertNotIn("OnOwnerBeforeDead", hooks)
        count = len(life.events)
        repeat = env.apply("target", FixedDamageAction(FP.from_raw(1)), atk_scale=FP.from_int32(1))
        self.assertFalse(repeat.applied)
        self.assertEqual(len(life.events), count + 1)
        self.assertEqual(life.events[-1]["callback"], "OnBeingCalculateDamage")
        self.assertEqual(actor.hp.raw, 42950)
        env, life, actor, simulator, owner = component(hp=1)
        result = env.apply("target", FixedDamageAction(FP.from_raw((1 << 32)-42949)), atk_scale=FP.from_int32(1))
        self.assertTrue(result.killed)
        self.assertEqual(actor.hp.raw, 0)

    def test_zero_damage_is_still_admitted(self):
        env, life, actor, simulator, owner = component()
        result = env.apply("target", FixedDamageAction(FP.from_int32(-500)), atk_scale=FP.from_int32(1))
        self.assertTrue(result.applied)
        self.assertEqual((result.calculated.raw, result.applied_delta.raw), (0, 0))

    def test_owner_disable_stops_pending_recycle_without_faking_callback(self):
        env, life, actor, simulator, owner = component(hp=100)
        env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1))
        owner.active_in_hierarchy = False
        simulator.tick()
        self.assertFalse(actor.recycled)
        self.assertEqual(life.final_ids, {"target"})
        self.assertEqual(simulator.handlers, [])

    def test_death_during_coroutine_phase_registers_recycle_after_snapshot(self):
        life_delay = 1/30
        env, life, actor, simulator, owner = component(hp=100, delay=life_delay)
        def cast():
            yield fixed_seconds(life_delay, life.dt.as_float())
            env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1))
        simulator.start(CoroutineOwner(True, True), cast())
        simulator.tick()
        self.assertEqual(actor.finish_reason, 2)
        self.assertFalse(actor.recycled)
        self.assertEqual(len(simulator.handlers), 1)
        simulator.tick()
        self.assertTrue(actor.recycled)

    def test_finished_immediate_ore_callback_buff_is_explicitly_ignored(self):
        env, life, actor, simulator, owner = component(hp=100)
        result = env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1),
                           finished_transient_templates=("ore_s",))
        self.assertTrue(result.killed)
        ignored = next(e for e in life.events if e["kind"] == "damage_finished_transients_ignored")
        self.assertEqual(ignored["templates"], ["ore_s"])
        env, life, actor, simulator, owner = component()
        with self.assertRaises(UnverifiedMechanism):
            env.apply("target", FixedDamageAction(FP.from_int32(500)), atk_scale=FP.from_int32(1),
                      finished_transient_templates=("upeople_t",))
        self.assertEqual(actor.hp.raw, 1000 << 32)

    def test_unclosed_shapes_and_action_branches_reject_before_hp_mutation(self):
        for override in [{"source_exists":False}, {"source_action_slots_empty":False},
                         {"target_template_keys":("unknown",)},
                         {"source_buff_keys":("ore_listener",)}, {"undeadable":True},
                         {"max_minus_hp":FP.from_int32(1)}, {"es":FP.from_int32(1)},
                         {"target_talents":("revive",)}, {"use_specific_dead_anim":True},
                         {"active_enemy_skills":("attack_skill",)}, {"level_event_handlers":("scene",)}]:
            with self.subTest(override=override), self.assertRaises(UnverifiedMechanism):
                component(**override)
        for changes in [{"damage_type":1}, {"attack_type":1}, {"no_source_damage":True},
                        {"trigger_on_calculate_damage":True}, {"consider_unhurtable":True}]:
            env, life, actor, simulator, owner = component()
            with self.subTest(changes=changes), self.assertRaises(UnverifiedMechanism):
                env.apply("target", FixedDamageAction(FP.from_int32(500), **changes), atk_scale=FP.from_int32(1))
            self.assertEqual(actor.hp.raw, 1000 << 32)


if __name__ == '__main__':
    unittest.main()

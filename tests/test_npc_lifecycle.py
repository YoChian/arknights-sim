from dataclasses import replace
import json
import unittest

from arknights_probe.fp import FP
from arknights_probe.frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from arknights_probe.lifecycle import LifecycleRuntime
from arknights_probe.env import UnverifiedMechanism
from arknights_probe.npc_actions import EntityPtr, NpcEntity
from arknights_probe.npc_lifecycle import (
    DeadAnimationReceipt, EnemyFinishOptions, NpcLifecycleActor, NpcLifecycleHooks,
    NpcLifecycleRuntime, PoolRecycleReceipt, SchedulerCounters, SchedulerLedger,
    UnverifiedNpcLifecycle,
)

SOURCE = "explicit initialized NPC lifecycle fixture; no Unity/game execution"
DELTA = FP.from_raw(143165440).as_float()


def actor(**changes):
    value = NpcLifecycleActor(NpcEntity("npc", 24, True, True),
        EnemyFinishOptions(True, False, True, True, 11, False),
        CoroutineOwner(True, True), 1, 0, 0.3, False, True, False, SOURCE,
        False, False, 0)
    return replace(value, **changes)


class Fixture:
    def __init__(self, recycle_flag=True, animation_found=False, animation_length=None):
        self.frame = 0
        self.logs, self.routes, self.buff_calls = [], [], []
        self.simulator = SharedCoroutineSimulator(source=SOURCE, deterministic=True)
        self.ledger = SchedulerLedger(use_recycle_to_finish_scheduler=recycle_flag,
            counters=SchedulerCounters(0, 0, 0, 0, 0, SOURCE),
            remove_runtime_route=self.routes.append, source=SOURCE, fresh_event_pool=True)
        self.runtime = NpcLifecycleRuntime(simulator=self.simulator, ledger=self.ledger,
            hooks=NpcLifecycleHooks(
                owner_finish=lambda a, r, s: self.buff_calls.append(("finish", a.identity, r, s)),
                clear_buffs=lambda a, f: self.buff_calls.append(("clear", a.identity, f)),
                native_phase=lambda name, a, data: self.logs.append((name, a.identity.uid, data)),
                raw_recycle=lambda a: PoolRecycleReceipt(True, False, SOURCE),
                dead_animation=lambda a: DeadAnimationReceipt(animation_found, animation_length, SOURCE),
                source=SOURCE), delta_play_time_float=DELTA, frame=lambda: self.frame,
            no_hotfix=True, controller_exists=True, source=SOURCE)

    def tick(self):
        self.frame += 1
        self.simulator.tick()


class NpcLifecycleTests(unittest.TestCase):
    def test_finish7_returns_to_pool_synchronously_and_clears_final_by_reference(self):
        f, a = Fixture(), actor()
        captured = EntityPtr.capture(a.identity)
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=True)
        self.assertTrue(f.runtime.finish(a, 7, finish_source=EntityPtr.capture(None)))
        self.assertTrue(a.recycled)
        self.assertEqual(a.identity.uid, 0)
        self.assertTrue(a.identity.unity_exists)  # Pooled, not inferred destroyed.
        self.assertFalse(a.identity.alive)
        self.assertIsNone(captured.resolve())
        self.assertEqual(f.ledger.final, [])
        self.assertEqual(f.routes, [11])
        self.assertEqual(f.ledger.counters.finished, 0)
        self.assertEqual(f.ledger.counters.valid_missed, 0)

    def test_native_finish_hook_and_uid_order(self):
        f, a = Fixture(), actor()
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=False)
        f.runtime.finish(a, 7, finish_source=EntityPtr.capture(None))
        stages = [x["stage"] for x in f.runtime.events]
        self.assertLess(stages.index("buff_owner_finish"), stages.index("buff_clear"))
        self.assertLess(stages.index("entity_event2"), stages.index("battle_event6"))
        self.assertLess(stages.index("battle_event6"), stages.index("unregister_bobject"))
        self.assertLess(stages.index("uid_invalidated"), stages.index("battle_event8"))
        self.assertLess(stages.index("battle_event8"), stages.index("raw_pool_recycled"))
        self.assertLess(stages.index("raw_pool_recycled"), stages.index("mode_on_enemy_finished"))
        event8 = next(x for x in f.runtime.events if x["stage"] == "battle_event8")
        self.assertEqual(event8["uid"], 0)
        self.assertEqual([x[0] for x in f.buff_calls], ["finish", "clear"])

    def test_death2_waits_shared_coroutines_before_event8(self):
        f, a = Fixture(), actor()
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=False)
        f.runtime.finish(a, 2, finish_source=EntityPtr.capture(None))
        self.assertEqual(f.ledger.wave, [])
        self.assertEqual(f.ledger.final, [a])
        self.assertEqual(a.identity.uid, 24)
        for _ in range(8):
            f.tick()
            self.assertFalse(a.recycled)
        f.tick()
        self.assertTrue(a.recycled)
        self.assertEqual(f.ledger.final, [])

    def test_specific_death_animation_updates_delay_only_if_found(self):
        f, a = Fixture(animation_found=True, animation_length=1.0), actor(use_specific_dead_animation=True)
        f.runtime.finish(a, 2, finish_source=EntityPtr.capture(None))
        self.assertEqual(a.recycle_delay, 1.0)
        for _ in range(29): f.tick()
        self.assertFalse(a.recycled)
        f.tick()
        self.assertTrue(a.recycled)
        g, b = Fixture(animation_found=True, animation_length=1.0), actor()
        g.runtime.finish(b, 2, finish_source=EntityPtr.capture(None))
        self.assertNotEqual(b.recycle_delay, 1.0)

    def test_effectively_zero_death_delay_is_synchronous(self):
        for delay in (-0.1, 0.0, 1e-5):
            with self.subTest(delay=delay):
                f, a = Fixture(), actor(recycle_delay=delay)
                f.runtime.finish(a, 2, finish_source=EntityPtr.capture(None))
                self.assertTrue(a.recycled)

    def test_coroutine_owner_is_not_alive_and_disabled_owner_does_not_auto_recycle(self):
        f, a = Fixture(), actor()
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=True)
        f.runtime.finish(a, 2, finish_source=EntityPtr.capture(None))
        a.coroutine_owner.active_in_hierarchy = False
        for _ in range(20): f.tick()
        self.assertFalse(a.recycled)
        self.assertEqual(f.ledger.final, [a])
        self.assertEqual(a.identity.uid, 24)

    def test_recycle_flag_false_binds_only6_and_releases_final_before_uid_zero(self):
        f, a = Fixture(False), actor()
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=False)
        f.runtime.finish(a, 2, finish_source=EntityPtr.capture(None))
        self.assertEqual(f.ledger.bound_events, (6,))
        self.assertEqual(f.ledger.final, [])
        self.assertEqual(a.identity.uid, 24)

    def test_ground_bound_absence_preserves_final_and_does_not_invent_event8(self):
        f, a = Fixture(), actor(ground_bound_exists=False)
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=True)
        f.runtime.finish(a, 7, finish_source=EntityPtr.capture(None))
        self.assertTrue(a.recycled)
        self.assertEqual(f.ledger.final, [a])
        self.assertFalse(any(x["stage"] == "battle_event8" for x in f.runtime.events))

    def test_dummy_unit_does_not_emit6_but_recycling_can_emit8(self):
        f, a = Fixture(), actor(is_dummy=True)
        f.ledger.attach(a, managed_by_scheduler=True, dont_block_wave=False)
        f.runtime.finish(a, 7, finish_source=EntityPtr.capture(None))
        self.assertEqual(f.ledger.wave, [a])
        self.assertEqual(f.ledger.final, [])
        self.assertEqual(f.routes, [])

    def test_repeat_finish7_still_calls_outer_mode_hook_with_pooled_uid(self):
        f, a = Fixture(), actor()
        f.runtime.finish(a, 7, finish_source=EntityPtr.capture(None))
        self.assertFalse(f.runtime.finish(a, 7, finish_source=EntityPtr.capture(None)))
        self.assertEqual(len(f.buff_calls), 2)
        self.assertEqual(len([x for x in f.logs if x[0] == "mode_on_enemy_finished"]), 2)
        self.assertEqual(f.logs[-2][1], 0)

    def test_captured_source_resolves_once_before_owner_finish(self):
        f, a = Fixture(), actor(recycle_delay=0.0)
        host = NpcEntity("host", 23, True, True)
        f.runtime.finish(a, 2, finish_source=EntityPtr.capture(host))
        self.assertIs(f.buff_calls[0][3], host)
        source_event = next(x for x in f.runtime.events if x["stage"] == "source_on_target_killed")
        self.assertEqual(source_event["source_entity"], {"token":"host", "uid":23})
        json.dumps(f.runtime.events)
        g, b = Fixture(), actor(recycle_delay=0.0)
        stale = EntityPtr.capture(host)
        host.uid = 99
        g.runtime.finish(b, 2, finish_source=stale)
        self.assertIsNone(g.buff_calls[0][3])

    def test_summon_missed_count_depends_unharmful_but_finish_is_not_suppressed(self):
        for reason, unharmful, expected in ((7,False,1),(7,True,0),(2,False,0)):
            f, a = Fixture(), actor(recycle_delay=0.0)
            a.options = replace(a.options, unharmful=unharmful)
            f.runtime.finish(a, reason, finish_source=EntityPtr.capture(None))
            self.assertEqual(f.ledger.counters.valid_missed, expected)
            self.assertTrue(a.recycled)

    def test_ordinary_finished_killed_and_valid_counters_are_separate(self):
        f, a = Fixture(), actor()
        a.options = EnemyFinishOptions(False, True, False, False, 2, False)
        a.finish_reason = 7
        f.ledger.on_unit_finished(a)
        self.assertEqual((f.ledger.counters.finished,f.ledger.counters.killed,
            f.ledger.counters.valid_finished,f.ledger.counters.valid_killed,
            f.ledger.counters.valid_missed),(1,1,1,0,1))
        a.is_invalid_killed = True
        f.ledger.on_unit_finished(a)
        self.assertEqual(f.ledger.counters.finished,2)
        self.assertEqual(f.ledger.counters.valid_finished,1)

    def test_override_negative_kill_delta_clamps_after_int32_wrap(self):
        f, a = Fixture(), actor(is_override_kill_count=True, override_kill_count=-5)
        a.options = EnemyFinishOptions(False, False, False, False, 2, False)
        a.finish_reason = 2
        f.ledger.counters.valid_killed = 2
        f.ledger.on_unit_finished(a)
        self.assertEqual(f.ledger.counters.valid_killed,0)
        self.assertEqual(f.ledger.counters.valid_finished,0)
        f.ledger.counters.finished = (1<<31)-1
        f.ledger.on_unit_finished(a)
        self.assertEqual(f.ledger.counters.finished,-(1<<31))

    def test_remove_first_reference_only_and_future_groups_stop_at_first_match(self):
        f, a = Fixture(), actor()
        other = actor(identity=NpcEntity("other",24,True,True))
        f.ledger.wave[:] = [a,other,a]
        f.ledger.final[:] = [a,other,a]
        f.ledger.future_groups = ([a],[a])
        f.ledger.on_unit_finished(a)
        self.assertEqual(f.ledger.wave,[other,a])
        self.assertEqual(f.ledger.future_groups,([],[a]))
        a.identity.uid = 0
        f.ledger.on_enemy_recycled(a)
        self.assertEqual(f.ledger.final,[other,a])

    def test_distinct_wrappers_share_the_same_native_entity_reference(self):
        f,a=Fixture(),actor()
        wrapper=replace(a)
        f.ledger.final.append(a)
        f.ledger.on_enemy_recycled(wrapper)
        self.assertEqual(f.ledger.final,[])

    def test_declared_factory_state_fields_are_updated_on_the_same_identity(self):
        from dataclasses import dataclass
        @dataclass(eq=False)
        class PreparedStateIdentity(NpcEntity):
            state_id: int = 1
            finish_reason: int = 0
        entity=PreparedStateIdentity('prepared factory',24,True,True)
        f,a=Fixture(),actor(identity=entity)
        f.runtime.finish(a,7,finish_source=EntityPtr.capture(None))
        self.assertIs(a.identity,entity)
        self.assertEqual((entity.state_id,entity.finish_reason,entity.uid,entity.alive),(-1,7,0,False))

    def test_final_predicate_does_not_generate_full_map_win(self):
        f, a = Fixture(), actor()
        self.assertFalse(f.ledger.final_not_finished(mode_blocks=False,block_keys=(),source=SOURCE))
        self.assertTrue(f.ledger.final_not_finished(mode_blocks=True,block_keys=(),source=SOURCE))
        f.ledger.final.append(a)
        self.assertTrue(f.ledger.final_not_finished(mode_blocks=False,block_keys=(),source=SOURCE))
        self.assertFalse(f.runtime.info()["battle_ready"])
        self.assertFalse(f.runtime.info()["full_map_win_generated"])

    def test_invalid_context_rejected(self):
        f, a = Fixture(), actor()
        with self.assertRaises(UnverifiedNpcLifecycle):
            f.runtime.finish(a,1,finish_source=EntityPtr.capture(None))
        with self.assertRaises(UnverifiedNpcLifecycle):
            SchedulerLedger(use_recycle_to_finish_scheduler=True,counters=f.ledger.counters,
                remove_runtime_route=lambda i: None,source=SOURCE,fresh_event_pool=False)
        with self.assertRaises(UnverifiedNpcLifecycle):
            EnemyFinishOptions(1,False,True,True,11,False)

    def test_old_ordinary_lifecycle_npc_guard_still_rejects(self):
        r=LifecycleRuntime(initial_life=3,initial_temp_life=0,dt=FP(143165440),
            use_recycle_to_finish_scheduler=True,context_source=SOURCE)
        with self.assertRaises(UnverifiedMechanism) as caught:
            r.spawn("npc","enemy_3001_upeopl",max_hp=FP.from_int32(100),
                birth_delay=0.0,recycle_delay=0.3,life_point_reduce=0,managed=True,
                wave_block=False,not_count_in_total=True,lifecycle_templates=())
        self.assertIn("active lifecycle templates",str(caught.exception))


if __name__ == "__main__":
    unittest.main()

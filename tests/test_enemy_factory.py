"""Source and lifecycle boundaries for the staged NPC factory component."""
from dataclasses import replace
import json
from pathlib import Path
import tempfile
import unittest

from arknights_probe.data import Dataset
from arknights_probe.enemy_factory import (
    INPUTS, CursorPreparationReceipt, EnemyFactoryCallbacks, EnemyFactoryContext,
    EnemyFactoryRuntime, FactoryPhaseReceipt, PreparedFactoryRoute,
    RegistrationReceipt, UnityAllocationReceipt, UnverifiedFactoryContext, prepare_enemy,
)
from arknights_probe.fp import FP
from arknights_probe.npc_actions import EntityPtr
from arknights_probe.npc_summon import SummonOptions

ROOT = Path(__file__).resolve().parents[1]
DT = FP(143165440)


class FactoryFixture:
    """All providers are declared test fixtures, never Unity/native results."""
    def __init__(self, prepared, *, controller_state=True, delayed_tile=False, born_hook=None):
        self.prepared, self.frame, self.time = prepared, 0, FP(0)
        self.log = []
        self.cursor = object()
        self.born_hook = born_hook
        context = EnemyFactoryContext("explicit test fixture; no live Unity", True, True,
                                      controller_state, True, delayed_tile, False)

        def phase(actor, name, payload):
            self.log.append((name, actor, actor.state_id, actor.initialized, actor.borned, actor.hp.raw, payload))
            return FactoryPhaseReceipt(actor.token, actor.uid, name, "explicit test-only provider")

        def born(actor):
            self.log.append(("entity_event0", actor, actor.state_id, actor.initialized, actor.borned))

        def buffs(actor):
            self.log.append(("buff_owner_event12", actor, actor.state_id, actor.initialized, actor.borned))
            if self.born_hook:
                self.born_hook(actor)

        def register(actor):
            self.log.append(("registration", actor, actor.state_id, actor.initialized, actor.borned))
            return RegistrationReceipt(actor.token, actor.uid, True, "explicit test registration provider")

        def transition(actor, old, new):
            self.log.append(("admission", actor, old, new))
            return True

        callbacks = EnemyFactoryCallbacks(phase,
            lambda actor, route: CursorPreparationReceipt(actor.token, actor.uid, self.cursor, "explicit cursor provider"),
            born, buffs, register, lambda actor: self.log.append(("enemy_on_born", actor)), transition,
            lambda actor, dt: self.log.append(("move", actor, self.frame)))
        self.runtime = EnemyFactoryRuntime(context, callbacks, lambda: (self.frame, self.time))
        self.receipt = UnityAllocationReceipt("test_npc", 2, prepared.prefab_key,
            prepared.prefab_bundle_sha256, prepared.enemy_script_path_id, True, True, True,
            "explicit allocation/Awake/reset/controller receipt; no game execution")
        self.route = PreparedFactoryRoute(object(), 0, (1.0, 2.0), (0.25, -0.25),
            (2,1), (2,3), (2,1), False, "explicit prepared Route getters")
        self.options = SummonOptions(True, True, False, True, 0)

    def spawn(self):
        actor = self.runtime.allocate(self.prepared, self.receipt)
        return self.runtime.spawn(actor, self.route, self.options)

    def tick(self, actor, delta=DT):
        self.frame += 1
        self.time += delta
        return self.runtime.tick_birth(actor, delta)


class EnemyFactoryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(ROOT / "data/manifest.json")
        cls.upeopl = prepare_enemy(cls.dataset, "enemy_3001_upeopl")
        cls.shdopl = prepare_enemy(cls.dataset, "enemy_2133_shdopl")

    def test_real_map_refs_prefabs_and_blackboard_binding(self):
        u, h = self.upeopl, self.shdopl
        self.assertEqual(u.reference["level"], 0)
        self.assertEqual(h.reference["level"], 0)
        self.assertEqual(u.attributes["maxHp"], FP.from_float32(3500))
        self.assertEqual(h.attributes["maxHp"], FP.from_float32(5000))
        self.assertEqual((u.delay_to_born,h.delay_to_born), (0.0,1.0))
        self.assertEqual(u.common_ability_templates, ("empty",))
        self.assertEqual(u.talents[0].template_keys, ("upeople_t","upeople_t_1"))
        self.assertEqual(u.talents[0].blackboard_rows[0].value, -1.0)
        self.assertEqual(h.talents[0].blackboard_rows[0].value_str, "enemy_3001_upeopl")
        # False optional values remain source declarations, not a forced zero.
        self.assertFalse(h.reference["overwrittenData"]["attributes"]["maxHp"]["m_defined"])

    def test_source_tampering_is_rejected_before_allocation(self):
        d = json.loads(INPUTS.read_text(encoding="utf-8"))
        d["selected"][1]["enemy_component"]["fields"]["_delayToBorn"] = 9.0
        with tempfile.TemporaryDirectory(dir=ROOT / "evidence") as tmp:
            path = Path(tmp) / "changed_inputs.json"
            path.write_text(json.dumps(d), encoding="utf-8")
            with self.assertRaises(UnverifiedFactoryContext):
                prepare_enemy(self.dataset, "enemy_3001_upeopl", inputs_path=path)

    def test_unknown_enemy_and_context_paths_rejected(self):
        with self.assertRaises(UnverifiedFactoryContext):
            prepare_enemy(self.dataset, "enemy_1034_laxe")
        for changes in ({"native_default_no_hotfix":False}, {"no_global_numeric_modifiers":False},
                        {"default_game_mode":False}, {"is_dummy":True}, {"controller_state_nonzero":1}):
            with self.assertRaises(UnverifiedFactoryContext):
                replace(FactoryFixture(self.upeopl).runtime.context, **changes)

    def test_allocation_is_uninitialized_and_unity_null_factory_is_null(self):
        f = FactoryFixture(self.upeopl)
        self.assertIsNone(f.runtime.allocate(f.prepared, replace(f.receipt,unity_exists=False)))
        actor = f.runtime.allocate(f.prepared, f.receipt)
        self.assertEqual((actor.state_id,actor.hp.raw,actor.initialized,actor.borned,actor.alive),(-1,0,False,False,False))
        with self.assertRaises(UnverifiedFactoryContext):
            f.runtime.allocate(f.prepared,f.receipt)
        g = FactoryFixture(self.upeopl)
        with self.assertRaises(UnverifiedFactoryContext):
            g.runtime.allocate(g.prepared,replace(g.receipt,enemy_script_path_id=999))
        with self.assertRaises(UnverifiedFactoryContext):
            g.runtime.allocate(g.prepared,replace(g.receipt,controller_instances_ready=False))

    def test_init_hp_birth_registration_order_and_same_identity(self):
        f = FactoryFixture(self.upeopl)
        actor = f.spawn()
        labels = [x[0] for x in f.log]
        attach = f.log[labels.index("enemy_on_init_controllers_skills_talent_attach")]
        self.assertEqual(attach[2:6], (-1,False,False,0))
        born = f.log[labels.index("entity_event0")]
        self.assertEqual(born[2:], (6,True,False))
        self.assertLess(labels.index("entity_event0"),labels.index("buff_owner_event12"))
        self.assertLess(labels.index("buff_owner_event12"),labels.index("registration"))
        self.assertLess(labels.index("registration"),labels.index("unit_on_born_start_common_and_dynamic_abilities"))
        self.assertLess(labels.index("unit_on_born_start_common_and_dynamic_abilities"),
                        labels.index("unit_on_born_controller_event_and_owner_post_born"))
        self.assertLess(labels.index("unit_on_born_controller_event_and_owner_post_born"),labels.index("enemy_on_born"))
        self.assertLess(labels.index("enemy_on_born"),labels.index("bobject_borned_written"))
        self.assertTrue(all(x[1] is actor for x in f.log))
        self.assertIs(actor.cursor,f.cursor)
        self.assertIs(EntityPtr.capture(actor).resolve(),actor)
        self.assertEqual(actor.talent_blackboards["Dead"].integer("value"),-1)
        self.assertTrue(actor.registered and actor.borned and actor.initialized and actor.alive)
        self.assertEqual(actor.state_id,6)

    def test_spawn_rejects_initialized_or_copied_actor(self):
        f = FactoryFixture(self.upeopl)
        actor = f.spawn()
        with self.assertRaises(UnverifiedFactoryContext):
            f.runtime.spawn(actor,f.route,f.options)
        with self.assertRaises(UnverifiedFactoryContext):
            f.runtime.tick_birth(replace(actor),DT)

    def test_replaced_preparation_cannot_forge_source_hp_or_birth_delay(self):
        f=FactoryFixture(self.upeopl)
        for replaced in (replace(self.upeopl),replace(self.upeopl,delay_to_born=4.0),
                         replace(self.upeopl,attributes={"maxHp":FP.from_int32(1)})):
            with self.assertRaises(UnverifiedFactoryContext):
                f.runtime.allocate(replaced,f.receipt)

    def test_upeopl_zero_birth_waits_one_state_tick_then_moves_next(self):
        f = FactoryFixture(self.upeopl)
        actor = f.spawn()
        self.assertFalse(f.tick(actor))
        self.assertEqual(actor.state_id,1)
        self.assertFalse(any(x[0]=="move" for x in f.log))
        labels=[x[0] for x in f.log]
        self.assertLess(labels.index("born_state_exit_animation"),labels.index("move_state_enter"))
        self.assertTrue(f.tick(actor))
        self.assertEqual(next(x[2] for x in f.log if x[0]=="move"),2)

    def test_shdopl_one_second_uses_actual_dt_without_force_move(self):
        f=FactoryFixture(self.shdopl)
        actor=f.spawn()
        for _ in range(30):
            self.assertFalse(f.tick(actor))
        self.assertEqual(actor.state_id,6) # 30*143165440 is just short of FP.One.
        self.assertFalse(f.tick(actor))
        self.assertEqual(actor.state_id,1)
        self.assertTrue(f.tick(actor))

    def test_birth_boundary_is_raw_le_zero_not_mathutil_epsilon(self):
        for remaining in (1,42949,42950,42951,DT.raw):
            f=FactoryFixture(self.upeopl);actor=f.spawn()
            actor.born_remaining=FP(DT.raw+remaining)
            self.assertFalse(f.tick(actor))
            self.assertEqual(actor.state_id,6)
            self.assertFalse(f.tick(actor,FP(remaining)))
            self.assertEqual(actor.state_id,1)

    def test_passive_interruption_is_not_overwritten_by_born_write(self):
        f=FactoryFixture(self.shdopl,born_hook=lambda actor:setattr(actor,"state_id",11))
        actor=f.spawn()
        self.assertEqual(actor.state_id,11)
        with self.assertRaises(UnverifiedFactoryContext):
            f.tick(actor)

    def test_controller_state_zero_skips_registration_only(self):
        f=FactoryFixture(self.upeopl,controller_state=False,delayed_tile=True)
        actor=f.spawn()
        self.assertFalse(actor.registered)
        self.assertNotIn("registration",[x[0] for x in f.log])
        self.assertIn("enemy_tile_cache_delayed",[x[0] for x in f.log])
        self.assertTrue(actor.borned)

    def test_options_unharmful_is_independent_of_disappearance_and_hp(self):
        f=FactoryFixture(self.shdopl);actor=f.spawn()
        self.assertEqual(actor.life_point_reduce,0)
        self.assertEqual(actor.hp,FP.from_float32(5000))
        g=FactoryFixture(self.shdopl);g.options=replace(g.options,unharmful=False)
        actor2=g.spawn();self.assertEqual(actor2.life_point_reduce,1)
        self.assertEqual(actor2.state_id,6)
        for options in (object(),replace(f.options,spawned_count=True),replace(f.options,action_data={})):
            h=FactoryFixture(self.upeopl);a=h.runtime.allocate(h.prepared,h.receipt)
            with self.assertRaises(UnverifiedFactoryContext):h.runtime.spawn(a,h.route,options)

    def test_missing_phase_cursor_or_register_receipt_fails_closed(self):
        for replacement in (
            {"external_phase":lambda a,p,x:None},
            {"build_cursor":lambda a,r:CursorPreparationReceipt(a.token,a.uid+1,object(),"test")},
            {"register_unit":lambda a:RegistrationReceipt(a.token,a.uid,False,"test")},
        ):
            f=FactoryFixture(self.upeopl)
            f.runtime.callbacks=replace(f.runtime.callbacks,**replacement)
            with self.assertRaises(UnverifiedFactoryContext):f.spawn()

    def test_fsm_admission_cannot_sneak_in_state_mutation(self):
        f=FactoryFixture(self.upeopl)
        def mutate(actor,old,new):actor.state_id=new;return True
        f.runtime.callbacks=replace(f.runtime.callbacks,fsm_transition=mutate)
        with self.assertRaises(UnverifiedFactoryContext):f.spawn()

    def test_hidden_origin_route_is_explicitly_rejected(self):
        f=FactoryFixture(self.upeopl);f.route=replace(f.route,origin_tile_hidden=True)
        with self.assertRaises(UnverifiedFactoryContext):f.spawn()


if __name__=="__main__":unittest.main()

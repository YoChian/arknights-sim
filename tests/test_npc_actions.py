from pathlib import Path
import json
import struct
import unittest

from arknights_probe.fp import FP
from arknights_probe.npc_actions import (
    NpcEntity, EntityPtr, BuffPtr, NpcBuff, DataPair, NpcBlackboard,
    NpcContext, NpcSnapshot, NpcCallbacks, NpcActionRuntime, ActionNode,
    check_execute, run_action_list, resolve_action_target, insert_buff_by_priority,
    bind_talent_blackboard, native_fp_ge, UnverifiedNpcContext,
)


def entity(token="host", uid=12, alive=True, exists=True):
    return NpcEntity(token, uid, exists, alive, grid_position=(2, 5))


def buff(template="enemy_shdopl_finish", *, owner=None, source=None, bb=None, priority=2000, uid=31):
    owner = owner or entity("npc", 17)
    source = source or entity()
    return NpcBuff("buff:"+template, uid, template, owner, EntityPtr.capture(source),
                   bb or NpcBlackboard(), priority, True)


def runtime(callbacks=None, context=None):
    return NpcActionRuntime(context or NpcContext(), callbacks or NpcCallbacks(),
                            no_hotfix=True, mode="default_noncoop", dispatch_source="explicit initialized fixture")


class PointerAndContextTests(unittest.TestCase):
    def test_uid_equality_and_destroyed_gate_are_independent_of_alive(self):
        e = entity(alive=False)
        self.assertIs(EntityPtr.capture(e).resolve(), e)
        p = EntityPtr.capture(e)
        e.uid += 1
        self.assertIsNone(p.resolve())
        e.uid -= 1
        e.unity_exists = False
        self.assertIsNone(p.resolve())
        self.assertIsNone(EntityPtr(None, 123).resolve())

    def test_matching_zero_and_uint32_max_are_valid(self):
        for uid in [0, 0xffffffff]:
            e = entity(uid=uid)
            self.assertIs(EntityPtr.capture(e).resolve(), e)
        for uid in [-1, 1<<32, True]:
            with self.assertRaises(UnverifiedNpcContext):
                EntityPtr(None, uid)

    def test_buff_source_is_guarded_but_owner_and_snapshot_source_are_direct(self):
        b = buff()
        snapshot = NpcSnapshot(source=b.source.entity, buff=b)
        self.assertIs(resolve_action_target(snapshot, 2), b.source.entity)
        b.source.entity.uid += 1
        self.assertIsNone(resolve_action_target(snapshot, "BUFF_SOURCE"))
        self.assertIs(resolve_action_target(snapshot, "SOURCE"), b.source.entity)
        self.assertIs(resolve_action_target(snapshot, "BUFF_OWNER"), b.owner)

    def test_unknown_snapshot_slots_and_missing_buff_are_rejected(self):
        with self.assertRaises(UnverifiedNpcContext):
            resolve_action_target(NpcSnapshot(), "MODIFIER_SOURCE")
        with self.assertRaises(UnverifiedNpcContext):
            resolve_action_target(NpcSnapshot(), 3)

    def test_nested_guard_restores_all_supported_slots_after_exception(self):
        original = NpcSnapshot(entity("original", 1), entity("target", 2))
        c = NpcContext(original)
        with c.change_guard(source=entity("outer", 3)):
            outer = c.current
            with self.assertRaises(RuntimeError):
                with c.change_guard(source=entity("inner", 4), target=None):
                    self.assertEqual(c.current.source.token, "inner")
                    raise RuntimeError("external fixture exception")
            self.assertEqual(c.current, outer)
        self.assertEqual(c.current, original)
        self.assertEqual(c.depth, 0)

    def test_restored_pointer_stack_revalidates_after_uid_reuse(self):
        e = entity()
        c = NpcContext(NpcSnapshot(source=e))
        with c.change_guard(source=None):
            e.uid += 1
        self.assertIsNone(c.current.source)

    def test_duplicate_guard_snapshots_stale_pointer_as_null(self):
        e = entity()
        c = NpcContext(NpcSnapshot(source=e))
        original_uid = e.uid
        e.uid += 1
        with c.change_guard(main_target=None):
            e.uid = original_uid
            self.assertIsNone(c.current.source)
        self.assertIs(c.current.source,e)


class BlackboardTests(unittest.TestCase):
    def test_copy_preserves_order_and_number_scan_skips_string_rows(self):
        b = NpcBlackboard([DataPair("VALUE", 0, "text"), DataPair("value", -1.1), DataPair("value", 99)])
        self.assertEqual(b.integer("VaLuE"), -2)
        self.assertEqual(b.string("value"), "text")
        self.assertEqual(len(b.entries), 3)
        self.assertEqual(b.fp("missing", FP(42)), FP(42))

    def test_assignment_replaces_first_match_and_clears_other_payload(self):
        b = NpcBlackboard([DataPair("VaLuE", 7), DataPair("value", 8)])
        b.assign_string("VALUE", "enemy")
        self.assertEqual(b.entries[0], DataPair("value", 0, "enemy"))
        self.assertEqual(b.number("value"), 8)
        b.assign_number("VALUE", 2.5)
        self.assertEqual(b.entries[0], DataPair("value", 2.5))
        self.assertEqual(b.integer("value"), 2)

    def test_native_integer_floor_boundaries(self):
        for value, expected in [(-1.1,-2),(-1.5,-2),(-.01,-1),(-0.0,0),(.5,0),(1.5,1),(1.9,1),(2.5,2)]:
            self.assertEqual(NpcBlackboard([DataPair("value", value)]).integer("value"), expected)

    def test_dead_prefix_is_ordinal_ignore_case_and_does_not_match_deadly(self):
        rows = [DataPair("dead.value", -1), DataPair("DeAd.OTHER", 3), DataPair("deadly.value", 90)]
        b = bind_talent_blackboard(rows, "Dead")
        self.assertEqual(b.integer("value"), -1)
        self.assertEqual(b.integer("other"), 3)
        self.assertEqual([r.key for r in b.entries], ["value", "other"])

    def test_numeric_then_string_pass_keeps_string_and_resets_numeric_payload(self):
        rows = [DataPair("summon.enemy_key", 7, "enemy_3001_upeopl")]
        b = bind_talent_blackboard(rows, "summon")
        self.assertEqual(b.entries, [DataPair("enemy_key", 0, "enemy_3001_upeopl")])
        self.assertEqual(b.number("enemy_key", 41), 41)
        self.assertEqual(b.string("enemy_key"), "enemy_3001_upeopl")

    def test_empty_key_getters_use_defaults_and_empty_value_str_is_numeric(self):
        b = NpcBlackboard([DataPair("", 9, "not empty"), DataPair("lock", 2, "")])
        self.assertEqual(b.number("", 4), 4)
        self.assertEqual(b.string("", "default"), "default")
        self.assertEqual(b.integer("lock"), 2)

    def test_copy_is_independent_and_unknown_culture_unicode_nan_rejected(self):
        b = NpcBlackboard([DataPair("lock", 0)])
        clone = b.clone(); clone.assign_number("lock", 1)
        self.assertEqual(b.integer("lock"), 0)
        with self.assertRaises(UnverifiedNpcContext):
            NpcBlackboard(culture="unknown-live-culture")
        with self.assertRaises(UnverifiedNpcContext):
            DataPair("İ", 1)
        with self.assertRaises(UnverifiedNpcContext):
            DataPair("value", float("nan"))


class ActionFlowTests(unittest.TestCase):
    def test_condition_truth_table(self):
        for previous in [False, True]:
            for condition in [-1,0,1,2,3]:
                self.assertEqual(check_execute(condition, previous),
                                 {0:True,1:previous,2:not previous}.get(condition,False))

    def test_false_execute_short_circuits_default_but_ifnot_can_recover(self):
        reached = []
        first = ActionNode("false", lambda: False)
        out = run_action_list((first,ActionNode("lock",lambda: reached.append("lock") or True)))
        self.assertEqual(out.executed, ("false",))
        self.assertEqual(out.stopped_before, "lock")
        self.assertEqual(reached, [])
        out = run_action_list((first,ActionNode("IfNot",lambda: True,2),ActionNode("lock",lambda: reached.append("lock") or True)))
        self.assertTrue(out.result)
        self.assertEqual(reached, ["lock"])

    def test_allowed_source_failure_and_nonboolean_callback_are_rejected(self):
        out = run_action_list((ActionNode("wrong",lambda: True,0,2),),source_type=1)
        self.assertEqual(out.stopped_before, "wrong")
        with self.assertRaises(UnverifiedNpcContext):
            run_action_list((ActionNode("bad",lambda: None),))

    def test_native_ge_inclusive_epsilon_boundary_and_wrapped_subtraction(self):
        one = 1<<32
        self.assertFalse(native_fp_ge(FP(one-42951),FP(one)))
        self.assertTrue(native_fp_ge(FP(one-42950),FP(one)))
        self.assertTrue(native_fp_ge(FP(one-42949),FP(one)))
        self.assertFalse(native_fp_ge(FP(-(1<<63)), FP(-(1<<63))))


class PriorityTests(unittest.TestCase):
    def test_high_priority_first_equal_priority_arrival_order(self):
        refs = ()
        for i,p in enumerate([0,2000,0,2000,1000]):
            b = buff(priority=p,uid=i+1);b.token = str(i)
            refs = insert_buff_by_priority(refs,BuffPtr(b,b.uid))
        self.assertEqual([r.buff.token for r in refs],["1","3","4","0","2"])

    def test_invalid_incoming_appends_and_invalid_existing_is_skipped(self):
        stale = buff(priority=10000,uid=1);r = BuffPtr(stale,1);stale.uid = 2
        new = buff(priority=3,uid=3);valid = BuffPtr(new,3)
        self.assertEqual(insert_buff_by_priority((r,),valid),(valid,r))
        self.assertEqual(insert_buff_by_priority((valid,),r),(valid,r))


class NpcEventTests(unittest.TestCase):
    def test_event10_finish7_reenters_event4_then_short_circuits_lock_clear(self):
        b = buff();calls = []
        c = NpcContext(NpcSnapshot(source=entity("caller",1)))
        callbacks = NpcCallbacks(
            restore_to=lambda req: calls.append(("restore",req.target.token,req.source.token)) or True,
            set_disappeared=lambda e,v:calls.append(("hide",e.token,v)),
            finish_buffs=lambda e,k:calls.append(("remove",e.token,k)),
            clear_buffs=lambda e:calls.append(("clear",e.token)),
            modify_life=lambda req:calls.append(("life",req.delta)) or True,
        )
        r = runtime(callbacks,c)
        def finish(e):
            calls.append(("finish",7));e.alive = False
            r.owner_finish(b,7)
        callbacks.finish_no_reason = finish
        result = r.run_buff_event(b,10)
        self.assertFalse(result.result)
        self.assertEqual(result.stopped_before,"AssignValueToBB")
        self.assertEqual(sum(x[0]=="restore" for x in calls),2)
        self.assertEqual(b.blackboard.number("lock",-1),-1)
        self.assertFalse(any(x[0] in ("life","clear") for x in calls))
        self.assertEqual(c.current.source.token,"caller")
        self.assertEqual(c.depth,0)
        events = [x[2] for x in r.trace if x[0]=="event"]
        self.assertEqual(events,[10,4])

    def test_event4_existing_lock_stops_at_ifnot_before_restore(self):
        b = buff(bb=NpcBlackboard([DataPair("lock",1)]))
        result = runtime().run_buff_event(b,4)
        self.assertEqual(result.executed,("FilterByBlackboardValue",))
        self.assertEqual(result.stopped_before,"IfNot")

    def test_death2_uses_bound_minus_one_and_finish7_does_not(self):
        b = buff("upeople_t",bb=bind_talent_blackboard([DataPair("dead.value",-1)],"Dead"))
        calls = []
        r = runtime(NpcCallbacks(modify_life=lambda req:calls.append(req) or True))
        r.owner_finish(b,7)
        self.assertEqual(calls,[])
        r.owner_finish(b,2)
        self.assertEqual(len(calls),1)
        self.assertEqual((calls[0].delta,calls[0].branch,calls[0].is_reach_exit),(-1,0,False))
        self.assertIs(calls[0].source,b.owner)
        self.assertEqual(r.context.depth,0)

    def test_owner_finish_populates_main_target_not_buff_source(self):
        b = buff("upeople_t",bb=NpcBlackboard([DataPair("value",-1)]))
        killer = entity("killer",99)
        seen = []
        r = runtime(NpcCallbacks(modify_life=lambda req:seen.append(req.snapshot) or True))
        r.owner_finish(b,2,finish_source=killer)
        self.assertIs(seen[0].main_target,killer)
        self.assertIs(seen[0].source,b.source.entity)

    def test_start_uses_bound_enemy_key_grid_and_does_not_synchronously_create_child(self):
        b = buff("enemy_shdopl_passive",bb=bind_talent_blackboard([DataPair("summon.enemy_key",0,"enemy_3001_upeopl")],"summon"))
        seen = []
        r = runtime(NpcCallbacks(schedule_summon=lambda req:seen.append(req),set_disappeared=lambda e,v:seen.append((e.token,v))))
        result = r.run_buff_event(b,0)
        self.assertTrue(result.result)
        self.assertEqual(seen[0].enemy_key,"enemy_3001_upeopl")
        self.assertEqual(seen[0].host_grid_position,(2,5))
        self.assertIsNot(seen[0].blackboard,b.blackboard)
        self.assertEqual(seen[1],("npc",True))

    def test_reused_buff_source_makes_restore_return_false_before_any_provider(self):
        b = buff();b.source.entity.uid += 1
        result = runtime().run_buff_event(b,10)
        self.assertEqual(result.stopped_before,"SetDisappear")
        self.assertEqual(result.executed,("ForceSetToSourcePosition",))

    def test_explicit_scope_and_unclosed_audio_or_tween_paths_are_rejected(self):
        with self.assertRaises(UnverifiedNpcContext):
            NpcActionRuntime(NpcContext(),NpcCallbacks(),no_hotfix=False,mode="default_noncoop",dispatch_source="fixture")
        with self.assertRaises(UnverifiedNpcContext):
            NpcActionRuntime(NpcContext(),NpcCallbacks(),no_hotfix=True,mode="live_rogue_unknown",dispatch_source="fixture")
        with self.assertRaises(UnverifiedNpcContext):
            runtime().run_buff_event(buff("upeople_t_1"),3)
        b = buff();b.owner.is_tile_unit = True
        with self.assertRaises(UnverifiedNpcContext):
            runtime().run_buff_event(b,4)


class CrossLanguageReferenceTests(unittest.TestCase):
    def test_independent_csharp_vectors(self):
        path = Path(__file__).resolve().parents[1]/"evidence/npc_actions/reference_vectors.json"
        d = json.loads(path.read_text("utf8"))
        self.assertFalse(d["game_code_loaded"])
        self.assertGreaterEqual(len(d["vectors"]),100)
        for item in d["vectors"]:
            v,e = item["input"],item["expected"]
            with self.subTest(kind=v["kind"],id=v["id"]):
                if v["kind"] == "floor":
                    self.assertEqual(NpcBlackboard([DataPair("value",v["value"])]).integer("value"),e["value"])
                elif v["kind"] == "ge":
                    self.assertEqual(native_fp_ge(FP(v["left"]),FP(v["right"])),e["value"])
                elif v["kind"] == "condition":
                    self.assertEqual(check_execute(v["condition"],v["previous"]),e["value"])
                elif v["kind"] == "uid":
                    obj = None if v["null"] else entity(uid=v["current"],exists=v["exists"],alive=v["alive"])
                    self.assertEqual(EntityPtr(obj,v["saved"]).resolve() is not None,e["value"])
                elif v["kind"] == "bind":
                    rows = [DataPair(x["key"],x["value"],x.get("text")) for x in v["rows"]]
                    got = bind_talent_blackboard(rows,v["prefix"])
                    self.assertEqual([{"key":x.key,"value_bits":struct.unpack("<I",struct.pack("<f",x.value))[0],"text":x.value_str} for x in got.entries],
                                     [{"key":x["key"],"value_bits":x["value_bits"],"text":x["text"]} for x in e["rows"]])


if __name__ == "__main__":
    unittest.main()

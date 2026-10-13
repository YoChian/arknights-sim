from dataclasses import dataclass
import json
from pathlib import Path
import unittest

from arknights_probe.fp import FP, MAX_VALUE_RAW
from arknights_probe.npc_actions import (
    NpcEntity, NpcBuff, NpcBlackboard, DataPair, EntityPtr, BuffPtr,
    NpcCallbacks, NpcActionRuntime, NpcContext,
)
from arknights_probe.buff_container import (
    SortedDoubleBufferedBuffList, BuffInitShape, BuffContainerHooks,
    NpcBuffContainer, UnverifiedBuffContainer, lifetime_is_zero,
)


def entity(token="owner", uid=1):
    return NpcEntity(token, uid, True, True, grid_position=(2, 3))


def buff(owner, token, uid, priority=0, template="empty", source=None, bb=()):
    return NpcBuff(token, uid, template, owner, EntityPtr.capture(source or owner),
                   NpcBlackboard(bb), priority, True, True)


@dataclass
class Packet:
    source: EntityPtr
    target: EntityPtr
    shared_flags: int = 0
    skip_sp_recovery: bool = False
    cancel_reason: int = -1
    final_delta: FP = FP(-2147483648000)


class Fixture:
    def __init__(self):
        self.log = []
        self.owner = entity()
        self.containers = {}
        self.on_restore = None
        self.on_schedule = None
        self.on_recycle = None
        callbacks = NpcCallbacks(
            restore_to=self.restore,
            set_disappeared=lambda target, value: self.log.append(("disappear", target.token, value)),
            finish_buffs=lambda target, key: self.containers[target].finish_buffs_by_id(key),
            finish_no_reason=self.finish7,
            clear_buffs=lambda target: self.containers[target].clear(),
            schedule_summon=self.schedule,
            modify_life=lambda request: self.log.append(("life", request.delta)) or True,
        )
        self.actions = NpcActionRuntime(NpcContext(), callbacks, no_hotfix=True,
                                       mode="default_noncoop", dispatch_source="owned native container fixture")
        self.hooks = BuffContainerHooks(
            attribute_modifier=lambda b, enabled: self.log.append(("attribute", b.token, enabled)),
            owner_buff_started=lambda b: self.log.append(("owner_start", b.token)),
            owner_buff_finished=lambda b, finished: self.log.append(("owner_finish_buff", b.token, finished)),
            recycle=self.recycle,
            override_transition=self.override,
            opaque_event=lambda b, event, snapshot: self.log.append(("explicit_audio", b.token, event)),
            owner_buff_late_enabled=lambda b: self.log.append(("owner_late", b.token)),
        )
        self.c = self.new_container(self.owner)

    def new_container(self, owner):
        c = NpcBuffContainer(owner, self.actions, self.hooks, no_hotfix=True)
        self.containers[owner] = c
        return c

    def add(self, b, *, active=True, c=None, lifetime=None, override_key=""):
        return (c or self.c).add_initialized(b, BuffInitShape(
            b.token, lifetime or FP.from_int32(-1), "explicit post-Reset test receipt",
            override_key=override_key), owner_active=active)

    def override(self, operation, b, c):
        self.log.append(("override", operation, b.token))
        # Explicit, single-member fixture. It is not a native override engine.
        if operation == "register":
            c.set_enabled(b, True)

    def schedule(self, request):
        self.log.append(("summon", request.enemy_key))
        if self.on_schedule:
            self.on_schedule(request)

    def restore(self, request):
        self.log.append(("restore", request.target.token, request.source.token))
        if self.on_restore:
            return self.on_restore(request)
        return True

    def finish7(self, target):
        target.alive = False
        c = self.containers[target]
        c.on_owner_finish(7, self.actions.context.current.source)
        c.clear(is_owner_finished=True)

    def recycle(self, b, deferred):
        self.log.append(("pool", b.token, deferred))
        if self.on_recycle:
            self.on_recycle(b, deferred)


class DoubleBufferedTests(unittest.TestCase):
    def make(self, priorities=(0, 2000, 0)):
        owner = entity()
        values = [buff(owner, str(i), i + 1, p) for i, p in enumerate(priorities)]
        queue = SortedDoubleBufferedBuffList()
        for b in values:
            queue.add(BuffPtr(b, b.uid))
        return queue, values

    def collect(self, queue, backwards=False):
        with queue.iterate(backwards=backwards) as it:
            found = []
            while it.move_next():
                found.append(it.current.buff.token)
            return found

    def test_high_priority_first_and_equal_fifo(self):
        q, _ = self.make()
        self.assertEqual(self.collect(q), ["1", "0", "2"])
        self.assertEqual(self.collect(q, True), ["2", "0", "1"])

    def test_remove_changes_live_but_nested_keeps_outer_snapshot(self):
        q, values = self.make()
        with q.iterate() as outer:
            outer.move_next()
            self.assertTrue(q.remove(values[0]))
            self.assertEqual(self.collect(q), ["1", "0", "2"])
            self.assertEqual(q.depth, 1)
        self.assertEqual(self.collect(q), ["1", "2"])

    def test_new_member_hidden_from_all_nested_iterators(self):
        q, values = self.make((0,))
        with q.iterate() as outer:
            b = buff(values[0].owner, "new", 9, 2000)
            q.add(BuffPtr(b, b.uid))
            self.assertEqual(self.collect(q), ["0"])
            self.assertEqual(self.collect(q, True), ["0"])
            self.assertTrue(outer.move_next())
            self.assertEqual(outer.current.buff.token, "0")
        self.assertEqual(self.collect(q), ["new", "0"])

    def test_clear_live_does_not_clear_nested_snapshot(self):
        q, _ = self.make()
        with q.iterate():
            q.clear()
            self.assertEqual(self.collect(q), ["1", "0", "2"])
        self.assertEqual(self.collect(q), [])

    def test_uid_invalidates_snapshot_immediately(self):
        q, values = self.make((0,))
        with q.iterate() as it:
            values[0].uid += 1
            it.move_next()
            self.assertIsNone(it.current.resolve())
            q.clear_invalid_if_not_loop()
            self.assertEqual(len(q.live), 1)
        q.clear_invalid_if_not_loop()
        self.assertEqual(q.live, [])

    def test_reused_iterators_reset_index_and_dispose_once(self):
        q, _ = self.make()
        first = q.get_enumerator()
        first.move_next()
        first.dispose()
        first.dispose()
        self.assertEqual(q.depth, 0)
        second = q.get_enumerator()
        self.assertIs(first, second)
        self.assertEqual(second.index, -1)
        second.dispose()
        self.assertEqual(len(q.forward_pool), 1)

    def test_exception_disposes_nested_and_outer(self):
        q, _ = self.make()
        with self.assertRaises(RuntimeError):
            with q.iterate():
                with q.iterate(backwards=True):
                    raise RuntimeError("owned callback fixture")
        self.assertEqual(q.depth, 0)
        self.assertEqual((len(q.forward_pool), len(q.backward_pool)), (1, 1))

    def test_depth_overflow_is_explicit_gate(self):
        q, _ = self.make()
        q.depth = 65535
        with self.assertRaises(UnverifiedBuffContainer):
            q.get_enumerator()


class ContainerTests(unittest.TestCase):
    def test_register_then_start_then_enabled(self):
        f = Fixture()
        b = buff(f.owner, "host", 11, template="enemy_shdopl_passive", bb=[DataPair("enemy_key", 0, "enemy_3001_upeopl")])
        observed = []
        f.on_schedule = lambda r: observed.append((f.c.uid_map[11] is b, f.c.state(b).started, f.c.state(b).actually_enabled))
        f.add(b)
        self.assertEqual(observed, [(True, False, False)])
        self.assertTrue(f.c.state(b).started)
        self.assertTrue(f.c.state(b).actually_enabled)

    def test_inactive_register_born_does_not_start_but_tick_does(self):
        f = Fixture()
        b = buff(f.owner, "host", 11, template="enemy_shdopl_passive", bb=[DataPair("enemy_key", 0, "enemy_3001_upeopl")])
        f.add(b, active=False)
        f.c.on_owner_born()
        f.c.on_owner_post_born()
        self.assertFalse(f.c.state(b).started)
        self.assertFalse(any(x[0] == "summon" for x in f.log))
        f.c.tick(FP.from_float32(1 / 30))
        self.assertEqual(sum(x[0] == "summon" for x in f.log), 1)
        self.assertFalse(f.c.state(b).late_enabled)

    def test_tick_starts_disabled_buff_then_skips_late_enable(self):
        f = Fixture()
        b = buff(f.owner, "empty", 11)
        f.add(b, active=False)
        f.c.set_enabled(b, False)
        f.c.tick(FP(100))
        self.assertTrue(f.c.state(b).started)
        self.assertEqual(f.c.state(b).existing_time.raw, 100)
        self.assertFalse(any(x[0] == "owner_late" for x in f.log))

    def test_finish_by_key_only_marks_then_cleanup_removes(self):
        f = Fixture()
        b = buff(f.owner, "key", 11)
        f.add(b)
        f.log.clear()
        f.c.finish_buffs_by_id("key", update_override_map=False)
        self.assertIn(11, f.c.uid_map)
        self.assertEqual(len(f.c.buffs.live), 1)
        self.assertFalse(f.c.state(b).actually_finished)
        self.assertFalse(any(x[0] == "pool" for x in f.log))
        f.c.check_finished()
        self.assertEqual(f.c.uid_map, {})
        self.assertEqual(f.c.buffs.live, [])
        self.assertTrue(f.c.state(b).actually_finished)
        self.assertIn(("pool", "key", False), f.log)

    def test_remove_uid_and_key_exclusion(self):
        f = Fixture()
        a, b = buff(f.owner, "a", 11), buff(f.owner, "b", 12)
        f.c.add_initialized(a, BuffInitShape("same", FP.from_int32(-1), "fixture"), owner_active=True)
        f.c.add_initialized(b, BuffInitShape("same", FP.from_int32(-1), "fixture"), owner_active=True)
        f.c.finish_buffs_by_id("same", excluded_buff=a)
        self.assertFalse(f.c.state(a).marked_finished)
        self.assertTrue(f.c.state(b).marked_finished)
        f.c.remove_uid(11)
        self.assertTrue(f.c.state(a).marked_finished)

    def test_key_match_is_case_sensitive(self):
        f = Fixture()
        b = buff(f.owner, "Mixed", 11)
        f.add(b)
        f.c.finish_buffs_by_id("mixed")
        self.assertFalse(f.c.state(b).marked_finished)

    def test_finish_dispatch_ignores_finished_and_disabled_gate(self):
        f = Fixture()
        host = entity("host", 99)
        f.new_container(host)
        b = buff(f.owner, "finish", 11, 2000, "enemy_shdopl_finish", source=host)
        f.add(b)
        f.c.mark_finish(b)
        f.log.clear()
        f.c.on_owner_finish(7)
        self.assertEqual(sum(x[0] == "restore" for x in f.log), 1)
        self.assertTrue(f.c.state(b).actually_finished)

    def test_damage_skips_finished_and_disabled(self):
        f = Fixture()
        host = entity("host", 99)
        f.new_container(host)
        b = buff(f.owner, "finish", 11, 2000, "enemy_shdopl_finish", source=host)
        f.add(b)
        f.c.set_enabled(b, False)
        f.log.clear()
        f.c.on_take_damage(Packet(EntityPtr.capture(host), EntityPtr.capture(f.owner)))
        self.assertFalse(any(x[0] == "restore" for x in f.log))

    def npc_pair(self):
        f = Fixture()
        host = entity("host", 99)
        hc = f.new_container(host)
        passive = buff(host, "enemy_shdopl_passive", 21, 0, "enemy_shdopl_passive", bb=[DataPair("enemy_key", 0, "enemy_3001_upeopl")])
        f.add(passive, c=hc)
        # Input order is actual common, Dead, Dead audio, additional finish.
        members = [buff(f.owner, "neutral", 10),
                   buff(f.owner, "dead", 11, template="upeople_t", bb=[DataPair("value", -1)]),
                   buff(f.owner, "audio", 12, template="upeople_t_1"),
                   buff(f.owner, "finish", 13, 2000, "enemy_shdopl_finish", source=host)]
        for b in members:
            f.add(b, active=False)
        f.c.tick(FP(100))
        f.log.clear()
        return f, host, hc, passive, members

    def test_real_membership_damage_finish7_reentry_two_restores(self):
        f, host, hc, passive, members = self.npc_pair()
        packet = Packet(EntityPtr.capture(host), EntityPtr.capture(f.owner))
        self.assertIs(f.c.on_take_damage(packet), packet)
        self.assertEqual(sum(x[0] == "restore" for x in f.log), 2)
        self.assertFalse(any(x[0] in ("life", "explicit_audio") for x in f.log))
        self.assertFalse(f.owner.alive)
        self.assertEqual(members[-1].blackboard.integer("lock"), 0)
        self.assertEqual(f.c.buffs.live, [])
        self.assertEqual(f.c.uid_map, {})
        self.assertEqual(f.c.buffs.depth, 0)
        self.assertEqual(f.actions.context.depth, 0)
        self.assertEqual(sum(x[0] == "pool" for x in f.log), 4)
        self.assertTrue(all(x[2] for x in f.log if x[0] == "pool"))
        self.assertTrue(hc.state(passive).marked_finished)
        self.assertFalse(hc.state(passive).actually_finished)
        hc.tick(FP(100))
        self.assertTrue(hc.state(passive).actually_finished)

    def test_cancelled_zero_damage_still_dispatches_container_event10(self):
        f, host, _, _, _ = self.npc_pair()
        packet = Packet(EntityPtr.capture(host), EntityPtr.capture(f.owner), cancel_reason=0, final_delta=FP(0))
        f.c.on_take_damage(packet)
        self.assertEqual(sum(x[0] == "restore" for x in f.log), 2)
        self.assertEqual(packet.cancel_reason, 0)
        self.assertEqual(packet.final_delta.raw, 0)

    def test_death2_dispatches_real_dead_member_and_explicit_audio(self):
        f, host, _, _, _ = self.npc_pair()
        f.owner.alive = False
        f.c.on_owner_finish(2, host)
        self.assertEqual(sum(x[0] == "restore" for x in f.log), 1)
        self.assertIn(("life", -1), f.log)
        self.assertIn(("explicit_audio", "audio", 3), f.log)
        f.c.clear(is_owner_finished=True)

    def test_nested_cleanup_uid_change_skips_invalid_finished_snapshot(self):
        f = Fixture()
        b = buff(f.owner, "dead", 11, template="upeople_t", bb=[DataPair("value", -1)])
        f.add(b)
        f.c.mark_finish(b)
        f.log.clear()
        def pool(current, deferred):
            current.uid += 1
            f.c.on_owner_finish(2)
        f.on_recycle = pool
        f.c.check_finished()
        self.assertFalse(any(x[0] == "life" for x in f.log))
        self.assertEqual(f.c.buffs.depth, 0)

    def test_clear_requests_deferred_pool_once_before_live_clear(self):
        f = Fixture()
        b = buff(f.owner, "a", 11)
        f.add(b)
        observed = []
        f.on_recycle = lambda value, deferred: observed.append((deferred, len(f.c.buffs.live), len(f.c.uid_map)))
        f.c.clear(is_owner_finished=True)
        f.c.clear(is_owner_finished=True)
        self.assertEqual(observed, [(True, 1, 1)])
        self.assertTrue(f.c.state(b).marked_finished)
        self.assertTrue(f.c.state(b).actually_finished)

    def test_clear_second_pass_recycles_buff_added_during_finish_notification(self):
        f = Fixture()
        old = buff(f.owner, "old", 11)
        new = buff(f.owner, "new", 12)
        f.add(old)
        def notified(b, owner_finished):
            f.log.append(("notify", b.token))
            if b is old:
                f.add(new, active=False)
        f.hooks.owner_buff_finished = notified
        f.log.clear()
        f.c.clear(is_owner_finished=True)
        self.assertIn(("pool", "old", True), f.log)
        self.assertIn(("pool", "new", False), f.log)
        # The fallback pass does not call MarkFinish/OnFinish on the new Buff.
        self.assertFalse(f.c.state(new).marked_finished)
        self.assertFalse(f.c.state(new).actually_finished)
        self.assertEqual(f.c.buffs.live, [])

    def test_callback_failure_disposes_context_and_snapshot_without_fake_rollback(self):
        f = Fixture()
        host = entity("host", 99)
        f.new_container(host)
        b = buff(f.owner, "finish", 11, 2000, "enemy_shdopl_finish", source=host)
        f.add(b)
        def throwing(request):
            raise RuntimeError("external restore fixture failure")
        f.on_restore = throwing
        with self.assertRaises(RuntimeError):
            f.c.on_take_damage(Packet(EntityPtr.capture(host), EntityPtr.capture(f.owner)))
        self.assertEqual(f.c.buffs.depth, 0)
        self.assertEqual(f.actions.context.depth, 0)
        self.assertIsNone(f.c.current_modifier)
        self.assertEqual(len(f.c.buffs.live), 1)

    def test_duplicate_uid_fails_before_register(self):
        f = Fixture()
        a, b = buff(f.owner, "a", 11), buff(f.owner, "b", 11)
        f.add(a)
        with self.assertRaises(UnverifiedBuffContainer):
            f.add(b)
        self.assertEqual(f.c.uid_map, {11: a})

    def test_instant_lifetime_zero_finishes_after_start_and_rejects_creation(self):
        f = Fixture()
        b = buff(f.owner, "instant", 11)
        value = f.c.add_initialized(b, BuffInitShape("instant", FP(0), "fixture immediate"), owner_active=True)
        self.assertIsNone(value)
        self.assertTrue(f.c.state(b).started)
        self.assertTrue(f.c.state(b).actually_finished)

    def test_lifetime_zero_boundary_uses_strict_abs_less_and_min_saturates(self):
        for raw, expected in [(0, True), (42949, True), (-42949, True), (42950, False),
                              (-42950, False), (-(1 << 63), False), (MAX_VALUE_RAW, False)]:
            self.assertEqual(lifetime_is_zero(FP(raw)), expected)

    def test_override_backend_is_required_and_receives_mark_ignoring_false_flag(self):
        f = Fixture()
        b = buff(f.owner, "key", 11)
        f.add(b, override_key="actual.runtime.key")
        f.log.clear()
        f.c.finish_buffs_by_id("key", update_override_map=False)
        self.assertIn(("override", "mark", "key"), f.log)
        f.c.check_finished()
        self.assertIn(("override", "remove", "key"), f.log)
        f.c.clear()
        self.assertIn(("override", "clear", "key"), f.log)
        self.assertEqual(f.c.override_keys, {})

    def test_unknown_initialization_shapes_are_rejected(self):
        for kwargs in [dict(suppression_flags=("silenced",)), dict(filters_passed=False),
                       dict(derived_buff_count=1), dict(resistance_mask=1),
                       dict(abnormal_anti_mask=1), dict(durable=True),
                       dict(status_resistable=True), dict(can_slow_down=True), dict(trigger_count=1)]:
            with self.subTest(kwargs=kwargs), self.assertRaises(UnverifiedBuffContainer):
                BuffInitShape("key", FP.from_int32(-1), "fixture", **kwargs)

    def test_no_audio_provider_no_override_provider_fail_at_registration(self):
        f = Fixture()
        f.hooks.opaque_event = None
        with self.assertRaises(UnverifiedBuffContainer):
            f.add(buff(f.owner, "audio", 11, template="upeople_t_1"))
        f.hooks.override_transition = None
        with self.assertRaises(UnverifiedBuffContainer):
            f.add(buff(f.owner, "key", 12), override_key="key")
        self.assertEqual(f.c.uid_map, {})

    def test_finite_tick_is_strict_gate_before_start(self):
        f = Fixture()
        b = buff(f.owner, "a", 11)
        f.add(b, active=False, lifetime=FP.from_int32(2))
        with self.assertRaises(UnverifiedBuffContainer):
            f.c.tick(FP(100))
        self.assertFalse(f.c.state(b).started)

    def test_target_killed_empty_gate_and_packet_shape(self):
        f = Fixture()
        b = buff(f.owner, "a", 11)
        f.add(b)
        f.c.on_target_killed(entity("target", 98))
        self.assertIn(("target_killed_empty", "a", "target"), f.c.trace)
        with self.assertRaises(UnverifiedBuffContainer):
            f.c.on_take_damage(object())

    def test_reference_vectors(self):
        p = Path(__file__).resolve().parents[1] / "evidence/buff_container/reference_vectors.json"
        if not p.exists():
            self.skipTest("Reference generator pending")
        vectors = json.loads(p.read_text("utf8"))
        for vector in vectors["vectors"]:
            owner = entity()
            q = SortedDoubleBufferedBuffList()
            values = {}
            stack = []
            observed = []
            for operation in vector["operations"]:
                kind = operation[0]
                if kind == "add":
                    b = buff(owner, str(operation[1]), operation[1], operation[2])
                    values[operation[1]] = b
                    q.add(BuffPtr(b, b.uid))
                elif kind == "begin":
                    stack.append(q.get_enumerator(backwards=bool(operation[1])))
                elif kind == "next":
                    it = stack[-1]
                    observed.append(it.current.captured_uid if it.move_next() else -1)
                elif kind == "remove":
                    q.remove(values[operation[1]])
                elif kind == "clear":
                    q.clear()
                elif kind == "invalidate":
                    values[operation[1]].uid += 10000
                elif kind == "scan":
                    with q.iterate(backwards=bool(operation[1])) as it:
                        while it.move_next():
                            current = it.current.resolve()
                            observed.append(current.uid if current is not None else -3)
                    observed.append(-2)
                elif kind == "end":
                    stack.pop().dispose()
                elif kind == "live":
                    observed.extend(x.captured_uid for x in q.live)
                    observed.append(-2)
            self.assertEqual(observed, vector["expected"], vector["id"])


if __name__ == "__main__":
    unittest.main()

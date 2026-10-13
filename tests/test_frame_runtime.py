import unittest

from arknights_probe.coroutines import NEXT_FRAME
from arknights_probe.fp import FP
from arknights_probe.frame_runtime import (CoroutineOwner, NativeObjectRegistry,
    RegisteredObject, SelectedFrameLoop, SharedCoroutineSimulator,
    UnverifiedFrameContext)


class FrameRuntimeTests(unittest.TestCase):
    def simulator(self):
        return SharedCoroutineSimulator(source="explicit static component fixture", deterministic=True)

    def test_start_primes_and_completed_handle_is_allocated(self):
        sim = self.simulator()
        events = []
        def routine():
            events.append("prime")
            yield NEXT_FRAME
            events.append("finish")
        self.assertEqual(sim.start(CoroutineOwner(True, True), routine()), 1)
        self.assertEqual(events, ["prime"])
        sim.tick()
        self.assertEqual(events, ["prime", "finish"])
        self.assertEqual(sim.start(CoroutineOwner(True, True), iter(())), 2)
        self.assertFalse(sim.handlers)
        self.assertEqual(sim.start(CoroutineOwner(True, True), None), 0)

    def test_new_coroutine_during_simulation_misses_current_snapshot(self):
        sim = self.simulator()
        events = []
        owner = CoroutineOwner(True, True)
        def child():
            events.append("child prime")
            yield NEXT_FRAME
            events.append("child next")
        def parent():
            yield NEXT_FRAME
            sim.start(owner, child())
        sim.start(owner, parent())
        sim.tick()
        self.assertEqual(events, ["child prime"])
        sim.tick()
        self.assertEqual(events, ["child prime", "child next"])

    def test_nested_start_keeps_outer_allocated_handle_and_append_order(self):
        sim = self.simulator()
        owner = CoroutineOwner(True, True)
        def child():
            yield NEXT_FRAME
        def parent():
            self.assertEqual(sim.start(owner, child()), 2)
            yield NEXT_FRAME
        self.assertEqual(sim.start(owner, parent()), 1)
        self.assertEqual([h.handle for h in sim.handlers], [2, 1])

    def test_stop_inside_snapshot_prevents_later_execution_without_dispose(self):
        sim = self.simulator()
        events = []
        owner = CoroutineOwner(True, True)
        victim_handle = 0
        def killer():
            yield NEXT_FRAME
            self.assertTrue(sim.stop(victim_handle))
        def victim():
            yield NEXT_FRAME
            events.append("unexpected")
        sim.start(owner, killer())
        victim_handle = sim.start(owner, victim())
        sim.tick()
        self.assertEqual(events, [])
        self.assertFalse(sim.by_handle)
        self.assertFalse(sim.stop(victim_handle))

    def test_inactive_or_destroyed_owner_stops(self):
        for field in ["exists", "active_in_hierarchy"]:
            sim = self.simulator()
            owner = CoroutineOwner(True, True)
            def routine():
                yield NEXT_FRAME
                self.fail("Unavailable owner advanced")
            sim.start(owner, routine())
            setattr(owner, field, False)
            sim.tick()
            self.assertFalse(sim.handlers)

    def test_uid_sort_equal_insert_and_reference_remove(self):
        registry = NativeObjectRegistry()
        events = []
        def obj(uid, label):
            return RegisteredObject(uid, True, lambda _: events.append(label), lambda _: None)
        a, b, c = obj(5, "a"), obj(3, "b"), obj(5, "c")
        for x in [a, b, c]: registry.register(x)
        registry.fixed_tick(FP(1))
        self.assertEqual(events, ["b", "c", "a"])
        self.assertFalse(registry.unregister(obj(5, "other")))
        self.assertTrue(registry.unregister(a))

    def test_fixed_snapshot_is_not_rechecked_and_late_rebuilds(self):
        registry = NativeObjectRegistry()
        events = []
        b = RegisteredObject(2, True, lambda _: events.append("b fixed"), lambda _: events.append("b late"))
        c = RegisteredObject(3, True, lambda _: events.append("c fixed"), lambda _: events.append("c late"))
        def a_fixed(_):
            b.borned = False
            registry.unregister(b)
            registry.register(c)
        a = RegisteredObject(1, True, a_fixed, lambda _: events.append("a late"))
        registry.register(a); registry.register(b)
        registry.fixed_tick(FP(1)); registry.late_tick(FP(1))
        self.assertEqual(events, ["b fixed", "a late", "c late"])

    def test_started_in_fixed_advances_again_in_same_frame(self):
        sim, registry = self.simulator(), NativeObjectRegistry()
        events = []
        def routine():
            events.append("prime")
            yield NEXT_FRAME
            events.append("coroutine")
        obj = RegisteredObject(1, True,
            lambda _: sim.start(CoroutineOwner(True, True), routine()),
            lambda _: events.append("late"))
        registry.register(obj)
        frame = SelectedFrameLoop(dt=FP(1), registry=registry, simulator=sim,
            before_coroutines=(lambda _: events.append("before"),),
            after_coroutines=(lambda _: events.append("after"),), source="explicit component fixture")
        frame.tick()
        self.assertEqual(events, ["prime", "before", "coroutine", "after", "late"])

    def test_invalid_context_rejected(self):
        with self.assertRaises(UnverifiedFrameContext):
            SharedCoroutineSimulator(source="fixture", deterministic=False)
        with self.assertRaises(UnverifiedFrameContext):
            RegisteredObject(1 << 32, True, lambda _: None, lambda _: None).validate()

    def test_uids_above_signed_boundary_remain_unsigned(self):
        registry, events = NativeObjectRegistry(), []
        for uid in [0xFFFFFFFF, 1, 0x80000000]:
            registry.register(RegisteredObject(uid, True, lambda _, u=uid: events.append(u), lambda _: None))
        registry.fixed_tick(FP(1))
        self.assertEqual(events, [1, 0x80000000, 0xFFFFFFFF])

from dataclasses import replace
import unittest

from arknights_probe.fp import FP
from arknights_probe.frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from arknights_probe.npc_summon import (
    SummonHost, SummonedActor, SummonCallbacks, TrackedSummonRequest,
    TrackedSummonRuntime, UnverifiedSummonContext,
    NativeCheckpointData, NativeRouteData, duplicate_route_data,
)


class TrackedSummonTests(unittest.TestCase):
    def make(self, *, factory_exists=True, allow=True, stop=False, delay=0):
        self.frame = 0
        self.calls = []
        self.simulator = SharedCoroutineSimulator(source="explicit component fixture", deterministic=True)
        self.owner = CoroutineOwner(True, True)
        self.origin = {"captured": "route A"}
        self.host = SummonHost(23, True, self.origin, 6, 0, "prepared host getters")
        self.spawned = SummonedActor(24, True, object(), object(), "explicit initialized NPC factory result")

        def duplicate(origin):
            self.calls.append(("duplicate", origin))
            return dict(origin)

        def generate(count, route):
            self.calls.append(("generate", count, route))
            return (count, route)

        def factory(key, route, options):
            self.calls.append(("factory", key, route, options))
            return self.spawned if factory_exists else None

        callbacks = SummonCallbacks(
            duplicate, generate, factory,
            lambda actor, progress: self.calls.append(("progress", progress)),
            lambda actor, position: self.calls.append(("position", position)),
            lambda actor: self.calls.append(("face",)),
            lambda host, actor: self.calls.append(("buff", host.instance_uid, actor.host_uid)),
            lambda: self.calls.append(("before",)),
            lambda host, actor: self.calls.append(("mode_spawned",)),
            lambda: self.calls.append(("after",)), "explicit route/factory/mode callbacks")
        self.runtime = TrackedSummonRuntime(
            simulator=self.simulator, owner=self.owner, callbacks=callbacks,
            allow_summon=allow, spawned_count=10, delta_play_time_float=1 / 30,
            frame=lambda: self.frame, native_default_no_hotfix=True,
            source="d__129 selected branch fixture")
        self.request = TrackedSummonRequest(
            "enemy_3001_upeopl", self.host, (5.0, 2.0), FP.from_int32(delay),
            True, True, True, stop, True, True, False, "selected shipped summon flags")
        return self.runtime

    def tick(self, n=1):
        for _ in range(n):
            self.frame += 1
            self.simulator.tick()

    def test_zero_delay_is_one_shared_tick_and_final_only(self):
        rt = self.make()
        self.assertEqual(rt.start(self.request), 1)
        self.assertEqual(self.calls, [("before",)])
        self.assertEqual(rt.final, [])
        self.tick()
        self.assertEqual([c[0] for c in self.calls],
                         ["before", "duplicate", "generate", "factory", "progress", "position", "face", "buff", "mode_spawned", "after"])
        self.assertEqual(rt.final, [self.spawned])
        self.assertEqual(rt.wave, [])
        opts = self.calls[3][3]
        self.assertEqual((opts.unharmful, opts.always_count_as_killed,
                          opts.dont_count_as_finished, opts.is_summon, opts.spawned_count),
                         (True, False, True, True, 11))
        self.assertEqual(rt.events[-2]["frame"], 1)

    def test_origin_progress_and_uid_captured_but_host_death_does_not_stop_false_branch(self):
        rt = self.make()
        rt.start(self.request)
        self.host.origin_route = {"live": "route B"}
        self.host.origin_cursor_index = 99
        self.host.instance_uid = 0
        self.host.alive = False
        self.tick()
        self.assertIs(self.calls[1][1], self.origin)
        self.assertIn(("progress", 6), self.calls)
        self.assertEqual(self.spawned.host_uid, 23)
        # Source attachment sees the live source object; ObjectPtr validity is
        # separately checked by the action/buff runtime, not frozen to UID 23.
        self.assertIn(("buff", 0, 23), self.calls)

    def test_stop_true_uid_change_cancels_after_wait(self):
        rt = self.make(stop=True)
        rt.start(self.request)
        self.host.instance_uid = 25
        self.tick()
        self.assertEqual(self.calls, [("before",), ("after",)])
        self.assertEqual(rt.spawned_count, 10)
        self.assertEqual(rt.events[-2]["event"], "cancelled_host_gate")

    def test_allow_cancellation_runs_after_but_initial_rejection_does_not(self):
        rt = self.make()
        rt.start(self.request)
        rt.allow_summon = False
        self.tick()
        self.assertEqual(self.calls, [("before",), ("after",)])
        rt = self.make(allow=False)
        rt.start(self.request)
        self.assertEqual(self.calls, [])
        self.assertEqual(self.simulator.handlers, [])

    def test_factory_null_increments_counter_but_skips_mode_after_and_membership(self):
        rt = self.make(factory_exists=False)
        rt.start(self.request)
        self.tick()
        self.assertEqual(rt.spawned_count, 11)
        self.assertEqual([c[0] for c in self.calls], ["before", "duplicate", "generate", "factory"])
        self.assertEqual(rt.final, [])
        self.assertFalse(rt.events[-1]["mode_after_called"])

    def test_controller_owner_deactivation_stops_without_host_alive_or_finally_hook(self):
        rt = self.make()
        rt.start(self.request)
        self.owner.active_in_hierarchy = False
        self.tick()
        self.assertEqual(self.calls, [("before",)])
        self.assertEqual(self.simulator.handlers, [])

    def test_fp_positive_wait_and_chunking(self):
        def run(chunks):
            rt = self.make(delay=1)
            rt.start(self.request)
            for n in chunks:
                self.tick(n)
            return rt.events, [c[0] for c in self.calls]
        a = run([31])
        b = run([7, 12, 12])
        self.assertEqual(a, b)
        self.assertEqual(next(e["frame"] for e in a[0] if e["event"] == "spawned"), 30)

    def test_unverified_random_and_route_branches_are_rejected(self):
        rt = self.make()
        for changes in ({"ignore_offset": False}, {"check_motion_mode_all": False}, {"skip_checkpoints": True}):
            with self.assertRaises(UnverifiedSummonContext):
                rt.start(replace(self.request, **changes))
        self.assertEqual(self.calls, [])

    def test_duplicate_route_preserves_fields_and_detaches_checkpoint_objects(self):
        cp = NativeCheckpointData(1, 99.0, (2, 3), (0.25, -0.5), True, 0.125)
        route = NativeRouteData(0, (0, 1), (6, 7), (0.5, 0.25), (-0.0, 0.0),
                                [cp], False, True, False, True, "source declaration")
        copied = duplicate_route_data(route)
        self.assertEqual(copied, route)
        self.assertIsNot(copied, route)
        self.assertIsNot(copied.checkpoints, route.checkpoints)
        self.assertIsNot(copied.checkpoints[0], cp)
        copied.checkpoints[0].time = 1.0
        self.assertEqual(cp.time, 99.0)
        copied.visit_every_tile_center = False
        self.assertTrue(route.visit_every_tile_center)

    def test_duplicate_null_and_empty_checkpoint_arrays_stay_distinct(self):
        route = NativeRouteData(1, (0, 0), (0, 0), (0.0, 0.0), (0.0, 0.0),
                                None, True, False, True, False, "source declaration")
        self.assertIsNone(duplicate_route_data(route).checkpoints)
        route.checkpoints = []
        copied = duplicate_route_data(route)
        self.assertEqual(copied.checkpoints, [])
        self.assertIsNot(copied.checkpoints, route.checkpoints)

    def test_duplicate_missing_checkpoint_and_unrounded_position_reject(self):
        route = NativeRouteData(0, (0, 0), (0, 0), (0.0, 0.0), (0.0, 0.0),
                                [None], True, False, False, False, "source declaration")
        with self.assertRaises(UnverifiedSummonContext):
            duplicate_route_data(route)
        rt = self.make()
        with self.assertRaises(UnverifiedSummonContext):
            rt.start(replace(self.request, position=(0.1, 0.0)))


if __name__ == "__main__":
    unittest.main()

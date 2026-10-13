import unittest
from dataclasses import replace
import json
from pathlib import Path

from arknights_probe.fp import FP, binary32
from arknights_probe.frame_runtime import SharedCoroutineSimulator
from arknights_probe.npc_restore import (NpcRestoreActor, NpcRestoreContext,
    NpcRestoreRuntime, RestoreCallbacks, RestoreCursor, RestoreRoute, TweenTicket,
    UnverifiedRestoreContext, color_segment)


DT = FP(143165440)


def route(token="route", count=0, tile=False, node=False):
    return RestoreRoute(token, count, tile, node, "explicit prepared native route fixture")


def actor(token="host", uid=1, **changes):
    values = dict(token=token, uid=uid, unity_exists=True, is_enemy=True,
                  is_giant_boss=False, grid_position=(4, 3), is_disappeared=False,
                  game_active=True, state_id=1, cursor=RestoreCursor(route(), 0),
                  body_color=(.25, .5, .75, .8), render_color=(.5, .6, .7, .9))
    values.update(changes)
    return NpcRestoreActor(**values)


class Fixture:
    """Explicit synchronous providers; does not emulate DOTween stepping."""
    def __init__(self, dt=DT):
        self.frame, self.raw, self.calls, self.requests = 0, 0, [], []
        self.dt = dt
        self.sim = SharedCoroutineSimulator(source="controlled test fixture", deterministic=True)
        self.callbacks = RestoreCallbacks(
            set_active=lambda a, v: self.calls.append(("active", a.token, v)),
            set_grid_position=lambda a, v: self.calls.append(("grid", a.token, v)),
            apply_state_modifier=lambda a, v: self.calls.append(("modifier", a.token, v)),
            tween_start=self.start_tween, tween_kill=self.kill_tween,
            face_from_cursor=lambda a: self.calls.append(("face", a.token)),
            move_tick=lambda a, dt: self.calls.append(("move", a.token, dt.raw)),
            before_disappear=lambda a, v: self.calls.append(("before", a.token, v)),
            disappear_changed=lambda a, v: self.calls.append(("changed", a.token, v)),
            set_color=lambda a, v: self.calls.append(("color", a.token, v)),
            state_transition=lambda a, old, new: True)
        self.context = NpcRestoreContext("controlled test; no Unity oracle", True, True,
                                        dt.as_float(), True, True)
        self.runtime = NpcRestoreRuntime(self.context, self.sim,
                                       lambda: (self.frame, self.raw), self.callbacks)

    def start_tween(self, a, request):
        self.requests.append(request)
        return TweenTicket("ticket" + str(len(self.requests)), "explicit callback fixture")

    def kill_tween(self, a, ticket, complete):
        self.calls.append(("kill", a.token, ticket.token, complete))
        # External fixture explicitly implements completion setter dispatch.
        request = self.requests[int(ticket.token[6:]) - 1]
        if complete:
            for name, target, duration in request.segments:
                request.setter(name, target)

    def tick(self, a):
        self.frame += 1
        self.raw += self.dt.raw
        moved = self.runtime.tick(a, self.dt)
        self.sim.tick()
        return moved


class NpcRestoreTests(unittest.TestCase):
    def test_hidden_state_primes_modifier_then_tween_then_event(self):
        f, a = Fixture(), actor()
        self.assertTrue(f.runtime.set_disappeared(a, True))
        self.assertEqual(a.state_id, 11)
        self.assertTrue(a.is_disappeared and a.state_modifier_applied)
        self.assertEqual([x[0] for x in f.calls], ["before", "modifier", "changed"])
        self.assertEqual(len(f.requests), 1)
        self.assertNotEqual(a.coroutine_handle, 0)
        self.assertEqual([x[0] for x in f.requests[0].segments], ["rgb", "alpha"])
        self.assertEqual([x[2] for x in f.requests[0].segments], [binary32(.15)] * 2)
        self.assertEqual(f.requests[0].base_color, tuple(map(binary32, (.5, .6, .7, .9))))

    def test_float_wait_hides_at_frame_nine_after_immediate_prime(self):
        f, a = Fixture(), actor()
        f.runtime.set_disappeared(a, True)
        for _ in range(8):
            self.assertFalse(f.tick(a))
            self.assertTrue(a.game_active)
        self.assertFalse(f.tick(a))
        self.assertFalse(a.game_active)
        self.assertEqual(a.render_color, (0., 0., 0., 0.))
        self.assertTrue(a.is_disappeared)
        self.assertEqual(len(f.sim.handlers), 0)
        self.assertNotEqual(a.coroutine_handle, 0)  # Id valid until OnExit invalidation.

    def test_clear_flag_does_not_exit_until_state_tick(self):
        f, a = Fixture(), actor()
        f.runtime.set_disappeared(a, True)
        f.runtime.set_disappeared(a, False)
        self.assertEqual(a.state_id, 11)
        self.assertEqual(len(f.requests), 1)
        self.assertFalse(f.tick(a))
        self.assertEqual(a.state_id, 1)
        self.assertEqual(a.coroutine_handle, 0)
        self.assertTrue(a.game_active)
        self.assertEqual(len(f.requests), 2)
        self.assertFalse(any(x[0] == "move" for x in f.calls))
        self.assertTrue(f.tick(a))
        self.assertEqual(sum(x[0] == "move" for x in f.calls), 1)

    def test_early_appear_does_not_wait_or_kill_old_tween_in_normal_branch(self):
        f, a = Fixture(), actor()
        f.runtime.set_disappeared(a, True)
        f.runtime.set_disappeared(a, False)
        f.tick(a)
        self.assertFalse(any(x[0] == "kill" for x in f.calls))
        self.assertEqual(a.render_color, (0., 0., 0., 1.))
        self.assertEqual([x[0] for x in f.requests[-1].segments], ["alpha", "rgb"])
        self.assertEqual(f.requests[-1].base_color, tuple(map(binary32, a.body_color)))
        for _ in range(12):
            f.tick(a)
        self.assertTrue(a.game_active)  # Stopped hide coroutine must not deactivate later.

    def test_disable_appear_tween_one_shot_kills_complete_restores_body_color(self):
        f, a = Fixture(), actor(disable_appear_tween_color=True)
        f.runtime.set_disappeared(a, True)
        f.runtime.set_disappeared(a, False)
        f.tick(a)
        self.assertEqual(len(f.requests), 1)
        self.assertFalse(a.disable_appear_tween_color)
        self.assertEqual(a.render_color, tuple(map(binary32, a.body_color[:3])) + (1.,))
        self.assertEqual(sum(x[0] == "kill" for x in f.calls), 1)

    def test_uid_zero_or_unchanged_value_is_noop_action_success(self):
        for a in (actor(uid=0), actor(is_disappeared=True, state_id=11)):
            f = Fixture()
            self.assertTrue(f.runtime.set_disappeared(a, True))
            self.assertEqual(f.calls, [])
            self.assertEqual(f.requests, [])

    def test_nonexistent_target_returns_false(self):
        f, a = Fixture(), actor(unity_exists=False)
        self.assertFalse(f.runtime.set_disappeared(a, True))

    def test_unsupported_state_admission_rejected(self):
        f = Fixture()
        with self.assertRaises(UnverifiedRestoreContext):
            f.runtime.set_disappeared(actor(state_id=6), True)
        with self.assertRaises(UnverifiedRestoreContext):
            f.runtime.tick(actor(state_id=5), DT)

    def test_color_callbacks_do_binary32_products_with_no_progress_clamp(self):
        base = (.123456789, .9, -.4, .7)
        expected = tuple(binary32(binary32(x) * binary32(1.3)) for x in base[:3])
        self.assertEqual(color_segment(base, 1.3, "rgb"), expected + (binary32(.7),))
        self.assertEqual(color_segment(base, -.5, "alpha"), (0., 0., 0., binary32(binary32(.7) * -.5)))

    def test_float_wait_ties_even_not_ceil(self):
        # This explicit Single produces 2.5f -> two yields, not three.
        f, a = Fixture(FP.from_float32(.12000000476837158)), actor()
        f.runtime.set_disappeared(a, True)
        f.tick(a)
        self.assertTrue(a.game_active)
        f.tick(a)
        self.assertFalse(a.game_active)

    def test_restore_uses_current_grid_and_source_route_identity_then_progress(self):
        f, target = Fixture(), actor(pull_sources=(("pullA", 2), ("pullB", 0)),
                                     disabled_pull_sources=(("old", 1),))
        r = route("source-route")
        source = actor("npc", 2, grid_position=(7, -4), cursor=RestoreCursor(r, 17))
        self.assertTrue(f.runtime.restore_to(target, source))
        self.assertEqual(target.grid_position, (7, -4))
        self.assertIs(target.cursor.route, r)
        self.assertEqual(target.cursor.cursor_index, 17)
        self.assertEqual(target.cursor.cached_direction, (0., 0.))
        self.assertEqual(target.disabled_pull_sources, target.pull_sources)
        target.pull_sources += (("future", 3),)
        self.assertEqual(len(target.disabled_pull_sources), 2)
        self.assertEqual([x["kind"] for x in f.runtime.events],
                         ["restore_position", "disable_current_still_pull", "route_reassigned"])

    def test_route_flags_are_sticky_or_and_stably_depends_on_checkpoint_count(self):
        f, a = Fixture(), actor()
        a.cursor.visit_every_tile_center = True
        a.cursor.visited_map = ((True, False), (False, True))
        f.runtime.reassign_route(a, route(node=True), -8)
        self.assertTrue(a.cursor.visit_every_tile_center and a.cursor.visit_every_node_center)
        self.assertTrue(a.cursor.visit_every_node_stably)
        self.assertEqual(a.cursor.visited_map, ((False, False), (False, False)))
        self.assertEqual(a.cursor.cursor_index, -8)  # no native clamping
        f.runtime.reassign_route(a, route(), 0)
        self.assertTrue(a.cursor.visit_every_node_center)

    def test_uninitialized_map_or_nonempty_checkpoint_route_requires_provider(self):
        f, a = Fixture(), actor()
        with self.assertRaises(UnverifiedRestoreContext):
            f.runtime.reassign_route(a, route(tile=True), 0)
        with self.assertRaises(UnverifiedRestoreContext):
            f.runtime.reassign_route(a, route(count=2), 0)

    def test_nonempty_route_uses_explicit_fresh_checkpoint_reset_then_assigns_progress(self):
        f, a = Fixture(), actor()
        def reset(target, r):
            target.cursor.checkpoint_objects = ("newCP0", "newCP1")
            target.cursor.cached_direction = (0., 0.)
            target.cursor.cursor_index = 0  # provider runs Reset/OnBegin(0)
        f.runtime.callbacks = replace(f.callbacks, rebuild_and_reset_cursor=reset)
        f.runtime.reassign_route(a, route(count=2), 1)
        self.assertEqual(a.cursor.checkpoint_objects, ("newCP0", "newCP1"))
        self.assertEqual(a.cursor.cursor_index, 1)
        self.assertFalse(a.cursor.visit_every_node_stably)

    def test_release_provider_can_destroy_target_native_recheck_returns_false(self):
        f, a = Fixture(), actor(blocker_valid=True)
        f.runtime.callbacks = replace(f.callbacks, release_blocker=lambda x: setattr(x, "unity_exists", False))
        self.assertFalse(f.runtime.restore_to(a, actor("npc", 2)))
        self.assertFalse(any(x[0] == "grid" for x in f.calls))

    def test_valid_blocker_or_block_tween_requires_provider(self):
        f = Fixture()
        for a in (actor(blocker_valid=True), actor(block_tween=TweenTicket("b", "fixture"))):
            with self.assertRaises(UnverifiedRestoreContext):
                f.runtime.restore_to(a, actor("npc", 2))
            self.assertEqual(a.grid_position, (4, 3))

    def test_giant_or_non_enemy_target_returns_false_source_non_enemy_skips_route(self):
        f = Fixture()
        self.assertFalse(f.runtime.restore_to(actor(is_giant_boss=True), actor("npc", 2)))
        self.assertFalse(f.runtime.restore_to(actor(is_enemy=False), actor("npc", 2)))
        a = actor()
        self.assertTrue(f.runtime.restore_to(a, actor("source", 0, is_enemy=False, cursor=None)))
        self.assertEqual(a.cursor.route.token, "route")

    def test_context_and_external_color_are_required(self):
        for values in ((False, True, True), (True, False, True), (True, True, False)):
            with self.assertRaises(UnverifiedRestoreContext):
                NpcRestoreContext("fixture", values[0], values[1], .03, values[2], True)
        a = actor(render_color=None)
        with self.assertRaises(UnverifiedRestoreContext):
            Fixture().runtime.set_disappeared(a, True)

    def test_inactive_parent_and_denied_fsm_adapter_are_rejected(self):
        with self.assertRaises(UnverifiedRestoreContext):
            NpcRestoreContext("fixture", True, True, DT.as_float(), True, False)
        f, a = Fixture(), actor()
        f.runtime.callbacks = replace(f.callbacks, state_transition=lambda a, old, new: False)
        with self.assertRaises(UnverifiedRestoreContext):
            f.runtime.set_disappeared(a, True)

    def test_tween_provider_cannot_silently_return_unknown_ticket(self):
        f = Fixture()
        f.runtime.callbacks = replace(f.callbacks, tween_start=lambda a, r: None)
        with self.assertRaises(UnverifiedRestoreContext):
            f.runtime.set_disappeared(actor(), True)

    def test_48_csharp_reference_vectors_recomputed_with_current_module(self):
        path = Path(__file__).resolve().parents[1] / "evidence/npc_restore/reference_results.json"
        reference = json.loads(path.read_text())
        self.assertEqual(reference["vector_count"], 48)
        self.assertIn("NOT client oracle", reference["kind"])
        for row in reference["vectors"]:
            v = row["input"]
            f, a = Fixture(FP.from_float32(v["delta_float"])), actor()
            f.runtime.set_disappeared(a, True)
            if v["clear_frame"] == 0:
                f.runtime.set_disappeared(a, False)
            for n in range(1, 25):
                if n == v["clear_frame"]:
                    f.runtime.set_disappeared(a, False)
                f.tick(a)
            def first(kind, predicate=lambda e: True):
                return next((e["frame"] for e in f.runtime.events
                             if e["kind"] == kind and predicate(e)), -1)
            actual = (first("set_active", lambda e: e["value"] is False),
                      first("switch_default_requested"), first("move_tick"), int(a.game_active))
            self.assertEqual(actual, tuple(map(int, row["csharp"].split(",")[:4])))


if __name__ == "__main__":
    unittest.main()

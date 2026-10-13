import unittest

from arknights_probe.fp import FP, binary32
from arknights_probe.movement import (LocalVector2 as V, NativeTileSnapshot as T,
    NativeWalkPathGrid, WalkRouteSpec, CheckpointSpec, compile_walk_route)
from arknights_probe.runtime_movement import (PeriodicTicker, NativeDirectionCursor,
    MovementContext, NativeMoveController, NativeRouteMover, obstacle_avoid_force, deterministic_position,
    TileOptions, initialize_cached_tile, rewrite_cached_tile, build_cached_walk_grid)


def open_grid(height=5, width=5):
    return NativeWalkPathGrid([[T(1, 15, False, False) for _ in range(width)] for _ in range(height)],
                              source="explicit unit cached-state fixture")


class RuntimeMovementTests(unittest.TestCase):
    def test_periodic_ready_is_call_count_and_next_rearms(self):
        ticker = PeriodicTicker(3)
        self.assertTrue(ticker.tick())
        self.assertTrue(ticker.next())
        self.assertFalse(ticker.next())
        self.assertEqual([ticker.tick() for _ in range(3)], [False, False, True])

    def test_position_rounding_stages_and_disabled_identity(self):
        position = V(1.23456, -1.23456)
        self.assertIs(deterministic_position(position, False), position)
        self.assertEqual(deterministic_position(position, True), V(1.2346, -1.2346))
        self.assertEqual(deterministic_position(V(.00005, -.00005), True), V(0, 0))
        with self.assertRaises(ValueError):
            deterministic_position(V(1e12, 0), True)

    def test_obstacle_avoidance_symmetry_and_grid_delta_fallback(self):
        rows = [[T(1, 15, False, False) for _ in range(3)] for _ in range(3)]
        rows[1][2] = T(0, 15, False, False)
        right = NativeWalkPathGrid(rows, source="right obstacle")
        self.assertEqual(obstacle_avoid_force(right, V(1.4, 1), V(1.4, 1), half_body_width=.2), V(-1, 0))
        rows[1][2], rows[1][0] = rows[1][0], rows[1][2]
        left = NativeWalkPathGrid(rows, source="left obstacle")
        self.assertEqual(obstacle_avoid_force(left, V(.6, 1), V(.6, 1), half_body_width=.2), V(1, 0))
        blocked = NativeWalkPathGrid([[T(0, 15, False, False), T(0, 15, False, False)],
                                      [T(0, 15, False, False), T(1, 15, False, False)]], source="diagonal rescue")
        self.assertEqual(obstacle_avoid_force(blocked, V(0, 0), V(0, 0), half_body_width=.2), V(1, 1))

    def test_obstacle_avoidance_ignores_outside_neighbors(self):
        self.assertEqual(obstacle_avoid_force(open_grid(), V(0, 0), V(0, 0), half_body_width=.2), V(0, 0))
        self.assertEqual(obstacle_avoid_force(open_grid(), V(-10, -10), V(0, 0), half_body_width=.2), V(0, 0))

    def test_controller_accelerates_and_can_move_gate_keeps_state(self):
        context = MovementContext("explicit flags", False, True, V(0, 0), 2.5, 4, .2, False, False)
        controller = NativeMoveController(open_grid(), context)
        delta, still = controller.calculate_delta(V(1, 0), .1, speed=1, position=V(2, 2),
                                                  offset_position=V(2, 2), can_move=True)
        self.assertEqual(controller.velocity, V(.25, 0))
        self.assertEqual(delta, V(binary32(.25 * binary32(.1)), 0))
        self.assertFalse(still)
        before = controller.velocity, controller.ticker.remaining
        self.assertEqual(controller.calculate_delta(V(1, 0), .1, speed=1, position=V(2, 2),
                            offset_position=V(2, 2), can_move=False), (V(0, 0), True))
        self.assertEqual(before, (controller.velocity, controller.ticker.remaining))

    def test_controller_flags_choose_distinct_native_force(self):
        values = []
        for flag in (False, True):
            controller = NativeMoveController(open_grid(), MovementContext("scenario", False, flag, V(0, 0), 2.5, 4, .2, False, False))
            values.append(controller.calculate_delta(V(1, 0), .1, speed=1, position=V(2, 2),
                            offset_position=V(2, 2), can_move=True)[0])
        self.assertEqual(values, [V(.1, 0), V(.025, 0)])

    def test_cursor_wait_countdown_and_tick_advances_once(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0),
            (CheckpointSpec("WAIT_FOR_SECONDS", .2, (0, 0), V(0, 0), 0),
             CheckpointSpec("WAIT_FOR_SECONDS", 0, (0, 0), V(0, 0), 0)))
        cursor = NativeDirectionCursor(compile_walk_route(spec, grid), grid, offset=V(0, 0), initial_position=V(1, 1), always_check_current_point=False)
        cursor.tick(FP.from_float32(.1), V(1, 1), check_reached=False)
        self.assertEqual(cursor.checkpoint_index, 0)
        self.assertEqual(cursor.direction(V(1, 1)), V(0, 0))
        cursor.tick(FP.from_float32(.1), V(1, 1), check_reached=True)
        self.assertEqual(cursor.checkpoint_index, 1)
        cursor.direction(V(1, 1))
        self.assertEqual(cursor.checkpoint_index, 2)  # direction loops over reached CPs

    def test_cursor_prediction_skips_wait_without_advancing(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(.2, -.2),
            (CheckpointSpec("WAIT_FOR_SECONDS", 99, (0, 0), V(0, 0), 0),
             CheckpointSpec("MOVE", 0, (2, 3), V(.1, 0), .1)))
        cursor = NativeDirectionCursor(compile_walk_route(spec, grid), grid, offset=V(-.2, .2), initial_position=V(1.2, .8), always_check_current_point=False)
        predicted, direction, target = cursor.predict_reached(V(1.2, .8), 5)
        self.assertTrue(predicted)
        self.assertEqual(target, V(binary32(binary32(3.1) - binary32(-.2)), binary32(2 - binary32(.2))))
        self.assertEqual(cursor.checkpoint_index, 0)
        self.assertGreater(direction.x, 0)

    def test_exit_radius_checks_locator_and_does_not_prove_life_loss(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(.2, -.2), ())
        cursor = NativeDirectionCursor(compile_walk_route(spec, grid), grid, offset=V(-.2, .2), initial_position=V(1.2, .8), always_check_current_point=False)
        self.assertTrue(cursor.reached_exit(V(4.2, .8)))
        self.assertFalse(cursor.reached_exit(V(4.3, .8)))

    def test_unknown_conveyor_context_fails_closed(self):
        with self.assertRaisesRegex(ValueError, "Conveyor"):
            MovementContext("unknown conveyor fixture", False, True, V(0, 0), 2.5, 4, .2, True, False)

    def test_native_acceleration_reaches_exit_without_terminal_fixture(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0), ())
        mover = NativeRouteMover(compile_walk_route(spec, grid), grid,
            MovementContext("explicit native prefab parameters", True, True, V(0, 0), 8, 10, .2, False, False),
            position=V(1, 1), cursor_offset=V(0, 0))
        for _ in range(100):
            mover.move_by_cursor(.03333330154418945, speed=1, can_move=True, actually_ground_bound=False)
            if mover.cursor.reached_exit(mover.position):
                break
        self.assertTrue(mover.cursor.reached_exit(mover.position))
        self.assertLessEqual(abs(4 - mover.position.x), .05)
        self.assertFalse(mover.snapshot()["battle_ready"])

    def test_prediction_snap_preserves_controller_velocity(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0), ())
        mover = NativeRouteMover(compile_walk_route(spec, grid), grid,
            MovementContext("fixture", False, True, V(0, 0), 8, 10, .2, False, False),
            position=V(3.99, 1), cursor_offset=V(0, 0))
        mover.controller.velocity = V(.4, .1)
        mover.move_by_cursor(.1, speed=1, can_move=True, actually_ground_bound=False)
        self.assertEqual(mover.controller.velocity, V(.4, .1))
        self.assertEqual(mover.position, V(4, 1))

    def test_ground_bound_early_return_does_not_assign_position(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0), ())
        mover = NativeRouteMover(compile_walk_route(spec, grid), grid,
            MovementContext("fixture", True, True, V(0, 0), 8, 10, .2, False, False),
            position=V(1.23456, 1), cursor_offset=V(0, 0))
        before = mover.position
        mover.move_by_cursor(.1, speed=1, can_move=True, actually_ground_bound=True)
        self.assertEqual(mover.position, before)
        self.assertEqual(mover.last_update["kind"], "ground_bound")

    def test_tick_wait_advances_after_move_and_born_tick_does_not_move(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0),
            (CheckpointSpec("WAIT_FOR_SECONDS", .2, (0, 0), V(0, 0), 0),))
        mover = NativeRouteMover(compile_walk_route(spec, grid), grid,
            MovementContext("scoped FSM input", False, True, V(0, 0), 8, 10, .2, False, False),
            position=V(1, 1), cursor_offset=V(0, 0))
        flags = dict(speed=1, alive_after_unit_tick=True, can_move=True,
                     actually_ground_bound=False, check_cursor_reached=True, exit_allowed=True)
        first = mover.tick(FP.from_float32(.1), move_state_tick=False, **flags)
        self.assertEqual(first["position"], [1, 1])
        self.assertEqual(first["cursor"]["wait_remaining_raw"], FP.from_float32(.1).raw)
        second = mover.tick(FP.from_float32(.1), move_state_tick=True, **flags)
        self.assertEqual(second["position"], [1, 1])
        self.assertEqual(second["cursor"]["checkpoint_index"], 1)
        third = mover.tick(FP.from_float32(.1), move_state_tick=True, **flags)
        self.assertGreater(third["position"][0], 1)
        self.assertEqual(third["current_frame"], 3)

    def test_exit_gate_is_external_and_exit_request_cannot_repeat(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0), ())
        mover = NativeRouteMover(compile_walk_route(spec, grid), grid,
            MovementContext("exit gate fixture", False, True, V(0, 0), 8, 10, .2, False, False),
            position=V(4, 1), cursor_offset=V(0, 0))
        flags = dict(speed=1, move_state_tick=False, alive_after_unit_tick=True, can_move=True,
                     actually_ground_bound=False, check_cursor_reached=True)
        self.assertFalse(mover.tick(FP.from_float32(.1), exit_allowed=False, **flags)["exit_requested"])
        self.assertTrue(mover.tick(FP.from_float32(.1), exit_allowed=True, **flags)["exit_requested"])
        with self.assertRaisesRegex(ValueError, "lifecycle owner"):
            mover.tick(FP.from_float32(.1), exit_allowed=True, **flags)

    def test_tile_init_and_altar_rewrite_preserve_height(self):
        tile = initialize_cached_tile(native_type="Torappu.Battle.Tile", buildable_type=3,
            passable_mask=3, advanced_build_mask=1, height_type=1, walk_goto_mask=15,
            source="processed TileData with native ctor advanced default")
        self.assertFalse(tile.cached.override_obstacle_move_cost)
        self.assertTrue(tile.cached.force_set_height_type)
        options = TileOptions(0, 2, False, 0, 0, False)
        altar, dirty, accepted = rewrite_cached_tile(tile, options, keep_passable_mask=False,
            keep_buildable_type=False, ignore_block_any_routes=False, batching=False,
            routes_reachable=True, source="explicit pinned altar mode")
        self.assertTrue(accepted)
        self.assertEqual(dirty, 1)
        self.assertEqual(altar.cached.height_type, 1)
        self.assertFalse(altar.snapshot().walk_passable)
        self.assertEqual(altar.origin, tile.origin)

    def test_tile_unknown_global_reachability_gate_and_origin_rollback(self):
        tile = initialize_cached_tile(native_type="Torappu.Battle.Tile", buildable_type=3,
            passable_mask=3, advanced_build_mask=1, height_type=0, walk_goto_mask=15, source="fixture")
        kwargs = dict(keep_passable_mask=False, keep_buildable_type=False, ignore_block_any_routes=False,
                      batching=False, source="fixture rewrite")
        with self.assertRaisesRegex(ValueError, "all-routes-reachable"):
            rewrite_cached_tile(tile, TileOptions(0, 2, False, 1, 0, False), routes_reachable=None, **kwargs)
        changed, _, _ = rewrite_cached_tile(tile, TileOptions(0, 3, True, 1, 0, False), routes_reachable=True, **kwargs)
        rolled_back, _, accepted = rewrite_cached_tile(changed, TileOptions(0, 2, True, 1, 0, False), routes_reachable=False, **kwargs)
        self.assertFalse(accepted)
        self.assertEqual(rolled_back.cached, tile.origin)
        self.assertNotEqual(rolled_back.cached, changed.cached)

    def test_hole_native_million_cost_does_not_use_override_flag(self):
        tiles = []
        for native_type in ["Torappu.Battle.Tile", "Torappu.Battle.HoleTile"]:
            tiles.append(initialize_cached_tile(native_type=native_type, buildable_type=0,
                passable_mask=1, advanced_build_mask=1, height_type=0, walk_goto_mask=15, source="actual native class fixture"))
        grid = build_cached_walk_grid([tiles], source="initialized cached tiles")
        self.assertEqual([tile.move_cost for tile in grid.tiles[0]], [1, 1000000])
        self.assertEqual([tile.is_obstacle_like for tile in grid.tiles[0]], [False, True])
        self.assertFalse(grid.tiles[0][1].override_obstacle_move_cost)

    def test_born_fsm_tick_also_reassigns_deterministic_local_position(self):
        grid = open_grid()
        spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0), ())
        mover = NativeRouteMover(compile_walk_route(spec, grid), grid,
            MovementContext("scoped Born FSM input", True, True, V(0, 0), 8, 10, .2, False, False),
            position=V(1.23456, 1), cursor_offset=V(0, 0))
        snapshot = mover.tick(FP.from_float32(.1), speed=1, move_state_tick=False, alive_after_unit_tick=True,
            can_move=True, actually_ground_bound=False, check_cursor_reached=True, exit_allowed=True)
        self.assertEqual(mover.position, V(1.2346, 1))
        self.assertTrue(snapshot["last_update"]["fsm_position_reassigned"])

    def test_zero_checkpoint_stable_cursor_predicts_native_intermediate_node(self):
        rows = [[T(0 if c == 2 and r < 4 else 1, 15, False, False) for c in range(5)] for r in range(5)]
        grid = NativeWalkPathGrid(rows, source="asymmetric cached-state path fixture")
        spec = WalkRouteSpec((1, 0), (1, 4), V(0, 0), ())
        compiled = compile_walk_route(spec, grid)
        cursor = NativeDirectionCursor(compiled, grid, offset=V(0, 0),
            initial_position=V(0, 1), always_check_current_point=False)
        self.assertTrue(cursor.visit_every_node_stably)
        self.assertEqual(compiled.final_map[1][0].next_grid, (4, 1))
        # First lookup at constructor's nextGrid advances the cached nextGrid
        # but falls through to final target; later lookup returns the node.
        self.assertEqual(cursor.next_target(V(0, 1)), V(4, 1))
        self.assertEqual(cursor.next_target(V(0, 1)), V(1, 4))
        self.assertEqual(cursor.direction(V(0, 1)), V(1, 3).normalized())

    def test_prefab_always_check_flag_changes_unreachable_move_skip(self):
        rows = [[T(1, 15, False, False) for _ in range(3)] for _ in range(3)]
        rows[0][0] = T(0, 15, False, False)
        grid = NativeWalkPathGrid(rows, source="invalid current path-node fixture")
        spec = WalkRouteSpec((0, 0), (2, 2), V(0, 0),
            (CheckpointSpec("MOVE", 0, (1, 1), V(0, 0), 0),))
        compiled = compile_walk_route(spec, grid)
        indices = []
        for flag in (False, True):
            cursor = NativeDirectionCursor(compiled, grid, offset=V(0, 0),
                initial_position=V(0, 0), always_check_current_point=flag)
            self.assertFalse(cursor.visit_every_node_stably)
            cursor.direction(V(0, 0))
            indices.append(cursor.checkpoint_index)
        self.assertEqual(indices, [1, 0])


if __name__ == "__main__":
    unittest.main()

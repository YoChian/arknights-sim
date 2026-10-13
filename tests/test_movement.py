import unittest
import copy
from pathlib import Path

from arknights_probe.fp import FP
from arknights_probe.movement import (LocalVector2, WaitCheckpoint, WalkRouteSpec,
    NativeTileSnapshot, NativeWalkPathGrid, compile_walk_route,
    check_distance, clamp_magnitude, grid_to_local, local_to_grid,
    normalize_direction_safely, vector_is_zero)
from arknights_probe.coroutines import float_wait_frames
from arknights_probe.timeline import ASSET_DEFAULT_DT_RAW
from arknights_probe.data import DataError, Dataset


class WaitCheckpointTests(unittest.TestCase):
    def test_countdown_clamps_and_begin_resets(self):
        wait = WaitCheckpoint(.25)
        self.assertFalse(wait.is_reached)
        wait.tick(FP.from_float32(.125))
        self.assertEqual(wait.remaining.raw, 1 << 29)
        wait.tick(FP.from_float32(.5))
        self.assertEqual(wait.remaining.raw, 0)
        self.assertTrue(wait.is_reached)
        wait.begin()
        self.assertEqual(wait.remaining.raw, 1 << 30)

    def test_zero_checkpoint_is_immediately_reached(self):
        self.assertTrue(WaitCheckpoint(0).is_reached)
        wait = WaitCheckpoint(1)
        wait.tick(FP.from_raw(0))
        self.assertEqual(wait.remaining, FP.from_int32(1))

    def test_real_waits_use_fp_countdown_not_scheduler_rounding(self):
        dt = FP.from_raw(ASSET_DEFAULT_DT_RAW)
        for seconds in [99, 60, 120, 78, 45, 35, 5, 8, 10]:
            wait = WaitCheckpoint(seconds)
            expected_ticks = (wait.initial.raw + dt.raw - 1) // dt.raw
            for _ in range(expected_ticks - 1):
                wait.tick(dt)
            self.assertFalse(wait.is_reached, seconds)
            wait.tick(dt)
            self.assertTrue(wait.is_reached, seconds)
            self.assertEqual(expected_ticks, float_wait_frames(seconds, dt.as_float()) + 1)

    def test_input_bits_are_binary32_before_fp(self):
        self.assertEqual(WaitCheckpoint(.1).initial.raw, 429496736)
        self.assertNotEqual(WaitCheckpoint(.1).initial.raw, FP.from_double(.1).raw)

    def test_invalid_wait_input_is_rejected_before_fp_conversion(self):
        for value in [-1e-100, float("nan"), float("inf"), True, "1"]:
            with self.subTest(value=value), self.assertRaises(DataError):
                WaitCheckpoint(value)
        with self.assertRaises(DataError):
            WaitCheckpoint(1).tick(FP.from_raw(-1))


class WalkRouteDeclarationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(Path(__file__).resolve().parents[1] / "data/manifest.json")

    def parse(self, route):
        return WalkRouteSpec.from_json(route, height=7, width=11)

    def test_all_real_walk_routes_preserve_offsets_waits_and_scope(self):
        routes = self.dataset.level["routes"]
        self.assertEqual(sum(route["motionMode"] == "WALK" for route in routes), 28)
        for index in range(10, 38):
            spec = self.parse(routes[index])
            self.assertEqual(spec.end, (3, 0))
            self.assertFalse(spec.scope()["autonomous_route_ready"])
            self.assertFalse(spec.scope()["spawn_zero_range_rng_consumption_validated"])
        self.assertEqual(self.parse(routes[29]).spawn_offset, LocalVector2(.2, -.2))
        self.assertEqual(self.parse(routes[14]).checkpoints[0].reach_offset, LocalVector2(-.33, -.01))
        self.assertEqual([cp.seconds for cp in self.parse(routes[27]).checkpoints if cp.kind == "WAIT_FOR_SECONDS"], [8, 5, 10, 5])

    def test_placeholders_and_unknown_branches_fail_closed(self):
        for route in self.dataset.level["routes"][:10]:
            with self.assertRaises(DataError):
                self.parse(route)
        changes = [("allowDiagonalMove", False), ("visitEveryNodeCenter", True),
                   ("visitEveryTileCenter", True), ("visitEveryCheckPoint", True),
                   ("motionMode", "FLY"), ("spawnRandomRange", {"x": .1, "y": 0})]
        for key, value in changes:
            route = copy.deepcopy(self.dataset.level["routes"][28])
            route[key] = value
            with self.subTest(key=key), self.assertRaises(DataError):
                self.parse(route)
        route = copy.deepcopy(self.dataset.level["routes"][28])
        route["checkpoints"][0]["type"] = "PATROL_MOVE"
        with self.assertRaises(DataError):
            self.parse(route)
        route["checkpoints"][0]["type"] = "MOVE"
        route["checkpoints"][0]["randomizeReachOffset"] = True
        with self.assertRaises(DataError):
            self.parse(route)

    def test_unknown_fields_and_coordinates_are_rejected(self):
        route = copy.deepcopy(self.dataset.level["routes"][28])
        route["futureRule"] = True
        with self.assertRaises(DataError):
            self.parse(route)
        route.pop("futureRule")
        route["endPosition"]["row"] = 7
        with self.assertRaises(DataError):
            self.parse(route)


class NativeFloatGeometryTests(unittest.TestCase):
    def test_local_grid_axes_and_nearest_even_boundaries(self):
        self.assertEqual(grid_to_local((1, 10)), LocalVector2(10, 1))
        self.assertEqual(local_to_grid(LocalVector2(.5, 1.5)), (2, 0))
        self.assertEqual(local_to_grid(LocalVector2(-.5, -1.5)), (-2, 0))
        self.assertEqual(local_to_grid(LocalVector2(2.5, 3.5)), (4, 2))

    def test_single_storage_arithmetic_and_radius_comparison(self):
        a = LocalVector2(1 << 20, 0)
        self.assertEqual((a + LocalVector2(.03125, 0)).x, a.x)
        self.assertEqual((a + LocalVector2(.125, 0)).x, a.x + .125)
        self.assertTrue(check_distance(LocalVector2(0, 0), LocalVector2(.05, 0), .05))
        self.assertFalse(check_distance(LocalVector2(0, 0), LocalVector2(.05, .05), .05))

    def test_normalizer_threshold_differs_from_safe_component_zero(self):
        diagonal = LocalVector2(.000009, .000009)
        self.assertTrue(vector_is_zero(diagonal))
        self.assertEqual(normalize_direction_safely(diagonal), LocalVector2(0, 0))
        self.assertNotEqual(diagonal.normalized(), LocalVector2(0, 0))
        self.assertEqual(LocalVector2(1e-5, 0).normalized(), LocalVector2(0, 0))
        self.assertEqual(LocalVector2(3, 4).normalized(), LocalVector2(.6, .8))

    def test_native_clamp_and_zero_limit(self):
        vector = LocalVector2(3, 4)
        self.assertIs(clamp_magnitude(vector, 5), vector)
        self.assertEqual(clamp_magnitude(vector, 2), LocalVector2(1.2, 1.6))
        self.assertEqual(clamp_magnitude(vector, 0), LocalVector2(0, 0))
        self.assertEqual(clamp_magnitude(vector, -2), LocalVector2(-1.2, -1.6))


class NativePathTests(unittest.TestCase):
    def grid(self, height, width):
        return [[NativeTileSnapshot(3, 15, False, False) for _ in range(width)] for _ in range(height)]

    def test_weighted_fifo_takes_low_cost_detour_and_strict_tie_order(self):
        rows = self.grid(3, 5)
        rows[1][2] = NativeTileSnapshot(3, 15, True, True)
        nodes = NativeWalkPathGrid(rows, source="unit_test_explicit_cached_tile_fixture").next_map((1, 4), smooth=False)
        self.assertEqual(nodes[1][0].distance, 6)  # Unit-cost BFS would choose the four-edge middle row.
        self.assertEqual(nodes[1][2].distance, 1001)  # Goal cost is zero; predecessor pays its own 1000.
        square = NativeWalkPathGrid(self.grid(2, 2), source="unit_test_equal_cost_fifo_fixture").next_map((1, 1), smooth=False)
        self.assertEqual(square[0][0].next_grid, (0, 1))  # Down predecessor is queued before left.

    def test_direction_masks_and_unpassable_targets(self):
        rows = self.grid(1, 2)
        rows[0][0] = NativeTileSnapshot(1, 1 << 1, False, False)  # Native right index is 1.
        nodes = NativeWalkPathGrid(rows, source="unit_test_one_way_fixture").next_map((0, 1), smooth=False)
        self.assertEqual(nodes[0][0].distance, 1)
        rows[0][0] = NativeTileSnapshot(1, 1 << 3, False, False)
        nodes = NativeWalkPathGrid(rows, source="unit_test_wrong_one_way_fixture").next_map((0, 1), smooth=False)
        self.assertFalse(nodes[0][0].is_valid)
        rows[0][1] = NativeTileSnapshot(2, 15, False, False)
        nodes = NativeWalkPathGrid(rows, source="unit_test_fly_only_goal_fixture").next_map((0, 1))
        self.assertTrue(all(not node.is_valid for row in nodes for node in row))

    def test_native_smoothing_rejects_corner_cut_and_obstacle_like_cell(self):
        rows = self.grid(2, 2)
        grid = NativeWalkPathGrid(rows, source="unit_test_open_smoothing_fixture")
        nodes = grid.next_map((1, 1), smooth=False)
        self.assertTrue(grid.raycast_bresenham((0, 0), (1, 1), nodes))
        self.assertEqual(grid.next_map((1, 1))[0][0].next_grid, (1, 1))
        rows[0][1] = NativeTileSnapshot(0, 0, False, False)
        grid = NativeWalkPathGrid(rows, source="unit_test_corner_fixture")
        nodes = grid.next_map((1, 1), smooth=False)
        self.assertTrue(nodes[0][0].is_valid)
        self.assertFalse(grid.raycast_bresenham((0, 0), (1, 1), nodes))
        self.assertEqual(grid.next_map((1, 1))[0][0].next_grid, (1, 0))

    def test_snapshot_requires_explicit_complete_context(self):
        with self.assertRaises(DataError):
            NativeWalkPathGrid(self.grid(1, 1), source="")
        with self.assertRaises(DataError):
            NativeWalkPathGrid([[{"tileKey": "tile_road"}]], source="raw_resource_insufficient")
        with self.assertRaises(DataError):
            NativeTileSnapshot(1, 16, False, False)

    def test_backward_route_maps_keep_wait_empty_and_future_turn(self):
        dataset = Dataset.from_manifest(Path(__file__).resolve().parents[1] / "data/manifest.json")
        route = copy.deepcopy(dataset.level["routes"][28])
        route["startPosition"], route["endPosition"] = {"row": 0, "col": 0}, {"row": 1, "col": 2}
        cp = copy.deepcopy(route["checkpoints"][0])
        cp["position"] = {"row": 0, "col": 2}
        wait = copy.deepcopy(cp)
        wait["type"], wait["time"] = "WAIT_FOR_SECONDS", 5
        route["checkpoints"] = [cp, wait]
        compiled = compile_walk_route(WalkRouteSpec.from_json(route, height=2, width=3),
            NativeWalkPathGrid(self.grid(2, 3), source="unit_test_two_segment_route_fixture"))
        self.assertIsNone(compiled.checkpoint_maps[1])
        self.assertEqual(compiled.checkpoint_maps[0][0][0].distance_to_final, 3)
        self.assertEqual(compiled.checkpoint_maps[0][0][1].next_turn, LocalVector2(0, 1))
        self.assertFalse(compiled.scope["autonomous_route_ready"])


if __name__ == "__main__":
    unittest.main()

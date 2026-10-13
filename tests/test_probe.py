from copy import deepcopy
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from arknights_probe import Dataset, DataError, DeclarationProbeEnv, UnverifiedMechanism
from arknights_probe.data import read_json, sha256
from arknights_probe.navigation import cardinal_path, route_probe


def fixture():
    route = {"motionMode": "WALK", "startPosition": {"row": 0, "col": 0},
             "endPosition": {"row": 0, "col": 2}, "checkpoints": [], "allowDiagonalMove": False,
             "visitEveryTileCenter": False, "visitEveryNodeCenter": False, "visitEveryCheckPoint": False}
    action = {"actionType": "SPAWN", "key": "enemy_test", "count": 2, "preDelay": 3.0,
              "interval": 1.0, "routeIndex": 0, "managedByScheduler": True, "blockFragment": False,
              "dontBlockWave": False, "forceBlockWaveInBranch": False, "weight": 0}
    level = {"mapData": {"map": {"row_size": 1, "column_size": 3, "matrix_data": [0, 0, 0]},
                         "tiles": [{"tileKey": "tile_road", "passableMask": "ALL"}], "tags": []},
             "routes": [route], "extraRoutes": [deepcopy(route)], "enemyDbRefs": [{"id": "enemy_test", "level": 0}],
             "waves": [{"preDelay": 0, "postDelay": 0, "maxTimeWaitingForNextWave": -1,
                        "fragments": [{"preDelay": 0, "actions": [action]}]}],
             "branches": {"test_branch": {"phases": [{"preDelay": 0, "actions": [deepcopy(action)]}]}},
             "randomSeed": 123, "predefines": {}, "hardPredefines": {}}
    return level


class StructuralTests(unittest.TestCase):
    def test_reject_wrong_matrix_dimensions(self):
        data = fixture()
        data["mapData"]["map"]["matrix_data"].pop()
        with self.assertRaisesRegex(DataError, "dimensions"):
            Dataset(data)

    def test_reject_tile_reference(self):
        data = fixture()
        data["mapData"]["map"]["matrix_data"][0] = 5
        with self.assertRaisesRegex(DataError, "tile reference"):
            Dataset(data)

    def test_branch_route_pool_is_extra(self):
        data = fixture()
        data["extraRoutes"] = []
        with self.assertRaisesRegex(DataError, "invalid route reference"):
            Dataset(data)

    def test_reject_missing_enemy_level(self):
        with self.assertRaisesRegex(DataError, "missing level"):
            Dataset(fixture(), {"enemies": {"enemies": {"enemy_test": [{"level": 1}]}}})

    def test_reject_nan_and_boolean_count(self):
        for invalid in (float("nan"), True):
            data = fixture()
            data["waves"][0]["fragments"][0]["actions"][0]["count"] = invalid
            with self.assertRaises(DataError):
                Dataset(data)

    def test_reject_spawn_placeholder(self):
        data = fixture()
        data["routes"][0]["motionMode"] = "E_NUM"
        with self.assertRaisesRegex(DataError, "placeholder"):
            Dataset(data)

    def test_hash_pin_rejects_tamper(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            level = root / "level.json"
            level.write_text(json.dumps(fixture()), encoding="utf-8")
            manifest = root / "manifest.json"
            manifest.write_text(json.dumps({"format_version": 1, "files": {"level": {"path": "level.json", "sha256": sha256(level)}}}), encoding="utf-8")
            Dataset.from_manifest(manifest)
            level.write_text("{}", encoding="utf-8")
            with self.assertRaisesRegex(DataError, "Source changed"):
                Dataset.from_manifest(manifest)

    def test_reject_duplicate_json_key(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "bad.json"
            path.write_text('{"a":1,"a":2}', encoding="utf-8")
            with self.assertRaisesRegex(DataError, "duplicate"):
                read_json(path)


class EnvironmentTests(unittest.TestCase):
    def test_declaration_env_does_not_consume_legacy_random(self):
        env = DeclarationProbeEnv(Dataset(fixture()))
        with patch("arknights_probe.legacy_random.LegacyRandom.sample", side_effect=AssertionError("No automatic battle RNG")):
            _, info = env.reset(seed=42)
            env.step({"type": "next"})
        self.assertFalse(info["native_seed_equivalence"])
        self.assertFalse(info["battle_ready"])

    def test_deterministic_reset_and_exhaustion(self):
        env = DeclarationProbeEnv(Dataset(fixture()))
        first = env.reset(seed=42)
        result = env.step({"type": "next"})
        self.assertIsNone(result[1])
        self.assertTrue(result[2])
        self.assertEqual(first, env.reset(seed=42))
        self.assertEqual(result, env.step({"type": "next"}))
        with self.assertRaisesRegex(RuntimeError, "exhausted"):
            env.step({"type": "next"})

    def test_fail_closed_does_not_mutate_cursor(self):
        env = DeclarationProbeEnv(Dataset(fixture()))
        env.reset()
        with self.assertRaises(UnverifiedMechanism):
            env.step({"type": "deploy", "character": "char_test"})
        self.assertEqual(0, env.cursor)
        with self.assertRaises(UnverifiedMechanism):
            env.compile_battle_schedule()

    def test_observation_does_not_mutate_input(self):
        env = DeclarationProbeEnv(Dataset(fixture()))
        observation, _ = env.reset()
        observation["next_declaration"]["action"]["count"] = 999
        self.assertEqual(env.step({"type": "next"})[4]["inspected_declaration"]["action"]["count"], 2)

    def test_reset_explicit_branch_does_not_simulate_activation(self):
        env = DeclarationProbeEnv(Dataset(fixture()))
        observation, info = env.reset(options={"branch": "test_branch"})
        self.assertEqual(observation["next_declaration"]["route_pool"], "extraRoutes")
        self.assertFalse(info["branch_activation_simulated"])


class NavigationTests(unittest.TestCase):
    def test_native_rowflip_on_asymmetric_map(self):
        data = fixture()
        data["mapData"]["map"] = {"row_size": 2, "column_size": 3, "matrix_data": [0, 0, 0, 1, 1, 1]}
        data["mapData"]["tiles"].append({"tileKey": "tile_wall", "passableMask": "FLY_ONLY"})
        ds = Dataset(data)
        self.assertEqual(ds.tile(0, 0)["tileKey"], "tile_wall")
        self.assertEqual(ds.tile(1, 0)["tileKey"], "tile_road")
        self.assertEqual(ds.matrix_tile(0, 0)["tileKey"], "tile_road")
        self.assertIsNone(cardinal_path(ds, (0, 0), (0, 2)))
        self.assertIsNotNone(cardinal_path(ds, (0, 0), (0, 2), row_mapping="matrix"))
        self.assertTrue(route_probe(ds, 0)["coordinate_mapping_native_verified"])

    def test_native_rowflip_preserves_columns_and_tile_indirection(self):
        data = fixture()
        data["mapData"]["map"] = {"row_size": 2, "column_size": 3, "matrix_data": [4, 1, 5, 2, 0, 3]}
        data["mapData"]["tiles"] = [{"tileKey": f"test_{i}", "passableMask": "ALL"} for i in range(6)]
        ds = Dataset(data)
        self.assertEqual([ds.tile(0, c)["tileKey"] for c in range(3)], ["test_2", "test_0", "test_3"])
        self.assertEqual([ds.tile(1, c)["tileKey"] for c in range(3)], ["test_4", "test_1", "test_5"])
        with self.assertRaises(DataError):
            ds.tile(-1, 0)

    def test_path_and_obstacle(self):
        data = fixture()
        ds = Dataset(data)
        self.assertEqual(cardinal_path(ds, (0, 0), (0, 2)), [(0, 0), (0, 1), (0, 2)])
        data["mapData"]["tiles"].append({"tileKey": "tile_wall", "passableMask": "FLY_ONLY"})
        data["mapData"]["map"]["matrix_data"][1] = 1
        self.assertIsNone(cardinal_path(Dataset(data), (0, 0), (0, 2)))

    def test_route_probe_declares_its_limits(self):
        result = route_probe(Dataset(fixture()), 0)
        self.assertTrue(result["all_segments_reachable"])
        self.assertEqual(result["scope"], "cardinal_grid_topology_only")


if __name__ == "__main__":
    unittest.main()

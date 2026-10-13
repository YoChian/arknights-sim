"""Integration checks for the pinned user-owned snapshot prepared by the CLI."""
from pathlib import Path
import unittest

from arknights_probe import Dataset, DeclarationProbeEnv
from arknights_probe.navigation import route_probe


class LocalSnapshotTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        manifest = Path(__file__).resolve().parents[1] / "data" / "manifest.json"
        if not manifest.is_file():
            raise unittest.SkipTest("Run python -m arknights_probe prepare for local snapshot tests")
        cls.dataset = Dataset.from_manifest(manifest)

    def test_local_snapshot_cross_references(self):
        summary = self.dataset.summary()
        self.assertEqual(summary["dimensions"], {"rows": 7, "cols": 11})
        self.assertEqual(summary["enemy_references"], 10)
        self.assertEqual(summary["route_modes"], {"E_NUM": 10, "WALK": 28})
        self.assertEqual(summary["main_declarations"], 38)
        self.assertEqual(summary["schema_status"], "structurally_verified_community_schema")
        self.assertIn("rogue_6", summary["topics"])

    def test_local_full_replay_is_repeatable(self):
        env = DeclarationProbeEnv(self.dataset)
        def replay():
            obs, info = env.reset(seed=42)
            events = []
            while obs["remaining"]:
                obs, reward, done, truncated, detail = env.step({"type": "next"})
                self.assertIsNone(reward)
                events.append(detail["inspected_declaration"])
            self.assertTrue(done)
            return events
        self.assertEqual(replay(), replay())

    def test_local_route_anchor_connectivity(self):
        result = route_probe(self.dataset, 10)
        self.assertTrue(result["all_segments_reachable"])
        self.assertEqual(result["declared_wait_seconds"], [99.0])

    def test_local_native_coordinate_mapping_all_walk_routes(self):
        probes = [route_probe(self.dataset, i) for i, route in enumerate(self.dataset.routes) if route["motionMode"] == "WALK"]
        self.assertEqual(len(probes), 28)
        self.assertTrue(all(probe["all_segments_reachable"] for probe in probes))
        self.assertTrue(all(probe["coordinate_mapping_native_verified"] for probe in probes))
        self.assertEqual(self.dataset.tile(1, 10)["tileKey"], "tile_start")
        self.assertEqual(self.dataset.matrix_tile(1, 10)["tileKey"], "tile_forbidden")


if __name__ == "__main__":
    unittest.main()

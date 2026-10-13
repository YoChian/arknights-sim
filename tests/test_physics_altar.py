from pathlib import Path
import unittest

from arknights_probe import Dataset
from arknights_probe.physics_altar import PhysicsPlannedAltarProbe


ROOT = Path(__file__).resolve().parents[1]


class PhysicsAltarTests(unittest.TestCase):
    def make(self):
        return PhysicsPlannedAltarProbe(Dataset.from_manifest(ROOT / "data/manifest.json"))

    def test_query_is_captured_in_fixed_phase_before_pre_delay_damage(self):
        p = self.make()
        p.step(210)
        record = p.physics_records[0]
        self.assertEqual(len(record["plans"]), 3)
        for plan in record["plans"]:
            self.assertEqual((plan["epoch"]["frame"], plan["epoch"]["phase"]), (210, "objects_fixed"))
            self.assertEqual(plan["layer_mask"], 268436992)
            self.assertEqual(plan["buffer_capacity"], 128)
        self.assertEqual([r["unity_collider_ids"] for r in record["results"]], [[200], [200], [200]])
        self.assertFalse(record["physics_overlap_generated"])
        self.assertEqual(p.damage_results, [])
        p.step(17)
        self.assertEqual(len(p.damage_results), 1)
        self.assertEqual(p.damage_results[0]["frame"], 227)

    def test_bound_external_receipts_preserve_dedup_damage_and_delayed_recycle(self):
        p = self.make()
        s = p.step(10000)
        self.assertEqual(len(p.physics_records), 18)
        self.assertEqual(sum(x["applied"] for x in p.damage_results), 18)
        self.assertEqual((p.damage_results[1]["frame"], p.damage_results[-1]["frame"]), (469, 4325))
        self.assertEqual((s["frame"], s["hp_raw"], s["life"], s["recycled"]), (4343, 0, 3, True))
        a = p.artifact()
        for name in ("battle_ready", "autonomous_route_ready", "runtime_battle_validated"):
            self.assertFalse(a[name])
        self.assertIn("not executed", a["external_inputs"]["unity_simulation_and_sync"])

    def test_reset_and_chunked_steps_preserve_query_receipt_epochs(self):
        p = self.make()
        p.step(500)
        expected = p.artifact()
        p.reset()
        p.step(209)
        p.step(1)
        p.step(17)
        p.step(273)
        self.assertEqual(p.artifact(), expected)


if __name__ == "__main__":
    unittest.main()

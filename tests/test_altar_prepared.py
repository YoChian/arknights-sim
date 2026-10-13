import unittest
from pathlib import Path

from arknights_probe import Dataset
from arknights_probe.altar_prepared import PreparedAltarProbe
from arknights_probe.altar_component import AltarComponentProbe
from arknights_probe.fp import FP


class PreparedAltarIntegrationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(Path(__file__).resolve().parents[1] / "data/manifest.json")

    def test_real_preparation_and_masks_reach_first_damage(self):
        probe = PreparedAltarProbe(self.dataset)
        self.assertEqual(probe.preparation.duration.raw, FP.from_int32(1).raw)
        self.assertEqual(probe.preparation.cooldown.raw, FP.from_int32(1).raw)
        self.assertEqual(probe.selection_inputs["source_side"], 2)
        self.assertEqual(probe.selection_inputs["absolute_target_side_mask"], 7)
        self.assertEqual(probe.selection_inputs["source_purpose_mask"], 0)
        self.assertEqual(probe.selection_inputs["query_layer_mask"], 0x10000600)
        probe.step(230)
        self.assertEqual([d["frame"] for d in probe.damage_results], [227])
        self.assertEqual(probe.actor.hp.raw, FP.from_int32(8500).raw)
        self.assertEqual(probe.selections[0]["hit_uids"], [2])
        self.assertFalse(probe.snapshot()["battle_ready"])

    def test_prepared_duration_changes_second_cast_without_changing_damage(self):
        old = AltarComponentProbe(self.dataset)
        new = PreparedAltarProbe(self.dataset)
        old.step(470)
        new.step(470)
        self.assertEqual([d["frame"] for d in old.damage_results], [227, 457])
        self.assertEqual([d["frame"] for d in new.damage_results], [227, 469])
        self.assertEqual(new.actor.hp.raw, old.actor.hp.raw)
        self.assertEqual(new.skill.context.prepared_duration.raw, FP.from_int32(1).raw)

    def test_prepared_chain_finishes_via_damage_and_delayed_recycle(self):
        probe = PreparedAltarProbe(self.dataset)
        result = probe.step(10000)
        self.assertEqual(len(probe.damage_results), 18)
        self.assertTrue(all(d["applied"] for d in probe.damage_results))
        self.assertEqual(result["hp_raw"], 0)
        self.assertEqual(result["finish_reason"], 2)
        self.assertTrue(result["recycled"])
        self.assertEqual(result["life"], 3)
        self.assertEqual(result["finish_request"], "win")
        self.assertGreater(result["frame"], probe.damage_results[-1]["frame"])
        self.assertGreater(result["frame"], 4139)
        self.assertIsNone(result["reward"])

    def test_reset_rebuilds_prepared_skill_and_selector_before_ticking(self):
        probe = PreparedAltarProbe(self.dataset)
        probe.step(470)
        expected = probe.artifact()
        initial = probe.reset()
        self.assertEqual(initial["frame"], 0)
        self.assertEqual(probe.simulator.next_handle, 0)
        probe.step(240)
        probe.step(230)
        self.assertEqual(probe.artifact(), expected)
        self.assertEqual(len(probe.registry.objects), 2)


if __name__ == "__main__":
    unittest.main()

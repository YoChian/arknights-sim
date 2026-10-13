from copy import deepcopy
from pathlib import Path
import unittest

from arknights_probe.data import DataError, Dataset, read_json
from arknights_probe.enemy_creation_inputs import derive_enemy_runtime
from arknights_probe.prepare import DEFAULT_MANIFEST
from arknights_probe.timeline import compile_timeline
from arknights_probe.enemy_validation import verify_enemy_rules_evidence, verify_enemy_data_evidence


class CreationInputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(DEFAULT_MANIFEST)
        cls.prefabs = read_json(Path(r"D:\Repo\.rea-tools\arknights-pc\native_v4\resources\prefab_inputs.json"))
        cls.counted = {key: True for key in cls.dataset.enemy_refs}

    def derive(self, prefabs=None, counted=None):
        return derive_enemy_runtime(self.dataset, self.prefabs if prefabs is None else prefabs,
                                    counted_creation=self.counted if counted is None else counted,
                                    source="explicit_post_Init_alive_fixture_and_absent_hotfix_context")

    def test_real_prefab_delays_replace_zero_fixture(self):
        report = self.derive()
        runtime = report["enemy_runtime"]
        self.assertEqual({key for key, item in runtime.items() if item["extraSpawnDelay"] == 1},
                         {"enemy_2133_shdopl", "enemy_2152_shezlc"})
        self.assertTrue(all(item["extraSpawnDelay"] == 0 for key, item in runtime.items()
                            if key not in {"enemy_2133_shdopl", "enemy_2152_shezlc"}))
        self.assertFalse(report["creation_runtime_validated"])
        self.assertTrue(verify_enemy_data_evidence()["healthy"])
        self.assertIn("post_Init_counted_creation_eligibility", report["external"])

    def test_bits_and_tile_dependent_delay_are_strict(self):
        key = next(iter(self.prefabs["enemies"]))
        for field, value in (("delay_to_born_bits", "0x3f800000"), ("only_delay_on_start_tile", True),
                             ("delay_to_born_float32", float("inf"))):
            changed = deepcopy(self.prefabs)
            changed["enemies"][key][field] = value
            with self.assertRaises(DataError):
                self.derive(changed)

    def test_creation_eligibility_is_explicit_and_can_be_false(self):
        counted = dict(self.counted)
        key = next(iter(counted))
        counted[key] = False
        self.assertFalse(self.derive(counted=counted)["enemy_runtime"][key]["successfulCountedCreation"])
        del counted[key]
        with self.assertRaises(DataError):
            self.derive(counted=counted)

    def test_reviewed_static_and_shipped_inputs_match_pins(self):
        report = verify_enemy_rules_evidence()
        self.assertTrue(report["healthy"])
        self.assertFalse(report["creation_runtime_validated"])

    def test_resolved_timeline_examples_retain_explicit_eligibility_and_choices(self):
        root = Path(__file__).resolve().parents[1]
        runtime = self.derive()["enemy_runtime"]
        for mode in ("normal", "four_star"):
            config = read_json(root / f"examples/timeline_{mode}_resolved.json")
            self.assertEqual(config["enemy_runtime"], runtime)
            self.assertIn("external_post_Init_alive_creation_fixture", config["input_source"])
            compiled = compile_timeline(self.dataset, **config)
            self.assertEqual(compiled.group_selections, {"t1": 0, "t2": 5, "c1": 4})


if __name__ == "__main__":
    unittest.main()

import copy
import json
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import unittest

from arknights_probe.data import Dataset
from arknights_probe.fp import FP
from arknights_probe.skill_preparation import (INPUTS, UnverifiedPreparation,
    prepare_altar_skill, prepare_specified_ability)

ROOT = Path(__file__).resolve().parents[1]


def specified(**changes):
    values = dict(pre_delay=.6, cooldown=1., time_mode=2, animation_key="",
        animation_keys=("Idle", "Born", "Die"), wait_for_attack_event=False,
        max_anim_scale=-1., native_default_no_hotfix=True)
    values.update(changes)
    return prepare_specified_ability(**values)


class SkillPreparationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(ROOT / "data/manifest.json")

    def prepare(self, dataset=None, **changes):
        flags = dict(native_default_no_hotfix=True, no_external_skill_modifier=True)
        flags.update(changes)
        return prepare_altar_skill(self.dataset if dataset is None else dataset, **flags)

    def test_actual_resource_preparation_is_not_table_duration(self):
        result = self.prepare()
        self.assertEqual(result.pre_delay.raw, 2576980480)
        self.assertEqual(result.duration.raw, 4294967296)
        self.assertEqual(result.cooldown.raw, 4294967296)
        self.assertEqual(self.dataset.tables["skills"]["skills"]["sktok_ore"]["levels"][0]["duration"], 0.)
        self.assertEqual(result.blackboard, {"value": 500., "duration": 0.})
        self.assertNotEqual(result.duration.raw, FP.from_float32(result.blackboard["duration"]).raw)

    def test_actual_sp_owner_and_range_declarations(self):
        p = self.prepare()
        self.assertEqual((p.sp_cost, p.init_sp), (7, 0))
        self.assertEqual(p.sp_increment.raw, FP.from_int32(1).raw)
        self.assertEqual(p.sp_recovery_per_second.raw, FP.from_int32(1).raw)
        self.assertEqual((p.skill_id, p.range_id), ("sktok_ore", "x-1"))
        self.assertEqual(p.provenance["ability_behaviour_count"], 1)
        self.assertEqual(p.provenance["basic_skill_behaviour_count"], 0)
        self.assertTrue(any("Unity Init" in c for c in p.remaining_external_context))

    def test_fp_min_applies_after_single_conversion(self):
        self.assertEqual(specified(pre_delay=2., cooldown=1.)[0], FP.from_int32(1))
        self.assertEqual(specified(pre_delay=1., cooldown=1.)[0], FP.from_int32(1))
        self.assertEqual(specified(pre_delay=0., cooldown=1.)[0], FP(0))
        self.assertEqual(specified(pre_delay=.6, cooldown=0.)[0], FP(0))
        self.assertEqual(specified(pre_delay=.60000001)[0], FP(2576980480))
        self.assertEqual(specified(pre_delay=2 ** -33)[0], FP(0))

    def test_missing_animation_skips_max_anim_scale_block(self):
        self.assertEqual(specified(max_anim_scale=0.), specified(max_anim_scale=-1.))
        self.assertEqual(specified(max_anim_scale=100.), specified(max_anim_scale=-1.))

    def test_matching_animation_and_other_modes_rejected(self):
        for changes in [dict(animation_key="Idle"), dict(animation_keys=("",)),
                        dict(time_mode=0), dict(time_mode=1), dict(time_mode=3),
                        dict(time_mode=True), dict(wait_for_attack_event=True),
                        dict(animation_keys=("Idle", "Idle"))]:
            with self.subTest(changes=changes), self.assertRaises(UnverifiedPreparation):
                specified(**changes)

    def test_numeric_boundaries_rejected(self):
        for value in [True, -.1, float("nan"), float("inf"), 1e39, 1e10]:
            with self.subTest(value=value), self.assertRaises(UnverifiedPreparation):
                specified(pre_delay=value)
        with self.assertRaises(UnverifiedPreparation):
            specified(cooldown=-1.)

    def test_context_booleans_are_explicit(self):
        for key in ("native_default_no_hotfix", "no_external_skill_modifier"):
            for value in (False, 1, None, "true"):
                with self.subTest(key=key, value=value), self.assertRaises(UnverifiedPreparation):
                    self.prepare(**{key: value})

    def test_changed_skill_row_rejected(self):
        tables = dict(self.dataset.tables)
        tables["skills"] = copy.deepcopy(tables["skills"])
        tables["skills"]["skills"]["sktok_ore"]["levels"][0]["duration"] = 1.
        with self.assertRaises(UnverifiedPreparation):
            self.prepare(SimpleNamespace(tables=tables, level=self.dataset.level))

    def test_changed_predefine_rejected(self):
        level = copy.deepcopy(self.dataset.level)
        next(p for p in level["predefines"]["tokenInsts"] if p["alias"] == "trap_011_ore#1")["hidden"] = True
        with self.assertRaises(UnverifiedPreparation):
            self.prepare(SimpleNamespace(tables=self.dataset.tables, level=level))

    def test_resource_snapshot_cannot_be_silently_replaced(self):
        with TemporaryDirectory() as directory:
            p = Path(directory) / "inputs.json"
            data = json.loads(INPUTS.read_text(encoding="utf-8"))
            data["prefabs"][0]["rule_components"][0]["class_name"] = "Changed"
            p.write_text(json.dumps(data), encoding="utf-8")
            with self.assertRaises(UnverifiedPreparation):
                self.prepare(resource_inputs_path=p)

    def test_result_is_independent_and_json_serializable(self):
        a = self.prepare()
        a.blackboard["duration"] = 123.
        b = self.prepare()
        self.assertEqual(b.blackboard["duration"], 0.)
        self.assertEqual(json.loads(json.dumps(b.as_dict()))["duration_raw"], 4294967296)

    def test_cross_language_reference_is_not_client_oracle(self):
        evidence = ROOT / "evidence/skill_preparation"
        report = json.loads((evidence / "reference_report.json").read_text(encoding="utf-8"))
        self.assertTrue(report["all_equal"])
        self.assertFalse(report["client_runtime_compared"])
        self.assertGreaterEqual(report["vectors"], 16)
        self.assertEqual((evidence / "reference_output.tsv").read_text(),
                         (evidence / "python_output.tsv").read_text())


if __name__ == "__main__":
    unittest.main()

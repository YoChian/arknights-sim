from copy import deepcopy
import unittest

from arknights_probe.data import DataError, Dataset
from arknights_probe.enemy_data import resolve_enemy
from arknights_probe.enemy_rules import apply_selected_attribute_mul, enemy_profile
from arknights_probe.prepare import DEFAULT_MANIFEST


class EnemyRuleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = Dataset.from_manifest(DEFAULT_MANIFEST)

    def enemy(self, key="enemy_2133_shdopl"):
        return resolve_enemy(self.data.tables["enemies"], self.data.enemy_refs[key])

    def test_installed_enemy_selected_multiplier_preserves_overwrite_and_original(self):
        before = self.enemy()
        original = deepcopy(before)
        result = apply_selected_attribute_mul(before, {"atk": 1.2, "maxHp": 1.4}, source="selected_fixture")
        self.assertEqual(result.attribute_values["atk"], 384)
        self.assertEqual(result.attribute_values["maxHp"], 7000)
        self.assertEqual(before, original)
        self.assertEqual(result.talent_blackboard, original.talent_blackboard)
        self.assertTrue(any(x["key"] == "summon.enemy_key" and x["valueStr"] == "enemy_3001_upeopl"
                            for x in result.talent_blackboard))
        self.assertFalse(enemy_profile(result)["battle_ready"])

    def test_integer_multiplier_ties_even_after_single_write(self):
        for hp, expected in ((3, 2), (5, 2), (7, 4), (9, 4)):
            database = {"enemies": {"test": [{"level": 0, "enemyData": {
                "attributes": {"maxHp": {"m_defined": True, "m_value": hp}}}}]}}
            enemy = resolve_enemy(database, {"useDb": True, "id": "test", "level": 0})
            result = apply_selected_attribute_mul(enemy, {"maxHp": .5}, source="half_fixture")
            self.assertEqual(result.attribute_values["maxHp"], expected)

    def test_fp_clamp_precedes_integer_write_and_refresh(self):
        enemy = self.enemy()
        result = apply_selected_attribute_mul(enemy, {"maxHp": -2, "magicResistance": 10}, source="clamp_fixture")
        self.assertEqual(result.attribute_values["maxHp"], 1)
        self.assertEqual(result.attribute_values["magicResistance"], 100)
        self.assertEqual(result.attributes["magicResistance"].raw, 100 << 32)

    def test_unknown_nonfinite_bool_or_unsourced_modifier_is_rejected(self):
        enemy = self.enemy()
        for values, source in (({"unknown": 1}, "test"), ({"atk": float("nan")}, "test"),
                               ({"atk": True}, "test"), ({"atk": 1}, ""), ({"atk": 1e100}, "test")):
            with self.assertRaises(DataError):
                apply_selected_attribute_mul(enemy, values, source=source)

    def test_all_ten_references_can_be_reviewed_without_inferred_run_modifiers(self):
        profiles = [enemy_profile(resolve_enemy(self.data.tables["enemies"], ref))
                    for ref in self.data.enemy_refs.values()]
        self.assertEqual(len(profiles), 10)
        self.assertTrue(all(not p["effective_entity_modifiers_applied"] and not p["battle_ready"] for p in profiles))
        peoples = next(p for p in profiles if p["id"] == "enemy_3001_upeopl")
        self.assertEqual(peoples["attribute_values"]["magicResistance"], 0)
        self.assertEqual(peoples["attribute_values"]["baseAttackTime"], 1)


if __name__ == "__main__":
    unittest.main()

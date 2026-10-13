from copy import deepcopy
import json
from pathlib import Path
import unittest

from arknights_probe.data import DataError
from arknights_probe.enemy_data import (resolve_enemy_reference, resolve_enemy,
                                       UnverifiedEnemyData, read_attribute,
                                       write_attribute, refresh_attributes,
                                       clamp_attribute)
from arknights_probe.fp import FP


def defined(value):
    return {"m_defined": True, "m_value": value}


class EnemyDataTests(unittest.TestCase):
    def test_actual_ten_refs_restore_missing_defaults_and_overwrite(self):
        fixture = json.loads((Path(__file__).resolve().parents[1] / "evidence/enemy_data/fixtures.json").read_text(encoding="utf8"))
        resolved = {ref["id"]: resolve_enemy(fixture["database"], ref) for ref in fixture["references"]}
        self.assertEqual(len(resolved), 10)
        for result in resolved.values():
            self.assertEqual(result.applied_levels, [0])
            self.assertEqual(len(result.attributes), 34)
            self.assertEqual(len(result.attribute_values), 45)
            self.assertEqual(result.unsupported_mechanisms, set())
            self.assertEqual(result.values["key"], result.enemy_id)
        friendly = resolved["enemy_3001_upeopl"]
        self.assertEqual(friendly.attributes["magicResistance"].raw, 0)
        self.assertEqual(friendly.attributes["baseAttackTime"].raw, 1 << 32)
        self.assertEqual(friendly.attributes["moveSpeed"].raw, 2791728640)
        self.assertEqual(friendly.field_sources["attributes.baseAttackTime"], "AttributesData.ctor")
        self.assertEqual(friendly.values["lifePointReduce"], 0)
        summon = resolved["enemy_2133_shdopl"]
        self.assertEqual(summon.talent_blackboard, [{"key": "summon.enemy_key", "value": 0.0, "valueStr": "enemy_3001_upeopl"}])
        self.assertEqual(len(resolved["enemy_1085_sotiwz_3"].skills), 2)

    def test_independent_csharp_reference_numeric_vectors(self):
        path = Path(__file__).resolve().parents[1] / "evidence/enemy_data/reference_vectors.json"
        vectors = json.loads(path.read_text(encoding="utf8"))["vectors"]
        self.assertEqual(len(vectors), 629)
        for vector in vectors:
            case, expected = vector["input"], vector["expected"]
            with self.subTest(id=case["id"]):
                database = {"enemies": {"enemy": [{"level": 0, "enemyData": {}}]}}
                result = resolve_enemy(database, {"useDb": True, "id": "enemy", "level": 0})
                value = FP.from_raw(case["fp_raw"]) if case["mode"] == "write_fp" else case["value"]
                write_attribute(result, case["name"], value)
                refresh_attributes(result)
                self.assertEqual(result.attribute_values[case["name"]], expected["decoded"])
                self.assertEqual(result.unclamped_attributes[case["name"]].raw, expected["unclamped_raw"])
                self.assertEqual(result.attributes[case["name"]].raw, expected["clamped_raw"])

    def test_ordered_optional_inheritance_preserves_defined_zero_and_false(self):
        database = {"enemies": {"enemy": [
            {"level": 0, "enemyData": {"attributes": {"maxHp": defined(100), "atk": defined(20), "stunImmune": defined(True)}}},
            {"level": 1, "enemyData": {"attributes": {"maxHp": {"m_defined": False, "m_value": 0}, "atk": defined(0), "stunImmune": defined(False)}}},
        ]}}
        result = resolve_enemy_reference({"useDb": True, "id": "enemy", "level": 1}, database)
        self.assertEqual(result.applied_levels, [0, 1])
        self.assertEqual({name: result.attribute_values[name] for name in ("maxHp", "atk", "stunImmune")},
                         {"maxHp": 100, "atk": 0, "stunImmune": False})
        self.assertEqual(result.field_sources["attributes.maxHp"], "database:enemy:level:0")
        self.assertEqual(result.attribute_values["def"], 0)
        self.assertEqual(result.require_attributes("maxHp"), {"maxHp": FP.from_int32(100)})
        self.assertEqual(result.unresolved_defaults, set())
        with self.assertRaises(UnverifiedEnemyData):
            result.require_attributes("unknown")

    def test_exact_level_required_and_unsorted_list_is_not_resorted(self):
        entries = [{"level": 2, "enemyData": {"attributes": {"atk": defined(2)}}},
                   {"level": 0, "enemyData": {"attributes": {"atk": defined(9)}}}]
        database = {"enemies": {"enemy": entries}}
        reference = {"useDb": True, "id": "enemy", "level": 0}
        self.assertEqual(resolve_enemy_reference(reference, database).applied_levels, [])
        reference["level"] = 1
        with self.assertRaises(DataError):
            resolve_enemy_reference(reference, database)
        reference["level"] = -1
        result = resolve_enemy_reference(reference, database)
        self.assertEqual(result.applied_levels, [2])
        self.assertEqual(result.attribute_values["atk"], 2)

    def test_nonoptional_override_retained_with_all_wrappers_undefined(self):
        reference = {"useDb": True, "id": "enemy", "level": 0, "overwrittenData": {
            "attributes": {"maxHp": {"m_defined": False, "m_value": 0}},
            "talentBlackboard": [{"key": "summon.enemy_key", "value": 0, "valueStr": "other_enemy"}]}}
        database = {"enemies": {"enemy": [{"level": 0, "enemyData": {"attributes": {"maxHp": defined(100)}}}]}}
        original = deepcopy((reference, database))
        result = resolve_enemy_reference(reference, database)
        self.assertEqual(result.attribute_values["maxHp"], 100)
        self.assertEqual(result.collection_layers[0]["values"]["talentBlackboard"][0]["valueStr"], "other_enemy")
        self.assertEqual(result.talent_blackboard, [{"key": "summon.enemy_key", "value": 0.0, "valueStr": "other_enemy"}])
        self.assertEqual((reference, database), original)

    def test_defaults_are_constructor_values_not_optional_placeholders(self):
        database = {"enemies": {"enemy": [{"level": 0, "enemyData": {"attributes": {
            "maxHp": {"m_defined": False, "m_value": 0},
            "baseAttackTime": {"m_defined": False, "m_value": 0},
            "magicResistance": {"m_defined": False, "m_value": 100},
        }}}]}}
        result = resolve_enemy(database, {"useDb": True, "id": "enemy", "level": 0})
        self.assertEqual(result.attribute_values["maxHp"], 100)
        self.assertEqual(result.attribute_values["baseAttackTime"], 1.0)
        self.assertEqual(result.attribute_values["magicResistance"], 0.0)
        self.assertEqual(result.attribute_values["damageHitratePhysical"], 1.0)
        self.assertEqual(result.attribute_values["epBreakRecoverSpeed"], 1.0)
        self.assertEqual(result.values["rangeRadius"], -1.0)
        self.assertEqual(result.values["lifePointReduce"], 1)
        self.assertEqual(result.values["motion"], "WALK")
        self.assertEqual(result.values["applyWay"], "MELEE")
        self.assertEqual(result.values["levelType"], "NORMAL")

    def test_single_int_conversion_clamp_and_primitive_fp_views(self):
        database = {"enemies": {"enemy": [{"level": 0, "enemyData": {"attributes": {
            "maxHp": defined(16777217), "moveSpeed": defined(0.0),
            "magicResistance": defined(120.0), "tauntLevel": defined(-3),
        }}}]}}
        result = resolve_enemy(database, {"useDb": True, "id": "enemy", "level": 0})
        self.assertEqual(result.numeric["maxHp"], 16777216)
        self.assertEqual(result.numeric["moveSpeed"], 0.0)
        self.assertEqual(result.attributes["moveSpeed"].raw, 429496736)
        self.assertEqual(result.attributes["magicResistance"], FP.from_int32(100))
        self.assertEqual(result.attributes["tauntLevel"], FP.from_int32(-2))
        self.assertEqual(result.unclamped_attributes["magicResistance"], FP.from_int32(120))
        write_attribute(result, "maxHp", FP.from_float32(2.5))
        self.assertEqual(result.numeric["maxHp"], 2)
        self.assertEqual(read_attribute(result, "maxHp"), 2.0)
        refresh_attributes(result)
        self.assertEqual(result.attributes["maxHp"], FP.from_int32(2))
        self.assertEqual(result.database_attribute_values["maxHp"], 16777216)
        write_attribute(result, "maxHp", 2147483647)
        self.assertEqual(result.numeric["maxHp"], -(1 << 31))
        refresh_attributes(result)
        self.assertEqual(result.attributes["maxHp"], FP.from_int32(1))
        self.assertEqual(clamp_attribute("attackSpeed", FP.from_int32(0)), FP.from_int32(20))

    def test_blackboard_key_replacement_moves_key_to_end_and_string_gate(self):
        database = {"enemies": {"enemy": [
            {"level": 0, "enemyData": {"talentBlackboard": [{"key": "x", "value": 1}, {"key": "y", "value": 2}]}},
            {"level": 1, "enemyData": {"talentBlackboard": [{"key": "x", "value": 9, "valueStr": ""}, {"key": "x", "valueStr": "text", "value": 999}]}},
        ]}}
        result = resolve_enemy(database, {"useDb": True, "id": "enemy", "level": 1})
        self.assertEqual(result.talent_blackboard, [{"key": "y", "value": 2.0}, {"key": "x", "value": 0.0, "valueStr": "text"}])

    def test_skill_replacement_inherits_blackboard_only_when_new_board_nonempty(self):
        database = {"enemies": {"enemy": [
            {"level": 0, "enemyData": {"skills": [{"prefabKey": "S", "cooldown": 3.0, "blackboard": [{"key": "x", "value": 1}, {"key": "y", "value": 2}]}]}},
            {"level": 1, "enemyData": {"skills": [{"prefabKey": "S", "cooldown": 4.0, "blackboard": [{"key": "x", "value": 0}]}]}},
            {"level": 2, "enemyData": {"skills": [{"prefabKey": "S", "cooldown": 5.0, "blackboard": []}]}},
        ]}}
        one = resolve_enemy(database, {"useDb": True, "id": "enemy", "level": 1})
        self.assertEqual(one.skills[0]["cooldown"], 4.0)
        self.assertEqual(one.skills[0]["blackboard"], [{"key": "y", "value": 2.0}, {"key": "x", "value": 0.0}])
        two = resolve_enemy(database, {"useDb": True, "id": "enemy", "level": 2})
        self.assertEqual(two.skills[0]["blackboard"], [])

    def test_bad_optional_and_unsupported_reference_fail_closed(self):
        database = {"enemies": {"enemy": [{"level": 0, "enemyData": {"attributes": {"maxHp": {"m_defined": 1, "m_value": 10}}}}]}}
        with self.assertRaises(DataError):
            resolve_enemy_reference({"useDb": True, "id": "enemy", "level": 0}, database)
        with self.assertRaises(UnverifiedEnemyData):
            resolve_enemy_reference({"useDb": False, "id": "enemy", "level": 0}, database)
        database["enemies"]["enemy"][0]["enemyData"]["attributes"]["maxHp"] = defined(True)
        with self.assertRaises(DataError):
            resolve_enemy_reference({"useDb": True, "id": "enemy", "level": 0}, database)


if __name__ == "__main__":
    unittest.main()

"""Static EnemyDatabase resolution; battle effect modifiers are separate.

GetComputedEnemyData 0x182417f40 applies database entries in stored order,
stopping at the first level above the requested level. Missing optional values
are never turned into zero. AttributesData construction and the Reset FP view
are recovered separately from dynamic _CalculateAttributeValue effects.
"""
from __future__ import annotations

from copy import deepcopy
from dataclasses import dataclass, field
import math
from typing import Any

from .data import DataError
from .fp import FP, binary32, MIN_VALUE, MAX_VALUE


class UnverifiedEnemyData(RuntimeError):
    """A needed native mechanism or default is not established."""


INT_ATTRIBUTES = frozenset({"maxHp", "atk", "def", "cost", "blockCnt", "respawnTime",
                            "maxDeployCount", "massLevel", "baseForceLevel", "tauntLevel"})
FLOAT_ATTRIBUTES = frozenset({"magicResistance", "moveSpeed", "attackSpeed", "baseAttackTime",
                              "hpRecoveryPerSec", "spRecoveryPerSec", "epDamageResistance", "epResistance",
                              "damageHitratePhysical", "damageHitrateMagical", "epBreakRecoverSpeed"})
BOOL_ATTRIBUTES = frozenset({"stunImmune", "silenceImmune", "sleepImmune", "frozenImmune", "levitateImmune",
                             "disarmedCombatImmune", "fearedImmune", "palsyImmune", "attractImmune",
                             "teleportImmune", "groundBoundImmune"})
OPTIONAL_FIELDS = frozenset({"name", "description", "prefabKey", "applyWay", "motion", "enemyTags",
                             "lifePointReduce", "levelType", "rangeRadius", "numOfExtraDrops",
                             "viewRadius", "notCountInTotal"})
COLLECTION_FIELDS = frozenset({"talentBlackboard", "skills", "spData"})
RUNTIME_INT_ATTRIBUTES = INT_ATTRIBUTES | {"maxDeckStackCnt", "maxEp"}
RUNTIME_FLOAT_ATTRIBUTES = FLOAT_ATTRIBUTES | {
    "abilityRangeForwardExtend", "defPenetrate", "magicResistPenetrate",
    "hpRecoveryPerSecByMaxHpRatio", "defPenetrateFixed", "oneMinusStatusResistance",
    "magicResistPenetrateFixed", "epRecoveryPerSec", "spRecoverRatio", "slowDown", "blockRadiusScale",
}
NUMERIC_ATTRIBUTES = RUNTIME_INT_ATTRIBUTES | RUNTIME_FLOAT_ATTRIBUTES

# Torappu.AttributesData..ctor 0x18231b650. The two uninitialized
# ObscuredInt values (atk/def) decode to zero via InternalDecrypt.
DEFAULT_ATTRIBUTE_VALUES = {
    "maxHp": 100, "atk": 0, "def": 0, "magicResistance": 0.0,
    "cost": 1, "blockCnt": 1, "moveSpeed": 1.0, "attackSpeed": 100.0,
    "baseAttackTime": 1.0, "respawnTime": 60, "hpRecoveryPerSec": 0.0,
    "spRecoveryPerSec": 1.0, "maxDeployCount": 1, "maxDeckStackCnt": 0,
    "tauntLevel": 0, "massLevel": 0, "baseForceLevel": 0,
    "epDamageResistance": 0.0, "epResistance": 0.0,
    "damageHitratePhysical": 1.0, "damageHitrateMagical": 1.0,
    "abilityRangeForwardExtend": 0.0, "defPenetrate": 0.0,
    "magicResistPenetrate": 0.0, "hpRecoveryPerSecByMaxHpRatio": 0.0,
    "defPenetrateFixed": 0.0, "oneMinusStatusResistance": 1.0,
    "magicResistPenetrateFixed": 0.0, "maxEp": 1000,
    "epRecoveryPerSec": 0.0, "spRecoverRatio": 1.0,
    "epBreakRecoverSpeed": 1.0, "slowDown": 1.0, "blockRadiusScale": 1.0,
    **{name: False for name in BOOL_ATTRIBUTES},
}

# Native ctor flags plus metadata v29 per-field constructor arguments.
# GetRangeAsTVector2 uses FP.MinValue/MaxValue when the bound flag is false.
_RANGE_SINGLE_VALUES = {
    "maxHp": (1.0, None), "atk": (0.0, None), "def": (0.0, None),
    "magicResistance": (0.0, 100.0), "cost": (0.0, None), "blockCnt": (0.0, None),
    "moveSpeed": (binary32(0.1), None), "attackSpeed": (20.0, None),
    "baseAttackTime": (0.0, None), "respawnTime": (0.0, None),
    "hpRecoveryPerSec": (0.0, None), "spRecoveryPerSec": (0.0, None),
    "maxDeployCount": (0.0, None), "maxDeckStackCnt": (0.0, None),
    "tauntLevel": (-2.0, 2.0), "massLevel": (None, None), "baseForceLevel": (None, None),
    "epDamageResistance": (0.0, 100.0), "epResistance": (0.0, 100.0),
    "damageHitratePhysical": (0.0, 1.0), "damageHitrateMagical": (0.0, 1.0),
    "abilityRangeForwardExtend": (None, None), "defPenetrate": (0.0, 1.0),
    "magicResistPenetrate": (0.0, 1.0), "hpRecoveryPerSecByMaxHpRatio": (0.0, 1.0),
    "defPenetrateFixed": (0.0, None), "oneMinusStatusResistance": (binary32(0.001), 1000.0),
    "magicResistPenetrateFixed": (0.0, None), "maxEp": (0.0, 1000.0),
    "epRecoveryPerSec": (0.0, None), "spRecoverRatio": (0.0, None),
    "epBreakRecoverSpeed": (0.0, None), "slowDown": (0.0, 1.0), "blockRadiusScale": (0.0, None),
}
ATTRIBUTE_RANGES = {
    name: (MIN_VALUE if lo is None else FP.from_float32(lo),
           MAX_VALUE if hi is None else FP.from_float32(hi))
    for name, (lo, hi) in _RANGE_SINGLE_VALUES.items()
}
_ENUM_NAMES = {"applyWay": ("NONE", "MELEE", "RANGED", "ALL"),
               "motion": ("WALK", "FLY", "E_NUM"),
               "levelType": ("NORMAL", "ELITE", "BOSS", "E_NUM")}


def _top_field_value(name: str, value: Any) -> Any:
    if name in _ENUM_NAMES:
        names = _ENUM_NAMES[name]
        if type(value) is int and 0 <= value < len(names):
            return names[value]
        if type(value) is str and value in names:
            return value
        raise UnverifiedEnemyData(f"{name}: unknown enum value {value!r}")
    if name in {"rangeRadius", "viewRadius"}:
        if type(value) not in (float, int) or not math.isfinite(value):
            raise DataError(f"{name}: expected finite Single")
        single = binary32(value)
        if not math.isfinite(single):
            raise DataError(f"{name}: not representable as finite Single")
        return single
    if name in {"lifePointReduce", "numOfExtraDrops"}:
        if type(value) is not int or not -(1 << 31) <= value < 1 << 31:
            raise DataError(f"{name}: expected signed int32")
    elif name == "notCountInTotal":
        if type(value) is not bool:
            raise DataError("notCountInTotal: expected Boolean")
    elif name == "enemyTags":
        if value is not None and (type(value) is not list or any(type(tag) is not str for tag in value)):
            raise DataError("enemyTags: expected String array or null")
    elif value is not None and type(value) is not str:
        raise DataError(f"{name}: expected String or null")
    return value


def _optional(value: Any, label: str) -> tuple[bool, Any]:
    if type(value) is not dict or type(value.get("m_defined")) is not bool:
        raise DataError(f"{label}: expected explicit Boolean m_defined wrapper")
    if not value["m_defined"]:
        # A placeholder value is not read by the native defined gate.
        return False, None
    if "m_value" not in value:
        raise UnverifiedEnemyData(f"{label}: defined optional lacks its serialized value")
    return True, deepcopy(value["m_value"])


def _attribute_value(name: str, value: Any) -> int | float | bool:
    if name in INT_ATTRIBUTES:
        if type(value) is not int or not -(1 << 31) <= value < 1 << 31:
            raise DataError(f"attributes.{name}: expected signed int32")
        return value
    if name in FLOAT_ATTRIBUTES:
        if type(value) not in (int, float) or not math.isfinite(value):
            raise DataError(f"attributes.{name}: expected finite number")
        result = binary32(value)
        if not math.isfinite(result):
            raise DataError(f"attributes.{name}: not representable as finite Single")
        return result
    if name in BOOL_ATTRIBUTES:
        if type(value) is not bool:
            raise DataError(f"attributes.{name}: expected Boolean")
        return value
    raise UnverifiedEnemyData(f"Unknown EnemyDatabase attribute: {name}")


@dataclass
class ResolvedEnemyData:
    enemy_id: str
    requested_level: int
    applied_levels: list[int] = field(default_factory=list)
    values: dict[str, Any] = field(default_factory=dict)
    attribute_values: dict[str, int | float | bool] = field(default_factory=dict)
    database_attribute_values: dict[str, int | float | bool] = field(default_factory=dict)
    unclamped_attributes: dict[str, FP] = field(default_factory=dict)
    attributes: dict[str, FP] = field(default_factory=dict)
    field_sources: dict[str, str] = field(default_factory=dict)
    collection_layers: list[dict] = field(default_factory=list)
    unresolved_defaults: set[str] = field(default_factory=set)
    unsupported_mechanisms: set[str] = field(default_factory=set)
    talent_blackboard: list[dict] = field(default_factory=list)
    skills: list[dict] = field(default_factory=list)
    sp_data: dict | None = None
    attribute_scope: str = "Reset raw FP values; dynamic battle effects and Lua overrides excluded"

    @property
    def numeric(self) -> dict[str, int | float]:
        """Decoded numeric AttributesData values, before Reset conversion/clamp."""
        return {name: self.attribute_values[name] for name in NUMERIC_ATTRIBUTES}

    def require_attributes(self, *names: str) -> dict[str, FP]:
        missing = [name for name in names if name not in self.attributes]
        if missing:
            raise UnverifiedEnemyData("Unresolved Reset FP attributes: " + ", ".join(missing))
        return {name: self.attributes[name] for name in names}


def clamp_attribute(name: str, value: FP) -> FP:
    if name not in ATTRIBUTE_RANGES or type(value) is not FP:
        raise UnverifiedEnemyData(f"No recovered numeric AttributeMeta range: {name}")
    lo, hi = ATTRIBUTE_RANGES[name]
    return FP(max(lo.raw, min(value.raw, hi.raw)))


def read_attribute(result: ResolvedEnemyData, name: str) -> float:
    """ReadAttributesField: numeric Obscured values become a Single."""
    if name not in NUMERIC_ATTRIBUTES or name not in result.attribute_values:
        raise UnverifiedEnemyData(f"Unsupported numeric AttributesData field: {name}")
    return binary32(result.attribute_values[name])


def write_attribute(result: ResolvedEnemyData, name: str, value: FP | float | int,
                    *, source: str = "modifier") -> None:
    """WriteAttributesField(FP/Single), including rounded signed-int32 writes.

    Range clamping is a separate caller action in ApplyChangesToAttributes.
    Call refresh_attributes after preprocessing to build the Reset FP view.
    """
    if name not in NUMERIC_ATTRIBUTES:
        raise UnverifiedEnemyData(f"Unsupported numeric AttributesData field: {name}")
    if type(value) is FP:
        single = value.as_float()
    elif type(value) in (float, int):
        single = binary32(value)
    else:
        raise DataError(f"{name}: expected FP or a finite numeric value")
    if not math.isfinite(single):
        raise UnverifiedEnemyData("Nonfinite WriteAttributesField input is outside this closure")
    if name in RUNTIME_INT_ATTRIBUTES:
        # Native double Round helper implements ties-to-even. The following
        # CVTTSD2SI uses signed 32-bit INT_MIN for an invalid masked conversion.
        rounded = round(single)
        decoded = rounded if -(1 << 31) <= rounded < (1 << 31) else -(1 << 31)
    else:
        decoded = single
    result.attribute_values[name] = decoded
    result.field_sources["attributes." + name] = source


def refresh_attributes(result: ResolvedEnemyData) -> None:
    """Attributes.Reset path; does not run _CalculateAttributeValue effects."""
    result.unclamped_attributes = {name: FP.from_float32(read_attribute(result, name))
                                   for name in NUMERIC_ATTRIBUTES}
    result.attributes = {name: clamp_attribute(name, value)
                         for name, value in result.unclamped_attributes.items()}


def _blackboard_pairs(pairs: Any, label: str) -> list[dict]:
    if type(pairs) is not list:
        raise DataError(f"{label}: expected Blackboard pair list")
    result = []
    for pair in pairs:
        if type(pair) is not dict or type(pair.get("key")) is not str:
            raise DataError(f"{label}: malformed Blackboard pair")
        string = pair.get("valueStr")
        if string is not None and type(string) is not str:
            raise DataError(f"{label}: valueStr must be String or null")
        if string:
            result.append({"key": pair["key"], "value": 0.0, "valueStr": string})
        else:
            value = pair.get("value", 0.0)
            if type(value) not in (int, float) or not math.isfinite(value):
                raise DataError(f"{label}: numeric Blackboard value must be finite")
            result.append({"key": pair["key"], "value": binary32(value)})
    return result


def _merge_blackboard(existing: list[dict], incoming: Any, label: str) -> list[dict]:
    result = deepcopy(existing)
    for pair in _blackboard_pairs(incoming, label):
        # Native List.RemoveAll(predicate key equality) then List.Add(pair).
        result = [old for old in result if old["key"] != pair["key"]]
        result.append(pair)
    return result


def _merge_skills(result: ResolvedEnemyData, incoming: Any, source: str) -> None:
    if type(incoming) is not list:
        raise DataError(f"{source}.skills: expected list")
    for skill in incoming:
        if type(skill) is not dict or type(skill.get("prefabKey")) is not str:
            raise DataError(f"{source}.skills: missing String prefabKey")
        existing = next((s for s in result.skills if s["prefabKey"] == skill["prefabKey"]), None)
        new = deepcopy(skill)
        board = skill.get("blackboard")
        if existing is not None and board:
            new["blackboard"] = _merge_blackboard(existing.get("blackboard") or [], board, source+".skills.blackboard")
        elif board is not None:
            new["blackboard"] = _blackboard_pairs(board, source+".skills.blackboard")
        result.skills = [s for s in result.skills if s["prefabKey"] != skill["prefabKey"]]
        result.skills.append(new)


def _apply_layer(result: ResolvedEnemyData, layer: Any, source: str) -> None:
    if type(layer) is not dict:
        raise DataError(f"{source}: expected enemyData object")
    unknown = set(layer) - OPTIONAL_FIELDS - COLLECTION_FIELDS - {"attributes"}
    if unknown:
        raise UnverifiedEnemyData(f"{source}: unrecognized enemyData fields {sorted(unknown)}")
    for name in OPTIONAL_FIELDS:
        if name not in layer:
            continue
        defined, value = _optional(layer[name], source + "." + name)
        if defined:
            target_name = "key" if name == "prefabKey" else name
            result.values[target_name] = _top_field_value(name, value)
            result.field_sources[target_name] = source
    attributes = layer.get("attributes")
    if attributes is not None:
        if type(attributes) is not dict:
            raise DataError(f"{source}.attributes: expected object")
        for name, wrapper in attributes.items():
            if name not in INT_ATTRIBUTES | FLOAT_ATTRIBUTES | BOOL_ATTRIBUTES:
                raise UnverifiedEnemyData(f"Unknown EnemyDatabase attribute: {name}")
            defined, value = _optional(wrapper, f"{source}.attributes.{name}")
            if defined:
                decoded = _attribute_value(name, value)
                if name in NUMERIC_ATTRIBUTES:
                    # _ConvertEnemyAttributes also passes DB int through a
                    # boxed ReadAttributesField Single and WriteAttributesField.
                    write_attribute(result, name, decoded, source=source)
                else:
                    result.attribute_values[name] = decoded
                result.field_sources["attributes." + name] = source
    collections = {name: deepcopy(layer[name]) for name in COLLECTION_FIELDS if name in layer and layer[name] is not None}
    if collections:
        # Preserve nonoptional layers even when every optional is undefined.
        result.collection_layers.append({"source": source, "values": collections})
        if "talentBlackboard" in collections:
            result.talent_blackboard = _merge_blackboard(result.talent_blackboard, collections["talentBlackboard"], source+".talentBlackboard")
        if "skills" in collections:
            _merge_skills(result, collections["skills"], source)
        if "spData" in collections:
            result.sp_data = deepcopy(collections["spData"])


def resolve_enemy_reference(reference: dict, database: dict) -> ResolvedEnemyData:
    """Resolve the ordinary native database path, before global preprocessing."""
    if type(reference) is not dict or reference.get("useDb") is not True:
        raise UnverifiedEnemyData("Only useDb=True EnemyData references are currently recovered")
    enemy_id = reference.get("id")
    level = reference.get("level")
    if type(enemy_id) is not str or not enemy_id:
        raise DataError("Enemy reference id must be a nonempty string")
    if type(level) is not int or not -(1 << 31) <= level < 1 << 31:
        raise DataError("Enemy reference level must be signed int32")
    enemies = database.get("enemies") if type(database) is dict else None
    if type(enemies) is not dict or enemy_id not in enemies:
        raise DataError(f"Enemy database id not found: {enemy_id}")
    entries = enemies[enemy_id]
    if type(entries) is not list or not entries:
        raise DataError(f"Enemy database has no levels: {enemy_id}")
    for entry in entries:
        if type(entry) is not dict or type(entry.get("level")) is not int:
            raise DataError(f"Malformed EnemyLevel: {enemy_id}")
    if level >= 0 and not any(entry["level"] == level for entry in entries):
        raise DataError(f"Exact enemy level not found: {enemy_id}/{level}")
    result = ResolvedEnemyData(enemy_id, level)
    result.attribute_values = deepcopy(DEFAULT_ATTRIBUTE_VALUES)
    result.values = {"name": None, "description": None, "key": None, "alias": enemy_id,
                     "applyWay": "MELEE", "motion": "WALK", "enemyTags": None, "notCountInTotal": False,
                     "lifePointReduce": 1, "rangeRadius": -1.0, "viewRadius": -1.0,
                     "numOfExtraDrops": 0, "levelType": "NORMAL"}
    result.field_sources = {"attributes."+name: "AttributesData.ctor" for name in result.attribute_values}
    selected = entries[:1] if level < 0 else entries
    for entry in selected:
        if level >= 0 and entry["level"] > level:
            break
        source = f"database:{enemy_id}:level:{entry['level']}"
        _apply_layer(result, entry.get("enemyData"), source)
        result.applied_levels.append(entry["level"])
    if reference.get("overwrittenData") is not None:
        _apply_layer(result, reference["overwrittenData"], "level:overwrittenData")
    result.database_attribute_values = deepcopy(result.attribute_values)
    refresh_attributes(result)
    return result


def resolve_enemy(database: dict, reference: dict) -> ResolvedEnemyData:
    """Database-first entry point used by battle creation preprocessing."""
    return resolve_enemy_reference(reference, database)

"""Bounded static preparation of the shipped default source-stone altar skill.

This translates selected native resource assignment branches. It does not
instantiate Unity objects, execute Character.Init, or infer scene owner flags.
"""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import math
import struct

from .data import read_json, sha256
from .fp import FP

INPUTS = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v7\skill_preparation\resource_inputs.json")
INPUTS_SHA256 = "28a7a63a3b02398e5d902f8cc25add8dffebfeb5c0ad804ce2b6c47af685ae2e"


class UnverifiedPreparation(ValueError):
    pass


def _require(condition, message):
    if not condition:
        raise UnverifiedPreparation(message)


def _float32(value, label):
    _require(type(value) in (int, float) and math.isfinite(value), f"{label}: finite number required")
    try:
        result = struct.unpack("<f", struct.pack("<f", value))[0]
    except (OverflowError, struct.error) as exc:
        raise UnverifiedPreparation(f"{label}: outside Single range") from exc
    _require(math.isfinite(result), f"{label}: outside Single range")
    return result


def prepare_specified_ability(*, pre_delay, cooldown, time_mode, animation_key,
                              animation_keys, wait_for_attack_event,
                              max_anim_scale, native_default_no_hotfix):
    """Actual SPECIFIED mode with no matching animation or timing override.

    AbstractAnimatedAbility.UpdatePlaybackSpeed(initial=0) initializes
    attackTime = get_cooldown() and animScale = 1. A failed animation lookup
    skips the entire scaling/maxAnimScale block, then preDelay is
    Min(attackTime, FP(float32(animScale * serializedPreDelay))). GetDuration
    returns attackTime, including when the skill table duration is zero.
    """
    _require(native_default_no_hotfix is True, "native default/null hotfix required")
    _require(type(time_mode) is int and time_mode == 2, "only SPECIFIED TimeMode=2 recovered here")
    _require(wait_for_attack_event is False, "attack-event waits are outside this preparation path")
    _require(isinstance(animation_key, str), "animation key required")
    _require(isinstance(animation_keys, (tuple, list)) and all(isinstance(k, str) for k in animation_keys),
             "explicit initialized animation keys required")
    _require(len(set(animation_keys)) == len(animation_keys), "duplicate animation dictionary keys")
    _require(animation_key not in animation_keys, "matching animation requires unrecovered clip/scaling preparation")
    pre = _float32(pre_delay, "preDelay")
    cd = _float32(cooldown, "cooldown")
    _float32(max_anim_scale, "maxAnimScale")  # Not applied when animation lookup fails.
    _require(pre >= 0 and cd >= 0, "negative specified times outside supported altar preparation")
    cooldown_fp = FP.from_float32(cd)
    pre_fp = FP.from_float32(_float32(_float32(1, "animScale") * pre, "scaledPreDelay"))
    _require(cooldown_fp.raw >= 0 and pre_fp.raw >= 0, "Single to FP conversion exceeds supported positive time range")
    return (pre_fp if pre_fp.raw < cooldown_fp.raw else cooldown_fp), cooldown_fp, cooldown_fp


@dataclass(frozen=True)
class PreparedAltarSkill:
    pre_delay: FP
    duration: FP
    cooldown: FP
    sp_cost: int
    init_sp: int
    sp_increment: FP
    sp_recovery_per_second: FP
    blackboard: dict[str, float]
    skill_id: str
    range_id: str
    provenance: dict
    remaining_external_context: tuple[str, ...]

    def as_dict(self):
        return {
            "skill_id": self.skill_id, "range_id": self.range_id,
            "pre_delay_raw": self.pre_delay.raw, "duration_raw": self.duration.raw,
            "cooldown_raw": self.cooldown.raw, "sp_cost": self.sp_cost, "init_sp": self.init_sp,
            "sp_increment_raw": self.sp_increment.raw,
            "sp_recovery_per_second_raw": self.sp_recovery_per_second.raw,
            "blackboard": dict(self.blackboard), "provenance": self.provenance,
            "remaining_external_context": list(self.remaining_external_context),
        }


def _component(prefabs, prefab_name, class_name):
    selected = [c for p in prefabs if p["name"] == prefab_name
                for c in p["rule_components"] if c["class_name"] == class_name]
    _require(len(selected) == 1, f"expected one actual {prefab_name}/{class_name}")
    c = selected[0]
    _require(c["assembly"] == "Assembly-CSharp.dll", "component assembly changed")
    return c


def prepare_altar_skill(dataset, *, resource_inputs_path=INPUTS,
                        native_default_no_hotfix: bool,
                        no_external_skill_modifier: bool) -> PreparedAltarSkill:
    """Prepare exact PHASE_0/level1/skill-level1 default altar declarations.

    External blackboards, delta/modifier data, changed prefabs and alternative
    modes must use a separately recovered path. Owner/coroutine/target/damage
    conditions remain caller declarations listed in the returned result.
    """
    _require(native_default_no_hotfix is True, "native default/null hotfix required")
    _require(no_external_skill_modifier is True, "external skill/attribute/modifier preparation unsupported")
    path = Path(resource_inputs_path)
    _require(sha256(path) == INPUTS_SHA256, "preparation resource snapshot changed")
    inputs = read_json(path)
    _require(inputs.get("format") == "altar_skill_preparation_inputs_v1", "preparation resource format changed")
    for source in inputs["sources"]:
        _require(sha256(Path(source["path"])) == source["sha256"], f"preparation source changed: {source['path']}")
    skill_bundle = dataset.tables["skills"]["skills"]["sktok_ore"]
    character = dataset.tables["characters"]["characters"]["trap_011_ore"]
    _require(skill_bundle == inputs["skill"], "altar skill table row changed")
    _require(character == inputs["character"], "altar character table row changed")
    predefines = [p for p in dataset.level["predefines"]["tokenInsts"]
                  if p["alias"] == "trap_011_ore#1"]
    _require(predefines == [inputs["predefine"]], "only exact visible altar predefine supported")
    predefine = predefines[0]
    _require(predefine["inst"] == {"characterKey": "trap_011_ore", "level": 1,
                 "phase": "PHASE_0", "favorPoint": 0, "potentialRank": 0}, "predefine attributes changed")
    _require(predefine["skillIndex"] == 0 and predefine["mainSkillLvl"] == 1
             and not predefine["skinId"] and not predefine["hidden"], "alternative skill/skin/hidden preparation unsupported")
    row = skill_bundle["levels"][0]
    _require(len(skill_bundle["levels"]) == 1 and row["prefabId"] == "sktok_ore"
             and row["skillType"] == "AUTO" and row["durationType"] == "NONE", "altar skill level changed")
    _require(row["spData"] == {"spType": "INCREASE_WITH_TIME", "maxChargeTime": 1,
                "spCost": 7, "initSp": 0, "increment": 1.0}, "unsupported SP preparation")
    _require(row["duration"] == 0.0 and row["blackboard"] == [{"key": "value", "value": 500.0}],
             "unsupported blackboard preparation")
    prefabs = inputs["prefabs"]
    ability = _component(prefabs, "sktok_ore", "Torappu.Battle.Abilities.AnimatedActionToTargetAbility")
    cast = _component(prefabs, "sktok_ore", "Torappu.Battle.CastSkill")
    trap = _component(prefabs, "trap_011_ore", "Torappu.Battle.Trap")
    mode = _component(prefabs, "trap_011_ore", "Torappu.Battle.TrapMode")
    animator = _component(prefabs, "trap_011_ore", "Torappu.Battle.MeshAnimator")
    af, cf, tf, mf = [c["fields"] for c in (ability, cast, trap, mode)]
    _require(tf["_animator"] == {"m_FileID": 0, "m_PathID": animator["path_id"]}, "altar animator reference changed")
    _require(mf["_animatorHooker"] == {"m_FileID": 0, "m_PathID": 0}, "default mode animation hooker unsupported")
    _require(cf["_trigger"] == {"m_FileID": 0, "m_PathID": 0}
             and cf["_availableValidator"] == {"m_FileID": 0, "m_PathID": 0}
             and cf["_extraAbilities"] == [] and cf["_writeDurationToAttackBlackboard"] == 0,
             "trigger/validator/extra ability/attack-blackboard preparation unsupported")
    _require(af["_timeMode"] == 2 and af["_cooldown"] == 1.0 and af["_preDelay"] == 0.6000000238418579
             and af["_animKey"] == "" and af["_waitForAttackEvent"] == 0
             and af["_maxAnimScale"] == -1.0 and af["_affectedBySlowDown"] == 0,
             "altar serialized preparation branch changed")
    keys = tuple(a["animKey"] for a in animator["fields"]["_animations"])
    _require(keys == ("Idle", "Born", "Die"), "animation dictionary input changed")
    # AbilityBehaviour discovery only includes components on this GameObject.
    same_object = [c["class_name"] for p in prefabs if p["name"] == "sktok_ore"
                   for c in p["rule_components"] if c["fields"]["m_GameObject"] == af["m_GameObject"]]
    _require(set(same_object) == {"Torappu.Battle.Abilities.UberEffectEmitter", "Torappu.Battle.AlwaysTrigger",
        "Torappu.Battle.CastSkill", "Torappu.Battle.Abilities.AnimatedActionToTargetAbility"},
        "ability GameObject rule component inventory changed")
    pre, duration, cooldown = prepare_specified_ability(pre_delay=af["_preDelay"], cooldown=af["_cooldown"],
        time_mode=af["_timeMode"], animation_key=af["_animKey"], animation_keys=keys,
        wait_for_attack_event=bool(af["_waitForAttackEvent"]), max_anim_scale=af["_maxAnimScale"],
        native_default_no_hotfix=native_default_no_hotfix)
    bb = {p["key"]: _float32(p["value"], "blackboard") for p in row["blackboard"]}
    # SkillData.InitIfNot: GE(duration,0) -> Assign("duration",duration).
    bb["duration"] = _float32(row["duration"], "skill duration")
    attrs = character["phases"][0]["attributesKeyFrames"][0]
    _require(attrs["level"] == 1 and attrs["data"]["spRecoveryPerSec"] == 1.0,
             "SP recovery attribute changed")
    return PreparedAltarSkill(pre, duration, cooldown, 7, 0, FP.from_float32(row["spData"]["increment"]),
        FP.from_float32(attrs["data"]["spRecoveryPerSec"]), bb, "sktok_ore", row["rangeId"],
        {"kind": "bounded static native preparation; no target execution", "resource_inputs": str(path.resolve()),
         "resource_inputs_sha256": sha256(path), "sources": inputs["sources"],
         "components": [{k: c[k] for k in ("class_name", "path_id", "script_path_id", "serialized_sha256")}
                        for c in (ability, cast, trap, mode, animator)],
         "native_chain": ["DataConvertUtil.GetSkillData(1827433b0)",
            "SkillDB.TryGetSkill/_TryGetSkill(18210a200/18210a350)",
            "SkillDataBundle.TryGetSkill(182529ce0)",
            "Character._AssignData/_PreprocessSkill(180a33dd0/180a37070)", "SkillData.InitIfNot(18252a520)",
            "Character._AssignSkill(180a344b0)",
            "BasicSkill.AssignData(1809582e0)", "Ability.SetData/DoSetData(1805d6bc0/1805d5540)",
            "Ability.Attach/DoAttach(1805d4ae0/1805d4f00)",
            "AbstractAnimatedAbility.DoAttach(180eff930)", "AbilityStandard.OnAttached(1805d07a0)",
            "DoUpdatePlaybackSpeed/Abstract.UpdatePlaybackSpeed(1805cff60/180f00820)",
            "get_cooldown(180f01050)/GetDuration(180effbe0)"],
         "table_duration_float32": bb["duration"], "actual_time_mode": "SPECIFIED=2",
         "initial_anim_scale_float32": 1.0, "animation_lookup": "empty key absent from Idle/Born/Die dictionary",
         "basic_skill_behaviour_count": 0, "ability_behaviour_count": 1,
         "ability_behaviour": "UberEffectEmitter inherits Behaviour.UpdatePlaybackSpeed(1805db9c0): out=1, return=false; no override",
         "range_radius_float32": -1.0,
         "blackboard_duration_origin": "SkillData.InitIfNot assigns duration=0; SPECIFIED mode does not read _cooldownKey",
         "availability": "initial cooldown timer ready under default Reset; owner/event/abnormal state still external"},
        ("Resource declarations are installed in the default mode; animation dictionary initialized from this prefab; no animation override.",
         "Native default methods with null hotfix slots, no extra blackboard/delta, potential/skin/global preparation modifiers.",
         "Owner exists and attachment/registration completed; no full Unity Init or loading process executed by this component.",
         "Owner validity, abnormal/dying/skill flags, event modifiers and skill admission remain explicit scene inputs.",
         "UberEffectEmitter's inherited timing override is recovered; visual initialization/effect emission is not executed.",
         "Deterministic shared coroutine branch, frame clock, physics target order and damage/lifecycle context remain separately declared."))

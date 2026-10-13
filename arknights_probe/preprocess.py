"""Independent static Rogue group selection; never infer live run RNG state.

Roguelike DoPreprocess 0x1808f8240, weighted helper 0x1845951b0,
Range(float) 0x181a96e30, MathUtil.LE 0x1866e56f0; getters
0x1808eb4c0 (int32 -> Single) / 0x1808eb4d0 (stored Single).
Group enumeration order and retain counts are mandatory external inputs.
"""
from __future__ import annotations

import copy
import math

from .data import Dataset, require
from .fp import binary32

EPSILON = binary32(1e-5)


def random_range_float(rng, minimum: float, maximum: float) -> float:
    minimum, maximum = binary32(minimum), binary32(maximum)
    sample = binary32(rng.next_double())
    width = binary32(maximum - minimum)
    return binary32(binary32(sample * width) + minimum)


def weighted_choice(items: list[dict], rng):
    """Native <=weight+float32(1e-5), one NextDouble even at total zero."""
    weights = []
    total = binary32(0)
    for item in items:
        weight = item["weight"]
        require(type(weight) in (int, float) and math.isfinite(weight) and weight >= 0, "Weight must be finite and nonnegative")
        weight = binary32(weight)
        weights.append(weight)
        total = binary32(total + weight)
    require(math.isfinite(total), "Weight sum overflow")
    draw = random_range_float(rng, 0, total)
    for item, weight in zip(items, weights):
        if draw <= binary32(weight + EPSILON):
            return item
        draw = binary32(draw - weight)
    return items[-1] if items else None


def rogue_preprocess(dataset: Dataset, *, rng, topic_id: str, mimic_count: int,
                     gold_count: int, group_order: list[str], input_source: str) -> dict:
    """Return original actionIndex choices for this map's Rogue groups.

    RNG object is supplied independently (e.g. LegacyRandom). This reproduces
    the static local algorithm using the explicit order, not current client
    seed initialization or total game-wide RNG consumption. General/pack-group
    preprocessing and non-ALWAYS declarations deliberately fail closed.
    """
    require(type(mimic_count) is int and -(1 << 31) <= mimic_count < (1 << 31), "mimic_count must be signed int32")
    require(type(gold_count) is int and -(1 << 31) <= gold_count < (1 << 31), "gold_count must be signed int32")
    require(isinstance(input_source, str) and bool(input_source), "Preprocess inputs need a source")
    detail = dataset.tables.get("topics", {}).get("details", {}).get(topic_id)
    require(isinstance(detail, dict) and isinstance(detail.get("gameConst"), dict), "Topic gameConst missing")
    const = detail["gameConst"]
    mimics, gold_key = set(const["mimicEnemyIds"]), const["goldChestTrapId"]
    aliases = {x["alias"]: x["inst"]["characterKey"] for x in dataset.level.get("predefines", {}).get("tokenInsts", [])}
    groups = {}
    for wi, wave in enumerate(dataset.level["waves"]):
        for fi, fragment in enumerate(wave["fragments"]):
            for ai, action in enumerate(fragment["actions"]):
                key = action.get("randomSpawnGroupKey")
                if not key:
                    continue
                require(not action.get("randomSpawnGroupPackKey"), "General packed groups not supported")
                require(action.get("randomType") == action.get("refreshType") == "ALWAYS", "Non-ALWAYS preprocessing not restored")
                require(action["actionType"] in {"SPAWN", "ACTIVATE_PREDEFINED", "EMPTY"}, "Unsupported Rogue grouped action")
                require(key not in groups or groups[key][0] == (wi, fi), "Qualify repeated group keys before preprocessing")
                candidates = groups.setdefault(key, ((wi, fi), []))[1]
                candidates.append({"actionIndex": ai, "weight": action["weight"], "action": copy.deepcopy(action),
                                   "mimic": action["actionType"] == "SPAWN" and action["key"] in mimics,
                                   "gold": action["actionType"] == "ACTIVATE_PREDEFINED" and aliases.get(action["key"]) == gold_key})
    require(isinstance(group_order, list) and len(group_order) == len(groups) and set(group_order) == set(groups), "Provide every group exactly once in explicit group_order")
    selected_mimic, selected_gold, draws = set(), set(), 0
    preserve = mimic_count >= 0 and gold_count >= 0

    def select_special(flag, count):
        nonlocal draws
        special = []
        for key in group_order:
            total = binary32(0)
            found = False
            for candidate in groups[key][1]:
                if candidate[flag]:
                    found = True
                    total = binary32(total + binary32(candidate["weight"]))
            if found:
                special.append({"key": key, "weight": total})
        selected = set()
        for _ in range(min(count, len(special))):
            chosen = weighted_choice(special, rng)
            draws += 1
            selected.add(chosen["key"])
            special.remove(chosen)
        return selected

    if preserve:
        selected_mimic = select_special("mimic", mimic_count)
        selected_gold = select_special("gold", gold_count)
    choices, candidate_report = {}, {}
    for key in group_order:
        eligible = []
        for candidate in groups[key][1]:
            keep = True
            action = candidate["action"]
            if preserve and action["actionType"] == "SPAWN":
                keep = ((candidate["mimic"] and key in selected_mimic) or
                        (not candidate["mimic"] and key not in selected_mimic and key not in selected_gold))
            elif preserve and action["actionType"] == "ACTIVATE_PREDEFINED":
                keep = ((candidate["gold"] and key in selected_gold) or
                        (not candidate["gold"] and key not in selected_mimic and key not in selected_gold))
            if keep:
                eligible.append(candidate)
        candidate_report[key] = [x["actionIndex"] for x in eligible]
        if eligible:
            chosen = weighted_choice(eligible, rng)
            draws += 1
            choices[key] = chosen["actionIndex"]
        else:
            choices[key] = None  # No implicit first candidate or random draw.
    return {"scope": "independent_static_rogue_preprocessor_with_explicit_order_and_retain_inputs",
            "group_selections": choices, "group_order": list(group_order),
            "preserve_mode": preserve, "mimic_count": mimic_count, "gold_count": gold_count,
            "selected_mimic_groups": sorted(selected_mimic), "selected_gold_groups": sorted(selected_gold),
            "eligible_original_indices": candidate_report, "next_double_calls": draws,
            "input_source": input_source, "topic_id": topic_id,
            "client_run_seed_validated": False, "client_rng_consumption_validated": False,
            "client_runtime_compared": False, "battle_ready": False}

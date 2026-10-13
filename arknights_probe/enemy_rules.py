"""Selected static enemy attribute operations, separate from rune selection.

This composes the recovered FP multiply/clamp/write operation. The caller must
identify the selected modifiers: Rune.Verify, a live Rogue run's modifiers and
hotfix dispatch are not inferred from a difficulty label by this component.
"""
from __future__ import annotations

from copy import deepcopy
import math

from .data import require
from .fp import FP, binary32


ATTRIBUTE_MUL_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "EAttribuesMul.DoPreprocessEnemy": "0x180cf84c0",
    "Rune.ApplyChangesToAttributesMul": "0x180ce87f0",
    "multiply_delegate": "0x180cf1990",
    "client_runtime_compared": False,
    "selector_restored": False,
}


def apply_selected_attribute_mul(enemy, multipliers: dict[str, float], *, source: str):
    """Return a copy with explicit field-name multipliers applied.

    Inputs are runtime attribute names, not a declaration of all active runes.
    Native ReadAttributesField returns Single even for integer fields. The
    product is clamped in FP, then written through Single and the native field
    conversion, and finally refreshed using Battle.Attributes.Reset semantics.
    """
    # Import at use time so the data reader can be used independently.
    from .enemy_data import (NUMERIC_ATTRIBUTES, clamp_attribute,
                             read_attribute, refresh_attributes, write_attribute)
    require(type(multipliers) is dict, "Selected multipliers must be a dictionary")
    require(type(source) is str and bool(source.strip()), "Selected multipliers require a source")
    result = deepcopy(enemy)
    for name, multiplier in multipliers.items():
        require(name in NUMERIC_ATTRIBUTES, f"Unknown numeric attribute {name!r}")
        require(type(multiplier) in (int, float) and math.isfinite(multiplier),
                f"{name}: multiplier must be finite")
        multiplier = binary32(multiplier)
        require(math.isfinite(multiplier), f"{name}: multiplier overflows Single")
        left = FP.from_float32(read_attribute(result, name))
        right = FP.from_float32(multiplier)
        write_attribute(result, name, clamp_attribute(name, left * right))
        result.field_sources["attributes." + name] = source
    refresh_attributes(result)
    return result


def enemy_profile(enemy) -> dict:
    """Reviewable decoded primitives and pre-entity-modifier FP values."""
    return {
        "id": enemy.enemy_id,
        "requested_level": enemy.requested_level,
        "applied_levels": list(enemy.applied_levels),
        "values": deepcopy(enemy.values),
        "attribute_values": deepcopy(enemy.attribute_values),
        "database_attribute_values": deepcopy(enemy.database_attribute_values),
        "unclamped_attributes_fp_raw": {name: value.raw for name, value in enemy.unclamped_attributes.items()},
        "attributes_fp_raw": {name: value.raw for name, value in enemy.attributes.items()},
        "field_sources": deepcopy(enemy.field_sources),
        "talent_blackboard": deepcopy(enemy.talent_blackboard),
        "skills": deepcopy(enemy.skills),
        "sp_data": deepcopy(enemy.sp_data),
        "unresolved_defaults": sorted(enemy.unresolved_defaults),
        "unsupported_mechanisms": sorted(enemy.unsupported_mechanisms),
        "scope": "decoded_database_and_explicit_selected_attribute_operations",
        "effective_entity_modifiers_applied": False,
        "battle_ready": False,
    }

"""Derive scheduler inputs from enemy data and shipped prefab fields.

Creation eligibility remains an explicit fixture: a Unity prefab's existence
does not prove that CreateEnemy/Init/state-machine transitions succeed live.
"""
from __future__ import annotations

import math
import struct

from .data import require
from .enemy_data import resolve_enemy
from .fp import binary32


def derive_enemy_runtime(dataset, prefab_inputs: dict, *, counted_creation: dict[str, bool], source: str) -> dict:
    require(type(source) is str and bool(source.strip()), "Creation fixture requires a source")
    require(type(prefab_inputs) is dict and prefab_inputs.get("format") == "native_v4_prefab_inputs_v1",
            "Unsupported prefab evidence format")
    require(type(counted_creation) is dict and set(counted_creation) == set(dataset.enemy_refs),
            "Supply explicit counted-creation eligibility for exactly all enemy references")
    prefabs = prefab_inputs.get("enemies")
    require(type(prefabs) is dict, "Missing enemy prefab evidence")
    runtime = {}
    for key, reference in dataset.enemy_refs.items():
        require(key in prefabs, f"{key}: missing prefab evidence")
        prefab = prefabs[key]
        require(type(prefab) is dict, f"{key}: prefab evidence must be an object")
        require(prefab.get("only_delay_on_start_tile") is False,
                f"{key}: tile-dependent delay getter branch is not recovered")
        delay = prefab.get("delay_to_born_float32")
        require(type(delay) in (float, int) and math.isfinite(delay) and delay >= 0,
                f"{key}: delay must be finite and nonnegative")
        delay = binary32(delay)
        require(math.isfinite(delay), f"{key}: delay overflows Single")
        bits = struct.unpack("<I", struct.pack("<f", delay))[0]
        require(type(prefab.get("delay_to_born_bits")) is str and bits == int(prefab["delay_to_born_bits"], 16),
                f"{key}: prefab Single bits mismatch")
        enemy = resolve_enemy(dataset.tables["enemies"], reference)
        not_counted = enemy.values.get("notCountInTotal")
        require(type(not_counted) is bool, f"{key}: unresolved notCountInTotal")
        require(type(counted_creation[key]) is bool, f"{key}: counted creation fixture must be Boolean")
        runtime[key] = {"extraSpawnDelay": delay, "notCountInTotal": not_counted,
                        "successfulCountedCreation": counted_creation[key]}
    return {
        "enemy_runtime": runtime,
        "source": source,
        "derived": ["extraSpawnDelay_from_prefab_get_delayToBorn", "notCountInTotal_from_EnemyDB_TryGet"],
        "external": ["post_Init_counted_creation_eligibility", "native_hotfix_overrides_absent"],
        "creation_runtime_validated": False,
        "battle_ready": False,
    }

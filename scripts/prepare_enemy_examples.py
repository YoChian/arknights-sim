"""Refresh review examples after deliberately reviewing enemy evidence."""
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.data import Dataset, read_json
from arknights_probe.enemy_creation_inputs import derive_enemy_runtime
from arknights_probe.enemy_data import resolve_enemy
from arknights_probe.enemy_rules import apply_selected_attribute_mul, enemy_profile
from arknights_probe.prepare import DEFAULT_MANIFEST


def save(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf8")


def main():
    data = Dataset.from_manifest(DEFAULT_MANIFEST)
    prefabs = read_json(Path(r"D:\Repo\.rea-tools\arknights-pc\native_v4\resources\prefab_inputs.json"))
    runtime = derive_enemy_runtime(data, prefabs,
        counted_creation={key: True for key in data.enemy_refs},
        source="native_EnemyDB_TryGet_and_shipped_prefab_delay; external_post_Init_alive_creation_fixture_true; native_hotfix_overrides_absent")
    save(ROOT / "artifacts/enemy_creation_inputs.json", runtime)
    for mode in ("normal", "four_star"):
        fixture = read_json(ROOT / f"examples/timeline_{mode}_external.json")
        fixture["enemy_runtime"] = runtime["enemy_runtime"]
        fixture["input_source"] = runtime["source"] + "; external_original_group_indices_t1=0_t2=5_c1=4"
        save(ROOT / f"examples/timeline_{mode}_resolved.json", fixture)
    original = [enemy_profile(resolve_enemy(data.tables["enemies"], ref)) for ref in data.enemy_refs.values()]
    operation = read_json(ROOT / "examples/enemy_attribute_mul_selected.json")
    changed = [enemy_profile(apply_selected_attribute_mul(resolve_enemy(data.tables["enemies"], ref),
        operation["multipliers"], source=operation["source"])) for ref in data.enemy_refs.values()]
    save(ROOT / "artifacts/enemies_resolved.json", {"scope": "static_EnemyDB_defaults_and_ref_overwrite", "enemies": original, "battle_ready": False})
    save(ROOT / "artifacts/enemies_selected_mul.json", {"scope": "explicit_selected_attribute_mul_operation", "selected_operations": operation, "enemies": changed, "battle_ready": False})
    print(json.dumps({"enemy_references": len(original), "delay_one_second": [k for k, v in runtime["enemy_runtime"].items() if v["extraSpawnDelay"] == 1], "created_examples": 2}))


if __name__ == "__main__":
    main()

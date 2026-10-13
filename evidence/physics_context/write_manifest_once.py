"""Freeze explicitly reviewed new evidence; old v6 hashes are never refreshed."""
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
ANALYSIS = Path(r"D:\Repo\.rea-tools\arknights-pc")
PHYSICS = ANALYSIS / "native_v8" / "physics_context"


def read(path):
    return json.loads(path.read_text("utf-8"))


def sha(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def main():
    output = HERE / "native_evidence.json"
    if output.exists():
        raise SystemExit("Reviewed manifest already exists; do not automatically replace pins.")
    comparison = read(HERE / "reference_comparison.json")
    if comparison["all_passed"] is not True or comparison["tests_run"] != 25:
        raise ValueError("The reviewed 25 bounded checks must pass before freezing.")
    entries = {}

    def pin(path, expected=None):
        path = Path(path).resolve()
        digest = sha(path)
        if expected is not None and digest != expected:
            raise ValueError(f"Existing source pin changed; explicit review required: {path}")
        key = str(path).casefold()
        previous = entries.get(key)
        if previous and previous["sha256"] != digest:
            raise ValueError(f"Conflicting source pin: {path}")
        entries[key] = {"path": str(path), "sha256": digest}

    old_path = ROOT / "evidence" / "targeting" / "native_evidence.json"
    old = read(old_path)
    for entry in old["files"]:
        pin(entry["path"], entry["sha256"])
    pin(old_path)
    for relative in (
        "arknights_probe/physics_context.py", "tests/test_physics_context.py",
        "tests/test_physics_context_reference.py",
    ):
        pin(ROOT / relative)
    for name in (
        "PhysicsContextReference.cs", "PhysicsContextReference.exe",
        "generate_reference_input.py", "reference_input.json", "reference_vectors.json",
        "check_reference.py", "reference_comparison.json", "REPORT.md",
        "verify_evidence.py", "write_manifest_once.py",
    ):
        pin(HERE / name)
    # Every file in this owned directory is a completed, reviewed artifact.
    for path in sorted(PHYSICS.iterdir()):
        if path.is_file():
            pin(path)
    for batch in (1, 2):
        for kind in ("results", "raw", "input"):
            pin(ANALYSIS / "native_v8" / "core" / f"{kind}_round{batch}.json")
    for name in ("prepare.py", "ArknightsFocused.java"):
        pin(ANALYSIS / "native_v8" / "core" / name)

    prefabs = read(PHYSICS / "prefab_physics_inputs.json")
    for entry in prefabs["input_pins"]:
        pin(entry["path"], entry["sha256"])
    for prefab in prefabs["prefabs"]:
        entry = prefab["source_pin"]
        pin(entry["path"], entry["sha256"])
    inventory = read(PHYSICS / "engine_inventory.json")
    for entry in (inventory["engine"]["source_pin"],
                  inventory["game_assembly"]["source_pin"], inventory["settings_source_pin"]):
        pin(entry["path"], entry["sha256"])
    fields = read(PHYSICS / "native_fields.json")
    pin(fields["registration_reference_path"], fields["registration_reference_sha256"])
    pin(fields["helper_source_path"], fields["helper_source_sha256"])
    for entry in fields["method_map_sources"]:
        pin(entry["path"], entry["sha256"])
    static = read(PHYSICS / "static_inputs.json")
    pin(static["decoder_source_path"], static["decoder_source_sha256"])
    raw = read(PHYSICS / "raw_helpers.json")
    pin(raw["source_helper_path"], raw["source_helper_sha256"])
    reused = read(PHYSICS / "reused_native.json")
    for entry in reused["functions"]:
        pin(entry["source_report_path"], entry["source_report_sha256"])

    selections = read(PHYSICS / "selection.json") + read(PHYSICS / "selection_extra.json")
    selected = {entry["address"].lower() for entry in selections}
    functions = [function for batch in (1, 2) for function in
                 read(ANALYSIS / "native_v8" / "core" / f"results_round{batch}.json")["functions"]]
    recovered = [function for function in functions if function["address"].lower() in selected]
    if len(recovered) != len(selected):
        raise ValueError("Every physics selection must have one completed native result.")
    counts = dict(comparison["counts"])
    counts.update({
        "tests_run": comparison["tests_run"],
        "preserved_v6_file_pins": len(old["files"]),
        "physics_selected_addresses": len(selected),
        "physics_recovered_functions": len(recovered),
        "short_raw_helpers": len(raw["functions"]),
        "reused_native_functions": len(reused["functions"]),
        "metadata_types": len(fields["types"]),
        "metadata_fields": sum(len(row["fields"]) for row in fields["types"]),
        "generic_instances": len(fields["generic_instances"]),
        "prefabs": len(prefabs["prefabs"]),
        "prefab_nodes": sum(len(row["nodes"]) for row in prefabs["prefabs"]),
        "prefab_colliders": sum(len(row["colliders"]) for row in prefabs["prefabs"]),
        "prefab_rigidbodies": sum(len(row["rigidbodies"]) for row in prefabs["prefabs"]),
        "unresolved_prefab_references": sum(len(row["unresolved_references"]) for row in prefabs["prefabs"]),
    })
    manifest = {
        "manifest_version": 1,
        "scope": "static prefab physics declarations and native binary32 query arguments/phase subsequence; explicit external Unity bounds/pose/filter/hit receipts; independent C# scalar translation comparison",
        "target_sha256": fields["target_sha256"],
        "metadata_sha256": fields["metadata_sha256"],
        "reference_scope": comparison["scope"],
        "arithmetic_scope": "finite normal-or-zero binary32 intermediates, nearest-even assumption; live MXCSR/FTZ/DAZ not validated",
        "native_query_arguments_reconstructed": True,
        "physics_context_component_available": True,
        "physics_overlap_generated": False,
        "filter_consistency_generated": False,
        "world_bounds_generated": False,
        "engine_sync_generated": False,
        "engine_registration_pairing_proven": False,
        "runtime_battle_validated": False,
        "client_runtime_compared": False,
        "hotfix_runtime_compared": False,
        "battle_ready": False,
        "counts": counts,
        "files": list(entries.values()),
    }
    with output.open("x", encoding="utf-8") as stream:
        json.dump(manifest, stream, ensure_ascii=False, indent=2)
        stream.write("\n")
    print(json.dumps({"manifest": str(output), "files": len(entries), "counts": counts}, indent=2))


if __name__ == "__main__":
    main()

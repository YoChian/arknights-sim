"""One-time reviewed v7 targeting freeze. Refuses to replace existing pins.

This is a record of the explicit initial file selection, not an update tool.
Future drift must be reviewed instead of running this against new file contents.
"""
from pathlib import Path
import hashlib
import json


OUT = Path(__file__).resolve().parent
PROJECT = OUT.parents[1]
ANALYSIS = PROJECT.parent / ".rea-tools" / "arknights-pc"
TARGET = ANALYSIS / "native_v7" / "targeting"
DEST = OUT / "native_evidence.json"


def digest(path):
    with path.open("rb") as source:
        return hashlib.file_digest(source, "sha256").hexdigest()


def freeze():
    if DEST.exists():
        raise FileExistsError("Reviewed manifest already exists; do not automatically repin.")
    previous = PROJECT / "evidence" / "targeting" / "native_evidence.json"
    reused = json.loads(previous.read_text("utf-8"))
    files = {str(Path(x["path"]).resolve()): dict(x) for x in reused["files"]}
    for path, entry in files.items():
        if digest(Path(path)) != entry["sha256"]:
            raise ValueError(f"Existing v6 pin changed before freeze: {path}")
    paths = [previous, PROJECT / "arknights_probe" / "targeting_runtime.py",
             PROJECT / "tests" / "test_targeting_runtime.py",
             PROJECT / "tests" / "test_targeting_runtime_reference.py",
             PROJECT / "evidence" / "fp" / "FPReference.cs",
             ANALYSIS / "native_v5" / "devices" / "raw_helpers.json",
             ANALYSIS / "native_v5" / "resources" / "rule_prefab_subtrees.json",
             ANALYSIS / "native_v7" / "skill_preparation" / "tag_manager_inputs.json",
             ANALYSIS / "native_v7" / "core" / "reused_round2.json"]
    paths += [OUT / name for name in (
        "TargetingRuntimeReference.cs", "TargetingRuntimeReference.exe",
        "generate_reference_input.py", "reference_input.json", "reference_vectors.json",
        "reference_comparison.json", "REPORT.md", "verify_evidence.py", "write_manifest_once.py")]
    paths += [TARGET / name for name in (
        "selection.json", "selection_extra.json", "selection_flags.json", "prepare_selection.py",
        "export_native_fields.py", "native_fields.json", "field_offsets.json",
        "inspect_generic_identities.py", "generic_identities.json",
        "inspect_generic_dispatch.py", "generic_dispatch.json",
        "inspect_short_helpers.py", "raw_helpers.json", "extract_constants.py", "constants.json",
        "REPORT.md", "NOTES.md")]
    selected = [entry for name in ("selection.json", "selection_extra.json", "selection_flags.json")
                for entry in json.loads((TARGET / name).read_text("utf-8"))]
    selected_addresses = {x["address"] for x in selected}
    reports = []
    for number in (2, 3, 4):
        report_path = ANALYSIS / "native_v7" / "core" / f"results_round{number}.json"
        report = json.loads(report_path.read_text("utf-8"))
        functions = report["functions"]
        assert all(x["decompile_completed"] and x["imported_memory_matches_source"] for x in functions)
        requested = [x for x in functions if x["address"] in selected_addresses]
        paths += [report_path, report_path.parent / f"raw_round{number}.json"]
        # These batches preserve full pseudocode in JSON, not separate C files.
        assert all(isinstance(x["pseudocode"], str) and x["pseudocode"] for x in requested)
        reports.append({"path": str(report_path), "shared_functions": len(functions),
                        "shared_ranges": sum(len(x["ranges"]) for x in functions),
                        "all_imported_ranges_match": True,
                        "targeting_requested_addresses": [x["address"] for x in requested],
                        "count_scope": "Shared batch totals; targeting addresses listed separately"})
    for path in paths:
        path = path.resolve()
        files[str(path)] = {"path": str(path), "sha256": digest(path)}
    constants = json.loads((TARGET / "constants.json").read_text("utf-8"))
    raw = json.loads((TARGET / "raw_helpers.json").read_text("utf-8"))
    vectors = json.loads((OUT / "reference_vectors.json").read_text("utf-8"))
    manifest = {
        "manifest_version": 1,
        "scope": "ordinary native altar logical inputs/status/HitRange aggregation and ALL PriorityQueue; external Unity Physics2D and frozen runtime field/provider snapshots; independent C# comparisons",
        "target_sha256": constants["target_sha256"], "metadata_sha256": constants["metadata_sha256"],
        "runtime_battle_validated": False, "client_runtime_compared": False,
        "hotfix_runtime_compared": False, "battle_ready": False,
        "physics_overlap_generated": False, "native_masks_derived": True,
        "native_all_order_generated": True, "native_all_membership_rule_reconstructed": True,
        "reference_scope": "source-owned separate C# native-rule translation, shared validated FP division; not a native/client oracle",
        "counts": {"component_tests": 21, "reference_tests": 4,
                   "comparator_pairs": len(vectors["comparisons"]), "queue_cases": len(vectors["queues"]),
                   "queue_output_identities": sum(len(x["order"]) for x in vectors["queues"]),
                   "status_cases": len(vectors["statuses"]), "side_mask_cases": len(vectors["masks"]),
                   "targeting_selected_addresses": len(selected_addresses),
                   "short_raw_helpers": len(raw["functions"])},
        "selected_entries": selected, "native_reports": reports,
        "reused_manifest": str(previous),
        "reuse_policy": "The v6 manifest and all its existing pins were verified and retained; no old file was repinned.",
        "review_policy": "Fixed reviewed hashes; no automatic refresh on drift.",
        "remaining_gaps": ["Unity collider/transform/Physics2D query geometry, membership and order",
                           "live layer overrides/hotfix/static engine state",
                           "dynamic abnormal counts and actual provider algorithms/registration",
                           "runtime createdTime/mapLayer field provenance and mutable callbacks",
                           "sandbox secondary weight transformation"],
        "files": list(files.values())}
    with DEST.open("x", encoding="utf-8") as target:
        json.dump(manifest, target, ensure_ascii=False, indent=2)
    return {"path": str(DEST), "files": len(files), "counts": manifest["counts"]}


if __name__ == "__main__":
    print(json.dumps(freeze(), indent=2))

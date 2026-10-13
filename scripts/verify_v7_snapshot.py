"""Verify previous components and reviewed v7 evidence, then run the new probe."""
import contextlib
import io
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import verify_snapshot as previous
from arknights_probe import Dataset
from arknights_probe.altar_prepared import PreparedAltarProbe
from arknights_probe.data import read_json, require
from arknights_probe.v7_validation import verify_v7_evidence


def main():
    artifacts = ROOT / "artifacts"
    output = io.StringIO()
    with contextlib.redirect_stdout(output):
        previous_status = previous.main()
    (artifacts / "verification_v7_previous_console.txt").write_text(output.getvalue(), encoding="utf-8")
    require(previous_status == 0, "Previous component verification failed")
    base = read_json(artifacts / "verification.json")
    evidence = verify_v7_evidence()
    probe = PreparedAltarProbe(Dataset.from_manifest(ROOT / "data/manifest.json"))
    final = probe.step(10000)
    artifact = probe.artifact()
    trace_path = artifacts / "altar_component_prepared.json"
    trace_path.write_text(json.dumps(artifact, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    report = {
        "healthy": base["healthy"] and evidence["healthy"],
        "tests_run": base["tests_run"], "failures": base["failures"],
        "errors": base["errors"], "skipped": base["skipped"],
        "source_hashes_verified": base["source_hashes_verified"],
        "previous_verification": str(artifacts / "verification.json"),
        "v7_component_evidence": evidence,
        "prepared_altar_component": {
            "snapshot": final,
            "damage_applications": sum(d["applied"] for d in probe.damage_results),
            "first_damage_frame": probe.damage_results[0]["frame"] if probe.damage_results else None,
            "preparation": artifact["preparation"],
            "selection_inputs": artifact["selection_inputs"],
            "external_inputs": artifact["external_inputs"],
            "artifact": str(trace_path),
        },
        "scope": "static_preparation_and_targeting_with_external_physics_single_actor_composition",
        "battle_ready": False, "autonomous_route_ready": False, "runtime_battle_validated": False,
    }
    path = artifacts / "verification_v7.json"
    path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "healthy": report["healthy"], "tests_run": report["tests_run"],
        "file_pins_checked": evidence["file_pins_checked"],
        "native_selected_entries": evidence["native_selected_entries"],
        "native_ranges_checked": evidence["original_native_ranges_checked"],
        "prepared_altar_snapshot": final, "report": str(path),
    }, ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

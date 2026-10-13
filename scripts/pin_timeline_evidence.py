"""Explicitly pin the reviewed static reports; verification never refreshes pins."""
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT.parent / ".rea-tools" / "arknights-pc" / "native_v3"
REPORTS = [*(f"timeline/results_round{i}.json" for i in range(2, 7)),
           "timeline/weight_getter_disassembly.json", "fixedpoint/scheduler_field_offsets.json",
           "fixedpoint/clock_summary.json", "fixedpoint/time_manager_default.json",
           "sorting/results_round1.json", "sorting/results_round2.json"]


def main():
    files = []
    for name in REPORTS:
        path = SOURCE / name
        data = path.read_bytes()
        files.append({"path": str(path), "bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()})
    target = json.loads((SOURCE / REPORTS[0]).read_text("utf-8"))["target_sha256"]
    ledger = {"target_sha256": target, "scope": "static_native_components_no_client_runtime_or_hotfix_oracle", "files": files}
    destination = ROOT / "evidence/timeline/provenance.json"
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(json.dumps(ledger, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"ledger": str(destination), "files_pinned": len(files)}))


if __name__ == "__main__":
    main()

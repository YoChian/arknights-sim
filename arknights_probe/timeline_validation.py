"""Verify selected static evidence snapshots, separate from runtime fidelity."""
from pathlib import Path

from .data import read_json, require, sha256

LEDGER = Path(__file__).resolve().parents[1] / "evidence" / "timeline" / "provenance.json"


def verify_timeline_evidence() -> dict:
    ledger = read_json(LEDGER)
    files = ledger["files"]
    require(bool(files), "Timeline evidence ledger is empty")
    for spec in files:
        path = Path(spec["path"])
        require(path.is_file(), f"Missing static timeline evidence {path}")
        require(sha256(path) == spec["sha256"], f"Changed static timeline evidence {path}")
    return {"healthy": True, "scope": "hash_pinned_static_native_and_serialized_clock_evidence",
            "target_sha256": ledger["target_sha256"], "files_checked": len(files),
            "ledger_sha256": sha256(LEDGER), "files": files,
            "client_runtime_compared": False, "live_fixed_delta_validated": False}

"""Check reviewed movement evidence pins; this is not a live-game check."""
from pathlib import Path

from .data import read_json, require, sha256

DIRECTORY = Path(__file__).resolve().parents[1] / "evidence/movement"


def verify_movement_evidence():
    evidence = read_json(DIRECTORY / "native_evidence.json")
    require(evidence.get("files"), "Empty movement evidence ledger")
    for entry in evidence["files"]:
        path = Path(entry["path"])
        if not path.is_absolute():
            require(path.name == str(path), "Movement reference must be a local filename")
            path = DIRECTORY / path
        require(path.is_file() and sha256(path) == entry["sha256"], f"Changed or missing movement evidence: {path}")
    return {"healthy": True, "files_checked": len(evidence["files"]),
            "ledger_sha256": sha256(DIRECTORY / "native_evidence.json"),
            "reference_scope": evidence["reference_scope"], "reference_counts": evidence["counts"],
            "client_runtime_compared": False, "autonomous_route_ready": False, "battle_ready": False}

"""Read-only checks of reviewed v7 files and exact original native ranges."""
from pathlib import Path
import hashlib

from .data import read_json, require, sha256
from .v6_validation import verify_v6_evidence

ROOT = Path(__file__).resolve().parents[1]


def verify_v7_evidence(*, check_native_bytes=True):
    """Keep prior evidence immutable; verify new sources independently."""
    previous = verify_v6_evidence(check_native_bytes=check_native_bytes)
    manifest = read_json(ROOT / "evidence/v7/manifest.json")
    for item in manifest["files"]:
        path = Path(item["path"])
        require(path.is_file(), f"Missing v7 evidence: {path}")
        require(sha256(path) == item["sha256"], f"V7 evidence changed: {path}")
    addresses, ranges, batches = set(), [], []
    for item in manifest["native_batches"]:
        data = read_json(Path(item["path"]))
        functions = data["functions"]
        require(len(functions) == item["entries"], "V7 batch size changed")
        for function in functions:
            require(function["decompile_completed"] and function["imported_memory_matches_source"],
                    f"Incomplete v7 native entry: {function['address']}")
            require(all(r["match"] for r in function["imported_range_checks"]),
                    f"V7 imported bytes differ: {function['address']}")
            require(function["address"] not in addresses, "Duplicate v7 selected entry")
            addresses.add(function["address"])
            ranges.extend(function["ranges"])
        batches.append({"entries": len(functions),
                        "ranges": sum(len(f["ranges"]) for f in functions)})
    if check_native_bytes:
        target = Path(manifest["target_path"])
        require(sha256(target) == manifest["target_sha256"], "V7 target identity changed")
        with target.open("rb") as source:
            for span in ranges:
                size = int(span["end"], 16) - int(span["start"], 16) + 1
                source.seek(span["source_file_offset"])
                require(hashlib.sha256(source.read(size)).hexdigest() == span["source_sha256"],
                        f"Original v7 bytes changed: {span['start']}")
    return {"healthy": True, "scope": manifest["scope"],
            "previous_v6_evidence": previous,
            "file_pins_checked": len(manifest["files"]),
            "native_batches": batches, "native_selected_entries": len(addresses),
            "native_imported_ranges": len(ranges),
            "original_native_ranges_checked": len(ranges) if check_native_bytes else 0,
            "client_runtime_compared": False, "battle_ready": False,
            "autonomous_route_ready": False, "runtime_battle_validated": False}

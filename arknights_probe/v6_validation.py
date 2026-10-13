"""Read-only verification of separately reviewed v6 evidence pins."""
from pathlib import Path
import hashlib

from .data import read_json, require, sha256

ROOT = Path(__file__).resolve().parents[1]


def verify_v6_evidence(*, check_native_bytes=True):
    manifest = read_json(ROOT / "evidence/v6/manifest.json")
    for item in manifest["files"]:
        path = Path(item["path"])
        require(sha256(path) == item["sha256"], f"V6 evidence changed: {path}")
    batches, addresses, native_ranges = [], set(), []
    rejected = {entry["address"] for entry in manifest["rejected_entries"]}
    for item in manifest["native_batches"]:
        data = read_json(Path(item["path"]))
        functions = data["functions"]
        require(len(functions) == item["entries"], "V6 native batch size changed")
        for function in functions:
            require(function["decompile_completed"] and function["imported_memory_matches_source"],
                    f"Incomplete V6 native entry: {function['address']}")
            require(all(r["match"] for r in function["imported_range_checks"]),
                    "V6 native imported range mismatch")
            require(function["address"] not in addresses, "Duplicated V6 selected entry")
            addresses.add(function["address"])
            native_ranges.extend(function["ranges"])
        batches.append({"entries": len(functions), "ranges": sum(len(f["ranges"]) for f in functions)})
    require(rejected <= addresses, "Rejected candidate is absent from the preserved native batches")
    if check_native_bytes:
        with Path(manifest["target_path"]).open("rb") as source:
            for span in native_ranges:
                size = int(span["end"], 16) - int(span["start"], 16) + 1
                source.seek(span["source_file_offset"])
                require(hashlib.sha256(source.read(size)).hexdigest() == span["source_sha256"],
                        f"Original native bytes changed: {span['start']}")
    return {"healthy": True, "scope": "reviewed_v6_selected_static_components",
            "file_pins_checked": len(manifest["files"]), "native_batches": batches,
            "native_selected_entries": len(addresses), "native_imported_ranges": len(native_ranges),
            "rejected_candidate_entries": len(rejected),
            "accepted_candidate_entries": len(addresses - rejected),
            "original_native_ranges_checked": len(native_ranges) if check_native_bytes else 0,
            "physics_overlap_backend": "explicit_external_snapshot",
            "client_runtime_compared": False, "battle_ready": False,
            "autonomous_route_ready": False, "runtime_battle_validated": False}

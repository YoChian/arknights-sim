"""Read-only reviewed physics-context pins; no automatic refresh."""
import hashlib
import json
from pathlib import Path


def verify(root: Path | None = None):
    root = root or Path(__file__).resolve().parent
    manifest = json.loads((root/"native_evidence.json").read_text("utf-8"))
    for entry in manifest["files"]:
        path = Path(entry["path"])
        if not path.is_absolute():
            raise ValueError(f"Absolute physics pin required: {path}")
        with path.open("rb") as source:
            actual = hashlib.file_digest(source,"sha256").hexdigest()
        if actual != entry["sha256"]:
            raise ValueError(f"Physics evidence changed; review before repinning: {path}")
    return {"scope": manifest["scope"], "files_verified": len(manifest["files"]),
            "counts": manifest["counts"], "physics_overlap_generated": False,
            "engine_sync_generated": False, "runtime_battle_validated": False, "battle_ready": False}


if __name__ == "__main__":
    print(json.dumps(verify(),ensure_ascii=False,indent=2))

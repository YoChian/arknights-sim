"""Read-only verification of reviewed movement pins; never refreshes them."""
import hashlib
import json
from pathlib import Path


def verify(root: Path | None = None) -> dict:
    root = root or Path(__file__).resolve().parent
    manifest = json.loads((root / "native_evidence.json").read_text("utf-8"))
    checked = []
    for entry in manifest["files"]:
        path = Path(entry["path"])
        if not path.is_absolute():
            path = root / path
        with path.open("rb") as source:
            digest = hashlib.file_digest(source, "sha256").hexdigest()
        if digest != entry["sha256"]:
            raise ValueError(f"Movement evidence changed; review before repinning: {path}")
        checked.append(str(path))
    return {"scope": manifest["scope"], "files_verified": len(checked),
            "runtime_battle_validated": False, "battle_ready": False}


if __name__ == "__main__":
    print(json.dumps(verify(), ensure_ascii=False, indent=2))

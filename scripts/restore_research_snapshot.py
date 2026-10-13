"""Verify or restore byte-identical research files; never overwrite conflicts."""
from pathlib import Path
import argparse
import gzip
import hashlib
import json

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verify-only", action="store_true", help="Check archive bytes without restoring files")
    parser.add_argument("--research-root", type=Path, help="Restore directory; defaults to the original analysis root")
    args = parser.parse_args()
    manifest = json.loads((ROOT/"research/snapshot_manifest.json").read_text(encoding="utf8"))
    if manifest["format"] != "arknights-research-backup-v1":
        raise ValueError("Unknown backup format")
    target_root = (args.research_root or Path(manifest["analysis_root"])).resolve()
    checked = restored = reused = 0
    # Validate every archive and destination before writing any new file.
    plans = []
    for item in manifest["files"]:
        archive = (ROOT/item["archive_path"]).resolve()
        target = (target_root/item["relative_path"]).resolve()
        if not archive.is_relative_to(ROOT/"research") or not target.is_relative_to(target_root):
            raise ValueError("Backup path escapes its expected root")
        raw = archive.read_bytes()
        if hashlib.sha256(raw).hexdigest() != item["archive_sha256"]:
            raise ValueError("Archive changed: " + str(archive))
        data = gzip.decompress(raw) if item["compression"] == "gzip" else raw
        if len(data) != item["bytes"] or hashlib.sha256(data).hexdigest() != item["sha256"]:
            raise ValueError("Original bytes do not match: " + str(archive))
        checked += 1
        if not args.verify_only:
            if target.exists():
                with target.open("rb") as stream:
                    if hashlib.file_digest(stream,"sha256").hexdigest() != item["sha256"]:
                        raise ValueError("Restore conflict; existing file left unchanged: " + str(target))
                reused += 1
            else:
                plans.append((archive, target, item))
    for archive, target, item in plans:
        raw = archive.read_bytes()
        data = gzip.decompress(raw) if item["compression"] == "gzip" else raw
        target.parent.mkdir(parents=True, exist_ok=True)
        with target.open("xb") as stream:
            stream.write(data)
        restored += 1
    print(json.dumps({"healthy": True, "checked": checked, "restored": restored, "reused": reused,
        "verify_only": args.verify_only, "target_root": str(target_root)}, ensure_ascii=False))


if __name__ == "__main__":
    main()

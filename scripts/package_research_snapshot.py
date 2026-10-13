"""Archive reviewed external research dependencies without client originals.

Run from the original D:/Repo workspace. Existing evidence is never rewritten.
Large inputs are stored as deterministic gzip streams, retaining original SHA.
"""
from pathlib import Path
import gzip
import hashlib
import json
import shutil

ROOT = Path(__file__).resolve().parents[1]
ANALYSIS = ROOT.parent / ".rea-tools/arknights-pc"
ARCHIVE = ROOT / "research/arknights-pc"
TEXT = {".py", ".json", ".md", ".cs", ".java", ".mjs", ".c", ".csv", ".tsv", ".txt", ".fbs", ".lua"}
OWN_EXES = {
    "native_v8/npc_actions/NativeNpcActionsReference.exe",
    "native_v9/buff_container/NativeBuffContainerReference.exe",
}


def digest(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def main():
    sources = set()
    excluded = {}
    for path in (ROOT / "evidence").rglob("*.json"):
        try:
            data = json.loads(path.read_text(encoding="utf8"))
        except (ValueError, UnicodeError):
            continue
        if not isinstance(data, dict):
            continue
        for item in data.get("files", []):
            if isinstance(item, dict) and "path" in item:
                source = Path(item["path"]).resolve()
                try:
                    relative = source.relative_to(ANALYSIS.resolve()).as_posix()
                except ValueError:
                    if not source.is_relative_to(ROOT):
                        excluded[str(source)] = "external original/tool dependency; retained locally"
                    continue
                if source.suffix.lower() in TEXT or relative in OWN_EXES:
                    sources.add(source)
                else:
                    excluded[str(source)] = "raw payload or external executable; retained locally"
    # Include the normalized tables explicitly used by Dataset.
    data = json.loads((ROOT / "data/manifest.json").read_text(encoding="utf8"))
    sources.update(Path(item["path"]).resolve() for item in data["files"].values())
    # Reports and extraction source are useful even where not in an old pin list.
    for folder in [ANALYSIS / f"native_v{i}" for i in range(2, 10)]:
        sources.update(folder.rglob("*.md"))
    for extension in ("*.py", "*.fbs", "*.md"):
        sources.update((ANALYSIS / "resources_v2").rglob(extension))
    sources.add(ANALYSIS / "resources_v2/verification.json")
    records = []
    for source in sorted(sources):
        relative = source.resolve().relative_to(ANALYSIS.resolve())
        size = source.stat().st_size
        compressed = size > 5_000_000 and source.suffix.lower() in TEXT
        output = ARCHIVE / relative
        if compressed:
            output = output.with_name(output.name + ".gz")
        output.parent.mkdir(parents=True, exist_ok=True)
        if compressed:
            with source.open("rb") as incoming, output.open("wb") as raw:
                with gzip.GzipFile(filename="", fileobj=raw, mode="wb", mtime=0) as outgoing:
                    shutil.copyfileobj(incoming, outgoing)
        else:
            shutil.copyfile(source, output)
        records.append({"original_path": str(source), "relative_path": relative.as_posix(),
            "archive_path": output.relative_to(ROOT).as_posix(), "compression": "gzip" if compressed else "none",
            "bytes": size, "sha256": digest(source), "archive_sha256": digest(output)})
    manifest = {"format": "arknights-research-backup-v1", "stage": "v9", "analysis_root": str(ANALYSIS),
        "files": records, "excluded_dependencies": [{"path": p, "reason": reason} for p, reason in sorted(excluded.items())],
        "client_originals_included": False, "battle_ready": False}
    path = ROOT / "research/snapshot_manifest.json"
    path.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    print(json.dumps({"files": len(records), "original_bytes": sum(r["bytes"] for r in records),
        "stored_bytes": sum((ROOT/r["archive_path"]).stat().st_size for r in records),
        "excluded_dependencies": len(excluded), "manifest": str(path)}, ensure_ascii=False))


if __name__ == "__main__":
    main()

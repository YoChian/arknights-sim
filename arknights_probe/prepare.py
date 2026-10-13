"""Pin normalized JSON sources and extraction evidence without duplicating them."""
from pathlib import Path
import json

from .data import Dataset, DataError, read_json, sha256, require
from .coordinates import NATIVE_COORDINATE_EVIDENCE
from .legacy_random import NATIVE_RNG_EVIDENCE

DEFAULT_SOURCE = Path(__file__).resolve().parents[2] / ".rea-tools" / "arknights-pc" / "resources_v2"
DEFAULT_MANIFEST = Path(__file__).resolve().parents[1] / "data" / "manifest.json"
PATTERNS = {"level": "level_rogue6_1-1.json", "enemies": "enemy_database*.json",
            "characters": "character_table*.json", "skills": "skill_table*.json",
            "topics": "roguelike_topic_table*.json", "constants": "gamedata_const*.json"}


def prepare(source_dir: Path, output: Path) -> dict:
    source_dir = source_dir.resolve()
    normalized = source_dir / "normalized"
    files, loaded = {}, {}
    for role, pattern in PATTERNS.items():
        matches = sorted(normalized.glob(pattern))
        require(len(matches) == 1, f"Expected one {role} file for {pattern}; found {len(matches)}")
        path = matches[0].resolve()
        files[role] = {"path": str(path), "sha256": sha256(path), "bytes": path.stat().st_size}
        loaded[role] = read_json(path)
    verification_path = source_dir / "verification.json"
    provenance_paths = [verification_path, source_dir / "sample_provenance.json", source_dir / "download_provenance.json"]
    evidence = [{"path": str(p), "sha256": sha256(p)} for p in provenance_paths if p.is_file()]
    verified = read_json(verification_path) if verification_path.is_file() else []
    names = {entry["name"] for entry in verified if entry.get("structural_verification", {}).get("populated_unknown_fields") == 0}
    all_verified = all(Path(spec["path"]).stem in names for spec in files.values())
    manifest = {"format_version": 1, "files": files, "provenance": {
        "level_id": Path(files["level"]["path"]).stem,
        "schema_status": "structurally_verified_community_schema" if all_verified else "pending_structural_verification",
        "runtime_semantics_status": "not_validated",
        "coordinate_access": NATIVE_COORDINATE_EVIDENCE,
        "independent_legacy_rng_component": NATIVE_RNG_EVIDENCE,
        "extraction_evidence": evidence,
        "scope": "local PC client snapshot; no game execution or server requests",
    }}
    dataset = Dataset(loaded.pop("level"), loaded, manifest["provenance"])
    manifest["validated_summary"] = dataset.summary()
    output = output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    return {"manifest": str(output), "source_roles": list(files), "summary": dataset.summary()}

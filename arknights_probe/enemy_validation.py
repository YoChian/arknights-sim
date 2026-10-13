"""Static provenance checks, separate from live battle equivalence."""
from pathlib import Path

from .data import read_json, require, sha256

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "evidence/enemy_rules/provenance.json"


def verify_enemy_rules_evidence():
    ledger = read_json(LEDGER)
    require(ledger.get("files"), "Empty enemy evidence ledger")
    for entry in ledger["files"]:
        path = Path(entry["path"])
        require(path.is_file() and sha256(path) == entry["sha256"], f"Changed or missing enemy evidence: {path}")
    prefab_entry = next(entry for entry in ledger["files"] if Path(entry["path"]).name == "prefab_inputs.json")
    prefabs = read_json(Path(prefab_entry["path"]))
    shipped = [prefabs["index_pin"], prefabs["script_source_pin"], *prefabs["prefab_source_pins"]]
    for entry in shipped:
        path = Path(entry["path"])
        require(path.is_file() and path.stat().st_size == entry["bytes"] and sha256(path) == entry["sha256"],
                f"Changed or missing shipped prefab input: {path}")
    return {"healthy": True, "scope": ledger["scope"], "files_checked": len(ledger["files"]),
            "shipped_inputs_checked": len(shipped), "ledger_sha256": sha256(LEDGER),
            "target_sha256": ledger["target_sha256"], "client_runtime_compared": False,
            "creation_runtime_validated": False, "selector_restored": False}


def verify_enemy_data_evidence():
    directory = ROOT / "evidence/enemy_data"
    manifest = read_json(directory / "manifest.json")
    require(manifest.get("format") == "enemy_data_evidence_v1", "Unsupported enemy data evidence manifest")
    for name, expected in manifest["file_sha256"].items():
        require(Path(name).name == name, "Enemy data evidence names must be local filenames")
        path = directory / name
        require(path.is_file() and sha256(path) == expected, f"Changed or missing enemy data evidence: {path}")
    require(sha256(ROOT / "arknights_probe/enemy_data.py") == manifest["module_sha256"], "Enemy data module changed since evidence review")
    require(sha256(ROOT / "tests/test_enemy_data.py") == manifest["test_sha256"], "Enemy data tests changed since evidence review")
    return {"healthy": True, "files_checked": len(manifest["file_sha256"]),
            "manifest_sha256": sha256(directory / "manifest.json"), "client_runtime_compared": False}

"""Explicitly pin reviewed v6 sources; never run automatically from verification."""
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.data import read_json, require, sha256

NATIVE = ROOT.parent / ".rea-tools/arknights-pc/native_v6"


def main():
    paths = set()
    def add(path):
        path = Path(path).resolve()
        require(path.is_file(), f"Missing reviewed v6 input: {path}")
        paths.add(path)
    for module in ("frame_runtime", "skill_runtime", "targeting", "damage", "altar_component", "v6_validation", "__main__"):
        add(ROOT / "arknights_probe" / (module + ".py"))
    for test in ("frame_runtime", "skill_runtime", "targeting", "damage", "altar_component"):
        add(ROOT / "tests" / ("test_" + test + ".py"))
    for script in ("probe_altar_component", "pin_v6_evidence", "verify_snapshot"):
        add(ROOT / "scripts" / (script + ".py"))
    components = []
    for folder, filename in (("skill_runtime", "native_manifest.json"),
                             ("targeting", "native_evidence.json"), ("damage", "manifest.json")):
        path = ROOT / "evidence" / folder / filename
        add(path)
        document = read_json(path)
        for item in document["files"]:
            add(item["path"])
            require(sha256(Path(item["path"])) == item["sha256"], f"Child evidence changed before review: {item['path']}")
        components.append(str(path))
    batches = []
    for index in (1, 2, 3):
        for filename in (f"input_round{index}.json", f"results_round{index}.json",
                         f"raw_round{index}.json", f"ownership_round{index}.json"):
            add(NATIVE / "core" / filename)
        result_path = NATIVE / "core" / f"results_round{index}.json"
        functions = read_json(result_path)["functions"]
        require(all(f["decompile_completed"] and f["imported_memory_matches_source"] for f in functions),
                "Incomplete selected native batch")
        batches.append({"path": str(result_path), "entries": len(functions)})
    for folder, filenames in {
        "core": ("prepare.py", "ArknightsFocused.java", "rejected_entries.json"),
        "frame": ("native_fields.json", "field_offsets.json", "identity_corrections.json", "REPORT.md")
    }.items():
        for filename in filenames: add(NATIVE / folder / filename)
    add(ROOT.parent / ".rea-tools/arknights-pc/native_v5/resources/range_table.json")
    manifest = {"scope": "explicitly_reviewed_v6_component_sources",
        "target_path": r"D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll",
        "files": [{"path": str(path), "sha256": sha256(path)} for path in sorted(paths)],
        "native_batches": batches, "components": components,
        "rejected_entries": read_json(NATIVE / "core/rejected_entries.json")["rejected_entries"],
        "client_runtime_compared": False, "full_scene_ready": False}
    output = ROOT / "evidence/v6/manifest.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"pins": len(paths), "manifest": str(output)}, ensure_ascii=False))


if __name__ == "__main__":
    main()

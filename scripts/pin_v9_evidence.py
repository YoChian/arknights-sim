"""Explicit reviewed-file pinning; verification never calls this script."""
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.data import read_json, require, sha256
from arknights_probe.v8_validation import verify_v8_evidence

NATIVE = ROOT.parent / ".rea-tools/arknights-pc/native_v9"


def main():
    verify_v8_evidence()
    review = read_json(ROOT / "evidence/v9/reviewed_inputs.json")
    paths = set()
    def add(path):
        path = Path(path).resolve()
        require(path.is_file(), f"Missing reviewed input: {path}")
        paths.add(path)
    components = []
    for path in review["components"]:
        add(path)
        child = read_json(Path(path))
        for item in child["files"]:
            add(item["path"])
            require(sha256(Path(item["path"])) == item["sha256"],
                    f"Child evidence changed before pinning: {item['path']}")
        components.append(path)
    batches = []
    for tag in review["native_batch_tags"]:
        require(tag.startswith("round") and tag[5:].isdigit(), "Invalid reviewed batch tag")
        for filename in ("input_", "results_", "raw_", "ownership_", "selection_"):
            add(NATIVE / "core" / (filename + tag + ".json"))
        result_path = NATIVE / "core" / ("results_" + tag + ".json")
        functions = read_json(result_path)["functions"]
        require(all(f["decompile_completed"] and f["imported_memory_matches_source"] for f in functions),
                "Incomplete reviewed native batch")
        batches.append({"path": str(result_path), "entries": len(functions)})
    for path in review["files"]:
        add(path)
    for filename in ("prepare.py", "raw_selected.py", "ArknightsFocused.java", "run.mjs"):
        add(NATIVE / "core" / filename)
    add(ROOT / "evidence/v9/reviewed_inputs.json")
    target = Path(r"D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll")
    require(sha256(target) == review["target_sha256"], "Reviewed target identity changed")
    manifest = {"scope": "reviewed_v9_npc_factory_buff_membership_damage_reaction_and_lifecycle",
                "target_path": str(target), "target_sha256": review["target_sha256"],
                "files": [{"path": str(p), "sha256": sha256(p)} for p in sorted(paths)],
                "native_batches": batches, "components": components,
                "client_runtime_compared": False, "full_scene_ready": False}
    output = ROOT / "evidence/v9/manifest.json"
    output.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"pins": len(paths), "manifest": str(output)}, ensure_ascii=False))


if __name__ == "__main__":
    main()

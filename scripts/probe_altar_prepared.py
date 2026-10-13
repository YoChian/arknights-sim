"""Run the source-prepared altar; physics/status context remains explicit."""
import argparse
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe import Dataset
from arknights_probe.altar_prepared import PreparedAltarProbe


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--frames", type=int, default=10000)
    parser.add_argument("--output", type=Path, default=ROOT / "artifacts/altar_component_prepared.json")
    args = parser.parse_args()
    probe = PreparedAltarProbe(Dataset.from_manifest(ROOT / "data/manifest.json"))
    final = probe.step(args.frames)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(probe.artifact(), ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"artifact": str(args.output.resolve()), **final}, ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

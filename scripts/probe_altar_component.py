"""Save the explicit altar/one-stationary-enemy composition artifact."""
import argparse
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.altar_component import AltarComponentProbe
from arknights_probe.data import Dataset
from arknights_probe.prepare import DEFAULT_MANIFEST


def make_probe(dataset=None):
    return AltarComponentProbe(dataset or Dataset.from_manifest(DEFAULT_MANIFEST))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--frames", type=int, default=5000)
    parser.add_argument("--output", type=Path, default=ROOT / "artifacts/altar_component_external.json")
    args = parser.parse_args()
    probe = make_probe()
    probe.step(args.frames)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(probe.artifact(), ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"artifact": str(args.output.resolve()), **probe.snapshot()}, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()

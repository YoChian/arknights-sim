"""Run the prepared altar using explicit epoch-bound Unity query receipts."""
import argparse
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe import Dataset
from arknights_probe.physics_altar import PhysicsPlannedAltarProbe


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--frames", type=int, default=10000)
    parser.add_argument("--output", type=Path, default=ROOT / "artifacts/altar_physics_contract.json")
    args = parser.parse_args()
    probe = PhysicsPlannedAltarProbe(Dataset.from_manifest(ROOT / "data/manifest.json"))
    probe.step(args.frames)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(probe.artifact(), ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    print(json.dumps({"artifact": str(args.output), "snapshot": probe.snapshot(),
                      "query_calls": len(probe.physics_records),
                      "first_query": probe.physics_records[0]["plans"][0]["epoch"] if probe.physics_records else None},
                     ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

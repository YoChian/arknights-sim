"""Run both explicit NPC event fixtures; no game or full-map execution."""
import argparse
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.npc_component import run_npc_component_fixtures


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=ROOT / "artifacts/npc_component.json")
    args = parser.parse_args()
    artifact = run_npc_component_fixtures()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(artifact, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"artifact": str(args.output),
                      "damage_signal": artifact["damage_signal_fixture"]["snapshot"],
                      "death_signal": artifact["death_signal_fixture"]["snapshot"]},
                     ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

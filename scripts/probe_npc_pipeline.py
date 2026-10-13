"""Run our selected prepared NPC composition, never the game client."""
from pathlib import Path
import json
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.npc_pipeline import run_npc_pipeline_fixtures


if __name__ == "__main__":
    result = run_npc_pipeline_fixtures()
    path = ROOT / "artifacts/npc_pipeline.json"
    path.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    print(json.dumps(dict(artifact=str(path), after_reaction=result["after_reaction"],
                         death_after=result["death_fixture"]["snapshot"]), ensure_ascii=False, indent=2))

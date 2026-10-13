"""Intentionally pin reviewed static inputs; verification never refreshes pins."""
from pathlib import Path
import json
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.data import sha256

ANALYSIS = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v4")
FILES = [ANALYSIS / "creation" / name for name in (
    "results_round1.json", "results_round2.json", "input_round2.json", "raw_round3.json", "input_round3.json")]
FILES += [ANALYSIS / "resources" / "prefab_inputs.json"]
LEDGER = ROOT / "evidence/enemy_rules/provenance.json"
LEDGER.parent.mkdir(parents=True, exist_ok=True)
LEDGER.write_text(json.dumps({
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "scope": "static_selected_attribute_mul_and_prefab_scheduler_delay",
    "files": [{"path": str(path), "sha256": sha256(path)} for path in FILES],
    "selector_restored": False,
    "creation_runtime_validated": False,
    "client_runtime_compared": False,
}, indent=2) + "\n", encoding="utf8")
print(json.dumps({"files_pinned": len(FILES), "ledger": str(LEDGER)}))

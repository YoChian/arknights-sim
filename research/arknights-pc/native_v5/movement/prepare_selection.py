"""Request exact new metadata candidates; root runs shared Ghidra serially."""
from pathlib import Path
import json

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).parent
selected = {
    70688: "Tile prefab/data initialization and origin/cached options",
    70729: "Map TileData assignment",
    70734: "Option override update",
    70736: "Restore origin options",
    70737: "Refresh cache/route side effects",
    70739: "Trap option rewrite entry",
    70740: "Default preprocess cache/source",
    77519: "Trap.OnInit rewrite timing and TrapMode options",
    70270: "DirectionCursor creation/default flags and offset",
    76531: "Enemy FP tick movement/cursor/controller call order",
    76397: "Default main cursor dispatch excludes trace/fear/attract",
    76398: "Default move cursor dispatch",
    77885: "Base local position assignment and deterministic processing",
    25960: "PeriodicTicker integer frame cadence",
    25961: "PeriodicTicker reset base state",
    25962: "PeriodicTicker alternate reset",
    25963: "PeriodicTicker check and increment",
    64441: "Actual deterministic-mode getter",
    66413: "canMove status gate",
    66492: "ActuallyGroundBound movement early exit",
    70219: "WAIT Checkpoint zero movement vector (base Checkpoint method is abstract)",
    70183: "Checkpoint next index transition",
    71064: "Controller conveyor early-exit path; require explicit absent fixture",
    71065: "Conveyor motion applicability gating",
}
rows = json.loads((ROOT / "core/Assembly-CSharp_candidate_method_map.json").read_text())
requests = []
for index, reason in selected.items():
    row = next(row for row in rows if row["metadata_method_index"] == index)
    assert row["candidate_va"]
    requests.append({"type": row["type"], "method": row["method"], "address": row["candidate_va"],
                     "metadata_method_index": index, "reason": reason})
(OUT / "selection.json").write_text(json.dumps(requests, indent=2), encoding="utf-8")
print(json.dumps({"entries": len(requests), "path": str(OUT / "selection.json")}))

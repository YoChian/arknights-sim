"""Create reviewed evidence and fixed-context path artifacts after checks pass.

This script deliberately writes pins. Do not use it to silence a changed-source
test failure without reviewing the source and reference differences.
"""
from pathlib import Path
import hashlib, json, sys

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[1]
ANALYSIS = ROOT.parent / ".rea-tools/arknights-pc"
sys.path.insert(0, str(ROOT))
from arknights_probe.data import Dataset
from arknights_probe.movement import NativeTileSnapshot, NativeWalkPathGrid, WalkRouteSpec, compile_walk_route


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


files = [
    "MovementReference.cs", "reference_input.json", "reference_vectors.json", "static_tile_fixture.json",
    str(ANALYSIS / "native_v4/movement/results_round2.json"),
    str(ANALYSIS / "native_v4/creation/results_round2.json"),
    str(ANALYSIS / "native_v4/attributes/results_round3.json"),
    str(ANALYSIS / "native_v4/movement/raw_float_helpers.json"),
    str(ANALYSIS / "native_v4/movement/raw_float_followups.json"),
    str(ANALYSIS / "native_v4/movement/raw_geometry_followups2.json"),
    str(ANALYSIS / "native_v4/movement/float_literal_constants.json"),
    str(ANALYSIS / "native_v4/resources/native_fields.json"),
    str(ANALYSIS / "native_v4/resources/shared_consts.json"),
    str(ANALYSIS / "native_v4/resources/attribute_meta.json"),
]
reports = []
for relative in ("native_v4/movement/results_round2.json", "native_v4/creation/results_round2.json", "native_v4/attributes/results_round3.json"):
    report = json.loads((ANALYSIS / relative).read_text())
    assert all(f["decompile_completed"] and f["imported_memory_matches_source"] and all(piece["match"] for piece in f["imported_range_checks"]) for f in report["functions"])
    reports.append({"path": relative, "complete_entries": len(report["functions"]), "all_imported_ranges_match": True})
fixture = json.loads((OUT / "static_tile_fixture.json").read_text())
dataset = Dataset.from_manifest(ROOT / "data/manifest.json")
grid = NativeWalkPathGrid([[NativeTileSnapshot(**tile) for tile in row] for row in fixture["logical_rows"]], source=fixture["source"])
inventory = []
for index, route in enumerate(dataset.level["routes"]):
    if route["motionMode"] != "WALK":
        continue
    spec = WalkRouteSpec.from_json(route, height=grid.height, width=grid.width)
    compiled = compile_walk_route(spec, grid)
    first = next((nodes for nodes in compiled.checkpoint_maps if nodes is not None), compiled.final_map)
    node = first[spec.start[0]][spec.start[1]]
    inventory.append({"route_index": index, "start": list(spec.start), "end": list(spec.end),
                      "initial_next_grid": list(node.next_grid), "initial_distance_to_final": node.distance_to_final,
                      "MOVE_maps": sum(nodes is not None for nodes in compiled.checkpoint_maps),
                      "wait_seconds": [cp.seconds for cp in spec.checkpoints if cp.kind == "WAIT_FOR_SECONDS"],
                      "spawn_offset": {"x": spec.spawn_offset.x, "y": spec.spawn_offset.y},
                      "start_reachable": node.is_valid})
(OUT / "path_inventory.json").write_text(json.dumps({"scope": grid.scope(), "fixture": "static_tile_fixture.json",
    "limits": fixture["limits"] + ["weighted distances are not elapsed seconds", "checkpoint maps are not movement trajectories", "full controller/cursor/leak simulation absent"],
    "routes": inventory}, indent=2), encoding="utf-8")
files.append("path_inventory.json")
reference_input = json.loads((OUT / "reference_input.json").read_text())
reference = json.loads((OUT / "reference_vectors.json").read_text())
counts = {"geometry_cases": len(reference["geometry"]), "geometry_assertions": len(reference["geometry"]) * 8,
          "path_cases": len(reference["paths"]),
          "path_node_snapshots": sum(len(case["raw"]) + len(case["smooth"]) for case in reference["paths"]),
          "raycasts": sum(len(case["rays"]) for case in reference["paths"]),
          "realmap_conditional_routes_compiled": len(inventory)}
report = {"scope": "native WAIT/float geometry/default WALK path components and independent C# translation checks",
          "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
          "client_runtime_compared": False, "hotfix_runtime_compared": False,
          "autonomous_route_ready": False, "battle_ready": False,
          "sse_assumption": "masked exceptions; nearest-even binary32 arithmetic; finite local coordinates",
          "reference_scope": "source-owned independent reconstructed C#, not a native/client oracle",
          "counts": counts, "native_reports": reports,
          "overload_correction": {"0x180ad3e60": "VisualObject.SetPosition(GridPosition), old initial Vector2 label was wrong",
                                  "0x180ad3dc0": "VisualObject.SetPosition(Vector2), actual Enemy call target",
                                  "0x1808b6530": "CalculateTotalForce nonvirtual",
                                  "virtual_slot_7": "_CalculateSteeringForce", "virtual_slot_8": "CalculateIsHanging"},
          "files": [{"path": name, "sha256": digest(Path(name) if Path(name).is_absolute() else OUT / name)} for name in files],
          "limits": ["no autonomous movement/leak/lifecycle completion claimed",
                     "cached Tile.Init state, device rewrite and dynamic obstacle context unresolved",
                     "controller forces, tick/position assignment and mode gates are not integrated",
                     "Python fail-closed excludes nonfinite coordinates, int32 overflow, unavailable/destroyed Unity objects",
                     "reference C# checks independent arithmetic and path translation, not fixture correctness or runtime RNG order"]}
(OUT / "native_evidence.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
print(json.dumps(counts, indent=2))

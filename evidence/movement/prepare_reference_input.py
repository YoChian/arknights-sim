"""Generate reviewed input fixtures, never Python solver outputs."""
from pathlib import Path
import copy, json, math, struct

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[1]


def bits(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


geometry = []
vectors = [(0, 0), (3, 4), (-3, 4), (1e-5, 0), (9e-6, 9e-6),
           (.5, 1.5), (-.5, -1.5), (2.5, 3.5), (.2, -.2), (-.33, -.01),
           (1e-20, -1e-20), (1048576, .03125), (1234.5678, -999.9999)]
eps_bits = bits(1e-5)
vectors.extend((struct.unpack("<f", struct.pack("<I", eps_bits + delta))[0], 0) for delta in (-1, 1))
for index, (x, y) in enumerate(vectors):
    for maximum in (0, 2, 5, -2):
        geometry.append({"name": f"g{index}_max{maximum}", "x": bits(x), "y": bits(y),
                         "max": bits(maximum), "radius": bits(.05), "target_x": bits(.05), "target_y": bits(0)})


def tile(mask=3, goto=15, cost=False, obstacle=False):
    return {"passable_mask": mask, "walk_goto_mask": goto,
            "override_obstacle_move_cost": cost, "is_obstacle_like": obstacle}


paths = []


def add(name, rows, target):
    height, width = len(rows), len(rows[0])
    rays = []
    for start in ((0, 0), (height - 1, width - 1), (0, width - 1), (height - 1, 0)):
        for end in ((0, 0), target, (height - 1, width - 1)):
            rays.append({"start": list(start), "end": list(end)})
    paths.append({"name": name, "rows": rows, "target": list(target), "rays": rays})


add("equal_fifo_square", [[tile() for c in range(2)] for r in range(2)], (1, 1))
rows = [[tile() for c in range(5)] for r in range(3)]
rows[1][2] = tile(cost=True, obstacle=True)
add("weighted_detour", rows, (1, 4))
rows = [[tile() for c in range(2)] for r in range(2)]
rows[0][1] = tile(0, 0)
add("corner_blocked", rows, (1, 1))
add("one_way_right", [[tile(1, 2), tile()]], (0, 1))
add("one_way_wrong", [[tile(1, 8), tile()]], (0, 1))
add("fly_only_goal", [[tile(), tile(2)]], (0, 1))

# Fixed non-game LCG creates additional synthetic graph fixtures; no claim
# about the client's RNG algorithm or consumption order is involved.
state = 0x4d4f5645
for case in range(20):
    height, width = 2 + case % 4, 2 + case % 5
    rows = []
    for r in range(height):
        row = []
        for c in range(width):
            state = (1664525 * state + 1013904223) & 0xffffffff
            row.append(tile(0 if state % 11 == 0 else 3, 15 if state % 5 else state % 16,
                            state % 13 == 0, state % 17 == 0))
        rows.append(row)
    rows[-1][-1] = tile()
    add(f"synthetic_{case}", rows, (height - 1, width - 1))

manifest = json.loads((ROOT / "data/manifest.json").read_text())
level_path = Path(manifest["files"]["level"]["path"])
if not level_path.is_absolute():
    level_path = ROOT / "data" / level_path
level = json.loads(level_path.read_text())
# This is an explicit declaration-only frozen scenario. Defaults below are
# fixture inputs, not a reconstruction of prefab/cached Tile.Init state.
height, width = level["mapData"]["map"]["row_size"], level["mapData"]["map"]["column_size"]
masks = {"NONE": 0, "WALK_ONLY": 1, "FLY_ONLY": 2, "ALL": 3}
rows = []
for r in range(height):
    row = []
    for c in range(width):
        index = level["mapData"]["map"]["matrix_data"][(height-r-1) * width + c]
        row.append(tile(masks[level["mapData"]["tiles"][index]["passableMask"]]))
    rows.append(row)
source = "explicit frozen scenario: resource passable declarations, goto=15, costs=1, obstacleLike=false; prefab/device rewrites and dynamic boxes excluded"
fixture = {"source": source, "source_level_sha256": manifest["files"]["level"]["sha256"],
           "limits": ["cached tile initialization not validated", "altar/device options and boxes not applied", "not a live-client map oracle"],
           "logical_rows": rows}
(OUT / "static_tile_fixture.json").write_text(json.dumps(fixture, indent=2), encoding="utf-8")
for target in ((3, 0), (1, 9), (5, 7)):
    add(f"realmap_conditional_target_{target[0]}_{target[1]}", copy.deepcopy(rows), target)
(OUT / "reference_input.json").write_text(json.dumps({"scope": "independent C# static native translation; explicit synthetic/frozen fixture inputs; not client oracle",
    "geometry": geometry, "paths": paths}, indent=2), encoding="utf-8")
print(json.dumps({"geometry_cases": len(geometry), "path_cases": len(paths)}))

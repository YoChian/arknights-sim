"""Cardinal grid reachability probe; explicitly not Unity pathfinding."""
from collections import deque
from html import escape
from pathlib import Path

from .data import Dataset, DataError
from .coordinates import NATIVE_COORDINATE_EVIDENCE


def cardinal_path(dataset: Dataset, start: tuple[int, int], end: tuple[int, int], *, row_mapping: str = "bottom_origin") -> list[tuple[int, int]] | None:
    if row_mapping not in {"matrix", "bottom_origin"}:
        raise DataError("Unknown row mapping")
    def tile(point):
        row, col = point
        return dataset.tile(row, col) if row_mapping == "bottom_origin" else dataset.matrix_tile(row, col)
    for point in (start, end):
        if tile(point)["passableMask"] != "ALL":
            return None
    queue, parent = deque([start]), {start: None}
    while queue:
        point = queue.popleft()
        if point == end:
            result = []
            while point is not None:
                result.append(point)
                point = parent[point]
            return list(reversed(result))
        row, col = point
        # Stable diagnostic tie order only. No claim about client's tie breaking.
        for nr, nc in ((row - 1, col), (row, col - 1), (row, col + 1), (row + 1, col)):
            node = nr, nc
            if (0 <= nr < dataset.rows and 0 <= nc < dataset.cols and node not in parent
                    and tile(node)["passableMask"] == "ALL"):
                parent[node] = point
                queue.append(node)
    return None


def route_probe(dataset: Dataset, index: int, *, extra: bool = False, row_mapping: str = "bottom_origin") -> dict:
    routes = dataset.extra_routes if extra else dataset.routes
    if type(index) is not int or not 0 <= index < len(routes):
        raise DataError("Route index out of range")
    route = routes[index]
    if route["motionMode"] != "WALK":
        raise DataError("Topology probe only supports WALK; E_NUM placeholders are not routes")
    anchors = [dataset.position(route["startPosition"], "start")]
    for cp in route.get("checkpoints", []):
        if cp["type"] == "MOVE":
            anchors.append(dataset.position(cp["position"], "checkpoint"))
    anchors.append(dataset.position(route["endPosition"], "end"))
    segments = [{"from": a, "to": b, "cardinal_path": cardinal_path(dataset, a, b, row_mapping=row_mapping)} for a, b in zip(anchors, anchors[1:])]
    return {"route_index": index, "route_pool": "extraRoutes" if extra else "routes",
            "coordinate_mapping": row_mapping, "coordinate_mapping_native_verified": row_mapping == "bottom_origin",
            "coordinate_mapping_basis": "native_mapdata_get_item" if row_mapping == "bottom_origin" else "raw_matrix_storage_view_not_route_coordinates",
            "coordinate_evidence": NATIVE_COORDINATE_EVIDENCE if row_mapping == "bottom_origin" else None,
            "scope": "cardinal_grid_topology_only", "anchors": anchors, "segments": segments,
            "declared_wait_seconds": [cp["time"] for cp in route.get("checkpoints", []) if cp["type"] == "WAIT_FOR_SECONDS"],
            "all_segments_reachable": all(x["cardinal_path"] is not None for x in segments),
            "limits": ["No movement speed, steering, diagonal path, collision, offsets or reach thresholds",
                       "Tile indexing is recovered; cardinal BFS is a diagnostic, not full Unity pathfinding",
                       "Wait declarations are inspected but not executed"]}


def render_svg(dataset: Dataset, path: Path, route: int | None = None, *, row_mapping: str = "bottom_origin") -> None:
    if row_mapping not in {"matrix", "bottom_origin"}:
        raise DataError("Unknown row mapping")
    cell, left, top = 62, 38, 118
    width, height = left * 2 + cell * dataset.cols, top + cell * dataset.rows + 118
    colors = {"tile_forbidden": "#222834", "tile_wall": "#59616f", "tile_road": "#2e6970",
              "tile_floor": "#3c7c72", "tile_start": "#d5535f", "tile_end": "#548eed", "tile_hole": "#11151f"}
    labels = {"tile_forbidden": "×", "tile_wall": "W", "tile_road": ".", "tile_floor": "F", "tile_start": "S", "tile_end": "E", "tile_hole": "O"}
    body = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">',
            '<rect width="100%" height="100%" fill="#151923"/>',
            '<g font-family="Segoe UI,Arial,sans-serif" fill="#e7edf4">',
            '<text x="38" y="38" font-size="24">level_rogue6_1-1 · extracted map</text>',
            f'<text x="38" y="68" font-size="14">7 × 11 · {"native logical coordinates" if row_mapping == "bottom_origin" else "raw matrix storage view"}: {row_mapping}</text>',
            '<text x="38" y="92" font-size="13" fill="#c0a674">No combat, timing, random groups or Unity pathfinding simulation</text>']
    for r in range(dataset.rows):
        for c in range(dataset.cols):
            tile = dataset.matrix_tile(r, c)
            x, y = left + c * cell, top + r * cell
            body += [f'<rect x="{x}" y="{y}" width="{cell-2}" height="{cell-2}" rx="4" fill="{colors.get(tile["tileKey"], "#777")}"><title>{escape(str(tile))}</title></rect>',
                     f'<text x="{x+cell/2}" y="{y+29}" text-anchor="middle" font-size="21">{escape(labels.get(tile["tileKey"], "?"))}</text>',
                     f'<text x="{x+cell/2}" y="{y+48}" text-anchor="middle" font-size="10" fill="#acbac7">{dataset.rows-1-r if row_mapping == "bottom_origin" else r},{c}</text>']
    if route is not None:
        probe = route_probe(dataset, route, row_mapping=row_mapping)
        display_row = lambda r: dataset.rows-1-r if row_mapping == "bottom_origin" else r
        for segment in probe["segments"]:
            points = segment["cardinal_path"]
            if points:
                coords = " ".join(f"{left+c*cell+cell/2},{top+display_row(r)*cell+cell/2}" for r, c in points)
                body.append(f'<polyline points="{coords}" stroke="#ffd56b" stroke-width="4" opacity="0.9" fill="none"/>')
        for i, (r, c) in enumerate(probe["anchors"]):
            body.append(f'<circle cx="{left+c*cell+cell/2}" cy="{top+display_row(r)*cell+cell/2}" r="7" fill="#ffd56b"><title>anchor {i}</title></circle>')
    y = top + dataset.rows * cell + 27
    body += [f'<text x="38" y="{y}" font-size="13">S start tile · E end tile · F floor · W wall · O hole · × forbidden</text>',
             f'<text x="38" y="{y+24}" font-size="13">Yellow: cardinal reachability diagnostic for route {route}, not actual enemy motion.</text>',
             f'<text x="38" y="{y+48}" font-size="13" fill="#9aabba">Source version and SHA-256 are pinned in data/manifest.json.</text>', '</g></svg>']
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(body), encoding="utf-8")

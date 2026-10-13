"""Movement components recovered from static native paths.

Only proved components are exposed. A WAIT checkpoint uses a Q32.32 countdown,
which differs from the scheduler's rounded frame wait. Full WALK route movement
is being recovered; this module does not replace native paths with grid BFS.
"""
from __future__ import annotations

from dataclasses import dataclass
from collections import deque
import math

from .data import array, integer, number, obj, require
from .fp import FP, binary32

WAIT_CHECKPOINT_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "WaitForSecondsCheckpoint.OnBegin": "0x1808a8a20",
    "WaitForSecondsCheckpoint.OnTick": "0x1808a8a90",
    "WaitForSecondsCheckpoint.get_isReached": "0x1808a89c0",
    "component": "FP countdown max(0,remaining-delta), not scheduler frame rounding",
    "client_runtime_compared": False,
}


class WaitCheckpoint:
    """Static WAIT_FOR_SECONDS timer; callers determine cursor tick ordering."""
    def __init__(self, seconds: float):
        # The original CheckpointData.time is Single. Conversion follows the
        # recovered FP(float32) implicit operator, including its exact bits.
        seconds = number(seconds, "Checkpoint seconds", minimum=0)
        self.initial = FP.from_float32(seconds)
        require(self.initial.raw >= 0, "Only finite nonnegative checkpoint waits are supported")
        self.remaining = self.initial

    def begin(self) -> None:
        self.remaining = self.initial

    @property
    def is_reached(self) -> bool:
        return self.remaining.raw <= 0

    def tick(self, delta: FP) -> None:
        require(isinstance(delta, FP) and delta.raw >= 0, "Checkpoint delta must be a nonnegative FP")
        result = self.remaining - delta
        self.remaining = FP.from_raw(max(0, result.raw))

    def snapshot(self) -> dict:
        return {"initial_raw": self.initial.raw, "remaining_raw": self.remaining.raw,
                "is_reached": self.is_reached}


@dataclass(frozen=True)
class LocalVector2:
    """Unity local-map position/offset storage, rounded to binary32 per field."""

    x: float
    y: float

    def __post_init__(self):
        for key in ("x", "y"):
            value = binary32(number(getattr(self, key), f"Vector2.{key}"))
            require(math.isfinite(value), f"Vector2.{key}: binary32 overflow")
            object.__setattr__(self, key, value)

    @classmethod
    def from_json(cls, value: dict, label: str) -> "LocalVector2":
        value = obj(value, label)
        require(set(value) == {"x", "y"}, f"{label}: unexpected vector fields")
        return cls(number(value["x"], label + ".x"), number(value["y"], label + ".y"))

    def __add__(self, other: "LocalVector2") -> "LocalVector2":
        return LocalVector2(binary32(self.x + other.x), binary32(self.y + other.y))

    def __sub__(self, other: "LocalVector2") -> "LocalVector2":
        return LocalVector2(binary32(self.x - other.x), binary32(self.y - other.y))

    def scale(self, scalar: float) -> "LocalVector2":
        scalar = binary32(number(scalar, "Vector2 scalar"))
        return LocalVector2(binary32(self.x * scalar), binary32(self.y * scalar))

    @property
    def squared_magnitude(self) -> float:
        # Explicit MULSS/MULSS/ADDSS order; no double-valued hypot or FMA.
        return binary32(binary32(self.y * self.y) + binary32(self.x * self.x))

    @property
    def magnitude(self) -> float:
        # Native get_normalized promotes the rounded Single sum to Double,
        # performs SQRT, then CVTSD2SS before DIVSS on each axis.
        return binary32(math.sqrt(self.squared_magnitude))

    def normalized(self) -> "LocalVector2":
        magnitude = self.magnitude
        if magnitude <= binary32(1e-5):
            return LocalVector2(0, 0)
        return LocalVector2(binary32(self.x / magnitude), binary32(self.y / magnitude))


def grid_to_local(grid: tuple[int, int]) -> LocalVector2:
    """GridPosition.get_asLocalPosition: x=column, y=row; no half-cell shift."""
    require(isinstance(grid, tuple) and len(grid) == 2 and all(type(x) is int for x in grid),
            "Grid position must be an integer (row,column) tuple")
    return LocalVector2(grid[1], grid[0])


def local_to_grid(position: LocalVector2) -> tuple[int, int]:
    """FromVectorPosition uses native nearest-even integer conversion on y,x."""
    require(isinstance(position, LocalVector2), "Local position must be a LocalVector2")
    result = round(position.y), round(position.x)
    require(all(-(1 << 31) <= x < (1 << 31) for x in result), "Grid rounding exceeds supported int32 range")
    return result


def check_distance(lhs: LocalVector2, rhs: LocalVector2, distance: float) -> bool:
    """MathUtil.CheckDistance exact Single squared-distance comparison."""
    distance = binary32(number(distance, "CheckDistance distance"))
    delta = lhs - rhs
    return binary32(distance * distance) >= delta.squared_magnitude


def vector_is_zero(vector: LocalVector2) -> bool:
    """MathUtil.IsZero(Vector2) compares each component to binary32 1e-5."""
    threshold = binary32(1e-5)
    return abs(vector.x) <= threshold and abs(vector.y) <= threshold


def normalize_direction_safely(vector: LocalVector2, tolerance: float = 1e-5) -> LocalVector2:
    tolerance = binary32(number(tolerance, "direction tolerance", minimum=0))
    if abs(vector.x) <= tolerance and abs(vector.y) <= tolerance:
        return LocalVector2(0, 0)
    return vector.normalized()


def clamp_magnitude(vector: LocalVector2, max_length: float) -> LocalVector2:
    """Unity helper 0x1805e7770: compare squared norms, divide, then multiply.

    Negative max_length intentionally retains the native helper's arithmetic;
    runtime enemy move speed must separately pass its attribute constraints.
    """
    max_length = binary32(number(max_length, "max_length"))
    require(math.isfinite(max_length), "max_length: binary32 overflow")
    if vector.squared_magnitude <= binary32(max_length * max_length):
        return vector
    magnitude = vector.magnitude
    return LocalVector2(binary32(binary32(vector.x / magnitude) * max_length),
                        binary32(binary32(vector.y / magnitude) * max_length))


# GridPosition.cctor / MapUtil.GetFourWayDirection enumerate up,right,down,left.
FOUR_NEIGHBORS = ((1, 0), (0, 1), (-1, 0), (0, -1))
INVERSE_DIRECTIONS = (2, 3, 0, 1)


@dataclass(frozen=True)
class NativeTileSnapshot:
    """Explicit cached tile state, not inferred from a tile key or height.

    Callers must identify the source of the complete runtime snapshot. The
    resource declarations alone do not resolve prefab options or dynamic masks.
    """
    passable_mask: int
    walk_goto_mask: int
    override_obstacle_move_cost: bool
    is_obstacle_like: bool

    def __post_init__(self):
        require(type(self.passable_mask) is int and 0 <= self.passable_mask <= 3,
                "Only WALK/FLY passable mask bits are supported")
        require(type(self.walk_goto_mask) is int and 0 <= self.walk_goto_mask <= 15,
                "WALK goto mask must contain four native direction bits")
        require(type(self.override_obstacle_move_cost) is bool and type(self.is_obstacle_like) is bool,
                "Tile obstacle flags must be explicit booleans")

    @property
    def walk_passable(self) -> bool:
        return bool(self.passable_mask & 1)

    @property
    def move_cost(self) -> int:
        return 1000 if self.override_obstacle_move_cost else 1

    def passable_goto(self, direction: int) -> bool:
        require(type(direction) is int and 0 <= direction < 4, "Invalid native four-way direction")
        return self.walk_passable and bool(self.walk_goto_mask & (1 << direction))


@dataclass
class PathNode:
    grid: tuple[int, int]
    tile: NativeTileSnapshot
    next_grid: tuple[int, int]
    has_next: bool = False
    distance: int = -1
    distance_to_final: int = -1
    in_open_list: bool = False
    next_turn: LocalVector2 = LocalVector2(0, 0)

    @property
    def is_valid(self) -> bool:
        return self.distance >= 0  # The explicit snapshot has no destroyed Unity tile objects.

    @property
    def obstacle_like_or_invalid(self) -> bool:
        return not self.is_valid or self.tile.is_obstacle_like

    def safe_next_position(self) -> LocalVector2:
        return grid_to_local(self.next_grid if self.is_valid and self.has_next else self.grid)

    def safe_next_direction(self) -> LocalVector2:
        if not self.is_valid or not self.has_next:
            return LocalVector2(0, 0)
        return (grid_to_local(self.next_grid) - grid_to_local(self.grid)).normalized()


class NativeWalkPathGrid:
    """Native default WALK SPFA and Bresenham smoothing over explicit tile state.

    A declared source string is mandatory because runtime cached tile state is
    not reconstructed by this class. Dynamic tile changes need a fresh grid.
    It does not supply movement controller state, enemies, device effects or
    mode permission, and does not grant autonomous battle readiness.
    """
    def __init__(self, rows: list[list[NativeTileSnapshot]], *, source: str):
        require(isinstance(source, str) and bool(source.strip()), "Tile snapshot source is required")
        require(isinstance(rows, list) and rows and isinstance(rows[0], list) and rows[0],
                "A nonempty logical bottom-origin tile matrix is required")
        self.height, self.width = len(rows), len(rows[0])
        require(all(isinstance(row, list) and len(row) == self.width for row in rows), "Tile matrix must be rectangular")
        require(all(isinstance(tile, NativeTileSnapshot) for row in rows for tile in row), "Every tile needs explicit native cached state")
        self.tiles = tuple(tuple(row) for row in rows)
        self.source = source

    def valid_grid(self, grid: tuple[int, int]) -> bool:
        return 0 <= grid[0] < self.height and 0 <= grid[1] < self.width

    def next_map(self, target: tuple[int, int], *, smooth: bool = True) -> list[list[PathNode]]:
        require(self.valid_grid(target), "Path target lies outside the map")
        require(type(smooth) is bool, "smooth must be a boolean")
        nodes = [[PathNode((r, c), self.tiles[r][c], (r, c)) for c in range(self.width)] for r in range(self.height)]
        goal = nodes[target[0]][target[1]]
        queue = deque()
        if goal.tile.walk_passable:
            goal.distance, goal.in_open_list = 0, True
            queue.append(goal)
        while queue:
            current = queue.popleft()
            current.in_open_list = False
            for direction, (dr, dc) in enumerate(FOUR_NEIGHBORS):
                grid = current.grid[0] + dr, current.grid[1] + dc
                if not self.valid_grid(grid):
                    continue
                neighbor = nodes[grid[0]][grid[1]]
                if not neighbor.tile.passable_goto(INVERSE_DIRECTIONS[direction]):
                    continue
                distance = current.distance + neighbor.tile.move_cost
                require(distance < (1 << 31), "Native distance int32 overflow is unsupported")
                if not neighbor.is_valid or distance < neighbor.distance:
                    neighbor.next_grid = current.grid
                    neighbor.distance = distance
                    neighbor.has_next = True
                    if not neighbor.in_open_list:
                        neighbor.in_open_list = True
                        queue.append(neighbor)
        for row in nodes:
            for node in row:
                node.distance_to_final = node.distance
                if smooth and node.is_valid and node.has_next:
                    successor = node.next_grid
                    while nodes[successor[0]][successor[1]].has_next:
                        farther = nodes[successor[0]][successor[1]].next_grid
                        if not self.raycast_bresenham(node.grid, farther, nodes):
                            break
                        successor = farther
                    node.next_grid = successor
        return nodes

    def raycast_bresenham(self, start: tuple[int, int], end: tuple[int, int], nodes: list[list[PathNode]]) -> bool:
        """Transcribe native WALK raycast, including corner cells and goto bits."""
        require(self.valid_grid(start) and self.valid_grid(end), "Raycast endpoints outside map")
        dr, dc = abs(end[0] - start[0]), abs(end[1] - start[1])
        row_major = dc < dr
        # After swaps the major axis always increases. Native mask checks also
        # use this scan direction, independently of the original route order.
        u0, v0 = start if row_major else (start[1], start[0])
        u1, v1 = end if row_major else (end[1], end[0])
        if u1 < u0:
            u0, u1, v0, v1 = u1, u0, v1, v0
        major, minor = u1 - u0, abs(v1 - v0)
        step = 1 if v0 < v1 else -1
        major_direction = 0 if row_major else 1
        minor_direction = (1 if step == 1 else 3) if row_major else (0 if step == 1 else 2)

        def at(u, v):
            grid = (u, v) if row_major else (v, u)
            require(self.valid_grid(grid), "Native raycast reached an unsupported out-of-map cell")
            return nodes[grid[0]][grid[1]]

        if minor < 2:
            for row in range(min(start[0], end[0]), max(start[0], end[0]) + 1):
                for col in range(min(start[1], end[1]), max(start[1], end[1]) + 1):
                    if nodes[row][col].obstacle_like_or_invalid:
                        return False
        error, v = -major, v0
        for u in range(u0, u1 + 1):
            node = at(u, v)
            if node.obstacle_like_or_invalid or not node.tile.passable_goto(major_direction):
                return False
            error += 2 * minor
            if u < u1 and error >= 0:
                minor_neighbor, major_neighbor = at(u, v + step), at(u + 1, v)
                if minor_neighbor.obstacle_like_or_invalid or major_neighbor.obstacle_like_or_invalid:
                    return False
                if (not node.tile.passable_goto(minor_direction)
                    or not major_neighbor.tile.passable_goto(minor_direction)
                    or not minor_neighbor.tile.passable_goto(major_direction)):
                    return False
                v += step
                error -= 2 * major
        return True

    def generate_next_turns(self, nodes: list[list[PathNode]], target: tuple[int, int],
                            following: list[list[PathNode]] | None = None) -> None:
        """Route._GenerateNextTurn/_GetNextTurn over a completed next map.

        Native reuses the former open-list bit as a visited cache. Following
        checkpoint maps contribute their target node's direction and next turn.
        """
        for row in nodes:
            for node in row:
                node.in_open_list = False
        following_node = following[target[0]][target[1]] if following is not None else None
        target_node = nodes[target[0]][target[1]]
        target_node.in_open_list = True
        target_node.next_turn = following_node.next_turn if following_node else LocalVector2(0, 0)
        threshold = binary32(binary32(1e-5) * binary32(1e-5))

        def visit(node):
            if node.in_open_list:
                return node.next_turn
            node.in_open_list = True
            if not node.has_next:
                node.next_turn = LocalVector2(0, 0)
                return node.next_turn
            if following_node and node.next_grid == following_node.grid:
                next_direction = following_node.safe_next_direction()
                if (next_direction - node.safe_next_direction()).squared_magnitude >= threshold:
                    node.next_turn = next_direction
                else:
                    node.next_turn = following_node.next_turn
                return node.next_turn
            successor = nodes[node.next_grid[0]][node.next_grid[1]]
            next_direction = successor.safe_next_direction()
            if (next_direction - node.safe_next_direction()).squared_magnitude >= threshold:
                node.next_turn = next_direction
            else:
                node.next_turn = visit(successor)
            return node.next_turn

        for row in nodes:
            for node in row:
                visit(node)

    def scope(self) -> dict:
        return {"scope": "native_default_WALK_path_over_explicit_frozen_cached_tile_snapshot",
                "tile_source": self.source, "logical_grid_origin": "bottom",
                "native_neighbor_order": [list(value) for value in FOUR_NEIGHBORS],
                "native_reverse_directions": list(INVERSE_DIRECTIONS),
                "tile_initialization_reconstructed": False,
                "devices_and_dynamic_tile_changes_applied": False,
                "client_runtime_compared": False, "autonomous_route_ready": False, "battle_ready": False}


@dataclass
class CompiledWalkRoute:
    spec: "WalkRouteSpec"
    final_map: list[list[PathNode]]
    checkpoint_maps: tuple[list[list[PathNode]] | None, ...]
    scope: dict


def compile_walk_route(spec: "WalkRouteSpec", grid: NativeWalkPathGrid) -> CompiledWalkRoute:
    """Route.ReconstructRoute's default MOVE/WAIT map and distance closure.

    Unreachable MOVE targets are rejected because their cursor skip semantics
    are outside this path-only compiler. WAIT does not create a next map.
    """
    require(isinstance(spec, WalkRouteSpec), "Expected a validated WALK route")
    final = grid.next_map(spec.end)
    require(final[spec.end[0]][spec.end[1]].is_valid, "Unpassable route end needs unsupported skip/exit context")
    grid.generate_next_turns(final, spec.end)
    following = final
    maps = [None] * len(spec.checkpoints)
    for index in range(len(spec.checkpoints) - 1, -1, -1):
        cp = spec.checkpoints[index]
        if cp.kind == "WAIT_FOR_SECONDS":
            continue
        require(following[cp.grid[0]][cp.grid[1]].is_valid, "MOVE target cannot reach following target in this frozen tile context")
        current = grid.next_map(cp.grid)
        require(current[cp.grid[0]][cp.grid[1]].is_valid, "Unpassable MOVE checkpoint needs unsupported cursor skip context")
        grid.generate_next_turns(current, cp.grid, following)
        distance_suffix = following[cp.grid[0]][cp.grid[1]].distance_to_final
        for row in current:
            for node in row:
                if node.is_valid:
                    distance = node.distance + distance_suffix
                    require(-(1 << 31) <= distance < (1 << 31), "Native route total distance int32 overflow unsupported")
                    node.distance_to_final = distance
        maps[index], following = current, current
    return CompiledWalkRoute(spec, final, tuple(maps), grid.scope())


def _grid(value: dict, label: str, height: int, width: int) -> tuple[int, int]:
    value = obj(value, label)
    require(set(value) == {"row", "col"}, f"{label}: unexpected grid fields")
    row, col = integer(value["row"], label + ".row"), integer(value["col"], label + ".col")
    require(row < height and col < width, f"{label}: outside {height}x{width} map")
    return row, col


@dataclass(frozen=True)
class CheckpointSpec:
    kind: str
    seconds: float
    grid: tuple[int, int]
    reach_offset: LocalVector2
    reach_distance: float


@dataclass(frozen=True)
class WalkRouteSpec:
    """Validated declarations for the currently recovered default WALK branch.

    This is not a path compiler. Tile costs/passability and controller runtime
    context must be supplied to a separately proved implementation.
    """

    start: tuple[int, int]
    end: tuple[int, int]
    spawn_offset: LocalVector2
    checkpoints: tuple[CheckpointSpec, ...]

    @classmethod
    def from_json(cls, route: dict, *, height: int, width: int) -> "WalkRouteSpec":
        route = obj(route, "route")
        integer(height, "height", minimum=1)
        integer(width, "width", minimum=1)
        expected = {"motionMode", "startPosition", "endPosition", "spawnOffset", "spawnRandomRange",
                    "checkpoints", "allowDiagonalMove", "visitEveryTileCenter",
                    "visitEveryNodeCenter", "visitEveryCheckPoint"}
        require(set(route) == expected, "Route has missing or unrecovered fields")
        require(route["motionMode"] == "WALK", "Only default WALK declarations are supported")
        require(route["allowDiagonalMove"] is True, "Nondiagonal smoothing branch is unrecovered")
        for key in ("visitEveryTileCenter", "visitEveryNodeCenter", "visitEveryCheckPoint"):
            require(route[key] is False, f"{key}: route cursor branch is unrecovered")
        random_range = LocalVector2.from_json(route["spawnRandomRange"], "spawnRandomRange")
        require(random_range == LocalVector2(0, 0), "Nonzero spawn random range needs explicit RNG state")
        checkpoints = []
        cp_fields = {"type", "time", "position", "reachOffset", "randomizeReachOffset", "reachDistance"}
        for index, cp in enumerate(array(route["checkpoints"], "checkpoints")):
            label = f"checkpoint[{index}]"
            cp = obj(cp, label)
            require(set(cp) == cp_fields, f"{label}: missing or unrecovered fields")
            require(cp["type"] in ("MOVE", "WAIT_FOR_SECONDS"), f"{label}: unsupported checkpoint {cp['type']}")
            require(cp["randomizeReachOffset"] is False, f"{label}: randomized reach offset needs RNG context")
            seconds = binary32(number(cp["time"], label + ".time", minimum=0))
            reach_distance = binary32(number(cp["reachDistance"], label + ".reachDistance", minimum=0))
            require(math.isfinite(seconds) and math.isfinite(reach_distance), f"{label}: binary32 overflow")
            checkpoints.append(CheckpointSpec(cp["type"], seconds,
                _grid(cp["position"], label + ".position", height, width),
                LocalVector2.from_json(cp["reachOffset"], label + ".reachOffset"), reach_distance))
        return cls(_grid(route["startPosition"], "route.startPosition", height, width),
                   _grid(route["endPosition"], "route.endPosition", height, width),
                   LocalVector2.from_json(route["spawnOffset"], "spawnOffset"), tuple(checkpoints))

    def scope(self) -> dict:
        return {"coordinate_space": "local_map_float32", "logical_grid_origin": "bottom",
                "checkpoint_kinds": sorted({cp.kind for cp in self.checkpoints}),
                "wait_timer": "signed_FP_Q32_32_countdown",
                "path_algorithm": "native_weighted_SPFA_and_Bresenham_smoothing_required",
                "spawn_zero_range_rng_consumption_validated": False,
                "autonomous_route_ready": False, "battle_ready": False,
                "unresolved": ["tile_runtime_context", "controller_forces_and_initial_state",
                               "prediction_and_position_determinism", "mode_exit_permission",
                               "device_effects_and_dynamic_obstacles"]}

"""Static native movement rules over an explicit, frozen runtime context.

This module never promotes a declared map to cached tile state. It supplies no
combat, device effects, hotfix dispatch, animation, spatial index or mode life
state. Those owners must provide their verified context to a caller.
"""
from __future__ import annotations

from dataclasses import dataclass, replace
import math

from .data import require, integer, number
from .fp import FP, binary32
from .movement import (LocalVector2, NativeTileSnapshot, NativeWalkPathGrid, CompiledWalkRoute,
                       WaitCheckpoint, grid_to_local, local_to_grid,
                       check_distance, vector_is_zero, clamp_magnitude,
                       normalize_direction_safely)

ZERO = LocalVector2(0, 0)
EIGHT_NEIGHBORS = ((1, 0), (1, 1), (0, 1), (-1, 1),
                   (-1, 0), (-1, -1), (0, -1), (1, -1))


@dataclass(frozen=True)
class TileOptions:
    """Unboxed native Tile.Options fields, distinct from declared TileData."""
    buildable_type: int
    passable_mask: int
    override_obstacle_move_cost: bool
    advanced_build_mask: int
    height_type: int
    force_set_height_type: bool

    def __post_init__(self):
        for name in ("buildable_type", "passable_mask", "advanced_build_mask", "height_type"):
            integer(getattr(self, name), "TileOptions." + name)
        require(self.passable_mask <= 3, "Unsupported motion mask")
        require(type(self.override_obstacle_move_cost) is bool and type(self.force_set_height_type) is bool,
                "TileOptions native bools required")


@dataclass(frozen=True)
class _EffectiveTileSnapshot(NativeTileSnapshot):
    native_move_cost: int

    @property
    def move_cost(self):
        return self.native_move_cost


@dataclass(frozen=True)
class TileRuntimeCache:
    native_type: str
    origin: TileOptions
    cached: TileOptions
    walk_goto_mask: int
    source: str

    @property
    def move_cost(self):
        if self.native_type == "Torappu.Battle.HoleTile":
            return 1000000  # native override 0x1808addd0, independent of +98
        return 1000 if self.cached.override_obstacle_move_cost else 1

    def snapshot(self) -> NativeTileSnapshot:
        return _EffectiveTileSnapshot(self.cached.passable_mask, self.walk_goto_mask,
            self.cached.override_obstacle_move_cost, self.move_cost > 999, self.move_cost)


def initialize_cached_tile(*, native_type: str, buildable_type: int, passable_mask: int,
                           advanced_build_mask: int, height_type: int,
                           walk_goto_mask: int, source: str) -> TileRuntimeCache:
    """Tile.Init default, after caller-supplied rune preprocessing.

    Inputs are the actual processed TileData values; passing a prefab's _data
    defaults is incorrect. Advanced mask is TileData+28, not playerSideMask
    (+24). Goto restrictions are separately built by Map and are mandatory.
    Supports base Tile and the proved HoleTile overrides. No other derived
    type or hotfix dispatch is silently approximated.
    """
    require(native_type in ("Torappu.Battle.Tile", "Torappu.Battle.HoleTile"),
            "Unrecovered Tile subclass/context")
    require(isinstance(source, str) and bool(source.strip()), "Processed TileData source required")
    require(type(walk_goto_mask) is int and 0 <= walk_goto_mask <= 15, "Explicit WALK goto mask required")
    options = TileOptions(buildable_type, passable_mask, False, advanced_build_mask, height_type, True)
    return TileRuntimeCache(native_type, options, options, walk_goto_mask, source)


def rewrite_cached_tile(cache: TileRuntimeCache, options: TileOptions, *,
                        keep_passable_mask: bool, keep_buildable_type: bool,
                        ignore_block_any_routes: bool, batching: bool,
                        routes_reachable: bool | None, source: str):
    """TryUpdateOptions / RewriteOptions in a fixed tile context.

    Returns (new_cache, dirty_motion_mask, accepted). The caller owns route
    rebuild/update-passable ordering and the global all-routes-reachable check.
    A rejected rewrite restores originOptions, not the preceding cached value.
    """
    require(isinstance(cache, TileRuntimeCache) and isinstance(options, TileOptions), "Explicit native tile cache/options required")
    require(all(type(v) is bool for v in (keep_passable_mask, keep_buildable_type, ignore_block_any_routes, batching)),
            "Tile rewrite branch inputs require explicit bools")
    require(isinstance(source, str) and bool(source.strip()), "Tile rewrite source required")
    if keep_passable_mask:
        options = replace(options, passable_mask=cache.cached.passable_mask)
    if keep_buildable_type:
        options = replace(options, buildable_type=cache.cached.buildable_type)
    if not options.force_set_height_type:
        options = replace(options, height_type=cache.cached.height_type)
    new = replace(cache, cached=options, source=cache.source + " → " + source)
    dirty = (cache.cached.passable_mask ^ options.passable_mask) & 3
    if new.move_cost != cache.move_cost:
        dirty |= 1
    if dirty and not batching and not ignore_block_any_routes:
        require(type(routes_reachable) is bool, "Native all-routes-reachable outcome is required for this rewrite")
        if not routes_reachable:
            return replace(new, cached=cache.origin), dirty, False
    return new, dirty, True


def build_cached_walk_grid(rows: list[list[TileRuntimeCache]], *, source: str) -> NativeWalkPathGrid:
    require(isinstance(rows, list) and all(isinstance(row, list) for row in rows), "Logical tile cache rows required")
    require(all(isinstance(tile, TileRuntimeCache) for row in rows for tile in row), "Every tile requires native cache initialization")
    return NativeWalkPathGrid([[tile.snapshot() for tile in row] for row in rows], source=source)


def deterministic_position(position: LocalVector2, enabled: bool) -> LocalVector2:
    """Single→Double, Round(Double*10^4,ToEven)/10^4, Double→Single.

    DeterministicUtil 0x180af56e0 / Math.Round 0x185ebaf20. The native
    roundLimit is 1e16; this finite coordinate implementation keeps scaled
    values within an exactly representable integer, avoiding CLR overflow
    and exotic NaN paths. It is deliberately not Python round(x,4).
    """
    require(type(enabled) is bool, "deterministic flag needs explicit bool")
    if not enabled:
        return position
    require(max(abs(position.x), abs(position.y)) < 1e11,
            "Deterministic coordinate exceeds the supported finite range")

    def axis(value):
        scaled = float(value) * 10000.0
        rounded = float(round(scaled))
        if rounded == 0:
            rounded = math.copysign(0.0, value)
        return binary32(rounded / 10000.0)

    return LocalVector2(axis(position.x), axis(position.y))


class PeriodicTicker:
    """Recovered Tick/Next counter; period is a call count, not seconds."""
    def __init__(self, interval: int = 3):
        self.interval = integer(interval, "Ticker interval", minimum=1)
        self.remaining = 0

    def tick(self) -> bool:
        if self.remaining > 0:
            self.remaining -= 1
        return self.remaining == 0

    def next(self) -> bool:
        if self.remaining != 0:
            return False
        self.remaining = self.interval
        return True


def obstacle_avoid_force(grid: NativeWalkPathGrid, offset_position: LocalVector2,
                         foot_position: LocalVector2, *, half_body_width: float) -> LocalVector2:
    """0x1808b6af0, including native 8-neighbor order and integer Abs.

    The controller's half-body width is serialized (ctor initializes .2). The foot position
    comes from its cached OnStart foot offset, and grid lookup uses the cursor
    locator (offset position), not the foot position.
    """
    radius = binary32(number(half_body_width, "Controller half-body width", minimum=0))
    current = local_to_grid(offset_position)
    if not grid.valid_grid(current):
        return ZERO
    if not grid.tiles[current[0]][current[1]].walk_passable:
        distance, answer = binary32(3.4028234663852886e38), ZERO
        for dr, dc in EIGHT_NEIGHBORS:
            neighbor = current[0] + dr, current[1] + dc
            if not grid.valid_grid(neighbor) or not grid.tiles[neighbor[0]][neighbor[1]].walk_passable:
                continue
            candidate = (offset_position - grid_to_local(neighbor)).squared_magnitude
            if candidate < distance:  # strict comparison retains first tie
                distance, answer = candidate, LocalVector2(dc, dr)
        return answer  # native returns the grid delta without normalization
    center, answer = grid_to_local(current), ZERO
    for dr, dc in EIGHT_NEIGHBORS:
        neighbor = current[0] + dr, current[1] + dc
        if not grid.valid_grid(neighbor):
            continue
        tile = grid.tiles[neighbor[0]][neighbor[1]]
        if tile.walk_passable and not tile.is_obstacle_like:
            continue
        edge_x = binary32(foot_position.x + binary32(binary32(dc) * radius))
        # Raw MULSS multiplies radius by ZERO on y; preserve its rounding.
        edge_y = binary32(foot_position.y + binary32(radius * 0.0))
        px = max(0.0, binary32(binary32(edge_x - center.x) * binary32(dc)))
        py = max(0.0, binary32(binary32(edge_y - center.y) * binary32(dr)))
        px = binary32(binary32(abs(dc)) * binary32(px - binary32(.25)))
        py = binary32(binary32(abs(dr)) * binary32(py - binary32(.25)))
        if px > 0 and py > 0:
            px = py = binary32(binary32(px + py) * binary32(.5))
        elif abs(dr) + abs(dc) != 1 or (px <= 0 and py <= 0):
            continue
        x = binary32(binary32(-px) * binary32(dc))
        y = binary32(binary32(-py) * binary32(dr))
        answer = LocalVector2(binary32(binary32(x + x) + answer.x),
                              binary32(binary32(y + y) + answer.y))
    return answer.normalized()


class NativeDirectionCursor:
    """Default MOVE/WAIT cursor, all optional visitation flags false."""
    def __init__(self, route: CompiledWalkRoute, grid: NativeWalkPathGrid,
                 *, offset: LocalVector2, initial_position: LocalVector2,
                 always_check_current_point: bool):
        require(isinstance(route, CompiledWalkRoute), "Compiled WALK route required")
        require(isinstance(grid, NativeWalkPathGrid), "Explicit cached tile snapshot required")
        require(isinstance(offset, LocalVector2), "Explicit cursor offset required")
        require(isinstance(initial_position, LocalVector2), "Cursor's object initial position required")
        require(type(always_check_current_point) is bool, "alwaysCheckCurrentPoint requires explicit prefab state")
        self.route, self.grid, self.offset = route, grid, offset
        self.always_check_current_point = always_check_current_point
        # BasicCursor constructor derives this additional flag from count,
        # independently of the three route JSON visitation flags.
        self.visit_every_node_stably = len(route.spec.checkpoints) == 0
        self.next_grid = local_to_grid(initial_position)
        self.checkpoint_index = 0
        self.waits = [WaitCheckpoint(cp.seconds) if cp.kind == "WAIT_FOR_SECONDS" else None
                      for cp in route.spec.checkpoints]
        self._begin()

    def _begin(self):
        if self.checkpoint_index < len(self.waits) and self.waits[self.checkpoint_index] is not None:
            self.waits[self.checkpoint_index].begin()

    def _next(self):
        self.checkpoint_index += 1
        self._begin()

    def locator(self, position: LocalVector2) -> LocalVector2:
        return position + self.offset

    def _at(self, nodes, locator):
        p = local_to_grid(locator)
        require(self.grid.valid_grid(p), "Cursor locator outside map needs native go-back context")
        return nodes[p[0]][p[1]]

    def _checkpoint_reached(self, locator):
        cp = self.route.spec.checkpoints[self.checkpoint_index]
        if cp.kind == "WAIT_FOR_SECONDS":
            return self.waits[self.checkpoint_index].is_reached
        nodes = self.route.checkpoint_maps[self.checkpoint_index]
        p = local_to_grid(locator)
        # Default alwaysCheckCurrentPoint=false: invalid/unreachable skips MOVE.
        if not self.always_check_current_point and (not self.grid.valid_grid(p) or not nodes[p[0]][p[1]].is_valid):
            return True
        target = grid_to_local(cp.grid) + cp.reach_offset
        return check_distance(locator, target, max(binary32(.05), cp.reach_distance))

    def tick(self, delta: FP, position: LocalVector2, *, check_reached: bool):
        require(type(check_reached) is bool, "Cursor check_reached requires explicit bool")
        if self.checkpoint_index >= len(self.route.spec.checkpoints):
            return
        timer = self.waits[self.checkpoint_index]
        if timer is not None:
            timer.tick(delta)
        if check_reached and self._checkpoint_reached(self.locator(position)):
            self._next()  # OnTick advances at most one checkpoint

    def _next_grid(self, at):
        require(self.grid.valid_grid(at), "Stable cursor grid outside supported map")
        node = self.route.final_map[at[0]][at[1]]
        return node.next_grid if node.is_valid and node.has_next else node.grid

    def _stable_target(self, position):
        if not self.visit_every_node_stably:
            return None
        locator = self.locator(position)
        current = local_to_grid(locator)
        require(self.grid.valid_grid(current), "Stable cursor locator outside supported map")
        if current != self.next_grid:
            self.next_grid = self._next_grid(current)
        if self.grid.valid_grid(self.next_grid) and self.grid.tiles[self.next_grid[0]][self.next_grid[1]].walk_passable:
            target = grid_to_local(self.next_grid)
            if not check_distance(locator, target, .25):
                return target
            self.next_grid = self._next_grid(self.next_grid)
        return None

    def _locator_target(self, position) -> LocalVector2:
        stable = self._stable_target(position)
        if stable is not None:
            return stable
        # _GetNextTarget scans future position-related checkpoints, skips WAIT
        # without mutating the cursor, and does not consult the path next grid.
        for cp in self.route.spec.checkpoints[self.checkpoint_index:]:
            if cp.kind == "MOVE":
                return grid_to_local(cp.grid) + cp.reach_offset
        return grid_to_local(self.route.spec.end)

    def next_target(self, position: LocalVector2) -> LocalVector2:
        return self._locator_target(position) - self.offset

    def predict_reached(self, position: LocalVector2, step: float):
        locator_target = self._locator_target(position)
        target = locator_target - self.offset
        delta = locator_target - self.locator(position)
        direction = delta.normalized()
        step = binary32(number(step, "Prediction step", minimum=0))
        return delta.squared_magnitude <= binary32(step * step), direction, target

    def direction(self, position: LocalVector2) -> LocalVector2:
        locator = self.locator(position)
        require(self.grid.valid_grid(local_to_grid(locator)), "Cursor outside map needs native go-back context")
        stable = self._stable_target(position)
        if stable is not None:
            return (stable - locator).normalized()
        while self.checkpoint_index < len(self.route.spec.checkpoints):
            cp = self.route.spec.checkpoints[self.checkpoint_index]
            if cp.kind == "WAIT_FOR_SECONDS":
                direction = ZERO
            else:
                node = self._at(self.route.checkpoint_maps[self.checkpoint_index], locator)
                target = node.safe_next_position()
                if (node.next_grid if node.is_valid and node.has_next else node.grid) == cp.grid:
                    target = target + cp.reach_offset
                direction = (target - locator).normalized() if node.is_valid else ZERO
            if not self._checkpoint_reached(locator):
                return direction
            self._next()  # GetNextDirection can advance several reached checkpoints
        node = self._at(self.route.final_map, locator)
        return (node.safe_next_position() - locator).normalized() if node.is_valid else ZERO

    def reached_exit(self, position: LocalVector2) -> bool:
        locator = self.locator(position)
        return (local_to_grid(locator) == self.route.spec.end and
                (locator - grid_to_local(self.route.spec.end)).squared_magnitude <= binary32(.0025000002))

    def snapshot(self):
        return {"checkpoint_index": self.checkpoint_index,
                "visit_every_node_stably": self.visit_every_node_stably,
                "next_grid": list(self.next_grid),
                "always_check_current_point": self.always_check_current_point,
                "wait_remaining_raw": (self.waits[self.checkpoint_index].remaining.raw
                    if self.checkpoint_index < len(self.waits) and self.waits[self.checkpoint_index] else None)}


@dataclass(frozen=True)
class MovementContext:
    """Explicit runtime branches. No boolean silently selects a client default."""
    source: str
    deterministic: bool
    new_steering: bool
    foot_offset: LocalVector2
    initial_steering: float
    max_force: float
    half_body_width: float
    conveyor_present: bool
    always_check_current_point: bool

    def __post_init__(self):
        require(isinstance(self.source, str) and bool(self.source.strip()), "Movement context source required")
        require(all(type(v) is bool for v in (self.deterministic, self.new_steering, self.conveyor_present, self.always_check_current_point)),
                "Movement runtime flags require explicit bools")
        require(isinstance(self.foot_offset, LocalVector2), "OnStart cached foot offset required")
        for name in ("initial_steering", "max_force", "half_body_width"):
            object.__setattr__(self, name, binary32(number(getattr(self, name), name, minimum=0)))
            require(math.isfinite(getattr(self, name)), f"{name}: binary32 overflow")
        require(not self.conveyor_present, "Conveyor displacement is not yet supported")


class NativeMoveController:
    """Native acceleration / avoidance / ClampMagnitude with explicit flags."""
    def __init__(self, grid: NativeWalkPathGrid, context: MovementContext):
        self.grid, self.context = grid, context
        self.velocity, self.last_avoid = ZERO, ZERO
        self.ticker = PeriodicTicker(3)

    def calculate_delta(self, direction: LocalVector2, delta: float, *, speed: float,
                        position: LocalVector2, offset_position: LocalVector2,
                        can_move: bool):
        require(type(can_move) is bool, "can_move requires explicit native state")
        speed = binary32(number(speed, "Runtime move speed", minimum=0))
        delta = binary32(number(delta, "Movement delta", minimum=0))
        if speed <= binary32(1e-5) or not can_move:
            return ZERO, True  # retain velocity and timer on this early branch
        direction = direction.normalized()
        if self.ticker.tick():
            avoid = obstacle_avoid_force(self.grid, offset_position, position + self.context.foot_offset,
                                         half_body_width=self.context.half_body_width)
            dot = binary32(binary32(avoid.y * direction.y) + binary32(avoid.x * direction.x))
            self.last_avoid = avoid - direction.scale(dot)
            self.ticker.next()
        ratio = binary32(self.velocity.magnitude / speed)
        correction = self.last_avoid.scale(max(binary32(.5), ratio))
        still = vector_is_zero(direction) and vector_is_zero(correction)
        factor, limit = (self.context.initial_steering, self.context.max_force) if self.context.new_steering else (binary32(100), binary32(100))
        force = clamp_magnitude((direction.scale(speed) - self.velocity).scale(factor) + correction, limit)
        self.velocity = clamp_magnitude(self.velocity + force.scale(delta), speed)
        return self.velocity.scale(delta), still


class NativeRouteMover:
    """_MoveByCursor's physical update; caller owns FSM/cursor tick order.

    The actual position is Single local-map x,y, while WAIT is separately FP.
    Constructor position/offset must come from a verified creation context.
    Zero spawn-random range still consumes RNG in the native creation path;
    this component receives the already resolved spawn position and does not
    silently seed or dispatch the battle RNG.
    """
    def __init__(self, route: CompiledWalkRoute, grid: NativeWalkPathGrid,
                 context: MovementContext, *, position: LocalVector2,
                 cursor_offset: LocalVector2):
        require(isinstance(context, MovementContext) and isinstance(grid, NativeWalkPathGrid),
                "Explicit movement and cached-map contexts required")
        require(isinstance(position, LocalVector2), "Explicit post-Init position required")
        require(grid.valid_grid(local_to_grid(position)), "Initial position outside supported map context")
        self.position = position
        self.cursor = NativeDirectionCursor(route, grid, offset=cursor_offset,
            initial_position=position, always_check_current_point=context.always_check_current_point)
        self.controller = NativeMoveController(grid, context)
        self.context, self.grid = context, grid
        self.direction, self.still = ZERO, True
        self.current_frame, self.time_raw, self.exit_requested = 0, 0, False
        self.last_update = {"kind": "initialized", "position_assignment_applied": False}

    def move_by_cursor(self, delta: float, *, speed: float, can_move: bool,
                       actually_ground_bound: bool):
        require(type(actually_ground_bound) is bool, "Ground-bound state requires explicit bool")
        require(type(can_move) is bool, "can_move requires explicit bool")
        delta = binary32(number(delta, "_MoveByCursor delta", minimum=0))
        speed = binary32(number(speed, "Resolved runtime speed", minimum=0))
        require(math.isfinite(delta) and math.isfinite(speed), "Movement input binary32 overflow")
        if actually_ground_bound:
            self.direction, self.still = ZERO, True
            self.last_update = {"kind": "ground_bound", "position_assignment_applied": False}
            return self.snapshot()
        old_grid = local_to_grid(self.position)
        require(self.grid.valid_grid(old_grid), "Native outside-map go-back context is unsupported")
        predicted, direction, target = self.cursor.predict_reached(self.position, binary32(speed * delta))
        if predicted:
            displacement = deterministic_position(target - self.position, self.context.deterministic)
            self.position = deterministic_position(target, self.context.deterministic)
            self.direction = direction
            self.still = vector_is_zero(direction) or vector_is_zero(displacement)
            self.last_update = {"kind": "predicted_reach", "position_assignment_applied": True,
                                "controller_velocity_updated": False}
            return self.snapshot()
        direction = self.cursor.direction(self.position)
        movement, still = self.controller.calculate_delta(direction, delta, speed=speed,
            position=self.position, offset_position=self.cursor.locator(self.position), can_move=can_move)
        candidate = self.position + movement
        new_grid = local_to_grid(candidate)
        reflected = False
        if new_grid != old_grid:
            require(self.grid.valid_grid(new_grid), "Movement entering outside map needs native go-back context")
            if not self.grid.tiles[new_grid[0]][new_grid[1]].walk_passable:
                normal = (grid_to_local(new_grid) - self.position).normalized()
                dot = binary32(binary32(movement.x * normal.x) + binary32(movement.y * normal.y))
                twice = binary32(dot + dot)
                movement = movement - normal.scale(twice)
                reflected = True
        self.position = deterministic_position(self.position + movement, self.context.deterministic)
        self.direction, self.still = normalize_direction_safely(direction), still
        self.last_update = {"kind": "controller_move", "position_assignment_applied": True,
                            "controller_velocity_updated": can_move and speed > binary32(1e-5),
                            "reflected_unpassable_entry": reflected}
        return self.snapshot()

    def tick(self, delta: FP, *, speed: float, move_state_tick: bool,
             alive_after_unit_tick: bool, can_move: bool, actually_ground_bound: bool,
             check_cursor_reached: bool, exit_allowed: bool):
        """Recovered relative Unit/FSM movement→Enemy cursor→exit ordering.

        The lifecycle owner must report whether the *pre-tick* FSM dispatch
        executed MoveState's default no-target/no-abnormal branch. Born→Move
        does not run MoveState within that same tick. Enemy.OnTick advances the
        cursor after the Unit/FSM tick whenever its post-Unit alive gate passes;
        this includes a still-active BornState. Exit permission is external to
        geometry; the returned exit request needs the real mode/lifecycle owner.
        """
        require(isinstance(delta, FP) and delta.raw > 0, "Movement tick requires positive FP delta")
        require(all(type(v) is bool for v in (move_state_tick, alive_after_unit_tick, can_move,
                    actually_ground_bound, check_cursor_reached, exit_allowed)),
                "Tick requires explicit native state/gate outcomes")
        require(not self.exit_requested, "Exit already requested; lifecycle owner must consume it before another tick")
        self.current_frame += 1
        self.time_raw = (FP.from_raw(self.time_raw) + delta).raw
        if move_state_tick:
            self.move_by_cursor(delta.as_float(), speed=speed, can_move=can_move,
                                actually_ground_bound=actually_ground_bound)
        else:
            self.last_update = {"kind": "no_move_state_dispatch", "position_assignment_applied": False}
        # EnemyStateMachine.OnTick's default tail reads Transform.localPosition
        # and invokes slot13 _AssignLocalPosInternal when deterministic=true.
        # This occurs even if Born/another state did not move this frame.
        if self.context.deterministic:
            self.position = deterministic_position(self.position, True)
        self.last_update["fsm_position_reassigned"] = self.context.deterministic
        if alive_after_unit_tick:
            self.cursor.tick(delta, self.position, check_reached=check_cursor_reached)
            if self.cursor.reached_exit(self.position) and exit_allowed:
                self.exit_requested = True
        return self.snapshot()

    def snapshot(self):
        return {"position": [self.position.x, self.position.y],
                "locator_position": [self.cursor.locator(self.position).x, self.cursor.locator(self.position).y],
                "velocity": [self.controller.velocity.x, self.controller.velocity.y],
                "direction": [self.direction.x, self.direction.y], "still": self.still,
                "cursor": self.cursor.snapshot(), "reached_exit_geometry": self.cursor.reached_exit(self.position),
                "current_frame": self.current_frame, "time_raw": self.time_raw,
                "exit_requested": self.exit_requested,
                "last_update": dict(self.last_update), "runtime_battle_validated": False,
                "battle_ready": False}

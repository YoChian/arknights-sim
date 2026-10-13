"""Bounded NPC restore and Enemy.DisappearState execution.

The native default, deterministic branch is modeled. Unity existence, event/
Buff dispatch, modifier effects, route construction and DOTween execution are
explicit providers. This component never claims a complete Enemy or Unity FSM.
"""
from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass, field
import math

from .coroutines import fixed_seconds
from .fp import FP, binary32
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator


class UnverifiedRestoreContext(ValueError):
    pass


def _require(value, message):
    if not value:
        raise UnverifiedRestoreContext(message)


def _flag(value, name):
    _require(type(value) is bool, name + " must be an explicit Boolean")
    return value


def _color(value):
    _require(isinstance(value, tuple) and len(value) == 4, "RGBA tuple required")
    value = tuple(binary32(x) for x in value)
    _require(all(math.isfinite(x) for x in value), "finite RGBA values required")
    return value


def color_segment(base_color, progress: float, kind: str):
    """Exact native setter arithmetic; easing/progress comes from a provider."""
    base = _color(base_color)
    p = binary32(progress)
    _require(math.isfinite(p), "finite tween setter input required")
    if kind == "rgb":
        return tuple(binary32(x * p) for x in base[:3]) + (base[3],)
    if kind == "alpha":
        return (0.0, 0.0, 0.0, binary32(base[3] * p))
    raise UnverifiedRestoreContext("unknown native color setter")


@dataclass(frozen=True)
class RestoreRoute:
    token: str
    checkpoint_count: int
    visit_every_tile_center: bool
    visit_every_node_center: bool
    source: str
    runtime_ready: bool = True

    def __post_init__(self):
        _require(bool(self.token) and bool(self.source), "prepared route identity/source required")
        _require(type(self.checkpoint_count) is int and self.checkpoint_count >= 0,
                 "checkpoint count must be a nonnegative Int32")
        _require(self.checkpoint_count < (1 << 31), "checkpoint count exceeds Int32")
        for n in ("visit_every_tile_center", "visit_every_node_center", "runtime_ready"):
            _flag(getattr(self, n), n)
        _require(self.runtime_ready, "uninitialized native Route is outside this component")


@dataclass
class RestoreCursor:
    route: RestoreRoute
    cursor_index: int
    cached_direction: tuple[float, float] = (0.0, 0.0)
    visit_every_tile_center: bool = False
    visit_every_node_center: bool = False
    visit_every_node_stably: bool = True
    visited_map: tuple = ()
    checkpoint_objects: tuple = ()

    def validate(self):
        _require(isinstance(self.route, RestoreRoute), "prepared current route required")
        _require(type(self.cursor_index) is int and -(1 << 31) <= self.cursor_index < (1 << 31),
                 "cursor progress is a native Int32")
        for n in ("visit_every_tile_center", "visit_every_node_center", "visit_every_node_stably"):
            _flag(getattr(self, n), n)
        _require(isinstance(self.cached_direction, tuple) and len(self.cached_direction) == 2,
                 "cached direction tuple required")
        _require(isinstance(self.visited_map, tuple) and isinstance(self.checkpoint_objects, tuple),
                 "explicit immutable cursor snapshots required")
        if self.visited_map:
            _require(all(isinstance(row, tuple) and len(row) == len(self.visited_map[0])
                         and all(type(x) is bool for x in row) for row in self.visited_map)
                     and len(self.visited_map[0]) > 0,
                     "visited-map snapshot must be a rectangular Boolean array matching the current native Map")


@dataclass(frozen=True)
class TweenRequest:
    kind: str
    base_color: tuple[float, float, float, float]
    # Both use Append, not Join: two sequential 0.15f segments.
    segments: tuple[tuple[str, float, float], ...]
    source: str
    setter: Callable[[str, float], None] = field(compare=False, repr=False)


@dataclass(frozen=True)
class TweenTicket:
    token: str
    source: str

    def __post_init__(self):
        _require(bool(self.token) and bool(self.source), "explicit Tween backend ticket/source required")


@dataclass(eq=False)
class NpcRestoreActor:
    token: str
    uid: int
    unity_exists: bool
    is_enemy: bool
    is_giant_boss: bool
    grid_position: tuple[int, int]
    is_disappeared: bool
    game_active: bool
    state_id: int
    cursor: RestoreCursor | None
    disable_appear_tween_color: bool = False
    body_color: tuple[float, float, float, float] = (1.0, 1.0, 1.0, 1.0)
    pull_sources: tuple = ()
    disabled_pull_sources: tuple = ()
    blocker_valid: bool = False
    block_tween: TweenTicket | None = None
    # Explicit current animator.color snapshot, distinct from GetBodyColor.
    render_color: tuple[float, float, float, float] | None = None
    coroutine_handle: int = 0
    disappear_tween: TweenTicket | None = None
    state_modifier_applied: bool = False
    _owner: CoroutineOwner | None = field(default=None, repr=False)

    def validate(self):
        _require(bool(self.token), "actor identity/source required")
        _require(type(self.uid) is int and 0 <= self.uid < (1 << 32), "UID must be UInt32")
        for n in ("unity_exists", "is_enemy", "is_giant_boss", "is_disappeared", "game_active",
                  "disable_appear_tween_color", "blocker_valid", "state_modifier_applied"):
            _flag(getattr(self, n), n)
        _require(type(self.state_id) is int, "explicit initialized state required")
        _require(isinstance(self.grid_position, tuple) and len(self.grid_position) == 2
                 and all(type(x) is int and -(1 << 31) <= x < (1 << 31) for x in self.grid_position),
                 "explicit (row,col) Int32 grid position required")
        self.body_color = _color(self.body_color)
        if self.render_color is None:
            raise UnverifiedRestoreContext("current animator color must be supplied separately")
        self.render_color = _color(self.render_color)
        _require(isinstance(self.pull_sources, tuple) and isinstance(self.disabled_pull_sources, tuple),
                 "explicit ListSet source snapshots required")
        _require(len(set(self.pull_sources)) == len(self.pull_sources), "pull ListSet snapshot must be unique")
        if self.cursor is not None:
            self.cursor.validate()


@dataclass(frozen=True)
class NpcRestoreContext:
    source: str
    native_default_no_hotfix: bool
    deterministic: bool
    delta_play_time_float: float
    default_move_registered: bool
    active_hierarchy_matches_self: bool

    def __post_init__(self):
        _require(bool(self.source), "execution context provenance required")
        for n in ("native_default_no_hotfix", "deterministic", "default_move_registered",
                  "active_hierarchy_matches_self"):
            _require(_flag(getattr(self, n), n), n + " must be true for the supported branch")
        dt = binary32(self.delta_play_time_float)
        _require(math.isfinite(dt) and dt > 0, "positive native deltaPlayTime Single required")
        object.__setattr__(self, "delta_play_time_float", dt)


@dataclass(frozen=True)
class RestoreCallbacks:
    set_active: Callable
    set_grid_position: Callable
    apply_state_modifier: Callable
    tween_start: Callable
    tween_kill: Callable
    face_from_cursor: Callable
    move_tick: Callable
    before_disappear: Callable
    disappear_changed: Callable
    set_color: Callable
    # Explicit admitted FSM/Move hook adapter. Called before Disappear.OnEnter
    # for 1->11, after Disappear.OnExit for 11->1. Must return exact True.
    state_transition: Callable
    release_blocker: Callable | None = None
    kill_block_tween: Callable | None = None
    # Nonempty routes: native Route.GetCheckpointNextMap/_CreateCheckpoint/
    # DirectionCursor.Reset/OnBegin behavior is supplied explicitly.
    rebuild_and_reset_cursor: Callable | None = None

    def __post_init__(self):
        for n in ("set_active", "set_grid_position", "apply_state_modifier", "tween_start",
                  "tween_kill", "face_from_cursor", "move_tick", "before_disappear",
                  "disappear_changed", "set_color", "state_transition"):
            _require(callable(getattr(self, n)), "explicit provider required: " + n)


class NpcRestoreRuntime:
    def __init__(self, context: NpcRestoreContext, simulator: SharedCoroutineSimulator,
                 clock: Callable, callbacks: RestoreCallbacks):
        _require(isinstance(context, NpcRestoreContext) and isinstance(simulator, SharedCoroutineSimulator),
                 "native context and shared deterministic simulator required")
        _require(callable(clock) and isinstance(callbacks, RestoreCallbacks), "clock/callback context required")
        self.context, self.simulator, self.clock, self.callbacks = context, simulator, clock, callbacks
        self.events: list[dict] = []

    def _event(self, actor, kind, **details):
        frame, raw = self.clock()
        _require(type(frame) is int and type(raw) is int, "clock returns (frame,FP raw time)")
        self.events.append(dict(frame=frame, time_raw=raw, actor=actor.token, kind=kind, **details))

    def _owner(self, actor):
        if actor._owner is None:
            actor._owner = CoroutineOwner(actor.unity_exists, actor.game_active)
        actor._owner.exists, actor._owner.active_in_hierarchy = actor.unity_exists, actor.game_active
        return actor._owner

    def sync_owner(self, actor):
        """Caller must resupply Unity existence/active hierarchy changes before ticks."""
        actor.validate()
        self._owner(actor)

    def _set_active(self, actor, value):
        self.callbacks.set_active(actor, value)
        actor.game_active = value
        self._owner(actor)
        self._event(actor, "set_active", value=value)

    def _set_color(self, actor, value):
        value = _color(value)
        self.callbacks.set_color(actor, value)
        actor.render_color = value
        self._event(actor, "set_color", value=value)

    def _start_tween(self, actor, kind, base):
        target = binary32(0.0 if kind == "disappear" else 1.0)
        sequence = ("rgb", "alpha") if kind == "disappear" else ("alpha", "rgb")
        request = TweenRequest(kind, base, tuple((name, target, binary32(.15)) for name in sequence),
                               self.context.source,
                               lambda name, p: self._set_color(actor, color_segment(base, p, name)))
        ticket = self.callbacks.tween_start(actor, request)
        _require(isinstance(ticket, TweenTicket), "backend must return a source-backed TweenTicket")
        self._event(actor, "tween_start", tween_kind=kind, token=ticket.token)
        return ticket

    def _kill_tween(self, actor, ticket):
        # DOTween.Kill(null,true) is a native permitted no-op.
        if ticket is not None:
            self.callbacks.tween_kill(actor, ticket, True)
            self._event(actor, "tween_kill", token=ticket.token, complete=True)

    def _do_disappear(self, actor):
        actor.disappear_tween = self._start_tween(actor, "disappear", actor.render_color)
        yield fixed_seconds(binary32(.3), self.context.delta_play_time_float)
        self._kill_tween(actor, actor.disappear_tween)
        self._set_active(actor, False)

    def _enter(self, actor):
        self.callbacks.apply_state_modifier(actor, True)
        actor.state_modifier_applied = True
        self._event(actor, "modifier_add")
        actor.state_id = 11
        actor.coroutine_handle = self.simulator.start(self._owner(actor), self._do_disappear(actor))
        self._event(actor, "disappear_enter", coroutine_handle=actor.coroutine_handle)

    def _exit(self, actor):
        if actor.coroutine_handle != 0:
            self.simulator.stop(actor.coroutine_handle)
            actor.coroutine_handle = 0
            self._event(actor, "coroutine_stop_invalidate")
        self.callbacks.apply_state_modifier(actor, False)
        actor.state_modifier_applied = False
        self._event(actor, "modifier_remove")
        self._set_active(actor, True)
        base = actor.body_color  # explicit GetBodyColor snapshot, not animator.color
        if actor.disable_appear_tween_color:
            self._kill_tween(actor, actor.disappear_tween)
            self._set_color(actor, base[:3] + (binary32(1.0),))
        else:
            self._set_color(actor, (0.0, 0.0, 0.0, binary32(1.0)))
            self._start_tween(actor, "appear", base)
        actor.disable_appear_tween_color = False
        self._event(actor, "disappear_exit")

    def set_disappeared(self, actor: NpcRestoreActor, value: bool):
        actor.validate()
        _flag(value, "disappeared")
        if not actor.unity_exists:
            return False
        _require(actor.is_enemy, "only Enemy disappearing FSM is implemented")
        if actor.uid == 0 or actor.is_disappeared == value:
            self._event(actor, "setter_no_change")
            return True
        if value:
            _require(actor.state_id == 1, "only initialized MOVE -> DISAPPEAR admission is supported")
        else:
            _require(actor.state_id == 11, "clearing flag requires initialized DISAPPEAR state")
        self.callbacks.before_disappear(actor, value)
        self._event(actor, "before_disappear", value=value)
        actor.is_disappeared = value
        if value:
            _require(self.callbacks.state_transition(actor, 1, 11) is True,
                     "explicit admitted MOVE->DISAPPEAR FSM adapter required")
            self._enter(actor)
        else:
            self.callbacks.face_from_cursor(actor)
            self._event(actor, "face_from_cursor")
        self.callbacks.disappear_changed(actor, value)
        self._event(actor, "disappear_changed", value=value)
        return True

    def tick(self, actor: NpcRestoreActor, dt: FP):
        actor.validate()
        _require(isinstance(dt, FP), "native FP tick required")
        self._owner(actor)
        if not actor.unity_exists:
            return False
        if actor.state_id == 11:
            _require(actor.state_modifier_applied, "DISAPPEAR tick requires initialized modifier attachment")
            if not actor.is_disappeared:
                self._event(actor, "switch_default_requested", requested=0, resolved=1)
                self._exit(actor)
                _require(self.callbacks.state_transition(actor, 11, 1) is True,
                         "explicit admitted DEFAULT/MOVE FSM adapter required")
                actor.state_id = 1
            # The old state's OnTick was selected once: no same-call Move.OnTick.
            return False
        _require(actor.state_id == 1 and not actor.is_disappeared,
                 "state Tick outside supported MOVE/DISAPPEAR branch")
        self.callbacks.move_tick(actor, dt)
        self._event(actor, "move_tick")
        return True

    def reassign_route(self, target: NpcRestoreActor, route: RestoreRoute, progress: int):
        _require(target.cursor is not None, "native ReassignRoute requires a nonnull cursor")
        c = target.cursor
        c.validate()
        _require(isinstance(route, RestoreRoute), "prepared source Route required")
        _require(type(progress) is int and -(1 << 31) <= progress < (1 << 31),
                 "AssignHostRouteProgress stores Int32 without range clamp")
        _require(route.checkpoint_count == 0 or callable(self.callbacks.rebuild_and_reset_cursor),
                 "nonempty route checkpoint construction/Reset/OnBegin provider required")
        needs_visits = (c.visit_every_tile_center or route.visit_every_tile_center
                        or c.visit_every_node_center or route.visit_every_node_center)
        _require(not needs_visits or bool(c.visited_map) or callable(self.callbacks.rebuild_and_reset_cursor),
                 "visited-map allocation needs explicit dimensions/Reset provider")
        c.route = route
        c.visit_every_tile_center |= route.visit_every_tile_center
        c.visit_every_node_center |= route.visit_every_node_center
        c.visit_every_node_stably = route.checkpoint_count == 0
        if route.checkpoint_count or (needs_visits and not c.visited_map):
            self.callbacks.rebuild_and_reset_cursor(target, route)
            _require(len(c.checkpoint_objects) == route.checkpoint_count,
                     "provider must return every newly created checkpoint")
        else:
            c.checkpoint_objects = ()
            c.cursor_index = 0  # Reset sets -1, then _ReadNext increments to 0.
            c.cached_direction = (0.0, 0.0)
            if c.visit_every_tile_center or c.visit_every_node_center:
                c.visited_map = tuple(tuple(False for _ in row) for row in c.visited_map)
        # Native progress assignment is after Reset, with no additional OnBegin.
        c.cursor_index = progress
        self._event(target, "route_reassigned", route=route.token, progress=progress)

    def restore_to(self, target: NpcRestoreActor, source: NpcRestoreActor,
                   *, release_blocker: bool = True, disable_still_pull: bool = True,
                   assign_route: bool = True):
        target.validate()
        source.validate()
        for value, name in ((release_blocker, "release_blocker"), (disable_still_pull, "disable_still_pull"),
                            (assign_route, "assign_route")):
            _flag(value, name)
        if not target.unity_exists or not target.is_enemy or target.is_giant_boss or not source.unity_exists:
            return False
        # Reject missing providers before mutating position.
        if release_blocker:
            _require(not target.blocker_valid or callable(self.callbacks.release_blocker),
                     "valid blocker requires explicit native Unblock provider")
            _require(target.block_tween is None or callable(self.callbacks.kill_block_tween),
                     "block tween requires explicit kill provider")
        if assign_route and source.is_enemy:
            _require(source.cursor is not None and target.cursor is not None, "source/target cursor required")
            _require(source.cursor.route.checkpoint_count == 0
                     or callable(self.callbacks.rebuild_and_reset_cursor), "nonempty route Reset provider required")
        if release_blocker:
            if target.blocker_valid:
                self.callbacks.release_blocker(target)
                self._event(target, "release_blocker")
            if target.block_tween is not None:
                self.callbacks.kill_block_tween(target, target.block_tween)
                self._event(target, "kill_block_tween")
            if not target.unity_exists:
                return False
        self.callbacks.set_grid_position(target, source.grid_position)
        target.grid_position = source.grid_position
        self._event(target, "restore_position", grid_position=source.grid_position)
        if disable_still_pull:
            target.disabled_pull_sources = target.pull_sources
            self._event(target, "disable_current_still_pull", count=len(target.pull_sources))
        if assign_route and source.is_enemy:
            self.reassign_route(target, source.cursor.route, source.cursor.cursor_index)
        return True

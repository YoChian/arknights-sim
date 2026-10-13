"""Bounded Scheduler d__129 tracked summon, using explicit creation callbacks.

The source sequence is 0x18094fb90 (v7 exact PE ranges). It captures origin
route/progress/UID before its FP wait and uses the shared controller coroutine
owner. Enemy factory, route construction, initialization and mode hooks remain
declared inputs; this component never silently creates an ordinary enemy in
place of an NPC. Only the ignoreOffset/checkMotionMode ALL/no-skip branch is
implemented. This is not a full Scheduler or a battle bootstrap.
"""
from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass
import math
import struct

from .fp import FP
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from .skill_runtime import fp_fixed_seconds, fp_wait_frames


class UnverifiedSummonContext(ValueError):
    pass


def _bool(value, name):
    if type(value) is not bool:
        raise UnverifiedSummonContext(f"{name} must be an explicit bool")
    return value


def _uid(value):
    if type(value) is not int or not 0 <= value < (1 << 32):
        raise UnverifiedSummonContext("instanceUid must be UInt32")
    return value


@dataclass
class NativeCheckpointData:
    checkpoint_type: int
    time: float
    position: tuple[int, int]
    reach_offset: tuple[float, float]
    randomize_reach_offset: bool
    reach_distance: float


@dataclass
class NativeRouteData:
    motion_mode: int
    start_position: tuple[int, int]
    end_position: tuple[int, int]
    spawn_random_range: tuple[float, float]
    spawn_offset: tuple[float, float]
    checkpoints: list[NativeCheckpointData] | None
    allow_diagonal_move: bool
    visit_every_tile_center: bool
    visit_every_node_center: bool
    visit_every_checkpoint: bool
    source: str


def duplicate_route_data(data: NativeRouteData) -> NativeRouteData:
    """0x18242d930 copies all ten fields and allocates each checkpoint anew.

    Null array and empty array stay distinct. GridPosition/Vector2 are value
    copies. No route construction, cache generation or pathfinding occurs.
    """
    if not isinstance(data, NativeRouteData) or not data.source:
        raise UnverifiedSummonContext("source-bound NativeRouteData required")
    if data.checkpoints is not None and (
            not isinstance(data.checkpoints, list)
            or any(not isinstance(cp, NativeCheckpointData) for cp in data.checkpoints)):
        raise UnverifiedSummonContext("null checkpoint entries are outside selected native branch")
    cps = None if data.checkpoints is None else [NativeCheckpointData(
        cp.checkpoint_type, cp.time, tuple(cp.position), tuple(cp.reach_offset),
        cp.randomize_reach_offset, cp.reach_distance) for cp in data.checkpoints]
    return NativeRouteData(data.motion_mode, tuple(data.start_position), tuple(data.end_position),
                           tuple(data.spawn_random_range), tuple(data.spawn_offset), cps,
                           data.allow_diagonal_move, data.visit_every_tile_center,
                           data.visit_every_node_center, data.visit_every_checkpoint,
                           data.source)


@dataclass
class SummonHost:
    """Prepared native getter values; cached origin may differ from current route."""
    instance_uid: int
    alive: bool
    origin_route: object
    origin_cursor_index: int
    changeable_motion_mode: int
    source: str

    def validate(self):
        _uid(self.instance_uid)
        _bool(self.alive, "host.alive")
        if not self.source or self.origin_route is None:
            raise UnverifiedSummonContext("capturable origin route and source required")
        if type(self.origin_cursor_index) is not int or not -(1 << 31) <= self.origin_cursor_index < (1 << 31):
            raise UnverifiedSummonContext("origin progress must be Int32")
        if type(self.changeable_motion_mode) is not int or self.changeable_motion_mode not in (0, 1):
            raise UnverifiedSummonContext("only explicit ground/fly ALL branch supported")


@dataclass(eq=False)
class SummonedActor:
    """Factory output, not a default-initialized LifecycleEnemy."""
    instance_uid: int
    unity_exists: bool
    cursor: object
    actor: object
    source: str
    host_uid: int = 0

    def validate(self):
        _uid(self.instance_uid)
        _bool(self.unity_exists, "summoned Unity object exists")
        if not self.source:
            raise UnverifiedSummonContext("factory/initialization provenance required")
        if self.unity_exists and (self.cursor is None or self.actor is None):
            raise UnverifiedSummonContext("existing factory result needs cursor and actor")


@dataclass(frozen=True)
class SummonOptions:
    unharmful: bool
    always_count_as_killed: bool
    dont_count_as_finished: bool
    is_summon: bool
    spawned_count: int
    # Remaining fields in the caller's zeroed Options stack value.
    disable_born_tween_color: bool = False
    hidden_group_key: None = None
    action_extra_meta: None = None
    action_data: None = None
    no_log_in_enemy_stats_when_finished: bool = False


@dataclass(frozen=True)
class TrackedSummonRequest:
    enemy_key: str
    host: SummonHost
    position: tuple[float, float]
    delay: FP
    managed_by_scheduler: bool
    dont_block_wave: bool
    unharmful: bool
    stop_if_host_dead: bool
    ignore_offset: bool
    check_motion_mode_all: bool
    skip_checkpoints: bool
    source: str

    def validate(self):
        self.host.validate()
        if not self.enemy_key or not self.source or not isinstance(self.delay, FP):
            raise UnverifiedSummonContext("enemy key, FP delay and request provenance required")
        if (not isinstance(self.position, tuple) or len(self.position) != 2
                or not all(type(x) is float and math.isfinite(x) for x in self.position)):
            raise UnverifiedSummonContext("explicit finite prepared Single position required")
        if any(struct.unpack("<f", struct.pack("<f", x))[0] != x for x in self.position):
            raise UnverifiedSummonContext("position must already be rounded to native Single")
        for name in ("managed_by_scheduler", "dont_block_wave", "unharmful", "stop_if_host_dead",
                     "ignore_offset", "check_motion_mode_all", "skip_checkpoints"):
            _bool(getattr(self, name), name)
        if not self.ignore_offset or not self.check_motion_mode_all or self.skip_checkpoints:
            raise UnverifiedSummonContext("random offset / special route branch is not recovered")


@dataclass(frozen=True)
class SummonCallbacks:
    duplicate_route_data: Callable[[object], object]
    generate_runtime_route: Callable[[int, object], object]
    create_initialized_enemy: Callable[[str, object, SummonOptions], SummonedActor | None]
    assign_host_route_progress: Callable[[SummonedActor, int], None]
    set_position: Callable[[SummonedActor, tuple[float, float]], None]
    init_face_to: Callable[[SummonedActor], None]
    attach_additional_buffs: Callable[[SummonHost, SummonedActor], None]
    mode_before: Callable[[], None]
    mode_spawned: Callable[[SummonHost, SummonedActor], None]
    mode_after: Callable[[], None]
    source: str

    def validate(self):
        if not self.source or not all(callable(getattr(self, n)) for n in self.__dataclass_fields__ if n != "source"):
            raise UnverifiedSummonContext("all creation/route/buff/mode callbacks must be explicit")


class TrackedSummonRuntime:
    def __init__(self, *, simulator: SharedCoroutineSimulator, owner: CoroutineOwner,
                 callbacks: SummonCallbacks, allow_summon: bool, spawned_count: int,
                 delta_play_time_float: float, frame: Callable[[], int],
                 native_default_no_hotfix: bool, source: str):
        if not isinstance(simulator, SharedCoroutineSimulator) or not isinstance(owner, CoroutineOwner):
            raise UnverifiedSummonContext("shared simulator and Unity coroutine owner required")
        callbacks.validate()
        _bool(allow_summon, "allowSummonSpawnEnemy")
        if not _bool(native_default_no_hotfix, "native_default_no_hotfix") or not source or not callable(frame):
            raise UnverifiedSummonContext("default native branch, clock and source required")
        if type(spawned_count) is not int or not 0 <= spawned_count < (1 << 31) - 1:
            raise UnverifiedSummonContext("explicit non-overflowed spawned counter required")
        fp_wait_frames(FP.from_raw(0), delta_play_time_float)
        self.simulator, self.owner, self.callbacks = simulator, owner, callbacks
        self.allow_summon, self.spawned_count = allow_summon, spawned_count
        self.delta_play_time_float, self.frame, self.source = delta_play_time_float, frame, source
        self.wave: list[SummonedActor] = []
        self.final: list[SummonedActor] = []
        self.events: list[dict] = []

    def _record(self, event, **data):
        self.events.append({"frame": self.frame(), "event": event, **data})

    def start(self, request: TrackedSummonRequest):
        request.validate()
        return self.simulator.start(self.owner, self._routine(request))

    def _routine(self, request):
        if not _bool(self.allow_summon, "allowSummonSpawnEnemy"):
            self._record("rejected_before_capture")
            return
        host = request.host
        # Capture values, not live getters, before the coroutine's first yield.
        route, progress, captured_uid = host.origin_route, host.origin_cursor_index, _uid(host.instance_uid)
        self._record("capture", host_uid=captured_uid, origin_cursor_index=progress)
        self.callbacks.mode_before()
        yield fp_fixed_seconds(request.delay, self.delta_play_time_float)
        if not _bool(self.allow_summon, "allowSummonSpawnEnemy"):
            self._record("cancelled_allow_gate")
        elif request.stop_if_host_dead and (
                captured_uid != _uid(host.instance_uid) or not _bool(host.alive, "host.alive")):
            self._record("cancelled_host_gate")
        else:
            if self.spawned_count >= (1 << 31) - 1:
                raise UnverifiedSummonContext("spawn counter overflow not supported")
            self.spawned_count += 1
            options = SummonOptions(request.unharmful, False, True, True, self.spawned_count)
            self._record("counter_and_options", spawned_count=self.spawned_count)
            duplicated = self.callbacks.duplicate_route_data(route)
            if duplicated is None:
                raise UnverifiedSummonContext("route duplicate cannot be null in this branch")
            runtime_route = self.callbacks.generate_runtime_route(self.spawned_count, duplicated)
            if runtime_route is None:
                raise UnverifiedSummonContext("runtime route generation requires explicit result")
            spawned = self.callbacks.create_initialized_enemy(request.enemy_key, runtime_route, options)
            if spawned is None:
                self._record("unity_null_factory_result", mode_after_called=False)
                return  # Native Unity-null early return skips the final mode hook.
            spawned.validate()
            if not spawned.unity_exists:
                self._record("unity_null_factory_result", mode_after_called=False)
                return
            self.callbacks.assign_host_route_progress(spawned, progress)
            spawned.host_uid = captured_uid
            if request.managed_by_scheduler:
                if not request.dont_block_wave:
                    self.wave.append(spawned)
                self.final.append(spawned)
            self._record("tracked", summoned_uid=spawned.instance_uid, host_uid=captured_uid,
                         wave_member=request.managed_by_scheduler and not request.dont_block_wave,
                         final_member=request.managed_by_scheduler)
            self.callbacks.set_position(spawned, request.position)
            self.callbacks.init_face_to(spawned)
            self.callbacks.attach_additional_buffs(host, spawned)
            self.callbacks.mode_spawned(host, spawned)
            self._record("spawned", summoned_uid=spawned.instance_uid)
        self.callbacks.mode_after()
        self._record("mode_after")


"""Selected native NPC finish/recycle orchestration and Scheduler accounting.

Existing initialized actors are admitted explicitly. This does not create a
Unity object or bypass LifecycleRuntime.spawn's NPC rejection. Animation,
visual cleanup, level scripts, registries and raw pool operations are named
providers. Only a fresh event pool's first OnGameReset binding is represented;
the decoded counters do not implement ObscuredInt's encryption/anti-cheat.
"""
from __future__ import annotations

from collections.abc import Callable
from dataclasses import asdict, dataclass
import math

from .coroutines import fixed_seconds
from .fp import binary32
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from .npc_actions import DEATH_REASONS, EntityPtr, NpcEntity


class UnverifiedNpcLifecycle(ValueError):
    pass


def _require(value, message):
    if not value:
        raise UnverifiedNpcLifecycle(message)


def _bool(value, name):
    _require(type(value) is bool, name + " must be an explicit Boolean")
    return value


def _int(value, name):
    _require(type(value) is int and -(1 << 31) <= value < (1 << 31), name + " must be Int32")
    return value


def _single(value, name):
    _require(type(value) in (int, float) and math.isfinite(value), name + " must be finite")
    value = binary32(value)
    _require(math.isfinite(value), name + " must be finite Single")
    return value


def _wrap32(value):
    return (value + (1 << 31)) % (1 << 32) - (1 << 31)


def _log_value(value):
    if isinstance(value, NpcEntity):
        return {"token": value.token, "uid": value.uid}
    if isinstance(value, dict):
        return {key: _log_value(item) for key, item in value.items()}
    if isinstance(value, (tuple, list)):
        return [_log_value(item) for item in value]
    return value


@dataclass(frozen=True)
class EnemyFinishOptions:
    unharmful: bool
    always_count_as_killed: bool
    dont_count_as_finished: bool
    is_summon: bool
    spawned_count: int
    no_log_in_enemy_stats_when_finished: bool

    def __post_init__(self):
        for name in ("unharmful", "always_count_as_killed", "dont_count_as_finished",
                     "is_summon", "no_log_in_enemy_stats_when_finished"):
            _bool(getattr(self, name), name)
        _int(self.spawned_count, "spawned_count")

    @classmethod
    def from_summon_options(cls, options):
        """Explicit selected fields of the existing native summon Options value."""
        return cls(options.unharmful, options.always_count_as_killed,
                   options.dont_count_as_finished, options.is_summon,
                   options.spawned_count, options.no_log_in_enemy_stats_when_finished)


@dataclass(eq=False)
class NpcLifecycleActor:
    identity: NpcEntity
    options: EnemyFinishOptions
    coroutine_owner: CoroutineOwner
    state_id: int
    finish_reason: int
    recycle_delay: float
    is_dummy: bool
    ground_bound_exists: bool
    use_specific_dead_animation: bool
    source: str
    is_invalid_killed: bool
    is_override_kill_count: bool
    override_kill_count: int
    recycled: bool = False

    def __post_init__(self):
        _require(isinstance(self.identity, NpcEntity), "Use the same initialized NpcEntity identity")
        _require(isinstance(self.options, EnemyFinishOptions), "Explicit native enemy Options required")
        _require(isinstance(self.coroutine_owner, CoroutineOwner), "Explicit Unity coroutine owner required")
        _int(self.state_id, "state_id")
        _int(self.finish_reason, "finish_reason")
        self.recycle_delay = _single(self.recycle_delay, "delayToRecycle")
        for name in ("is_dummy", "ground_bound_exists", "use_specific_dead_animation",
                     "is_invalid_killed", "is_override_kill_count", "recycled"):
            _bool(getattr(self, name), name)
        _int(self.override_kill_count, "overrideKillCnt")
        _require(bool(self.source), "Initialized actor source required")

    def set_state(self, state):
        self.state_id = _int(state, "state_id")
        # FactoryEnemy is a NpcEntity subclass with the corresponding declared
        # fields. The old identity class still shares UID/alive/Unity existence.
        if hasattr(self.identity, "state_id"):
            self.identity.state_id = state

    def set_finish_reason(self, reason):
        self.finish_reason = _int(reason, "finish_reason")
        if hasattr(self.identity, "finish_reason"):
            self.identity.finish_reason = reason


@dataclass(frozen=True)
class DeadAnimationReceipt:
    """GetAnimationTime('Die') and omitted visual/Tween work are external."""
    animation_found: bool
    animation_length: float | None
    source: str

    def __post_init__(self):
        _bool(self.animation_found, "GetAnimationTime result")
        _require(bool(self.source), "Animation result/provider provenance required")
        if self.animation_found:
            _require(self.animation_length is not None, "Found death animation requires length")
            object.__setattr__(self, "animation_length", _single(self.animation_length, "animation length"))
        else:
            _require(self.animation_length is None, "Missing animation must not supply a duration")


@dataclass(frozen=True)
class PoolRecycleReceipt:
    """Physical existence/activation after raw pooling are supplied, not inferred."""
    unity_exists: bool
    active_in_hierarchy: bool
    source: str

    def __post_init__(self):
        _bool(self.unity_exists, "pooled Unity existence")
        _bool(self.active_in_hierarchy, "pooled GameObject activation")
        _require(bool(self.source), "Raw pool provider provenance required")
        _require(self.unity_exists or not self.active_in_hierarchy,
                 "A destroyed Unity object cannot be active")


@dataclass
class SchedulerCounters:
    finished: int
    killed: int
    valid_finished: int
    valid_killed: int
    valid_missed: int
    source: str

    def __post_init__(self):
        for name in ("finished", "killed", "valid_finished", "valid_killed", "valid_missed"):
            _int(getattr(self, name), name)
        _require(bool(self.source), "Decoded counter source required")

    def increment(self, name, amount=1):
        setattr(self, name, _wrap32(getattr(self, name) + amount))


def _remove_first(sequence, actor):
    # Native List.Remove/selected HashSet.Remove uses the object reference;
    # a zero UID after OnRecycle does not change that reference.
    for index, item in enumerate(sequence):
        if item.identity is actor.identity:
            del sequence[index]
            return True
    return False


class SchedulerLedger:
    def __init__(self, *, use_recycle_to_finish_scheduler: bool,
                 counters: SchedulerCounters, remove_runtime_route: Callable[[int], None],
                 source: str, fresh_event_pool: bool):
        self.use_recycle_to_finish_scheduler = _bool(use_recycle_to_finish_scheduler, "recycling flag")
        _require(_bool(fresh_event_pool, "fresh_event_pool"),
                 "Multiple OnGameReset/persistent event pools are outside this component")
        _require(isinstance(counters, SchedulerCounters) and callable(remove_runtime_route) and source,
                 "Decoded counters, runtime-route provider and source required")
        self.counters, self.remove_runtime_route, self.source = counters, remove_runtime_route, source
        self.wave, self.final, self.dynamic = [], [], []
        self.future_groups: tuple[list[NpcLifecycleActor], ...] = ()
        self.bound_events = (6, 8) if self.use_recycle_to_finish_scheduler else (6,)

    def attach(self, actor, *, managed_by_scheduler: bool, dont_block_wave: bool):
        _require(isinstance(actor, NpcLifecycleActor), "Initialized lifecycle actor required")
        if _bool(managed_by_scheduler, "managed_by_scheduler"):
            if not _bool(dont_block_wave, "dont_block_wave"):
                self.wave.append(actor)
            self.final.append(actor)
        else:
            _bool(dont_block_wave, "dont_block_wave")

    def on_unit_finished(self, actor):
        _require(isinstance(actor, NpcLifecycleActor), "Lifecycle actor required")
        if not actor.identity.is_enemy or not actor.identity.unity_exists:
            return
        _remove_first(self.wave, actor)
        _remove_first(self.dynamic, actor)
        for group in self.future_groups:
            if _remove_first(group, actor):
                break
        if not self.use_recycle_to_finish_scheduler:
            _remove_first(self.final, actor)
        options = actor.options
        if options.is_summon:
            self.remove_runtime_route(options.spawned_count)
        death = actor.finish_reason in DEATH_REASONS
        if not options.dont_count_as_finished and not options.is_summon:
            self.counters.increment("finished")
            if options.always_count_as_killed or death:
                self.counters.increment("killed")
            if actor.is_override_kill_count:
                if actor.override_kill_count > 0:
                    self.counters.increment("valid_finished")
                if death:
                    self.counters.increment("valid_killed", actor.override_kill_count)
                    self.counters.valid_killed = max(0, self.counters.valid_killed)
                elif actor.override_kill_count > 0:
                    self.counters.increment("valid_missed")
            elif not actor.is_invalid_killed:
                self.counters.increment("valid_finished")
                self.counters.increment("valid_killed" if death else "valid_missed")
        if options.is_summon and not options.unharmful and not death:
            self.counters.increment("valid_missed")

    def on_enemy_recycled(self, actor):
        if (8 in self.bound_events and actor.identity.is_enemy
                and actor.identity.unity_exists):
            _remove_first(self.final, actor)

    def final_not_finished(self, *, mode_blocks: bool, block_keys: tuple[str, ...], source: str):
        _bool(mode_blocks, "GameNotFinishCondition")
        _require(type(block_keys) is tuple and all(type(x) is str for x in block_keys) and source,
                 "Explicit mode/blocking-key predicate context required")
        return bool(self.final) or mode_blocks or bool(block_keys)

    def snapshot(self):
        return {"wave": [a.identity.token for a in self.wave],
                "final": [a.identity.token for a in self.final],
                "counters": asdict(self.counters), "bound_events": list(self.bound_events),
                "event_binding_scope": "first Scheduler.OnGameReset with explicit fresh event pool and constant config",
                "counter_backend": "decoded Int32 semantics; ObscuredInt implementation excluded"}


@dataclass(frozen=True)
class NpcLifecycleHooks:
    owner_finish: Callable[[NpcLifecycleActor, int, NpcEntity | None], None]
    clear_buffs: Callable[[NpcLifecycleActor, bool], None]
    native_phase: Callable[[str, NpcLifecycleActor, dict], None]
    raw_recycle: Callable[[NpcLifecycleActor], PoolRecycleReceipt]
    dead_animation: Callable[[NpcLifecycleActor], DeadAnimationReceipt]
    source: str

    def validate(self):
        _require(self.source and all(callable(getattr(self, field))
                 for field in self.__dataclass_fields__ if field != "source"),
                 "All Buff/cleanup/pool/animation providers must be explicit")


class NpcLifecycleRuntime:
    def __init__(self, *, simulator: SharedCoroutineSimulator, ledger: SchedulerLedger,
                 hooks: NpcLifecycleHooks, delta_play_time_float: float,
                 frame: Callable[[], int], no_hotfix: bool, controller_exists: bool,
                 source: str):
        _require(isinstance(simulator, SharedCoroutineSimulator) and isinstance(ledger, SchedulerLedger),
                 "Explicit shared coroutine simulator and Scheduler backend required")
        hooks.validate()
        _require(_bool(no_hotfix, "no_hotfix") and source and callable(frame),
                 "Native default branch, frame getter and source required")
        self.controller_exists = _bool(controller_exists, "controller_exists")
        self.delta_play_time_float = _single(delta_play_time_float, "deltaPlayTimeFloat")
        _require(self.delta_play_time_float > 0, "Positive coroutine delta required")
        self.simulator, self.ledger, self.hooks, self.frame, self.source = simulator, ledger, hooks, frame, source
        self.events = []

    def _record(self, stage, actor, **details):
        row = {"frame": self.frame(), "stage": stage, "actor": actor.identity.token,
               "uid": actor.identity.uid, "finish_reason": actor.finish_reason, **_log_value(details)}
        self.events.append(row)
        return row

    def _phase(self, stage, actor, **details):
        self._record(stage, actor, **details)
        self.hooks.native_phase(stage, actor, dict(details))

    def finish(self, actor: NpcLifecycleActor, reason: int, *, finish_source: EntityPtr):
        _require(isinstance(actor, NpcLifecycleActor) and isinstance(finish_source, EntityPtr),
                 "Same initialized actor and explicit captured context source required")
        _int(reason, "finish reason")
        _require(reason in (2, 7), "Only selected death2 and no-reason7 paths are closed")
        if reason == 2:
            _require(not actor.recycled, "Repeated DeadState entry on pooled actor is outside this scope")
            actor.set_state(5)
            self._phase("dead_state_release_block", actor)
            receipt = self.hooks.dead_animation(actor)
            _require(isinstance(receipt, DeadAnimationReceipt), "Explicit death animation receipt required")
            if receipt.animation_found and actor.use_specific_dead_animation:
                actor.recycle_delay = receipt.animation_length
            self._record("dead_state_animation_provider", actor, source=receipt.source,
                         delay_single=actor.recycle_delay)
        self._phase("enemy_log_runtime_snapshot", actor)
        if not actor.options.no_log_in_enemy_stats_when_finished:
            self._phase("enemy_stats_finish", actor, requested_reason=reason)
        if reason == 2:
            self._phase("enemy_death_extra_log", actor)
        # Entity.unfinished is finishReason==0. Enemy's outer wrapper still
        # invokes mode.OnEnemyFinished after the guarded base call returns.
        changed = actor.finish_reason == 0
        if changed:
            actor.set_finish_reason(reason)
            actor.set_state(-1)
            actor.identity.alive = False
            self._phase("state_machine_stop", actor)
            resolved_source = finish_source.resolve()
            if reason in DEATH_REASONS:
                if resolved_source is not None:
                    self._phase("source_on_target_killed", actor, source_entity=resolved_source)
                self._phase("entity_event1", actor)
            self._record("buff_owner_finish", actor)
            self.hooks.owner_finish(actor, reason, resolved_source)
            self._record("buff_clear", actor, is_owner_finished=True)
            self.hooks.clear_buffs(actor, True)
            self._phase("entity_clear_abilities_hold_effects_ep", actor)
            self._phase("entity_event2", actor)
            self._phase("unit_finish_animator_mode_visual_cleanup", actor)
            if not actor.is_dummy:
                self._record("battle_event6", actor)
                self.ledger.on_unit_finished(actor)
            self._phase("enemy_level_event3_tile_block_skill_cleanup", actor)
            # DefaultGameMode.DestroyEntity: death and exit use a delay;
            # selected no-reason7 recycles immediately regardless of delay.
            self._record("default_mode_destroy_entity", actor, requested_reason=reason)
            if reason == 7:
                self._recycle(actor)
            else:
                self._schedule_recycle(actor)
        self._phase("mode_on_enemy_finished", actor, requested_reason=reason)
        self._phase("enemy_after_finish_gates", actor)
        return changed

    def _schedule_recycle(self, actor):
        if actor.recycle_delay <= binary32(1e-5):
            self._recycle(actor)
            return
        def routine():
            yield fixed_seconds(actor.recycle_delay, self.delta_play_time_float)
            self._recycle(actor)
        self._record("delayed_recycle_started", actor, delay_single=actor.recycle_delay)
        self.simulator.start(actor.coroutine_owner, routine())

    def _recycle(self, actor):
        _require(not actor.recycled, "Duplicate raw pool callback requires a separate external context")
        self._phase("unit_recycle_dynamic_abilities_modes_unregister_talents_visual", actor)
        self._phase("entity_recycle_cleanup_clear_abilities", actor)
        self._phase("unregister_bobject", actor)
        actor.identity.uid = 0
        self._record("uid_invalidated", actor)
        self._phase("enemy_reset_cursor_and_route", actor)
        if actor.ground_bound_exists:
            self._phase("ground_bound_recycle", actor)
            if self.controller_exists:
                self._record("battle_event8", actor)
                self.ledger.on_enemy_recycled(actor)
        actor.recycled = True
        receipt = self.hooks.raw_recycle(actor)
        _require(isinstance(receipt, PoolRecycleReceipt), "Raw pool operation requires its explicit receipt")
        actor.identity.unity_exists = receipt.unity_exists
        actor.coroutine_owner.exists = receipt.unity_exists
        actor.coroutine_owner.active_in_hierarchy = receipt.active_in_hierarchy
        self._record("raw_pool_recycled", actor, provider_source=receipt.source,
                     unity_exists=receipt.unity_exists, active_in_hierarchy=receipt.active_in_hierarchy)

    def info(self):
        return {"scope": "selected initialized NPC Finish7/death2 default-mode callback chain",
                "native_event_binding_reconstructed": True,
                "event_pool_backend": "selected synchronous first-reset callbacks",
                "native_pool_executed": False, "native_animation_executed": False,
                "native_factory_executed": False, "full_map_win_generated": False,
                "runtime_battle_validated": False, "battle_ready": False,
                "source": self.source, "provider_source": self.hooks.source,
                "scheduler": self.ledger.snapshot()}

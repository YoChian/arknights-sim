"""Recovered logical enemy lifecycle, with explicit run and mode context.

The component ends at a mode's logical FinishGame request. Unity's visual
outro, object-pool rendering, active talents and live hotfixes are not executed.
Call state and recycling ticks in the phases recovered by the enclosing scene.
"""
from __future__ import annotations

from copy import deepcopy
from dataclasses import dataclass
import math
from typing import Callable

from .coroutines import CoroutineRunner, fixed_seconds
from .data import require
from .env import UnverifiedMechanism
from .fp import FP, binary32


SINGLE_EPSILON = binary32(1e-5)  # 0x186e3fd88: acc52737
ALIVE_EPSILON_RAW = 42950  # MathUtil.GT(FP): EN5, recovered static initialization
BORN_STATE, MOVE_STATE, EXIT_STATE, STOPPED_STATE = 6, 1, 7, -1
REACH_EXIT_REASON = 1

LIFECYCLE_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "Entity.OnBorn": "0x1806f7df0",
    "Enemy.States.ConstructStateMachine": "0x180a9b3e0",
    "BornState.OnEnter": "0x180a884c0",
    "BornState.OnTick": "0x180a887a0",
    "StateMachine.Tick": "0x1826483e0",
    "Enemy.ReachExit": "0x180a73600",
    "Enemy.OnFinish": "0x180a70920",
    "Entity.OnFinish": "0x1806f8c40",
    "Entity.FinishMe": "0x1806f3360",
    "DefaultGameMode.DestroyEntity": "0x180c18e70",
    "Scheduler._OnUnitDestroyed": "0x18091bcb0",
    "BattleController._DoApplyGlobalModifier": "0x180636a90",
    "BObject.DestroyMe": "0x180662710",
    "PoolManagerExtensions._RecycleAsync_MonoBehaviour.MoveNext": "0x180661ec0",
    "IReusable.OnRecycle_dispatch": "0x185c27ff0",
    "client_runtime_compared": False,
}

# These assets contain lifecycle actions. An empty tuple supplied by the caller
# cannot erase an already identified source dependency.
UNSUPPORTED_ENEMY_LIFECYCLE = {
    "enemy_2133_shdopl": ("enemy_shdopl_passive", "enemy_shdopl_finish"),
    "enemy_3001_upeopl": ("upeople_t", "upeople_t_1"),
}


def _int32(value: int, name: str) -> int:
    require(type(value) is int and -(1 << 31) <= value < 1 << 31,
            f"{name} must be a signed int32")
    return value


def _single(value: float, name: str) -> float:
    require(type(value) in (int, float) and math.isfinite(value), f"{name} must be finite")
    result = binary32(value)
    require(math.isfinite(result), f"{name} overflows Single")
    return result


def native_alive(state_id: int, hp: FP, *, registered_states=range(1, 17)) -> bool:
    """Ordinary Entity.alive: state exists and MathUtil.GT(hp, FP.Zero)."""
    require(type(state_id) is int and isinstance(hp, FP), "alive needs state ID and FP HP")
    return state_id > 0 and state_id in registered_states and hp.raw > ALIVE_EPSILON_RAW


@dataclass
class LifecycleEnemy:
    identifier: str
    enemy_key: str
    hp: FP
    born_remaining: FP
    recycle_delay: float
    life_point_reduce: int
    managed: bool
    wave_block: bool
    not_count_in_total: bool
    state_id: int = BORN_STATE
    finish_reason: int = 0
    recycled: bool = False

    @property
    def alive(self) -> bool:
        return native_alive(self.state_id, self.hp)

    @property
    def move_state_ready(self) -> bool:
        return self.state_id == MOVE_STATE and self.alive and not self.finish_reason


class LifecycleRuntime:
    """A logical entity backend for the ordinary native default-mode paths.

    ``initial_life`` is a run input. LevelData.initialLifePoint is never used as
    a substitute. The DynamicConfig recycling flag is an explicit context input.
    Empty modifier/talent context is a declared offline scenario, not evidence
    that a real Rogue run has no modifiers.
    """

    def __init__(self, *, initial_life: int, initial_temp_life: int, dt: FP,
                 use_recycle_to_finish_scheduler: bool, context_source: str,
                 mode_backend: str = "DefaultGameMode", global_modifiers=(),
                 hotfix_policy: str = "excluded", on_event: Callable[[dict], None] | None = None):
        self.life = _int32(initial_life, "initial_life")
        self.temp_life = _int32(initial_temp_life, "initial_temp_life")
        require(self.life > 0 and self.temp_life >= 0, "Initial life must be positive and temp life nonnegative")
        require(isinstance(dt, FP) and 0 < dt.raw < (1 << 63), "dt must be a positive FP")
        require(type(use_recycle_to_finish_scheduler) is bool, "Supply the explicit scheduler recycling flag")
        require(type(context_source) is str and bool(context_source.strip()), "Lifecycle context requires a source")
        if mode_backend != "DefaultGameMode" or global_modifiers or hotfix_policy != "excluded":
            raise UnverifiedMechanism("Lifecycle requires explicit DefaultGameMode, empty global modifiers and excluded hotfix dispatch")
        require(on_event is None or callable(on_event), "on_event must be callable")
        self.dt = dt
        self.use_recycle_to_finish_scheduler = use_recycle_to_finish_scheduler
        self.context_source = context_source
        self.on_event = on_event
        self.enemies: dict[str, LifecycleEnemy] = {}
        self.wave_ids, self.final_ids = set(), set()
        self.events: list[dict] = []
        self.current_frame, self.time = 0, FP.from_raw(0)
        self.recycle_runners: dict[str, CoroutineRunner] = {}
        self.finish_request: str | None = None
        self.exit_life_lost = self.other_life_lost = 0

    @property
    def terminated(self) -> bool:
        return self.finish_request is not None

    @property
    def wave_blocked(self) -> bool:
        return bool(self.wave_ids)

    def _event(self, kind: str, **detail) -> dict:
        event = {"kind": kind, "frame": self.current_frame, "time_raw": self.time.raw, **deepcopy(detail)}
        self.events.append(event)
        if self.on_event:
            self.on_event(deepcopy(event))
        return event

    def info(self) -> dict:
        return {"scope": "static_default_mode_logical_enemy_lifecycle", "creation_backend": "logical_entity",
                "context_source": self.context_source, "initial_life_origin": "explicit_run_input",
                "mode_backend": "DefaultGameMode", "hotfix_policy": "excluded", "global_modifiers": [],
                "use_recycle_to_finish_scheduler": self.use_recycle_to_finish_scheduler,
                "active_lifecycle_templates_supported": False, "runtime_battle_validated": False,
                "pool_backend": "logical_pool_enabled",
                "scheduler_event_binding_verified": False,
                "finish_reason_scope": "ReachExit_reason1_only",
                "finish_scope": "logical_FinishGame_request_before_Unity_outro",
                "native_evidence": deepcopy(LIFECYCLE_EVIDENCE)}

    def spawn(self, identifier: str, enemy_key: str, *, max_hp: FP, birth_delay: float,
              recycle_delay: float, life_point_reduce: int, managed: bool, wave_block: bool,
              not_count_in_total: bool, lifecycle_templates: tuple[str, ...]) -> LifecycleEnemy:
        require(not self.terminated, "Cannot create after a logical finish request")
        require(type(identifier) is str and identifier and identifier not in self.enemies,
                "Enemy identifier must be nonempty and unique")
        require(type(enemy_key) is str and bool(enemy_key), "Enemy key is required")
        require(isinstance(max_hp, FP) and max_hp.raw >= 0, "max_hp must be nonnegative FP")
        require(all(type(x) is bool for x in (managed, wave_block, not_count_in_total)), "Membership flags must be boolean")
        require(type(lifecycle_templates) is tuple and all(type(x) is str and x for x in lifecycle_templates),
                "Supply reviewed lifecycle template keys as a tuple")
        if lifecycle_templates or enemy_key in UNSUPPORTED_ENEMY_LIFECYCLE:
            keys = lifecycle_templates or UNSUPPORTED_ENEMY_LIFECYCLE[enemy_key]
            raise UnverifiedMechanism(f"{enemy_key}: active lifecycle templates need an action executor: {', '.join(keys)}")
        birth_delay, recycle_delay = _single(birth_delay, "birth_delay"), _single(recycle_delay, "recycle_delay")
        cost = _int32(life_point_reduce, "life_point_reduce")
        require(cost >= 0, "Negative enemy exit costs are outside this lifecycle input scope")
        remaining = FP.from_float32(birth_delay) if birth_delay > SINGLE_EPSILON else FP.from_raw(0)
        actor = LifecycleEnemy(identifier, enemy_key, max_hp, remaining, recycle_delay, cost,
                               managed, wave_block, not_count_in_total)
        self.enemies[identifier] = actor
        tracked = managed and not not_count_in_total and actor.alive
        if tracked:
            self.final_ids.add(identifier)
            if wave_block:
                self.wave_ids.add(identifier)
        self._event("enemy_born", id=identifier, enemy_key=enemy_key, state_id=BORN_STATE,
                    born_remaining_raw=remaining.raw, hp_raw=max_hp.raw, alive=actor.alive,
                    tracked=tracked, wave_block=tracked and wave_block)
        return actor

    def begin_frame(self, *, frame: int | None = None, time: FP | None = None):
        """Set the shared clock before independently ordered scene phases."""
        next_frame = self.current_frame + 1 if frame is None else frame
        require(type(next_frame) is int and next_frame > self.current_frame, "Frames must advance")
        next_time = self.time + self.dt if time is None else time
        require(isinstance(next_time, FP) and next_time.raw >= self.time.raw, "Lifecycle clock must advance")
        self.current_frame, self.time = next_frame, next_time

    def tick_state(self, identifier: str, delta: FP | None = None) -> bool:
        """Return whether MOVE was already active on entry and may tick it.

        Born -> Move occurs after Born.OnTick; Move.OnTick is not called again
        during that same StateMachine.Tick.
        """
        actor = self.enemies[identifier]
        delta = self.dt if delta is None else delta
        require(isinstance(delta, FP) and delta.raw > 0, "State delta must be positive FP")
        if actor.recycled or actor.finish_reason:
            return False
        was_move = actor.state_id == MOVE_STATE
        if actor.state_id == BORN_STATE:
            actor.born_remaining = actor.born_remaining - delta
            if actor.born_remaining.raw <= 0:
                actor.state_id = MOVE_STATE
                self._event("enemy_birth_complete", id=identifier, state_id=MOVE_STATE,
                            born_remaining_raw=actor.born_remaining.raw)
        return was_move

    def _recycle(self, actor: LifecycleEnemy):
        if actor.recycled:
            return
        actor.recycled = True
        self.final_ids.discard(actor.identifier)
        self._event("enemy_recycled", id=actor.identifier, finish_reason=actor.finish_reason,
                    wave_membership_changed=False)

    def _schedule_recycle(self, actor: LifecycleEnemy):
        if actor.recycle_delay <= SINGLE_EPSILON:
            self._recycle(actor)
            return
        def coroutine():
            yield fixed_seconds(actor.recycle_delay, self.dt.as_float())
            self._recycle(actor)
        runner = CoroutineRunner(coroutine())
        self.recycle_runners[actor.identifier] = runner
        self._event("enemy_recycle_scheduled", id=actor.identifier, delay_single=actor.recycle_delay)
        runner.tick()  # Native StartBattleCoroutine advances immediately.

    def tick_recycling(self):
        """Advance the already started native wait stack in a coroutine phase."""
        for identifier, runner in list(self.recycle_runners.items()):
            if runner.active:
                runner.tick()
            if not runner.active:
                del self.recycle_runners[identifier]

    def modify_life(self, delta: int, *, source: str, is_reach_exit: bool = False,
                    to_temp_life: bool = False) -> dict:
        """Integer NewLifePointDelta path; temp absorption precedes life write."""
        delta = _int32(delta, "life delta")
        require(type(source) is str and source, "Life modification needs a source")
        require(type(is_reach_exit) is bool and type(to_temp_life) is bool, "Life flags must be boolean")
        if self.terminated:
            return {"applied": False, "applied_delta": 0, "life": self.life, "temp_life": self.temp_life}
        before_life, before_temp = self.life, self.temp_life
        temp = self.temp_life
        remaining = delta
        if remaining > 0 and to_temp_life:
            temp = _int32(temp + remaining, "temp life result")
            remaining = 0
        if temp > 0 and remaining < 0:
            if temp < -remaining:
                remaining += temp
                temp = 0
            else:
                temp += remaining
                remaining = 0
        written_life = _int32(self.life + remaining, "life result")
        self.life, self.temp_life = max(0, written_life), temp
        applied_delta = self.life - before_life
        if applied_delta < 0:
            if is_reach_exit:
                self.exit_life_lost += -applied_delta
            else:
                self.other_life_lost += -applied_delta
        # SetLifePoint calls OnPlayerLifeToZero before ModifyLifePoint emits22.
        if self.life == 0:
            self._request_finish("lose", source="DefaultGameMode.OnPlayerLifeToZero")
        event = self._event("life_modified", source=source, requested_delta=delta,
                            applied_delta=applied_delta, applied_delta_fp_raw=FP.from_int32(applied_delta).raw,
                            life_before=before_life, life=self.life, temp_life_before=before_temp,
                            temp_life=self.temp_life, is_reach_exit=is_reach_exit, event_id=0x22)
        return {"applied": True, "applied_delta": applied_delta, "life": self.life,
                "temp_life": self.temp_life, "event": deepcopy(event)}

    def finish(self, identifier: str, reason: int) -> bool:
        """Ordinary ReachExit callback chain, excluding active talents.

        Death state entry can change recycling delay. That path needs its own
        closure and is deliberately rejected here.
        """
        actor = self.enemies[identifier]
        reason = _int32(reason, "finish reason")
        require(reason > 0, "Finish reason must be positive")
        if reason != REACH_EXIT_REASON:
            raise UnverifiedMechanism("This lifecycle restores ReachExit reason1 only; death state entry is not closed")
        if actor.finish_reason or actor.recycled:
            return False
        actor.finish_reason, actor.state_id = reason, STOPPED_STATE
        self._event("enemy_finished", id=identifier, finish_reason=reason, state_id=STOPPED_STATE)
        # The real virtual OnFinish chain emits Unit event6, then Enemy exit.
        # Entity.OnFinish slot118 is ClearAbilities, not a recycle operation.
        self.wave_ids.discard(identifier)
        if not self.use_recycle_to_finish_scheduler:
            self.final_ids.discard(identifier)
        self._event("enemy_wave_released", id=identifier,
                    final_membership_retained=identifier in self.final_ids)
        # Enemy.OnFinish calls the base Unit/Entity chain first, then mode exit.
        if reason == REACH_EXIT_REASON:
            self.modify_life(-actor.life_point_reduce, source=identifier, is_reach_exit=True)
            self._event("enemy_reached_exit", id=identifier, event_id=7)
        # After virtual OnFinish returns, Entity.FinishMe calls mode.DestroyEntity.
        # DefaultGameMode reason1 selects RecycleSelfWithDelay.
        self._schedule_recycle(actor)
        return True

    def reach_exit(self, identifier: str) -> bool:
        actor = self.enemies[identifier]
        if actor.finish_reason or actor.recycled:
            return False
        require(actor.move_state_ready, "Exit requires a live enemy in the ordinary Move state")
        actor.state_id = EXIT_STATE
        self._event("enemy_exit_state", id=identifier, state_id=EXIT_STATE)
        return self.finish(identifier, REACH_EXIT_REASON)

    def _request_finish(self, outcome: str, *, source: str):
        if self.finish_request is None:
            self.finish_request = outcome
            self._event("battle_finish_requested", outcome=outcome, source=source,
                        scope="logical_default_mode_request_before_Unity_outro")

    def check_final(self, *, schedule_complete: bool, branches_active: bool) -> bool:
        require(type(schedule_complete) is bool and type(branches_active) is bool, "Final gates must be boolean")
        if not self.terminated and schedule_complete and not branches_active and not self.final_ids:
            self._request_finish("win", source="Scheduler._CheckFinalNotFinish/default_mode")
        return self.terminated

    def tick(self):
        """Convenience component tick; scene integration uses separate phases."""
        self.begin_frame()
        moved = {identifier: self.tick_state(identifier) for identifier in list(self.enemies)}
        self.tick_recycling()
        return moved

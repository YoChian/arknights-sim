"""Selected native altar AUTO/CharacterFSM/Ability cycle.

This component starts from explicitly prepared Init/AssignData/Attach inputs.
It is not a game bootstrap, a Physics2D oracle, or a damage implementation.
All paths assume the pinned default native methods, with null hotfix slots.
"""
from __future__ import annotations

from collections import deque
from collections.abc import Callable, Iterable
from dataclasses import dataclass

from .coroutines import NEXT_FRAME
from .devices import FP_LARGE_EPS_RAW, NaturalSpController
from .fp import FP, ZERO
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator


class UnverifiedSkillContext(ValueError):
    pass


def _bool(value, name):
    if type(value) is not bool:
        raise UnverifiedSkillContext(f"{name} must be an explicit bool")
    return value


def fp_wait_frames(delay: FP, delta_play_time_float: float) -> int:
    """FP wait 1806614a0 -> RoundToInt1866e6620 -> FP.Round/AsInt.

    The divisor is FP.from_float32(deltaPlayTime), not deltaPlayTimeFP read
    directly and not a binary32 quotient. FP.Round is nearest ties-even.
    """
    divisor = FP.from_float32(delta_play_time_float)
    if not isinstance(delay, FP) or divisor.raw <= 0:
        raise UnverifiedSkillContext("finite FP delay and positive float delta required")
    quotient = delay / divisor
    count = quotient.round().as_int()
    if not -(1 << 31) <= count < (1 << 31):
        raise UnverifiedSkillContext("FP wait count outside supported Int32 range")
    return max(1, count)


def fp_fixed_seconds(delay: FP, delta_play_time_float: float):
    for _ in range(fp_wait_frames(delay, delta_play_time_float)):
        yield NEXT_FRAME


@dataclass
class AbilityCooldown:
    """PeriodicTimer.Update clamps to zero; readiness is |remaining| < EN5."""
    period: FP
    remaining: FP

    @property
    def ready(self):
        return abs(self.remaining.raw) < FP_LARGE_EPS_RAW

    def reset(self, wait_first: bool):
        self.remaining = self.period if _bool(wait_first, "wait_first") else ZERO

    def tick(self, delta: FP):
        self.remaining = self.remaining - delta
        if self.remaining.raw <= 0:
            self.remaining = ZERO
            return True
        return False


@dataclass(frozen=True)
class AltarSkillContext:
    """A conditional post-initialization scene declaration, not inferred flags.

    Prepared times are actual runtime fields (preDelayFP, durationFP, cooldown
    FP), supplied explicitly until the full assignment/blackboard closure is
    implemented. Hooks and target selection are provided separately.
    """
    source: str
    prepared_time_source: str
    prepared_pre_delay: FP
    prepared_duration: FP
    prepared_cooldown: FP
    delta_play_time_float: float
    half_default_frame: FP
    sp_recovery_per_second: FP
    initialized_assigned_attached: bool
    native_default_no_hotfix: bool
    predefined: bool
    playing_at_initialize: bool
    dialog_target: bool
    owner_can_use_skill: bool
    ability_available: bool
    abnormal_state: bool
    other_sp_modifiers: bool
    active_skill_event_effects: bool
    chant_present: bool
    skill_behaviour_count: int
    extra_ability_count: int
    sp_cost: int
    init_sp: int

    def validate(self):
        if not self.source or not self.prepared_time_source:
            raise UnverifiedSkillContext("scene and prepared-time sources required")
        for name in ("initialized_assigned_attached", "native_default_no_hotfix",
                     "predefined", "playing_at_initialize", "dialog_target",
                     "owner_can_use_skill", "ability_available", "abnormal_state",
                     "other_sp_modifiers", "active_skill_event_effects", "chant_present"):
            _bool(getattr(self, name), name)
        if not self.initialized_assigned_attached or not self.native_default_no_hotfix:
            raise UnverifiedSkillContext("prepared native default skill required")
        if not self.predefined or self.playing_at_initialize or self.dialog_target:
            raise UnverifiedSkillContext("only predefined/not-playing/non-dialog Born path is closed")
        if (self.abnormal_state or self.other_sp_modifiers or
                self.active_skill_event_effects or self.chant_present):
            raise UnverifiedSkillContext("abnormal/modifier/event/chant path is outside this kernel")
        if type(self.skill_behaviour_count) is not int or self.skill_behaviour_count != 0:
            raise UnverifiedSkillContext("skill behaviours must be explicitly empty")
        if type(self.extra_ability_count) is not int or self.extra_ability_count != 0:
            raise UnverifiedSkillContext("extra abilities must be explicitly empty")
        if self.sp_cost != 7 or type(self.sp_cost) is not int or self.init_sp != 0:
            raise UnverifiedSkillContext("this component covers the altar SP7/init0 input")
        for name in ("prepared_pre_delay", "prepared_duration", "prepared_cooldown",
                     "half_default_frame", "sp_recovery_per_second"):
            v = getattr(self, name)
            if not isinstance(v, FP) or v.raw < 0 or v.raw >= (1 << 62):
                raise UnverifiedSkillContext(f"{name} must be a finite bounded nonnegative FP")
        if self.sp_recovery_per_second.raw == 0 or self.half_default_frame.raw == 0:
            raise UnverifiedSkillContext("positive recovery/half-frame required")
        fp_wait_frames(ZERO, self.delta_play_time_float)


def explicit_altar_fixture_context(*, source: str, prepared_time_source: str,
                                   pre_delay: FP, duration: FP, cooldown: FP,
                                   delta_play_time_float: float,
                                   half_default_frame: FP,
                                   sp_recovery_per_second: FP) -> AltarSkillContext:
    """Declare a small scene's assumptions visibly; never advertised as live state.

    The prefab's flags are AUTO, switchToState, no chant/behaviours/extra abilities,
    no begin/three-part animations, allowNoTarget, AT_BEGINING, HALF_FRAME,
    no cooldown reset on skill-end, no SP recovery while affecting, no overload,
    unlimited triggers, and escapeTime0. Other owner/event/SP modifiers are
    explicitly declared absent by this fixture, rather than silently ignored.
    """
    c = AltarSkillContext(
        source, prepared_time_source, pre_delay, duration, cooldown,
        delta_play_time_float, half_default_frame, sp_recovery_per_second,
        True, True, True, False, False, True, True, False, False, False, False,
        0, 0, 7, 0)
    c.validate()
    return c


class AltarSkillRuntime:
    """AUTO cycle driven by an external SelectedFrameLoop/shared simulator.

    initialize() reproduces the selected BORN7 -> queued IDLE1 transition.
    fixed_tick() covers FSM guard, natural SP, ability cooldown, BasicSkill
    UpdateSpRecovery and AUTO admission in that native order. The caller runs
    simulator.tick() later in the same global frame, never inside fixed_tick.
    Target objects are shallow copied at begin; membership/order is frozen,
    while each target's changing HP/liveness remains the target module's job.
    """
    BORN = 7
    IDLE = 1
    SKILL = 4

    def __init__(self, context: AltarSkillContext, *,
                 simulator: SharedCoroutineSimulator, unity_owner: CoroutineOwner,
                 clock: Callable[[], tuple[int, FP]],
                 select_targets: Callable[[], Iterable],
                 spell: Callable[[tuple], None],
                 on_event: Callable[[dict], None] | None = None):
        context.validate()
        if not isinstance(simulator, SharedCoroutineSimulator):
            raise UnverifiedSkillContext("shared deterministic simulator required")
        if not isinstance(unity_owner, CoroutineOwner) or not unity_owner.available():
            raise UnverifiedSkillContext("existing active Unity owner required")
        if not all(callable(v) for v in (clock, select_targets, spell)):
            raise UnverifiedSkillContext("clock, target selector, and spell operations required")
        self.context = context
        self.simulator, self.unity_owner = simulator, unity_owner
        self.clock, self.select_targets, self.spell = clock, select_targets, spell
        self.on_event = on_event
        self.events: list[dict] = []
        self.state = -1
        self.initialized = False
        self.alive = True
        self.is_casting = False
        self.cast_start_frame = 0
        self.cast_count = 0
        self.sp = FP.from_int32(context.init_sp)
        self.registered_as_modifier = False
        self.allow_other_sp_stop = False
        self.cooldown = AbilityCooldown(context.prepared_cooldown, ZERO)
        self.sp_controller = NaturalSpController.reset(
            context.sp_recovery_per_second, lambda: self.sp, self._write_sp,
            max_sp=context.sp_cost, sp_type=1)
        self._switch_busy = False
        self._pending: deque[int] = deque()
        self._handle = 0
        self.targets: tuple = ()
        self._pre_started_at = ZERO
        self._duration_at_begin = ZERO

    def _emit(self, kind: str, **extra):
        frame, time = self.clock()
        if type(frame) is not int or frame < 0 or not isinstance(time, FP):
            raise UnverifiedSkillContext("clock must return nonnegative frame and FP time")
        event = {"frame": frame, "time_raw": time.raw, "kind": kind, **extra}
        self.events.append(event)
        if self.on_event is not None:
            self.on_event(event.copy())

    def _write_sp(self, value: FP):
        # Selected Entity.set_sp clamp: no extra SP modifier/events in context.
        self.sp = FP(max(0, min(FP.from_int32(self.context.sp_cost).raw, value.raw)))

    def _register_modifier(self, value: bool):
        if self.registered_as_modifier != value:
            # Native setter updates backing flag before Register/Unregister.
            self.registered_as_modifier = value
            self._emit("sp_recovery_modifier", registered=value, abnormal_flag_mask=2)

    def initialize(self):
        if self.initialized:
            raise ValueError("already initialized")
        self.context.validate()
        self.initialized = True
        self._switch(self.BORN, force=True)

    def _switch(self, state: int, *, force=False):
        if state not in (self.BORN, self.IDLE, self.SKILL):
            raise UnverifiedSkillContext("only Born/Idle/Skill states are closed")
        if self._switch_busy:
            self._pending.append(state)
            self._emit("state_switch_queued", state=state)
            return
        self._switch_busy = True
        try:
            old = self.state
            if old == state:
                return
            if not force and old < 1:
                return
            if old == self.SKILL and self.is_casting:
                raise UnverifiedSkillContext("active abnormal/interruption transition is not closed")
            if old == self.BORN:
                self._emit("born_exit", skip_attack_until_next_frame=True)
            self.state = state
            self._emit("state_enter", state=state, previous=old)
            if state == self.BORN:
                # BornState.OnEnter predefined && !BC.isPlaying short circuit.
                self._switch(self.IDLE)
            elif state == self.SKILL:
                self._emit("before_skill")
                if self._cast():
                    # _DoStartSkill calls OnEnterSkillState only after Cast returns.
                    self.cooldown.reset(True)
                    self._emit("skill_state_cooldown_reset", remaining_raw=self.cooldown.remaining.raw)
                else:
                    self._emit("after_skill", failed=True)
                    self._switch(self.IDLE)
            self._emit("state_changed", state=state, previous=old)
        finally:
            self._switch_busy = False
            # ScopeDisposal dequeues one then recursively drains on disposal.
            if self._pending:
                self._switch(self._pending.popleft())

    @property
    def sp_enough(self):
        # MathUtil.GE(sp,cost) is strict sp > cost-EN5.
        return self.sp.raw > FP.from_int32(self.context.sp_cost).raw - FP_LARGE_EPS_RAW

    @property
    def ready(self):
        return self.context.ability_available and self.cooldown.ready and not self.is_casting

    def fixed_tick(self, delta: FP):
        if not self.initialized:
            raise UnverifiedSkillContext("initialize before ticking")
        self.context.validate()
        if not isinstance(delta, FP) or delta.raw <= 0:
            raise ValueError("positive FP delta required")
        if not self.unity_owner.available():
            raise UnverifiedSkillContext("destroyed/inactive owner context is not closed")
        if not self.alive:
            raise UnverifiedSkillContext("owner death transition requires lifecycle integration")
        # Selected FSM.Tick has no escape/abnormal work in Idle, and in Skill
        # escape remains -ONE until normal finish callback (escapeTime is zero).
        if self.state == self.SKILL and not self.context.owner_can_use_skill:
            raise UnverifiedSkillContext("canUseAbility interruption is outside this context")
        count = self.sp_controller.on_tick(
            delta, sp_recover_stopped=self.registered_as_modifier or self.allow_other_sp_stop,
            timer_valid=True)
        if count:
            self._emit("sp_recovered", count=count, sp_raw=self.sp.raw)
        frame, _ = self.clock()
        # Entity skips registered Ability.OnTick on the first casting frame.
        if frame != self.cast_start_frame or not self.is_casting:
            self.cooldown.tick(delta)
        # BasicSkill.OnTick runs after Entity SP/cooldown. Its modifier release
        # can therefore only affect SP recovery starting in the following frame.
        self._register_modifier(self.is_casting)
        if self.context.owner_can_use_skill and self.ready and self.sp_enough:
            self._emit("auto_admitted")
            self._switch(self.SKILL)

    def _cast(self):
        if not self.alive or not self.sp_enough or not self.unity_owner.available():
            return False
        if self.is_casting:
            raise UnverifiedSkillContext("overlapping cast requires a different skill path")
        # CastDirectly selects AT_BEGINING before StartCastingInternal.
        self.targets = tuple(self.select_targets())
        self._emit("target_snapshot", count=len(self.targets))
        self.cooldown.reset(True)
        self.is_casting = True
        self.cast_start_frame, _ = self.clock()
        self.cast_count += 1
        self._duration_at_begin = self.context.prepared_duration
        self._emit("skill_start", cast=self.cast_count, sp_raw=self.sp.raw)
        self._handle = self.simulator.start(self.unity_owner, self._do_cast())
        # Native DoCast deducts SP after StartBattleCoroutine's immediate prime.
        self._write_sp(self.sp - FP.from_int32(self.context.sp_cost))
        self._emit("sp_consumed", cost=self.context.sp_cost, sp_raw=self.sp.raw)
        self._register_modifier(True)
        self._emit("cast_succeeded", cast=self.cast_count)
        return True

    def _pre_delay(self):
        _, self._pre_started_at = self.clock()
        self._emit("pre_delay_begin", delay_raw=self.context.prepared_pre_delay.raw)
        yield fp_fixed_seconds(self.context.prepared_pre_delay, self.context.delta_play_time_float)

    def _post_delay(self):
        _, now = self.clock()
        delay = FP(max(0, (self._duration_at_begin - (now - self._pre_started_at)).raw))
        self._emit("post_delay_begin", delay_raw=delay.raw)
        yield fp_fixed_seconds(delay, self.context.delta_play_time_float)

    def _do_cast(self):
        yield self._pre_delay()
        self._emit("spell", cast=self.cast_count, target_count=len(self.targets))
        self.spell(self.targets)
        if not self.is_casting:
            raise UnverifiedSkillContext("spell callback cancelled ability; interruption not closed")
        # Base CheckAnotherSpell is constant false without a hotfix override.
        yield self._post_delay()
        self._finish()

    def _finish(self):
        if not self.is_casting:
            return False
        # FinishIfNot saves callbacks; Cleanup clears casting before OnCastEnd.
        self.is_casting = False
        self.cast_start_frame = 0
        self._emit("ability_cleanup")
        if (abs((self._duration_at_begin - self.context.prepared_cooldown).raw) < FP_LARGE_EPS_RAW
                and self.cooldown.remaining.raw < self.context.half_default_frame.raw - FP_LARGE_EPS_RAW):
            self.cooldown.reset(False)
            self._emit("half_frame_cooldown_reset")
        self._emit("skill_end", cast=self.cast_count)
        # CastSkill.OnCastFinish then captured SkillState callback/escapeTime0.
        self._emit("after_skill", failed=False)
        self._switch(self.IDLE)
        return True


def verify_skill_evidence(*, check_native_bytes=True):
    """Validate pinned inputs and exact native ranges without executing client."""
    from pathlib import Path
    import hashlib
    import json
    path = Path(__file__).resolve().parents[1] / "evidence/skill_runtime/native_manifest.json"
    manifest = json.loads(path.read_text(encoding="utf-8"))
    failures = []
    for f in manifest["files"]:
        p = Path(f["path"])
        if not p.is_file() or hashlib.sha256(p.read_bytes()).hexdigest() != f["sha256"]:
            failures.append(f["path"])
    if check_native_bytes:
        p = Path(manifest["target_path"])
        with p.open("rb") as stream:
            for r in manifest["native_ranges"]:
                stream.seek(r["file_offset"])
                if hashlib.sha256(stream.read(r["size"])).hexdigest() != r["sha256"]:
                    failures.append(r["start"])
    return {"healthy": not failures, "failures": failures,
            "files": len(manifest["files"]), "native_ranges": len(manifest["native_ranges"]),
            "client_runtime_compared": False, "hotfix_runtime_compared": False}

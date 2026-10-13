"""Device kernels recovered from the pinned PC native artifact.

These are composable components, not a complete battle loop. Callers must
provide verified owner/selector/damage contexts. No absent context silently
means "false", and a damage action request is not an HP settlement oracle.
Evidence: native_v5/devices and native_v5/core rounds 1-3.
"""
from __future__ import annotations

from collections.abc import Callable, Iterable
from dataclasses import dataclass

from .fp import FP, binary32
from .coroutines import CoroutineRunner, fixed_seconds, float_wait_frames


class UnverifiedDeviceContext(ValueError):
    """A necessary native path or explicit scene input has not been supplied."""


# MathUtil .cctor copies FP.EN5, whose FP .cctor constructs One / 100000.
# The recovered FP division rounds this to 42950, unlike float32(0.00001).
FP_LARGE_EPS_RAW = (FP.from_int32(1) / FP.from_int32(100000)).raw


def _flag(value, name: str) -> bool:
    if type(value) is not bool:
        raise UnverifiedDeviceContext(f"{name} must be an explicit bool")
    return value


@dataclass
class PrecisePeriodicTimer:
    """UpdateMultiple / NextMultiple with MathUtil.LE's strict epsilon bound."""

    period: FP
    remaining: FP

    def __post_init__(self):
        if not isinstance(self.period, FP) or not isinstance(self.remaining, FP):
            raise TypeError("timer values must be FP")
        if self.period.raw <= 0:
            raise UnverifiedDeviceContext("positive timer period required")

    @classmethod
    def reset(cls, period: FP) -> PrecisePeriodicTimer:
        return cls(period, period)

    @property
    def ready(self) -> bool:
        # MathUtil.LE(a,b) -> FP.op_LessThan(a, b + FP_LARGE_EPS).
        return self.remaining.raw < FP_LARGE_EPS_RAW

    def update_multiple(self, delta: FP) -> int:
        if not isinstance(delta, FP) or delta.raw < 0:
            raise ValueError("timer delta must be nonnegative FP")
        self.remaining = self.remaining - delta
        if not self.ready:
            return 0
        count = max(0, ((-self.remaining) / self.period).raw >> 32) + 1
        if count >= 1 << 31:
            raise UnverifiedDeviceContext("timer count outside supported int32 scope")
        return count

    def next_multiple(self, count: int) -> bool:
        if type(count) is not int or not 0 <= count < 1 << 31:
            raise ValueError("count must be a nonnegative int32")
        if not self.ready:
            return False
        self.remaining = self.remaining + self.period * FP.from_int32(count)
        return True

    def tick(self, delta: FP) -> int:
        count = self.update_multiple(delta)
        if count > 0:
            self.next_multiple(count)
        return count


@dataclass
class NaturalSpController:
    """SpController.OnTick for a verified time-recovery owner.

    Entity.set_sp is an explicit injected native-context operation because it
    includes owner-specific clamps and events. The timer does not advance while
    stopped or full, matching the early returns before UpdateMultiple.
    """

    timer: PrecisePeriodicTimer
    read_sp: Callable[[], FP]
    write_sp: Callable[[FP], None]
    max_sp: int
    sp_type: int

    @classmethod
    def reset(cls, recovery_per_sec: FP, read_sp: Callable[[], FP],
              write_sp: Callable[[FP], None], *, max_sp: int,
              sp_type: int) -> NaturalSpController:
        if recovery_per_sec.raw <= 0:
            raise UnverifiedDeviceContext("positive verified SP recovery rate required")
        if type(max_sp) is not int or not 0 <= max_sp < 1 << 31:
            raise ValueError("max_sp must be a nonnegative int32")
        if type(sp_type) is not int or not 0 <= sp_type <= 7:
            raise ValueError("invalid SpType mask")
        if not callable(read_sp) or not callable(write_sp):
            raise UnverifiedDeviceContext("owner SP getter and setter must be supplied")
        period = FP.from_int32(1) / recovery_per_sec
        return cls(PrecisePeriodicTimer.reset(period), read_sp, write_sp, max_sp, sp_type)

    def on_tick(self, delta: FP, *, sp_recover_stopped: bool,
                timer_valid: bool) -> int:
        stopped = _flag(sp_recover_stopped, "sp_recover_stopped")
        valid = _flag(timer_valid, "timer_valid")
        if not self.sp_type & 1 or not valid or stopped:
            return 0
        sp = self.read_sp()
        if not isinstance(sp, FP):
            raise TypeError("owner SP getter must return FP")
        # SpController.get_isFull delegates directly to raw FP >=.
        if sp.raw >= FP.from_int32(self.max_sp).raw:
            return 0
        count = self.timer.tick(delta)
        if count > 0:
            self.write_sp(self.read_sp() + FP.from_int32(count))
        return count


@dataclass
class ImmediateBuffLifecycle:
    """The already verified IMMEDIATELY/zero-duration path of NewBuff.

    ON_BUFF_START runs before m_started=true. NewBuff then finds the started
    zero-life buff finished, synchronously invokes ON_BUFF_FINISH and removes
    it. General durable/override/derived-buff behavior is outside this kernel.
    """

    life_time: FP
    started: bool = False
    marked_finished: bool = False
    finish_ran: bool = False

    def __post_init__(self):
        if not isinstance(self.life_time, FP):
            raise TypeError("buff life_time must be FP")
        if self.life_time.raw == -(1 << 63):
            raise UnverifiedDeviceContext("FP.Abs overflow sentinel is outside the immediate-buff scope")
        for name in ["started", "marked_finished", "finish_ran"]:
            _flag(getattr(self, name), name)

    @property
    def is_finished(self) -> bool:
        return self.marked_finished or (
            self.started and abs(self.life_time.raw) < FP_LARGE_EPS_RAW)

    def attach_to_born_owner(self, on_start: Callable[[], None],
                             on_finish: Callable[[], None]) -> None:
        if self.started or self.finish_ran:
            raise ValueError("buff instance has already been attached")
        if abs(self.life_time.raw) >= FP_LARGE_EPS_RAW:
            raise UnverifiedDeviceContext("only the immediate zero-life buff path is closed")
        on_start()
        self.started = True
        if self.is_finished:
            # _FinishBuff sets the idempotency flag before executing actions.
            self.marked_finished = True
            self.finish_ran = True
            on_finish()


@dataclass(frozen=True)
class FixedDamageAction:
    value: FP
    damage_type: int = 3  # DamageType.PURE
    attack_type: int = 0  # SourceAttackType.NONE
    consider_unhurtable: bool = False
    no_source_damage: bool = False
    trigger_on_calculate_damage: bool = False


def ore_finish_actions(*, contains_buff: Callable[[str], bool],
                       damage: Callable[[FixedDamageAction], None],
                       switch_mode: Callable[[int, bool], None], value: FP,
                       mode: int) -> tuple[str, ...]:
    """ore_s then ore_buff finish actions on one already selected target.

    Callbacks are required: selector geometry, buff-container membership,
    damage/HP hooks and mode/FSM restart are independently verified contexts.
    This function never equates a damage request with successful HP loss.
    """
    if not all(callable(f) for f in [contains_buff, damage, switch_mode]):
        raise UnverifiedDeviceContext("buff lookup, damage and mode callbacks are required")
    if not isinstance(value, FP) or type(mode) is not int:
        raise TypeError("value must be FP and mode must be an explicit int")
    events = []
    if not _flag(contains_buff("ore_immune"), "ContainsBuff(ore_immune)"):
        damage(FixedDamageAction(value))
        events.append("damage_requested")
    if _flag(contains_buff("ore_listener"), "ContainsBuff(ore_listener)"):
        switch_mode(mode, True)
        events.append("mode_switch_requested")
    return tuple(events)


class PreDelayAbility:
    """EasyToStartAbility's verified wait-for-event=false pre-delay component.

    Targets are a supplied snapshot from AT_BEGINING selection. The cast's
    admission, Character skill-state transition, full cooldown/finish and HP
    settlement are owned by the surrounding verified scene assembly.
    """

    def __init__(self, *, pre_delay_float32: float, delta_float32: float,
                 deterministic_simulator: bool, spell: Callable[[tuple], None]):
        if not _flag(deterministic_simulator, "deterministic_simulator"):
            raise UnverifiedDeviceContext("Unity coroutine scheduling has not been observed")
        if not callable(spell):
            raise UnverifiedDeviceContext("verified spell executor required")
        self.delay = binary32(pre_delay_float32)
        self.delta = binary32(delta_float32)
        self.wait_frames = float_wait_frames(self.delay, self.delta)
        self.spell = spell
        self.runner = None

    @property
    def active(self) -> bool:
        return self.runner is not None and self.runner.active

    def begin(self, targets: Iterable, *, wait_for_attack_event: bool,
              interrupt_if_target_dead: bool) -> bool:
        if self.active:
            raise ValueError("ability already active")
        if _flag(wait_for_attack_event, "wait_for_attack_event"):
            raise UnverifiedDeviceContext("animation attack-event wait is not closed")
        if _flag(interrupt_if_target_dead, "interrupt_if_target_dead"):
            raise UnverifiedDeviceContext("conditional wait-for-target path is not closed")
        snapshot = tuple(targets)

        def cast():
            yield fixed_seconds(self.delay, self.delta)
            self.spell(snapshot)

        self.runner = CoroutineRunner(cast())
        # CastDirectly -> StartBattleCoroutine (deterministic branch) ->
        # CoroutineSimulator.StartCoroutine synchronously calls MoveNext.
        # This consumes the first wait marker at the begin frame itself.
        return self.runner.tick()

    def tick(self) -> bool:
        if self.runner is None:
            return False
        return self.runner.tick()


def verify_device_evidence(*, check_native_bytes: bool = False) -> dict:
    """Check pinned derived artifacts and optionally original PE range bytes.

    This read-only verification does not certify live hotfix state, the Unity
    branch, scene admission, damage hooks or a complete idle battle outcome.
    """
    import hashlib
    import json
    from pathlib import Path

    _flag(check_native_bytes, "check_native_bytes")
    root = Path(__file__).resolve().parents[1]
    manifest = json.loads((root / "evidence/devices/native_manifest.json").read_text("utf-8"))
    errors = []
    files_checked = 0
    for item in manifest["files"]:
        path = Path(item["path"])
        if not path.is_file():
            errors.append(f"missing: {path}")
            continue
        digest = hashlib.sha256(path.read_bytes()).hexdigest()
        files_checked += 1
        if digest != item["sha256"]:
            errors.append(f"SHA256 changed: {path}")
    ranges_checked = 0
    if check_native_bytes:
        with Path(manifest["target_path"]).open("rb") as target:
            for item in manifest["native_ranges"]:
                target.seek(item["file_offset"])
                body = target.read(item["bytes"])
                ranges_checked += 1
                if hashlib.sha256(body).hexdigest() != item["sha256"]:
                    errors.append(f"native body changed: {item['start']}")
    return {
        "healthy": not errors,
        "files_checked": files_checked,
        "native_ranges_checked": ranges_checked,
        "static_functions": manifest["static_functions"],
        "csharp_component_checks": manifest["csharp_component_checks"],
        "client_runtime_compared": False,
        "hotfix_runtime_compared": False,
        "complete_idle_scene_supported": False,
        "remaining": manifest["remaining"],
        "errors": errors,
    }

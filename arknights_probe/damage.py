"""Static PURE damage components; scene and active-rule gates are explicit.

The target client and its hotfix dispatch are never executed. This module's
arithmetic helpers do not certify arbitrary enemy damage/finish hooks.
"""
from __future__ import annotations

from dataclasses import dataclass
from copy import deepcopy

from .coroutines import fixed_seconds
from .data import require
from .devices import FixedDamageAction
from .env import UnverifiedMechanism
from .fp import FP
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from .lifecycle import ALIVE_EPSILON_RAW, LifecycleRuntime, SINGLE_EPSILON, STOPPED_STATE


PURE_DAMAGE_TYPE = 3
NONE_ATTACK_TYPE = 0

DAMAGE_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "BattleFormula.CalculateDamageInternal": "0x180656ba0",
    "AttackInfo.GetFinalAtk": "0x180648250",
    "Entity.ApplyModifier": "0x1806efd80",
    "Entity.DoApplyModifier": "0x1806f1c00",
    "Entity.SetHpInternal": "0x1806fd230",
    "Enemy.OnHpZero": "0x180a70e80",
    "client_runtime_compared": False,
}


def pure_damage_value(value: FP, atk_scale: FP) -> FP:
    """PURE branch with ordinary AttackInfo additive attack=FP.Zero.

    GetFinalAtk multiplies attack and scale with native FP arithmetic, then
    takes max(FP.Zero, result). PURE returns it without defense/MR calculations.
    """
    require(isinstance(value, FP) and isinstance(atk_scale, FP), "Damage and scale require FP")
    product = value * atk_scale
    return FP.from_raw(max(0, product.raw))


def ordinary_hp_write(requested_hp: FP, max_hp: FP) -> FP:
    """SetHpInternal's admitted no-minus-health/no-undead/no-hook clamp.

    The caller must close SetHpInternal admission and the BeforeTrySetHpZero
    callback. Native MathUtil.LE(hp, Zero) snaps hp < EN5 to zero. Equality
    remains EN5, while get_alive's strict GT test is false at that value.
    """
    require(isinstance(requested_hp, FP) and isinstance(max_hp, FP), "HP requires FP")
    require(max_hp.raw > 0, "Maximum HP must be positive")
    raw = max(0, min(requested_hp.raw, max_hp.raw))
    return FP.from_raw(0 if raw < ALIVE_EPSILON_RAW else raw)


@dataclass(frozen=True)
class DamageShape:
    """Reviewed ordinary entity inputs, before runtime damage hooks.

    Empty action/template inputs describe an explicit offline scenario. They
    are not observations that a live Rogue run has no attached modifiers.
    The altar's frosts_effect passive has flags but an empty action template.
    """
    max_hp: FP
    source_id: str
    source_key: str
    source_buff_keys: tuple[str, ...]
    source_exists: bool
    source_action_slots_empty: bool
    target_template_keys: tuple[str, ...]
    projectile_hit_failed: bool | None
    ability_hit_failed: bool | None
    invincible: bool
    unharmful: bool
    undeadable: bool
    max_minus_hp: FP
    es: FP
    sp_recover_on_damage: bool
    target_talents: tuple[str, ...]
    use_specific_dead_anim: bool
    blocked: bool
    active_enemy_skills: tuple[str, ...]
    level_event_handlers: tuple[str, ...]
    context_source: str
    fixture: bool = False

    def validate(self, enemy_key: str):
        require(isinstance(self.max_hp, FP) and self.max_hp.raw > ALIVE_EPSILON_RAW, "Positive max HP above EN5 required")
        require(isinstance(self.max_minus_hp, FP) and isinstance(self.es, FP), "Minus HP and shield require FP")
        require(all(type(x) is str and x for x in (self.source_id, self.source_key, self.context_source)),
                "Explicit source identity and reviewed context required")
        flags = (self.source_exists, self.source_action_slots_empty, self.invincible, self.unharmful,
                 self.undeadable, self.sp_recover_on_damage,
                 self.use_specific_dead_anim, self.blocked, self.fixture)
        require(all(type(x) is bool for x in flags), "Damage gates must be explicit bool")
        if not self.source_exists:
            raise UnverifiedMechanism("This damage path requires an existing SOURCE entity")
        if not self.source_action_slots_empty:
            raise UnverifiedMechanism("Source action slots must be explicitly initialized and empty")
        require(all(x is None or type(x) is bool for x in (self.projectile_hit_failed, self.ability_hit_failed)),
                "Projectile/ability hit-failed snapshots must be bool or absent None")
        for keys in (self.source_buff_keys, self.target_template_keys, self.target_talents,
                     self.active_enemy_skills, self.level_event_handlers):
            require(type(keys) is tuple and all(type(x) is str and x for x in keys), "Reviewed rule keys require tuples")
        if self.target_template_keys or self.target_talents or self.active_enemy_skills or self.level_event_handlers:
            raise UnverifiedMechanism("Active target, rebirth, skill or level-event rules are outside ordinary damage scope")
        if self.unharmful or self.undeadable or self.max_minus_hp.raw or self.es.raw or self.sp_recover_on_damage:
            raise UnverifiedMechanism("Ordinary damage requires no unharmful, undead, minus-health, shield or damaged-SP branch")
        if self.use_specific_dead_anim or self.blocked:
            raise UnverifiedMechanism("Specific death animation delay or blocker interactions are not supported")
        if not self.fixture and enemy_key != "enemy_1034_laxe":
            raise UnverifiedMechanism("Only the reviewed laxe prefab's target-buff-free shape is supported")
        if enemy_key in ("enemy_2133_shdopl", "enemy_3001_upeopl") or "trap" in enemy_key:
            raise UnverifiedMechanism("NPC/box death and damage hooks require separate rule execution")
        if not self.fixture and (self.source_key != "trap_011_ore" or self.source_buff_keys != ("frosts_effect",)):
            raise UnverifiedMechanism("Only reviewed altar frosts_effect with empty actions is supported as source")
        if self.fixture and self.source_buff_keys not in ((), ("frosts_effect",)):
            raise UnverifiedMechanism("Source buff actions must be empty or the reviewed frosts_effect declaration")


def ordinary_altar_shape(*, max_hp: FP, source_id: str, projectile_hit_failed: bool | None,
                         ability_hit_failed: bool | None, context_source: str) -> DamageShape:
    """Declare the reviewed laxe/altar offline shape, excluding dynamic rules.

    The enclosing scene must supply the actual max HP, source identity and hit
    failure snapshots. This declaration cannot certify live modifier absence.
    """
    return DamageShape(max_hp=max_hp, source_id=source_id, source_key="trap_011_ore",
                       source_buff_keys=("frosts_effect",), source_exists=True,
                       source_action_slots_empty=True,
                       target_template_keys=(), projectile_hit_failed=projectile_hit_failed,
                       ability_hit_failed=ability_hit_failed, invincible=False, unharmful=False,
                       undeadable=False, max_minus_hp=FP.from_raw(0), es=FP.from_raw(0),
                       sp_recover_on_damage=False, target_talents=(), use_specific_dead_anim=False,
                       blocked=False, active_enemy_skills=(), level_event_handlers=(),
                       context_source=context_source)


@dataclass(frozen=True)
class DamageResult:
    applied: bool
    cancel_reason: int
    calculated: FP
    applied_delta: FP
    hp_before: FP
    hp_after: FP
    killed: bool
    finish_reason: int


class DamageRuntime:
    """PURE/NONE kernel using shared lifecycle actors and coroutine phases.

    The shared simulator and Unity owner state are required inputs. This class
    does not advance the frame or run active abilities, physical selectors,
    death visuals, logger output or live hotfix delegates.
    """
    def __init__(self, lifecycle: LifecycleRuntime, simulator: SharedCoroutineSimulator, *, context_source: str):
        require(isinstance(lifecycle, LifecycleRuntime) and isinstance(simulator, SharedCoroutineSimulator),
                "Damage needs a logical lifecycle and shared deterministic simulator")
        require(type(context_source) is str and context_source, "Damage context source is required")
        self.lifecycle, self.simulator = lifecycle, simulator
        self.context_source = context_source
        self.shapes: dict[str, DamageShape] = {}
        self.owners: dict[str, CoroutineOwner] = {}
        self.recycle_handles: dict[str, int] = {}

    def attach(self, identifier: str, shape: DamageShape, *, recycle_owner: CoroutineOwner):
        require(identifier in self.lifecycle.enemies and identifier not in self.shapes, "Attach an existing unique lifecycle actor")
        require(isinstance(shape, DamageShape) and isinstance(recycle_owner, CoroutineOwner), "Reviewed shape and Unity owner required")
        actor = self.lifecycle.enemies[identifier]
        shape.validate(actor.enemy_key)
        require(0 <= actor.hp.raw <= shape.max_hp.raw, "Actor HP must lie within supplied max HP")
        self.shapes[identifier], self.owners[identifier] = shape, recycle_owner

    def _hook(self, identifier, callback, *, event_domain=None, event_id=None):
        self.lifecycle._event("damage_hook", id=identifier, callback=callback,
                              event_domain=event_domain, event_id=event_id,
                              rule_actions_executed=0)

    def _schedule_recycle(self, actor):
        if actor.recycle_delay <= SINGLE_EPSILON:
            self.lifecycle._recycle(actor)
            return
        def recycle():
            yield fixed_seconds(actor.recycle_delay, self.lifecycle.dt.as_float())
            self.lifecycle._recycle(actor)
        self.lifecycle._event("enemy_recycle_scheduled", id=actor.identifier,
                              delay_single=actor.recycle_delay, scheduler="shared_coroutine_simulator")
        self.recycle_handles[actor.identifier] = self.simulator.start(self.owners[actor.identifier], recycle())

    def _finish_hp_zero(self, actor, shape):
        self._hook(actor.identifier, "OnOwnerBeforeDead")
        actor.state_id = 5
        self.lifecycle._event("enemy_dead_state", id=actor.identifier, state_id=5,
                              visual_backend="excluded", recycle_delay_changed=False)
        # Enemy.FinishMe first enters DEAD5; Entity.FinishMe then stops the FSM
        # before virtual OnFinish. Non-specific Die animation retains delay.
        actor.finish_reason, actor.state_id = 2, STOPPED_STATE
        self.lifecycle._event("enemy_finished", id=actor.identifier, finish_reason=2,
                              state_id=STOPPED_STATE, source=shape.source_id)
        self._hook(shape.source_id, "OnTargetKilled", event_domain="buff", event_id=9)
        self.lifecycle._event("enemy_killed", id=actor.identifier, source=shape.source_id,
                              event_domain="entity", event_id=1)
        self.lifecycle.wave_ids.discard(actor.identifier)
        if not self.lifecycle.use_recycle_to_finish_scheduler:
            self.lifecycle.final_ids.discard(actor.identifier)
        self.lifecycle._event("enemy_wave_released", id=actor.identifier,
                              final_membership_retained=actor.identifier in self.lifecycle.final_ids)
        self._hook(actor.identifier, "Enemy.OnFinish.LevelEvent", event_domain="level", event_id=3)
        # Entity.FinishMe calls DefaultGameMode.DestroyEntity only after all
        # virtual OnFinish callbacks. Death chooses RecycleSelfWithDelay.
        self._schedule_recycle(actor)

    def apply(self, identifier: str, action: FixedDamageAction, *, atk_scale: FP,
              finished_transient_templates: tuple[str, ...] = ()) -> DamageResult:
        require(identifier in self.shapes, "Attach a reviewed damage shape before applying")
        require(isinstance(action, FixedDamageAction) and isinstance(atk_scale, FP), "Fixed action and FP scale required")
        require(type(action.damage_type) is int and type(action.attack_type) is int and
                all(type(x) is bool for x in (action.consider_unhurtable, action.no_source_damage,
                                             action.trigger_on_calculate_damage)), "Native action enums and flags required")
        if (action.damage_type != PURE_DAMAGE_TYPE or action.attack_type != NONE_ATTACK_TYPE or
            action.consider_unhurtable or action.no_source_damage or action.trigger_on_calculate_damage):
            raise UnverifiedMechanism("Only serialized ordinary PURE/NONE altar actions are closed")
        require(type(finished_transient_templates) is tuple and
                all(type(x) is str for x in finished_transient_templates), "Finished transient template snapshot required")
        if any(x not in ("ore_s", "ore_buff") for x in finished_transient_templates):
            raise UnverifiedMechanism("Only already finished ore_s/ore_buff transient buffs are reviewed")
        actor, shape = self.lifecycle.enemies[identifier], self.shapes[identifier]
        shape.validate(actor.enemy_key)
        before = actor.hp
        # FixedValueDamage calculates via BattleFormula before ApplyModifier's
        # get_alive gate. The retained logical target has an existing object;
        # its reviewed empty OnBeing action slots cannot change AttackInfo.
        self._hook(identifier, "OnBeingCalculateDamage")
        value = pure_damage_value(action.value, atk_scale)
        zero = FP.from_raw(0)
        if not actor.alive or actor.finish_reason or actor.recycled:
            return DamageResult(False, 0, value, zero, before, before, False, actor.finish_reason)
        if actor.state_id not in (1, 6):
            raise UnverifiedMechanism("Ordinary damage supports Move/Born state entry only")
        hit_failed = (shape.projectile_hit_failed if shape.projectile_hit_failed is not None
                      else shape.ability_hit_failed if shape.ability_hit_failed is not None else False)
        # Modifier.Cancel keeps the first reason: later Cancel calls return0.
        cancel = 1 if shape.invincible else 6 if hit_failed else 0
        after = before if cancel else ordinary_hp_write(before - value, shape.max_hp)
        if finished_transient_templates:
            self.lifecycle._event("damage_finished_transients_ignored", id=identifier,
                                  templates=list(finished_transient_templates),
                                  native_gate="Buff.isFinishedOrDisabled_true")
        self._hook(identifier, "OnBeforeApplyingModifier", event_domain="entity", event_id=8)
        self._hook(shape.source_id, "OnOutputModifier", event_domain="entity", event_id=11)
        self._hook(shape.source_id, "OnOutputDamage", event_domain="entity", event_id=14)
        self._hook(identifier, "OnApplyingModifier", event_domain="entity", event_id=9)
        self._hook(identifier, "OnTakeDamage", event_domain="entity", event_id=12)
        if cancel:
            self.lifecycle._event("damage_cancelled", id=identifier, cancel_reason=cancel, hp_raw=before.raw)
            return DamageResult(False, cancel, value, zero, before, before, False, actor.finish_reason)
        self._hook(shape.source_id, "OnBeforeTargetApplyModifier")
        if after.raw == 0:
            self._hook(identifier, "OnBeforeTrySetHpZero")
        actor.hp = after
        self.lifecycle._event("enemy_hp_written", id=identifier, hp_before_raw=before.raw, hp_raw=after.raw)
        killed = after.raw == 0
        if killed:
            self._finish_hp_zero(actor, shape)
        delta = after - before
        self._hook(identifier, "OnAppliedModifier", event_domain="entity", event_id=10)
        self._hook(shape.source_id, "OnAfterOutputDamage")
        return DamageResult(True, 0, value, delta, before, after, killed, actor.finish_reason)

    def info(self):
        return {"scope": "reviewed_PURE_NONE_damage_component", "context_source": self.context_source,
                "target_rules": "empty", "source_rules": "frosts_effect_empty_actions",
                "source_action_initialization": "explicit_empty_slot_context_before_kernel",
                "death_visuals": "excluded", "death_admission_verified": True,
                "death_recycle_delay": "retained_only_when_useSpecificDeadAnim_false",
                "trace_scope": "selected_damage_and_lifecycle_hooks",
                "client_runtime_compared": False, "complete_idle_scene_supported": False,
                "native_evidence": deepcopy(DAMAGE_EVIDENCE)}

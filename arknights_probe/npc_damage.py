"""Selected Entity/Unit OnTakeDamage reaction, before the HP write stage.

The caller supplies a decoded HP damage modifier and source-bound gate inputs.
This is not ApplyModifier, damage calculation, physics, or an HP update. The
native reaction may synchronously finish/recycle its owner inside Buff hooks;
the remaining Entity and Unit callbacks still run in their original order.
"""
from __future__ import annotations

from dataclasses import dataclass
from typing import Callable

from .data import require
from .env import UnverifiedMechanism
from .fp import FP
from .npc_actions import EntityPtr, NpcEntity


@dataclass
class NpcDamagePacket:
    source: EntityPtr
    target: EntityPtr
    value: FP
    shared_flags: int = 0
    skip_sp_recovery: bool = False
    cancel_reason: int = -1

    def validate(self):
        require(isinstance(self.source, EntityPtr) and isinstance(self.target, EntityPtr),
                "Decoded modifier source and target pointers required")
        require(isinstance(self.value, FP) and self.value.raw >= 42950,
                "Selected nonzero HP damage value must be at least native EN5")
        require(type(self.shared_flags) is int and self.shared_flags == 0,
                "Ignore-cancel/shared modifier branches are outside this selected shape")
        require(type(self.skip_sp_recovery) is bool and type(self.cancel_reason) is int,
                "Decoded modifier flags and cancellation state required")
        require(self.cancel_reason in (-1, 0, 1, 6), "Only selected native cancel reasons are admitted")

    @property
    def is_cancelled(self):
        # The selected positive value excludes the native abs(value)<EN5 case.
        # Cancel sets deltaType=NONE0; cancel_reason records that transition.
        return self.cancel_reason >= 0

    @property
    def final_delta(self):
        return FP.from_raw(0 if self.is_cancelled else -self.value.raw)

    def cancel(self, reason: int):
        require(reason in (0, 1, 6), "Selected damage cancellation reason required")
        if self.is_cancelled:
            return False
        self.cancel_reason = reason
        return True


@dataclass(frozen=True)
class DamageReactionInputs:
    source: str
    native_default_no_hotfix: bool
    is_disappeared: bool
    is_unhurtable_with_modifier: bool
    ability_damage_miss: bool
    bypass_unhurtable: bool
    sp_controller_exists: bool
    sp_recovery_type: int
    mode_backend: str

    def validate(self):
        require(type(self.source) is str and self.source, "Gate input provenance required")
        require(all(type(x) is bool for x in (
            self.native_default_no_hotfix, self.is_disappeared,
            self.is_unhurtable_with_modifier, self.ability_damage_miss,
            self.bypass_unhurtable, self.sp_controller_exists)), "Explicit reaction gates required")
        require(type(self.sp_recovery_type) is int and self.sp_recovery_type >= 0,
                "Decoded SP recovery type required")
        if not self.native_default_no_hotfix or self.mode_backend != "DefaultGameMode":
            raise UnverifiedMechanism("Only the selected default non-hotfix reaction is admitted")
        if self.sp_recovery_type & 4:
            raise UnverifiedMechanism("Damage SP recovery amount/controller branch remains external")


@dataclass(frozen=True)
class DamageReactionCallbacks:
    buff_on_take_damage: Callable[[NpcDamagePacket], object]
    mode_finalize: Callable[[NpcEntity, NpcDamagePacket], None]
    entity_event: Callable[[NpcEntity, int, NpcDamagePacket], None]
    animator_on_take_damage: Callable[[NpcEntity, NpcDamagePacket], None]
    source: str

    def validate(self):
        require(type(self.source) is str and self.source, "Reaction callback provenance required")
        require(all(callable(x) for x in (self.buff_on_take_damage, self.mode_finalize,
                self.entity_event, self.animator_on_take_damage)), "Reaction providers required")


class NpcDamageReactionRuntime:
    def __init__(self, callbacks: DamageReactionCallbacks):
        callbacks.validate()
        self.callbacks = callbacks
        self.events = []

    def react(self, owner: NpcEntity, packet: NpcDamagePacket, inputs: DamageReactionInputs):
        require(isinstance(owner, NpcEntity), "Same native owner identity required")
        packet.validate()
        inputs.validate()
        require(packet.target.resolve() is owner, "Modifier target must resolve to this owner at entry")
        # This method deliberately has no get_alive check: that belongs to the
        # caller's ApplyModifier entry, not Entity/Unit.OnTakeDamage itself.
        self.events.append("entity_on_take_damage")
        if inputs.is_disappeared:
            packet.cancel(0)
            self.events.append("disappeared_early_return")
        else:
            if not inputs.bypass_unhurtable and inputs.is_unhurtable_with_modifier:
                packet.cancel(1)
            if inputs.ability_damage_miss:
                packet.cancel(6)
            require(inputs.sp_controller_exists, "Entity.OnTakeDamage requires a nonnull SP controller")
            self.events.append("buff_container_on_take_damage")
            self.callbacks.buff_on_take_damage(packet)
            # Cancellation does not suppress the Buff event, mode finalize or
            # Entity event12. UID/alive may change during the Buff callback.
            self.events.append("mode_finalize_entity_damage")
            self.callbacks.mode_finalize(owner, packet)
            self.events.append("entity_event_12")
            self.callbacks.entity_event(owner, 12, packet)
        # Unit checks cancellation after its base call, with no new alive gate.
        if not packet.is_cancelled:
            self.events.append("unit_animator_on_take_damage")
            self.callbacks.animator_on_take_damage(owner, packet)
        return {"cancelled": packet.is_cancelled, "cancel_reason": packet.cancel_reason,
                "owner_uid_after": owner.uid, "owner_alive_after": owner.alive,
                "hp_write_executed": False, "apply_modifier_completed": False,
                "client_runtime_compared": False}

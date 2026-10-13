"""Source-prepared altar composition with external Physics2D overlap inputs."""
from __future__ import annotations

from pathlib import Path

from .altar_component import AltarComponentProbe
from .data import read_json, require
from .fp import FP
from .frame_runtime import CoroutineOwner, NativeObjectRegistry, RegisteredObject
from .skill_preparation import prepare_altar_skill
from .skill_runtime import AltarSkillRuntime, explicit_altar_fixture_context
from .targeting import TargetSnapshot, ColliderOverlapSnapshot, OverlapQuerySnapshot
from .targeting_runtime import (RuntimeAltarContext, RuntimeTargetData,
    AbnormalStatus, HitRangeManager, select_altar_targets_runtime)

RESOURCE_INPUTS = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v7\skill_preparation\resource_inputs.json")


def _source_side_from_prefab():
    resource = read_json(RESOURCE_INPUTS)
    prefabs = [p for p in resource["prefabs"] if p["name"] == "trap_011_ore"]
    require(len(prefabs) == 1, "Expected one reviewed altar prefab")
    components = [c for c in prefabs[0]["rule_components"]
                  if c["class_name"] == "Torappu.Battle.Trap"]
    require(len(components) == 1, "Expected one altar Trap component")
    side = components[0]["fields"]["_sideType"]
    require(type(side) is int and side == 2, "Reviewed altar side changed")
    return side


def _preparation_dict(prepared):
    return {
        "skill_id": prepared.skill_id, "range_id": prepared.range_id,
        "pre_delay_raw": prepared.pre_delay.raw,
        "duration_raw": prepared.duration.raw, "cooldown_raw": prepared.cooldown.raw,
        "sp_cost": prepared.sp_cost, "init_sp": prepared.init_sp,
        "sp_increment_raw": prepared.sp_increment.raw,
        "sp_recovery_per_second_raw": prepared.sp_recovery_per_second.raw,
        "blackboard": dict(prepared.blackboard),
        "provenance": prepared.provenance,
        "remaining_external_context": prepared.remaining_external_context,
        "unity_initialization_executed": False,
    }


class PreparedAltarProbe(AltarComponentProbe):
    """Reuse immutable v6 lifecycle/damage, install v7 inputs before frame 1.

    Only the selected preparation and targeting components are new. Object
    existence, empty global effects, native field snapshots and collision
    membership remain the same explicitly bounded scene assumptions.
    """
    def __init__(self, dataset):
        prepared = prepare_altar_skill(dataset, native_default_no_hotfix=True,
                                      no_external_skill_modifier=True)
        super().__init__(dataset)
        require(self.loop.frame == 0 and self.simulator.next_handle == 0
                and not self.simulator.handlers,
                "Prepared context must be installed before any coroutine or frame")
        self.preparation = prepared
        self.source = "one source-prepared altar/one stationary laxe; explicit empty run modifiers; no live game"
        require(prepared.sp_cost == 7 and prepared.init_sp == 0
                and prepared.sp_increment.raw == FP.from_int32(1).raw,
                "Prepared SP input is outside the reviewed skill runtime")
        context = explicit_altar_fixture_context(source=self.source,
            prepared_time_source="reviewed skill_preparation resource/native computation; no external skill modifier",
            pre_delay=prepared.pre_delay, duration=prepared.duration,
            cooldown=prepared.cooldown, delta_play_time_float=self.dt.as_float(),
            half_default_frame=FP.from_raw(self.dt.raw // 2),
            sp_recovery_per_second=prepared.sp_recovery_per_second)
        self.skill = AltarSkillRuntime(context, simulator=self.simulator,
            unity_owner=CoroutineOwner(True, True),
            clock=lambda: (self.lifecycle.current_frame, self.lifecycle.time),
            select_targets=self._select, spell=self._spell)
        self.skill.initialize()
        self.registry = NativeObjectRegistry()
        self.registry.register(RegisteredObject(1, True, self.skill.fixed_tick, lambda _: None))
        self.registry.register(self.target_object)
        self.loop.registry = self.registry
        self.target_status = AbnormalStatus.zeroed_prepared_fixture(
            self.source + "; explicit zero abnormal count/base-mask state")
        self.hit_range = HitRangeManager((), self.source + "; explicit empty provider dictionary")
        self.selector_context = RuntimeAltarContext(
            source_side=_source_side_from_prefab(), source_map_layer=0,
            collider_count=self.inputs["collider_count"], deterministic=True,
            is_sandbox=False, custom_validator=None, excluded_uids=frozenset(),
            hotfixes_absent=True, source=self.source + "; mapLayer0/non-sandbox/empty exclusions fixture")
        self.selection_inputs = {
            "source_side": self.selector_context.source_side,
            "absolute_target_side_mask": self.selector_context.absolute_target_side_mask,
            "query_layer_mask": self.selector_context.query_layer_mask,
            "source_purpose_mask": self.selector_context.source_purpose_mask,
            "side_source": str(RESOURCE_INPUTS) + ": trap_011_ore Trap._sideType",
            "ALL_backend": "native weighted priority queue reconstruction",
            "HitRange_backend": "native manager with explicitly empty provider registry",
            "physics_backend": "external ordered overlap snapshots",
        }

    def _select(self):
        target = TargetSnapshot(uid=2 if not self.actor.recycled else 0,
            side=2, motion=0, category=1, map_layer=0, alive=self.actor.alive,
            destroyed=self.actor.recycled, ally_target_free=None, heal_free=None,
            camouflage=None, source=self.source + "; explicit actor native field snapshot")
        query = OverlapQuerySnapshot(tuple(ColliderOverlapSnapshot((target,), False,
            self.source + "; external overlap membership/order, no geometry calculation")
            for _ in range(self.inputs["collider_count"])),
            layer_mask=self.selector_context.query_layer_mask,
            source=self.source + "; query mask derived from reviewed side/layer declarations")
        targets = {target.uid: RuntimeTargetData(
            created_time=FP.from_raw(0), attributes=self.target_status, hit_range=self.hit_range,
            source=self.source + "; explicit Enemy.createdTime raw0 field fixture")}
        result = select_altar_targets_runtime(query, self.selector_context, targets)
        self.selections.append({"frame": self.lifecycle.current_frame, **result.as_dict()})
        return result.hits

    def artifact(self):
        artifact = super().artifact()
        external = artifact["external_inputs"]
        for key in ("ALL_filter", "layer_mask", "prepared_time", "HitRange"):
            external.pop(key)
        external.update(
            skill_and_global_modifiers="explicit absent; Unity init/owner/mode flags remain fixture",
            hit_range_providers="explicit empty provider registry",
            target_attributes="explicit zero abnormal counts/base immunity mask",
            native_field_snapshots="target side/motion/category/mapLayer and source mapLayer explicit",
            created_time="explicit Enemy.createdTime FP raw0; not inferred from spawn time",
            target_disappeared=False,
            legacy_damage_field="v6 unharmful gate represents BObject.isDisappeared+0x26; Enemy.Options.unharmful is separate",
            extra_mode="explicit non-sandbox fixture")
        artifact.update(scope="source_prepared_altar_with_native_ALL_and_external_physics",
                        preparation=_preparation_dict(self.preparation),
                        selection_inputs=dict(self.selection_inputs))
        return artifact

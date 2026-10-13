"""Controlled altar/laxe composition; physics and prepared-time inputs are fixtures."""
from __future__ import annotations

from pathlib import Path

from .data import read_json, require
from .enemy_data import resolve_enemy
from .fp import FP
from .targeting import construct_range_boxes
from .targeting import (TargetSnapshot, ColliderOverlapSnapshot, OverlapQuerySnapshot,
    PredicateSnapshot, AltarSelectorContext, AllPostFilterSnapshot, select_altar_targets)
from .devices import ImmediateBuffLifecycle, FixedDamageAction
from .damage import DamageRuntime, ordinary_altar_shape
from .frame_runtime import (CoroutineOwner, NativeObjectRegistry, RegisteredObject,
    SharedCoroutineSimulator, SelectedFrameLoop)
from .lifecycle import LifecycleRuntime
from .skill_runtime import AltarSkillRuntime, explicit_altar_fixture_context
from .timeline import ASSET_DEFAULT_DT_RAW

RANGE_FILE = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v5\resources\range_table.json")


def altar_declared_inputs(dataset):
    skill = dataset.tables["skills"]["skills"]["sktok_ore"]["levels"][0]
    require(skill["skillType"] == "AUTO" and skill["spData"]["spType"] == "INCREASE_WITH_TIME",
            "This component supports the reviewed AUTO/time-SP altar level only")
    require(skill["spData"]["maxChargeTime"] == 1 and skill["spData"]["spCost"] == 7
            and skill["spData"]["initSp"] == 0 and skill["spData"]["increment"] == 1.0,
            "Altar SP declarations changed")
    blackboard = {entry["key"]: entry["value"] for entry in skill["blackboard"]}
    require(set(blackboard) == {"value"} and blackboard["value"] == 500.0,
            "Altar damage declarations changed")
    ranges = read_json(RANGE_FILE)
    declaration = ranges[skill["rangeId"]]
    boxes = construct_range_boxes([(g["row"], g["col"]) for g in declaration["grids"]],
                                  direction=declaration["direction"])
    resolved = resolve_enemy(dataset.tables["enemies"], dataset.enemy_refs["enemy_1034_laxe"])
    return {"skill_level": skill, "range_id": skill["rangeId"], "range_source": str(RANGE_FILE),
            "range_boxes": [box.as_dict() for box in boxes], "collider_count": len(boxes),
            "max_hp": resolved.attributes["maxHp"], "damage_value": FP.from_float32(blackboard["value"]),
            "enemy_attribute_origin": "EnemyDB+level reference; explicit empty global modifiers",
            "scope": "declarations and pre-global enemy HP; range boxes are not Physics2D hit decisions"}


class AltarComponentProbe:
    """One stationary laxe and one initialized altar, with visible fixture inputs.

    This is a repeatable composition of selected components. It does not run
    enemy AI/movement, Unity overlap, native ALL ordering, Init/AssignData or
    the map scheduler. The external inputs below remain explicit in artifacts.
    """
    target_id = "laxe#1"

    def __init__(self, dataset):
        self.inputs = altar_declared_inputs(dataset)
        self.dataset = dataset
        self.dt = FP.from_raw(ASSET_DEFAULT_DT_RAW)
        self.source = "controlled one-altar/one-stationary-laxe fixture; empty global rules; no live game"
        self.simulator = SharedCoroutineSimulator(source=self.source, deterministic=True)
        self.registry = NativeObjectRegistry()
        self.lifecycle = LifecycleRuntime(initial_life=3, initial_temp_life=0, dt=self.dt,
            use_recycle_to_finish_scheduler=True, context_source=self.source)
        self.actor = self.lifecycle.spawn(self.target_id, "enemy_1034_laxe",
            max_hp=self.inputs["max_hp"], birth_delay=0, recycle_delay=.6,
            life_point_reduce=1, managed=True, wave_block=True, not_count_in_total=False,
            lifecycle_templates=())
        self.damage = DamageRuntime(self.lifecycle, self.simulator, context_source=self.source)
        self.damage.attach(self.target_id, ordinary_altar_shape(max_hp=self.inputs["max_hp"],
            source_id="altar#1", projectile_hit_failed=None, ability_hit_failed=False,
            context_source=self.source), recycle_owner=CoroutineOwner(True, True))
        self.selections, self.damage_results, self.buff_events = [], [], []
        skill_context = explicit_altar_fixture_context(source=self.source,
            prepared_time_source="explicit prepared field fixture: preDelay=.6,duration=0,cooldown=0; native preparation not executed",
            pre_delay=FP.from_float32(.6), duration=FP.from_raw(0), cooldown=FP.from_raw(0),
            delta_play_time_float=self.dt.as_float(), half_default_frame=FP.from_raw(ASSET_DEFAULT_DT_RAW // 2),
            sp_recovery_per_second=FP.from_int32(1))
        self.skill = AltarSkillRuntime(skill_context, simulator=self.simulator,
            unity_owner=CoroutineOwner(True, True),
            clock=lambda: (self.lifecycle.current_frame, self.lifecycle.time),
            select_targets=self._select, spell=self._spell)
        self.skill.initialize()
        self.registry.register(RegisteredObject(1, True, self.skill.fixed_tick, lambda _: None))
        self.target_object = RegisteredObject(2, True,
            lambda dt: self.lifecycle.tick_state(self.target_id, dt), lambda _: None)
        self.registry.register(self.target_object)
        self.lifecycle.on_event = self._lifecycle_event
        self.loop = SelectedFrameLoop(dt=self.dt, registry=self.registry, simulator=self.simulator,
            before_coroutines=(), after_coroutines=(), source=self.source + "; intervening modules explicitly empty")

    def _lifecycle_event(self, event):
        if event["kind"] == "enemy_recycled":
            # Clear validity during the coroutine callback, before the late
            # phase rebuilds its object snapshot.
            self.target_object.instance_uid = 0

    def _select(self):
        # This supplier explicitly replaces the Unity query. It does not test
        # a point against range grids or manufacture a native collision result.
        target = TargetSnapshot(uid=2 if not self.actor.recycled else 0,
            side=2, motion=0, category=1, map_layer=0, alive=self.actor.alive,
            destroyed=self.actor.recycled, ally_target_free=None, heal_free=None,
            camouflage=False, source=self.source + "; logical actor status snapshot")
        query = OverlapQuerySnapshot(tuple(ColliderOverlapSnapshot((target,), False,
            self.source + "; explicit overlap membership/order, no geometry calculation")
            for _ in range(self.inputs["collider_count"])), layer_mask=123,
            source=self.source + "; external Physics2D fixture, mask123 is not a live mask")
        context = AltarSelectorContext(source_side=4, source_map_layer=0, source_purpose_mask=1,
            absolute_target_side_mask=7, query_layer_mask=123, collider_count=self.inputs["collider_count"],
            opposite_side_mask=3, ability_ignores_camouflage=False, deterministic=True,
            hit_range=PredicateSnapshot({2: True}, self.source + "; explicit HitRange result"),
            has_custom_validator=False, custom_validator=None, excluded_uids=frozenset(), source=self.source)
        uids = (2,) if self.actor.alive and not self.actor.recycled else ()
        result = select_altar_targets(query, context,
            AllPostFilterSnapshot(uids, uids, self.source + "; external single-member ALL output"))
        self.selections.append({"frame": self.lifecycle.current_frame, **result.as_dict()})
        return result.hits

    def _spell(self, targets):
        # Selected executor: finished ore_s's event1 issues PURE/NONE damage.
        # laxe has no ore_listener, so the separate ore_buff mode action is a
        # no-op. General buff attachment or listener mode-switch is not modeled.
        for target in targets:
            require(target.uid == 2, "Only the reviewed laxe actor is supported")
            transient = ImmediateBuffLifecycle(FP.from_raw(0))
            def finish():
                require(transient.marked_finished, "Damage hook must see a finished transient")
                result = self.damage.apply(self.target_id, FixedDamageAction(self.inputs["damage_value"]),
                    atk_scale=FP.from_int32(1), finished_transient_templates=("ore_s",))
                self.damage_results.append({"frame": self.lifecycle.current_frame,
                    "applied": result.applied, "cancel_reason": result.cancel_reason,
                    "calculated_raw": result.calculated.raw, "applied_delta_raw": result.applied_delta.raw,
                    "hp_before_raw": result.hp_before.raw, "hp_after_raw": result.hp_after.raw,
                    "killed": result.killed, "finish_reason": result.finish_reason})
            transient.attach_to_born_owner(lambda: None, finish)
            self.buff_events.append({"frame": self.lifecycle.current_frame, "template": "ore_s",
                "marked_finished_before_damage": transient.marked_finished,
                "ore_listener_present": False, "mode_action": "no_op_in_reviewed_laxe_context"})

    def step(self, frames=1):
        require(type(frames) is int and 1 <= frames <= 10000, "Bounded positive frame count required")
        for _ in range(frames):
            if self.lifecycle.terminated:
                break
            self.lifecycle.begin_frame()
            self.loop.tick()
            # Completion of the one-actor fixture's spawn schedule is supplied;
            # this is not the original map's wave/branch completion gate.
            self.lifecycle.check_final(schedule_complete=True, branches_active=False)
        return self.snapshot()

    def reset(self):
        self.__init__(self.dataset)
        return self.snapshot()

    def snapshot(self):
        return {"frame": self.loop.frame, "time_raw": self.loop.time_raw,
            "skill_state": self.skill.state, "sp_raw": self.skill.sp.raw,
            "casting": self.skill.is_casting, "cast_count": self.skill.cast_count,
            "hp_raw": self.actor.hp.raw, "alive": self.actor.alive,
            "finish_reason": self.actor.finish_reason, "recycled": self.actor.recycled,
            "life": self.lifecycle.life, "finish_request": self.lifecycle.finish_request,
            "reward": None, "battle_ready": False, "autonomous_route_ready": False,
            "runtime_battle_validated": False}

    def artifact(self):
        inputs = {k: v for k, v in self.inputs.items() if k not in ("max_hp", "damage_value")}
        inputs.update(max_hp_raw=self.inputs["max_hp"].raw, damage_value_raw=self.inputs["damage_value"].raw)
        return {"scope": "controlled_altar_skill_target_damage_lifecycle_composition",
            "inputs": inputs, "external_inputs": {"initial_life": 3, "birth_delay": 0,
                "recycle_delay": .6, "target_motion": "stationary external fixture; AI/movement/attacks excluded",
                "physics": "three explicit overlap snapshots; no collision engine",
                "ALL_filter": "external single-UID permutation",
                "HitRange": "explicit true fixture", "layer_mask": "external fixture123",
                "prepared_time": self.skill.context.prepared_time_source,
                "scheduler_complete": "one-actor fixture true; original wave scheduler not connected",
                "scheduler_event_bindings_verified": False, "intervening_controller_modules": []},
            "snapshot": self.snapshot(), "skill_events": self.skill.events,
            "target_selections": self.selections, "damage_results": self.damage_results,
            "buff_events": self.buff_events, "lifecycle_events": self.lifecycle.events,
            "battle_ready": False, "autonomous_route_ready": False, "runtime_battle_validated": False}

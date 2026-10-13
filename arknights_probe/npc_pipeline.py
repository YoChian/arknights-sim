"""Prepared NPC factory, real Buff traversal and native finish/recycle chain.

The host starts in an explicit MOVE fixture. Unity, routes, Buff Reset/override,
attributes, visuals, mode side effects and pooling remain named providers. Our
code executes the selected birth, Buff actions/reentry, reaction and Scheduler
accounting; it never starts the client or generates a full-map result.
"""
from __future__ import annotations

from pathlib import Path

from . import Dataset
from .buff_container import BuffContainerHooks, BuffInitShape, NpcBuffContainer
from .enemy_factory import (
    CursorPreparationReceipt, EnemyFactoryCallbacks, EnemyFactoryContext,
    EnemyFactoryRuntime, FactoryPhaseReceipt, PreparedFactoryRoute, RegistrationReceipt,
    UnityAllocationReceipt, prepare_enemy,
)
from .fp import FP
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from .lifecycle import LifecycleRuntime
from .npc_actions import (
    DataPair, EntityPtr, NpcActionRuntime, NpcBlackboard, NpcBuff, NpcCallbacks, NpcContext, NpcEntity,
    bind_talent_blackboard,
)
from .npc_component import NpcComponentProbe
from .npc_damage import (
    DamageReactionCallbacks, DamageReactionInputs, NpcDamagePacket, NpcDamageReactionRuntime,
)
from .npc_lifecycle import (
    DeadAnimationReceipt, EnemyFinishOptions, NpcLifecycleActor, NpcLifecycleHooks,
    NpcLifecycleRuntime, PoolRecycleReceipt, SchedulerCounters, SchedulerLedger,
)
from .npc_restore import (
    NpcRestoreActor, NpcRestoreContext, NpcRestoreRuntime, RestoreCallbacks, RestoreCursor, RestoreRoute,
)
from .npc_summon import (
    NativeRouteData, SummonCallbacks, SummonHost, SummonedActor, TrackedSummonRuntime, duplicate_route_data,
)

SOURCE = "explicit prepared NPC v9 fixture; no client runtime"
ROOT = Path(__file__).resolve().parents[1]


class _BoundSchedulerLedger(SchedulerLedger):
    """Bind v8 summon wrapper lists to the same native Enemy object reference."""
    def __init__(self, probe):
        self.probe = probe
        super().__init__(use_recycle_to_finish_scheduler=True,
            counters=SchedulerCounters(0, 0, 0, 0, 0, SOURCE),
            remove_runtime_route=lambda count: probe._log("runtime_route_remove_provider", count=count),
            source=SOURCE, fresh_event_pool=True)

    def _remove_wrapper(self, values, identity):
        for index, value in enumerate(values):
            if value.actor is identity:
                del values[index]
                return

    def on_unit_finished(self, actor):
        super().on_unit_finished(actor)
        if actor.identity.is_enemy and actor.identity.unity_exists:
            self._remove_wrapper(self.probe.summoning.wave, actor.identity)
            if not self.use_recycle_to_finish_scheduler:
                self._remove_wrapper(self.probe.summoning.final, actor.identity)

    def on_enemy_recycled(self, actor):
        super().on_enemy_recycled(actor)
        if 8 in self.bound_events and actor.identity.is_enemy and actor.identity.unity_exists:
            self._remove_wrapper(self.probe.summoning.final, actor.identity)


class NpcPipelineProbe(NpcComponentProbe):
    def __init__(self, dataset=None):
        self.dataset = dataset or Dataset.from_manifest(ROOT / "data/manifest.json")
        super().__init__()

    def reset(self):
        self.frame, self.time_raw = 0, 0
        self.dt = FP.from_raw(143165440)
        self.events, self.tweens, self.signal_results = [], {}, []
        self.restore_count = self.clear_count = 0
        self.finish_reason = None
        self.npc = self.npc_restore = self.finish_buff = self.dead_buff = None
        self.npc_lifecycle_actor = None
        self.passive_active = True
        self.containers = {}
        self.next_buff_uid = 110
        self.simulator = SharedCoroutineSimulator(source=SOURCE, deterministic=True)
        self.controller_owner = CoroutineOwner(True, True)
        self.life = LifecycleRuntime(initial_life=3, initial_temp_life=0, dt=self.dt,
            use_recycle_to_finish_scheduler=False, context_source=SOURCE,
            mode_backend="DefaultGameMode", global_modifiers=(), hotfix_policy="excluded")
        self.route_data = NativeRouteData(0, (0, 1), (6, 7), (0.0, 0.0), (0.0, 0.0), [],
                                        True, False, False, False, SOURCE)
        route = RestoreRoute("host_initial_route", 0, False, False, SOURCE, True)
        self.host = NpcEntity("host_shdopl", 23, True, True, True, False, (0, 1))
        self.host_restore = NpcRestoreActor(self.host.token, 23, True, True, False, (0, 1), False,
            True, 1, RestoreCursor(route, 0), body_color=(1.0, 1.0, 1.0, 1.0),
            render_color=(1.0, 1.0, 1.0, 1.0))
        self.host_capture = SummonHost(23, True, self.route_data, 0, 0, SOURCE)
        self.actions = NpcActionRuntime(NpcContext(), NpcCallbacks(
            restore_to=self._restore_to, set_disappeared=self._set_disappeared,
            finish_buffs=self._finish_buffs, finish_no_reason=self._finish_no_reason,
            modify_life=self._modify_life, clear_buffs=self._clear_buffs,
            schedule_summon=self._schedule_summon), no_hotfix=True,
            mode="default_noncoop", dispatch_source=SOURCE)
        self.restoration = NpcRestoreRuntime(
            NpcRestoreContext(SOURCE, True, True, self.dt.as_float(), True, True),
            self.simulator, lambda: (self.frame, self.time_raw), RestoreCallbacks(
                set_active=lambda actor, value: self._log("unity_set_active_provider", value=value),
                set_grid_position=lambda actor, grid: self._log("unity_grid_position_provider", grid=list(grid)),
                apply_state_modifier=lambda actor, value: self._log("modifier_provider", added=value),
                tween_start=self._tween_start, tween_kill=self._tween_kill,
                face_from_cursor=lambda actor: self._log("face_provider"),
                move_tick=lambda actor, dt: self._log("stationary_host_move_provider"),
                before_disappear=lambda actor, value: self._log("before_disappear_provider", value=value),
                disappear_changed=lambda actor, value: self._log("disappear_changed_provider", value=value),
                set_color=lambda actor, value: self._log("unity_color_provider", color=list(value)),
                state_transition=self._admit_transition))
        self.summoning = TrackedSummonRuntime(simulator=self.simulator, owner=self.controller_owner,
            callbacks=SummonCallbacks(duplicate_route_data, self._generate_route, self._create_npc,
                self._assign_progress, self._set_npc_position,
                lambda actor: self._log("npc_face_provider"), self._attach_buffs,
                lambda: self._log("mode_before_provider"),
                lambda host, npc: self._log("mode_spawned_provider"),
                lambda: self._log("mode_after_provider"), SOURCE),
            allow_summon=True, spawned_count=10, delta_play_time_float=self.dt.as_float(),
            frame=lambda: self.frame, native_default_no_hotfix=True, source=SOURCE)
        self.ledger = _BoundSchedulerLedger(self)
        self.native_lifecycle = NpcLifecycleRuntime(simulator=self.simulator, ledger=self.ledger,
            hooks=NpcLifecycleHooks(
                lambda actor, reason, source: self.containers[actor.identity.token].on_owner_finish(reason, source),
                lambda actor, finished: self.containers[actor.identity.token].clear(is_owner_finished=finished),
                self._native_phase, self._raw_pool, lambda actor: DeadAnimationReceipt(False, None, SOURCE), SOURCE),
            delta_play_time_float=self.dt.as_float(), frame=lambda: self.frame,
            no_hotfix=True, controller_exists=True, source=SOURCE)
        self.factory = EnemyFactoryRuntime(EnemyFactoryContext(SOURCE, True, True, True, True, False, False),
            EnemyFactoryCallbacks(self._factory_phase, self._factory_cursor,
                lambda actor: self._log("entity_born_event_provider", uid=actor.uid),
                lambda actor: self.containers[actor.token].on_owner_born(),
                lambda actor: RegistrationReceipt(actor.token, actor.uid, True, SOURCE),
                lambda actor: self._log("enemy_born_visual_mode_provider", uid=actor.uid),
                lambda actor, old, new: self._admit_transition(actor, old, new),
                lambda actor, dt: self._log("stationary_npc_move_provider", uid=actor.uid)),
            lambda: (self.frame, FP.from_raw(self.time_raw)))
        self.reaction = NpcDamageReactionRuntime(DamageReactionCallbacks(
            lambda packet: self.containers[self.npc.token].on_take_damage(packet),
            lambda actor, packet: self._log("mode_finalize_damage_provider", uid=actor.uid),
            lambda actor, event, packet: self._log("entity_damage_event_provider", uid=actor.uid, event_id=event),
            lambda actor, packet: self._log("unit_damage_animator_provider", uid=actor.uid), SOURCE))
        self.altar = NpcEntity("altar_source", 9, True, True, False, True, (5, 6))
        self.containers[self.host.token] = self._container(self.host)
        self.passive_buff = NpcBuff("passive_buff", 100, "enemy_shdopl_passive", self.host,
            EntityPtr.capture(self.host), bind_talent_blackboard(
                [DataPair("summon.enemy_key", 0.0, "enemy_3001_upeopl")], "summon", culture="invariant"), 0, True)
        self._register_prepared(self.passive_buff, owner_active=True)
        return self.snapshot()

    def _container(self, owner):
        return NpcBuffContainer(owner, self.actions, BuffContainerHooks(
            lambda buff, enabled: self._log("attribute_modifier_provider", buff=buff.token, enabled=enabled),
            lambda buff: self._log("owner_buff_started_provider", buff=buff.token),
            lambda buff, finished: self._log("owner_buff_finished_provider", buff=buff.token, owner_finished=finished),
            lambda buff, next_frame: self._log("buff_pool_provider", buff=buff.token, next_frame=next_frame),
            self._unique_override_provider,
            lambda buff, event, snapshot: self._log("external_death_audio_create_buff_provider", buff=buff.token, event_id=event),
            lambda buff: self._log("owner_buff_late_enabled_provider", buff=buff.token)),
            no_hotfix=True)

    def _unique_override_provider(self, operation, buff, container):
        # These are explicitly supplied distinct post-Reset runtime keys. This
        # proves no competing member in this fixture, not EnsureIndependentKey.
        key = container.state(buff).shape.override_key
        if any(other is not buff and state.shape.override_key == key for other, state in container.states.items()):
            raise ValueError("Fixture cannot supply general duplicate override resolution")
        if operation == "register":
            container.set_enabled(buff, True)
        self._log("unique_override_provider", buff=buff.token, operation=operation)

    def _register_prepared(self, buff, *, owner_active):
        shape = BuffInitShape(buff.template_key, FP.from_int32(-1),
            SOURCE + "; post-Reset lifetime/filter/key receipt", "fixture_unique_" + buff.token)
        return self.containers[buff.owner.token].add_initialized(buff, shape, owner_active=owner_active)

    def _new_prepared_buff(self, owner, key, blackboard):
        uid = self.next_buff_uid
        self.next_buff_uid += 1
        priority = self.actions.templates[key]["raw"]["onEventPriority"]
        buff = NpcBuff(f"{owner.token}/{key}", uid, key, owner, EntityPtr.capture(owner), blackboard, priority, True)
        self._register_prepared(buff, owner_active=owner.initialized)
        if key == "upeople_t":
            self.dead_buff = buff
        return buff

    def _factory_phase(self, actor, phase, payload):
        self._log("factory_external_phase", phase=phase, initialized=actor.initialized)
        if phase == "unit_on_born_start_common_and_dynamic_abilities":
            for key in actor.prepared.common_ability_templates:
                self._new_prepared_buff(actor, key, NpcBlackboard(culture="invariant"))
        elif phase == "enemy_on_init_controllers_skills_talent_attach":
            for talent in actor.prepared.talents:
                for key in talent.template_keys:
                    self._new_prepared_buff(actor, key, NpcBlackboard(talent.blackboard_rows, culture="invariant"))
        elif phase == "unit_on_born_controller_event_and_owner_post_born":
            self.containers[actor.token].on_owner_post_born()
        return FactoryPhaseReceipt(actor.token, actor.uid, phase, SOURCE)

    def _factory_cursor(self, actor, route):
        cursor = RestoreCursor(route.route, 0)
        self.npc_restore = NpcRestoreActor(actor.token, actor.uid, True, True, False, route.current_grid,
            False, True, 6, cursor, body_color=(1.0, 1.0, 1.0, 1.0), render_color=(1.0, 1.0, 1.0, 1.0))
        return CursorPreparationReceipt(actor.token, actor.uid, cursor, SOURCE)

    def _create_npc(self, key, route, options):
        prepared = prepare_enemy(self.dataset, key)
        self.npc = self.factory.allocate(prepared, UnityAllocationReceipt("npc_upeopl", 24,
            prepared.prefab_key, prepared.prefab_bundle_sha256, prepared.enemy_script_path_id,
            True, True, True, SOURCE))
        self.containers[self.npc.token] = self._container(self.npc)
        self.factory.spawn(self.npc, PreparedFactoryRoute(route, 0, (1.0, 0.0), (0.0, 0.0),
            (0, 1), (6, 7), (0, 1), False, SOURCE), options)
        self.npc_lifecycle_actor = NpcLifecycleActor(self.npc, EnemyFinishOptions.from_summon_options(options),
            CoroutineOwner(True, True), self.npc.state_id, 0, 0.6, False, True, False,
            SOURCE + "; explicit retained recycle-delay Single0.6/controller/counter-state receipt", False, False, 0)
        self.ledger.attach(self.npc_lifecycle_actor, managed_by_scheduler=True, dont_block_wave=True)
        self._log("native_factory_spawn_completed", state=self.npc.state_id)
        return SummonedActor(self.npc.uid, True, self.npc.cursor, self.npc, SOURCE)

    def _attach_buffs(self, host, actor):
        priority = self.actions.templates["enemy_shdopl_finish"]["raw"]["onEventPriority"]
        self.finish_buff = NpcBuff("finish_buff", 101, "enemy_shdopl_finish", self.npc,
            EntityPtr.capture(self.host), NpcBlackboard(culture="invariant"), priority, True)
        self._register_prepared(self.finish_buff, owner_active=self.npc.initialized)

    def _finish_buffs(self, entity, key):
        self.containers[entity.token].finish_buffs_by_id(key)
        if entity is self.host and key == "enemy_shdopl_passive":
            self.passive_active = False
        self._log("native_mark_buff_finished", key=key)

    def _finish_no_reason(self, entity):
        if entity is not self.npc:
            raise ValueError("Selected fixture only finishes its created NPC")
        self.finish_reason = 7
        self.native_lifecycle.finish(self.npc_lifecycle_actor, 7, finish_source=EntityPtr.capture(self.altar))

    def _clear_buffs(self, entity):
        self.clear_count += 1
        self.containers[entity.token].clear()

    def _native_phase(self, stage, actor, payload):
        self._log("native_lifecycle_external_phase", phase=stage, uid=actor.identity.uid)

    def _raw_pool(self, actor):
        self.npc_restore.uid = actor.identity.uid
        self.npc_restore.alive = False
        return PoolRecycleReceipt(True, False, SOURCE)

    def step(self, frames):
        if type(frames) is not int or frames < 0:
            raise ValueError("nonnegative frame count required")
        for _ in range(frames):
            self.frame += 1
            self.time_raw = (FP.from_raw(self.time_raw) + self.dt).raw
            self.restoration.sync_owner(self.host_restore)
            self.restoration.tick(self.host_restore, self.dt)
            self.containers[self.host.token].tick(self.dt)
            if self.npc is not None and self.npc_lifecycle_actor.finish_reason == 0:
                # Entity.OnTick runs its FSM before BuffContainer.Tick. Actors
                # created in coros first enter this phase on the next frame.
                self.factory.tick_birth(self.npc, self.dt)
                self.npc_lifecycle_actor.set_state(self.npc.state_id)
                self.npc_restore.state_id = self.npc.state_id
                self.containers[self.npc.token].tick(self.dt)
            self.simulator.tick()
        return self.snapshot()

    def apply_prepared_damage(self, *, unhurtable=False):
        if self.npc is None or self.finish_reason is not None:
            raise ValueError("Existing unfinished NPC required")
        packet = NpcDamagePacket(EntityPtr.capture(self.altar), EntityPtr.capture(self.npc), FP.from_int32(500))
        result = self.reaction.react(self.npc, packet, DamageReactionInputs(SOURCE, True,
            False, unhurtable, False, False, True, 0, "DefaultGameMode"))
        self.signal_results.append(result)
        return self.snapshot()

    def take_damage_signal(self):
        raise ValueError("Use decoded modifier reaction, not a fabricated Buff event")

    def death_signal(self):
        if self.npc is None or self.finish_reason is not None:
            raise ValueError("Existing unfinished NPC required")
        self.finish_reason = 2
        self.native_lifecycle.finish(self.npc_lifecycle_actor, 2, finish_source=EntityPtr.capture(self.altar))
        return self.snapshot()

    def snapshot(self):
        result = super().snapshot()
        result.update(npc_uid=self.npc.uid if self.npc else None,
            npc_state=self.npc.state_id if self.npc else None,
            npc_hp_raw=self.npc.hp.raw if self.npc else None,
            npc_recycled=self.npc_lifecycle_actor.recycled if self.npc_lifecycle_actor else None,
            scheduler=self.ledger.snapshot())
        return result

    def artifact(self):
        return dict(scope="selected prepared NPC factory Buff reaction finish recycle and Scheduler composition",
            snapshot=self.snapshot(), events=self.events,
            action_trace=[list(x) for x in self.actions.trace],
            factory_events=self.factory.events, summon_events=self.summoning.events,
            restore_events=self.restoration.events, reaction_events=self.reaction.events,
            lifecycle_events=self.native_lifecycle.events,
            buff_traces={k:[list(x) for x in v.trace] for k,v in self.containers.items()},
            reaction_results=self.signal_results, life_events=self.life.events,
            external_inputs=dict(host_initial_state="initialized MOVE1 UID23", created_npc_uid=24,
                decoded_hp_damage_modifier_value=500, full_apply_modifier_and_hp_write=False,
                unity_allocation_awake_reset_controllers_pose_and_pool=SOURCE,
                buff_reset_filters_infinite_lifetime_and_unique_runtime_override_keys=SOURCE,
                buff_attribute_notifications_and_audio_create_buff=SOURCE,
                initial_life_temp_life=[3,0], initial_counters=[0,0,0,0,0],
                retained_recycle_delay_single=0.6, ground_bound_controller_exists=True,
                mode_effects_global_absence_and_registration=SOURCE,
                prepared_zero_checkpoint_route_and_stationary_movement=SOURCE,
                host_full_factory_birth=False, npc_live_pose_and_gate_results=SOURCE,
                fsm_admission_visuals_and_tween=SOURCE, tick_dt_raw=self.dt.raw,
                fresh_event_pool_first_reset=True, live_physics_hits=False),
            client_runtime_compared=False, battle_ready=False, autonomous_route_ready=False,
            runtime_battle_validated=False, reward=None)


def run_npc_pipeline_fixtures():
    damage = NpcPipelineProbe()
    damage.step(10)
    before = damage.snapshot()
    damage.supply_npc_pose()
    damage.apply_prepared_damage()
    after = damage.snapshot()
    damage.step(2)
    death = NpcPipelineProbe(damage.dataset)
    death.step(10)
    death.supply_npc_pose()
    death.death_signal()
    pending = death.snapshot()
    death.step(20)
    return dict(before_reaction=before, after_reaction=after, damage_fixture=damage.artifact(),
                death_before_recycle=pending, death_fixture=death.artifact())

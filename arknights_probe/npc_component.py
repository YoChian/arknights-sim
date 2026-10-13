"""Controlled composition of NPC actions, tracked summon and disappear/restore.

This fixture supplies initialized actors/buffs, a zero-checkpoint runtime route,
Unity/Tween/event providers and explicit NPC pose and damage/finish signals.
It exercises the recovered sequence without bypassing the older ordinary-
enemy lifecycle's NPC rejection. It never advances the original map or claims
that the supplied ON_TAKE_DAMAGE signal was produced by game physics/damage.
"""
from __future__ import annotations

from dataclasses import asdict

from .fp import FP
from .frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from .lifecycle import LifecycleRuntime
from .npc_actions import (
    DataPair, EntityPtr, NpcActionRuntime, NpcBlackboard, NpcBuff, NpcCallbacks,
    NpcContext, NpcEntity, bind_talent_blackboard,
)
from .npc_restore import (
    NpcRestoreActor, NpcRestoreContext, NpcRestoreRuntime, RestoreCallbacks,
    RestoreCursor, RestoreRoute, TweenTicket,
)
from .npc_summon import (
    NativeRouteData, SummonCallbacks, SummonHost, SummonedActor,
    TrackedSummonRequest, TrackedSummonRuntime, duplicate_route_data,
)


FIXTURE_SOURCE = "explicit initialized NPC component fixture; no client runtime"


class NpcComponentProbe:
    def __init__(self):
        self.reset()

    def reset(self):
        self.frame, self.time_raw = 0, 0
        self.dt = FP.from_raw(143165440)
        self.events = []
        self.tweens = {}
        self.restore_count = self.clear_count = 0
        self.finish_reason = None
        self.signal_results = []
        self.simulator = SharedCoroutineSimulator(source=FIXTURE_SOURCE, deterministic=True)
        self.controller_owner = CoroutineOwner(True, True)
        self.life = LifecycleRuntime(
            initial_life=3, initial_temp_life=0, dt=self.dt,
            use_recycle_to_finish_scheduler=False, context_source=FIXTURE_SOURCE,
            mode_backend="DefaultGameMode", global_modifiers=(), hotfix_policy="excluded")
        route = RestoreRoute("host_initial_route", 0, False, False, FIXTURE_SOURCE, True)
        self.route_data = NativeRouteData(
            0, (0, 1), (6, 7), (0.0, 0.0), (0.0, 0.0), [],
            True, False, False, False, FIXTURE_SOURCE)
        self.host = NpcEntity("host_shdopl", 23, True, True, True, False, (0, 1))
        self.host_restore = NpcRestoreActor(
            self.host.token, self.host.uid, True, True, False, (0, 1), False,
            True, 1, RestoreCursor(route, 0), body_color=(1.0, 1.0, 1.0, 1.0),
            render_color=(1.0, 1.0, 1.0, 1.0))
        self.host_capture = SummonHost(23, True, self.route_data, 0, 0, FIXTURE_SOURCE)
        self.npc = self.npc_restore = self.finish_buff = self.dead_buff = None
        self.passive_active = True
        self.actions = NpcActionRuntime(
            NpcContext(), NpcCallbacks(
                restore_to=self._restore_to, set_disappeared=self._set_disappeared,
                finish_buffs=self._finish_buffs, finish_no_reason=self._finish_no_reason,
                modify_life=self._modify_life, clear_buffs=self._clear_buffs,
                schedule_summon=self._schedule_summon),
            no_hotfix=True, mode="default_noncoop", dispatch_source=FIXTURE_SOURCE)
        self.restoration = NpcRestoreRuntime(
            NpcRestoreContext(FIXTURE_SOURCE, True, True, self.dt.as_float(), True, True),
            self.simulator, lambda: (self.frame, self.time_raw),
            RestoreCallbacks(
                set_active=lambda actor, value: self._log("unity_set_active_provider", value=value),
                set_grid_position=lambda actor, grid: self._log("unity_grid_position_provider", grid=list(grid)),
                apply_state_modifier=lambda actor, value: self._log("modifier_provider", added=value),
                tween_start=self._tween_start, tween_kill=self._tween_kill,
                face_from_cursor=lambda actor: self._log("face_provider"),
                move_tick=lambda actor, dt: self._log("stationary_move_provider"),
                before_disappear=lambda actor, value: self._log("before_disappear_provider", value=value),
                disappear_changed=lambda actor, value: self._log("disappear_changed_provider", value=value),
                set_color=lambda actor, value: self._log("unity_color_provider", color=list(value)),
                state_transition=self._admit_transition))
        self.summoning = TrackedSummonRuntime(
            simulator=self.simulator, owner=self.controller_owner,
            callbacks=SummonCallbacks(
                duplicate_route_data=duplicate_route_data,
                generate_runtime_route=self._generate_route,
                create_initialized_enemy=self._create_npc,
                assign_host_route_progress=self._assign_progress,
                set_position=self._set_npc_position,
                init_face_to=lambda actor: self._log("npc_face_provider"),
                attach_additional_buffs=self._attach_buffs,
                mode_before=lambda: self._log("mode_before_provider"),
                mode_spawned=lambda host, npc: self._log("mode_spawned_provider"),
                mode_after=lambda: self._log("mode_after_provider"), source=FIXTURE_SOURCE),
            allow_summon=True, spawned_count=10, delta_play_time_float=self.dt.as_float(),
            frame=lambda: self.frame, native_default_no_hotfix=True, source=FIXTURE_SOURCE)
        summon_bb = bind_talent_blackboard(
            [DataPair("summon.enemy_key", 0.0, "enemy_3001_upeopl")], "summon", culture="invariant")
        self.passive_buff = NpcBuff(
            "passive_buff", 100, "enemy_shdopl_passive", self.host,
            EntityPtr.capture(self.host), summon_bb, 0, True)
        self.actions.run_buff_event(self.passive_buff, 0)
        return self.snapshot()

    def _log(self, event, **details):
        self.events.append(dict(frame=self.frame, event=event, **details))

    def _admit_transition(self, actor, old, new):
        self._log("external_transition_and_move_hooks", old=old, new=new, admitted=True)
        return True

    def _schedule_summon(self, request):
        if request.host is not self.host or request.enemy_key != "enemy_3001_upeopl":
            raise ValueError("fixture only accepts source-bound selected NPC")
        row, col = request.host_grid_position
        self.summoning.start(TrackedSummonRequest(
            request.enemy_key, self.host_capture, (float(col), float(row)), FP(0),
            True, True, True, False, True, True, False, FIXTURE_SOURCE))

    def _generate_route(self, count, data):
        # This is a supplied initialized Route, not Map.GenerateRuntimeRoute.
        self._log("prepared_route_provider", spawned_count=count)
        return RestoreRoute(f"npc_runtime_route_{count}", len(data.checkpoints or ()),
                            data.visit_every_tile_center, data.visit_every_node_center,
                            FIXTURE_SOURCE, True)

    def _create_npc(self, key, route, options):
        self.npc = NpcEntity("npc_upeopl", 24, True, True, True, False, (0, 1))
        self.npc_restore = NpcRestoreActor(
            self.npc.token, self.npc.uid, True, True, False, (0, 1), False, True,
            1, RestoreCursor(route, 0), body_color=(1.0, 1.0, 1.0, 1.0),
            render_color=(1.0, 1.0, 1.0, 1.0))
        self.dead_buff = NpcBuff(
            "dead_buff", 102, "upeople_t", self.npc, EntityPtr.capture(self.npc),
            bind_talent_blackboard([DataPair("dead.value", -1.0)], "Dead", culture="invariant"), 0, True)
        self._log("initialized_factory_provider", enemy_key=key, options=asdict(options))
        return SummonedActor(24, True, self.npc_restore.cursor, self.npc, FIXTURE_SOURCE)

    def _assign_progress(self, actor, progress):
        actor.cursor.cursor_index = progress
        self._log("prepared_progress_provider", progress=progress)

    def _set_npc_position(self, actor, position):
        # External current GridPosition is separately supplied; no coordinate
        # conversion or original Transform hierarchy is inferred here.
        self._log("unity_position_provider", position=list(position))

    def _attach_buffs(self, host, actor):
        self.finish_buff = NpcBuff(
            "finish_buff", 101, "enemy_shdopl_finish", self.npc,
            EntityPtr.capture(self.host), NpcBlackboard(culture="invariant"), 0, True)
        self._log("additional_initialized_buff_provider", template="enemy_shdopl_finish")

    def _restore_actor(self, entity):
        return self.host_restore if entity is self.host else self.npc_restore

    def _restore_to(self, request):
        self.restore_count += 1
        result = self.restoration.restore_to(
            self._restore_actor(request.target), self._restore_actor(request.source),
            release_blocker=request.release_blocker,
            disable_still_pull=request.disable_current_still_pull,
            assign_route=request.reassign_route)
        request.target.grid_position = self._restore_actor(request.target).grid_position
        self._log("restore_callback", result=result)
        return result

    def _set_disappeared(self, entity, value):
        self.restoration.set_disappeared(self._restore_actor(entity), value)

    def _finish_buffs(self, entity, key):
        if entity is self.host and key == "enemy_shdopl_passive":
            self.passive_active = False
            self._log("finish_passive_provider")

    def _finish_no_reason(self, entity):
        self.finish_reason = 7
        entity.alive = False
        self._log("synchronous_finish7_provider")
        # Explicit initialized Buff membership/order. Whole BuffContainer
        # double buffering, Entity.FinishMe and mode/pool are not implemented.
        self.actions.owner_finish(self.dead_buff, 7)
        self.actions.owner_finish(self.finish_buff, 7)

    def _modify_life(self, request):
        self.life.current_frame = self.frame
        self.life.time = FP.from_raw(self.time_raw)
        result = self.life.modify_life(request.delta, source="Dead/value explicit NPC event provider",
                                       is_reach_exit=request.is_reach_exit, to_temp_life=False)
        self._log("modify_life_provider", delta=request.delta, life=self.life.life)
        return result["applied"]

    def _clear_buffs(self, entity):
        self.clear_count += 1
        self._log("clear_buffs_provider")

    def _tween_start(self, actor, request):
        token = f"{actor.token}/{request.kind}/{len(self.tweens)}"
        self.tweens[token] = request
        self._log("tween_ticket_provider", token=token, segments=[list(x) for x in request.segments])
        return TweenTicket(token, FIXTURE_SOURCE)

    def _tween_kill(self, actor, ticket, complete):
        request = self.tweens[ticket.token]
        if complete:
            # Provider only executes explicit completion endpoints. It does
            # not synthesize DOTween easing, time progression or interpolation.
            for kind, endpoint, duration in request.segments:
                request.setter(kind, endpoint)
        self._log("tween_completion_provider", token=ticket.token)

    def step(self, frames):
        if type(frames) is not int or frames < 0:
            raise ValueError("nonnegative frame count required")
        for _ in range(frames):
            self.frame += 1
            self.time_raw = (FP.from_raw(self.time_raw) + self.dt).raw
            self.restoration.sync_owner(self.host_restore)
            self.restoration.tick(self.host_restore, self.dt)
            self.simulator.tick()
        return self.snapshot()

    def supply_npc_pose(self, grid_position=(3, 5), cursor_index=4):
        if self.npc is None or self.finish_reason is not None:
            raise ValueError("an existing unfinished NPC is required")
        self.npc.grid_position = grid_position
        self.npc_restore.grid_position = grid_position
        self.npc_restore.cursor.cursor_index = cursor_index
        self._log("external_npc_pose", grid=list(grid_position), cursor_index=cursor_index)

    def take_damage_signal(self):
        if self.npc is None or self.finish_reason is not None:
            raise ValueError("an existing unfinished NPC is required")
        self._log("external_on_take_damage10", hp_damage_calculated=False)
        result = self.actions.run_buff_event(self.finish_buff, 10)
        self.signal_results.append(dict(event=10, result=result.result,
                                       executed=list(result.executed), stopped_before=result.stopped_before))
        return self.snapshot()

    def death_signal(self):
        if self.npc is None or self.finish_reason is not None:
            raise ValueError("an existing unfinished NPC is required")
        self.finish_reason = 2
        self.npc.alive = False
        self._log("external_finish_reason2", hp_damage_calculated=False)
        self.actions.owner_finish(self.dead_buff, 2)
        self.actions.owner_finish(self.finish_buff, 2)
        return self.snapshot()

    def snapshot(self):
        return dict(frame=self.frame, time_raw=self.time_raw,
                    npc_created=self.npc is not None, npc_alive=self.npc.alive if self.npc else None,
                    host_disappeared=self.host_restore.is_disappeared,
                    host_game_active=self.host_restore.game_active,
                    host_state=self.host_restore.state_id,
                    host_grid=list(self.host_restore.grid_position),
                    host_route=self.host_restore.cursor.route.token,
                    host_cursor_index=self.host_restore.cursor.cursor_index,
                    passive_active=self.passive_active, restore_callbacks=self.restore_count,
                    finish_reason=self.finish_reason, clear_callbacks=self.clear_count,
                    lock=self.finish_buff.blackboard.number("lock") if self.finish_buff else None,
                    life=self.life.life, temp_life=self.life.temp_life,
                    wave_members=len(self.summoning.wave), final_members=len(self.summoning.final),
                    reward=None, battle_ready=False, autonomous_route_ready=False,
                    runtime_battle_validated=False)

    def artifact(self):
        return dict(scope="controlled_npc_actions_summon_disappear_restore_with_external_signals",
                    snapshot=self.snapshot(), events=self.events,
                    action_trace=[list(x) for x in self.actions.trace],
                    summon_events=self.summoning.events, restore_events=self.restoration.events,
                    signal_results=self.signal_results, life_events=self.life.events,
                    external_inputs=dict(
                        initialized_entities_and_buffs=True, buff_dispatch_and_membership=FIXTURE_SOURCE,
                        initial_host_uid=23, initialized_npc_uid=24, initial_spawned_counter=10,
                        tick_dt_raw=self.dt.raw, delta_play_time_single=self.dt.as_float(),
                        shared_controller_owner_exists_and_active=True,
                        clock_anchor="initialized MOVE host before passive fixture activation",
                        npc_pose_and_take_damage_or_finish_signals=True,
                        native_default_no_hotfix=True, default_noncoop_empty_global_modifiers=True,
                        initial_life_and_temp_life=[3, 0], blackboard_culture="invariant_ascii",
                        prepared_zero_checkpoint_runtime_routes=True, stationary_move_provider=True,
                        fsm_admission_and_move_enter_exit_hooks=FIXTURE_SOURCE,
                        unity_active_hierarchy_matches_self=True,
                        unity_activation_position_color_and_tween_provider=True,
                        tween_time_and_easing_simulated=False,
                        factory_and_birth_registration_implemented=False,
                        physics_hits_supplied=False, npc_hp_damage_calculated=False,
                        entity_finish_mode_pool_and_full_buff_container_implemented=False,
                        final_membership_pending_native_mode_recycle=True),
                    client_runtime_compared=False, battle_ready=False,
                    autonomous_route_ready=False, runtime_battle_validated=False, reward=None)


def run_npc_component_fixtures():
    damage = NpcComponentProbe()
    damage.step(10)
    hidden = damage.snapshot()
    damage.supply_npc_pose()
    damage.take_damage_signal()
    after_signal = damage.snapshot()
    damage.step(2)
    death = NpcComponentProbe()
    death.step(10)
    death.supply_npc_pose()
    death.death_signal()
    death.step(2)
    return dict(hidden_before_signal=hidden, after_damage_signal=after_signal,
                damage_signal_fixture=damage.artifact(), death_signal_fixture=death.artifact())

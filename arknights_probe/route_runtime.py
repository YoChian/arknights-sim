"""Automatic single-actor route/lifecycle experiment over explicit inputs.

This closes component ownership: movement requests an exit, lifecycle applies
its callback chain, and its coroutine removes final membership. It deliberately
has no whole-map constructor: scene.py still rejects unimplemented scene rules.
"""
from __future__ import annotations

import copy
import math

from .data import number, require
from .fp import binary32
from .lifecycle import BORN_STATE, LifecycleRuntime
from .runtime_movement import NativeRouteMover


class RouteLifecycleProbe:
    def __init__(self, mover: NativeRouteMover, lifecycle: LifecycleRuntime,
                 identifier: str, *, speed: float, speed_source: str,
                 scenario_source: str, can_move: bool, actually_ground_bound: bool,
                 check_cursor_reached: bool, exit_allowed: bool):
        require(isinstance(mover, NativeRouteMover), 'Native route mover required')
        require(isinstance(lifecycle, LifecycleRuntime), 'Lifecycle runtime required')
        require(list(lifecycle.enemies) == [identifier], 'Probe needs exactly one created actor')
        require(lifecycle.enemies[identifier].state_id == BORN_STATE and lifecycle.current_frame == 0,
                'Probe needs a freshly created Born-state actor')
        require(lifecycle.on_event is None, 'Probe owns its lifecycle events')
        require(mover.current_frame == 0, 'Probe needs a fresh mover')
        require(all(type(v) is bool for v in (can_move, actually_ground_bound,
                    check_cursor_reached, exit_allowed)), 'Explicit movement gates required')
        require(all(isinstance(s, str) and s.strip() for s in (speed_source, scenario_source)),
                'Probe inputs need provenance')
        self.speed = binary32(number(speed, 'Runtime speed', minimum=0))
        require(math.isfinite(self.speed), 'Runtime speed overflows Single')
        self.identifier = identifier
        self.speed_source, self.scenario_source = speed_source, scenario_source
        self.gates = {'can_move': can_move, 'actually_ground_bound': actually_ground_bound,
                      'check_cursor_reached': check_cursor_reached, 'exit_allowed': exit_allowed}
        self._initial = copy.deepcopy((mover, lifecycle))
        self.reset()

    def reset(self):
        self.mover, self.lifecycle = copy.deepcopy(self._initial)
        return self.observe(), self.info()

    def info(self):
        return {'scope': 'automatic_single_actor_route_lifecycle_component',
            'scenario_source': self.scenario_source, 'speed_source': self.speed_source,
            'movement_context_source': self.mover.context.source,
            'tile_context_source': self.mover.grid.source,
            'state_gates': copy.deepcopy(self.gates), 'lifecycle': self.lifecycle.info(),
            'native_relative_order': ['Unit/FSM', 'Enemy/cursor', 'exit/finish callbacks',
                                      'battle coroutine recycling', 'logical final check'],
            'reward_defined': False, 'seed_consumed': False,
            'external_lifecycle_events_required': False,
            'full_scene_ability_executor': False, 'full_scene_scheduler_connected': False,
            'autonomous_route_ready': False, 'battle_ready': False,
            'client_runtime_compared': False}

    def observe(self):
        actor = self.lifecycle.enemies[self.identifier]
        return {'frame': self.lifecycle.current_frame, 'time_raw': self.lifecycle.time.raw,
            'actor_id': self.identifier, 'state_id': actor.state_id, 'hp_raw': actor.hp.raw,
            'birth_remaining_raw': actor.born_remaining.raw, 'alive': actor.alive,
            'finish_reason': actor.finish_reason, 'recycled': actor.recycled,
            'movement': self.mover.snapshot(), 'life': self.lifecycle.life,
            'temp_life': self.lifecycle.temp_life,
            'wave_membership': sorted(self.lifecycle.wave_ids),
            'final_membership': sorted(self.lifecycle.final_ids),
            'finish_request': self.lifecycle.finish_request,
            'terminated': self.lifecycle.terminated}

    def step(self, action: dict):
        require(isinstance(action, dict) and action.get('type') == 'tick',
                'Route probe accepts automatic ticks only')
        require(set(action) <= {'type', 'frames'}, 'Unknown route probe action fields')
        frames = action.get('frames', 1)
        require(type(frames) is int and 1 <= frames <= 100000, 'frames must be 1..100000')
        start = len(self.lifecycle.events)
        for _ in range(frames):
            if self.lifecycle.terminated:
                break
            self.lifecycle.begin_frame()
            actor = self.lifecycle.enemies[self.identifier]
            if not actor.recycled and not actor.finish_reason:
                dispatched_move = self.lifecycle.tick_state(self.identifier)
                movement = self.mover.tick(self.lifecycle.dt, speed=self.speed,
                    move_state_tick=dispatched_move,
                    alive_after_unit_tick=actor.alive, **self.gates)
                if movement['exit_requested']:
                    self.lifecycle.reach_exit(self.identifier)
            self.lifecycle.tick_recycling()
            self.lifecycle.check_final(schedule_complete=True, branches_active=False)
        observation = self.observe()
        return observation, None, observation['terminated'], False, {
            **self.info(), 'events': copy.deepcopy(self.lifecycle.events[start:])}

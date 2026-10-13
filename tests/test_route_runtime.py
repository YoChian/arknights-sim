import unittest

from arknights_probe.fp import FP
from arknights_probe.movement import (LocalVector2 as V, NativeTileSnapshot as T,
    NativeWalkPathGrid, WalkRouteSpec, CheckpointSpec, compile_walk_route)
from arknights_probe.runtime_movement import MovementContext, NativeRouteMover
from arknights_probe.lifecycle import LifecycleRuntime, MOVE_STATE
from arknights_probe.route_runtime import RouteLifecycleProbe


def probe(*, life=3, temp_life=0, birth_delay=.2, recycle_delay=.3, can_move=True):
    grid = NativeWalkPathGrid([[T(1, 15, False, False) for _ in range(6)] for _ in range(3)],
        source='explicit open cached tile fixture; no altar or boxes')
    spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0),
        (CheckpointSpec('MOVE', 0, (1, 4), V(0, 0), .05),))
    context = MovementContext(source='explicit isolated movement branches', deterministic=True,
        new_steering=True, foot_offset=V(0, 0), initial_steering=8, max_force=10,
        half_body_width=.2, conveyor_present=False, always_check_current_point=False)
    mover = NativeRouteMover(compile_walk_route(spec, grid), grid, context,
                            position=V(1, 1), cursor_offset=V(0, 0))
    runtime = LifecycleRuntime(initial_life=life, initial_temp_life=temp_life,
        dt=FP.from_float32(.1), use_recycle_to_finish_scheduler=True,
        context_source='explicit single-actor empty modifier logical fixture')
    runtime.spawn('actor', 'isolated_fixture', max_hp=FP.from_int32(100), birth_delay=birth_delay,
        recycle_delay=recycle_delay, life_point_reduce=1, managed=True, wave_block=True,
        not_count_in_total=False, lifecycle_templates=())
    return RouteLifecycleProbe(mover, runtime, 'actor', speed=1, speed_source='explicit fixture',
        scenario_source='controlled single actor; excludes whole scene actions', can_move=can_move,
        actually_ground_bound=False, check_cursor_reached=True, exit_allowed=True)


class RouteLifecycleTests(unittest.TestCase):
    def test_birth_transition_does_not_dispatch_move_twice(self):
        env = probe()
        env.step({'type': 'tick'})
        state, _, done, _, _ = env.step({'type': 'tick'})
        self.assertEqual(MOVE_STATE, state['state_id'])
        self.assertEqual([1.0, 1.0], state['movement']['position'])
        self.assertFalse(done)
        state, *_ = env.step({'type': 'tick'})
        self.assertGreater(state['movement']['position'][0], 1)

    def test_exit_wave_release_and_delayed_final_recycle_are_automatic(self):
        env = probe()
        released = None
        while not env.observe()['terminated']:
            state, *_ = env.step({'type': 'tick'})
            if state['finish_reason'] and not state['recycled']:
                released = state
        self.assertIsNotNone(released)
        self.assertEqual([], released['wave_membership'])
        self.assertEqual(['actor'], released['final_membership'])
        self.assertEqual(2, released['life'])
        self.assertEqual('win', state['finish_request'])
        self.assertEqual([], state['final_membership'])
        self.assertTrue(state['recycled'])
        kinds = [e['kind'] for e in env.lifecycle.events]
        self.assertFalse(any(kind.startswith('external_') for kind in kinds))
        self.assertFalse(env.info()['battle_ready'])

    def test_temporary_life_absorbs_exit_cost(self):
        env = probe(life=1, temp_life=1)
        state, reward, done, _, _ = env.step({'type': 'tick', 'frames': 200})
        self.assertEqual((1, 0), (state['life'], state['temp_life']))
        self.assertEqual('win', state['finish_request'])
        self.assertTrue(done)
        self.assertIsNone(reward)

    def test_zero_delay_recycle_follows_exit_callback_and_life_settlement(self):
        env = probe(recycle_delay=0)
        state, _, done, _, _ = env.step({'type': 'tick', 'frames': 200})
        self.assertTrue(done)
        kinds = [e['kind'] for e in env.lifecycle.events]
        self.assertLess(kinds.index('enemy_wave_released'), kinds.index('life_modified'))
        self.assertLess(kinds.index('life_modified'), kinds.index('enemy_reached_exit'))
        self.assertLess(kinds.index('enemy_reached_exit'), kinds.index('enemy_recycled'))
        self.assertLess(kinds.index('enemy_recycled'), kinds.index('battle_finish_requested'))
        self.assertTrue(state['recycled'])

    def test_life_zero_finishes_before_pending_recycle(self):
        env = probe(life=1, recycle_delay=1)
        state, _, done, _, _ = env.step({'type': 'tick', 'frames': 200})
        self.assertTrue(done)
        self.assertEqual('lose', state['finish_request'])
        self.assertEqual(0, state['life'])
        self.assertFalse(state['recycled'])
        self.assertEqual(['actor'], state['final_membership'])

    def test_reset_replays_same_component_trace_and_gates_can_stop_motion(self):
        env = probe()
        first = env.step({'type': 'tick', 'frames': 200})[0]
        events = list(env.lifecycle.events)
        env.reset()
        self.assertEqual(first, env.step({'type': 'tick', 'frames': 200})[0])
        self.assertEqual(events, env.lifecycle.events)
        blocked = probe(can_move=False)
        state, _, done, _, _ = blocked.step({'type': 'tick', 'frames': 50})
        self.assertEqual([1.0, 1.0], state['movement']['position'])
        self.assertFalse(done)
        self.assertEqual(['actor'], state['wave_membership'])


if __name__ == '__main__':
    unittest.main()

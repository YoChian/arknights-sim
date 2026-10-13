"""Run an isolated route/lifecycle experiment and save its automatic trace."""
import argparse
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from arknights_probe.fp import FP
from arknights_probe.timeline import ASSET_DEFAULT_DT_RAW
from arknights_probe.movement import (LocalVector2 as V, NativeTileSnapshot as T,
    NativeWalkPathGrid, WalkRouteSpec, CheckpointSpec, compile_walk_route)
from arknights_probe.runtime_movement import MovementContext, NativeRouteMover
from arknights_probe.lifecycle import LifecycleRuntime
from arknights_probe.route_runtime import RouteLifecycleProbe


def make_probe(initial_life=3, initial_temp_life=0):
    grid = NativeWalkPathGrid([[T(1, 15, False, False) for _ in range(6)] for _ in range(3)],
        source='controlled open cached tile fixture; excludes real scene devices and enemies')
    spec = WalkRouteSpec((1, 1), (1, 4), V(0, 0), (
        CheckpointSpec('MOVE', 0, (1, 1), V(0, 0), .05),
        CheckpointSpec('WAIT_FOR_SECONDS', .3, (0, 0), V(0, 0), 0),
        CheckpointSpec('MOVE', 0, (1, 4), V(0, 0), .05)))
    context = MovementContext(source='explicit deterministic/new-steering/zero-offset fixture branches',
        deterministic=True, new_steering=True, foot_offset=V(0, 0), initial_steering=8,
        max_force=10, half_body_width=.2, conveyor_present=False, always_check_current_point=False)
    mover = NativeRouteMover(compile_walk_route(spec, grid), grid, context,
                            position=V(1, 1), cursor_offset=V(0, 0))
    lifecycle = LifecycleRuntime(initial_life=initial_life, initial_temp_life=initial_temp_life,
        dt=FP.from_raw(ASSET_DEFAULT_DT_RAW), use_recycle_to_finish_scheduler=True,
        context_source='explicit single-actor DefaultGameMode logical fixture, empty modifiers/no hotfix')
    lifecycle.spawn('isolated_actor', 'isolated_fixture', max_hp=FP.from_int32(100),
        birth_delay=.2, recycle_delay=.6, life_point_reduce=1, managed=True, wave_block=True,
        not_count_in_total=False, lifecycle_templates=())
    return RouteLifecycleProbe(mover, lifecycle, 'isolated_actor', speed=1,
        speed_source='explicit component fixture speed',
        scenario_source='controlled one-actor component experiment, not level_rogue6_1-1 execution',
        can_move=True, actually_ground_bound=False, check_cursor_reached=True, exit_allowed=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--frames', type=int, default=300)
    parser.add_argument('--initial-life', type=int, default=3)
    parser.add_argument('--temp-life', type=int, default=0)
    parser.add_argument('--output', type=Path, default=ROOT / 'artifacts/route_lifecycle_component.json')
    args = parser.parse_args()
    if not 1 <= args.frames <= 100000:
        parser.error('--frames must be 1..100000')
    env = make_probe(args.initial_life, args.temp_life)
    initial, info = env.reset()
    samples = []
    for _ in range(args.frames):
        state, _, done, _, _ = env.step({'type': 'tick'})
        samples.append({'frame': state['frame'], 'time_raw': state['time_raw'],
            'position': state['movement']['position'], 'state_id': state['state_id'],
            'birth_remaining_raw': state['birth_remaining_raw'],
            'cursor': state['movement']['cursor'], 'life': state['life'],
            'temp_life': state['temp_life'], 'recycled': state['recycled']})
        if done:
            break
    result = {'initial': initial, 'info': info, 'frame_samples': samples,
              'events': env.lifecycle.events, 'final': env.observe(), 'reward': None}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2), encoding='utf8')
    print(json.dumps({'path': str(args.output.resolve()), 'frames': env.lifecycle.current_frame,
        'finish_request': env.lifecycle.finish_request, 'life': env.lifecycle.life,
        'temp_life': env.lifecycle.temp_life, 'battle_ready': False}))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())

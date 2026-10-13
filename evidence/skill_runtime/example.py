"""Explicit minimal-component fixture; not the stage's real idle result."""
from arknights_probe.fp import FP, ZERO
from arknights_probe.frame_runtime import SharedCoroutineSimulator, CoroutineOwner
from arknights_probe.skill_runtime import AltarSkillRuntime, explicit_altar_fixture_context

dt = FP(143165440)
clock = {"frame": 0, "time": ZERO}
simulator = SharedCoroutineSimulator(source="explicit skill component fixture", deterministic=True)
context = explicit_altar_fixture_context(
    source="predefined altar already Init/AssignData/Attach; initialized before playing; no hotfix",
    prepared_time_source="externally supplied prepared fields; assignment/blackboard not claimed complete",
    pre_delay=FP.from_float32(.6), duration=FP.from_int32(1), cooldown=FP.from_int32(1),
    delta_play_time_float=dt.as_float(), half_default_frame=FP(71582720),
    sp_recovery_per_second=FP.from_int32(1))
# This target is an explicit HP fixture. Real enemy HP comes from attributes.
target = {"uid": 2, "hp_fixture": 750}
def spell(targets):
    for candidate in targets:
        candidate["hp_fixture"] = max(0, candidate["hp_fixture"] - 500)
# A real composition injects the targeting and damage kernels here. This local
# callback only demonstrates scheduling, not native HP/death settlement.
kernel = AltarSkillRuntime(context, simulator=simulator,
    unity_owner=CoroutineOwner(True, True),  # actual coroutine owner is Ability
    clock=lambda: (clock["frame"], clock["time"]),
    select_targets=lambda: (target,) if target["hp_fixture"] > 0 else (), spell=spell)
kernel.initialize()
for frame in range(1, 501):
    clock["frame"] = frame
    clock["time"] += dt
    kernel.fixed_tick(dt)  # object phase
    simulator.tick()      # shared phase, including same-frame start
print([e for e in kernel.events if e["kind"] in ("skill_start", "spell", "skill_end")])

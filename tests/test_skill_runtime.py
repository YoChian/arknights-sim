import unittest
from dataclasses import replace

from arknights_probe.fp import FP, ZERO, SCALE
from arknights_probe.frame_runtime import CoroutineOwner, SharedCoroutineSimulator
from arknights_probe.skill_runtime import (
    AbilityCooldown, AltarSkillRuntime, UnverifiedSkillContext,
    explicit_altar_fixture_context, fp_wait_frames)
from arknights_probe.devices import FP_LARGE_EPS_RAW


DT = FP(143165440)


class Fixture:
    def __init__(self, *, pre_delay=None, duration=None, cooldown=None, targets=None):
        self.frame = 0
        self.time = ZERO
        self.targets = [] if targets is None else targets
        self.snapshots = []
        self.sim = SharedCoroutineSimulator(source="self-authored skill test", deterministic=True)
        self.context = explicit_altar_fixture_context(
            source="explicit minimal scene fixture, no live client",
            prepared_time_source="explicit post-AssignData time fields; not runtime observation",
            pre_delay=FP.from_float32(.6) if pre_delay is None else pre_delay,
            duration=FP.from_int32(1) if duration is None else duration,
            cooldown=FP.from_int32(1) if cooldown is None else cooldown,
            delta_play_time_float=DT.as_float(), half_default_frame=FP(71582720),
            sp_recovery_per_second=FP.from_int32(1))
        self.runtime = AltarSkillRuntime(
            self.context, simulator=self.sim,
            unity_owner=CoroutineOwner(True, True), clock=lambda: (self.frame, self.time),
            select_targets=lambda: self.targets, spell=self.snapshots.append)
        self.runtime.initialize()

    def tick(self, count=1):
        for _ in range(count):
            self.frame += 1
            self.time += DT
            self.runtime.fixed_tick(DT)
            self.sim.tick()

    def frames(self, kind):
        return [e["frame"] for e in self.runtime.events if e["kind"] == kind]


class SkillRuntimeTests(unittest.TestCase):
    def test_independent_bounded_reference_report_and_trace(self):
        from pathlib import Path
        import json
        root = Path(__file__).resolve().parents[1] / "evidence/skill_runtime"
        report = json.loads((root / "reference_report.json").read_text())
        self.assertTrue(report["all_equal"])
        self.assertEqual(report["frames_total"], 5550)
        self.assertEqual(report["event_rows"], 263)
        self.assertEqual((root / "reference_output.tsv").read_text(),
                         (root / "python_output.tsv").read_text())
        self.assertFalse(report["client_runtime_compared"])

    def test_fp_wait_uses_fp_division_and_ties_even(self):
        for numerator, expected in [(1, 1), (3, 2), (5, 2), (7, 4), (9, 4)]:
            self.assertEqual(fp_wait_frames(FP(numerator * SCALE // 2), 1.0), expected)
        self.assertEqual(fp_wait_frames(ZERO, 1.0), 1)
        self.assertEqual(fp_wait_frames(FP.from_int32(-3), 1.0), 1)
        self.assertEqual(fp_wait_frames(FP.from_float32(.6), DT.as_float()), 18)

    def test_wait_rejects_bad_divisors(self):
        for divisor in [0, -1, float("inf"), float("nan")]:
            with self.assertRaises(UnverifiedSkillContext):
                fp_wait_frames(ZERO, divisor)

    def test_timer_readiness_strict_abs_epsilon(self):
        timer = AbilityCooldown(FP.from_int32(1), FP(FP_LARGE_EPS_RAW - 1))
        self.assertTrue(timer.ready)
        timer.remaining = FP(FP_LARGE_EPS_RAW)
        self.assertFalse(timer.ready)
        timer.remaining = FP(-FP_LARGE_EPS_RAW)
        self.assertFalse(timer.ready)
        timer.remaining = FP(-FP_LARGE_EPS_RAW + 1)
        self.assertTrue(timer.ready)

    def test_timer_update_uses_raw_le_zero_not_ready_predicate(self):
        timer = AbilityCooldown(FP.from_int32(1), FP(FP_LARGE_EPS_RAW - 1))
        self.assertFalse(timer.tick(ZERO))
        self.assertNotEqual(timer.remaining.raw, 0)
        self.assertTrue(timer.tick(FP(FP_LARGE_EPS_RAW)))
        self.assertEqual(timer.remaining, ZERO)
        timer.reset(True)
        self.assertEqual(timer.remaining, timer.period)
        timer.reset(False)
        self.assertEqual(timer.remaining, ZERO)

    def test_predefined_born_transition_is_queued_and_drained(self):
        f = Fixture()
        self.assertEqual(f.runtime.state, AltarSkillRuntime.IDLE)
        records = f.runtime.events
        self.assertEqual([(x["kind"], x.get("state")) for x in records], [
            ("state_enter", 7), ("state_switch_queued", 1), ("state_changed", 7),
            ("born_exit", None), ("state_enter", 1), ("state_changed", 1)])
        self.assertTrue(all(x["frame"] == 0 for x in records))

    def test_auto_requires_seven_sp_and_no_frame_zero_cast(self):
        f = Fixture()
        f.tick(209)
        self.assertEqual(f.frames("skill_start"), [])
        self.assertEqual(f.runtime.sp, FP.from_int32(6))
        f.tick()
        self.assertEqual(f.frames("skill_start"), [210])
        self.assertEqual(f.runtime.sp, ZERO)

    def test_start_prime_precedes_sp_consumption_and_modifier(self):
        f = Fixture()
        f.runtime.sp = FP.from_int32(7)
        f.tick()
        kinds = [e["kind"] for e in f.runtime.events if e["frame"] == 1]
        self.assertLess(kinds.index("pre_delay_begin"), kinds.index("sp_consumed"))
        self.assertLess(kinds.index("sp_consumed"), kinds.index("sp_recovery_modifier"))
        self.assertLess(kinds.index("cast_succeeded"), kinds.index("skill_state_cooldown_reset"))

    def test_shared_phase_reaches_spell_after_seventeen_later_frames(self):
        f = Fixture()
        f.tick(226)
        self.assertEqual(f.frames("spell"), [])
        f.tick()
        self.assertEqual(f.frames("spell"), [227])
        self.assertEqual(f.runtime.state, AltarSkillRuntime.SKILL)

    def test_zero_predelay_still_yields_but_spells_in_start_frame_shared_phase(self):
        f = Fixture(pre_delay=ZERO, duration=ZERO, cooldown=ZERO)
        f.runtime.sp = FP.from_int32(7)
        f.tick()
        self.assertEqual(f.frames("skill_start"), [1])
        self.assertEqual(f.frames("spell"), [1])
        self.assertEqual(f.frames("skill_end"), [])
        f.tick()
        self.assertEqual(f.frames("skill_end"), [2])

    def test_target_snapshot_membership_order_keeps_live_object_references(self):
        a, b = {"hp": 750}, {"hp": 1250}
        f = Fixture(targets=[a, b])
        f.runtime.sp = FP.from_int32(7)
        f.tick()
        f.targets[:] = [b]
        a["hp"] = 700
        f.tick(17)
        self.assertEqual(len(f.snapshots), 1)
        self.assertEqual(f.snapshots[0], (a, b))
        self.assertIs(f.snapshots[0][0], a)
        self.assertEqual(f.snapshots[0][0]["hp"], 700)

    def test_empty_targets_allowed_and_one_spell(self):
        f = Fixture()
        f.runtime.sp = FP.from_int32(7)
        f.tick(31)
        self.assertEqual(f.snapshots, [()])
        self.assertEqual(len(f.frames("spell")), 1)

    def test_sp_recovery_freezes_through_cast_and_one_next_object_phase(self):
        f = Fixture()
        f.tick(241)
        self.assertEqual(f.frames("skill_end"), [240])
        releases = [e for e in f.runtime.events if e["kind"] == "sp_recovery_modifier" and not e["registered"]]
        self.assertEqual([e["frame"] for e in releases], [241])
        self.assertEqual(f.runtime.sp, ZERO)
        self.assertEqual(f.runtime.sp_controller.timer.remaining, FP(SCALE + 28672))
        f.tick(30)
        self.assertEqual(f.runtime.sp, FP.from_int32(1))
        self.assertEqual(f.frames("sp_recovered")[-1], 271)

    def test_two_repeat_cycles_are_not_fixed210_plus18_shortcuts(self):
        f = Fixture()
        f.tick(500)
        self.assertEqual(f.frames("skill_start"), [210, 452])
        self.assertEqual(f.frames("spell"), [227, 469])
        self.assertEqual(f.frames("skill_end"), [240, 482])

    def test_half_frame_reset_strict_threshold_and_duration_match(self):
        f = Fixture()
        r = f.runtime
        r.is_casting = True
        r.state = r.SKILL
        r._duration_at_begin = f.context.prepared_duration
        threshold = f.context.half_default_frame.raw - FP_LARGE_EPS_RAW
        r.cooldown.remaining = FP(threshold)
        r._finish()
        self.assertNotIn("half_frame_cooldown_reset", [e["kind"] for e in r.events])
        r.is_casting = True
        r.state = r.SKILL
        r.cooldown.remaining = FP(threshold - 1)
        r._finish()
        self.assertEqual(r.cooldown.remaining, ZERO)
        self.assertEqual(f.frames("half_frame_cooldown_reset"), [0])

    def test_finish_clears_casting_before_callback_and_keeps_modifier_until_tick(self):
        f = Fixture()
        observed = []
        f.runtime.on_event = lambda e: observed.append((e["kind"], f.runtime.is_casting, f.runtime.registered_as_modifier))
        f.runtime.sp = FP.from_int32(7)
        f.tick(31)
        self.assertIn(("skill_end", False, True), observed)
        self.assertEqual(f.runtime.state, AltarSkillRuntime.IDLE)
        f.tick()
        self.assertFalse(f.runtime.registered_as_modifier)

    def test_sp_enough_strict_epsilon_boundary(self):
        r = Fixture().runtime
        r.sp = FP(FP.from_int32(7).raw - FP_LARGE_EPS_RAW)
        self.assertFalse(r.sp_enough)
        r.sp = FP(r.sp.raw + 1)
        self.assertTrue(r.sp_enough)

    def test_unclosed_contexts_fail_explicitly(self):
        f = Fixture()
        for name, value in [("native_default_no_hotfix", False), ("initialized_assigned_attached", False),
                            ("predefined", False), ("playing_at_initialize", True), ("dialog_target", True),
                            ("abnormal_state", True), ("other_sp_modifiers", True), ("active_skill_event_effects", True),
                            ("chant_present", True), ("skill_behaviour_count", 1), ("extra_ability_count", 1)]:
            with self.subTest(name=name), self.assertRaises(UnverifiedSkillContext):
                replace(f.context, **{name: value}).validate()

    def test_cannot_tick_before_initialize_or_double_initialize(self):
        f = Fixture()
        with self.assertRaises(ValueError):
            f.runtime.initialize()
        f.runtime.initialized = False
        with self.assertRaises(UnverifiedSkillContext):
            f.runtime.fixed_tick(DT)

    def test_owner_inactive_or_dies_is_not_silently_skipped(self):
        f = Fixture()
        f.runtime.alive = False
        with self.assertRaises(UnverifiedSkillContext):
            f.tick()
        f.runtime.alive = True
        f.runtime.unity_owner.active_in_hierarchy = False
        with self.assertRaises(UnverifiedSkillContext):
            f.tick()

    def test_not_skill_eligible_owner_may_recover_but_not_cast(self):
        f = Fixture()
        f.runtime.context = replace(f.context, owner_can_use_skill=False)
        f.tick(250)
        self.assertEqual(f.runtime.sp, FP.from_int32(7))
        self.assertEqual(f.frames("skill_start"), [])


if __name__ == "__main__":
    unittest.main()

import unittest

from arknights_probe.devices import (
    FP_LARGE_EPS_RAW, FixedDamageAction, ImmediateBuffLifecycle,
    NaturalSpController, PrecisePeriodicTimer, PreDelayAbility,
    UnverifiedDeviceContext, ore_finish_actions,
    verify_device_evidence,
)
from arknights_probe.fp import FP


ONE = FP.from_int32(1)
ZERO = FP.from_raw(0)
DT = FP.from_raw(143165440)


class DeviceTests(unittest.TestCase):
    def test_derived_evidence_and_original_native_body_hashes(self):
        evidence = verify_device_evidence(check_native_bytes=True)
        self.assertTrue(evidence["healthy"], evidence["errors"])
        self.assertEqual(evidence["files_checked"], 31)
        self.assertEqual(evidence["native_ranges_checked"], 262)
        self.assertEqual(evidence["static_functions"], 104)
        self.assertEqual(evidence["csharp_component_checks"], 71)
        self.assertFalse(evidence["client_runtime_compared"])
        self.assertFalse(evidence["complete_idle_scene_supported"])

    def owner(self, initial=ZERO, maximum=7, rate=ONE, sp_type=1):
        state = {"sp": initial, "writes": []}
        def write(value):
            state["writes"].append(value.raw)
            # Explicit test fixture of the closed DoSetSpInternal clamp path.
            state["sp"] = FP.from_raw(max(0, min(FP.from_int32(maximum).raw, value.raw)))
        controller = NaturalSpController.reset(
            rate, lambda: state["sp"], write, max_sp=maximum, sp_type=sp_type)
        return controller, state

    def test_native_epsilon_is_division_constant_and_strict(self):
        self.assertEqual(FP_LARGE_EPS_RAW, 42950)
        self.assertNotEqual(FP_LARGE_EPS_RAW, FP.from_float32(0.00001).raw)
        self.assertTrue(PrecisePeriodicTimer(ONE, FP.from_raw(42949)).ready)
        self.assertFalse(PrecisePeriodicTimer(ONE, FP.from_raw(42950)).ready)
        self.assertFalse(PrecisePeriodicTimer(ONE, FP.from_raw(42951)).ready)

    def test_multiple_periods_and_separate_update_next(self):
        timer = PrecisePeriodicTimer.reset(ONE)
        self.assertEqual(timer.update_multiple(FP.from_float32(3.25)), 3)
        self.assertEqual(timer.remaining, FP.from_float32(-2.25))
        self.assertTrue(timer.next_multiple(3))
        self.assertEqual(timer.remaining, FP.from_float32(0.75))
        self.assertFalse(timer.next_multiple(3))
        self.assertEqual(timer.remaining, FP.from_float32(0.75))

    def test_timer_small_positive_ready_still_returns_one(self):
        timer = PrecisePeriodicTimer(ONE, FP.from_raw(42949))
        self.assertEqual(timer.tick(ZERO), 1)
        self.assertEqual(timer.remaining.raw, ONE.raw + 42949)

    def test_exact_period_boundary(self):
        timer = PrecisePeriodicTimer.reset(ONE)
        self.assertEqual(timer.tick(ONE), 1)
        self.assertEqual(timer.remaining, ONE)
        self.assertEqual(timer.tick(FP.from_float32(0.5)), 0)
        self.assertEqual(timer.remaining, FP.from_float32(0.5))

    def test_default_delta_first_seven_sp_and_drift_boundary(self):
        controller, state = self.owner(maximum=100)
        increments = []
        for frame in range(1, 362):
            if controller.on_tick(DT, sp_recover_stopped=False, timer_valid=True):
                increments.append(frame)
        self.assertEqual(increments[:7], [30, 60, 90, 120, 150, 180, 210])
        self.assertEqual(increments[:12], [30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 331, 361])
        self.assertEqual(state["sp"], FP.from_int32(12))
        # This is a reset-at-frame-zero owner fixture, not the full altar FSM.

    def test_stopped_full_invalid_and_non_time_masks_freeze_timer(self):
        controller, state = self.owner()
        for flag in [(True, True), (False, False)]:
            self.assertEqual(controller.on_tick(DT, sp_recover_stopped=flag[0], timer_valid=flag[1]), 0)
            self.assertEqual(controller.timer.remaining, ONE)
        state["sp"] = FP.from_int32(7)
        self.assertEqual(controller.on_tick(DT, sp_recover_stopped=False, timer_valid=True), 0)
        self.assertEqual(controller.timer.remaining, ONE)
        for mask in [0, 2, 4, 6]:
            other, _ = self.owner(sp_type=mask)
            self.assertEqual(other.on_tick(DT, sp_recover_stopped=False, timer_valid=True), 0)
            self.assertEqual(other.timer.remaining, ONE)

    def test_owner_setter_controls_clamp_and_multiple_recovery(self):
        controller, state = self.owner(initial=FP.from_int32(6))
        self.assertEqual(controller.on_tick(FP.from_int32(3), sp_recover_stopped=False, timer_valid=True), 3)
        self.assertEqual(state["writes"], [FP.from_int32(9).raw])
        self.assertEqual(state["sp"], FP.from_int32(7))
        before = controller.timer.remaining
        self.assertEqual(controller.on_tick(ONE, sp_recover_stopped=False, timer_valid=True), 0)
        self.assertEqual(controller.timer.remaining, before)

    def test_sp_missing_context_and_invalid_period_fail(self):
        controller, _ = self.owner()
        with self.assertRaises(UnverifiedDeviceContext):
            controller.on_tick(DT, sp_recover_stopped=None, timer_valid=True)
        with self.assertRaises(UnverifiedDeviceContext):
            NaturalSpController.reset(ZERO, lambda: ZERO, lambda _: None, max_sp=7, sp_type=1)
        with self.assertRaises(UnverifiedDeviceContext):
            PrecisePeriodicTimer.reset(ZERO)
        with self.assertRaises(ValueError):
            PrecisePeriodicTimer.reset(ONE).tick(FP.from_raw(-1))

    def test_immediate_start_finish_flags_and_callback_order(self):
        buff = ImmediateBuffLifecycle(ZERO)
        seen = []
        self.assertFalse(buff.is_finished)
        buff.attach_to_born_owner(
            lambda: seen.append(("start", buff.started, buff.is_finished, buff.finish_ran)),
            lambda: seen.append(("finish", buff.started, buff.is_finished, buff.finish_ran)),
        )
        self.assertEqual(seen, [("start", False, False, False), ("finish", True, True, True)])
        with self.assertRaises(ValueError):
            buff.attach_to_born_owner(lambda: None, lambda: None)

    def test_immediate_zero_epsilon_and_durable_rejection(self):
        for raw in [-42950, 42950]:
            buff = ImmediateBuffLifecycle(FP.from_raw(raw), started=True)
            self.assertFalse(buff.is_finished)
            with self.assertRaises(UnverifiedDeviceContext):
                ImmediateBuffLifecycle(FP.from_raw(raw)).attach_to_born_owner(lambda: None, lambda: None)
        for raw in [-42949, 42949]:
            self.assertTrue(ImmediateBuffLifecycle(FP.from_raw(raw), started=True).is_finished)
        self.assertTrue(ImmediateBuffLifecycle(ONE, marked_finished=True).is_finished)

    def test_ore_damage_request_is_separate_from_listener_switch(self):
        for immune in [False, True]:
            for listener in [False, True]:
                effects = []
                events = ore_finish_actions(
                    contains_buff=lambda key: {"ore_immune": immune, "ore_listener": listener}[key],
                    damage=lambda action: effects.append(("damage", action)),
                    switch_mode=lambda mode, restart: effects.append(("mode", mode, restart)),
                    value=FP.from_int32(500), mode=1,
                )
                self.assertEqual(events, (() if immune else ("damage_requested",)) +
                                 (("mode_switch_requested",) if listener else ()))
                if not immune:
                    self.assertEqual(effects[0], ("damage", FixedDamageAction(FP.from_int32(500))))
                if listener:
                    self.assertEqual(effects[-1], ("mode", 1, True))

    def test_ore_callbacks_cannot_be_omitted_or_return_unknown_flags(self):
        with self.assertRaises(UnverifiedDeviceContext):
            ore_finish_actions(contains_buff=None, damage=lambda _: None,
                               switch_mode=lambda *_: None, value=ONE, mode=1)
        with self.assertRaises(UnverifiedDeviceContext):
            ore_finish_actions(contains_buff=lambda _: None, damage=lambda _: None,
                               switch_mode=lambda *_: None, value=ONE, mode=1)

    def ability(self, delay, spell):
        return PreDelayAbility(pre_delay_float32=delay, delta_float32=DT.as_float(),
                               deterministic_simulator=True, spell=spell)

    def test_predelay_begin_primes_snapshot_and_spell_at_relative_frame18(self):
        spells = []
        ability = self.ability(0.6, lambda targets: spells.append(targets))
        targets = ["a", "b"]
        self.assertTrue(ability.begin(targets, wait_for_attack_event=False, interrupt_if_target_dead=False))
        self.assertEqual(ability.runner.ticks, 1)
        self.assertEqual(ability.wait_frames, 18)
        self.assertEqual(spells, [])
        targets[:] = ["c"]
        for _ in range(17):
            self.assertTrue(ability.tick())
        self.assertEqual(spells, [])
        self.assertFalse(ability.tick())
        self.assertEqual(spells, [("a", "b")])
        self.assertFalse(ability.active)

    def test_zero_delay_still_waits_one_tick_and_nearest_ties_even(self):
        calls = []
        ability = self.ability(0, lambda _: calls.append("spell"))
        ability.begin((), wait_for_attack_event=False, interrupt_if_target_dead=False)
        self.assertEqual(calls, [])
        ability.tick()
        self.assertEqual(calls, ["spell"])
        for delay, count in [(2.5, 2), (3.5, 4)]:
            a = PreDelayAbility(pre_delay_float32=delay, delta_float32=1,
                                deterministic_simulator=True, spell=lambda _: None)
            self.assertEqual(a.wait_frames, count)

    def test_animation_conditional_unity_and_missing_context_rejected(self):
        for context in [False, None]:
            with self.assertRaises(UnverifiedDeviceContext):
                PreDelayAbility(pre_delay_float32=0.6, delta_float32=1,
                                deterministic_simulator=context, spell=lambda _: None)
        for flags in [(True, False), (False, True), (None, False)]:
            with self.assertRaises(UnverifiedDeviceContext):
                self.ability(0.6, lambda _: None).begin((), wait_for_attack_event=flags[0], interrupt_if_target_dead=flags[1])


if __name__ == "__main__":
    unittest.main()

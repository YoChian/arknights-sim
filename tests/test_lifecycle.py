from pathlib import Path
import json
import unittest

from arknights_probe.data import DataError
from arknights_probe.env import UnverifiedMechanism
from arknights_probe.fp import FP, binary32
from arknights_probe.lifecycle import (LifecycleRuntime, native_alive, BORN_STATE,
    MOVE_STATE, STOPPED_STATE, SINGLE_EPSILON, ALIVE_EPSILON_RAW)


def runtime(**kwargs):
    options = dict(initial_life=5, initial_temp_life=0, dt=FP.from_raw(143165440),
                   use_recycle_to_finish_scheduler=True, context_source="explicit offline test scenario")
    options.update(kwargs)
    return LifecycleRuntime(**options)


def spawn(env, identifier="e", **kwargs):
    options = dict(max_hp=FP.from_int32(100), birth_delay=0, recycle_delay=.1,
                   life_point_reduce=1, managed=True, wave_block=True,
                   not_count_in_total=False, lifecycle_templates=())
    options.update(kwargs)
    return env.spawn(identifier, "enemy_test_ordinary", **options)


class LifecycleTests(unittest.TestCase):
    def test_zero_birth_delay_starts_alive_but_cannot_move_until_next_state_tick(self):
        env = runtime()
        actor = spawn(env)
        self.assertEqual(actor.state_id, BORN_STATE)
        self.assertTrue(actor.alive)
        self.assertFalse(actor.move_state_ready)
        self.assertEqual(env.wave_ids, {"e"})
        with self.assertRaises(DataError):
            env.reach_exit("e")
        env.begin_frame()
        self.assertFalse(env.tick_state("e"))
        self.assertEqual(actor.state_id, MOVE_STATE)
        self.assertTrue(actor.move_state_ready)
        env.begin_frame()
        self.assertTrue(env.tick_state("e"))

    def test_birth_uses_fp_subtraction_and_not_coroutine_rounding(self):
        env = runtime()
        actor = spawn(env, birth_delay=.05)
        self.assertFalse(env.tick_state("e"))
        self.assertEqual(actor.state_id, BORN_STATE)
        self.assertFalse(env.tick_state("e"))
        self.assertEqual(actor.state_id, MOVE_STATE)
        self.assertEqual(actor.born_remaining.raw,
                         FP.from_float32(.05).raw - 2 * env.dt.raw)
        tiny = spawn(env, "tiny", birth_delay=SINGLE_EPSILON)
        self.assertEqual(tiny.born_remaining.raw, 0)

    def test_alive_uses_registered_state_and_en5_not_zero_hp(self):
        self.assertFalse(native_alive(6, FP.from_raw(ALIVE_EPSILON_RAW)))
        self.assertTrue(native_alive(6, FP.from_raw(ALIVE_EPSILON_RAW + 1)))
        self.assertFalse(native_alive(-1, FP.from_int32(100)))
        self.assertFalse(native_alive(99, FP.from_int32(100)))
        env = runtime()
        actor = spawn(env, max_hp=FP.from_raw(1))
        self.assertFalse(actor.alive)
        self.assertEqual(env.final_ids, set())

    def test_exit_releases_wave_then_waits_for_pool_before_final(self):
        env = runtime()
        actor = spawn(env)
        env.tick()
        self.assertTrue(env.reach_exit("e"))
        self.assertEqual((actor.state_id, actor.finish_reason), (STOPPED_STATE, 1))
        self.assertFalse(actor.alive)
        self.assertFalse(env.wave_blocked)
        self.assertEqual(env.final_ids, {"e"})
        self.assertEqual(env.life, 4)
        self.assertFalse(env.check_final(schedule_complete=True, branches_active=False))
        env.tick()
        env.tick()
        self.assertFalse(actor.recycled)
        env.tick()
        self.assertTrue(actor.recycled)
        self.assertEqual(env.final_ids, set())
        self.assertTrue(env.check_final(schedule_complete=True, branches_active=False))
        self.assertEqual(env.finish_request, "win")
        kinds = [event["kind"] for event in env.events]
        self.assertLess(kinds.index("enemy_wave_released"), kinds.index("life_modified"))
        self.assertLess(kinds.index("life_modified"), kinds.index("enemy_recycle_scheduled"))
        self.assertLess(kinds.index("enemy_reached_exit"), kinds.index("enemy_recycle_scheduled"))
        self.assertLess(kinds.index("life_modified"), kinds.index("enemy_recycled"))
        self.assertLess(kinds.index("enemy_reached_exit"), kinds.index("enemy_recycled"))

    def test_scheduler_flag_can_release_final_before_actual_recycle(self):
        env = runtime(use_recycle_to_finish_scheduler=False)
        actor = spawn(env, recycle_delay=5)
        env.tick()
        env.reach_exit("e")
        self.assertFalse(actor.recycled)
        self.assertEqual(env.final_ids, set())
        self.assertTrue(env.check_final(schedule_complete=True, branches_active=False))

    def test_temp_life_absorbs_exit_cost_and_event_reports_permanent_delta(self):
        env = runtime(initial_life=3, initial_temp_life=2)
        spawn(env, life_point_reduce=3)
        env.tick()
        env.reach_exit("e")
        self.assertEqual((env.life, env.temp_life, env.exit_life_lost), (2, 0, 1))
        event = next(e for e in env.events if e["kind"] == "life_modified")
        self.assertEqual(event["applied_delta"], -1)
        self.assertEqual(event["applied_delta_fp_raw"], -(1 << 32))
        self.assertFalse(env.reach_exit("e"))
        self.assertEqual(env.life, 2)

    def test_exact_absorption_and_positive_temp_grant(self):
        env = runtime(initial_life=3, initial_temp_life=2)
        result = env.modify_life(-2, source="test", is_reach_exit=True)
        self.assertEqual((env.life, env.temp_life, result["applied_delta"]), (3, 0, 0))
        result = env.modify_life(4, source="test", to_temp_life=True)
        self.assertEqual((env.life, env.temp_life, result["applied_delta"]), (3, 4, 0))
        self.assertEqual(env.exit_life_lost, 0)

    def test_zero_life_requests_loss_before_event22_and_never_changes_to_win(self):
        env = runtime(initial_life=1)
        spawn(env)
        env.tick()
        env.reach_exit("e")
        self.assertEqual((env.life, env.finish_request), (0, "lose"))
        kinds = [e["kind"] for e in env.events]
        self.assertLess(kinds.index("battle_finish_requested"), kinds.index("life_modified"))
        env.final_ids.clear()
        env.check_final(schedule_complete=True, branches_active=False)
        self.assertEqual(env.finish_request, "lose")
        self.assertFalse(env.modify_life(9, source="after_game")["applied"])

    def test_effectively_zero_delay_recycles_without_a_wait_frame(self):
        env = runtime()
        actor = spawn(env, recycle_delay=SINGLE_EPSILON)
        env.tick()
        env.reach_exit("e")
        self.assertTrue(actor.recycled)
        self.assertEqual(env.recycle_runners, {})
        kinds = [e["kind"] for e in env.events]
        self.assertLess(kinds.index("enemy_wave_released"), kinds.index("enemy_recycled"))
        self.assertLess(kinds.index("life_modified"), kinds.index("enemy_recycled"))

    def test_unmanaged_not_counted_and_branch_gates_are_separate(self):
        env = runtime()
        spawn(env, "unmanaged", managed=False)
        spawn(env, "uncounted", not_count_in_total=True)
        self.assertFalse(env.wave_ids or env.final_ids)
        self.assertFalse(env.check_final(schedule_complete=False, branches_active=False))
        self.assertFalse(env.check_final(schedule_complete=True, branches_active=True))
        self.assertTrue(env.check_final(schedule_complete=True, branches_active=False))

    def test_explicit_context_and_active_npc_templates_fail_closed(self):
        for overrides in ({"initial_life": 0}, {"initial_temp_life": -1}, {"context_source": ""}):
            with self.subTest(overrides=overrides), self.assertRaises(DataError):
                runtime(**overrides)
        for overrides in ({"mode_backend": "RoguelikeGameMode"}, {"hotfix_policy": "assume_none"},
                          {"global_modifiers": ("unknown",)}):
            with self.subTest(overrides=overrides), self.assertRaises(UnverifiedMechanism):
                runtime(**overrides)
        env = runtime()
        self.assertFalse(env.info()["scheduler_event_binding_verified"])
        self.assertEqual(env.info()["finish_reason_scope"], "ReachExit_reason1_only")
        spawn(env)
        with self.assertRaises(UnverifiedMechanism):
            env.finish("e", 2)
        with self.assertRaises(UnverifiedMechanism):
            spawn(env, "active_talent", lifecycle_templates=("upeople_t",))
        for enemy in ("enemy_2133_shdopl", "enemy_3001_upeopl"):
            with self.subTest(enemy=enemy), self.assertRaises(UnverifiedMechanism):
                env.spawn(enemy, enemy, max_hp=FP.from_int32(100), birth_delay=0, recycle_delay=.1,
                          life_point_reduce=0, managed=False, wave_block=False,
                          not_count_in_total=True, lifecycle_templates=())

    def test_independent_csharp_reference_boundary_vectors(self):
        path = Path(__file__).resolve().parents[1]/"evidence/lifecycle/reference_vectors.json"
        data = json.loads(path.read_text(encoding="utf8"))
        self.assertGreaterEqual(len(data["vectors"]), 100)
        for vector in data["vectors"]:
            case, expected = vector["input"], vector["expected"]
            with self.subTest(id=case["id"]):
                if case["mode"] == "life":
                    env = runtime(initial_life=case["life"], initial_temp_life=case["temp"])
                    result = env.modify_life(case["delta"], source="CSharp static reference",
                                             to_temp_life=case["to_temp"], is_reach_exit=case["exit"])
                    self.assertEqual({"life": env.life, "temp": env.temp_life,
                                      "applied_delta": result["applied_delta"], "lost": env.terminated}, expected)
                elif case["mode"] == "alive":
                    self.assertEqual(native_alive(case["state"], FP.from_raw(case["hp_raw"])), expected["alive"])
                elif case["mode"] == "birth":
                    env = runtime(dt=FP.from_raw(case["dt_raw"]))
                    actor = spawn(env, birth_delay=case["delay"])
                    self.assertEqual(actor.born_remaining.raw, expected["remaining_raw"])
                    ticks = 0
                    while actor.state_id == BORN_STATE:
                        env.tick_state("e")
                        ticks += 1
                    self.assertEqual(ticks, expected["frames"])
                elif case["mode"] == "recycle":
                    env = runtime(dt=FP.from_raw(case["dt_raw"]))
                    actor = spawn(env, recycle_delay=case["delay"])
                    env.tick_state("e")
                    env.reach_exit("e")
                    ticks = 0
                    while not actor.recycled:
                        env.tick_recycling()
                        ticks += 1
                    self.assertEqual(ticks, expected["frames"])
                else:
                    self.fail(case["mode"])


if __name__ == "__main__":
    unittest.main()

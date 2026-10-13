import copy
from pathlib import Path
import unittest

from arknights_probe import Dataset, DataError
from arknights_probe.env import UnverifiedMechanism
from arknights_probe.fp import FP, binary32
from arknights_probe.coroutines import float_wait_frames
from arknights_probe.timeline import ASSET_DEFAULT_DT_RAW, TimelineEnv, compile_timeline, zero_enemy_fixture
from arknights_probe.timeline_validation import verify_timeline_evidence

ROOT = Path(__file__).resolve().parents[1]


class TimelineTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(ROOT / "data/manifest.json")

    def compile(self, **kwargs):
        options = {"mode": "NORMAL", "group_selections": {"t1": 0, "t2": 5, "c1": 4},
                   "enemy_runtime": zero_enemy_fixture(self.dataset), "input_source": "unit_test_explicit_zero_delay_counted_creation_fixture"}
        options.update(kwargs)
        return compile_timeline(self.dataset, **options)

    def test_static_evidence_hashes_and_runtime_boundary(self):
        evidence = verify_timeline_evidence()
        self.assertTrue(evidence["healthy"])
        self.assertEqual(evidence["files_checked"], 11)
        self.assertFalse(evidence["client_runtime_compared"])

    def test_info_is_copy_and_terminated_branch_is_rejected(self):
        env = TimelineEnv(self.dataset, self.compile(mode="FOUR_STAR"))
        _, info = env.reset()
        info["hidden_groups"].append("invented")
        info["external_inputs"]["input_source"] = "mutated"
        self.assertEqual(env.info()["hidden_groups"], ["raid"])
        self.assertNotEqual(env.info()["external_inputs"]["input_source"], "mutated")
        env.step({"type": "tick", "frames": 40})
        for identifier in list(env.alive):
            env.step({"type": "external_resolve", "id": identifier, "outcome": "missed", "source": "test_complete_terminal_fixture"})
        env.step({"type": "external_final_complete", "source": "test_final_keys_complete"})
        self.assertTrue(env.step({"type": "tick", "frames": 20})[2])
        with self.assertRaises(DataError):
            env.step({"type": "external_trigger_branch", "branch": "shsbox1", "source": "test_after_termination"})

    def test_modes_and_empty_choices_preserved_until_selection(self):
        normal = self.compile()
        raid = self.compile(mode="FOUR_STAR")
        self.assertEqual(normal.waves[0]["fragments"][0]["items"], [])
        self.assertEqual(normal.waves[2]["fragments"][0]["items"], [])
        self.assertEqual(normal.hidden_groups, ["normal"])
        self.assertEqual(raid.hidden_groups, ["raid"])
        normal_items = normal.waves[1]["fragments"][0]["items"]
        raid_items = raid.waves[1]["fragments"][0]["items"]
        self.assertEqual(len(normal_items), 14)
        self.assertEqual(len(raid_items), 14)
        self.assertEqual(sum(x["action"]["key"] == "enemy_1034_laxe" for x in normal_items), 2)
        self.assertEqual(sum(x["action"]["key"] == "enemy_1085_sotiwz_3" for x in raid_items), 3)
        self.assertEqual(len(normal.waves[1]["fragments"][1]["items"]), 3)  # two previews plus spawn
        self.assertEqual(raid.waves[1]["fragments"][1]["items"], [])

    def test_external_choices_are_strict_original_indices(self):
        for selection in ({"t1": None, "t2": 5, "c1": 4}, {"t1": 0, "t2": 0, "c1": 4}, {"t1": 0, "t2": 5}, {"t1": 0, "t2": 5, "c1": 4, "invented": 0}):
            with self.assertRaises(DataError):
                self.compile(group_selections=selection)
        boxes = self.compile(group_selections={"t1": 1, "t2": 6, "c1": 1})
        self.assertEqual([x["action"]["key"] for x in boxes.waves[0]["fragments"][0]["items"]], ["trap_321_shnbox#2", "trap_321_shnbox#1"])
        spawn = next(x for x in boxes.waves[2]["fragments"][0]["items"] if x["action"]["actionType"] == "SPAWN")
        self.assertEqual(spawn["action"]["key"], "enemy_2001_duckmi")

    def test_native_rounding_and_asset_clock(self):
        dt = FP.from_raw(ASSET_DEFAULT_DT_RAW).as_float()
        self.assertEqual(dt, 0.03333330154418945)
        self.assertEqual(float_wait_frames(1, dt), 30)
        self.assertEqual(float_wait_frames(binary32(.3), dt), 9)
        self.assertNotEqual(ASSET_DEFAULT_DT_RAW, FP.from_float32(1 / 30).raw)

    def test_preview_queue_order_and_two_step_float_arithmetic(self):
        items = self.compile().waves[1]["fragments"][1]["items"]
        self.assertEqual([x["action"]["actionType"] for x in items], ["PREVIEW_CURSOR", "PREVIEW_CURSOR", "SPAWN"])
        self.assertEqual([x["time"] for x in items], [24.0, binary32(binary32(.3) + 24), 27.0])

    def test_frame_spawns_serial_gate_requires_external_input(self):
        env = TimelineEnv(self.dataset, self.compile())
        _, info = env.reset(seed=42)
        env.step({"type": "tick", "frames": 1200})
        events = [x for x in env.events if x["kind"] == "spawn_request"]
        self.assertEqual(len(events), 15)
        self.assertEqual([x["frame"] for x in events[:14]], list(range(5, 19)))
        self.assertEqual(len([x for x in env.events if x["kind"] == "preview_cursor_request"]), 2)
        self.assertEqual(env.observe()["phase"], "wave_gate")
        self.assertEqual(env.observe()["time_raw"], 1200 * ASSET_DEFAULT_DT_RAW)
        self.assertFalse(info["battle_ready"])
        self.assertFalse(info["seed_consumed"])
        self.assertFalse(info["live_fixed_delta_validated"])
        env.step({"type": "tick", "frames": 10})
        self.assertEqual(len(env.alive), 15)
        for identifier in list(env.alive):
            observation, reward, done, _, _ = env.step({"type": "external_resolve", "id": identifier, "outcome": "killed", "source": "test_complete_terminal_fixture_including_recycle"})
            self.assertIsNone(reward)
            self.assertFalse(done)
        env.step({"type": "tick", "frames": 20})
        self.assertEqual(env.phase, "final_external_gate")
        env.step({"type": "external_final_complete", "source": "test_external_mode_and_block_key_completion"})
        self.assertTrue(env.step({"type": "tick"})[2])
        self.assertEqual(env.phase, "kernel_complete")

    def test_repeatability_branch_uses_extra_routes_and_resolve_is_not_combat(self):
        outputs = []
        for _ in range(2):
            env = TimelineEnv(self.dataset, self.compile(mode="FOUR_STAR"))
            env.reset(seed=123)
            env.step({"type": "external_trigger_branch", "branch": "shsbox1", "source": "explicit_test_trigger"})
            branch = env.events[-1]
            self.assertEqual(branch["kind"], "spawn_request")
            self.assertEqual(branch["route_pool"], "extraRoutes")
            self.assertEqual(branch["route_index"], 1)
            self.assertFalse(branch["wave_block"])
            env.step({"type": "tick", "frames": 40})
            outputs.append((env.observe(), env.events))
            with self.assertRaises(UnverifiedMechanism):
                env.step({"type": "deploy"})
            with self.assertRaises(DataError):
                env.step({"type": "external_resolve", "id": "unknown", "outcome": "killed", "source": "fixture"})
        self.assertEqual(outputs[0], outputs[1])

    def test_wave_release_and_recycle_are_separate_native_memberships(self):
        env = TimelineEnv(self.dataset, self.compile(mode="FOUR_STAR"))
        env.reset()
        env.step({"type": "tick", "frames": 40})
        identifier = next(iter(env.alive))
        env.step({"type": "external_release_wave", "id": identifier, "source": "test_release"})
        self.assertNotIn(identifier, env.wave_ids)
        self.assertIn(identifier, env.final_ids)
        self.assertIn(identifier, env.alive)
        env.step({"type": "external_recycle", "id": identifier, "source": "test_recycle"})
        self.assertNotIn(identifier, env.final_ids)
        self.assertNotIn(identifier, env.alive)
        other = next(iter(env.alive))
        env.step({"type": "external_recycle", "id": other, "source": "test_recycle_before_release"})
        self.assertIn(other, env.wave_ids)
        env.step({"type": "external_release_wave", "id": other, "source": "test_independent_release"})
        self.assertNotIn(other, env.wave_ids)

    def test_external_extra_delay_is_explicit_and_changes_schedule(self):
        runtime = zero_enemy_fixture(self.dataset)
        runtime["enemy_1085_sotiwz_3"]["extraSpawnDelay"] = 5
        compiled = self.compile(enemy_runtime=runtime)
        self.assertEqual(compiled.waves[1]["fragments"][1]["items"][-1]["time"], 22)
        with self.assertRaises(DataError):
            self.compile(enemy_runtime={})
        with self.assertRaises(DataError):
            self.compile(input_source="")

    def test_large_queue_uses_native_sort_and_non_always_fail_closed(self):
        level = copy.deepcopy(self.dataset.level)
        action = level["waves"][1]["fragments"][0]["actions"][0]
        action["count"] = 30
        other = Dataset(level, self.dataset.tables, self.dataset.provenance)
        compiled = compile_timeline(other, mode="NORMAL", group_selections={"t1": 0, "t2": 5, "c1": 4}, enemy_runtime=zero_enemy_fixture(other), input_source="test")
        items = compiled.waves[1]["fragments"][0]["items"]
        self.assertEqual(len(items), 43)
        self.assertEqual([x["time"] for x in items], sorted(x["time"] for x in items))
        action["count"] = 1
        action["randomType"] = "invented"
        other = Dataset(level, self.dataset.tables, self.dataset.provenance)
        with self.assertRaises(DataError):
            compile_timeline(other, mode="NORMAL", group_selections={"t1": 0, "t2": 5, "c1": 4}, enemy_runtime=zero_enemy_fixture(other), input_source="test")


if __name__ == "__main__":
    unittest.main()

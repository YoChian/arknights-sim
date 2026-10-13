import unittest

from arknights_probe.npc_component import NpcComponentProbe, run_npc_component_fixtures


class NpcComponentTests(unittest.TestCase):
    def test_zero_delay_summon_delayed_hide_and_next_tick_restore(self):
        probe = NpcComponentProbe()
        self.assertFalse(probe.snapshot()["npc_created"])
        self.assertEqual(probe.snapshot()["host_state"], 11)
        probe.step(1)
        self.assertTrue(probe.snapshot()["npc_created"])
        self.assertEqual((probe.snapshot()["wave_members"], probe.snapshot()["final_members"]), (0, 1))
        probe.step(7)
        self.assertTrue(probe.snapshot()["host_game_active"])
        probe.step(1)
        self.assertFalse(probe.snapshot()["host_game_active"])
        probe.supply_npc_pose((3, 5), 4)
        probe.take_damage_signal()
        s = probe.snapshot()
        self.assertEqual((s["host_grid"], s["host_cursor_index"], s["host_route"]),
                         ([3, 5], 4, "npc_runtime_route_11"))
        self.assertFalse(s["host_disappeared"])
        self.assertFalse(s["host_game_active"])
        self.assertEqual(s["host_state"], 11)
        probe.step(1)
        self.assertTrue(probe.snapshot()["host_game_active"])
        self.assertEqual(probe.snapshot()["host_state"], 1)
        self.assertFalse(any(e["frame"] == 10 and e["event"] == "stationary_move_provider" for e in probe.events))
        probe.step(1)
        self.assertTrue(any(e["frame"] == 11 and e["event"] == "stationary_move_provider" for e in probe.events))

    def test_synchronous_finish7_reentry_keeps_lock_zero_and_does_not_lose_life(self):
        p = NpcComponentProbe()
        p.step(10)
        p.supply_npc_pose()
        p.take_damage_signal()
        s = p.snapshot()
        self.assertEqual((s["finish_reason"], s["life"], s["lock"], s["clear_callbacks"]), (7, 3, 0.0, 0))
        self.assertEqual(s["restore_callbacks"], 2)  # Explicit fixture membership dispatch, not all native containers.
        self.assertEqual(p.signal_results[0]["stopped_before"], "AssignValueToBB")
        self.assertEqual(p.actions.context.depth, 0)
        self.assertIsNone(p.actions.context.current.buff)
        self.assertTrue(any(t[0] == "event" and t[2] == 4 and t[3] >= 2 for t in p.actions.trace))
        self.assertEqual(p.life.events, [])
        self.assertEqual(s["final_members"], 1)  # Native mode/pool not fabricated.

    def test_death2_uses_case_insensitive_dead_binding_and_default_life_component(self):
        p = NpcComponentProbe()
        p.step(10)
        p.supply_npc_pose()
        self.assertEqual(p.dead_buff.blackboard.integer("value"), -1)
        p.death_signal()
        self.assertEqual(p.snapshot()["life"], 2)
        self.assertEqual(p.snapshot()["restore_callbacks"], 1)
        self.assertEqual(len(p.life.events), 1)
        self.assertFalse(p.life.events[0]["is_reach_exit"])
        self.assertEqual(p.life.events[0]["requested_delta"], -1)

    def test_restoring_before_hide_wait_finishes_cancels_pending_deactivation(self):
        p = NpcComponentProbe()
        p.step(1)
        p.supply_npc_pose()
        p.take_damage_signal()
        p.step(15)
        self.assertTrue(p.snapshot()["host_game_active"])
        self.assertFalse(any(e["kind"] == "set_active" and not e["value"] for e in p.restoration.events))
        self.assertFalse(p.simulator.handlers)

    def test_changed_source_uid_stops_restore_action_without_finishing_npc(self):
        p = NpcComponentProbe()
        p.step(10)
        p.supply_npc_pose()
        p.host.uid = p.host_restore.uid = 1000
        p.take_damage_signal()
        self.assertTrue(p.snapshot()["npc_alive"])
        self.assertTrue(p.snapshot()["host_disappeared"])
        self.assertEqual(p.snapshot()["restore_callbacks"], 0)
        self.assertIsNone(p.snapshot()["finish_reason"])

    def test_reset_chunking_and_all_readiness_flags_remain_false(self):
        p = NpcComponentProbe()
        p.step(10)
        p.supply_npc_pose()
        p.take_damage_signal()
        p.step(2)
        artifact = p.artifact()
        p.reset()
        p.step(3)
        p.step(7)
        p.supply_npc_pose()
        p.take_damage_signal()
        p.step(1)
        p.step(1)
        self.assertEqual(p.artifact(), artifact)
        for name in ("battle_ready", "autonomous_route_ready", "runtime_battle_validated"):
            self.assertFalse(artifact[name])
        self.assertIsNone(artifact["reward"])
        self.assertFalse(artifact["external_inputs"]["npc_hp_damage_calculated"])
        self.assertEqual(run_npc_component_fixtures()["damage_signal_fixture"]["snapshot"], p.snapshot())


if __name__ == "__main__":
    unittest.main()

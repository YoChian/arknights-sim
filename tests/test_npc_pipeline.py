import unittest

from arknights_probe.npc_actions import EntityPtr
from arknights_probe.npc_pipeline import NpcPipelineProbe


class NpcPipelineTests(unittest.TestCase):
    def test_factory_and_lifecycle_use_one_identity_and_do_not_skip_birth(self):
        probe = NpcPipelineProbe()
        probe.step(1)
        self.assertEqual(probe.npc.state_id, 6)
        self.assertIs(probe.npc, probe.containers[probe.npc.token].owner)
        self.assertIs(probe.npc, probe.npc_lifecycle_actor.identity)
        self.assertEqual(probe.npc.hp.raw, 3500 << 32)
        self.assertTrue(probe.npc.borned)
        container = probe.containers[probe.npc.token]
        self.assertFalse(container.state(probe.dead_buff).started)
        common = next(buff for buff in container.states if buff.template_key == 'empty')
        self.assertTrue(container.state(common).started)
        self.assertNotIn(('owner_event', common.token, 12), container.trace)
        self.assertIn(('owner_event', common.token, 35), container.trace)
        probe.step(1)
        self.assertEqual(probe.npc.state_id, 1)
        self.assertTrue(probe.containers[probe.npc.token].state(probe.dead_buff).started)
        self.assertFalse(any(e['event'] == 'stationary_npc_move_provider' for e in probe.events))
        probe.step(1)
        self.assertTrue(any(e['event'] == 'stationary_npc_move_provider' for e in probe.events))

    def prepared(self):
        probe = NpcPipelineProbe()
        probe.step(10)
        probe.supply_npc_pose()
        return probe

    def test_native_finish7_recycles_and_clears_final_without_death_life(self):
        probe = self.prepared()
        captured = EntityPtr.capture(probe.npc)
        result = probe.apply_prepared_damage()
        self.assertEqual((result['finish_reason'], result['npc_uid'], result['final_members']), (7,0,0))
        self.assertEqual((result['life'],result['restore_callbacks'],result['lock'],result['clear_callbacks']), (3,2,0,0))
        self.assertEqual(result['host_grid'], [3,5])
        self.assertIsNone(captured.resolve())
        self.assertTrue(probe.npc.unity_exists)
        stages = [e['stage'] for e in probe.native_lifecycle.events]
        self.assertLess(stages.index('battle_event6'), stages.index('uid_invalidated'))
        self.assertLess(stages.index('uid_invalidated'), stages.index('battle_event8'))
        self.assertLess(stages.index('battle_event8'), stages.index('raw_pool_recycled'))
        self.assertEqual(probe.ledger.counters.finished, 0)
        self.assertEqual(probe.npc.hp.raw, 3500 << 32)

    def test_cancelled_damage_still_executes_npc_buff_and_skips_animator(self):
        probe = self.prepared()
        probe.apply_prepared_damage(unhurtable=True)
        self.assertTrue(probe.npc_lifecycle_actor.recycled)
        self.assertEqual(probe.signal_results[0]['cancel_reason'], 1)
        self.assertFalse(any(e['event'] == 'unit_damage_animator_provider' for e in probe.events))
        self.assertEqual(probe.life.life, 3)

    def test_reaction_continues_after_pool_with_uid_zero(self):
        probe = self.prepared()
        probe.apply_prepared_damage()
        tail = [e for e in probe.events if e['event'] in
                ('mode_finalize_damage_provider','entity_damage_event_provider','unit_damage_animator_provider')]
        self.assertEqual([e['uid'] for e in tail], [0,0,0])
        self.assertFalse(probe.signal_results[0]['apply_modifier_completed'])

    def test_death_releases_wave_then_retains_final_until_delayed_recycle(self):
        probe = self.prepared()
        probe.death_signal()
        self.assertEqual((probe.life.life,probe.restore_count,probe.npc.uid,len(probe.ledger.final)), (2,1,24,1))
        self.assertFalse(probe.npc_lifecycle_actor.recycled)
        probe.step(17)
        self.assertEqual(len(probe.ledger.final), 1)
        probe.step(1)
        self.assertEqual((probe.frame,probe.npc.uid,len(probe.ledger.final)), (28,0,0))
        self.assertTrue(any(e['event'] == 'external_death_audio_create_buff_provider' for e in probe.events))
        self.assertEqual(probe.ledger.counters.killed, 0)

    def test_restore_appearance_and_passive_cleanup_follow_next_tick(self):
        probe = self.prepared()
        probe.apply_prepared_damage()
        host_container = probe.containers[probe.host.token]
        self.assertTrue(host_container.state(probe.passive_buff).marked_finished)
        self.assertFalse(probe.host_restore.game_active)
        probe.step(1)
        self.assertTrue(probe.host_restore.game_active)
        self.assertEqual(probe.host_restore.state_id, 1)
        self.assertEqual(len(host_container.buffs.live), 0)
        self.assertFalse(any(e['event'] == 'stationary_host_move_provider' and e['frame']==11 for e in probe.events))
        probe.step(1)
        self.assertTrue(any(e['event'] == 'stationary_host_move_provider' and e['frame']==12 for e in probe.events))

    def test_segmented_steps_and_reset_keep_the_selected_trace(self):
        a = self.prepared()
        b = NpcPipelineProbe(a.dataset)
        b.step(3); b.step(7); b.supply_npc_pose()
        a.apply_prepared_damage(); b.apply_prepared_damage()
        a.step(2); b.step(1); b.step(1)
        self.assertEqual(a.artifact(), b.artifact())
        a.reset(); a.step(10); a.supply_npc_pose(); a.apply_prepared_damage(); a.step(2)
        self.assertEqual(a.artifact(), b.artifact())

    def test_closed_component_never_reports_training_or_full_map_win(self):
        probe = self.prepared()
        probe.apply_prepared_damage()
        artifact = probe.artifact()
        self.assertFalse(artifact['battle_ready'])
        self.assertFalse(artifact['autonomous_route_ready'])
        self.assertFalse(artifact['runtime_battle_validated'])
        self.assertIsNone(artifact['reward'])
        with self.assertRaises(ValueError):
            probe.take_damage_signal()


if __name__ == '__main__':
    unittest.main()

import unittest

from arknights_probe.altar_component import AltarComponentProbe
from arknights_probe.data import Dataset
from arknights_probe.devices import FixedDamageAction
from arknights_probe.fp import FP
from arknights_probe.prepare import DEFAULT_MANIFEST


class AltarCompositionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(DEFAULT_MANIFEST)

    def test_shared_skill_wait_target_dedup_and_hp_write(self):
        probe = AltarComponentProbe(self.dataset)
        probe.step(226)
        self.assertEqual(probe.actor.hp.as_int(), 9000)
        self.assertEqual(probe.skill.cast_count, 1)
        self.assertEqual(probe.selections[0]["hit_uids"], [2])
        self.assertEqual([d["reason"] for d in probe.selections[0]["decisions"]],
                         ["admitted", "duplicate_admitted_uid", "duplicate_admitted_uid"])
        probe.step()
        self.assertEqual(probe.damage_results[0]["frame"], 227)
        self.assertEqual(probe.actor.hp.as_int(), 8500)
        self.assertTrue(probe.buff_events[0]["marked_finished_before_damage"])
        self.assertFalse(probe.snapshot()["battle_ready"])

    def test_18_real_hp_writes_death_and_delayed_final_gate(self):
        probe = AltarComponentProbe(self.dataset)
        probe.step(4121)
        self.assertEqual(len(probe.damage_results), 18)
        self.assertTrue(all(d["applied"] for d in probe.damage_results))
        self.assertEqual(probe.actor.hp.raw, 0)
        self.assertEqual(probe.actor.finish_reason, 2)
        self.assertFalse(probe.lifecycle.wave_ids)
        self.assertEqual(probe.lifecycle.final_ids, {probe.target_id})
        self.assertIsNone(probe.lifecycle.finish_request)
        probe.step(18)
        self.assertTrue(probe.actor.recycled)
        self.assertEqual(probe.snapshot()["frame"], 4139)
        self.assertEqual(probe.lifecycle.finish_request, "win")
        self.assertEqual(probe.lifecycle.life, 3)
        self.assertFalse(probe.lifecycle.final_ids)

    def test_target_membership_snapshot_does_not_freeze_live_hp(self):
        probe = AltarComponentProbe(self.dataset)
        probe.step(210)  # Membership captured; native pre-delay still running.
        self.assertEqual(len(probe.skill.targets), 1)
        self.assertTrue(probe.skill.targets[0].alive)
        # Explicit additional fixture damage kills the same live actor.
        probe.damage.apply(probe.target_id, FixedDamageAction(FP.from_int32(9000)),
                           atk_scale=FP.from_int32(1))
        probe.step(17)
        self.assertEqual(len(probe.damage_results), 1)
        self.assertFalse(probe.damage_results[0]["applied"])
        self.assertEqual(probe.damage_results[0]["hp_before_raw"], 0)
        self.assertEqual(probe.actor.hp.raw, 0)

    def test_reset_and_chunked_steps_are_repeatable(self):
        probe = AltarComponentProbe(self.dataset)
        probe.step(500)
        first = probe.artifact()
        self.assertEqual(probe.reset()["frame"], 0)
        probe.step(200); probe.step(300)
        self.assertEqual(probe.artifact(), first)

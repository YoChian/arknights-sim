import unittest

from arknights_probe.env import UnverifiedMechanism
from arknights_probe.fp import FP
from arknights_probe.npc_actions import EntityPtr, NpcEntity
from arknights_probe.npc_damage import (
    DamageReactionCallbacks, DamageReactionInputs, NpcDamagePacket, NpcDamageReactionRuntime,
)


class NpcDamageTests(unittest.TestCase):
    def setup_runtime(self, *, buff=None):
        self.owner = NpcEntity("npc", 24, True, True, True, False, (3, 5))
        self.source = NpcEntity("altar", 9, True, True, False, True, (5, 6))
        self.calls = []
        def on_buff(packet):
            self.calls.append(("buff", self.owner.uid, packet.is_cancelled))
            if buff:
                buff(self.owner, packet)
        callbacks = DamageReactionCallbacks(on_buff,
            lambda owner, packet: self.calls.append(("mode", owner.uid, packet.is_cancelled)),
            lambda owner, event, packet: self.calls.append(("event", event, owner.uid)),
            lambda owner, packet: self.calls.append(("animator", owner.uid, owner.alive)), "fixture")
        return NpcDamageReactionRuntime(callbacks)

    def packet(self):
        return NpcDamagePacket(EntityPtr.capture(self.source), EntityPtr.capture(self.owner), FP.from_int32(500))

    def inputs(self, **changes):
        values = dict(source="explicit decoded fixture", native_default_no_hotfix=True,
            is_disappeared=False, is_unhurtable_with_modifier=False,
            ability_damage_miss=False, bypass_unhurtable=False,
            sp_controller_exists=True, sp_recovery_type=0, mode_backend="DefaultGameMode")
        values.update(changes)
        return DamageReactionInputs(**values)

    def test_sync_recycle_does_not_skip_remaining_unit_callbacks(self):
        def finish(owner, packet):
            owner.alive = False
            owner.uid = 0
        runtime = self.setup_runtime(buff=finish)
        result = runtime.react(self.owner, self.packet(), self.inputs())
        self.assertEqual(self.calls, [("buff",24,False),("mode",0,False),("event",12,0),("animator",0,False)])
        self.assertFalse(result["hp_write_executed"])

    def test_cancelled_packet_still_reaches_buff_mode_event(self):
        runtime = self.setup_runtime()
        packet = self.packet()
        runtime.react(self.owner, packet, self.inputs(is_unhurtable_with_modifier=True, ability_damage_miss=True))
        self.assertEqual(packet.cancel_reason, 1)
        self.assertEqual([c[0] for c in self.calls], ["buff","mode","event"])
        self.assertEqual(packet.final_delta.raw, 0)

    def test_disappeared_early_return_suppresses_container(self):
        runtime = self.setup_runtime()
        result = runtime.react(self.owner, self.packet(), self.inputs(is_disappeared=True))
        self.assertEqual(self.calls, [])
        self.assertEqual(result["cancel_reason"], 0)

    def test_bypass_only_skips_unhurtable_and_not_miss(self):
        runtime = self.setup_runtime()
        packet = self.packet()
        runtime.react(self.owner, packet, self.inputs(is_unhurtable_with_modifier=True,
                      bypass_unhurtable=True, ability_damage_miss=True))
        self.assertEqual(packet.cancel_reason, 6)

    def test_no_extra_alive_gate_at_reaction_entry(self):
        runtime = self.setup_runtime()
        self.owner.alive = False
        runtime.react(self.owner, self.packet(), self.inputs())
        self.assertEqual([c[0] for c in self.calls], ["buff","mode","event","animator"])

    def test_unclosed_sp_and_hotfix_branches_reject_before_dispatch(self):
        runtime = self.setup_runtime()
        with self.assertRaises(UnverifiedMechanism):
            runtime.react(self.owner, self.packet(), self.inputs(sp_recovery_type=4))
        with self.assertRaises(UnverifiedMechanism):
            runtime.react(self.owner, self.packet(), self.inputs(native_default_no_hotfix=False))
        self.assertEqual(self.calls, [])

    def test_shared_flags_and_small_value_reject(self):
        self.setup_runtime()
        packet = self.packet()
        packet.value = FP.from_raw(42949)
        with self.assertRaises(ValueError):
            packet.validate()
        packet.value = FP.from_int32(500)
        packet.shared_flags = 0x80
        with self.assertRaises(ValueError):
            packet.validate()


if __name__ == "__main__":
    unittest.main()

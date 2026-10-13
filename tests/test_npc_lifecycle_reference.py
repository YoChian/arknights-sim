"""Independent C# translated native branch comparisons, not client traces."""
import json
from pathlib import Path
import unittest
from dataclasses import replace

from arknights_probe.npc_actions import EntityPtr,NpcEntity
from arknights_probe.npc_lifecycle import EnemyFinishOptions,SchedulerCounters
from tests.test_npc_lifecycle import Fixture,actor

ROOT=Path(__file__).resolve().parents[1]/'evidence/npc_lifecycle'


class NpcLifecycleReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.input=json.loads((ROOT/'reference_input.json').read_text('utf-8'))
        cls.output=json.loads((ROOT/'reference_vectors.json').read_text('utf-8'))

    def test_all_option_flags_and_decoded_int32_counter_branches(self):
        expected={r['id']:r for r in self.output['accounting']}
        self.assertEqual(len(expected),640)
        for row in self.input['accounting']:
            with self.subTest(case=row['id']):
                f,a=Fixture(),actor()
                a.options=EnemyFinishOptions(row['unharmful'],row['always_count'],row['dont_count'],row['is_summon'],11,False)
                a.finish_reason=row['reason'];a.is_invalid_killed=row['invalid']
                a.is_override_kill_count=row['is_override'];a.override_kill_count=row['override_count']
                f.ledger.counters=SchedulerCounters(*row['counters'],'independent input fixture')
                f.ledger.on_unit_finished(a)
                c=f.ledger.counters
                self.assertEqual([c.finished,c.killed,c.valid_finished,c.valid_killed,c.valid_missed],expected[row['id']]['counters'])

    def test_finish_and_recycle_control_flow_frames_and_uid_order(self):
        expected={r['id']:r for r in self.output['lifetime']}
        self.assertEqual(len(expected),96)
        for row in self.input['lifetime']:
            with self.subTest(case=row['id']):
                f=Fixture(row['recycle_flag'],row['animation_found'],row['animation_length'] if row['animation_found'] else None)
                a=actor(recycle_delay=row['delay'],ground_bound_exists=row['ground'],is_dummy=row['dummy'],use_specific_dead_animation=row['specific'])
                a.options=replace(a.options,unharmful=row['unharmful'])
                a.coroutine_owner.active_in_hierarchy=row['owner_available']
                f.ledger.attach(a,managed_by_scheduler=True,dont_block_wave=row['dont_block'])
                source=NpcEntity('source',23,True,True) if row['source_exists'] else None
                f.runtime.finish(a,row['reason'],finish_source=EntityPtr.capture(source))
                for _ in range(32):f.tick()
                r=expected[row['id']]
                actual=[[x['stage'],x['frame'],x['uid']] for x in f.runtime.events]
                self.assertEqual(actual,r['stages'])
                self.assertEqual(a.recycled,r['recycled'])
                self.assertEqual(a.identity.uid,r['uid'])
                self.assertEqual(len(f.ledger.wave),r['wave'])
                self.assertEqual(len(f.ledger.final),r['final'])
                self.assertEqual(f.ledger.counters.valid_missed,r['valid_missed'])


if __name__=='__main__':unittest.main()

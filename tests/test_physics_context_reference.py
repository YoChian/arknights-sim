"""Separate C# scalar translation comparisons; not a Unity/client oracle."""
from pathlib import Path
import json
import struct
import unittest

from arknights_probe.physics_context import (PhysicsEpoch,UnityBoundsSnapshot,plan_box_overlap,
    radius_from_transformed_vector,legacy_filter_initial_bytes,battle_physics_phases,UnverifiedPhysicsContext)

ROOT=Path(__file__).resolve().parents[1]/"evidence"/"physics_context"


def vector(value):
    return tuple(struct.unpack('<f',struct.pack('<I',int(x,16)))[0] for x in value)


def bits(value):
    return f"0x{struct.unpack('<I',struct.pack('<f',value))[0]:08x}"


class PhysicsContextReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.input=json.loads((ROOT/"reference_input.json").read_text('utf-8'))
        cls.output=json.loads((ROOT/"reference_vectors.json").read_text('utf-8'))

    def test_bounds_two_getters_and_area_to_box_exact_single_bits(self):
        expected={x['id']:x for x in self.output['boxes']}
        self.assertEqual(len(expected),300)
        epoch=PhysicsEpoch(0,'objects_fixed',0,0,2,True,True,True,'explicit reference fixture')
        for row in self.input['boxes']:
            r=expected[row['id']]
            a=UnityBoundsSnapshot('box',vector(row['minimum_center']),vector(row['minimum_extents']),epoch,'min getter fixture','UnityEngine.BoxCollider2D')
            b=UnityBoundsSnapshot('box',vector(row['maximum_center']),vector(row['maximum_extents']),epoch,'max getter fixture','UnityEngine.BoxCollider2D')
            with self.subTest(case=row['id']):
                if not r['finite_scope']:
                    with self.assertRaises(UnverifiedPhysicsContext):plan_box_overlap(a,b,layer_mask=512,source='finite component scope')
                    continue
                self.assertEqual([bits(x) for x in a.minimum()],r['minimum'])
                self.assertEqual([bits(x) for x in b.maximum()],r['maximum'])
                p=plan_box_overlap(a,b,layer_mask=512,source='native scalar reference')
                actual=p.as_dict()['argument_bits']
                self.assertEqual(actual['boxCenter'],r['box_center'])
                self.assertEqual(actual['boxSize'],r['box_size'])
                self.assertEqual(actual['angle'],[r['angle']])

    def test_transformed_radius_scalar_magnitude_bits_and_finite_gate(self):
        expected={x['id']:x for x in self.output['radii']}
        self.assertEqual(len(expected),200)
        for row in self.input['radii']:
            r=expected[row['id']]
            with self.subTest(case=row['id']):
                if not r['finite_scope']:
                    with self.assertRaises(UnverifiedPhysicsContext):radius_from_transformed_vector(vector(row['transformed_radius_vector']))
                else:self.assertEqual(bits(radius_from_transformed_vector(vector(row['transformed_radius_vector']))),r['radius'])

    def test_pre_consistency_filter_payload_bits(self):
        expected={x['id']:x for x in self.output['filters']}
        self.assertEqual(len(expected),30)
        for row in self.input['filters']:
            with self.subTest(case=row['id']):
                self.assertEqual(legacy_filter_initial_bytes(row['layer_mask'],row['queries_hit_triggers']).hex(),expected[row['id']]['initial_filter_hex'])

    def test_facade_mode_branch_reference(self):
        self.assertEqual(len(self.output['simulation_modes']),3)
        for mode,automatic,manual in self.output['simulation_modes']:
            phases=battle_physics_phases(simulation_mode=mode,hotfixes_absent=True,source='explicit mode fixture')
            self.assertEqual(int('manual_simulate' in phases),manual)
            self.assertEqual(int('manual_simulate' not in phases),automatic)


if __name__=='__main__':unittest.main()

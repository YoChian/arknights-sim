from copy import deepcopy
import json
import unittest

from arknights_probe import LegacyRandom
from arknights_probe.legacy_random import INT_MIN, INT_MAX, MBIG
from arknights_probe.rng_validation import verify_rng_reference


class LegacyRandomTests(unittest.TestCase):
    def test_independent_csharp_vectors_all_methods_and_seeds(self):
        report = verify_rng_reference()
        self.assertEqual(report["seed_count"], 8)
        self.assertEqual(report["checks"], {"next_integer_checks": 1024, "sample_binary64_checks": 128,
                                           "next_double_binary64_checks": 128, "bounded_integer_checks": 64,
                                           "range_integer_checks": 56, "range_consumption_checks": 8,
                                           "system_random_sequence_differences": 8})
        self.assertFalse(report["client_runtime_compared"])

    def test_seed_sign_symmetry_and_int32_boundary(self):
        for seed in (1, 42, 161803398, INT_MAX):
            positive, negative = LegacyRandom(seed), LegacyRandom(-seed)
            self.assertEqual([positive.next() for _ in range(120)], [negative.next() for _ in range(120)])
        self.assertEqual(LegacyRandom(INT_MIN).snapshot()["initial_seed"], INT_MIN)
        for invalid in (INT_MAX + 1, INT_MIN - 1, True, 1.0, None):
            with self.assertRaises(ValueError):
                LegacyRandom(invalid)

    def test_next_zero_consumes_but_unit_range_does_not(self):
        rng, reference = LegacyRandom(42), LegacyRandom(42)
        self.assertEqual(rng.next(0), 0)
        reference.sample()
        self.assertEqual(rng.snapshot(), reference.snapshot())
        before = rng.snapshot()
        self.assertEqual(rng.next_range(-8, -7), -8)
        self.assertEqual(rng.next_range(8, 8), 8)
        self.assertEqual(before, rng.snapshot())

    def test_invalid_boundaries_do_not_consume_state(self):
        rng = LegacyRandom(42)
        before = rng.snapshot()
        for bad in (-1, INT_MAX + 1, True, 2.5):
            with self.assertRaises(ValueError):
                rng.next(bad)
        for low, high in ((1, 0), (INT_MIN, INT_MAX), (INT_MIN, 0), (0, INT_MAX + 1)):
            with self.assertRaises(ValueError):
                rng.next_range(low, high)
        self.assertEqual(before, rng.snapshot())

    def test_snapshot_json_roundtrip_and_ring_wrap(self):
        rng = LegacyRandom(INT_MIN)
        for _ in range(55):
            rng.next_double()
        state = json.loads(json.dumps(rng.snapshot()))
        self.assertEqual(state["inext"], 55)
        self.assertEqual(state["inextp"], 31)
        restored = LegacyRandom.from_snapshot(state)
        expected = [rng.next() for _ in range(100)]
        self.assertEqual(expected, [restored.next() for _ in range(100)])
        rng.restore(state)
        self.assertEqual(expected, [rng.next() for _ in range(100)])

    def test_snapshot_detached_and_invalid_restore_atomic(self):
        rng = LegacyRandom(42)
        state = rng.snapshot()
        state["seed_array"][1] = 0
        self.assertNotEqual(state, rng.snapshot())
        before = rng.snapshot()
        for patch in ({"seed_array": [0] * 55}, {"inextp": 21}, {"sample_count": -1}, {"algorithm_id": "System.Random"}):
            bad = deepcopy(before)
            bad.update(patch)
            with self.assertRaises(ValueError):
                rng.restore(bad)
            self.assertEqual(before, rng.snapshot())

    def test_no_mbig_decrement_branch_and_offset31(self):
        # Synthetic valid-format state exercises a branch absent from native
        # Sample. It does not claim this state is reached by any client seed.
        rng = LegacyRandom(0)
        state = rng.snapshot()
        self.assertEqual(state["inextp"], 31)
        state["seed_array"] = [0] * 56
        state["seed_array"][1] = MBIG
        rng.restore(state)
        self.assertEqual(rng.sample(), 1.0)
        self.assertEqual(rng.snapshot()["seed_array"][1], MBIG)


if __name__ == "__main__":
    unittest.main()

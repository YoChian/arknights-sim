from pathlib import Path
import unittest

from arknights_probe import Dataset, DataError, LegacyRandom
from arknights_probe.fp import binary32
from arknights_probe.preprocess import EPSILON, random_range_float, rogue_preprocess, weighted_choice

ROOT = Path(__file__).resolve().parents[1]


class Draws:
    def __init__(self, *values):
        self.values = iter(values)
        self.calls = 0
    def next_double(self):
        self.calls += 1
        return next(self.values)


class PreprocessTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(ROOT / "data/manifest.json")

    def process(self, rng, **kwargs):
        options = {"rng": rng, "topic_id": "rogue_6", "mimic_count": -1, "gold_count": -1,
                   "group_order": ["t1", "t2", "c1"], "input_source": "independent_explicit_test_inputs"}
        options.update(kwargs)
        return rogue_preprocess(self.dataset, **options)

    def test_weight_threshold_epsilon_and_zero_weight_draw(self):
        a, b = {"weight": 1, "name": "a"}, {"weight": 1, "name": "b"}
        self.assertIs(weighted_choice([a, b], Draws((1 + EPSILON / 2) / 2)), a)
        self.assertIs(weighted_choice([a, b], Draws((1 + EPSILON * 2) / 2)), b)
        zero = {"weight": 0}
        rng = Draws(.75)
        self.assertIs(weighted_choice([zero, zero], rng), zero)
        self.assertEqual(rng.calls, 1)
        empty_rng = Draws(.5)
        self.assertIsNone(weighted_choice([], empty_rng))
        self.assertEqual(empty_rng.calls, 1)  # standalone helper, caller avoids empty

    def test_float_range_rounds_sample_multiply_and_add(self):
        sample = .1234567890123456
        minimum, maximum = binary32(1e6), binary32(1e6 + 7)
        expected = binary32(binary32(binary32(sample) * binary32(maximum - minimum)) + minimum)
        self.assertEqual(random_range_float(Draws(sample), minimum, maximum), expected)

    def test_empty_choice_and_explicit_original_indices(self):
        rng = Draws(0, 0, .99)
        result = self.process(rng)
        self.assertEqual(result["group_selections"], {"t1": 0, "t2": 5, "c1": 4})
        self.assertEqual(result["next_double_calls"], 3)
        self.assertFalse(result["client_rng_consumption_validated"])
        self.assertFalse(result["battle_ready"])

    def test_preserve_zero_filters_mimics_but_keeps_empty(self):
        result = self.process(Draws(.95, .95, .5), mimic_count=0, gold_count=0)
        self.assertEqual(result["eligible_original_indices"]["c1"], [4])
        self.assertEqual(result["group_selections"]["c1"], 4)
        self.assertEqual(result["selected_gold_groups"], [])
        self.assertEqual(result["next_double_calls"], 3)

    def test_preserve_mimic_group_does_not_guarantee_mimic_spawn(self):
        # First draw chooses the sole mimic-containing group. EMPTY remains.
        result = self.process(Draws(.5, 0, 0, .99), mimic_count=1, gold_count=0)
        self.assertEqual(result["selected_mimic_groups"], ["c1"])
        self.assertEqual(result["eligible_original_indices"]["c1"], [0, 1, 2, 3, 4])
        self.assertEqual(result["group_selections"]["c1"], 4)
        self.assertEqual(result["next_double_calls"], 4)

    def test_negative_either_counter_uses_ordinary_mode(self):
        result = self.process(Draws(0, 0, 0), mimic_count=-1, gold_count=0)
        self.assertFalse(result["preserve_mode"])
        self.assertEqual(result["group_selections"]["c1"], 0)

    def test_seed_repeatability_is_independent_not_client_run(self):
        left = self.process(LegacyRandom(42), mimic_count=0, gold_count=0)
        right = self.process(LegacyRandom(42), mimic_count=0, gold_count=0)
        self.assertEqual(left, right)
        for order in (["t1", "c1"], ["t1", "t1", "c1"], ["t1", "t2", "c1", "unknown"]):
            with self.assertRaises(DataError):
                self.process(LegacyRandom(42), group_order=order)


if __name__ == "__main__":
    unittest.main()

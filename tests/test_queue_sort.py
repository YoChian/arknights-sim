import unittest
from arknights_probe.queue_sort import native_queue_sort, single_compare_to
from arknights_probe.sort_validation import verify_sort_reference


class QueueSortTests(unittest.TestCase):
    def test_independent_csharp_reference_exact_identity_order(self):
        result = verify_sort_reference()
        self.assertEqual(result["case_count"], 152)
        self.assertEqual(result["identity_checks"], 5616)
        self.assertEqual(result["single_compare_to_checks"], 81)
        self.assertEqual(result["host_list_sort_different_cases"], 56)
        self.assertFalse(result["client_runtime_compared"])
    def test_equal_keys_exchange_and_input_identity(self):
        for size, expected in [(2, [1, 0]), (3, [2, 1, 0]), (4, [2, 3, 0, 1])]:
            items = [{"id": i, "time": 0} for i in range(size)]
            result = native_queue_sort(items, key=lambda x: x["time"])
            self.assertEqual([x["id"] for x in result], expected)
            self.assertEqual([x["id"] for x in items], list(range(size)))
            self.assertTrue(all(x is items[x["id"]] for x in result))

    def test_single_nan_and_signed_zero_order(self):
        nan = float("nan")
        self.assertEqual(single_compare_to(nan, nan), 0)
        self.assertEqual(single_compare_to(nan, 0), -1)
        self.assertEqual(single_compare_to(0, nan), 1)
        self.assertEqual(single_compare_to(-0., 0.), 0)

    def test_large_queue_and_rounded_float_keys(self):
        items = [{"id": i, "time": (200 - i) % 23} for i in range(201)]
        result = native_queue_sort(items, key=lambda x: x["time"])
        self.assertEqual([x["time"] for x in result], sorted(x["time"] for x in items))
        self.assertEqual(sorted(x["id"] for x in result), list(range(201)))
        self.assertEqual([x["id"] for x in native_queue_sort([{"id": 0, "time": 1}, {"id": 1, "time": 1 + 1e-9}], key=lambda x: x["time"])], [1, 0])


if __name__ == "__main__":
    unittest.main()

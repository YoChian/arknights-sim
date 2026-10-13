"""Independent translated C# rules; not a running native/client oracle."""
import json
from pathlib import Path
import unittest

from arknights_probe.fp import FP
from arknights_probe.targeting_runtime import (weighted_target_compare,order_created_targets,
    AbnormalStatus,convert_target_side,side_layer_mask)


ROOT=Path(__file__).resolve().parents[1]/"evidence"/"targeting_runtime"


class TargetingRuntimeReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.input=json.loads((ROOT/"reference_input.json").read_text("utf-8"))
        cls.vectors=json.loads((ROOT/"reference_vectors.json").read_text("utf-8"))

    def test_comparator_integer_fraction_bins_threshold_epsilon_extremes(self):
        expected={x["id"]:x["comparison"] for x in self.vectors["comparisons"]}
        self.assertEqual(len(expected),1500)
        for row in self.input["comparisons"]:
            with self.subTest(case=row["id"]):
                result=weighted_target_compare(row["uid"],FP.from_raw(int(row["raw"])),
                    row["other_uid"],FP.from_raw(int(row["other_raw"])))
                self.assertEqual(result,expected[row["id"]])

    def test_queue_reference_order_and_rechecked_membership(self):
        expected={x["id"]:x for x in self.vectors["queues"]}
        self.assertEqual(len(expected),120)
        for row in self.input["queues"]:
            alive=tuple((x["uid"],FP.from_raw(int(x["raw"]))) for x in row["items"] if x["alive"])
            with self.subTest(case=row["id"]):
                self.assertEqual(list(order_created_targets(alive,is_sandbox=False,hotfixes_absent=True,
                    source="explicit C# queue fixture")),expected[row["id"]]["order"])
                self.assertEqual([x["uid"] for x in row["items"] if x["alive"]],expected[row["id"]]["kept"])
                self.assertEqual([x["uid"] for x in row["items"] if not x["alive"]],expected[row["id"]]["dropped"])

    def test_abnormal_signed_counts_base_fallback_and_immune_reference(self):
        expected={x["id"]:x for x in self.vectors["statuses"]}
        self.assertEqual(len(expected),400)
        for row in self.input["statuses"]:
            state=AbnormalStatus({row["flag"]:row["active"]},{row["flag"]:row["immune"]},
                int(row["base_bits"]),"explicit raw counter/bit fixture")
            with self.subTest(case=row["id"]):
                self.assertEqual(state.flag(row["flag"]),expected[row["id"]]["flag"])
                self.assertEqual(state.immune(row["flag"]),expected[row["id"]]["immune"])

    def test_all_side_combinations_and_actual_layers_reference(self):
        self.assertEqual(len(self.vectors["masks"]),64)
        for side,target,absolute,mask in self.vectors["masks"]:
            with self.subTest(side=side,target=target):
                self.assertEqual(convert_target_side(side,target),absolute)
                self.assertEqual(side_layer_mask(absolute),mask)


if __name__=="__main__":unittest.main()

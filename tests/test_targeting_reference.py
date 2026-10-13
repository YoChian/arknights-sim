"""Source-owned C# translation checks; Unity/native ALL are external inputs."""
import json
from pathlib import Path
import struct
import unittest

from arknights_probe.targeting import (construct_range_boxes, TargetSnapshot,
    ColliderOverlapSnapshot, OverlapQuerySnapshot, AltarSelectorContext,
    PredicateSnapshot, AllPostFilterSnapshot, select_altar_targets)


EVIDENCE = Path(__file__).resolve().parents[1] / "evidence" / "targeting"


def bits(value):
    return struct.unpack("<i",struct.pack("<f",value))[0]


class TargetingReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.inputs=json.loads((EVIDENCE/"reference_input.json").read_text("utf-8"))
        cls.vectors=json.loads((EVIDENCE/"reference_vectors.json").read_text("utf-8"))

    def test_independent_csharp_bounded_grid_to_collider_values_and_order(self):
        expected={x["id"]:x["box_bits"] for x in self.vectors["geometry"]}
        self.assertEqual(len(expected),148)
        for case in self.inputs["geometry"]:
            with self.subTest(case=case["id"]):
                boxes=construct_range_boxes(case["grids"],direction=case["direction"])
                actual=[[bits(v) for v in [b.minimum.x,b.minimum.y,b.size.x,b.size.y,b.center.x,b.center.y]] for b in boxes]
                self.assertEqual(actual,expected[case["id"]])

    def test_independent_csharp_admission_dedup_cap_and_uint32_order(self):
        expected={x["id"]:x for x in self.vectors["collectors"]}
        self.assertEqual(len(expected),112)
        for case in self.inputs["collectors"]:
            states={t["uid"]:t for c in case["colliders"] for t in c["hits"] if t is not None}
            colliders=[]
            for c in case["colliders"]:
                hits=tuple(None if t is None else TargetSnapshot(
                    **{k:t[k] for k in ["uid","side","motion","category","map_layer","alive","destroyed",
                                       "ally_target_free","heal_free","camouflage"]},
                    source="explicit C# reference frozen entity fixture") for t in c["hits"])
                colliders.append(ColliderOverlapSnapshot(hits,c["destroyed"],"external Physics2D fixture, not engine output"))
            raw=case["context"]
            ctx=AltarSelectorContext(**raw,absolute_target_side_mask=7,query_layer_mask=123,
                collider_count=len(colliders),
                hit_range=PredicateSnapshot({u:t["hit_range"] for u,t in states.items()},"fixture HitRange provider"),
                custom_validator=PredicateSnapshot({u:t["custom_validator"] for u,t in states.items()},"fixture custom validator")
                    if raw["has_custom_validator"] else None,
                excluded_uids=frozenset(u for u,t in states.items() if t["excluded"]),
                source="explicit source/masks/status fixture")
            ref=expected[case["id"]]
            # Reversal is a supplied permutation, not a reconstructed ALL comparator.
            post=AllPostFilterSnapshot(tuple(ref["collector"]),tuple(ref["fixture_all_output"]),
                "explicit reversed ALL permutation fixture; client ordering unclaimed")
            with self.subTest(case=case["id"]):
                actual=select_altar_targets(OverlapQuerySnapshot(tuple(colliders),123,"external query fixture"),ctx,post)
                self.assertEqual(list(actual.collector_uids),ref["collector"])
                self.assertEqual([t.uid for t in actual.hits],ref["fixture_all_output"])
                self.assertEqual(actual.capped,ref["capped"])
                self.assertEqual([[d["collider_index"],d["hit_index"],d["uid"],d["reason"]] for d in actual.decisions],ref["decisions"])


if __name__ == "__main__":
    unittest.main()

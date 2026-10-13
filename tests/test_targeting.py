import unittest
from dataclasses import replace
import struct

from arknights_probe.movement import LocalVector2 as V
from arknights_probe.targeting import (construct_range_boxes, rotate_range_grid,
    SourceMotionSnapshot, resolve_source_motion, UnverifiedTargetContext,
    WorldBounds2D, TargetSnapshot, ColliderOverlapSnapshot, OverlapQuerySnapshot,
    PredicateSnapshot, AltarSelectorContext, AllPostFilterSnapshot, select_altar_targets)


def entity(uid, **changes):
    initial = TargetSnapshot(uid=uid, side=2, motion=0, category=1, map_layer=0,
        alive=True, destroyed=False, ally_target_free=None, heal_free=None,
        camouflage=False, source="explicit frozen entity fixture")
    return replace(initial, **changes)


def context(uids, **changes):
    initial = AltarSelectorContext(source_side=4, source_map_layer=0, source_purpose_mask=1,
        absolute_target_side_mask=7, query_layer_mask=123, collider_count=1,
        opposite_side_mask=3, ability_ignores_camouflage=False, deterministic=True,
        hit_range=PredicateSnapshot({uid: True for uid in uids}, "explicit provider outcomes"),
        has_custom_validator=False, custom_validator=None, excluded_uids=frozenset(),
        source="fixture: sktok_ore native prefab branch, owner/masks supplied")
    return replace(initial, **changes)


def query(*groups, layer_mask=123):
    return OverlapQuerySnapshot(tuple(ColliderOverlapSnapshot(tuple(group), False,
        "external Physics2D-to-Entity overlap order fixture") for group in groups), layer_mask,
        "external Physics2D query fixture; engine behavior not evaluated")


def order(collector, final=None):
    return AllPostFilterSnapshot(tuple(collector), tuple(collector if final is None else final),
        "explicit ALL output fixture; native SortedSet order not claimed")


class TargetingGeometryTests(unittest.TestCase):
    def test_real_thirteen_grid_declaration_is_three_overlapping_colliders(self):
        grids = [(2,0),(1,-1),(1,0),(1,1),(0,-2),(0,-1),(0,0),(0,1),(0,2),(-1,-1),(-1,0),(-1,1),(-2,0)]
        boxes = construct_range_boxes(grids, direction=1)
        self.assertEqual([(b.minimum, b.size) for b in boxes],
            [(V(-.5,-2.5), V(1,5)), (V(-1.5,-1.5), V(3,3)), (V(-2.5,-.5), V(5,1))])
        self.assertEqual([b.center for b in boxes], [V(0,0)] * 3)
        self.assertGreater(sum(b.size.x*b.size.y for b in boxes), len(grids))

    def test_native_growth_uses_all_set_not_only_uncovered_cells(self):
        boxes = construct_range_boxes([(0,0),(0,1),(1,0),(1,1),(1,2)], direction=0)
        self.assertEqual([(b.minimum, b.size) for b in boxes],
            [(V(-.5,-.5),V(2,2)), (V(1.5,.5),V(1,1))])
        cross = construct_range_boxes([(0,1),(1,0),(1,1),(1,2),(2,1)], direction=0)
        self.assertEqual([(b.minimum,b.size) for b in cross],
            [(V(.5,-.5),V(1,3)), (V(-.5,.5),V(3,1))])

    def test_signed_row_column_sort_and_duplicate_declarations(self):
        a = construct_range_boxes([(0,0),(2,2),(0,0),(-2,-3)], direction=0)
        b = construct_range_boxes([(-2,-3),(0,0),(2,2)], direction=0)
        self.assertEqual(a,b)
        self.assertEqual(a[0].minimum, V(-3.5,-2.5))
        self.assertEqual(construct_range_boxes([], direction=0), ())

    def test_current_to_target_quarter_turns_and_bounds(self):
        self.assertEqual(rotate_range_grid((2,3),1,0),(3,-2))
        self.assertEqual(rotate_range_grid((2,3),0,1),(-3,2))
        self.assertEqual(rotate_range_grid((2,3),0,2),(-2,-3))
        with self.assertRaises(UnverifiedTargetContext):
            rotate_range_grid((2,3),4)
        with self.assertRaises(UnverifiedTargetContext):
            construct_range_boxes([(0,2**31-1)],direction=0)

    def test_snapshot_fallback_retains_captured_motion(self):
        snap = SourceMotionSnapshot(0)
        self.assertEqual(resolve_source_motion(reference_valid=True,current_motion=1,captured=snap),(True,1))
        self.assertEqual(resolve_source_motion(reference_valid=False,current_motion=None,captured=snap),(True,0))
        self.assertEqual(resolve_source_motion(reference_valid=False,current_motion=None,captured=None),(False,2))
        with self.assertRaises(UnverifiedTargetContext):
            resolve_source_motion(reference_valid=True,current_motion=None,captured=snap)

    def test_world_bounds_edges_are_inclusive_without_implicit_epsilon(self):
        bounds = WorldBounds2D(V(-.5,-1.5), V(.5,1.5), "explicit native world SafeBounds fixture")
        self.assertTrue(bounds.contains(V(.5,1.5)))
        above_half = struct.unpack("<f", struct.pack("<I", 0x3f000001))[0]
        self.assertFalse(bounds.contains(V(above_half,1.5)))
        self.assertFalse(bounds.contains(V(-.5,-1.5001)))


class TargetingAdmissionTests(unittest.TestCase):
    def test_single_laxe_scope_returns_explicit_order_and_sources(self):
        result = select_altar_targets(query([entity(2)]),context([2]),order([2]))
        self.assertEqual([t.uid for t in result.hits],[2])
        info = result.as_dict()
        self.assertFalse(info["physics_overlap_generated"])
        self.assertFalse(info["native_all_order_generated"])
        self.assertFalse(info["battle_ready"])
        self.assertIn("external Physics2D",info["query_source"])
        self.assertEqual(info["decisions"][0]["reason"],"admitted")

    def test_collector_uid_sort_is_unsigned_then_external_all_order_applies(self):
        uids = [0xffffffff, 2, 0x80000000, 1]
        collector = [1,2,0x80000000,0xffffffff]
        result = select_altar_targets(query([entity(u) for u in uids]), context(uids), order(collector,uids))
        self.assertEqual(result.collector_uids,tuple(collector))
        self.assertEqual([t.uid for t in result.hits],uids)

    def test_uint32_boundaries_reject_signed_or_bool_uid(self):
        for value in [-1,2**32,True]:
            with self.subTest(value=value), self.assertRaises(UnverifiedTargetContext):
                entity(value)

    def test_native_limit_happens_before_deterministic_uid_sort(self):
        uids = list(range(200,0,-1))
        collector = list(range(73,201))
        result = select_altar_targets(query([entity(u) for u in uids]),context(uids),order(collector))
        self.assertEqual(result.collector_uids,tuple(collector))
        self.assertTrue(result.capped)
        self.assertEqual(len(result.decisions),128)
        self.assertNotIn(1,result.collector_uids)

    def test_nondeterministic_collector_preserves_supplied_engine_order(self):
        result = select_altar_targets(query([entity(9),entity(2)]), context([9,2],deterministic=False), order([9,2]))
        self.assertEqual(result.collector_uids,(9,2))

    def test_uid_dedup_runs_after_admission_across_overlapping_range_boxes(self):
        first, rejected = entity(4), entity(9)
        ctx = context([4,9],collider_count=2,
            hit_range=PredicateSnapshot({4:True,9:False},"known native provider outcomes"))
        result = select_altar_targets(query([rejected,first],[first,rejected]),ctx,order([4]))
        self.assertEqual([d["reason"] for d in result.decisions],
            ["hit_range_provider","admitted","duplicate_admitted_uid","hit_range_provider"])

    def test_null_destroyed_invalid_uid_and_dead_do_not_request_later_gates(self):
        targets = [None,entity(2,destroyed=True,alive=None),entity(0,alive=None),entity(3,alive=False)]
        result = select_altar_targets(query(targets),context([]),order([]))
        self.assertEqual([d["reason"] for d in result.decisions],
            ["collider_has_no_live_entity","entity_destroyed","instance_uid_invalid","entity_not_alive"])

    def test_default_category_and_motion_masks_use_native_results(self):
        result = select_altar_targets(query([entity(2,category=2),entity(3,motion=2),entity(4,category=3,motion=1)]),
            context([4]),order([4]))
        self.assertEqual([d["reason"] for d in result.decisions],["category_mask","motion_mask","admitted"])

    def test_collector_does_not_reapply_entity_side_after_layer_query(self):
        result = select_altar_targets(query([entity(2,side=4,ally_target_free=False)]),
            context([2],absolute_target_side_mask=3),order([2]))
        self.assertEqual(result.collector_uids,(2,))

    def test_native_source_side_and_purpose_predicates_are_conditional(self):
        result = select_altar_targets(query([entity(2,side=4,ally_target_free=True),entity(3,heal_free=True)]),
            context([2,3],source_purpose_mask=3),order([]))
        self.assertEqual([d["reason"] for d in result.decisions],["ally_target_free","heal_free"])
        with self.assertRaisesRegex(UnverifiedTargetContext,"isAllyTargetFree"):
            select_altar_targets(query([entity(2,side=4)]),context([2]),order([2]))
        with self.assertRaisesRegex(UnverifiedTargetContext,"isHealFree"):
            select_altar_targets(query([entity(2)]),context([2],source_purpose_mask=2),order([2]))

    def test_map_layer_gate_precedes_unknown_hit_range_and_camouflage(self):
        result = select_altar_targets(query([entity(2,map_layer=1,camouflage=None)]),context([]),order([]))
        self.assertEqual(result.decisions[0]["reason"],"map_layer")
        with self.assertRaisesRegex(UnverifiedTargetContext,"IsInHitRange"):
            select_altar_targets(query([entity(2)]),context([]),order([2]))

    def test_camouflage_filters_opponents_only_and_ability_flag_can_bypass(self):
        result = select_altar_targets(query([entity(2,camouflage=True),entity(3,side=1,camouflage=True,ally_target_free=False)]),
            context([2,3],source_side=1,opposite_side_mask=2),order([3]))
        self.assertEqual([d["reason"] for d in result.decisions],["enemy_camouflage","admitted"])
        result = select_altar_targets(query([entity(2,camouflage=None)]),
            context([2],ability_ignores_camouflage=True),order([2]))
        self.assertEqual(result.collector_uids,(2,))

    def test_custom_validator_then_exclusion_set(self):
        ctx = context([2,3],has_custom_validator=True,
            custom_validator=PredicateSnapshot({2:False,3:True},"explicit registered validator outcomes"),excluded_uids=frozenset([3]))
        result = select_altar_targets(query([entity(2),entity(3)]),ctx,order([]))
        self.assertEqual([d["reason"] for d in result.decisions],["custom_validator","advanced_exclusion_set"])
        with self.assertRaises(UnverifiedTargetContext):
            context([2],has_custom_validator=True)

    def test_external_predicate_snapshot_copies_mapping(self):
        values = {2:True}
        gate = PredicateSnapshot(values,"immutable fixture snapshot")
        values[2] = False
        self.assertTrue(gate.resolve(2,"provider"))

    def test_layer_mask_and_all_colliders_must_match_query_context(self):
        for q in [query([entity(2)],layer_mask=0),query([entity(2)],[])] :
            with self.assertRaises(UnverifiedTargetContext):
                select_altar_targets(q,context([2]),order([2]))

    def test_unknown_or_mismatched_all_order_fails_closed(self):
        q, ctx = query([entity(2),entity(3)]),context([2,3])
        for snapshot in [None,order([3,2]),order([2,3],[2]),order([2,3],[2,2]),order([2,3],[2,9])]:
            with self.subTest(snapshot=snapshot), self.assertRaises(UnverifiedTargetContext):
                select_altar_targets(q,ctx,snapshot)

    def test_conflicting_states_for_one_uid_reject_mutable_context(self):
        with self.assertRaisesRegex(UnverifiedTargetContext,"conflicting mutable"):
            select_altar_targets(query([entity(2),entity(2,alive=False)]),context([2]),order([2]))


if __name__ == "__main__":
    unittest.main()

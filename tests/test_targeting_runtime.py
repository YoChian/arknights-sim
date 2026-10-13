import unittest
from dataclasses import replace

from arknights_probe.fp import FP
from arknights_probe.targeting import (TargetSnapshot,PredicateSnapshot,
    ColliderOverlapSnapshot,OverlapQuerySnapshot,UnverifiedTargetContext)
from arknights_probe.targeting_runtime import (RuntimeAltarContext,RuntimeTargetData,
    AbnormalStatus,HitRangeManager,select_altar_targets_runtime,weighted_target_compare,
    order_created_targets,convert_target_side,same_side_mask,opposite_side_mask,
    side_layer_mask,SMALL_GAP,BIG_GAP)


def target(uid,**changes):
    t=TargetSnapshot(uid,2,0,1,0,True,False,None,None,None,"explicit core field fixture")
    return replace(t,**changes)


def context(**changes):
    c=RuntimeAltarContext(2,0,3,True,False,None,frozenset(),True,
        "actual prefab source2 + explicit normal/no-hotfix native context fixture")
    return replace(c,**changes)


def data(**changes):
    d=RuntimeTargetData(FP.from_raw(0),AbnormalStatus.zeroed_prepared_fixture("explicit zero counters/base fixture"),
        HitRangeManager((),"explicit empty native provider dictionary fixture"),"explicit createdTime raw0 native field")
    return replace(d,**changes)


def query(groups,ctx):
    return OverlapQuerySnapshot(tuple(ColliderOverlapSnapshot(tuple(g),False,"external ordered Physics2D fixture") for g in groups),
        ctx.query_layer_mask,"external overlap results, derived mask, no geometry generated")


class RuntimeTargetInputsTests(unittest.TestCase):
    def test_actual_source_mask_and_purpose_do_not_use_old_fixture_123_or_ability_purpose(self):
        c=context()
        self.assertEqual((c.source_side,c.absolute_target_side_mask,c.query_layer_mask,c.source_purpose_mask),
                         (2,7,0x10000600,0))
        self.assertEqual(side_layer_mask(1),1024)
        self.assertEqual(side_layer_mask(2),512)
        self.assertEqual(side_layer_mask(4),1<<28)

    def test_side_arrays_native_asymmetry_and_exact_single_bit_match(self):
        self.assertEqual([same_side_mask(x) for x in [1,2,4]],[1,2,4])
        self.assertEqual([opposite_side_mask(x) for x in [1,2,4]],[2,5,2])
        self.assertEqual(convert_target_side(4,3),6)
        self.assertEqual(convert_target_side(0,3),3)
        self.assertEqual(convert_target_side(3,3),3)
        self.assertEqual(convert_target_side(1,4),7)
        for composite in (3,5,6,7):
            self.assertEqual(same_side_mask(composite),composite)
            self.assertEqual(opposite_side_mask(composite),0)
            self.assertEqual(convert_target_side(composite,3),composite)

    def test_native_flag_dynamic_immune_then_base_mask_fallback(self):
        a=AbnormalStatus({17:1},{17:0,9:0},0,"explicit counts")
        self.assertTrue(a.camouflage)
        self.assertFalse(replace(a,immune_counts={17:1,9:0}).flag(17))
        self.assertTrue(replace(a,immune_counts={17:1,9:0},base_flags=1<<17).flag(17))
        self.assertFalse(replace(a,immune_counts={17:0,9:1}).camouflage)
        self.assertTrue(replace(a,immune_counts={17:-1,9:-1}).camouflage)

    def test_signed_count_bounds_and_unknown_are_not_zero(self):
        with self.assertRaises(UnverifiedTargetContext):
            AbnormalStatus({17:32768},{17:0},0,"outside native Int16")
        with self.assertRaises(UnverifiedTargetContext):
            AbnormalStatus({}, {},0,"missing count").flag(17)
        self.assertFalse(AbnormalStatus({17:-32768},{17:32767},0,"boundary counts").flag(17))
        self.assertFalse(AbnormalStatus({}, {63:1},1<<63,"native SETG high-bit fallback").flag(63))

    def test_counter_mapping_is_copied(self):
        active={17:0};immune={17:0}
        a=AbnormalStatus(active,immune,0,"frozen native counts")
        active[17]=1
        self.assertFalse(a.flag(17))

    def test_empty_and_null_provider_registry_pass_without_external_bool(self):
        self.assertTrue(HitRangeManager((),"empty initialized registry").is_in_hit_range(2))
        self.assertTrue(HitRangeManager((("null",None),),"registered null entry").is_in_hit_range(2))

    def test_provider_AND_and_unknown_follow_native_short_circuit(self):
        yes=PredicateSnapshot({2:True},"provider implementation fixture")
        no=PredicateSnapshot({2:False},"provider implementation fixture")
        unknown=PredicateSnapshot({},"unimplemented provider")
        self.assertFalse(HitRangeManager((("no",no),("unknown",unknown)),"ordered registry").is_in_hit_range(2))
        self.assertTrue(HitRangeManager((("a",yes),("b",yes)),"ordered registry").is_in_hit_range(2))
        with self.assertRaises(UnverifiedTargetContext):
            HitRangeManager((("unknown",unknown),("no",no)),"ordered registry").is_in_hit_range(2)

    def test_register_retains_non_null_and_replaces_null(self):
        yes=PredicateSnapshot({2:True},"first provider")
        no=PredicateSnapshot({2:False},"other provider")
        m=HitRangeManager((),"registration fixture").register("x",yes)
        self.assertIs(m.register("x",no),m)
        replaced=HitRangeManager((("x",None),),"null registration").register("x",no)
        self.assertFalse(replaced.is_in_hit_range(2))

    def test_sandbox_hotfixes_and_unlabelled_context_reject(self):
        for kw in [{"is_sandbox":True},{"hotfixes_absent":False},{"source":""}]:
            with self.assertRaises(UnverifiedTargetContext):context(**kw)


class RuntimeAllQueueTests(unittest.TestCase):
    def test_same_bin_uses_uid_not_raw_time(self):
        items=((9,FP.from_raw(0)),(2,FP.from_raw(SMALL_GAP.raw//2)))
        self.assertEqual(order_created_targets(items,is_sandbox=False,hotfixes_absent=True,source="native bin fixture"),(2,9))

    def test_adjacent_small_bins_preserve_weight_priority(self):
        self.assertLess(weighted_target_compare(9,FP.from_raw(SMALL_GAP.raw-1),2,SMALL_GAP),0)
        self.assertGreater(weighted_target_compare(9,SMALL_GAP,2,FP.from_raw(SMALL_GAP.raw-1)),0)

    def test_equal_created_time_unsigned_uid_order(self):
        items=((0xffffffff,FP.from_int32(5)),(2,FP.from_int32(5)),(0x80000000,FP.from_int32(5)))
        self.assertEqual(order_created_targets(items,is_sandbox=False,hotfixes_absent=True,source="same time fixture"),
                         (2,0x80000000,0xffffffff))

    def test_queue_keeps_equal_entries_inserts_before_not_set_dedup(self):
        items=((2,FP.from_raw(0)),(2,FP.from_raw(0)))
        self.assertEqual(order_created_targets(items,is_sandbox=False,hotfixes_absent=True,source="queue duplicate fixture"),(2,2))

    def test_large_integer_and_fractional_bins_and_threshold_boundary(self):
        large=FP.from_int32(1000001)
        self.assertLess(weighted_target_compare(9,large,2,FP.from_int32(1000002)),0)
        self.assertLess(weighted_target_compare(9,large,2,large+SMALL_GAP),0)
        self.assertGreater(weighted_target_compare(9,large,2,large+FP.from_raw(SMALL_GAP.raw//2)),0)
        # Exact/mixed threshold path leaves raw weights; EPSILON then ties one bit.
        self.assertGreater(weighted_target_compare(9,BIG_GAP-FP.from_raw(1),2,BIG_GAP),0)
        self.assertLess(weighted_target_compare(9,BIG_GAP-FP.from_raw(50000),2,BIG_GAP),0)


class RuntimeSelectionTests(unittest.TestCase):
    def test_single_laxe_three_external_overlaps_generate_ALL(self):
        t=target(2);c=context()
        r=select_altar_targets_runtime(query([[t],[t],[t]],c),c,{2:data()})
        self.assertEqual([x.uid for x in r.hits],[2])
        self.assertEqual([x["reason"] for x in r.decisions],["admitted","duplicate_admitted_uid","duplicate_admitted_uid"])
        info=r.as_dict()
        self.assertTrue(info["native_all_order_generated"])
        self.assertFalse(info["physics_overlap_generated"])
        self.assertFalse(info["battle_ready"])

    def test_status_booleans_are_computed_from_counts_not_external_getter_results(self):
        c=context();t=target(2,ally_target_free=True,heal_free=True,camouflage=True)
        r=select_altar_targets_runtime(query([[t],[],[]],c),c,{2:data()})
        self.assertEqual([x.uid for x in r.hits],[2])
        self.assertFalse(r.hits[0].ally_target_free)
        self.assertFalse(r.hits[0].camouflage)
        self.assertIsNone(r.hits[0].heal_free)  # native purpose0 never needs it

    def test_ALL_created_time_reorders_collector_and_member_can_disappear_at_recheck(self):
        c=context();a,b,d=target(1),target(2),target(3)
        values={1:data(created_time=FP.from_int32(20)),2:data(created_time=FP.from_int32(1)),
                3:data(postfilter_alive=False)}
        r=select_altar_targets_runtime(query([[a,b,d],[],[]],c),c,values)
        self.assertEqual(r.collector_uids,(1,2,3))
        self.assertEqual([x.uid for x in r.hits],[2,1])
        self.assertEqual(r.all_decisions[-1],{"uid":3,"reason":"not_alive_at_ALL"})

    def test_native_flags_same_side_ally_free_and_opponent_camouflage(self):
        c=context()
        blocked=data(attributes=AbnormalStatus({15:1},{15:0},0,"same-side immune input"))
        camouflage=data(attributes=AbnormalStatus({17:1},{17:0,9:0},0,"camo input"))
        r=select_altar_targets_runtime(query([[target(2),target(3,side=1)],[],[]],c),c,{2:blocked,3:camouflage})
        self.assertEqual([x["reason"] for x in r.decisions],["ally_target_free","enemy_camouflage"])
        self.assertEqual(r.hits,())

    def test_map_layer_and_provider_false_precede_unknown_camouflage_counts(self):
        c=context();unknown=AbnormalStatus({}, {},0,"unknown counters")
        denied=data(attributes=unknown,hit_range=HitRangeManager((("reject",PredicateSnapshot({2:False},"provider fixture")),),"registry"))
        # Different target side avoids same-side ally-free query.
        r=select_altar_targets_runtime(query([[target(2,side=1)],[],[]],c),c,{2:denied})
        self.assertEqual(r.decisions[0]["reason"],"hit_range_provider")
        r=select_altar_targets_runtime(query([[target(2,side=1,map_layer=3)],[],[]],c),c,{2:denied})
        self.assertEqual(r.decisions[0]["reason"],"map_layer")

    def test_query_mask_cache_count_missing_runtime_and_unknown_camouflage_fail(self):
        c=context();q=query([[target(2)],[],[]],c)
        for bad in [replace(q,layer_mask=123),replace(q,colliders=q.colliders[:1])]:
            with self.assertRaises(UnverifiedTargetContext):select_altar_targets_runtime(bad,c,{2:data()})
        with self.assertRaises(UnverifiedTargetContext):select_altar_targets_runtime(q,c,{})
        with self.assertRaises(UnverifiedTargetContext):
            select_altar_targets_runtime(q,c,{2:data(attributes=AbnormalStatus({15:0},{15:0},0,"camo unknown"))})

    def test_128_cap_before_sort_then_native_ALL_keeps_all_distinct_UIDs(self):
        c=context();uids=list(range(200,0,-1));ts=[target(u) for u in uids]
        r=select_altar_targets_runtime(query([ts,[],[]],c),c,{u:data() for u in uids})
        self.assertTrue(r.capped)
        self.assertEqual([x.uid for x in r.hits],list(range(73,201)))
        self.assertEqual(len(r.decisions),128)


if __name__=="__main__":unittest.main()

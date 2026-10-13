import json
from pathlib import Path
import struct
import unittest
from dataclasses import replace

from arknights_probe.physics_context import (
    PhysicsEpoch, UnityBoundsSnapshot, UnityVectorSnapshot, PhysicsQueryPlan,
    ContactFilterSnapshot, PhysicalColliderHit, ExternalOverlapResult,
    UnverifiedPhysicsContext, battle_physics_phases, load_prefab_physics_catalog,
    plan_box_overlap, plan_circle_overlap, radius_from_transformed_vector,
    legacy_filter_initial_bytes, range_query_transform_contract, bind_external_query_results,
)
from arknights_probe.targeting import TargetSnapshot

ANALYSIS = Path(__file__).resolve().parents[2]/".rea-tools"/"arknights-pc"/"native_v8"/"physics_context"


def epoch(**kw):
    return replace(PhysicsEpoch(5, "objects_fixed", 7, 9, 2, True, True, True, "explicit frozen scene state fixture"), **kw)


def bounds(key="box0", **kw):
    return replace(UnityBoundsSnapshot(key, (1.0, 2.0, 3.0), (.5, 1.0, .25), epoch(),
                                      "explicit Unity bounds getter fixture", "UnityEngine.BoxCollider2D"), **kw)


def box(key="box0", **kw):
    b=bounds(key, **kw)
    return plan_box_overlap(b, b, layer_mask=0x10000600, source="native box parameter fixture")


def entity(uid=2):
    return TargetSnapshot(uid, 2, 0, 1, 0, True, False, None, None, None, "explicit component state fixture")


def receipt(plan, hits=None, **kw):
    hits = hits if hits is not None else (PhysicalColliderHit(-777, entity(), "explicit Unity collider/component fixture"),)
    return replace(ExternalOverlapResult(plan.fingerprint, plan.epoch, len(hits), hits,
        ContactFilterSnapshot(legacy_filter_initial_bytes(plan.layer_mask, plan.epoch.queries_hit_triggers),
                              "explicit final-filter fixture equal to initial declaration; no engine call"),
        "explicit external query fixture; no computed overlap"), **kw)


class PhysicsDeclarationsTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = load_prefab_physics_catalog(ANALYSIS/"prefab_physics_inputs.json")

    def test_actual_circle_and_capsule_layers_and_triggers(self):
        for name, layer in (("enemy_1034_laxe",9),("enemy_2133_shdopl",9),("enemy_3001_upeopl",28)):
            row = self.catalog[name]
            self.assertEqual([x.collider_type for x in row.colliders], ["CircleCollider2D","CapsuleCollider2D"])
            self.assertEqual([x.layer for x in row.colliders], [layer,19])
            self.assertEqual([x.is_trigger for x in row.colliders], [True,False])
            self.assertEqual(row.colliders[0].fields["m_Radius"],struct.unpack("<f",struct.pack("<f",.1))[0])

    def test_body_defaults_and_skill_runtime_range_gap(self):
        self.assertEqual(self.catalog["sktok_ore"].colliders, ())
        self.assertEqual(self.catalog["sktok_ore"].rigidbodies, ())
        altar = self.catalog["trap_011_ore"]
        self.assertEqual(altar.colliders[0].fields["m_Radius"], .25)
        self.assertEqual(altar.rigidbodies[0]["fields"]["m_BodyType"], 1)
        self.assertEqual(self.catalog["enemy_1034_laxe"].rigidbodies[0]["fields"]["m_BodyType"], 0)

    def test_rigidbody_presence_does_not_imply_circle_marker_presence(self):
        for name,row in self.catalog.items():
            self.assertEqual(row.circle_overlap_fixed_components, ())
            if name != "sktok_ore":self.assertEqual(len(row.rigidbodies),1)

    def test_full_parent_chain_is_present_and_immutable(self):
        laxe = self.catalog["enemy_1034_laxe"]
        chain = laxe.colliders[1].transform_chain
        self.assertEqual(chain[0],laxe.root_transform_path_id)
        self.assertEqual(len(chain),2)
        with self.assertRaises(TypeError):laxe.colliders[0].fields["m_Radius"] = 9
        with self.assertRaises(TypeError):self.catalog["new"] = laxe

    def test_prefab_positions_are_not_runtime_world_pose(self):
        with self.assertRaises(UnverifiedPhysicsContext):self.catalog["enemy_1034_laxe"].infer_world_pose()
        self.assertNotEqual(self.catalog["enemy_1034_laxe"].transforms[self.catalog["enemy_1034_laxe"].root_transform_path_id]
                            ["transform"]["fields"]["m_LocalPosition"]["x"],0.0)

    def test_serialized_settings_and_literal_enums_are_initial_values(self):
        data=json.loads((ANALYSIS/"static_inputs.json").read_text("utf-8"))
        settings=data["Physics2DSettings"]["fields"]
        self.assertEqual((settings["m_SimulationMode"],settings["m_AutoSyncTransforms"],settings["m_QueriesHitTriggers"]),(0,True,True))
        enums={r["name"]:{e["name"]:e["default"]["value"] for e in r["entries"]} for r in data["enum_constants"]}
        self.assertEqual(enums["UnityEngine.SimulationMode2D"],{"FixedUpdate":0,"Update":1,"Script":2})
        self.assertEqual(enums["UnityEngine.RigidbodyType2D"],{"Dynamic":0,"Kinematic":1,"Static":2})


class NativeQueryArgumentsTests(unittest.TestCase):
    def test_two_bounds_getters_and_area_conversion(self):
        a=bounds(center=(10.,20.,30.),extents=(2.,3.,4.))
        b=bounds(center=(11.,22.,33.),extents=(1.,5.,6.),source="second distinct getter fixture")
        p=plan_box_overlap(a,b,layer_mask=-1,source="two native bounds reads")
        self.assertEqual(dict(p.arguments),{"pointA":(8.,17.),"pointB":(12.,27.),"boxCenter":(10.,22.),"boxSize":(4.,10.),"angle":(0.,)})
        self.assertEqual(p.as_dict()["physics_scene_handle"],0)

    def test_area_size_abs_and_zero_angle_are_native_not_point_intersection(self):
        p=plan_box_overlap(bounds(extents=(-2.,-3.,0.)),bounds(extents=(-2.,-3.,0.)),layer_mask=2,source="explicit signed bounds fixture")
        self.assertEqual(dict(p.arguments)["boxSize"],(4.,6.))
        bad=tuple((k,(123.,0.) if k=="boxCenter" else v) for k,v in p.arguments)
        with self.assertRaises(UnverifiedPhysicsContext):replace(p,arguments=bad)

    def test_radius_is_transformed_vector_magnitude_in_three_dimensions(self):
        self.assertEqual(radius_from_transformed_vector((3.,4.,12.)),13.)
        self.assertEqual(radius_from_transformed_vector((0.,0.,0.)),0.)

    def test_circle_marker_presence_not_rigidbody_uses_different_centers(self):
        vector=UnityVectorSnapshot((3.,4.,0.),epoch(),"explicit TransformVector(radius,0,0) fixture")
        cb=bounds(runtime_class="UnityEngine.CircleCollider2D")
        p=plan_circle_overlap("box0",vector,runtime_class="UnityEngine.CircleCollider2D",has_circle_overlap_fixed=True,
                              bounds=cb,world_position=None,layer_mask=512,source="marker branch fixture")
        self.assertEqual(dict(p.arguments),{"center":(1.,2.),"radius":(5.,)})
        q=plan_circle_overlap("circle",vector,runtime_class="UnityEngine.CircleCollider2D",has_circle_overlap_fixed=False,
            bounds=None,world_position=UnityVectorSnapshot((9.,10.,11.),epoch(),"world position fixture"),layer_mask=512,source="no marker fixture")
        self.assertEqual(dict(q.arguments)["center"],(9.,10.))

    def test_unknown_marker_pose_type_and_nonfinite_contexts_reject(self):
        v=UnityVectorSnapshot((1.,0.,0.),epoch(),"radius ray fixture")
        for runtime_class,marker in (("UnityEngine.CircleCollider2D",None),("UnityEngine.CapsuleCollider2D",False)):
            with self.assertRaises(UnverifiedPhysicsContext):plan_circle_overlap("x",v,runtime_class=runtime_class,
                has_circle_overlap_fixed=marker,bounds=None,world_position=None,layer_mask=1,source="unknown branch")
        with self.assertRaises(UnverifiedPhysicsContext):plan_box_overlap(bounds(runtime_class="UnityEngine.CapsuleCollider2D"),bounds(),layer_mask=1,source="wrong class")
        for v in ((float("inf"),0.,0.),(1e20,1e20,0.)):
            with self.assertRaises(UnverifiedPhysicsContext):radius_from_transformed_vector(v)

    def test_legacy_filter_before_consistency_has_exact_flags_and_depth(self):
        payload=legacy_filter_initial_bytes(-1,False)
        self.assertEqual(len(payload),28)
        self.assertEqual(payload[:8],bytes([0,1,1,0,0,0,0,0]))
        self.assertEqual(payload[8:20].hex(),"ffffffff000080ff0000807f")
        with self.assertRaises(UnverifiedPhysicsContext):ContactFilterSnapshot(b"", "missing final filter")

    def test_subnormal_geometry_requires_native_float_environment_evidence(self):
        with self.assertRaises(UnverifiedPhysicsContext):radius_from_transformed_vector((1e-20,0.,0.))
        with self.assertRaises(UnverifiedPhysicsContext):UnityVectorSnapshot((2.0**-149,0.,0.),epoch(),"subnormal input fixture")
        self.assertEqual(radius_from_transformed_vector((1e-30,0.,0.)),0.)

    def test_pose_contract_restores_local_on_normal_return_only(self):
        a=UnityVectorSnapshot((1.,2.,3.),epoch(),"saved local getter fixture")
        b=UnityVectorSnapshot((11.,22.,33.),epoch(transform_revision=8),"MapToWorld output fixture")
        trace=range_query_transform_contract(a,b,source="normal native pose sequence")
        self.assertEqual(trace["operations"], ["get_localPosition","set_position_world","FindTargets_DISPOSE","set_localPosition_saved"])
        self.assertTrue(trace["normal_return_only"])
        self.assertFalse(trace["exception_restore_validated"])


class PhysicsEpochAndBindingTests(unittest.TestCase):
    def test_native_manual_simulate_is_after_object_tick_before_coroutines(self):
        phases=battle_physics_phases(simulation_mode=2,hotfixes_absent=True,source="native BC phase fixture")
        self.assertLess(phases.index("objects_fixed"),phases.index("manual_simulate"))
        self.assertLess(phases.index("manual_simulate"),phases.index("coroutines"))
        for mode in (0,1):self.assertNotIn("manual_simulate",battle_physics_phases(simulation_mode=mode,hotfixes_absent=True,source="automatic branch fixture"))

    def test_unknown_hotfix_and_automatic_manual_phase_reject(self):
        for kw in ({"hotfixes_absent":False},{"auto_sync_transforms":None},{"simulation_mode":0,"phase":"manual_simulate"}):
            with self.assertRaises(UnverifiedPhysicsContext):epoch(**kw)

    def test_adapter_preserves_physical_and_entity_duplicates_before_collector(self):
        plans=tuple(box(f"box{i}") for i in range(3))
        results=tuple(receipt(p) for p in plans)
        bound=bind_external_query_results(plans,results,source="explicit 3 query fixture")
        self.assertEqual([x.hits[0].uid for x in bound.as_targeting_snapshot().colliders],[2,2,2])
        self.assertFalse(bound.as_dict()["physics_overlap_generated"])
        self.assertFalse(bound.as_dict()["runtime_battle_validated"])

    def test_old_pose_or_different_query_result_is_rejected(self):
        p=box();r=receipt(p)
        for bad in (replace(r,epoch=epoch(transform_revision=8)),replace(r,plan_fingerprint=box("different").fingerprint)):
            with self.assertRaises(UnverifiedPhysicsContext):bind_external_query_results((p,),(bad,),source="stale fixture")

    def test_count_prefix_complete_and_consistency_is_mandatory(self):
        p=box()
        with self.assertRaises(UnverifiedPhysicsContext):receipt(p,returned_count=2)
        with self.assertRaises(UnverifiedPhysicsContext):receipt(p,filter_after_consistency=None)
        with self.assertRaises(UnverifiedPhysicsContext):PhysicalColliderHit(None,entity(),"impossible null collider fixture")

    def test_full_buffer_reports_possible_truncation_without_fabricating_more_hits(self):
        p=box()
        hits=tuple(PhysicalColliderHit(i,None,"explicit no Entity component fixture") for i in range(128))
        bound=bind_external_query_results((p,),(receipt(p,hits),),source="full native buffer fixture")
        self.assertTrue(bound.as_dict()["results"][0]["buffer_may_be_truncated"])
        self.assertEqual(len(bound.as_targeting_snapshot().colliders[0].hits),128)

    def test_missing_query_reordered_results_and_mixed_epochs_reject(self):
        a,b=box("a"),box("b")
        with self.assertRaises(UnverifiedPhysicsContext):bind_external_query_results((a,b),(receipt(a),),source="missing query")
        with self.assertRaises(UnverifiedPhysicsContext):bind_external_query_results((a,b),(receipt(b),receipt(a)),source="reordered queries")
        b=box("b",epoch=epoch(scene_revision=10))
        with self.assertRaises(UnverifiedPhysicsContext):bind_external_query_results((a,b),(receipt(a),receipt(b)),source="mixed world revisions")


if __name__ == "__main__":unittest.main()

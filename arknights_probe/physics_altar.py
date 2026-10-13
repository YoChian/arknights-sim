"""Prepared altar composition with epoch-bound external Unity query receipts.

This instruments the selected frame component's actual callback phase. Bounds,
live engine settings, CheckConsistency and hit membership are named fixtures;
neither prefab geometry nor a replacement collision engine generates hits.
"""
from .altar_prepared import PreparedAltarProbe
from .fp import FP
from .physics_context import (
    PhysicsEpoch, UnityBoundsSnapshot, ContactFilterSnapshot,
    ExternalOverlapResult, PhysicalColliderHit, bind_external_query_results,
    legacy_filter_initial_bytes, plan_box_overlap,
)
from .targeting import TargetSnapshot
from .targeting_runtime import RuntimeTargetData, select_altar_targets_runtime


class PhysicsPlannedAltarProbe(PreparedAltarProbe):
    def __init__(self, dataset):
        super().__init__(dataset)
        self.physics_records = []
        self.query_phase = "objects_fixed"
        old_fixed = self.registry.objects[0].fixed_tick

        def fixed(dt):
            self.query_phase = "objects_fixed"
            old_fixed(dt)
        self.registry.objects[0].fixed_tick = fixed

        def mark_coroutines(dt):
            self.query_phase = "coroutines"
        self.loop.before = self.loop.before + (mark_coroutines,)
        self.selection_inputs["physics_backend"] = "epoch-bound external Unity bounds/filter/hit receipts"

    def _select(self):
        source = "explicit stationary altar query fixture; engine settings/bounds/filter/hits supplied, not measured"
        epoch = PhysicsEpoch(self.lifecycle.current_frame, self.query_phase, 0, 0,
                             2, True, True, True, source)
        target = TargetSnapshot(uid=2 if not self.actor.recycled else 0,
            side=2, motion=0, category=1, map_layer=0, alive=self.actor.alive,
            destroyed=self.actor.recycled, ally_target_free=None, heal_free=None,
            camouflage=None, source=self.source + "; explicit actor native fields")
        plans, receipts = [], []
        # Three independent external bounds getter pairs. These are not world
        # bounds computed from the serialized prefab or declaration rectangles.
        fixtures = (((5.0, 5.0, 0.0), (.5, 1.5, 0.0)),
                    ((6.0, 5.0, 0.0), (.5, .5, 0.0)),
                    ((7.0, 5.0, 0.0), (.5, 1.5, 0.0)))
        for index, (center, extents) in enumerate(fixtures):
            key = f"prepared_range_box_{index}"
            bounds_min = UnityBoundsSnapshot(key, center, extents, epoch, source + "; first bounds getter", "UnityEngine.BoxCollider2D")
            bounds_max = UnityBoundsSnapshot(key, center, extents, epoch, source + "; second bounds getter", "UnityEngine.BoxCollider2D")
            plan = plan_box_overlap(bounds_min, bounds_max,
                                    layer_mask=self.selector_context.query_layer_mask, source=source)
            plans.append(plan)
            final_filter = ContactFilterSnapshot(
                legacy_filter_initial_bytes(plan.layer_mask, True),
                source + "; explicit post-CheckConsistency equals initial payload fixture")
            receipts.append(ExternalOverlapResult(
                plan.fingerprint, epoch, 1,
                (PhysicalColliderHit(200, target, source + "; same collider returned by all three queries fixture"),),
                final_filter, source + "; supplied overlap prefix, no intersection calculated"))
        bound = bind_external_query_results(tuple(plans), tuple(receipts), source=source)
        self.physics_records.append(bound.as_dict())
        targets = {target.uid: RuntimeTargetData(
            created_time=FP.from_raw(0), attributes=self.target_status, hit_range=self.hit_range,
            source=self.source + "; explicit createdTime raw0")}
        result = select_altar_targets_runtime(bound.as_targeting_snapshot(), self.selector_context, targets)
        self.selections.append({"frame": self.lifecycle.current_frame, **result.as_dict()})
        return result.hits

    def artifact(self):
        result = super().artifact()
        result["scope"] = "prepared_altar_with_recovered_query_parameters_and_external_Unity_receipts"
        result["physics_queries"] = self.physics_records
        result["external_inputs"].update(
            physics_bounds="three explicitly supplied getter pairs; no prefab world-pose inference",
            physics_live_settings="manual mode2/autoSyncTransforms true/queriesHitTriggers true fixture",
            physics_contact_filter="post-CheckConsistency payload equals initial only as explicit fixture",
            physics_query_phase="instrumented selected-loop callback stage; complete BC modules remain absent",
            unity_simulation_and_sync="not executed; overlap membership is a supplied receipt")
        return result

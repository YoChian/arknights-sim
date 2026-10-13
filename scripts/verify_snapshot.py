"""Regenerate small review artifacts and run meaningful validation once."""
import io
import json
from pathlib import Path
import sys
import unittest
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from arknights_probe import Dataset, DeclarationProbeEnv
from arknights_probe.navigation import route_probe, render_svg
from arknights_probe.prepare import DEFAULT_MANIFEST
from arknights_probe.rng_validation import verify_rng_reference
from arknights_probe.timeline import TimelineEnv, compile_timeline
from arknights_probe.preprocess import rogue_preprocess
from arknights_probe.legacy_random import LegacyRandom
from arknights_probe.timeline_validation import verify_timeline_evidence
from arknights_probe.sort_validation import verify_sort_reference
from arknights_probe.fp import FP_EVIDENCE
from arknights_probe.data import read_json, sha256
from arknights_probe.enemy_validation import verify_enemy_rules_evidence, verify_enemy_data_evidence
from arknights_probe.enemy_creation_inputs import derive_enemy_runtime
from arknights_probe.enemy_data import resolve_enemy
from arknights_probe.enemy_rules import enemy_profile, apply_selected_attribute_mul
from arknights_probe.movement import WalkRouteSpec, WaitCheckpoint
from arknights_probe.movement_validation import verify_movement_evidence
from arknights_probe.fp import FP
from arknights_probe.timeline import ASSET_DEFAULT_DT_RAW
from arknights_probe.scene import audit_idle_scene, input_pins
from arknights_probe.component_validation import verify_v5_evidence
from probe_route_lifecycle import make_probe
from probe_altar_component import make_probe as make_altar_probe
from arknights_probe.v6_validation import verify_v6_evidence


def save(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def main():
    dataset = Dataset.from_manifest(DEFAULT_MANIFEST)
    artifacts = ROOT / "artifacts"
    rng_reference = verify_rng_reference()
    timeline_evidence = verify_timeline_evidence()
    sort_reference = verify_sort_reference()
    enemy_evidence = verify_enemy_rules_evidence()
    enemy_evidence["data_resolution"] = verify_enemy_data_evidence()
    movement_evidence = verify_movement_evidence()
    v5_evidence = verify_v5_evidence()
    v6_evidence = verify_v6_evidence()
    save(artifacts / "v6_component_evidence_verification.json", v6_evidence)
    altar_probe = make_altar_probe(dataset)
    altar_final = altar_probe.step(5000)
    save(artifacts / "altar_component_external.json", altar_probe.artifact())
    save(artifacts / "v5_component_evidence_verification.json", v5_evidence)
    save(artifacts / "movement_evidence_verification.json", movement_evidence)
    save(artifacts / "enemy_evidence_verification.json", enemy_evidence)
    prefab_inputs = read_json(Path(r"D:\Repo\.rea-tools\arknights-pc\native_v4\resources\prefab_inputs.json"))
    creation_inputs = derive_enemy_runtime(dataset, prefab_inputs,
        counted_creation={key: True for key in dataset.enemy_refs},
        source="native_EnemyDB_TryGet_and_shipped_prefab_delay; external_post_Init_alive_creation_fixture_true; native_hotfix_overrides_absent")
    save(artifacts / "enemy_creation_inputs.json", creation_inputs)
    enemies = [enemy_profile(resolve_enemy(dataset.tables["enemies"], ref)) for ref in dataset.enemy_refs.values()]
    save(artifacts / "enemies_resolved.json", {"scope": "static_EnemyDB_defaults_and_ref_overwrite", "enemies": enemies, "battle_ready": False})
    operation = read_json(ROOT / "examples/enemy_attribute_mul_selected.json")
    selected_enemies = [enemy_profile(apply_selected_attribute_mul(resolve_enemy(dataset.tables["enemies"], ref),
                       operation["multipliers"], source=operation["source"])) for ref in dataset.enemy_refs.values()]
    save(artifacts / "enemies_selected_mul.json", {"scope": "explicit_selected_attribute_mul_operation",
         "selected_operations": operation, "enemies": selected_enemies, "battle_ready": False})
    save(artifacts / "rng_reference_comparison.json", rng_reference)
    save(artifacts / "timeline_evidence_verification.json", timeline_evidence)
    save(artifacts / "sort_reference_comparison.json", sort_reference)
    timelines = {}
    for name in ("normal", "four_star"):
        config = read_json(ROOT / f"examples/timeline_{name}_external.json")
        timeline = TimelineEnv(dataset, compile_timeline(dataset, **config))
        initial, timeline_info = timeline.reset(seed=42)
        observation, reward, done, truncated, _ = timeline.step({"type": "tick", "frames": 1200})
        save(artifacts / f"timeline_{name}_external.json", {"initial": initial, "info": timeline_info,
             "events": timeline.events, "observation": observation, "reward": reward, "terminated": done, "truncated": truncated})
        timelines[name] = {"mode": config["mode"], "frames": observation["current_frame"], "time_raw": observation["time_raw"],
                           "phase": observation["phase"], "spawn_requests": sum(x["kind"] == "spawn_request" for x in timeline.events),
                           "preview_requests": sum(x["kind"] == "preview_cursor_request" for x in timeline.events),
                           "alive_tracked": len(timeline.alive), "clock_origin": timeline.clock_origin,
                           "input_source": config["input_source"], "battle_ready": False,
                           "live_fixed_delta_validated": False, "synthetic_kills_performed": False}
    preprocess = rogue_preprocess(dataset, rng=LegacyRandom(42), topic_id="rogue_6", mimic_count=0, gold_count=0,
                                  group_order=["t1", "t2", "c1"], input_source="independent_seed42_explicit_order_and_zero_retain_fixture")
    save(artifacts / "rogue_preprocess_seed42_external.json", preprocess)
    derived_timelines = {}
    for name in ("normal", "four_star"):
        config = read_json(ROOT / f"examples/timeline_{name}_resolved.json")
        if config["enemy_runtime"] != creation_inputs["enemy_runtime"]:
            raise ValueError("Resolved timeline example no longer matches reviewed enemy/prefab inputs")
        timeline = TimelineEnv(dataset, compile_timeline(dataset, **config))
        initial, timeline_info = timeline.reset(seed=42)
        observation, reward, done, truncated, _ = timeline.step({"type": "tick", "frames": 1200})
        save(artifacts / f"timeline_{name}_resolved.json", {"initial": initial, "info": timeline_info,
             "events": timeline.events, "observation": observation, "reward": reward, "terminated": done, "truncated": truncated})
        derived_timelines[name] = {"phase": observation["phase"], "spawn_requests": sum(e["kind"] == "spawn_request" for e in timeline.events),
             "derived_fields": creation_inputs["derived"], "external_fields": creation_inputs["external"], "battle_ready": False}
    v5_resources = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v5\resources")
    subtree_file = v5_resources / "rule_prefab_subtrees.json"
    template_file = v5_resources / "scene_templates.json"
    scene_audits = {}
    for name in ("normal", "four_star"):
        config_file = ROOT / f"examples/timeline_{name}_resolved.json"
        compiled = compile_timeline(dataset, **read_json(config_file))
        audit = audit_idle_scene(dataset, compiled, read_json(subtree_file),
            read_json(template_file), source="reviewed_shipped_transform_subtrees_and_template_closure")
        audit["input_pins"] = input_pins(config_file, subtree_file, template_file)
        save(artifacts / f"scene_{name}_audit.json", audit)
        scene_audits[name] = {"required_prefabs": len(audit["required_prefabs"]),
            "component_classes": len(audit["component_classes"]),
            "required_buff_templates": len(audit["required_buff_templates"]),
            "missing_prefabs": audit["missing_prefabs"], "missing_buff_templates": audit["missing_buff_templates"],
            "summon_dependencies": audit["summon_dependencies"], "execution_blockers": audit["execution_blockers"],
            "full_scene_ready": False}
    route_probe_env = make_probe()
    route_initial, route_info = route_probe_env.reset()
    route_final, route_reward, route_done, _, _ = route_probe_env.step({"type": "tick", "frames": 300})
    save(artifacts / "route_lifecycle_component_verification.json", {
        "initial": route_initial, "info": route_info, "events": route_probe_env.lifecycle.events,
        "final": route_final, "reward": route_reward, "terminated": route_done})
    walk_components, wait_components = [], []
    for pool, routes in (("routes", dataset.routes), ("extraRoutes", dataset.extra_routes)):
        for index, route in enumerate(routes):
            if route["motionMode"] != "WALK":
                continue
            spec = WalkRouteSpec.from_json(route, height=dataset.rows, width=dataset.cols)
            walk_components.append({"pool": pool, "route_index": index, "scope": spec.scope()})
            for cp_index, checkpoint in enumerate(spec.checkpoints):
                if checkpoint.kind != "WAIT_FOR_SECONDS":
                    continue
                wait = WaitCheckpoint(checkpoint.seconds)
                ticks = 0
                while not wait.is_reached:
                    wait.tick(FP.from_raw(ASSET_DEFAULT_DT_RAW))
                    ticks += 1
                wait_components.append({"pool": pool, "route_index": index, "checkpoint_index": cp_index,
                    "seconds_float32": checkpoint.seconds, "initial_fp_raw": wait.initial.raw,
                    "standalone_countdown_ticks": ticks})
    save(artifacts / "movement_components.json", {"walk_routes": walk_components, "wait_checkpoints": wait_components,
        "scope": "route_declarations_and_standalone_native_WAIT_countdown; full_cursor_tick_order_excluded",
        "autonomous_route_ready": False, "battle_ready": False})
    save(artifacts / "snapshot_summary.json", dataset.summary())
    routes = [route_probe(dataset, i) for i, route in enumerate(dataset.routes) if route["motionMode"] == "WALK"]
    storage_routes = [route_probe(dataset, i, row_mapping="matrix") for i, route in enumerate(dataset.routes) if route["motionMode"] == "WALK"]
    save(artifacts / "route_topology.json", routes)
    save(artifacts / "route_topology_bottom_origin.json", routes)
    save(artifacts / "route_topology_raw_matrix.json", storage_routes)
    render_svg(dataset, artifacts / "map.svg", route=10)
    render_svg(dataset, artifacts / "map_bottom_origin.svg", route=16, row_mapping="bottom_origin")
    render_svg(dataset, artifacts / "map_raw_matrix.svg", route=16, row_mapping="matrix")
    ET.parse(artifacts / "map.svg")
    env = DeclarationProbeEnv(dataset)
    observation, info = env.reset(seed=42)
    trace = {"initial": observation, "scope": info, "declarations": []}
    while observation["remaining"]:
        observation, reward, done, truncated, detail = env.step({"type": "next"})
        trace["declarations"].append(detail["inspected_declaration"])
    trace["final"] = {"observation": observation, "reward": reward, "terminated": done, "truncated": truncated}
    save(artifacts / "declaration_trace_seed42.json", trace)
    stream = io.StringIO()
    suite = unittest.defaultTestLoader.discover(str(ROOT / "tests"))
    result = unittest.TextTestRunner(stream=stream, verbosity=2).run(suite)
    (artifacts / "tests.txt").write_text(stream.getvalue(), encoding="utf-8")
    reference_dir = ROOT / "evidence/timeline_reference"
    reference = read_json(reference_dir / "reference_vectors.json")
    coroutine_reference = {"scope": reference["oracle_scope"], "validated_by_full_test_suite": result.wasSuccessful(),
         "coroutine_cases": len(reference["cases"]), "coroutine_tick_states": sum(len(x["trace"]) for x in reference["cases"]),
         "coroutine_events": sum(len(x["events"]) for x in reference["cases"]), "binary32_waits": len(reference["waits"]),
         "kernel_cases": len(reference["kernels"]), "kernel_tick_states": sum(len(x["trace"]) for x in reference["kernels"]),
         "kernel_events": sum(len(x["events"]) for x in reference["kernels"]),
         "files_sha256": {name: sha256(reference_dir / name) for name in ("TimelineReference.cs", "reference_input.json", "reference_vectors.json", "native_evidence.json")},
         "prepared_queues_sort_independently_compared": False, "client_runtime_compared": False}
    save(artifacts / "timeline_coroutine_reference_comparison.json", coroutine_reference)
    report = {"healthy": result.wasSuccessful(), "tests_run": result.testsRun,
              "failures": len(result.failures), "errors": len(result.errors), "skipped": len(result.skipped),
              "source_hashes_verified": True, "svg_xml_valid": True,
              "main_declarations_replayed": len(trace["declarations"]),
              "walk_routes_probed": len(routes),
              "cardinal_reachable_routes": sum(x["all_segments_reachable"] for x in routes),
              "raw_matrix_view_reachable_routes": sum(x["all_segments_reachable"] for x in storage_routes),
              "coordinate_mapping_native_verified": True,
              "coordinate_evidence_addresses": ["0x18241d270", "0x18241d1e0", "0x18241d300", "0x18241d330"],
              "legacy_rng_reference": rng_reference,
              "fixed_point_reference": {"scope": "independent_CSharp_native_translation_not_client_oracle",
                                          "native_functions": FP_EVIDENCE["native_functions"], "pair_cases": 7073,
                                          "unary_cases": 81, "float32_cases": 93, "double_cases": 92,
                                          "file_sha256": FP_EVIDENCE["file_sha256"], "client_runtime_compared": False},
              "sort_reference": sort_reference,
              "timeline_coroutine_reference": coroutine_reference,
              "timeline_evidence": {key: value for key, value in timeline_evidence.items() if key != "files"},
              "conditional_timeline_examples": timelines,
              "independent_preprocessor": {key: value for key, value in preprocess.items() if key != "eligible_original_indices"},
              "enemy_evidence": enemy_evidence,
              "enemy_resolution": {"references": len(enemies), "numeric_fields_per_ref": len(enemies[0]["attributes_fp_raw"]),
                    "numeric_reference": read_json(ROOT / "evidence/enemy_data/reference_comparison.json"),
                    "entity_effect_modifiers_applied": False, "rune_selector_restored": False},
              "derived_timeline_examples": derived_timelines,
              "movement_components": {"validated_walk_declarations": len(walk_components), "wait_checkpoints": len(wait_components),
                    "native_path_context": "explicit_cached_tile_snapshot_required", "autonomous_route_ready": False,
                    "evidence": movement_evidence},
              "runtime_battle_validated": False,
              "battle_ready": False,
              "autonomous_route_ready": False,
              "v5_component_evidence": v5_evidence,
              "v6_component_evidence": v6_evidence,
              "controlled_altar_component": {"frames": altar_final["frame"],
                  "casts": altar_final["cast_count"], "hp_raw": altar_final["hp_raw"],
                  "damage_applications": sum(d["applied"] for d in altar_probe.damage_results),
                  "first_damage_frame": altar_probe.damage_results[0]["frame"],
                  "finish_reason": altar_final["finish_reason"], "recycled": altar_final["recycled"],
                  "life": altar_final["life"], "finish_request": altar_final["finish_request"],
                  "physics_backend": "explicit_external_overlap_snapshot",
                  "ALL_order_backend": "explicit_external_output_snapshot",
                  "prepared_times": "explicit_field_fixture",
                  "original_map_scheduler_connected": False, "reward_defined": False,
                  "battle_ready": False, "autonomous_route_ready": False, "runtime_battle_validated": False},
              "scene_rule_audits": scene_audits,
              "automatic_route_lifecycle_component": {"frames": route_final["frame"],
                  "finish_request": route_final["finish_request"], "recycled": route_final["recycled"],
                  "life": route_final["life"], "reward_defined": False,
                  "full_scene_scheduler_connected": False, "battle_ready": False},
              "scope": "static_rule_components_conditional_scheduler_single_actor_route_lifecycle_and_controlled_altar_composition; full_shipped_scene_execution_not_closed"}
    save(artifacts / "verification.json", report)
    display = {key: value for key, value in report.items() if key != "legacy_rng_reference"}
    display["legacy_rng_reference"] = {key: rng_reference[key] for key in ("healthy", "scope", "seed_count", "checks", "client_runtime_compared")}
    print(json.dumps(display, ensure_ascii=False, indent=2))
    return 0 if result.wasSuccessful() else 1


if __name__ == "__main__":
    raise SystemExit(main())

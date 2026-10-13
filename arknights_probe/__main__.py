from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

from .data import Dataset, DataError
from .env import DeclarationProbeEnv, UnverifiedMechanism
from .navigation import route_probe, render_svg
from .prepare import DEFAULT_MANIFEST, DEFAULT_SOURCE, prepare
from .legacy_random import LegacyRandom, NATIVE_RNG_EVIDENCE
from .rng_validation import verify_rng_reference
from .timeline import TimelineEnv, compile_timeline, ASSET_DEFAULT_DT_RAW, zero_enemy_fixture
from .data import read_json
from .preprocess import rogue_preprocess
from .enemy_data import UnverifiedEnemyData
from .scene import audit_idle_scene, input_pins


def main():
    parser = argparse.ArgumentParser(description="Local Arknights static components; full battle is not implemented")
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("prepare", help="Validate and pin normalized JSON by SHA-256")
    p.add_argument("--source-dir", type=Path, default=DEFAULT_SOURCE)
    sub.add_parser("inspect", help="Map, wave, table and capability summary")
    p = sub.add_parser("trace", help="Inspect declarations in array order; this is not battle time")
    p.add_argument("--seed", type=int, default=42)
    p.add_argument("--branch")
    p.add_argument("--limit", type=int, default=5)
    p = sub.add_parser("topology", help="Cardinal grid reachability diagnostic")
    p.add_argument("--route", type=int, default=10)
    p.add_argument("--extra", action="store_true")
    p.add_argument("--row-mapping", choices=["matrix", "bottom_origin"], default="bottom_origin")
    p = sub.add_parser("rng", help="Independent recovered LegacyRandom component; no battle integration")
    p.add_argument("--seed", type=int, default=42)
    p.add_argument("--count", type=int, default=8)
    p.add_argument("--max", type=int, dest="maximum")
    sub.add_parser("rng-reference", help="Verify independent C# reference vectors, not the running client")
    p = sub.add_parser("render", help="Save an SVG with native logical coordinates and a cardinal probe")
    p.add_argument("--route", type=int, default=10)
    p.add_argument("--output", type=Path, default=Path("artifacts/map.svg"))
    p.add_argument("--row-mapping", choices=["matrix", "bottom_origin"], default="bottom_origin")
    p = sub.add_parser("timeline", help="Frame-driven static scheduler kernel with explicit external inputs; no combat")
    p.add_argument("--config", type=Path, required=True, help="JSON: mode, group_selections, enemy_runtime, input_source")
    p.add_argument("--frames", type=int, default=1200)
    p.add_argument("--seed", type=int, default=42, help="Recorded only, never a battle RNG seed")
    p.add_argument("--dt-raw", type=int, default=ASSET_DEFAULT_DT_RAW)
    p = sub.add_parser("scene-audit", help="List selected scene dependencies and unresolved execution rules")
    p.add_argument("--config", type=Path, required=True, help="Reviewed timeline config including original group choices")
    p = sub.add_parser("altar-component", help="Run the controlled altar/laxe composition with external physics/time fixtures")
    p.add_argument("--frames", type=int, default=5000)
    p.add_argument("--output", type=Path, default=Path("artifacts/altar_component_external.json"))
    p = sub.add_parser("preprocess", help="Independent static Rogue selection with explicit RNG/order/retain counters")
    p.add_argument("--seed", type=int, required=True)
    p.add_argument("--topic", required=True)
    p.add_argument("--mimic-count", type=int, required=True)
    p.add_argument("--gold-count", type=int, required=True)
    p.add_argument("--group-order", required=True, help="Comma-separated external group order; for this map t1,t2,c1")
    p = sub.add_parser("enemies", help="Resolve local enemy data and review pre-entity-modifier attributes")
    p.add_argument("--selected-multipliers", type=Path,
                   help="Optional explicit operation fixture: multipliers by runtime field name and source")
    args = parser.parse_args()
    try:
        if args.command == "prepare":
            result = prepare(args.source_dir, args.manifest)
        elif args.command == "rng":
            if not 0 <= args.count <= 10000:
                raise ValueError("--count must be between 0 and 10000")
            rng = LegacyRandom(args.seed)
            result = {"scope": "independent_legacy_random_component", "seed": args.seed,
                      "values": [rng.next(args.maximum) for _ in range(args.count)],
                      "native_evidence": NATIVE_RNG_EVIDENCE,
                      "client_runtime_compared": False, "battle_rng_connected": False}
        elif args.command == "rng-reference":
            result = verify_rng_reference()
        else:
            dataset = Dataset.from_manifest(args.manifest)
            if args.command == "inspect":
                result = dataset.summary()
            elif args.command == "altar-component":
                from .altar_component import AltarComponentProbe
                probe = AltarComponentProbe(dataset)
                probe.step(args.frames)
                args.output.parent.mkdir(parents=True, exist_ok=True)
                args.output.write_text(json.dumps(probe.artifact(), ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
                result = {"artifact": str(args.output.resolve()), **probe.snapshot()}
            elif args.command == "topology":
                result = route_probe(dataset, args.route, extra=args.extra, row_mapping=args.row_mapping)
            elif args.command == "render":
                render_svg(dataset, args.output, args.route, row_mapping=args.row_mapping)
                result = {"svg": str(args.output.resolve()), "scope": "cardinal_grid_topology_only"}
            elif args.command == "trace":
                if args.limit < 0:
                    raise ValueError("--limit must be nonnegative")
                env = DeclarationProbeEnv(dataset)
                observation, info = env.reset(seed=args.seed, options={"branch": args.branch})
                result = {"initial": observation, "info": info, "steps": []}
                while observation["remaining"] and len(result["steps"]) < args.limit:
                    observation, reward, done, truncated, detail = env.step({"type": "next"})
                    result["steps"].append({"observation": observation, "reward": reward, "terminated": done,
                                            "truncated": truncated, "info": detail})
                env.close()
            elif args.command == "scene-audit":
                resources = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v5\resources")
                subtree_file = resources / "rule_prefab_subtrees.json"
                template_file = resources / "scene_templates.json"
                compiled = compile_timeline(dataset, **read_json(args.config))
                result = audit_idle_scene(dataset, compiled, read_json(subtree_file),
                    read_json(template_file), source="static_shipped_transform_subtrees_and_buff_templates")
                result["input_pins"] = input_pins(args.config, subtree_file, template_file)
            elif args.command == "timeline":
                if not 1 <= args.frames <= 100000:
                    raise ValueError("--frames must be between 1 and 100000")
                config = read_json(args.config)
                allowed = {"mode", "group_selections", "enemy_runtime", "input_source", "enabled_hidden", "disabled_hidden"}
                if not isinstance(config, dict) or set(config) - allowed:
                    raise ValueError("Unknown or invalid timeline config fields")
                compiled = compile_timeline(dataset, **config)
                env = TimelineEnv(dataset, compiled, dt_raw=args.dt_raw)
                initial, info = env.reset(seed=args.seed)
                observation, reward, terminated, truncated, _ = env.step({"type": "tick", "frames": args.frames})
                result = {"initial": initial, "info": info, "events": env.events, "observation": observation,
                          "reward": reward, "terminated": terminated, "truncated": truncated}
            elif args.command == "preprocess":
                result = rogue_preprocess(dataset, rng=LegacyRandom(args.seed), topic_id=args.topic,
                                          mimic_count=args.mimic_count, gold_count=args.gold_count,
                                          group_order=args.group_order.split(","),
                                          input_source="explicit_cli_independent_seed_order_retain_fixture")
                result["independent_seed"] = args.seed
            elif args.command == "enemies":
                from .enemy_data import resolve_enemy
                from .enemy_rules import apply_selected_attribute_mul, enemy_profile
                modifiers = None
                if args.selected_multipliers is not None:
                    modifiers = read_json(args.selected_multipliers)
                    if type(modifiers) is not dict or set(modifiers) != {"multipliers", "source"}:
                        raise ValueError("Selected operations require exactly multipliers and source")
                profiles = []
                for reference in dataset.enemy_refs.values():
                    enemy = resolve_enemy(dataset.tables["enemies"], reference)
                    if modifiers is not None:
                        enemy = apply_selected_attribute_mul(enemy, modifiers["multipliers"], source=modifiers["source"])
                    profiles.append(enemy_profile(enemy))
                result = {"scope": "local_enemy_resolution_with_explicit_selected_operations",
                          "selected_operations": modifiers, "enemies": profiles,
                          "live_run_modifiers_inferred": False, "battle_ready": False}
        print(json.dumps(result, ensure_ascii=False, indent=2))
        return 0
    except (DataError, UnverifiedMechanism, UnverifiedEnemyData, ValueError, OSError, KeyError, TypeError, AssertionError) as exc:
        print(f"Probe blocked: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())

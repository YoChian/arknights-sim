"""Run the bounded scalar/contract checks and record their actual counts once."""
import json
from pathlib import Path
import sys
import unittest

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT))


def main():
    output = HERE / "reference_comparison.json"
    if output.exists():
        raise SystemExit("Comparison already exists; review changed evidence before replacing it.")
    suite = unittest.defaultTestLoader.loadTestsFromNames([
        "tests.test_physics_context", "tests.test_physics_context_reference"])
    result = unittest.TextTestRunner(verbosity=1).run(suite)
    vectors = json.loads((HERE / "reference_vectors.json").read_text("utf-8"))
    boxes = vectors["boxes"]
    radii = vectors["radii"]
    finite_boxes = sum(row["finite_scope"] for row in boxes)
    finite_radii = sum(row["finite_scope"] for row in radii)
    report = {
        "scope": "independent reconstructed C# scalar implementation comparison and explicit physics contract fixtures; not a Unity/native/client oracle",
        "all_passed": result.wasSuccessful(),
        "tests_run": result.testsRun,
        "failures": len(result.failures), "errors": len(result.errors),
        "counts": {
            "component_tests": 21, "reference_tests": 4,
            "box_cases": len(boxes), "supported_box_cases": finite_boxes,
            "rejected_box_cases": len(boxes) - finite_boxes,
            "box_single_bit_patterns": finite_boxes * 11,
            "radius_cases": len(radii), "supported_radius_cases": finite_radii,
            "rejected_radius_cases": len(radii) - finite_radii,
            "initial_filter_cases": len(vectors["filters"]),
            "simulation_mode_cases": len(vectors["simulation_modes"]),
        },
        "physics_overlap_generated": False,
        "filter_consistency_generated": False,
        "world_bounds_generated": False,
        "engine_sync_generated": False,
        "live_mxcsr_validated": False,
        "runtime_battle_validated": False,
        "battle_ready": False,
    }
    if not result.wasSuccessful():
        raise SystemExit("Checks failed; no comparison file written.")
    with output.open("x", encoding="utf-8") as stream:
        json.dump(report, stream, ensure_ascii=False, indent=2)
        stream.write("\n")
    print(json.dumps(report, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()

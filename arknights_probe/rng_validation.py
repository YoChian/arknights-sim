"""Compare Python against retained independently compiled C# reference vectors.

Both implementations translate the same native evidence. Agreement catches
translation/arithmetic differences; it does not prove real-client equivalence.
"""
from pathlib import Path
import struct

from .data import read_json, sha256
from .legacy_random import LegacyRandom, INT_MIN, INT_MAX, NATIVE_RNG_EVIDENCE

DEFAULT_REFERENCE_DIR = Path(__file__).resolve().parents[1] / "evidence" / "rng"


def verify_rng_reference(reference_dir: Path = DEFAULT_REFERENCE_DIR) -> dict:
    pins = {"LegacyRandomReference.cs": NATIVE_RNG_EVIDENCE["reference_source_sha256"],
            "reference_vectors.json": NATIVE_RNG_EVIDENCE["reference_vectors_sha256"],
            "native_report_round3.json": NATIVE_RNG_EVIDENCE["report_sha256"]}
    files = []
    for name, expected in pins.items():
        path = reference_dir / name
        digest = sha256(path)
        if digest != expected:
            raise AssertionError(f"RNG reference evidence changed: {path}")
        files.append({"path": str(path.resolve()), "sha256": digest})
    reference = read_json(reference_dir / "reference_vectors.json")
    if reference["oracle_scope"] != "independent C# translation of native pseudocode; not game runtime":
        raise AssertionError("Unexpected reference scope")
    seeds = [vector["seed"] for vector in reference["vectors"]]
    if seeds != [0, 1, -1, 42, -42, 1808733512, INT_MIN, INT_MAX]:
        raise AssertionError("Unexpected seed coverage")
    counts = {"next_integer_checks": 0, "sample_binary64_checks": 0, "next_double_binary64_checks": 0,
              "bounded_integer_checks": 0, "range_integer_checks": 0, "range_consumption_checks": 0,
              "system_random_sequence_differences": 0}
    comparison = []

    def match(actual, expected, context):
        if actual != expected:
            raise AssertionError(f"RNG reference mismatch: {context}; expected {expected!r}, got {actual!r}")

    for vector in reference["vectors"]:
        seed = vector["seed"]
        match(len(vector["next"]), 128, "Next coverage")
        match(len(vector["sample"]), 16, "Sample coverage")
        rng = LegacyRandom(seed)
        generated = [rng.next() for _ in vector["next"]]
        match(generated, vector["next"], f"seed={seed} Next 128")
        counts["next_integer_checks"] += len(generated)
        for method, key in (("sample", "sample_binary64_checks"), ("next_double", "next_double_binary64_checks")):
            rng = LegacyRandom(seed)
            for i, expected in enumerate(vector["sample"]):
                actual = getattr(rng, method)()
                match(struct.pack("<d", actual), struct.pack("<d", expected), f"seed={seed} {method}[{i}] binary64")
                counts[key] += 1
        rng = LegacyRandom(seed)
        match(len(vector["maxima"]), len(vector["bounded"]), "Next(max) coverage")
        match([rng.next(maximum) for maximum in vector["maxima"]], vector["bounded"], f"seed={seed} Next(max) consumption")
        counts["bounded_integer_checks"] += len(vector["bounded"])
        rng = LegacyRandom(seed)
        match(len(vector["minima"]), len(vector["range_maxima"]), "Next(min,max) coverage")
        match([rng.next_range(low, high) for low, high in zip(vector["minima"], vector["range_maxima"])],
              vector["ranged"], f"seed={seed} Next(min,max)")
        counts["range_integer_checks"] += len(vector["ranged"])
        match(rng.next(), vector["next_after_ranges"], f"seed={seed} Next after ranges (consumption)")
        counts["range_consumption_checks"] += 1
        if generated[:len(vector["system_random_next"])] == vector["system_random_next"]:
            raise AssertionError(f"LegacyRandom unexpectedly matches recorded System.Random sequence for {seed}")
        counts["system_random_sequence_differences"] += 1
        comparison.append({"seed": seed, "legacy_first": generated[0], "recorded_system_random_first": vector["system_random_next"][0]})
    return {"healthy": True, "scope": "cross_language_implementation_comparison_not_real_client_oracle",
            "seed_count": len(seeds), "seeds": seeds, "checks": counts, "evidence_files": files,
            "native_evidence": NATIVE_RNG_EVIDENCE, "first_value_comparison": comparison,
            "client_runtime_compared": False, "hot_patch_dispatch_validated": False,
            "battle_rng_consumption_validated": False, "declaration_env_rng_connected": False}

"""Cross-language static translation checks; no live game oracle."""
import hashlib
import json
from pathlib import Path
import struct
import unittest

from arknights_probe.movement import (LocalVector2, NativeTileSnapshot, NativeWalkPathGrid,
    clamp_magnitude, check_distance, local_to_grid, normalize_direction_safely, vector_is_zero)

ROOT = Path(__file__).resolve().parents[1] / "evidence/movement"
REFERENCE_PINS = {
    "MovementReference.cs": "87ca4f95e158c6307eeaed1a3e35f32299b139b1f1e2b03d07514e4a59eedea9",
    "reference_input.json": "9968dcd421504fdc9e3ab9ee4cdaad971e8b96b0c9a467a8e12c2ecb2f6cf919",
    "reference_vectors.json": "a5e8268e57cbbe93017696d3ef5f669f983bdcfeb7462e6716ab0b9968348689",
    "native_evidence.json": "b5a6378d851e02cf49fcf17e25b8ca883430c8e32c3dccb9f1b91b863b883f78",
}


def bits(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


def from_bits(value):
    return struct.unpack("<f", struct.pack("<I", value))[0]


def vector_bits(value):
    return [bits(value.x), bits(value.y)]


def dump(nodes):
    return [{"grid": list(node.grid), "next": list(node.next_grid), "distance": node.distance,
             "distance_to_final": node.distance_to_final, "has_next": node.has_next,
             "next_turn": vector_bits(node.next_turn)} for row in nodes for node in row]


class MovementReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.input = json.loads((ROOT / "reference_input.json").read_text())
        cls.reference = json.loads((ROOT / "reference_vectors.json").read_text())

    def test_float_geometry_bits_match_independent_csharp(self):
        self.assertEqual(len(self.input["geometry"]), 60)
        self.assertEqual(len(self.reference["geometry"]), 60)
        for source, expected in zip(self.input["geometry"], self.reference["geometry"]):
            with self.subTest(case=source["name"]):
                v = LocalVector2(from_bits(source["x"]), from_bits(source["y"]))
                target = LocalVector2(from_bits(source["target_x"]), from_bits(source["target_y"]))
                self.assertEqual(bits(v.squared_magnitude), expected["squared"])
                self.assertEqual(bits(v.magnitude), expected["magnitude"])
                self.assertEqual(vector_bits(v.normalized()), expected["normalized"])
                self.assertEqual(vector_bits(clamp_magnitude(v, from_bits(source["max"]))), expected["clamped"])
                self.assertEqual(list(local_to_grid(v)), expected["grid"])
                self.assertEqual(vector_is_zero(v), expected["is_zero"])
                self.assertEqual(vector_bits(normalize_direction_safely(v)), expected["safe_normalized"])
                self.assertEqual(check_distance(v, target, from_bits(source["radius"])), expected["check_distance"])

    def test_weighted_fifo_smoothing_turns_and_rays_match_csharp(self):
        self.assertEqual(len(self.input["paths"]), 29)
        self.assertEqual(len(self.reference["paths"]), 29)
        for source, expected in zip(self.input["paths"], self.reference["paths"]):
            with self.subTest(case=source["name"]):
                rows = [[NativeTileSnapshot(**tile) for tile in row] for row in source["rows"]]
                grid = NativeWalkPathGrid(rows, source="cross_language_explicit_fixture: " + source["name"])
                target = tuple(source["target"])
                raw = grid.next_map(target, smooth=False)
                self.assertEqual(dump(raw), expected["raw"])
                for ray, result in zip(source["rays"], expected["rays"]):
                    self.assertEqual(grid.raycast_bresenham(tuple(ray["start"]), tuple(ray["end"]), raw), result["clear"])
                smoothed = grid.next_map(target)
                grid.generate_next_turns(smoothed, target)
                self.assertEqual(dump(smoothed), expected["smooth"])

    def test_reference_and_native_evidence_pins(self):
        for name, expected in REFERENCE_PINS.items():
            self.assertEqual(hashlib.sha256((ROOT / name).read_bytes()).hexdigest(), expected, name)
        evidence = json.loads((ROOT / "native_evidence.json").read_text())
        self.assertFalse(evidence["client_runtime_compared"])
        self.assertFalse(evidence["autonomous_route_ready"])
        for entry in evidence["files"]:
            path = Path(entry["path"])
            if not path.is_absolute():
                path = ROOT / path
            self.assertEqual(hashlib.sha256(path.read_bytes()).hexdigest(), entry["sha256"], str(path))


if __name__ == "__main__":
    unittest.main()

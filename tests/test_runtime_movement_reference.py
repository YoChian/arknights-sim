"""Cross-language reconstructed arithmetic reference; not a live-client oracle."""
import hashlib
import json
from pathlib import Path
import struct
import unittest

from arknights_probe.movement import LocalVector2 as V, NativeTileSnapshot as T, NativeWalkPathGrid
from arknights_probe.runtime_movement import (deterministic_position, obstacle_avoid_force,
                                             MovementContext, NativeMoveController)

ROOT = Path(__file__).resolve().parents[1] / "evidence/runtime_movement"
PINS = {
    "RuntimeMovementReference.cs": "26c950ef341d010226db63e9a9329eec3a968efde2a16fcefa726779d84e15d7",
    "prepare_reference_input.py": "e97a0e4d8b4447402c8546e3964a89b2f793eab3b01d05be1ae43a70ce07bff1",
    "reference_input.json": "c2bd79026845fe780064cacc7e63f8d8bbedcd5b8a4d569eb7374b37af41d8a4",
    "reference_vectors.json": "e5f38edbcd9b3d0d23e825f57bfe61188e7cb0550961069b8341ed45e4d7cde7",
}


def value(bits):
    return struct.unpack("<f", struct.pack("<I", bits))[0]


def vector(bits):
    return V(value(bits[0]), value(bits[1]))


def bit_vector(v):
    return [struct.unpack("<I", struct.pack("<f", axis))[0] for axis in [v.x, v.y]]


def grid(rows):
    return NativeWalkPathGrid([[T(1 if t[0] else 0, 15, False, t[1]) for t in row] for row in rows],
                              source="independent C# explicit input fixture")


class RuntimeMovementReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        for name, expected in PINS.items():
            actual = hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            if actual != expected:
                raise AssertionError(f"Reference source changed; review before repinning: {name}")
        cls.inputs = json.loads((ROOT / "reference_input.json").read_text("utf-8"))
        cls.expected = json.loads((ROOT / "reference_vectors.json").read_text("utf-8"))
        for name in ("rounding", "avoidance", "controllers"):
            if len(cls.inputs[name]) != len(cls.expected[name]):
                raise AssertionError(f"Incomplete reference outputs: {name}")

    def test_single_double_decimal_rounding_bits(self):
        for index, (row, expected) in enumerate(zip(self.inputs["rounding"], self.expected["rounding"])):
            with self.subTest(index=index):
                self.assertEqual(bit_vector(deterministic_position(vector(row["position"]), row["enabled"])), expected)
        self.assertEqual(len(self.inputs["rounding"]), 320)

    def test_native_avoidance_branches_bits(self):
        for index, (row, expected) in enumerate(zip(self.inputs["avoidance"], self.expected["avoidance"])):
            with self.subTest(index=index):
                self.assertEqual(bit_vector(obstacle_avoid_force(grid(row["grid"]), vector(row["offset_position"]),
                    vector(row["foot_position"]), half_body_width=value(row["half_body_width"]))), expected)
        self.assertEqual(len(self.inputs["avoidance"]), 80)

    def test_native_controller_serial_frames_bits_and_consumption(self):
        for case_index, (case, expected) in enumerate(zip(self.inputs["controllers"], self.expected["controllers"])):
            t = case["context"]
            context = MovementContext("explicit independent reference", False, t["new_steering"],
                vector(t["foot_offset"]), value(t["initial_steering"]), value(t["max_force"]), value(t["half_body_width"]), False, False)
            controller = NativeMoveController(grid(case["grid"]), context)
            for frame, (step, golden) in enumerate(zip(case["steps"], expected)):
                with self.subTest(case=case_index, frame=frame):
                    movement, still = controller.calculate_delta(vector(step["direction"]), value(step["delta"]),
                        speed=value(step["speed"]), position=vector(step["position"]),
                        offset_position=vector(step["offset_position"]), can_move=step["can_move"])
                    self.assertEqual({"delta": bit_vector(movement), "velocity": bit_vector(controller.velocity),
                        "last_avoid": bit_vector(controller.last_avoid), "ticker": controller.ticker.remaining, "still": still}, golden)
            self.assertEqual(len(case["steps"]), len(expected))
        self.assertEqual(len(self.inputs["controllers"]), 80)
        self.assertEqual(sum(len(case["steps"]) for case in self.inputs["controllers"]), 2400)


if __name__ == "__main__":
    unittest.main()

from pathlib import Path
import json
import hashlib
import math
import struct
import unittest

from arknights_probe.fp import (
    FP, ONE, HALF, ZERO, SCALE, INT64_MIN, INT64_MAX, MAX_VALUE_RAW,
    MIN_VALUE_RAW, POSITIVE_INFINITY, NEGATIVE_INFINITY, NAN, binary32, FP_EVIDENCE,
)


REFERENCE = Path(__file__).resolve().parents[1] / "evidence" / "fp" / "reference_vectors.json"


class FixedPointTests(unittest.TestCase):
    def test_evidence_integrity_and_native_coverage(self):
        for name, digest in FP_EVIDENCE["file_sha256"].items():
            self.assertEqual(hashlib.sha256((REFERENCE.parent/name).read_bytes()).hexdigest(),digest,name)
        native=json.loads((REFERENCE.parent/"native_report.json").read_text("utf-8"))
        self.assertEqual(native["target_sha256"],FP_EVIDENCE["target_sha256"])
        self.assertEqual(len(native["functions"]),45)
        self.assertTrue(all(x["decompile_completed"] for x in native["functions"]))
        division=next(x for x in native["functions"] if x["token"]=="0x6000305")
        self.assertEqual(len(division["ranges"]),4)
        self.assertEqual(len(division["pe_unwind_components"]),4)
        self.assertFalse(FP_EVIDENCE["client_runtime_compared"])
        self.assertFalse(FP_EVIDENCE["hotfix_runtime_compared"])

    def test_independent_csharp_integer_reference(self):
        reference = json.loads(REFERENCE.read_text("utf-8"))
        self.assertEqual(reference["oracle_scope"], "independent C# translation of native instructions; not game runtime")
        self.assertEqual(reference["reference_pointer_bits"], 64)
        self.assertEqual(len(reference["pairs"]), 7073)
        for vector in reference["pairs"]:
            x, y = FP(int(vector["x"])), FP(int(vector["y"]))
            operations = {
                "add": x+y, "sub": x-y, "mul": x*y, "div": x/y,
                "overflow_add": x.overflow_add(y), "overflow_sub": x.overflow_sub(y),
            }
            for name, actual in operations.items():
                self.assertEqual(actual.raw, int(vector[name]), (name, x.raw, y.raw))
            if vector["mod"] is None:
                with self.assertRaises(ZeroDivisionError):
                    x % y
            else:
                self.assertEqual((x%y).raw, int(vector["mod"]), ("mod", x.raw, y.raw))
            self.assertEqual((x > y) - (x < y), vector["cmp"])

    def test_independent_csharp_unary_and_raw_to_float_reference(self):
        reference = json.loads(REFERENCE.read_text("utf-8"))
        self.assertEqual(len(reference["unary"]), 81)
        for vector in reference["unary"]:
            x = FP(int(vector["raw"]))
            for name, value in {"neg": -x, "abs": abs(x), "floor": x.floor(),
                                "ceiling": x.ceiling(), "round": x.round()}.items():
                self.assertEqual(value.raw, int(vector[name]), (name, x.raw))
            self.assertEqual(x.as_int(), vector["int"])
            self.assertEqual(x.as_long(), vector["int"])
            self.assertEqual(struct.pack("<f",x.as_float()).hex(), bytes.fromhex(vector["float_bits"])[::-1].hex(), ("as_float", x.raw))
            self.assertEqual(struct.pack("<d",x.as_double()).hex(), bytes.fromhex(vector["double_bits"])[::-1].hex(), ("as_double", x.raw))

    def test_independent_csharp_float_to_raw_reference(self):
        reference = json.loads(REFERENCE.read_text("utf-8"))
        self.assertEqual(len(reference["float32"]), 93)
        self.assertEqual(len(reference["double"]), 92)
        for vector in reference["float32"]:
            value = struct.unpack("<f",bytes.fromhex(vector["bits"])[::-1])[0]
            self.assertEqual(FP.from_float32(value).raw,int(vector["raw"]),("float32",vector["bits"]))
        for vector in reference["double"]:
            value = struct.unpack("<d",bytes.fromhex(vector["bits"])[::-1])[0]
            self.assertEqual(FP.from_double(value).raw,int(vector["raw"]),("double",vector["bits"]))

    def test_negative_conversion_and_rounding_modes(self):
        self.assertEqual(FP.from_float32(-0.1).as_int(),-1)
        self.assertEqual(FP.from_float32(-0.1).raw,-429496736)
        self.assertEqual(FP.from_double(-0.1).raw,-429496729)
        self.assertEqual((FP(-1)*HALF).raw,-1)  # multiplication floors
        for value, rounded in [(0.5,0),(1.5,2),(2.5,2),(-0.5,0),(-1.5,-2),(-2.5,-2)]:
            self.assertEqual(FP.from_double(value).round(),FP.from_int32(rounded))
        self.assertEqual((FP(1)/FP(2*SCALE)).raw,1)  # division half ties away
        self.assertEqual((FP(-1)/FP(2*SCALE)).raw,-1)

    def test_operator_overflow_zero_division_and_sentinels(self):
        self.assertEqual((FP(INT64_MAX)+FP(1)).raw,INT64_MIN)
        self.assertEqual((FP(INT64_MIN)-FP(1)).raw,INT64_MAX)
        self.assertEqual((ONE/ZERO),FP.from_int32(-1))
        self.assertEqual((ZERO/ZERO),FP.from_int32(-1))
        self.assertEqual((FP(INT64_MAX)/FP(1)).raw,MAX_VALUE_RAW)
        self.assertEqual((FP(INT64_MIN)/FP(1)).raw,MIN_VALUE_RAW)
        self.assertEqual((-FP(INT64_MIN)).raw,MAX_VALUE_RAW)
        self.assertEqual(abs(FP(INT64_MIN)).raw,MAX_VALUE_RAW)
        self.assertEqual((FP(INT64_MIN)%FP(-1)),ZERO)
        self.assertTrue(POSITIVE_INFINITY.is_infinity())
        self.assertTrue(NEGATIVE_INFINITY.is_infinity())
        self.assertTrue(NAN.is_nan())
        # These are raw equality predicates, not IEEE arithmetic propagation.
        self.assertEqual((POSITIVE_INFINITY+FP(1)),NAN)

    def test_binary32_time_input_and_repeated_steps_are_exact_raw(self):
        dt=FP.from_float32(1/30)
        self.assertEqual(dt.raw,143165584)
        self.assertEqual((dt*FP.from_int32(30)).raw,4294967520)
        self.assertNotEqual(dt,ONE/FP.from_int32(30))
        cumulative=ZERO
        for _ in range(30):
            cumulative+=dt
        self.assertEqual(cumulative.raw,4294967520)
        self.assertEqual(FP.from_float32(binary32(binary32(2*0.1)+7)).raw,30923763712)

    def test_raw_and_integer_boundaries(self):
        self.assertEqual(FP.from_int32(-(1<<31)).raw,INT64_MIN)
        self.assertEqual(FP.from_int64(1<<32),ZERO)
        self.assertEqual(FP.from_int64(INT64_MAX).raw,-SCALE)
        for value in [True,1.5,INT64_MIN-1,INT64_MAX+1,None]:
            with self.assertRaises(ValueError):
                FP(value)
        for value in [True,1.5,-(1<<31)-1,1<<31]:
            with self.assertRaises(ValueError):
                FP.from_int32(value)
        for value in [math.inf,-math.inf,math.nan,2**31]:
            self.assertEqual(FP.from_float32(value).raw,INT64_MIN)


if __name__ == "__main__":
    unittest.main()

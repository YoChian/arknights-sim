"""Torappu.FP arithmetic recovered from the installed Windows native artifact.

Evidence: native_v3/fixedpoint/{fp_results,fp_disassembly,fp_unwind}.json.
This reproduces static paths, including the client's unusual zero-division
result. It has not been compared against a running game or hotfix interpreter.
Floating conversions assume masked SSE exceptions and nearest-even MXCSR.
"""

from dataclasses import dataclass
import math
import struct

FRACTIONAL_BITS = 32
SCALE = 1 << FRACTIONAL_BITS
MASK64 = (1 << 64) - 1
INT64_MIN = -(1 << 63)
INT64_MAX = (1 << 63) - 1
MAX_VALUE_RAW = INT64_MAX - 1
MIN_VALUE_RAW = INT64_MIN + 2
POSITIVE_INFINITY_RAW = INT64_MAX
NEGATIVE_INFINITY_RAW = INT64_MIN + 1
NAN_RAW = INT64_MIN

FP_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "metadata_sha256": "d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f",
    "image": "Torappu.Common.dll",
    "type_definition_index": 38268,
    "native_functions": 45,
    "client_runtime_compared": False,
    "hotfix_runtime_compared": False,
    "sse_assumption": "masked exceptions; nearest-even floating arithmetic",
    "file_sha256": {
        "FPReference.cs": "ec50d0338883c6a4eb690d6da1fa7bedcc2b5cc58eaa5c10a12058014f126ec6",
        "reference_vectors.json": "60740a42b6f3db355107009d57da0c4f4bbe40c65eb048f0fa200cb56fa97bfe",
        "native_report.json": "e33f6349ad49e104fa82dc9276679427e5191059830423983d6bb1ca09483752",
        "native_disassembly.json": "503d12953eecbe58e4696abce8878d8d641658db5615814928d9093f408e5b2d",
        "native_types.json": "95319901ec246848e5750b00c10f23575a22baabc0f1c3ea9ed4a6b99de99a98",
        "metadata_declarations.json": "9f0ce8d5f88bfe40961b6426caf5bd76f1787e230c28ca754de1ab23a42920c4",
    },
}


def wrap64(value: int) -> int:
    """Unchecked x64 two's-complement result."""
    return ((value + (1 << 63)) & MASK64) - (1 << 63)


def binary32(value: float) -> float:
    """Round to an IEEE binary32 value, returned as a Python float."""
    value = float(value)
    try:
        return struct.unpack("<f", struct.pack("<f", value))[0]
    except OverflowError:
        return math.copysign(math.inf, value)


def _int_to_binary32(value: int) -> float:
    # Converting int64 through binary64 can double-round a binary32 midpoint.
    magnitude = abs(value)
    shift = max(0, magnitude.bit_length() - 24)
    if shift:
        high, low = divmod(magnitude, 1 << shift)
        half = 1 << (shift - 1)
        if low > half or (low == half and high & 1):
            high += 1
        magnitude = high << shift
    return float(-magnitude if value < 0 else magnitude)


def _cvtt_i64(value: float) -> int:
    # CVTTSS2SI/CVTTSD2SI return the integer-indefinite bit pattern when
    # invalid is masked. The target's live MXCSR has not been observed.
    if not math.isfinite(value) or value < INT64_MIN or value >= 1 << 63:
        return INT64_MIN
    return math.trunc(value)


def _divide_raw(left: int, right: int) -> int:
    """Exact uint64 loop from op_Division, not a generic saturated quotient."""
    if right == 0:
        return -SCALE
    remainder, divider = abs(left), abs(right)
    bit_position = 33
    quotient = 0
    while not divider & 15 and bit_position > 3:
        divider >>= 4
        bit_position -= 4
    while remainder and bit_position >= 0:
        shift = min(64 - remainder.bit_length(), bit_position)
        remainder = (remainder << shift) & MASK64
        bit_position -= shift
        part, remainder = divmod(remainder, divider)
        quotient = (quotient + (part << bit_position)) & MASK64
        if part & ~(MASK64 >> bit_position):
            return MIN_VALUE_RAW if (left ^ right) < 0 else MAX_VALUE_RAW
        remainder = (remainder << 1) & MASK64
        bit_position -= 1
    quotient = ((quotient + 1) & MASK64) >> 1
    return wrap64(-quotient if (left ^ right) < 0 else quotient)


@dataclass(frozen=True, order=True, slots=True)
class FP:
    """One signed 64-bit raw value, with 32 fractional bits."""

    raw: int

    def __post_init__(self):
        if type(self.raw) is not int or not INT64_MIN <= self.raw <= INT64_MAX:
            raise ValueError("raw must be a signed int64")

    @classmethod
    def from_raw(cls, value: int) -> "FP":
        return cls(value)

    @classmethod
    def from_int32(cls, value: int) -> "FP":
        if type(value) is not int or not -(1 << 31) <= value < 1 << 31:
            raise ValueError("value must be a signed int32")
        return cls(value << 32)

    @classmethod
    def from_int64(cls, value: int) -> "FP":
        if type(value) is not int or not INT64_MIN <= value <= INT64_MAX:
            raise ValueError("value must be a signed int64")
        return cls(wrap64(value << 32))

    @classmethod
    def from_float32(cls, value: float) -> "FP":
        return cls(_cvtt_i64(binary32(binary32(value) * SCALE)))

    @classmethod
    def from_double(cls, value: float) -> "FP":
        return cls(_cvtt_i64(float(value) * SCALE))

    def as_int(self) -> int:
        return self.raw >> 32

    def as_long(self) -> int:
        return self.raw >> 32

    def as_float(self) -> float:
        return _int_to_binary32(self.raw) * (2.0 ** -32)

    def as_double(self) -> float:
        return float(self.raw) * (2.0 ** -32)

    def __add__(self, other: "FP") -> "FP":
        if not isinstance(other, FP):
            return NotImplemented
        return FP(wrap64(self.raw + other.raw))

    def __sub__(self, other: "FP") -> "FP":
        if not isinstance(other, FP):
            return NotImplemented
        return FP(wrap64(self.raw - other.raw))

    def __mul__(self, other: "FP") -> "FP":
        if not isinstance(other, FP):
            return NotImplemented
        return FP(wrap64((self.raw * other.raw) >> 32))

    def __truediv__(self, other: "FP") -> "FP":
        if not isinstance(other, FP):
            return NotImplemented
        return FP(_divide_raw(self.raw, other.raw))

    def __mod__(self, other: "FP") -> "FP":
        if not isinstance(other, FP):
            return NotImplemented
        if other.raw == 0:
            raise ZeroDivisionError("native IDIV by zero")
        magnitude = abs(self.raw) % abs(other.raw)
        return FP(-magnitude if self.raw < 0 else magnitude)

    def __neg__(self) -> "FP":
        return FP(MAX_VALUE_RAW if self.raw == INT64_MIN else -self.raw)

    def __abs__(self) -> "FP":
        return FP(MAX_VALUE_RAW if self.raw == INT64_MIN else abs(self.raw))

    def sign(self) -> int:
        return (self.raw > 0) - (self.raw < 0)

    def floor(self) -> "FP":
        return FP((self.raw >> 32) << 32)

    def ceiling(self) -> "FP":
        return FP(wrap64(self.floor().raw + (SCALE if self.raw & 0xffffffff else 0)))

    def round(self) -> "FP":
        fraction = self.raw & 0xffffffff
        high = self.floor().raw
        if fraction > SCALE // 2 or (fraction == SCALE // 2 and high & SCALE):
            high += SCALE
        return FP(wrap64(high))

    def overflow_add(self, other: "FP") -> "FP":
        # These separate helpers saturate to int64 extrema (the sentinel bits).
        return FP(min(INT64_MAX, max(INT64_MIN, self.raw + other.raw)))

    def overflow_sub(self, other: "FP") -> "FP":
        return FP(min(INT64_MAX, max(INT64_MIN, self.raw - other.raw)))

    def is_infinity(self) -> bool:
        return self.raw in (POSITIVE_INFINITY_RAW, NEGATIVE_INFINITY_RAW)

    def is_nan(self) -> bool:
        return self.raw == NAN_RAW


ZERO = FP(0)
ONE = FP(SCALE)
HALF = FP(SCALE // 2)
MAX_VALUE = FP(MAX_VALUE_RAW)
MIN_VALUE = FP(MIN_VALUE_RAW)
POSITIVE_INFINITY = FP(POSITIVE_INFINITY_RAW)
NEGATIVE_INFINITY = FP(NEGATIVE_INFINITY_RAW)
NAN = FP(NAN_RAW)

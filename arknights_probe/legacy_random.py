"""Translation of this PC snapshot's Torappu.LegacyRandom native algorithm.

This is independent of DeclarationProbeEnv and has no hot-patch, factory,
battle or live-client equivalence claim. It is *not* System.Random.
"""
from __future__ import annotations

INT_MIN = -(1 << 31)
INT_MAX = (1 << 31) - 1
MBIG = INT_MAX
MSEED = 161803398
ALGORITHM_ID = "torappu_legacy_random_583b04ff_sample1860e0e90_v1"

NATIVE_RNG_EVIDENCE = {
    "kind": "static_native_decompilation",
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "report_path": r"D:\Repo\.rea-tools\arknights-pc\native_v2\focused_results_round3.json",
    "report_sha256": "f48a1ac56f11064265e0ebb7dbc12f7815f180e36a00e9d64a53a4febb568a72",
    "reference_source_sha256": "3f3daa216291e2b54466094f95706ac7cfa857db53950af7334edc04a2f13627",
    "reference_vectors_sha256": "642f90baf3ed87c29c340eda5c71e9906449fc7a09e14cc61865d61de538bf02",
    "seeded_ctor": "0x186505240",
    "sample": "0x1860e0e90",
    "next": "0x1860e0e40",
    "next_max": "0x186505190",
    "next_min_max": "0x186505090",
    "next_double_dispatch": "0x185549bb0",
    "random_factory_seeded": "0x1867323a0",
    "limits": "Names are analyst candidates matched to metadata/pointers and PE unwind. "
              "Factory type 0 selects the LegacyRandom seeded ctor statically; hot-patch/virtual dispatch "
              "in a running client and complete battle RNG consumption remain unverified.",
}


def i32(value: int) -> int:
    """Unchecked signed int32 conversion, including intermediate arithmetic."""
    return ((value + (1 << 31)) & 0xFFFFFFFF) - (1 << 31)


def _int32(value, label):
    if type(value) is not int or not INT_MIN <= value <= INT_MAX:
        raise ValueError(f"{label} must be a signed int32")
    return value


class LegacyRandom:
    """Recovered subtractive generator with inextp=31 and no MBIG correction."""

    def __init__(self, seed: int):
        seed = _int32(seed, "seed")
        self._seed = seed
        self._sample_count = 0
        self._array = [0] * 56
        # Native unchecked abs preserves INT_MIN rather than mapping it to INT_MAX.
        subtraction = seed if seed >= 0 else i32(-seed)
        mj = i32(MSEED - subtraction)
        self._array[55] = mj
        mk = 1
        for i in range(1, 55):
            ii = (21 * i) % 55
            self._array[ii] = mk
            mk = i32(mj - mk)
            if mk < 0:
                mk = i32(mk + MBIG)
            mj = self._array[ii]
        for _ in range(4):
            for i in range(1, 56):
                value = i32(self._array[i] - self._array[1 + (i + 30) % 55])
                if value < 0:
                    value = i32(value + MBIG)
                self._array[i] = value
        self._inext = 0
        self._inextp = 31

    def sample(self) -> float:
        self._inext += 1
        if self._inext > 55:
            self._inext = 1
        self._inextp += 1
        if self._inextp > 55:
            self._inextp = 1
        value = i32(self._array[self._inext] - self._array[self._inextp])
        if value < 0:
            value = i32(value + MBIG)
        # Deliberately no `if value == MBIG: value -= 1` branch.
        self._array[self._inext] = value
        self._sample_count += 1
        return float(value) * (1.0 / MBIG)

    def next_double(self) -> float:
        """Local call to recovered Sample; runtime virtual dispatch is not modeled."""
        return self.sample()

    def next(self, max_value: int | None = None) -> int:
        if max_value is None:
            return int(self.sample() * MBIG)
        max_value = _int32(max_value, "max_value")
        if max_value < 0:
            raise ValueError("max_value must be nonnegative")
        # max_value==0 still consumes a sample in the recovered overload.
        return int(self.sample() * max_value)

    def next_range(self, min_value: int, max_value: int) -> int:
        """Recovered narrow-range overload; unsupported wide ranges fail closed.

        The native range<2 fast return consumes no sample. Its wide/overflow
        paths are deliberately not exposed by this component.
        """
        min_value = _int32(min_value, "min_value")
        max_value = _int32(max_value, "max_value")
        if min_value > max_value:
            raise ValueError("min_value must not exceed max_value")
        difference = max_value - min_value
        if difference > INT_MAX:
            raise ValueError("Wide/overflowing int32 ranges are not supported")
        if difference < 2:
            return min_value
        return min_value + int(self.sample() * difference)

    def snapshot(self) -> dict:
        """JSON-safe local checkpoint, detached from mutable generator storage."""
        return {"format_version": 1, "algorithm_id": ALGORITHM_ID, "initial_seed": self._seed,
                "seed_array": self._array.copy(), "inext": self._inext, "inextp": self._inextp,
                "sample_count": self._sample_count}

    def restore(self, state: dict) -> None:
        """Restore our own checkpoint format after atomic structural validation.

        This does not import a client save or authenticate state reachability.
        """
        fields = {"format_version", "algorithm_id", "initial_seed", "seed_array", "inext", "inextp", "sample_count"}
        if type(state) is not dict or set(state) != fields:
            raise ValueError("Unsupported RNG checkpoint fields")
        if type(state["format_version"]) is not int or state["format_version"] != 1 or state["algorithm_id"] != ALGORITHM_ID:
            raise ValueError("Incompatible RNG checkpoint algorithm/version")
        seed = _int32(state["initial_seed"], "initial_seed")
        values = state["seed_array"]
        if type(values) is not list or len(values) != 56:
            raise ValueError("seed_array must contain 56 signed int32 values")
        values = [_int32(value, f"seed_array[{i}]") for i, value in enumerate(values)]
        if values[0] != 0:
            raise ValueError("Unused seed_array[0] must be zero")
        x, p, count = state["inext"], state["inextp"], state["sample_count"]
        if type(x) is not int or type(p) is not int or not 0 <= x <= 55 or not 1 <= p <= 55 or (p - x) % 55 != 31:
            raise ValueError("Invalid ring indices or offset")
        if type(count) is not int or count < 0:
            raise ValueError("sample_count must be a nonnegative integer")
        self._seed, self._array, self._inext, self._inextp, self._sample_count = seed, values, x, p, count

    @classmethod
    def from_snapshot(cls, state: dict) -> "LegacyRandom":
        generator = cls.__new__(cls)
        generator.restore(state)
        return generator

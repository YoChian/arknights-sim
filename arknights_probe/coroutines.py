"""Static RuntimeHandler stack semantics; no live Unity runtime comparison.

Native RuntimeHandler.MoveNext 0x18065ff70 treats an empty newly entered
IEnumerator as a frame boundary. Ordinary Python ``yield from`` does not.
"""
from __future__ import annotations

from collections.abc import Iterator
import math
from typing import Callable

from .fp import binary32

NEXT_FRAME = object()


class CoroutineRunner:
    def __init__(self, root: Iterator):
        if not isinstance(root, Iterator):
            raise TypeError("root must be an iterator")
        self.stack = [(True, root)]
        self.ticks = 0

    @property
    def active(self) -> bool:
        return bool(self.stack)

    def tick(self) -> bool:
        """Advance one native simulator tick; return whether the stack remains."""
        self.ticks += 1
        operations = 0
        while self.stack:
            operations += 1
            if operations > 100000:
                raise RuntimeError("Coroutine failed to yield within the diagnostic bound")
            first, iterator = self.stack.pop()
            try:
                current = next(iterator)
            except StopIteration:
                if first:
                    break
                continue
            self.stack.append((False, iterator))
            if isinstance(current, Iterator):
                self.stack.append((True, current))
                continue
            # Current == null or an ordinary marker both suspend one frame.
            break
        return self.active


def float_wait_frames(delay: float, delta_float: float,
                      round_to_int: Callable[[float], int] = round) -> int:
    """Float wait: binary32 division then max(1,nearest ties-even).

    Native helper 0x18059e290 was initially labeled CeilToInt, but its actual
    instructions implement nearest ties-even. Nonfinite/huge diagnostic inputs
    fail closed instead of emulating unchecked native conversion accidentally.
    """
    delay, delta = binary32(delay), binary32(delta_float)
    if not math.isfinite(delay) or not math.isfinite(delta) or delta <= 0:
        raise ValueError("Wait needs finite delay and positive finite delta")
    quotient = binary32(delay / delta)
    if not math.isfinite(quotient) or abs(quotient) > 2147483646:
        raise ValueError("Wait frame count outside supported native int32 range")
    return max(1, round_to_int(quotient))


def fixed_seconds(delay: float, delta_float: float,
                  round_to_int: Callable[[float], int] = round):
    for _ in range(float_wait_frames(delay, delta_float, round_to_int)):
        yield NEXT_FRAME


def wait_while(predicate: Callable[[], bool]):
    """Native WaitWhileFixed 0x1806619a0: yield before the first test."""
    while True:
        yield NEXT_FRAME
        if not predicate():
            return


def serial_queue(items, executor, delta_float: float,
                 round_to_int: Callable[[float], int] = round):
    """DefaultWaveHandler 0x18094e650: wait planned time differences serially."""
    planned = binary32(0.0)
    for item in items:
        time = binary32(item["time"])
        if planned < time:
            yield fixed_seconds(binary32(time - planned), delta_float, round_to_int)
        if item.get("isValid", True):
            yield executor(item)
        planned = time

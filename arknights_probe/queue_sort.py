"""Recovered ordering at GameAssembly 0x184547860, scoped to pure queue keys.

This midpoint-pivot Quicksort deliberately exchanges equal keys. It is not
Python's stable sort, nor a promise about a hotfixed/live runtime.
"""
from __future__ import annotations

import math
import struct
from collections.abc import Callable, Iterable
from typing import TypeVar

T = TypeVar("T")
SORT_ALGORITHM_ID = "arknights_583b04ff_queue_midpoint_quicksort_184547860_v1"
NATIVE_SORT_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "sort_entry": "0x184547860",
    "sort_range_sha256": "7ceb2c4945dd9b1ad05fe9b99336c414c74d1004301ae11475b9488719e7472d",
    "wrapper": "0x184543930",
    "comparator": "0x180950a00",
    "single_compare_to": "0x185ed0a10",
    "report_path": r"D:\Repo\.rea-tools\arknights-pc\native_v3\sorting\REPORT.md",
    "scope": "Static reconstruction of comparator-based queue sort; no live client or hotfix oracle.",
}


def binary32(value: float | int) -> float:
    """Round a scalar key once to the Single value stored in the native queue."""
    if type(value) not in (int, float):
        raise TypeError("Queue time key must be a Python int or float")
    try:
        return struct.unpack("<f", struct.pack("<f", float(value)))[0]
    except (OverflowError, struct.error) as exc:
        raise ValueError("Queue time cannot be represented as a binary32 value") from exc


def single_compare_to(left: float, right: float) -> int:
    """System.Single.CompareTo total order; NaN precedes every non-NaN.

    Arguments are already binary32 values. NaNs compare equal; signed zero
    compares equal. Infinite values retain the usual numeric ordering.
    """
    if left < right:
        return -1
    if left > right:
        return 1
    if left == right:
        return 0
    if math.isnan(left):
        return 0 if math.isnan(right) else -1
    return 1


def native_queue_sort(items: Iterable[T], key: Callable[[T], float | int]) -> list[T]:
    """Return queue items in recovered native order, without changing input.

    Original append order must be provided. Do not add an index/id tie breaker:
    equal-key swaps are part of the recovered algorithm. A pure key is read
    once per item, emulating the immutable float stored in each native record.
    """
    work = [(item, binary32(key(item))) for item in items]

    def quick_sort(left: int, right: int) -> None:
        while left < right:
            i, j = left, right
            pivot = work[left + (right - left) // 2][1]
            while True:
                # Bounds and comparison directions follow the raw instructions:
                # 0x184547905 / 0x184547a06 and signed JNS after comparator.
                while i < right and single_compare_to(work[i][1], pivot) < 0:
                    i += 1
                while j > left and single_compare_to(pivot, work[j][1]) < 0:
                    j -= 1
                if i > j:
                    break
                work[i], work[j] = work[j], work[i]
                i += 1
                j -= 1
            # Original code recursively sorts left, then loops over right.
            if left < j:
                quick_sort(left, j)
            if i >= right:
                return
            left = i

    if len(work) > 1:
        quick_sort(0, len(work) - 1)
    return [item for item, _ in work]

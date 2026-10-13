"""C# reconstruction comparison, never a running-client order oracle."""
from pathlib import Path
import struct

from .data import read_json, require, sha256
from .queue_sort import native_queue_sort, single_compare_to

REFERENCE = Path(__file__).resolve().parents[1] / "evidence/sorting/reference_vectors.json"
VECTOR_SHA256 = "3788877f048fc8cf06df84429885d3ffc760601891385cd4bcc0b3bce1c8626d"
SOURCE_SHA256 = "93068657ebbc01ce4b020df63b24e83127bfa7e905bdb2e4b825ec5110d78456"


def verify_sort_reference():
    require(sha256(REFERENCE) == VECTOR_SHA256, "Sort reconstruction vectors changed")
    require(sha256(REFERENCE.parent / "QueueSortReference.cs") == SOURCE_SHA256, "Sort C# reconstruction source changed")
    reference = read_json(REFERENCE)
    require(reference["kind"] == "independent C# reconstruction reference; not game oracle", "Sort reference scope changed")
    def value(bits):
        return struct.unpack("<f", struct.pack("<I", bits))[0]
    identities = 0
    host_different = 0
    for case in reference["cases"]:
        items = [{"id": i, "time": value(bits)} for i, bits in enumerate(case["keys_binary32_bits"])]
        result = [item["id"] for item in native_queue_sort(items, key=lambda item: item["time"])]
        require(result == case["recovered_ids"], f"Sort reference mismatch {case['name']}")
        identities += len(result)
        host_different += case["host_list_sort_ids"] != result
    for case in reference["single_compare_to_cases"]:
        require(single_compare_to(value(case["left_bits"]), value(case["right_bits"])) == case["comparison"], "Single.CompareTo reference mismatch")
    return {"healthy": True, "scope": reference["kind"], "case_count": len(reference["cases"]),
            "identity_checks": identities, "single_compare_to_checks": len(reference["single_compare_to_cases"]),
            "host_list_sort_different_cases": host_different, "vector_sha256": VECTOR_SHA256,
            "client_runtime_compared": False}

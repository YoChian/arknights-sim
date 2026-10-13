"""Prepare short call-target PE bodies without loading the whole image or Java."""
from pathlib import Path
import hashlib, json, re, struct, sys

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[1]
sys.path.insert(0, str(ROOT / "tools/python"))
import capstone

addresses = {
    "0x1807b31e0": ("RawMovementHelper", "IntegerSignOrAbsCallTarget"),
    "0x180a7f380": ("Torappu.Battle.Enemy", "get_offsetMapPosition"),
    "0x180a7cf50": ("Torappu.Battle.Enemy", "get_footMapPosition"),
    "0x1808980e0": ("Torappu.Battle.DirectionCursor", "get_alwaysCheckCurrentPoint"),
    "0x1804d57f0": ("RawMovementHelper", "DoubleFractionAndIntegerSplit"),
    "0x1804d3200": ("RawMovementHelper", "DoubleFloorCallTarget"),
    "0x1804d58c0": ("RawMovementHelper", "DoubleCeilingCallTarget"),
    "0x18000cec0": ("RawMovementHelper", "DoubleRoundToEven"),
    "0x185ebb460": ("System.Math", ".cctor"),
    "0x181e04370": ("Torappu.PeriodicTicker", "Next"),
    "0x180af54b0": ("Torappu.Battle.DeterministicUtil", "ProcessVector3"),
}
pe = next(x for x in json.loads((ROOT / "core/pe_inventory.json").read_text()) if x["path"].endswith("GameAssembly.dll"))
base = int(pe["image_base"], 16)


def fileoff(rva, n):
    for section in pe["sections"]:
        delta = rva - int(section["virtual_address"], 16)
        if 0 <= delta and delta + n <= section["raw_bytes"]:
            return section["raw_offset"] + delta
    raise ValueError("unbacked RVA")


with Path(pe["path"]).open("rb") as stream:
    assert hashlib.file_digest(stream, "sha256").hexdigest() == pe["sha256"]

    def read(offset, n):
        stream.seek(offset)
        data = stream.read(n)
        assert len(data) == n
        return data

    nt = struct.unpack("<I", read(0x3c, 4))[0]
    er, size = struct.unpack("<II", read(nt + 24 + 112 + 3 * 8, 8))
    pdata = read(fileoff(er, size), size)
    triples = [struct.unpack_from("<III", pdata, index * 12) for index in range(size // 12)]
    by_start = {piece[0]: piece for piece in triples}
    parents = {}
    for piece in triples:
        header = read(fileoff(piece[2], 4), 4)
        if header[0] >> 3 & 4:
            parent = struct.unpack("<III", read(fileoff(piece[2], 4) + 4 + ((header[2] + 1) // 2) * 4, 12))
            assert by_start[parent[0]] == parent
            parents[piece[0]] = parent[0]

    def root(address):
        seen = set()
        while address in parents:
            assert address not in seen
            seen.add(address)
            address = parents[address]
        return address

    groups = {}
    for piece in triples:
        groups.setdefault(root(piece[0]), []).append(piece)
    targets = []
    for va, (type_name, method_name) in addresses.items():
        start = int(va, 16) - base
        native_leaves = {
            "0x181e04370": [(0x181e04370, 0x181e04382)],
            "0x1804d57f0": [(0x1804d57f0, 0x1804d58b3)],
            "0x1804d3200": [(0x1804d3200, 0x1804d3212), (0x1804d3220, 0x1804d32be), (0x1804eefb0, 0x1804eefb7)],
            "0x1804d58c0": [(0x1804d58c0, 0x1804d58d2), (0x1804d58e0, 0x1804d598a), (0x1804eefd0, 0x1804eefd7)],
        }
        if va in native_leaves:
            pieces = [(begin-base,end-base,0) for begin,end in native_leaves[va]]
            boundary = "decoded complete native conditional leaf/CPU dispatch targets; padding excluded; nonfinite error tail outside finite movement scope"
        elif start in groups:
            pieces = groups[start]
            boundary = "exact recursive PE UNW_FLAG_CHAININFO group"
        else:
            # Only these two selected native bodies lack pdata and each is a
            # straight-line bounded leaf, not a branch-delimited guessed span.
            engine = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
            data = read(fileoff(start, 128), 128)
            end = None
            for instruction in engine.disasm(data, base + start):
                assert not instruction.mnemonic.startswith("j") and instruction.mnemonic != "call", va
                if instruction.mnemonic == "ret":
                    end = instruction.address - base + instruction.size
                    break
            assert end is not None
            pieces = [(start, end, 0)]
            boundary = "decoded straight-line native leaf through first RET; no calls or branches"
        ranges = []
        for begin, end, unwind in pieces:
            raw = read(fileoff(begin, end - begin), end - begin)
            ranges.append({"start": hex(base + begin), "end": hex(base + end - 1),
                           "source_file_offset": fileoff(begin, end - begin),
                           "source_sha256": hashlib.sha256(raw).hexdigest(),
                           "unwind_rva": hex(unwind), "chained": begin in parents})
        targets.append({"name": re.sub("[^A-Za-z0-9_]", "_", type_name + "_" + method_name),
                        "display_name": type_name + "." + method_name, "address": va,
                        "end_address": hex(base + max(p[1] for p in pieces) - 1),
                        "file_offset": fileoff(start, 1), "metadata_method_index": None,
                        "range_provenance": boundary, "ranges": ranges})

destination = OUT / (sys.argv[1] if len(sys.argv) > 1 else "input_raw_helpers.json")
destination.write_text(json.dumps({"target_sha256": pe["sha256"], "image_base": pe["image_base"],
                                    "targets": targets, "scope": "static raw followups; no target execution"}, indent=2))
print(json.dumps({"targets": len(targets), "output": str(destination)}))

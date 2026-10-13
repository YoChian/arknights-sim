"""Bounded RIP-relative method usage references; no target execution."""
import bisect
import hashlib
import json
from pathlib import Path
import re
import struct

OUT = Path(__file__).resolve().parent
BASE = OUT.parents[1]
HELPER = BASE / "native_v5" / "lifecycle" / "prepare.py"
ns = {"__file__": str(HELPER)}
exec(compile(HELPER.read_text("utf-8").split("selection=json.loads")[0], str(HELPER), "exec"), ns)
blob, pe = ns["b"], ns["pe"]
imagebase = int(pe["image_base"], 16)
targets = {72143: "Scheduler._OnUnitDestroyed", 72145: "Scheduler._OnEnemyRecycled"}
slots = {}
for idx, name in targets.items():
    word = struct.pack("<I", (3 << 29) | (idx << 1) | 1)
    for section in pe["sections"]:
        if section["name"] != ".data":
            continue
        start, end = section["raw_offset"], section["raw_offset"] + section["raw_bytes"]
        at = start
        while (at := blob.find(word, at, end)) >= 0:
            va = imagebase + int(section["virtual_address"], 16) + at - start
            if at % 8 == 0:
                slots[va] = {"method_index": idx, "name": name, "file_offset": at,
                             "usage_word": word.hex(), "raw_bytes8": blob[at:at+8].hex()}
            at += 4
starts = sorted(ns["by_start"])
rows = ns["rows"]
matches = []
pattern = re.compile(b"[\x48\x4c][\x8b\x8d][\x05\x0d\x15\x1d\x25\x2d\x35\x3d]....", re.DOTALL)
for section in pe["sections"]:
    if section["name"] not in (".text", "il2cpp"):
        continue
    start = section["raw_offset"]
    for match in pattern.finditer(blob, start, start + section["raw_bytes"]):
        off = match.start()
        va = imagebase + int(section["virtual_address"], 16) + off - start
        slot = va + 7 + struct.unpack_from("<i", blob, off + 3)[0]
        if slot not in slots:
            continue
        i = bisect.bisect_right(starts, va - imagebase) - 1
        triple = ns["by_start"][starts[i]] if i >= 0 else None
        root = ns["root"](triple[0]) if triple and triple[0] <= va-imagebase < triple[1] else None
        matches.append({"instruction_va": hex(va), "raw_bytes7": blob[off:off+7].hex(),
            "usage_slot_va": hex(slot), "usage_identity": slots[slot],
            "unwind_root": hex(imagebase + root) if root is not None else None,
            "candidate_aliases": [f"{x['type']}.{x['method']}" for x in rows
                                  if root is not None and x["candidate_va"] == hex(imagebase+root)]})
output = {"target_sha256": pe["sha256"], "helper_source_path": str(HELPER),
          "helper_source_sha256": hashlib.sha256(HELPER.read_bytes()).hexdigest(),
          "method_usage_slots": [{"va": hex(k), **v} for k,v in slots.items()],
          "rip_references": matches,
          "limits": ["Recognized x64 MOV/LEA RIP-relative patterns only; not all xrefs.",
                     "Source bytes plus metadata usage identity locate candidates; callers require semantic follow-up."]}
(OUT/"subscription_callers.json").write_text(json.dumps(output,indent=2)+"\n", "utf-8")
print(json.dumps(output, indent=2))

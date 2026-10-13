"""Retain exact RIP-relative double literals used by finite rounding paths."""
from pathlib import Path
import hashlib
import json
import re
import struct

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[1]
raw_path = OUT / "raw_raw_helpers.json"
raw = json.loads(raw_path.read_text("utf-8"))
pe = next(x for x in json.loads((ROOT / "core/pe_inventory.json").read_text()) if x["path"].endswith("GameAssembly.dll"))
base = int(pe["image_base"], 16)
records = []
with Path(pe["path"]).open("rb") as stream:
    assert hashlib.file_digest(stream, "sha256").hexdigest() == raw["target_sha256"]
    for fn in raw["functions"]:
        if "Double" not in fn["display_name"]:
            continue
        for part in fn["components"]:
            for ins in part["instructions"]:
                match = re.search(r"qword ptr \[rip \+ (0x[0-9a-f]+)\]", ins["operands"])
                if not match or ins["mnemonic"] not in ("movsd", "comisd", "ucomisd", "addsd", "subsd"):
                    continue
                va = int(ins["address"], 16) + len(bytes.fromhex(ins["bytes"])) + int(match[1], 16)
                for section in pe["sections"]:
                    delta = va - base - int(section["virtual_address"], 16)
                    if 0 <= delta and delta + 8 <= section["raw_bytes"]:
                        offset = section["raw_offset"] + delta
                        break
                else:
                    raise ValueError("Unbacked literal")
                stream.seek(offset)
                data = stream.read(8)
                records.append({"function": fn["display_name"], "instruction": ins["address"],
                    "literal_va": hex(va), "file_offset": offset, "bytes8": data.hex(),
                    "double_value": struct.unpack("<d", data)[0], "sha256": hashlib.sha256(data).hexdigest()})
result = {"target_sha256": pe["sha256"], "raw_source_path": str(raw_path),
    "raw_source_sha256": hashlib.sha256(raw_path.read_bytes()).hexdigest(),
    "round_limit_cctor_immediate_bits": "0x4341c37937e08000", "round_limit_value": 1e16,
    "records": records, "scope": "static finite Double rounding paths; no execution"}
(OUT / "rounding_literals.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"literal_reads": len(records), "values": sorted(set(str(x["double_value"]) for x in records))}))

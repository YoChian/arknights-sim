"""Bind retained method-info slots to native method specs and generic args.

Read-only PE/metadata inspection. Shared machine-code addresses alone do not
identify generic methods. This records the caller's actual encoded slots.
"""
from pathlib import Path
import hashlib
import json
import struct

ROOT = Path(__file__).resolve().parent
HELPER = ROOT / "export_native_fields.py"
ns = {"__file__": str(HELPER)}
exec(HELPER.read_text("utf-8").split("roots=")[0], ns)
b, meta, offset = ns["b"], ns["meta"], ns["offset"]
words = [int(word, 16) for word in ns["registration"]["registration"]["words"]]


def generic_inst(index):
    if index < 0:
        return None
    assert index < words[2]
    ptr_off = offset(words[3] + index * 8, 8)
    ptr = struct.unpack_from("<Q", b, ptr_off)[0]
    record_off = offset(ptr, 16)
    count, args_ptr = struct.unpack_from("<QQ", b, record_off)
    assert 0 < count < 64
    args_off = offset(args_ptr, count * 8)
    args = struct.unpack_from("<" + "Q" * count, b, args_off)
    return {"index": index, "pointer_record_file_offset": ptr_off,
            "record_va": hex(ptr), "record_file_offset": record_off,
            "raw_bytes16": b[record_off:record_off + 16].hex(),
            "argument_pointer_file_offset": args_off,
            "argument_pointers": [hex(p) for p in args],
            "arguments": [{"name": ns["native_type_address"](p)["name"],
                           "definition_index": ns["native_type_address"](p).get("definition_index"),
                           "address": hex(p)} for p in args]}


records = []
for address, call_target in [(0x188938418, 0x184d14820),
                             (0x188904ab8, 0x1844f9140),
                             (0x188904cf8, 0x1844f9740)]:
    slot_off = offset(address, 8)
    encoded = struct.unpack_from("<Q", b, slot_off)[0]
    kind, index = encoded >> 29, (encoded & 0x1fffffff) >> 1
    assert kind == 6 and index < words[8]
    spec_off = offset(words[9] + index * 12, 12)
    method_index, class_inst, method_inst = struct.unpack_from("<3i", b, spec_off)
    method = ns["methods"][method_index]
    records.append({"slot_va": hex(address), "slot_file_offset": slot_off,
                    "slot_raw_bytes8": b[slot_off:slot_off + 8].hex(),
                    "encoded": hex(encoded), "usage_kind": kind, "method_spec_index": index,
                    "method_spec_file_offset": spec_off,
                    "method_spec_raw_bytes12": b[spec_off:spec_off + 12].hex(),
                    "method_definition_index": method_index,
                    "declaring_type": ns["fullname"](method[1]),
                    "method_name": ns["text"](method[0]), "token": hex(method[5]),
                    "parameter_count": method[9],
                    "class_generic_inst": generic_inst(class_inst),
                    "method_generic_inst": generic_inst(method_inst),
                    "caller_bound_machine_target": hex(call_target)})

output = {"target_sha256": hashlib.sha256(b).hexdigest(),
          "metadata_sha256": hashlib.sha256(meta).hexdigest(), "records": records,
          "limits": ["Static caller-bound generic identity, not runtime/hotfix observation",
                     "Does not infer argument layout or algorithm from a shared address"]}
(ROOT / "generic_identities.json").write_text(json.dumps(output, ensure_ascii=False, indent=2), "utf-8")
print(json.dumps([{k: r[k] for k in ["method_definition_index", "declaring_type", "method_name", "parameter_count", "caller_bound_machine_target"]}
                  | {"class_args": r["class_generic_inst"]["arguments"] if r["class_generic_inst"] else None,
                     "method_args": r["method_generic_inst"]["arguments"] if r["method_generic_inst"] else None}
                 for r in records], ensure_ascii=False, indent=2))

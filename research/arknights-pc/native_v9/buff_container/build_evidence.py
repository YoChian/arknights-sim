"""Source-bound audit and owned evidence copies; never invokes target code."""
from pathlib import Path
import hashlib, json, shutil

OUT = Path(__file__).parent
ROOT = OUT.parents[1]
EVIDENCE = Path(r"D:\Repo\arknights-sim\evidence\buff_container")
helper = ROOT / "native_v4/resources/export_native_fields.py"
code = helper.read_text("utf8")
start, end = code.index("roots={"), code.index("selected=set(roots)")
code = code[:start] + "roots={1420,1421,1422,10085,10086,10087,10088,10089,10090,10201}\n" + code[end:]
(OUT / "export_native_fields.py").write_text(code, "utf8")
exec(compile(code, str(OUT / "export_native_fields.py"), "exec"), {"__file__":str(OUT / "export_native_fields.py")})
scope = {"__file__": str(OUT / "prepare.py")}
exec((OUT / "prepare.py").read_text("utf8").split("selection=json.loads")[0], scope)
binary, image_base = scope["b"], scope["base"]
reused = []
used_sources = []
plans = [
    ("native_v5/core/results_round1.json", ["0x1806fadf0"]),
    ("native_v5/core/results_round2.json", ["0x180668f20", "0x18067e5b0", "0x18067f9d0", "0x18067bb10", "0x1806872e0", "0x180687830", "0x180681cc0", "0x180acbdb0"]),
    ("native_v5/core/results_round3.json", ["0x18067f8e0", "0x180687e80", "0x18068d4b0"]),
    ("native_v7/npc/results_round2.json", ["0x1806873c0","0x180686200"]),
    ("native_v7/npc/results_round3.json", ["0x180675d90", "0x180664a90", "0x180686200"]),
    ("native_v6/damage/results_round1.json", ["0x1806795e0"]),
    ("native_v8/npc_actions/results_round1.json", ["0x180692370"]),
]
for relative, addresses in plans:
    source = ROOT / relative
    document = json.loads(source.read_text("utf8"))
    found = [f for f in document["functions"] if f["address"] in addresses]
    reused += [f | {"reused_source":str(source)} for f in found]
    used_sources.append({"path": str(source), "sha256":hashlib.sha256(source.read_bytes()).hexdigest(),
                         "selected_addresses": [f["address"] for f in found]})
(OUT / "results_reused.json").write_text(json.dumps({"functions":reused,"sources":used_sources}, indent=2), "utf8")

checks = []
counts = {"new_functions":0,"new_ranges":0,"new_bytes":0,"reused_functions":len(reused),
          "reused_ranges":0,"reused_bytes":0,"raw_functions":0,"raw_ranges":0,"raw_bytes":0}
for path in [OUT / ("results_round%d.json" % n) for n in range(1,5)] + [OUT / "results_reused.json"]:
    document = json.loads(path.read_text("utf8"))
    is_new = path.name != "results_reused.json"
    prefix = "new" if is_new else "reused"
    if is_new:
        counts["new_functions"] += len(document["functions"])
    for function in document["functions"]:
        assert function["decompile_completed"] and function["imported_memory_matches_source"], function["name"]
        for r in function["ranges"]:
            start, end = int(r["start"],16), int(r["end"],16)+1
            off = scope["rva"](start-image_base,end-start)
            raw = binary[off:off+end-start]
            match = hashlib.sha256(raw).hexdigest() == r["source_sha256"]
            assert match, (function["name"], r)
            checks.append({"function":function["address"],"kind":prefix,"start":r["start"],"bytes":len(raw),"match":match})
            counts[prefix+"_ranges"] += 1
            counts[prefix+"_bytes"] += len(raw)
raw = json.loads((OUT / "raw_helpers.json").read_text("utf8"))
counts["raw_functions"] = len(raw["functions"])
for function in raw["functions"]:
    for r in function["ranges"]:
        raw_bytes = bytes.fromhex(r["bytes_hex"])
        start, end = int(r["start"],16), int(r["end"],16)+1
        off = scope["rva"](start-image_base,end-start)
        assert off == r["source_file_offset"] and binary[off:off+len(raw_bytes)] == raw_bytes
        assert hashlib.sha256(raw_bytes).hexdigest() == r["source_sha256"]
        assert b"".join(bytes.fromhex(x["bytes"]) for x in r["instructions"]) == raw_bytes
        counts["raw_ranges"] += 1
        counts["raw_bytes"] += len(raw_bytes)
        checks.append({"function":function["address"],"kind":"raw","start":r["start"],"bytes":len(raw_bytes),"match":True})

old = Path(r"D:\Repo\arknights-sim\evidence\npc_actions\manifest.json")
old_doc = json.loads(old.read_text("utf8"))
pins = old_doc["files"]
assert all(hashlib.sha256(Path(x["path"]).read_bytes()).hexdigest() == x["sha256"] for x in pins)
summary = {"target_sha256": scope["pe"]["sha256"], "metadata_sha256":"d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f",
           "counts":counts,"all_current_original_ranges_match":True,"all_imported_ranges_match":True,
           "v8_manifest_unchanged_files":len(pins),"checks":checks,"reference_vectors":192,"tests":32,
           "limits":["Original static bytes and imported Ghidra bytes are checked; no target execution",
                     "C# is a source-owned cross-language reference, not a client oracle",
                     "Prepared Reset/filter/override/status/pool/audio context is explicit"]}
(OUT / "audit_summary.json").write_text(json.dumps(summary,indent=2),"utf8")
resource = ROOT / "native_v7/npc/resource_inputs.json"
shutil.copyfile(resource,OUT / "resource_inputs.json")
enums = ROOT / "native_v5/devices/enum_constants.json"
shutil.copyfile(enums,OUT / "enum_constants.json")
for path in OUT.iterdir():
    if path.suffix in [".json", ".cs"] and path.name not in ["raw_initial.json"]:
        shutil.copyfile(path,EVIDENCE/path.name)
print(json.dumps({"counts":counts,"v8_pins_unchanged":len(pins)}))

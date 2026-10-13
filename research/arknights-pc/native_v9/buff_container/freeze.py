"""Fix owned evidence/direct dependencies after completed tests and audit."""
from pathlib import Path
import json, hashlib, shutil

OUT = Path(__file__).parent
ROOT = OUT.parents[1]
SIM = Path(r"D:\Repo\arknights-sim")
EVIDENCE = SIM / "evidence/buff_container"
shutil.copyfile(OUT / "REPORT.md", EVIDENCE / "REPORT.md")
paths = set()
for root in (OUT, EVIDENCE):
    paths.update(p for p in root.iterdir() if p.is_file() and p.name != "manifest.json" and
                 p.suffix in (".json", ".py", ".cs", ".c", ".md", ".exe"))
paths.update(SIM / p for p in ("arknights_probe/buff_container.py", "tests/test_buff_container.py",
                             "arknights_probe/npc_actions.py", "arknights_probe/fp.py",
                             "evidence/npc_actions/resource_inputs.json", "evidence/npc_actions/manifest.json"))
for relative in [
    "core/pe_inventory.json", "core/Assembly-CSharp_candidate_method_map.json",
    "core/Torappu.Common_candidate_method_map.json", "core/ThirdPartyAssembly_candidate_method_map.json",
    "core/mscorlib_candidate_method_map.json", "native_v2/labels.tsv",
    "native_v3/fixedpoint/native_types.json", "native_v3/fixedpoint/inspect_native_types.py",
    "native_v4/resources/export_native_fields.py", "native_v5/devices/enum_constants.json",
    "native_v6/targeting/export_native_fields.py", "native_v6/targeting/inspect_generic_identities.py",
    "native_v7/targeting/export_native_fields.py", "native_v7/targeting/inspect_generic_dispatch.py",
    "native_v7/targeting/generic_identities.json", "native_v7/npc/resource_inputs.json",
    "native_v8/npc_actions/prepare.py",
]:
    paths.add(ROOT / relative)
for round_number in range(1,5):
    paths.add(ROOT / ("native_v9/core/results_round%d.json" % round_number))
    paths.add(ROOT / ("native_v9/core/raw_round%d.json" % round_number))
for source in json.loads((OUT / "results_reused.json").read_text("utf8"))["sources"]:
    paths.add(Path(source["path"]))
paths.add(Path(r"D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll"))
paths.add(Path(r"D:\Hypergryph Launcher\games\Arknights\Arknights_Data\il2cpp_data\Metadata\global-metadata.dat"))
files = [{"path":str(p), "sha256":hashlib.sha256(p.read_bytes()).hexdigest()} for p in sorted(paths)]
audit = json.loads((OUT / "audit_summary.json").read_text("utf8"))
manifest = {"component":"native_v9_buff_container", "frozen":True, "files":files,
            "tests":32,"independent_csharp_reference_vectors":192,"all_passed":True,
            "source_counts":audit["counts"],"old_v8_action_pins_unchanged":audit["v8_manifest_unchanged_files"],
            "scope":"Selected initialized NPC Buff membership/reentry; explicit creation filters, override, attribute, pool, owner and audio providers",
            "target_execution":False,"network":False}
serialized = json.dumps(manifest,indent=2)
for path in [OUT / "manifest.json", EVIDENCE / "manifest.json"]:
    path.write_text(serialized,"utf8")
assert all(hashlib.sha256(Path(r["path"]).read_bytes()).hexdigest() == r["sha256"] for r in files)
print(json.dumps({"manifest":str(EVIDENCE/"manifest.json"),"files":len(files),
                  "sha256":hashlib.sha256((EVIDENCE/"manifest.json").read_bytes()).hexdigest(),
                  "module_sha256":hashlib.sha256((SIM/"arknights_probe/buff_container.py").read_bytes()).hexdigest()}))

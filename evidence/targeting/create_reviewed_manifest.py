"""One-time initial manifest creation after static/source/test review.

Refuses to replace an existing manifest. Normal verification is read-only;
changed evidence requires an explicit review, not rerunning this file.
"""
import hashlib
import json
from pathlib import Path

ROOT=Path(__file__).resolve().parent
SIM=ROOT.parents[1]
ANALYSIS=Path(r"D:\Repo\.rea-tools\arknights-pc")
OUT=ANALYSIS/"native_v6"/"targeting"
TARGET_SHA="583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5"
METADATA_SHA="d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f"


def read(path):
    return json.loads(path.read_text("utf-8"))


def digest(path):
    with path.open("rb") as f:
        return hashlib.file_digest(f,"sha256").hexdigest()


def write(path,value):
    path.write_text(json.dumps(value,indent=2,ensure_ascii=False),"utf-8")


def create():
    manifest_path=ROOT/"native_evidence.json"
    if manifest_path.exists():
        raise FileExistsError("Reviewed pins already exist. Do not refresh automatically.")
    selected=read(OUT/"selection.json")+read(OUT/"selection_extra.json")
    wanted={x["address"].lower():x for x in selected}
    reports=[]
    recovered=[]
    for version in ["native_v5","native_v6"]:
        for n in range(1,4):
            path=ANALYSIS/version/"core"/f"results_round{n}.json"
            data=read(path)
            assert data["target_sha256"]==TARGET_SHA
            assert all(f["decompile_completed"] and f["imported_memory_matches_source"] and
                       all(x["match"] for x in f["imported_range_checks"]) for f in data["functions"])
            matched=[]
            if version=="native_v6":
                for f in data["functions"]:
                    if f["address"].lower() not in wanted:continue
                    matched.append(f["address"])
                    recovered.append({"request":wanted[f["address"].lower()],"report_path":str(path),
                        "native_display_name":f["display_name"],"metadata_method_index":f["metadata_method_index"],
                        "decompile_completed":True,"all_imported_ranges_match":True,
                        "ranges":f["ranges"],"imported_range_checks":f["imported_range_checks"]})
            reports.append({"path":str(path),"functions":len(data["functions"]),
                "ranges":sum(len(f["ranges"]) for f in data["functions"]),
                "all_imported_ranges_match":True,"targeting_requested_addresses":matched,
                "count_scope":"whole shared report totals; targeting coverage is separately listed"})
    assert {x["request"]["address"].lower() for x in recovered}==set(wanted)
    write(OUT/"recovered_functions.json",{"scope":"51 selected unique addresses, including two preexisting parent BObject entries",
        "target_sha256":TARGET_SHA,"records":recovered})
    prefab=read(OUT/"prefab_selector.json")
    prefab["scope"]="Verified resource identity/flags and native local bounding collider declarations; world Physics2D overlap and native ALL order remain external"
    prefab["native_local_collider_declarations"]=[
        {"minimum":[-.5,-2.5],"size":[1,5],"center":[0,0]},
        {"minimum":[-1.5,-1.5],"size":[3,3],"center":[0,0]},
        {"minimum":[-2.5,-.5],"size":[5,1],"center":[0,0]}]
    prefab["unknown_contexts"]=["live rangeId reset/cache/extensions and transform chain",
        "target UBody/Unity collider continuous world shape",
        "Unity Physics2D touch/buffer/order/synchronization",
        "initialized owner/masks/status/HitRange providers",
        "native ALL SortedSet gap/comparison/ties/extra-mode",
        "live hotfix pointer state"]
    write(OUT/"prefab_selector.json",prefab)
    vectors=read(ROOT/"reference_vectors.json")
    counts={"component_tests":23,"reference_tests":2,
        "geometry_cases":len(vectors["geometry"]),
        "box_bit_patterns":sum(len(x["box_bits"]) for x in vectors["geometry"]),
        "collector_cases":len(vectors["collectors"]),
        "collector_decisions":sum(len(x["decisions"]) for x in vectors["collectors"]),
        "admitted_collector_uids":sum(len(x["collector"]) for x in vectors["collectors"]),
        "targeting_selected_addresses":len(wanted),
        "short_raw_helpers":len(read(OUT/"raw_helpers.json")["functions"])}
    write(ROOT/"reference_comparison.json",{"scope":"independent source-owned C# vs Python, not native/client oracle",
        "all_tested_cases_passed":True,"counts":counts,
        "tests":"python -X utf8 -m unittest tests.test_targeting tests.test_targeting_reference -q",
        "external_inputs":["physics result and order","frozen owner/status/provider context","ALL reversal permutation fixture"],
        "runtime_battle_validated":False,"physics_overlap_generated":False,"native_all_order_generated":False})
    paths=[SIM/"arknights_probe"/x for x in ["targeting.py","movement.py","fp.py"]]
    paths+=[SIM/"tests"/x for x in ["test_targeting.py","test_targeting_reference.py"]]
    paths+=[ROOT/x for x in ["TargetingReference.cs","TargetingReference.exe","generate_reference_input.py",
        "reference_input.json","reference_vectors.json","reference_comparison.json","verify_evidence.py",
        "create_reviewed_manifest.py","REPORT.md"]]
    paths+=[OUT/x for x in ["selection.json","selection_extra.json","native_fields.json","field_offsets.json",
        "export_native_fields.py","prefab_selector.json","generic_identities.json","inspect_generic_identities.py",
        "inspect_short_helpers.py","raw_helpers.json","recovered_functions.json","NOTES.md"]]
    paths+=[Path(x["path"]) for x in reports]
    paths+=[ANALYSIS/"native_v6"/"core"/f"raw_round{n}.json" for n in range(1,4)]
    paths+=[ANALYSIS/"native_v5"/"resources"/x for x in
        ["rule_prefab_subtrees.json","range_table.json","range_provenance.json","range_asset_provenance.json"]]
    paths+=[ANALYSIS/"native_v5"/"devices"/"enum_constants.json",
        ANALYSIS/"native_v4"/"resources"/"native_fields.json",
        ANALYSIS/"native_v3"/"fixedpoint"/"native_types.json",
        ANALYSIS/"native_v3"/"fixedpoint"/"inspect_native_types.py",
        ANALYSIS/"native_v5"/"lifecycle"/"prepare.py",
        ANALYSIS/"core"/"pe_inventory.json"]
    paths+=[ANALYSIS/"core"/(x+"_candidate_method_map.json") for x in
        ["Assembly-CSharp","Torappu.Common","mscorlib","UnityEngine.CoreModule","UnityEngine.Physics2DModule"]]
    game=Path(r"D:\Hypergryph Launcher\games\Arknights")
    binary=game/"GameAssembly.dll"
    metadata=game/"Arknights_Data"/"il2cpp_data"/"Metadata"/"global-metadata.dat"
    assert digest(binary)==TARGET_SHA and digest(metadata)==METADATA_SHA
    paths += [binary,metadata,Path(prefab["source_game_bundle_pin"]["path"])]
    assert digest(paths[-1])==prefab["source_game_bundle_pin"]["sha256"]
    paths=list(dict.fromkeys(paths))
    files=[{"path":str(p),"bytes":p.stat().st_size,"sha256":digest(p)} for p in paths]
    write(manifest_path,{"manifest_version":1,
        "scope":"conditional sktok_ore native range declarations/admission/collector, external Physics2D and ALL snapshots, independent C# translation comparisons",
        "target_sha256":TARGET_SHA,"metadata_sha256":METADATA_SHA,
        "runtime_battle_validated":False,"client_runtime_compared":False,"hotfix_runtime_compared":False,
        "targeting_component_available":True,"physics_overlap_generated":False,
        "native_all_order_generated":False,"native_all_membership_validated":False,
        "battle_ready":False,"reference_scope":vectors["scope"],"counts":counts,
        "native_reports":reports,"files":files})
    return {"manifest":str(manifest_path),"files":len(files),"counts":counts}


if __name__=="__main__":
    print(json.dumps(create(),indent=2))

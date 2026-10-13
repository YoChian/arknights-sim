"""Freeze only this new evidence package and existing inputs; never repin old files."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
reused=[
 'core/pe_inventory.json','core/Assembly-CSharp_candidate_method_map.json',
 'native_v7/core/results_round2.json','native_v7/core/results_round3.json',
 'native_v7/core/raw_round2.json','native_v7/core/raw_round3.json',
 'native_v7/core/selection_round2.json','native_v7/core/selection_round3.json',
 'native_v5/resources/rule_prefab_subtrees.json','native_v5/resources/scene_templates.json',
 'native_v4/resources/exact_resource_inputs.json','native_v5/devices/enum_constants.json',
 'native_v6/skill/enum_constants.json',
 'native_v3/timeline/round3/Torappu_Battle_AsyncUtil_WaitForFixedSeconds_0x600fa85.c',
 'native_v3/timeline/round3/_WaitForFixedSeconds_d__5_MoveNext_0x600fab4.c',
 'native_v5/core/round1/Torappu_Battle_Enemy_OnFinish_0x6012af2.c',
 'native_v5/core/round1/Torappu_Battle_Entity_OnFinish_0x601045e.c',
 'native_v5/core/round2/Torappu_Battle_Enemy__AssignTalent_0x6012aec.c',
 'native_v5/core/round3/Torappu_Battle_Buff__RunActions_0x600fee4.c',
 'native_v5/lifecycle/raw_helpers.json','native_v5/lifecycle/callback_identity.json',
 'native_v5/lifecycle/REPORT.md','native_v5/lifecycle/manifest.json',
 'native_v6/damage/prior_native_results.json','native_v6/damage/native_report.json',
 'native_v6/damage/raw_helpers.json','native_v6/damage/manifest.json',
]
paths=set(OUT.rglob('*.py'))|set(OUT.rglob('*.c'))|set(OUT.rglob('*.md'))|set(OUT.rglob('*.json'))
paths.discard(OUT/'manifest.json')
paths.update(ROOT/p for p in reused)
for p in list(paths):assert p.is_file(),p
# Original resource binary pins are independently retained as inputs.
resources=json.loads((OUT/'resource_inputs.json').read_text('utf8'))
pins=[p['source_pin'] for p in resources['prefabs']]+[resources['template_source_pin']]
for p in pins:
 path=Path(p['path']);assert sha(path)==p['sha256'];paths.add(path)
for p in resources['input_sources']:
 for key,hkey in [('source','source_sha256'),('body_path','body_sha256')]:
  path=Path(p[key]);assert sha(path)==p[hkey];paths.add(path)
pe=next(p for p in json.loads((ROOT/'core/pe_inventory.json').read_text('utf8')) if p['path'].endswith('GameAssembly.dll'))
game=Path(pe['path']);assert sha(game)==pe['sha256'];paths.add(game)
meta=game.parent/'Arknights_Data/il2cpp_data/Metadata/global-metadata.dat'
expected='d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f'
assert sha(meta)==expected;paths.add(meta)
audit=json.loads((OUT/'audit_summary.json').read_text('utf8'))
manifest={'scope':'static_NPC_declaration_and_native_branch_recovery',
 'target_sha256':pe['sha256'],'metadata_sha256':expected,
 'game_launched':False,'client_runtime_compared':False,'npc_component_implemented':False,
 'npc_battle_ready':False,'old_evidence_modified':False,
 'counts':{'ghidra_functions':sum(x['functions'] for x in audit['ghidra']),
           'ghidra_imported_ranges':sum(x['imported_ranges'] for x in audit['ghidra']),
           'ghidra_imported_bytes':sum(x['bytes'] for x in audit['ghidra']),
           'raw_function_records':sum(x['functions'] for x in audit['raw']),
           'raw_ranges':sum(x['ranges'] for x in audit['raw']),
           'raw_bytes':sum(x['bytes'] for x in audit['raw'])},
 'errata':['Entity+0x26 means disappeared, separate from Enemy.Options.unharmful',
           'InstantKill Finish7 excludes ON_OWNER_KILLED',
           'normal InstantKill false result short-circuits following lock/Clear actions'],
 'files':[{'path':str(p.resolve()),'sha256':sha(p)} for p in sorted(paths,key=lambda p:str(p).lower())]}
(OUT/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
for p in manifest['files']:assert sha(Path(p['path']))==p['sha256']
print(json.dumps({'files':len(manifest['files']),'manifest':str(OUT/'manifest.json'),
                 'manifest_sha256':sha(OUT/'manifest.json'),'counts':manifest['counts']},indent=2))

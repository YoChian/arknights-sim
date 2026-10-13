"""Freeze v7 preparation-only evidence; previous v5/v6 files remain unchanged."""
from pathlib import Path
import hashlib,json
OUT=Path(__file__).parent;BASE=OUT.parents[1];SIM=Path(r'D:\Repo\arknights-sim');EVIDENCE=SIM/'evidence/skill_preparation'
files={p.resolve() for p in OUT.rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.name not in ['native_manifest.json','verification.json']}
files.update(p.resolve() for p in EVIDENCE.rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.name!='native_manifest.json')
files.update([SIM/'arknights_probe/skill_preparation.py',SIM/'tests/test_skill_preparation.py',SIM/'arknights_probe/fp.py'])
inputs=json.loads((OUT/'resource_inputs.json').read_text())
files.update(Path(s['path']) for s in inputs['sources']);files.update(Path(p['source_pin']['path']) for p in inputs['prefabs'])
files.update([BASE/'native_v6/skill/native_fields.json',BASE/'native_v6/skill/enum_constants.json',BASE/'native_v6/skill/raw_followups.json',
 BASE/'native_v6/skill/existing/91797_Torappu_Battle_Abilities_AbstractAnimatedAbility_GetDuration.c',
 BASE/'native_v6/skill/existing/91846_Torappu_Battle_Abilities_EasyToStartAbility_OnCastStart.c',
 BASE/'native_v6/skill/existing/72894_Torappu_Battle_CastSkill_AssignData.c',
 BASE/'native_v6/skill/round2/91780_Torappu_Battle_Abilities_AbstractAnimatedAbility_get_cooldown.c',
 BASE/'native_v3/fixedpoint/native_types.json',BASE/'native_v3/fixedpoint/inspect_native_types.py',
 BASE/'native_v4/resources/export_native_fields.py',BASE/'native_v4/resources/inspect_attribute_meta.py',
 BASE/'native_v4/resources/metadata_blob.py',BASE/'core/Assembly-CSharp_candidate_method_map.json'])
for n in [1,3,4]:
 files.update(BASE/'native_v7/core'/f'{prefix}_round{n}.json' for prefix in ['input','raw','results'])
inventory=json.loads((BASE/'core/pe_inventory.json').read_text());pe=next(p for p in inventory if p['path'].endswith('GameAssembly.dll'))
native=[];entries=[]
for n in [1,3,4]:
 for r in json.loads((OUT/f'results_round{n}.json').read_text()):
  f=r['result'];entries.append({'address':f['address'],'metadata_method_index':f['metadata_method_index'],'display_name':f['display_name'],'ranges':len(f['ranges']),'source_matches_import':f['imported_memory_matches_source']})
  for span in f['ranges']:
   native.append({'entry_address':f['address'],'start':span['start'],'end_exclusive':hex(int(span['end'],16)+1),'source_file_offset':span['source_file_offset'],'source_sha256':span['source_sha256']})
raw=json.loads((OUT/'raw_preparation.json').read_text())
for f in raw['functions']:
 for span in f['ranges']:
  native.append({'entry_address':f['address'],**{k:span[k] for k in ['start','end_exclusive','source_file_offset','source_sha256']}})
unique={(r['start'],r['end_exclusive'],r['source_sha256']):r for r in native}
manifest={'format':'native_v7_skill_preparation_manifest_v1','target_path':pe['path'],'target_sha256':pe['sha256'],
 'metadata_sha256':'d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f',
 'files':[{'path':str(p.resolve()),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in sorted(files,key=str)],
 'native_selected_entries':entries,'native_ranges':list(unique.values()),
 'test_count':12,'cross_language_vectors':18,'client_runtime_compared':False,
 'scope':'Static default SPECIFIED altar preparation; external owner/Unity initialization/global and physics context required'}
(OUT/'native_manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
(EVIDENCE/'native_manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print(json.dumps({'files':len(manifest['files']),'selected':len(entries),'fresh_selected_ranges':sum(e['ranges'] for e in entries),'raw_functions':len(raw['functions']),'unique_native_ranges':len(unique),'module_sha256':hashlib.sha256((SIM/'arknights_probe/skill_preparation.py').read_bytes()).hexdigest()}))

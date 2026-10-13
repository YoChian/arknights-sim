"""Pin owned evidence, sources, and all exact accepted native range bytes."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1];REPO=Path(r'D:\Repo\arknights-sim')
EVID=REPO/'evidence/skill_runtime'; EVID.mkdir(exist_ok=True)
files=set();records={};rejected=[]
def addfile(path):
 p=Path(path);assert p.is_file(),p;files.add(p)
def addrecord(r,source):
 if r['address']=='0x182648530':
  rejected.append({'address':r['address'],'source':str(source),'reason':'Provisional address points inside exact unwind root1826484b0..18264853f and starts at an instruction interior; not an independent function. Never used as behavior evidence.'});return
 records[r['address']]=r
for p in [OUT/'existing_native.json',OUT/'results_round1.json',OUT/'results_round2.json',OUT/'results_round3.json']:
 addfile(p)
 for row in json.loads(p.read_text()):
  addfile(row['source']);addfile(row['c_file']);addrecord(row['record'],row['source'])
# Additional manually cached inherited phase methods with exact source identity.
extra_indices={33272,33274,91784,91797,66697,77699}
extra_rows=[]
for root in [BASE/'native_v5/core',BASE/'native_v6/core']:
 for p in sorted(root.glob('results_round*.json')):
  for r in json.loads(p.read_text())['functions']:
   if r.get('metadata_method_index') not in extra_indices:continue
   if not r.get('decompile_completed') or not r.get('imported_memory_matches_source'):continue
   addfile(p);addrecord(r,p)
   extra_rows.append({'source':str(p),'metadata_method_index':r['metadata_method_index'],'address':r['address']})
for p in OUT.glob('existing/*.c'): addfile(p)
# Actual FP wait overload, not a similarly named float overload.
p=BASE/'native_v3/timeline/results_round3.json';addfile(p)
wait_raw={r['address']:r for r in json.loads((OUT/'raw_followups.json').read_text())['functions']}
for r in json.loads(p.read_text())['functions']:
 if r['token'] in ['0x600fa85','0x600fab4']:
  assert r.get('decompile_completed')
  # Historical v3 lacked imported-memory hash annotations. Verify boundaries
  # against our fresh exact PE chain groups and pin the fresh raw bytes.
  raw_record=wait_raw[r['address']]
  # v3 stored inclusive end addresses. Fresh PE ranges are end-exclusive.
  assert {(q['start'],int(q['end'],16)+1) for q in r['ranges']}=={(q['start'],int(q['end_exclusive'],16)) for q in raw_record['ranges']}
  r['ranges']=[dict(q,end=q['end_exclusive']) for q in raw_record['ranges']]
  addrecord(r,p)
  cfile=BASE/'native_v3/timeline/round3'/f"{r['name']}.c";addfile(cfile)
for name in ['declarations.json','native_fields.json','field_offsets.json','enum_constants.json',
             'selection.json','selection_extra.json','selection_round3.json','virtual_dispatch_raw.json',
             'raw_followups.json','raw_followups.py','reference_report.json','REPORT.md',
             'build_manifest.py','verify_reference.py']:
 addfile(OUT/name)
for name in ['altar_context.json','rule_prefab_subtrees.json','scene_templates.json']:
 addfile(BASE/'native_v5/resources'/name)
for path in [BASE/'native_v5/devices/raw_helpers.json',BASE/'native_v5/core/input_round5.json',BASE/'native_v5/core/raw_round5.json',
             REPO/'arknights_probe/skill_runtime.py',REPO/'tests/test_skill_runtime.py',
             REPO/'arknights_probe/fp.py',REPO/'arknights_probe/devices.py',REPO/'arknights_probe/coroutines.py']:
 addfile(path)
# frame_runtime.py is parent-owned and still being integrated: the skill module
# imports its stable public interface; parent frame manifest pins its final file.
for p in EVID.iterdir():
 if p.is_file() and p.name not in ['native_manifest.json','SkillCycleReference.exe']:addfile(p)
ranges={}
for r in records.values():
 for q in r['ranges']:
  end_exclusive=int(q['end_exclusive'],16) if 'end_exclusive' in q else int(q['end'],16)+1
  z=end_exclusive-int(q['start'],16)
  normalized={'start':q['start'],'size':z,'file_offset':q.get('source_file_offset',q.get('file_offset')),'sha256':q.get('source_sha256',q.get('sha256'))}
  assert normalized['file_offset'] is not None and normalized['sha256']
  ranges[(normalized['file_offset'],z)]=normalized
for p in [OUT/'virtual_dispatch_raw.json',OUT/'raw_followups.json']:
 for r in json.loads(p.read_text())['functions']:
  records[r['address']]=r
  for q in r['ranges']:
   z=int(q['end_exclusive'],16)-int(q['start'],16)
   ranges[(q['file_offset'],z)]={'start':q['start'],'size':z,'file_offset':q['file_offset'],'sha256':q['sha256']}
pe=next(p for p in json.loads((BASE/'core/pe_inventory.json').read_text()) if p['path'].endswith('GameAssembly.dll'))
manifest={'format':'native_v6_skill_component_manifest_v1','target_path':pe['path'],'target_sha256':pe['sha256'],
 'metadata_sha256':'d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f',
 'files':[{'path':str(p),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in sorted(files,key=str)],
 'accepted_native_functions':len(records),'native_ranges':sorted(ranges.values(),key=lambda q:q['file_offset']),
 'rejected_entries':rejected,'extra_inherited_methods':extra_rows,
 'coverage':'Conditional post-Init/AssignData/Attach altar AUTO cycle. Prepared timing/eligibility and absent modifier/event effects are explicit fixture inputs. No real client or hotfix runtime comparison.',
 'dependencies':'SharedCoroutineSimulator public API is parent-owned; its final implementation/source pin is covered by the frame-runtime manifest.'}
for p in [OUT/'native_manifest.json',EVID/'native_manifest.json']:
 p.write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print(json.dumps({'files':len(files),'accepted_native_functions':len(records),'native_ranges':len(ranges),'rejected_entries':len(rejected)}))

"""Audit exact current ranges and freeze the new NPC actions evidence only."""
from pathlib import Path
import json,hashlib,struct,shutil
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
REPO=Path(r'D:\Repo\arknights-sim');E=REPO/'evidence/npc_actions'
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def read(p):return json.loads(Path(p).read_text('utf8'))
def write(name,obj):
 t=json.dumps(obj,ensure_ascii=False,indent=2)+'\n';(OUT/name).write_text(t,encoding='utf8');(E/name).write_text(t,encoding='utf8')
pe=next(p for p in read(ROOT/'core/pe_inventory.json') if p['path'].endswith('GameAssembly.dll'))
b=Path(pe['path']).read_bytes();assert hashlib.sha256(b).hexdigest()==pe['sha256']
def offset(va,n):
 for s in pe['sections']:
  d=va-int(pe['image_base'],16)-int(s['virtual_address'],16)
  if 0<=d and d+n<=s['raw_bytes']:return s['raw_offset']+d
 raise ValueError(hex(va))
counts=[];checks=[]
for name in ['results_round1.json','results_round2.json']:
 d=read(OUT/name);n=bytes_n=0
 for f in d['functions']:
  assert f['decompile_completed'] and f['imported_memory_matches_source']
  for r in f['ranges']:
   size=int(r['end'],16)+1-int(r['start'],16);off=r['source_file_offset']
   assert hashlib.sha256(b[off:off+size]).hexdigest()==r['source_sha256']
  for r in f['imported_range_checks']:
   assert r['match'];n+=1;bytes_n+=r['bytes']
 counts.append({'collection':name,'functions':len(d['functions']),'ranges':n,'bytes':bytes_n,'all_match':True})
raw=read(OUT/'raw_helpers.json');rn=rb=0
for f in raw['functions']:
 for r in f['ranges']:
  size=int(r['end_exclusive'],16)-int(r['start'],16);off=r['source_file_offset'];body=b[off:off+size]
  assert hashlib.sha256(body).hexdigest()==r['source_sha256']
  for i in r['instructions']:
   start=int(i['address'],16)-int(r['start'],16);code=bytes.fromhex(i['bytes']);assert body[start:start+len(code)]==code
  checks.append({'function':f['name'],'start':r['start'],'bytes':size,'source_sha256':r['source_sha256'],'match':True})
  rn+=1;rb+=size
raw_info={'collection':'raw_helpers.json','functions':len(raw['functions']),'ranges':rn,'bytes':rb,'all_match':True}
# Resolve the method-definition usage word in MathUtil's GE delegate cctor.
va=0x18885a820;off=offset(va,4);word=struct.unpack_from('<I',b,off)[0]
assert word>>29==3 and (word&0x1fffffff)>>1==220331
proof={'target_sha256':pe['sha256'],
 'FP_GE_delegate':{'cctor':'0x1866e6e50','method_usage_slot':hex(va),'source_file_offset':off,
  'encoded_word':hex(word),'method_definition_index':220331,'native_method':'0x1866e4ba0',
  'assignment_static_offset':'0x28','GetCompareFuncFP_parameter':3,
  'semantics':'left.raw >= unchecked(right.raw - EN5.raw), inclusive',
  'epsilon_origin':'MathUtil.cctor copies FP static+0x78 (FP.EN5) to MathUtil static+0; recovered FP.EN5 raw=42950'},
 'Blackboard_floor':{'TryGetInt':'0x182320170','double_dispatch':'0x1804d3200',
  'SSE4':'0x1804eefb0 ROUNDSD xmm0,xmm0,9 (floor, suppress exceptions)',
  'scalar':'0x1804d3220 truncates positive magnitude and decrements non-integral negative values',
  'scope':'finite Single values whose floor is within Int32; nonfinite/out-of-range reject'},
 'context_fields':{'source':'0x10 ContextPtrStack<Entity>','target':'0x18 ContextPtrStack<Entity>',
  'buff':'0x20 ContextPtrStack<Buff>','mainTarget':'0x50 ContextValueStack<Entity>',
 'guard':'DuplicateAll takes resolved Snapshot and pushes new ObjectPtrs; stale source/target/buff duplicates as null. Setters Pop/Push selected top; Dispose pops once per stack',
  'scope':'source/target/buff/mainTarget only; non-tile Enemy owner; no modifier/projectile/ability mutation backend'},
 'key_case':{'prefix':'StartsWith(prefix, StringComparison.OrdinalIgnoreCase=5), then Substring(prefix.Length)',
  'assign':'ToLower() current culture, first String.Compare(old,key,true)==0 replacement; otherwise append',
  'lookup':'current-culture ignoreCase; _TryGetNumber skips matching rows with nonempty valueStr and continues',
  'scope':'ASCII keys under explicit invariant-culture fixture; no asserted observed live culture'},
 'priority':'SortedDoubleBufferedBuffList.Add immediate list only: descending priorities; new equal after existing equals; invalid incoming appends; skip invalid existing while scanning backward',
 'membership_and_reentrancy':'Caller supplies dispatched initialized Buff membership. This module does not synthesize full BuffContainer snapshots/deferred removal. Native synchronous selected-Buff recursion is executed without coalescing or pre-writing lock.'}
write('native_proofs.json',proof)
fields=read(OUT/'native_fields.json')
prefix=ROOT/'native_v8/npc_restore/talent_prefix_constants.json';assert prefix.is_file()
shutil.copyfile(prefix,E/'talent_prefix_constants.json')
old_manifest=read(ROOT/'native_v7/npc/manifest.json')
for p in old_manifest['files']:assert sha(p['path'])==p['sha256'],p['path']
summary={'scope':'selected initialized NPC Buff/event actions with explicit external providers',
 'target_sha256':pe['sha256'],'metadata_sha256':fields['metadata_sha256'],
 'ghidra':counts,'raw':raw_info,'raw_checks':checks,'all_original_checks_match':True,
 'v7_frozen_manifest_files_verified_unchanged':len(old_manifest['files']),
 'unit_tests':28,'independent_csharp_vectors':187,'client_runtime_compared':False,
 'game_launched':False,'complete_npc_simulator':False,
 'external_dependencies':['source/destination entity UID and Unity existence predicates','initialized Buff membership dispatch',
  'restoration/state/tween/route callbacks','shared tracked summon scheduler/factory/mode callbacks','life/global-modifier/mode callback',
  'full multi-Buff traversal and deferred mutation remain unsupported','audio CreateBuff node unsupported']}
write('audit_summary.json',summary)
for name in ['raw_helpers.json','native_fields.json','results_round1.json','results_round2.json']:
 shutil.copyfile(OUT/name,E/name)
print(json.dumps({'ghidra':counts,'raw':raw_info,'old_files':len(old_manifest['files'])},indent=2))

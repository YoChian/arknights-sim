"""Package exact NPC declarations, raw identities, and current validation.

This file neither imports the game nor writes to the simulator or old evidence.
"""
from pathlib import Path
import hashlib,json,struct
OUT=Path(__file__).parent; ROOT=OUT.parents[1]
def read(p):return json.loads((ROOT/p).read_text('utf8'))
def write(name,obj):
 (OUT/name).write_text(json.dumps(obj,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
fields=read('native_v7/npc/native_fields.json')
byname={t['name']:t for t in fields['types']}
prefabs=read('native_v5/resources/rule_prefab_subtrees.json')
templates=read('native_v5/resources/scene_templates.json')
inputs=read('native_v4/resources/exact_resource_inputs.json')
names=['enemy_2133_shdopl','enemy_3001_upeopl']
keys=['enemy_shdopl_passive','enemy_shdopl_finish','upeople_t','upeople_t_1','empty']
selected={k:templates['templates'][k] for k in keys}
parsed=[]
for key,item in selected.items():
 for event in item['raw']['eventToActions']['_items']:
  parsed.append({'template':key,'event':event['key'],
   'actions':json.loads(event['value']['SerializedState'])})
resource={'scope':'shipped declarations; activation and blackboard binding are separate runtime obligations',
 'prefabs':[p for p in prefabs['prefabs'] if p['name'] in names],
 'templates':selected,'parsed_event_actions':parsed,
 'enemy_database_records':{k:inputs['enemy_database_records'][k] for k in names},
 'enemyDbRefs':[r for r in inputs['level']['enemyDbRefs'] if r['id'] in names],
 'input_sources':inputs['sources'], 'level_asset':inputs['level_asset'],
 'template_source_pin':templates['source_pin'],
 'old_files_are_unchanged':True}
assert len(resource['prefabs'])==2
write('resource_inputs.json',resource)
oldenum=read('native_v5/devices/enum_constants.json')['enum_constants']
newenum=read('native_v6/skill/enum_constants.json')['enums']
write('enum_inputs.json',{'metadata_sha256':fields['metadata_sha256'],
 'v5_exact_records':[e for e in oldenum if e['name'] in [
  'Torappu.Battle.Buff.Event','Torappu.Battle.Action.Nodes.ActionTargetType','Torappu.MotionMask']],
 'v6_exact_records':[e for e in newenum if e['name'] in [
  'Torappu.Battle.Entity.FinishReason','Torappu.Battle.Enemy.States.State']],
 'limits':'Declarations are literal metadata constants, not active runtime state.'})

pe=next(x for x in read('core/pe_inventory.json') if x['path'].endswith('GameAssembly.dll'))
b=Path(pe['path']).read_bytes();assert hashlib.sha256(b).hexdigest()==pe['sha256']
base=int(pe['image_base'],16)
def file_offset(va,n):
 for s in pe['sections']:
  d=va-base-int(s['virtual_address'],16)
  if 0<=d and d+n<=s['raw_bytes']:return s['raw_offset']+d
 raise ValueError(hex(va))
iterator=byname['Torappu.Battle.Scheduler.<SpawnSummonedEnemyTrackedInGameMode>d__129']
native=iterator['byval_type'];usage_va=0x188899458;usage_off=file_offset(usage_va,4)
word=struct.unpack_from('<I',b,usage_off)[0]
assert word==0x200342f1 and (word&0x1fffffff)>>1==native['type_index']==106872
assert struct.unpack_from('<Q',b,native['pointer_record_file_offset'])[0]==int(native['address'],16)
assert b[native['file_offset']:native['file_offset']+12].hex()==native['raw_bytes12']
dispatch=read('native_v7/npc/raw_helpers.json')['functions'][0]['ranges']
table=next(r['embedded_jump_table'] for r in dispatch if 'embedded_jump_table' in r)
jump_bytes=bytes.fromhex(table['bytes'])
assert b[table['source_file_offset']:table['source_file_offset']+44]==jump_bytes
cases=['TARGET','SOURCE','BUFF_SOURCE','BUFF_OWNER','MODIFIER_TARGET','MODIFIER_SOURCE',
       'MAIN_TARGET','MAINBUFF_SOURCE','PROJECTILE_SOURCE','PROJECTILE_TRACETARGET','ABILITY_OWNER']
write('identity_proofs.json',{
 'target_sha256':pe['sha256'],
 'iterator':{'factory':'0x1809163b0','typeinfo_usage_va':hex(usage_va),'file_offset':usage_off,
   'raw_word':hex(word),'usage_kind':word>>29,'native_type_index':native['type_index'],
   'native_record':native,'definition_index':iterator['definition_index'],'name':iterator['name'],
   'MoveNext':next(m for m in iterator['methods'] if m['name']=='MoveNext')},
 'action_target_jump_table':{**table,'case_targets':[
   {'ordinal':i,'name':name,'branch_va':hex(base+struct.unpack_from('<I',jump_bytes,i*4)[0])}
   for i,name in enumerate(cases)]},
 'action_node_condition_slot':{
   'native_vtable_offset':'0x190','virtual_slot':5,
   'base_getter':next(m for m in byname['Torappu.Battle.Action.ActionNode']['methods'] if m['virtual_slot']==5),
   'no_override_proofs':[{ 'type':byname['Torappu.Battle.Action.Nodes.'+n]['name'],
     'definition_index':byname['Torappu.Battle.Action.Nodes.'+n]['definition_index'],
     'inheritance':byname['Torappu.Battle.Action.Nodes.'+n]['inheritance_chain_definition_indices'],
     'declared_method_records':byname['Torappu.Battle.Action.Nodes.'+n]['methods']}
     for n in ['AssignValueToBB','ClearAllBuffs']],
   'base_condition_normal_return':1,
   'CheckExecute_semantics':{'0':'true','1':'previousResult','2':'not previousResult','other':'false'},
   'normal_loop':'previousResult starts true; check allowedSource and CheckExecute before each Execute; false CheckExecute returns from the entire list; Execute result becomes previousResult',
   'InstantKill_false_consequence':'AssignValueToBB inherits condition1. Normal finishing returns alive=false, so lock and subsequent ClearAllBuffs do not execute.'},
 'field_errata':{'BObject.isDisappeared':next(f for f in byname['Torappu.Battle.BObject']['fields'] if 'isDisappeared' in f['name']),
  'Enemy.Options.unharmful':next(f for f in byname['Torappu.Battle.Enemy.Options']['fields'] if f['name']=='unharmful'),
  'note':'Separate storage and semantics. Entity+0x26 is disappeared. Options unharmful does not prove skip-damage-hooks.'}})

allrows=[]
for image in ['Assembly-CSharp','Torappu.Common','ThirdPartyAssembly','mscorlib']:
 allrows+=read(f'core/{image}_candidate_method_map.json')
next_targets=[
 ('spawn factory/registration/Born chain',0x18091b310),
 ('BasicCursor.OnRouteChanged',0x180875fa0),
 ('DirectionCursor.AssignHostRouteProgress',0x180894bb0),
 ('Enemy.DisappearState.OnEnter',0x180a8d030),
 ('Enemy.DisappearState.OnExit',0x180a8d1f0),
 ('Enemy.DisappearState.OnTick',0x180a8d370),
 ('Enemy.DisappearState._DoDisappear',0x180a8da00),
 ('Enemy.DisappearState._DoAppear',0x180a8d440),
 ('BasicTalent._CreateBlackboard',0x1809730d0),
 ('Blackboard.AssignByPrefix',0x18231d9c0),
 ('Blackboard.AssignValueStrByPrefix',0x18231dd20),
 ('SortedDoubleBufferedBuffList.Add',0x180692370),
 ('ObjectPtr validation shared raw call',0x1800c9210),
 ('gameMode helper called before FP wait',0x180942250),
 ('gameMode helper called after spawn callback',0x1808fdfc0),
 ('gameMode helper called at coroutine exit',0x1809421d0),
]
next_records=[]
for purpose,va in next_targets:
 matches=[r for r in allrows if r['candidate_va'] and int(r['candidate_va'],16)==va]
 next_records.append({'purpose':purpose,'address':hex(va),'metadata_candidates':matches,
  'identity_status':'candidate metadata + original pointer table' if matches else 'exact direct call target; name not resolved',
  'first16_source_file_offset':file_offset(va,16),'first16_source_bytes':b[file_offset(va,16):file_offset(va,16)+16].hex()})
write('selection_next.json',{'status':'future dependencies, not executed or claimed recovered in this round',
 'entries':next_records,'data_dependencies':[
  {'name':'talent prefix format string usage slot','address':'0x1887fb958','needed':'Resolve prefix format and case semantics for prefab GO Dead vs database dead.value'},
  {'name':'buff start/finish mutation order','needed':'Double-buffered priority traversal, source validity, active-buff removal and synchronous reentrancy semantics'},
  {'name':'Rogue runtime context','needed':'Explicit supported mode/hotfix/global modifiers/UID/object membership and initial life; no unproven live no-op assumption'}]})

checks=[];raw_stats=[];ghidra_stats=[]
for name in ['raw.json','raw_extra.json','raw_helpers.json','raw_dispatch.json']:
 d=read('native_v7/npc/'+name);functions=d if isinstance(d,list) else d['functions']
 count=byte_count=0
 for f in functions:
  for r in f['ranges']:
   start=int(r['start'],16);end=int(r['end_exclusive'],16) if 'end_exclusive' in r else int(r['end'],16)+1
   length=end-start;off=r['source_file_offset'];body=b[off:off+length]
   ok=hashlib.sha256(body).hexdigest()==r['source_sha256'];assert ok,(name,f.get('name',f.get('display_name')),r['start'])
   for i in r['instructions']:
    a=int(i['address'],16)-start;assert body[a:a+len(bytes.fromhex(i['bytes']))].hex()==i['bytes']
   checks.append({'collection':name,'function':f.get('name',f.get('display_name')),
                 'start':r['start'],'bytes':length,'match':ok})
   count+=1;byte_count+=length
 raw_stats.append({'file':name,'functions':len(functions),'ranges':count,'bytes':byte_count})
for name in ['results_round2.json','results_round3.json']:
 d=read('native_v7/npc/'+name);count=byte_count=0
 for f in d['functions']:
  assert f['decompile_completed'] and f['imported_memory_matches_source']
  for r in f['ranges']:
   length=int(r['end'],16)+1-int(r['start'],16);off=r['source_file_offset']
   assert hashlib.sha256(b[off:off+length]).hexdigest()==r['source_sha256']
  for r in f['imported_range_checks']:
   assert r['match'];count+=1;byte_count+=r['bytes']
 ghidra_stats.append({'file':name,'functions':len(d['functions']),'imported_ranges':count,'bytes':byte_count,'all_match':True})
old_pins=[]
for name in ['native_v5/lifecycle/manifest.json','native_v6/damage/manifest.json']:
 m=read(name);bad=[]
 for item in m['files']:
  if sha(item['path'])!=item['sha256']:bad.append(item['path'])
 assert not bad,bad
 old_pins.append({'manifest':str(ROOT/name),'sha256':sha(ROOT/name),'files_verified':len(m['files']),'unchanged':True})
write('audit_summary.json',{'target':pe['path'],'target_sha256':pe['sha256'],
 'metadata_sha256':fields['metadata_sha256'],'static_only':True,'game_launched':False,
 'ghidra':ghidra_stats,'raw':raw_stats,'source_range_checks':checks,
 'all_raw_ranges_and_instruction_bytes_match_original':True,'old_frozen_manifests':old_pins,
 'field_types':len(fields['types']),'field_records':sum(len(t['fields']) for t in fields['types']),
 'runtime_compared':False,'npc_component_implemented':False,'npc_battle_ready':False})
print(json.dumps({'Ghidra':ghidra_stats,'raw':raw_stats,'old_pins':old_pins},indent=2))

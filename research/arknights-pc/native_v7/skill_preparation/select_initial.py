"""Select exact metadata entrypoints missing from the existing native inventory."""
from pathlib import Path
import hashlib,json
OUT=Path(__file__).parent;BASE=OUT.parents[1];OLD=BASE/'native_v6/skill'
declarations=json.loads((OLD/'declarations.json').read_text())
fields=json.loads((OLD/'native_fields.json').read_text())
wanted={
 'Torappu.Battle.BasicSkill':['AssignData','Awake','PostprocessData','GetAttackBlackboard','get_ownerCanUseSkill','get_ownerSkillActivatable'],
 'Torappu.Battle.Ability':['SetData','DoSetData','UpdateBlackboard','Attach','DoAttach','DoReset','.ctor'],
 'Torappu.Battle.AbilityStandard':['DoSetData','OnAttached','Awake','.ctor'],
 'Torappu.Battle.Abilities.AbstractAnimatedAbility':['OnAttackTimeChanged','OnSlowDownChanged','.ctor'],
 'Torappu.Battle.Abilities.EasyToStartAbility':['.ctor'],
}
existing={}
for root in ['native_v4/creation','native_v4/attributes','native_v5/core','native_v6/core']:
 for p in (BASE/root).glob('results_round*.json'):
  for r in json.loads(p.read_text()).get('functions',[]):
   existing[r.get('metadata_method_index')]=(p,r)
selection=[];reused=[]
for owner,names in wanted.items():
 t=next(t for t in fields['types'] if t['name']==owner)
 for m in t['methods']:
  if m['name'] not in names:continue
  index=m['metadata_method_index'];candidate=m.get('native_candidate')
  if index in existing:
   p,r=existing[index]
   reused.append({'source':str(p),'source_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),
    'owner':owner,'metadata_method_index':index,'record':r})
   continue
  assert candidate and candidate['candidate_va'],(owner,m['name'])
  selection.append({'type':candidate['type'],'method':candidate['method'],'address':candidate['candidate_va'],
   'metadata_method_index':index,'owner':owner,'type_definition_index':t['definition_index'],'slot':m['virtual_slot'],
   'basis':'Pinned v6 full metadata/native field declarations; prerequisite of actual altar post-AssignData/Attach preparation'})
(OUT/'selection.json').write_text(json.dumps(selection,indent=2),encoding='utf-8')
(OUT/'reused_native.json').write_text(json.dumps(reused,indent=2),encoding='utf-8')
print(json.dumps({'selected':len(selection),'reused':len(reused),'functions':[(r['owner']+'.'+r['method'],r['address']) for r in selection]}))

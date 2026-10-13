"""Minimal exact native declaration/attribute/default evidence for preparation."""
from pathlib import Path
import json,sys,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1];prior=BASE/'native_v4/resources'
sys.path.insert(0,str(prior))
script=prior/'inspect_attribute_meta.py';ns={'__file__':str(script)}
exec(script.read_text().split('selected=[];enemy_fields=[]')[0],ns)
fullname,types,methods,fields,text,native_type,attributes_for_field,decode_default=[ns[k] for k in ['fullname','types','methods','fields','text','native_type','attributes_for_field','decode_default']]
wanted_names=['Torappu.SkillData','Torappu.SkillData.SpData','Torappu.SkillLevelData','Torappu.SpData','Torappu.Blackboard','Torappu.Battle.Entity.FriendComponent','Torappu.Battle.Abilities.AbstractAnimatedAbility','Torappu.Battle.Abilities.AbstractAnimatedAbility.TimeMode','Torappu.Battle.BasicSkill','Torappu.SkillType','Torappu.SkillDurationType']
declarations=[];constants={};attrs=[];maps=json.loads((BASE/'core/Assembly-CSharp_candidate_method_map.json').read_text());by_index={r['metadata_method_index']:r for r in maps}
for owner in range(len(types)):
 name=fullname(owner)
 if name not in wanted_names:continue
 t=types[owner];decl=[]
 for index in range(t[9],t[9]+t[17]):
  m=methods[index];decl.append({'name':text(m[0]),'metadata_method_index':index,'virtual_slot':m[8],'token':hex(m[5]),'native_candidate':by_index.get(index)})
 flds=[]
 for index in range(t[8],t[8]+t[19]):
  nt=native_type(fields[index][1]);fld={'name':text(fields[index][0]),'index':index,'token':hex(fields[index][2]),'native_type':nt}
  if nt['attrs']&64:fld['literal']=decode_default(index)
  flds.append(fld)
  if name in ['Torappu.Battle.Abilities.AbstractAnimatedAbility','Torappu.Battle.BasicSkill'] and not fld['name'].startswith(('__Hotfix','_c__')):
   attrs.append({'owner':name,**attributes_for_field(owner,index)})
 declarations.append({'name':name,'definition_index':owner,'fields':flds,'methods':decl})
 constants[name]=[{k:v for k,v in f.items() if k in ['name','index','token','literal']} for f in flds if 'literal' in f]
out={'metadata_sha256':hashlib.sha256(ns['meta']).hexdigest(),'target_sha256':ns['ns']['registration']['target_sha256'],'declarations':declarations,'constants':constants,'custom_attributes':attrs,'limits':'Exact metadata declaration/attribute arguments only; no target constructors executed.'}
(OUT/'metadata_declarations.json').write_text(json.dumps(out,indent=2,ensure_ascii=False),encoding='utf-8')
print(json.dumps({'types':[(t['name'],t['definition_index']) for t in declarations],'attributed_fields':[(a['owner'],a['field'],[x['attribute_type'] for x in a['attributes']]) for a in attrs if a['attributes']],'time_mode':constants.get('Torappu.Battle.Abilities.AbstractAnimatedAbility.TimeMode')},ensure_ascii=False))

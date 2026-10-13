"""Exact source candidates and existing results for staged Enemy factory."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/export_native_fields.py';ns={'__file__':str(source)}
exec(source.read_text().split('roots={')[0],ns)
maps=json.loads((BASE/'core/Assembly-CSharp_candidate_method_map.json').read_text())
owners={'Torappu.Battle.BattleFactory':{'CreateEnemy'},
        'Torappu.Battle.Enemy':{'Spawn','Init','Born','OnInit','_AssignData','_AssignTalent','AssignOptions','OnBorn'},
        'Torappu.Battle.Entity':{'Init','OnInit','OnBorn'},
        'Torappu.Battle.Unit':{'OnInit','OnPostInit','OnBorn'},
        'Torappu.Battle.BObject':{'Init','Born'},
        'Torappu.Battle.BattleController':{'RegisterUnit'},
        'Torappu.Battle.ObjectManager':{'Register'}}
recovered={}
for path in BASE.glob('native_v*/**/results*.json'):
 if 'enemy_factory' in path.parts:continue
 try:data=json.loads(path.read_text())
 except (ValueError,UnicodeError):continue
 records=data.get('functions',[]) if isinstance(data,dict) else []
 for r in records:
  if r.get('decompile_completed') and r.get('imported_memory_matches_source'):
   recovered.setdefault(r['address'],[]).append(str(path))
selected=[];reused=[]
for r in maps:
 i=r['metadata_method_index'];m=ns['methods'][i];owner=ns['fullname'](m[1])
 if owner not in owners or r['method'] not in owners[owner]:continue
 if i==66623:continue  # Six-parameter wrapper is not this Enemy.Init call.
 e={'type':owner,'method':r['method'],'metadata_method_index':i,'token':r['token'],
    'address':r['candidate_va'],'virtual_slot':m[8],
    'parameters':[{'name':ns['text'](p[0]),'native_type':ns['native_type'](p[2])['name']}
                   for p in ns['parameters'][m[3]:m[3]+m[9]]],
    'basis':'Exact metadata owner/token/codegen method pointer; CreateEnemy->Enemy.Init dependency'}
 if e['address'] in recovered:reused.append({**e,'sources':recovered[e['address']]})
 else:selected.append(e)
(OUT/'selection.json').write_text(json.dumps(selected,indent=2))
(OUT/'reused_native.json').write_text(json.dumps(reused,indent=2))
print(json.dumps({'new':selected,'reused':[{k:e[k] for k in ['type','method','address','parameters']} for e in reused]},indent=2))

"""Select exact NPC restore state/cursor entrypoints, reuse recovered ones."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/export_native_fields.py';ns={'__file__':str(source)}
exec(source.read_text().split('roots={')[0],ns)
types,methods,fullname=[ns[k] for k in ['types','methods','fullname']]
maps=json.loads((BASE/'core/Assembly-CSharp_candidate_method_map.json').read_text());by_index={r['metadata_method_index']:r for r in maps}
indices=[76777,76778,76779,76780,76781,76782,76783,70159,70269,76436,76492]
recovered={}
for path in BASE.glob('native_v*/**/results*.json'):
 if 'npc_restore' in path.parts:continue
 try:data=json.loads(path.read_text())
 except (ValueError,UnicodeError):continue
 records=data.get('functions',[]) if isinstance(data,dict) else []
 for r in records:
  if r.get('decompile_completed') and r.get('imported_memory_matches_source'):recovered.setdefault(r['address'],[]).append(str(path))
selection=[];reused=[]
for index in indices:
 m=methods[index];owner=m[1];r=by_index[index];entry={'type':fullname(owner),'method':r['method'],'metadata_method_index':index,'token':r['token'],'address':r['candidate_va'],'type_definition_index':owner,'virtual_slot':m[8],'basis':'Exact original metadata/native pointer candidate; NPC disappear state11 and route restore prerequisite'}
 if entry['address'] in recovered:reused.append({**entry,'sources':recovered[entry['address']]})
 else:selection.append(entry)
(OUT/'selection.json').write_text(json.dumps(selection,indent=2),encoding='utf-8')
(OUT/'reused_native.json').write_text(json.dumps(reused,indent=2),encoding='utf-8')
print(json.dumps({'new':selection,'reused':reused}))

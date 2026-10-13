from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=OUT/'select_targets.py';ns={'__file__':str(source)}
exec(source.read_text().split('owners=')[0],ns)
rows=[]
for r in ns['maps']:
 m=ns['ns']['methods'][r['metadata_method_index']];owner=ns['ns']['fullname'](m[1])
 if owner in ['Torappu.Battle.Enemy','Torappu.Battle.Unit','Torappu.Battle.Entity','Torappu.Battle.BObject','Torappu.Battle.ObjectManager'] and (m[8] in [23,24,30,31,231,236] or any(s in r['method'].lower() for s in ['register','create','assignoption'])):
  rows.append({**r,'owner':owner,'slot':m[8],'parameters':[
    {'name':ns['ns']['text'](p[0]),'type':ns['ns']['native_type'](p[2])['name']}
    for p in ns['ns']['parameters'][m[3]:m[3]+m[9]]]})
(OUT/'dispatch_candidates.json').write_text(json.dumps(rows,indent=2))
print(json.dumps([{k:r[k] for k in ['owner','method','slot','candidate_va','parameters']} for r in rows],indent=2))

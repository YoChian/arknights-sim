from pathlib import Path
import json
OUT=Path(__file__).parent
rows=[]
for e in json.loads((OUT/'reused_native.json').read_text()):
 candidates=[]
 for path in e['sources']:
  data=json.loads(Path(path).read_text())
  for r in data.get('functions',[]):
   if r['address']==e['address'] and r.get('decompile_completed') and r.get('imported_memory_matches_source'):
    candidates.append((len(r['ranges']),path,r))
 assert candidates,e
 _,path,r=max(candidates,key=lambda x:x[0]);dest=OUT/'reused'/f"{e['metadata_method_index']}_{e['type'].replace('.','_')}_{e['method']}.c"
 dest.parent.mkdir(exist_ok=True);dest.write_text(r['pseudocode'])
 rows.append({'selection':e,'result_source':path,'c_file':str(dest),'result':r})
(OUT/'reused_results.json').write_text(json.dumps(rows,indent=2))
print([(e['selection']['method'],e['selection']['address'],len(e['result']['ranges'])) for e in rows])

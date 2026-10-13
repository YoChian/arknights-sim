"""Retain exact owned entries and source-correlated pseudocode."""
from pathlib import Path
import json
OUT=Path(__file__).parent;CORE=OUT.parent/'core'
want={s['address']:s for p in ['selection.json','selection_extra.json'] for s in json.loads((OUT/p).read_text())}
res=json.loads((CORE/'results_round1.json').read_text());dest=OUT/'round1';dest.mkdir(exist_ok=True);owned=[]
for r in res['functions']:
 if r['address'] not in want:continue
 assert r['decompile_completed'] and r['imported_memory_matches_source']
 p=dest/(str(r['metadata_method_index'])+'_'+r['name']+'.c');p.write_text(r['pseudocode'].replace('\r',''),encoding='utf-8')
 owned.append({'selection':want[r['address']],'c_file':str(p),'result':r})
assert len(owned)==len(want)
(OUT/'results_round1.json').write_text(json.dumps(owned,indent=2),encoding='utf-8');print(len(owned),sum(len(r['result']['ranges']) for r in owned))

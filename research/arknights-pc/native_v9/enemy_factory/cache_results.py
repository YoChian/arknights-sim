from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
data=json.loads((BASE/'native_v9/core/results_round1.json').read_text())
by_address={r['address']:r for r in data['functions']};records=[]
for e in json.loads((OUT/'selection.json').read_text()):
 r=by_address[e['address']];assert r['decompile_completed'] and r['imported_memory_matches_source']
 assert all(x['match'] for x in r['imported_range_checks'])
 path=OUT/'round1'/f"{e['metadata_method_index']}_{e['type'].replace('.','_')}_{e['method']}.c"
 path.parent.mkdir(exist_ok=True);path.write_text(r['pseudocode'])
 records.append({'selection':e,'c_file':str(path),'result':r})
(OUT/'results_round1.json').write_text(json.dumps(records,indent=2))
print([(r['selection']['method'],r['selection']['address'],len(r['result']['ranges'])) for r in records])

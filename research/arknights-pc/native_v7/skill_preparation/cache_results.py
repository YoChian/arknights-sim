"""Copy only exact own selected native records; preserve source evidence."""
from pathlib import Path
import json
OUT=Path(__file__).parent;CORE=OUT.parent/'core'
for round_no,selection in [(1,'selection.json'),(3,'selection_extra.json'),(4,'selection_final.json')]:
 wanted={r['address']:r for r in json.loads((OUT/selection).read_text())};results=json.loads((CORE/f'results_round{round_no}.json').read_text())
 dest=OUT/f'round{round_no}';dest.mkdir(exist_ok=True);owned=[]
 for r in results['functions']:
  if r['address'] not in wanted:continue
  assert r['decompile_completed'] and r['imported_memory_matches_source']
  p=dest/(str(r['metadata_method_index'])+'_'+r['name']+'.c');p.write_text(r['pseudocode'].replace('\r',''),encoding='utf-8')
  owned.append({'selection':wanted[r['address']],'c_file':str(p),'result':r})
 assert len(owned)==len(wanted)
 (OUT/f'results_round{round_no}.json').write_text(json.dumps(owned,indent=2),encoding='utf-8');print(round_no,len(owned))

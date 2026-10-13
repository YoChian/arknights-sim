from pathlib import Path
import json
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
by_index={r['metadata_method_index']:r for r in json.loads((ROOT/'core/Assembly-CSharp_candidate_method_map.json').read_text('utf8'))}
indices=[98667,72111,76458,66580,66579,65373,65357,73301,73304,73322,73290,73317,72266]
selection=[]
for index in indices:
 r=by_index[index]
 selection.append({'type':r['type'],'method':r['method'],'address':r['candidate_va'],
                   'metadata_method_index':index,'token':r['token']})
(OUT/'selection_extra.json').write_text(json.dumps(selection,indent=2)+'\n',encoding='utf8')
print('selected extra',len(selection))

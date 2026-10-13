from pathlib import Path
import json
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
selection=json.loads((OUT/'selection.json').read_text('utf8'))
wanted={s['address'] for s in selection}
d=json.loads((ROOT/'native_v8/core/results_round1.json').read_text('utf8'))
functions=[f for f in d['functions'] if f['address'] in wanted]
assert len(functions)==len(wanted),(len(functions),len(wanted))
(OUT/'results_round1.json').write_text(json.dumps({'target_sha256':d['target_sha256'],
 'functions':functions},ensure_ascii=False,indent=2)+'\n',encoding='utf8')
(OUT/'round1').mkdir(exist_ok=True)
for f in functions:
 assert f['decompile_completed'] and f['imported_memory_matches_source']
 (OUT/'round1'/f"{f['name']}.c").write_text(f['pseudocode'],encoding='utf8')
print('own functions',len(functions))

"""Copy only this task's six second-round results without changing core."""
from pathlib import Path
import json
OUT = Path(__file__).parent
ROOT = OUT.parents[1]
selection = json.loads((OUT/'selection_extra.json').read_text('utf8'))
wanted = {x['address'] for x in selection if x['method'] != 'OnTargetKilled'}
data = json.loads((ROOT/'native_v6/core/results_round2.json').read_text('utf8'))
functions = [f for f in data['functions'] if f['address'] in wanted]
assert len(functions) == len(wanted) == 6
assert all(f['decompile_completed'] and f['imported_memory_matches_source'] for f in functions)
assert all(c['match'] for f in functions for c in f['imported_range_checks'])
(OUT/'results_round2.json').write_text(json.dumps({'target_sha256': data['target_sha256'],
                                               'functions': functions}, indent=2), encoding='utf8')
code = OUT/'round2'
code.mkdir(exist_ok=True)
for f in functions:
    (code/(f['name']+'.c')).write_text('\n'.join(x for x in f['pseudocode'].splitlines() if x.strip())+'\n', encoding='utf8')
print('decompiled', len(functions), 'source-matched ranges', sum(len(f['imported_range_checks']) for f in functions))

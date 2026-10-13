"""Verify original raw group coverage and recovered imported bytes."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent
raw=json.loads((OUT/'raw_helpers.json').read_text(encoding='utf-8'))
b=Path(raw['target_path']).read_bytes();assert hashlib.sha256(b).hexdigest()==raw['target_sha256']
ranges=[]
for f in raw['functions']:
    for r in f['ranges']:
        n=int(r['end_exclusive'],16)-int(r['start'],16);off=r['source_file_offset']
        assert hashlib.sha256(b[off:off+n]).hexdigest()==r['source_sha256']
        ranges.append({'function_address':f['address'],**{k:r[k] for k in ['start','end_exclusive','unwind_rva','chain_parent_start','source_file_offset','source_sha256']}})
records=[]
for name in ['results_round1.json','reused_results.json','dependency_results.json']:
    records+=json.loads((OUT/name).read_text(encoding='utf-8'))
for e in records:
    r=e['result'];assert r['decompile_completed'] and r['imported_memory_matches_source']
    assert all(c['match'] for c in r['imported_range_checks'])
    original={x['start']:x for x in ranges if x['function_address']==r['address']}
    assert set(original)=={s['start'] for s in r['ranges']},('incomplete original unwind group',r['address'])
    for span in r['ranges']:
        other=original[span['start']]
        assert int(span['end'],16)+1==int(other['end_exclusive'],16)
        assert span['source_sha256']==other['source_sha256']
out={'healthy':True,'target_path':raw['target_path'],'target_sha256':raw['target_sha256'],
    'fresh_entries':len(json.loads((OUT/'results_round1.json').read_text(encoding='utf-8'))),
    'reused_entries':len(records)-5,'imported_native_ranges':sum(len(r['result']['ranges']) for r in records),
    'raw_functions':len(raw['functions']),'verified_native_ranges':len(ranges),'native_ranges':ranges,
    'client_runtime_compared':False,
    'limits':['Imported byte match and chain coverage do not prove every decompiler expression correct.',
              'Unity allocation/reset/Awake, controller side effects, hit-range registration, mode/ability Attach, event12, born visual/backend, cursor, registry and MOVE hooks remain explicit providers.',
              'shdopl BORN-to-DISAPPEAR/start-Buff closure is not implemented by this component.']}
(OUT/'source_audit.json').write_text(json.dumps(out,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k not in ['native_ranges','limits']}))

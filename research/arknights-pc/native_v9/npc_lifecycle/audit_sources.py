"""Recheck exact original bytes of new and retained lifecycle records."""
import hashlib
import json
from pathlib import Path

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
def read(p):return json.loads(p.read_text('utf-8'))
pe=next(p for p in read(BASE/'core/pe_inventory.json') if p['path'].endswith('GameAssembly.dll'))
blob=Path(pe['path']).read_bytes()
assert hashlib.sha256(blob).hexdigest()==pe['sha256']
checks=[]
raw=read(OUT/'raw_helpers.json')
raw_final=next(f for f in raw['functions'] if f['address']=='0x1809196f0')

def check(function,kind):
    for r in function['ranges']:
        if 'end_exclusive' in r:sizes=[int(r['end_exclusive'],16)-int(r['start'],16)]
        else:sizes=[int(r['end'],16)-int(r['start'],16)+1,int(r['end'],16)-int(r['start'],16)]
        origin='retained source range record'
        if 'source_file_offset' not in r:
            assert function['address']=='0x1809196f0'
            matching_raw=next(x for x in raw_final['ranges'] if x['start']==r['start'])
            assert int(r['end'],16) in (int(matching_raw['end_exclusive'],16),int(matching_raw['end_exclusive'],16)-1)
            off=matching_raw['source_file_offset'];expected=matching_raw['source_sha256']
            origin='new independently extracted original raw range'
        else:
            off=r['source_file_offset'];expected=r['source_sha256']
        matching=[n for n in sizes if hashlib.sha256(blob[off:off+n]).hexdigest()==expected]
        assert len(matching)==1,(function['address'],r)
        n=matching[0];body=blob[off:off+n]
        for i in r.get('instructions',[]):
            pos=int(i['address'],16)-int(r['start'],16);raw=bytes.fromhex(i['bytes'])
            assert body[pos:pos+len(raw)]==raw,(function['address'],i)
        checks.append({'kind':kind,'function':function['address'],'start':r['start'],
            'source_file_offset':off,'bytes':n,'sha256':expected,'match':True,'expected_sha_origin':origin})

selected={x['address'] for p in ('selection.json','selection_extra.json') for x in read(OUT/p)}
new=[]
for batch in (1,2):
    path=BASE/f'native_v9/core/results_round{batch}.json'
    for f in read(path)['functions']:
        if f['address'] not in selected:continue
        assert f['decompile_completed'] and f['imported_memory_matches_source']
        assert all(x['match'] for x in f['imported_range_checks'])
        new.append(f);check(f,'new_decompile')
assert len(new)==len(selected)==9
reused=read(OUT/'reused_native.json')
for entry in reused['decompiled_functions']:
    assert hashlib.sha256(Path(entry['source_path']).read_bytes()).hexdigest()==entry['source_sha256']
    check(entry['function'],'reused_decompile')
for entry in reused['raw_functions']:
    assert hashlib.sha256(Path(entry['source_path']).read_bytes()).hexdigest()==entry['source_sha256']
    check(entry['function'],'reused_raw')
for f in raw['functions']:check(f,'new_raw')
report={
    'target_sha256':pe['sha256'],'new_decompiled_functions':len(new),
    'reused_decompiled_functions':len(reused['decompiled_functions']),
    'reused_decompiled_import_verification_recorded':sum(e['imported_memory_verification_recorded'] is True for e in reused['decompiled_functions']),
    'reused_raw_functions':len(reused['raw_functions']),'new_raw_functions':len(raw['functions']),
    'ranges':len(checks),'source_bytes':sum(r['bytes'] for r in checks),'all_original_bytes_match':True,
    'checks':checks,
    'limits':['One retained v3 CheckFinal decompile lacks an imported-memory verification field; its complete original raw ranges are independently corroborated here.',
              'Static source/import checks are not runtime execution or a live-hotfix audit.']}
(OUT/'source_audit.json').write_text(json.dumps(report,indent=2)+'\n','utf-8')
print(json.dumps({k:v for k,v in report.items() if k not in ('checks','limits')},indent=2))

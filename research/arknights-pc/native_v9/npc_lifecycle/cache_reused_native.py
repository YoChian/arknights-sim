"""Retain exact earlier native records with their source-report hashes."""
import hashlib
import json
from pathlib import Path

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
def read(p):return json.loads(p.read_text('utf-8'))
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
requests={
 'native_v4/creation/results_round2.json':{0x180a6d0d0},
 'native_v5/lifecycle/results_round1.json':{0x1806f8c40,0x1806f9e00,0x180a70920,0x180a71770},
 'native_v5/core/results_round1.json':{0x1806fb290},
 'native_v5/core/results_round2.json':{0x180aca5b0,0x18091bcb0,0x180662710,0x180661ec0},
 'native_v3/timeline/results_round6.json':{0x18091bb70,0x1809141e0},
 'native_v3/timeline/results_round2.json':{0x1809196f0},
}
records=[]
for relative,addresses in requests.items():
    p=BASE/relative;report=read(p)
    found={int(f['address'],16):f for f in report['functions'] if int(f['address'],16) in addresses}
    assert set(found)==addresses,(relative,addresses-set(found))
    for function in found.values():
        assert function['decompile_completed']
        if 'imported_memory_matches_source' in function:
            assert function['imported_memory_matches_source']
        records.append({'source_path':str(p),'source_sha256':sha(p),'function':function,
                        'imported_memory_verification_recorded':function.get('imported_memory_matches_source')})
raw_path=BASE/'native_v5/lifecycle/raw_helpers.json'
raw=read(raw_path)
raw_wanted={'Entity.FinishMe','DefaultGameMode.DestroyEntity','Entity.RecycleSelfImmediately',
            'BattleController.OnUnitFinished','PoolManager.Recycle','PoolManager._RecycleInternal',
            'IPooledObject.OnRecycle_call_target'}
raw_records=[{'source_path':str(raw_path),'source_sha256':sha(raw_path),'function':f}
             for f in raw['functions'] if f['name'] in raw_wanted]
assert {x['function']['name'] for x in raw_records}==raw_wanted
output={'target_sha256':raw['target_sha256'],'decompiled_functions':records,'raw_functions':raw_records,
        'limits':['Earlier source-owned native records retained unchanged; no rerun of Ghidra or game.',
                  'Generic/class identity of unresolved recycle cleanup is not inferred from an alias.']}
(OUT/'reused_native.json').write_text(json.dumps(output,ensure_ascii=False,indent=2)+'\n','utf-8')
print(json.dumps({'decompiled':len(records),'raw':len(raw_records)}))

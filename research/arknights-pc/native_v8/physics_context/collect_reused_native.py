"""Reuse exact earlier native bodies, preserving their source report hashes."""
from pathlib import Path
import hashlib
import json

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
requested={
    '0x18062c440':('native_v5/core/results_round1.json','BC ordinary tick physics/query phase subsequence'),
    '0x1809b6a30':('native_v6/core/results_round1.json','PhysicsRange temporary world pose/query/local restore'),
    '0x1809a6560':('native_v6/core/results_round1.json','Exact box/circle query and CircleColliderOverlapFixed cached lookup branch'),
    '0x1809b7550':('native_v6/core/results_round1.json','Runtime created BoxCollider2D declarations'),
}
rows=[]
for address,(relative,reason) in requested.items():
    path=BASE/relative;data=json.loads(path.read_text('utf-8'))
    found=[x for x in data['functions'] if x['address']==address]
    assert len(found)==1
    fn=found[0]
    assert fn['decompile_completed'] and fn['imported_memory_matches_source']
    rows.append({'reason':reason,'source_report_path':str(path),
                 'source_report_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'function':fn})
(OUT/'reused_native.json').write_text(json.dumps({'functions':rows,'limits':['Exact static earlier bodies, no new target execution or runtime observation.']},indent=2),'utf-8')
print('reused',len(rows))

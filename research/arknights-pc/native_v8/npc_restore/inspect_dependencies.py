"""Bind reused/default and DOTween call identities, without executing code."""
from pathlib import Path
import json,struct,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/export_native_fields.py';ns={'__file__':str(source)}
exec(source.read_text().split('roots={')[0],ns)
b=ns['b'];methods=ns['methods'];parameters=ns['parameters'];native_type=ns['native_type']
addresses={0x18424e070,0x18424f2c0,0x184262620,0x184260440,0x180647f20,
           0x1826483e0,0x180a9b3e0,0x180896720,0x1808762d0,0x180662be0}
records=[]
for image in ['DOTween','Assembly-CSharp']:
    path=BASE/f'core/{image}_candidate_method_map.json'
    rows=json.loads(path.read_text())
    for r in rows:
        if not r['candidate_va']:continue
        address=int(r['candidate_va'],16)
        if address not in addresses:continue
        i=r['metadata_method_index'];m=methods[i]
        pointer=struct.unpack_from('<Q',b,r['table_entry_file_offset'])[0]
        assert pointer==address
        records.append({**r,'qualified_owner':ns['fullname'](m[1]),
            'pointer_record_bytes8':b[r['table_entry_file_offset']:r['table_entry_file_offset']+8].hex(),
            'parameter_types':[native_type(p[2])['name'] for p in parameters[m[3]:m[3]+m[9]]],
            'source_candidate_map':str(path),'map_sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
assert {int(r['candidate_va'],16) for r in records}==addresses
(OUT/'dependency_identities.json').write_text(json.dumps({'records':records,
    'target_sha256':hashlib.sha256(b).hexdigest(),'metadata_sha256':hashlib.sha256(ns['meta']).hexdigest()},indent=2))
print([(r['candidate_va'],r['qualified_owner'],r['method'],r['parameter_types']) for r in records])

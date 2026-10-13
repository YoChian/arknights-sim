from pathlib import Path
import json,hashlib,struct
OUT=Path(__file__).parent
r=next(r for r in json.loads((OUT/'cipher_sample_provenance.json').read_text('utf-8')) if r['name']=='resource_index')
raw=Path(r['path']).read_bytes();body=raw[128:];p=OUT/'samples'/'resource_index.flat.bin';p.write_bytes(body)
root=struct.unpack_from('<I',body,0)[0];vt=root-struct.unpack_from('<i',body,root)[0];vl,sz=struct.unpack_from('<HH',body,vt)
provenance=r|{'prefix_bytes_removed':128,'body_path':str(p),'body_sha256':hashlib.sha256(body).hexdigest(),'body_bytes':len(body),'root_offset':root,'vtable_offset':vt,'vtable_bytes':vl,'root_fields':(vl-4)//2,'root_table_bytes':sz}
(OUT/'index_provenance.json').write_text(json.dumps(provenance,ensure_ascii=False,indent=2),'utf-8')
lua=(OUT/'samples'/'UIPatch.lua.published-decoded.bin').read_bytes();(OUT/'decoded'/'UIPatch.lua').write_bytes(lua)
rogue=json.loads((OUT/'samples'/'roguelike_table.published-decoded.bin').read_text('utf-8'));(OUT/'normalized'/'roguelike_table.json').write_text(json.dumps(rogue,ensure_ascii=False,indent=2),'utf-8')
print(json.dumps(provenance))

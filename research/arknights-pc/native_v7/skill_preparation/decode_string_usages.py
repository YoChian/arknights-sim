"""Resolve only selected original encoded literal slots with bounded metadata."""
from pathlib import Path
import json,struct,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/export_native_fields.py';ns={'__file__':str(source)}
exec(source.read_text().split('roots={')[0],ns)
b,meta,tables,offset=[ns[k] for k in ['b','meta','tables','offset']]
out=[]
for address in [0x188926a78,0x1889281b8,0x188836150,0x188835620,0x1887fc850]:
 off=offset(address,8);encoded=struct.unpack_from('<Q',b,off)[0];kind=encoded>>29;index=(encoded&0x1fffffff)>>1
 assert kind==5 and encoded&1
 start,size=tables['string_literals'];assert index*8+8<=size
 length,data_index=struct.unpack_from('<II',meta,start+index*8)
 data,size=tables['string_literal_data'];assert data_index+length<=size
 raw=meta[data+data_index:data+data_index+length]
 out.append({'slot_va':hex(address),'slot_file_offset':off,'slot_bytes8':b[off:off+8].hex(),'kind':kind,'source_index':index,'literal_record_file_offset':start+index*8,'literal_data_file_offset':data+data_index,'literal_bytes':raw.hex(),'value':raw.decode('utf-8')})
result={'target_sha256':ns['registration']['target_sha256'],'metadata_sha256':hashlib.sha256(meta).hexdigest(),'slots':out,'scope':'Original initialized usage encoding only, no target IL2CPP initialization executed.'}
(OUT/'string_usages.json').write_text(json.dumps(result,indent=2),encoding='utf-8');print(json.dumps(result))

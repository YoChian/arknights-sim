"""Exact SP-index enum literal and MathUtil.GE epsilon, no runtime calls."""
from pathlib import Path
import json,struct,sys,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/inspect_attribute_meta.py'
sys.path.insert(0,str(source.parent));ns={'__file__':str(source)}
exec(source.read_text().split('selected=[];enemy_fields=[]')[0],ns)
base=ns['ns'];b,meta,offset=[base[k] for k in ['b','meta','offset']]
slot=0x188820878;off=offset(slot,8);encoded=struct.unpack_from('<Q',b,off)[0];assert encoded>>29==1
native=ns['native_type']((encoded&0x1fffffff)>>1);t=ns['types'][native['definition_index']];values=[]
for index in range(t[8],t[8]+t[19]):
 f=ns['fields'][index];ft=ns['native_type'](f[1])
 if ft['attrs']&64:values.append({'name':ns['text'](f[0]),'field_index':index,'literal':ns['decode_default'](index)})
address=0x1866e4b98+0x75b1f0;literal_offset=offset(address,4);raw=b[literal_offset:literal_offset+4]
result={'target_sha256':base['registration']['target_sha256'],'metadata_sha256':hashlib.sha256(meta).hexdigest(),
 'sp_increment_enum_slot':{'va':hex(slot),'file_offset':off,'raw_bytes8':b[off:off+8].hex(),'native_type':native,'constants':values},
 'MathUtil_GE_epsilon':{'va':hex(address),'file_offset':literal_offset,'raw_bytes4':raw.hex(),'float32':struct.unpack('<f',raw)[0],
 'operation':'COMISS inputA,(inputB-epsilon) then SETAE; finite selected inputs only'},
 'interpretation':'SpData.Init loops0..3 and probes Enum.ToString keys; actual value/duration blackboard keys do not match any entry, so no SP-type/increment override.'}
(OUT/'preparation_constants.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
print(json.dumps({'enum':native['name'],'values':[(v['name'],v['literal']['value']) for v in values],'GE_epsilon':result['MathUtil_GE_epsilon']}))

"""Exact class/generic context records used by the native overlap caller."""
from pathlib import Path
import hashlib
import json
import struct

OUT=Path(__file__).resolve().parent
HELPER=OUT/'export_native_fields.py'
ns={'__file__':str(HELPER)}
exec(HELPER.read_text('utf-8').split('root_names=')[0],ns)
blob,offset,meta=ns['b'],ns['offset'],ns['meta']
words=[int(x,16) for x in ns['registration']['registration']['words']]
rows=[]
for address in (0x188891d40,0x188958a18,0x1888e14d8,0x18890dbb8):
    off=offset(address,8);value=struct.unpack_from('<Q',blob,off)[0]
    kind=value>>29;index=(value&0x1fffffff)>>1
    row={'slot_va':hex(address),'file_offset':off,'raw8':blob[off:off+8].hex(),'usage_kind':kind,'usage_index':index}
    if kind==1:
        row['native_type']=ns['native_type'](index)
    elif kind==6:
        so=offset(words[9]+12*index,12);method,ci,mi=struct.unpack_from('<3i',blob,so)
        m=ns['methods'][method]
        row.update(method_spec_file_offset=so,method_spec_raw12=blob[so:so+12].hex(),
                   method_definition_index=method,declaring_type=ns['fullname'](m[1]),method_name=ns['text'](m[0]),
                   class_inst_index=ci,method_inst_index=mi)
        inst=ci if ci>=0 else mi
        table=offset(words[3]+inst*8,8);pointer=struct.unpack_from('<Q',blob,table)[0]
        io=offset(pointer,16);argc,args=struct.unpack_from('<I4xQ',blob,io)
        ao=offset(args,argc*8)
        row['generic_arguments']=[ns['native_type_address'](a) for a in struct.unpack_from('<'+str(argc)+'Q',blob,ao)]
    rows.append(row)
output={'target_sha256':hashlib.sha256(blob).hexdigest(),'metadata_sha256':hashlib.sha256(meta).hexdigest(),
        'records':rows,'limits':['Encoded metadata usage and generic context identity, not resolved runtime object type or engine component attachment state.']}
(OUT/'caller_types.json').write_text(json.dumps(output,indent=2),'utf-8')
for row in rows:print(row['slot_va'],row['usage_kind'],row.get('native_type',{}).get('name'),row.get('method_name'),[x['name'] for x in row.get('generic_arguments',[])])

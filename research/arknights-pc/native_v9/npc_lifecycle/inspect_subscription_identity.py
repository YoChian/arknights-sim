"""Resolve OnGameReset's delegate type and generic On MethodInfo usages."""
import hashlib
import json
from pathlib import Path
import struct

OUT=Path(__file__).resolve().parent
HELPER=OUT/'export_native_fields.py'
ns={'__file__':str(HELPER)}
exec(HELPER.read_text('utf-8').split('root_names=')[0],ns)
blob,offset,meta=ns['b'],ns['offset'],ns['meta']
words=[int(x,16) for x in ns['registration']['registration']['words']]
records=[]
for address in (0x1888797f0,0x188811de0,0x18896eae0,0x18896e8a0):
    off=offset(address,8);value=struct.unpack_from('<Q',blob,off)[0]
    kind=value>>29;index=(value&0x1fffffff)>>1
    row={'slot_va':hex(address),'file_offset':off,'raw_bytes8':blob[off:off+8].hex(),
         'usage_kind':kind,'usage_index':index}
    if kind==1:
        row['native_type']=ns['native_type'](index)
    elif kind in (3,6):
        if kind==6:
            so=offset(words[9]+12*index,12);method,ci,mi=struct.unpack_from('<3i',blob,so)
            row.update(method_spec_file_offset=so,method_spec_raw12=blob[so:so+12].hex(),
                       class_inst_index=ci,method_inst_index=mi)
            args=[]
            for name,inst in (('class_arguments',ci),('method_arguments',mi)):
                if inst<0:continue
                table=offset(words[3]+inst*8,8);pointer=struct.unpack_from('<Q',blob,table)[0]
                io=offset(pointer,16);argc,argv=struct.unpack_from('<I4xQ',blob,io)
                ao=offset(argv,argc*8)
                row[name]=[ns['native_type_address'](a) for a in struct.unpack_from('<'+'Q'*argc,blob,ao)]
        else:method=index
        m=ns['methods'][method]
        row.update(method_definition_index=method,declaring_type=ns['fullname'](m[1]),
                   method_name=ns['text'](m[0]),metadata_method_record_file_offset=ns['tables']['methods'][0]+method*32)
    else:raise ValueError((address,kind,index))
    records.append(row)
output={'target_sha256':hashlib.sha256(blob).hexdigest(),'metadata_sha256':hashlib.sha256(meta).hexdigest(),
        'records':records,'limits':['Method/type identity only; whole IntEventPool ordering/reentrancy and BattleController bootstrap not executed.']}
(OUT/'subscription_identities.json').write_text(json.dumps(output,indent=2)+'\n','utf-8')
for row in records:
    print(row['slot_va'],row.get('native_type',{}).get('name'),row.get('declaring_type'),row.get('method_name'),
          [x['name'] for x in row.get('class_arguments',[])])

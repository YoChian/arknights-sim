"""Exact encoded caller slots for ALL weighted PriorityQueue, not shared aliases."""
from pathlib import Path
import hashlib,json,struct

OUT=Path(__file__).parent
HELPER=OUT/'export_native_fields.py'
ns={'__file__':str(HELPER)}
exec(HELPER.read_text('utf-8').split('roots=')[0],ns)
b,meta,offset=ns['b'],ns['meta'],ns['offset']
words=[int(x,16) for x in ns['registration']['registration']['words']]


def inst(index):
    if index<0:return None
    assert index<words[2]
    ptr_off=offset(words[3]+8*index,8)
    ptr=struct.unpack_from('<Q',b,ptr_off)[0]
    off=offset(ptr,16)
    argc,argv=struct.unpack_from('<QQ',b,off)
    assert 0<argc<64
    args_off=offset(argv,8*argc)
    argptrs=struct.unpack_from('<'+str(argc)+'Q',b,args_off)
    return {'index':index,'record_va':hex(ptr),'record_file_offset':off,
        'raw_bytes16':b[off:off+16].hex(),'argument_pointer_file_offset':args_off,
        'arguments':[ns['native_type_address'](p) for p in argptrs]}


records=[]
for address,target in [(0x18896e700,0x1851b2800),(0x18896eb80,0x1851b0a00),
                       (0x18896e940,0x1851afeb0),(0x18896edc0,0x1851b1b10),
                       (0x18896f000,0x1851b36f0),(0x18896f240,0x1848dd0d0)]:
    off=offset(address,8);raw=struct.unpack_from('<Q',b,off)[0]
    kind,index=raw>>29,(raw&0x1fffffff)>>1
    assert kind==6 and index<words[8]
    specoff=offset(words[9]+12*index,12)
    idx,cls,generic=struct.unpack_from('<3i',b,specoff)
    m=ns['methods'][idx]
    records.append({'slot_va':hex(address),'slot_file_offset':off,'slot_raw8':b[off:off+8].hex(),
        'usage_kind':kind,'method_spec_index':index,'method_spec_file_offset':specoff,
        'method_spec_raw12':b[specoff:specoff+12].hex(),'method_definition_index':idx,
        'declaring_type':ns['fullname'](m[1]),'method_name':ns['text'](m[0]),
        'token':hex(m[5]),'parameter_count':m[9],'class_generic_inst':inst(cls),
        'method_generic_inst':inst(generic),'caller_bound_machine_target':hex(target)})
types=[]
for address in [0x188966c90,0x1888800e0,0x1888a2040,0x1888f8818]:
    off=offset(address,8);raw=struct.unpack_from('<Q',b,off)[0]
    kind,index=raw>>29,(raw&0x1fffffff)>>1
    assert kind in [1,2]
    types.append({'slot_va':hex(address),'slot_file_offset':off,'slot_raw8':b[off:off+8].hex(),
        'usage_kind':kind,'native_type':ns['native_type'](index)})
output={'target_sha256':hashlib.sha256(b).hexdigest(),'metadata_sha256':hashlib.sha256(meta).hexdigest(),
    'method_records':records,'type_records':types,
    'correction':'v6 prose called this SortedSet/CompValue provisionally; actual types are PriorityQueue/WeightedTarget. v6 externally supplied ALL algorithm is unchanged and its pins are preserved.',
    'limits':['Exact static caller encoded identity. Shared machine pointer alone does not prove type or layout.','No live hotfix dispatch observed.']}
(OUT/'generic_identities.json').write_text(json.dumps(output,indent=2),'utf-8')
print(json.dumps([{'method':r['declaring_type']+'.'+r['method_name'],'idx':r['method_definition_index'],
    'address':r['caller_bound_machine_target']} for r in records],indent=2))
print([(x['slot_va'],x['native_type']['name']) for x in types])

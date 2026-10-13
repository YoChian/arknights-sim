"""Bind actual state helper MethodInfo slots to metadata generic specs."""
from pathlib import Path
import json,struct,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v6/targeting/inspect_generic_identities.py';code=source.read_text()
ns={'__file__':str(source)};exec(code.split('records = []')[0],ns)
b,meta,offset,words,generic_inst=[ns[k] for k in ['b','meta','offset','words','generic_inst']]
records=[]
for slot,target in [(0x1889576e0,0x18536e450),(0x188957b60,0x18536e540)]:
 off=offset(slot,8);encoded=struct.unpack_from('<Q',b,off)[0];kind=encoded>>29;index=(encoded&0x1fffffff)>>1
 assert kind==6 and index<words[8]
 spec_off=offset(words[9]+index*12,12);method_index,class_inst,method_inst=struct.unpack_from('<3i',b,spec_off);m=ns['ns']['methods'][method_index]
 records.append({'slot_va':hex(slot),'slot_file_offset':off,'raw_bytes8':b[off:off+8].hex(),'method_spec_index':index,'method_spec_file_offset':spec_off,'method_spec_bytes12':b[spec_off:spec_off+12].hex(),'method_definition_index':method_index,'owner':ns['ns']['fullname'](m[1]),'method_name':ns['ns']['text'](m[0]),'token':hex(m[5]),'parameter_count':m[9],'class_inst':generic_inst(class_inst),'method_inst':generic_inst(method_inst),'caller_bound_target':hex(target)})
(OUT/'generic_identities.json').write_text(json.dumps({'target_sha256':hashlib.sha256(b).hexdigest(),'metadata_sha256':hashlib.sha256(meta).hexdigest(),'records':records},indent=2),encoding='utf-8')
print(json.dumps([{k:r[k] for k in ['owner','method_name','parameter_count','caller_bound_target']} for r in records]))

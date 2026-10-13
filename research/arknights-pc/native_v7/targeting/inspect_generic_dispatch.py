"""Recover generic pointer identity by canonical table and observed callers.

No target code is executed. The canonical CompareTo pointer anchors the table;
all minimum-count entries must be file-backed. Two other observed constructor
addresses independently corroborate the inferred table and sharing family.
"""
from pathlib import Path
import hashlib,json,struct

OUT=Path(__file__).parent
HELPER=OUT/'export_native_fields.py'
ns={'__file__':str(HELPER)}
exec(HELPER.read_text('utf-8').split('roots=')[0],ns)
b,offset=ns['b'],ns['offset']
words=[int(x,16) for x in ns['registration']['registration']['words']]
function_off=offset(words[5],words[4]*16)
funcs=list(struct.iter_unpack('<4i',b[function_off:function_off+words[4]*16]))
assert all(0<=x[0]<words[8] and x[1]>=0 and x[2]>=0 and x[3]>=-1 for x in funcs)
spec_off=offset(words[9],words[8]*12)
specs=list(struct.iter_unpack('<3i',b[spec_off:spec_off+words[8]*12]))
identity=json.loads((OUT/'generic_identities.json').read_text('utf-8'))
anchors=[]
common=None
anchor_rows=[(205031,74744,0x1855279c0)]
for index,method_index,target in anchor_rows:
    matched=[(n,x) for n,x in enumerate(funcs) if x[0]==index]
    assert len(matched)==1,(index,matched)
    n,record=matched[0]
    hits=[]
    cursor=0
    while True:
        found=b.find(struct.pack('<Q',target),cursor)
        if found<0:break
        hits.append(found);cursor=found+1
    possible={p-record[1]*8 for p in hits if p-record[1]*8>=0}
    common=possible if common is None else common & possible
    anchors.append({'method_spec_index':index,'method_definition_index':method_index,
        'functions_record_index':n,'functions_record_file_offset':function_off+16*n,
        'functions_record_raw16':b[function_off+16*n:function_off+16*n+16].hex(),
        'generic_pointer_index':record[1],'observed_machine_target':hex(target),
        'all_matching_va_pointer_file_offsets':hits})
pointer_count=max(x[1] for x in funcs)+1
valid=[]
for table in common:
    if table+pointer_count*8>len(b):continue
    try:
        candidate=struct.unpack_from('<'+str(pointer_count)+'Q',b,table)
        for addr in candidate:
            if addr:offset(addr,1)
    except (ValueError,struct.error):continue
    valid.append((table,candidate))
assert len(valid)==1,[x[0] for x in valid]
table_off,pointers=valid[0]
outputs=[]
for n,spec in enumerate(specs):
    if spec[0] not in [74740,74741,74742,74743,74744,74745] or spec[1]!=83:continue
    matched=[(i,x) for i,x in enumerate(funcs) if x[0]==n]
    if not matched:continue
    assert len(matched)==1
    i,rec=matched[0]
    idx=rec[1];addr=pointers[idx];m=ns['methods'][spec[0]]
    outputs.append({'method_spec_index':n,'method_spec_file_offset':spec_off+12*n,
        'method_spec_raw12':b[spec_off+12*n:spec_off+12*n+12].hex(),
        'method_definition_index':spec[0],'declaring_type':ns['fullname'](m[1]),
        'method_name':ns['text'](m[0]),'parameter_count':m[9],'token':hex(m[5]),
        'functions_record_index':i,'functions_record_file_offset':function_off+16*i,
        'functions_record_raw16':b[function_off+16*i:function_off+16*i+16].hex(),
        'generic_pointer_index':idx,'generic_pointer_record_file_offset':table_off+idx*8,
        'address':hex(addr),'first16':b[offset(addr,16):offset(addr,16)+16].hex(),
        'compiled_sharing_arguments':'Object by genericInst83. Actual caller Entity context is proven separately by source-bound queue methods/type slots.'})
known={74740:0x185528950,74742:0x185528bb0,74744:0x1855279c0}
assert all(any(x['method_definition_index']==idx and int(x['address'],16)==address for x in outputs)
           for idx,address in known.items())
output={'target_sha256':hashlib.sha256(b).hexdigest(),
    'metadata_registration_function_records_va':hex(words[5]),'function_records_file_offset':function_off,
    'record_width':16,'function_record_count':words[4],
    'generic_pointer_table_file_offset':table_off,'min_proven_pointer_count':pointer_count,
    'all_min_count_pointers_file_backed':True,'independent_caller_anchors':anchors,
    'weighted_entity_methods':outputs,'independent_observed_targets':{str(i):hex(a) for i,a in known.items()},
    'limits':['Static pointer table identity, no target execution.',
        'Canonical WeightedTarget<Object> spec205031 matches caller observed CompareTo address; full minimum pointer count is file-backed.',
        'Entity methodSpecs need not appear in compiled generic function table: reference-type canonical sharing is not an Entity layout proof by itself.']}
(OUT/'generic_dispatch.json').write_text(json.dumps(output,indent=2),'utf-8')
print(json.dumps(outputs,indent=2))

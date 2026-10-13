"""Read-only native Il2CppType table candidate, validated against declarations.

Layout source: Perfare/Il2CppDumper Il2CppClass.cs, accessed 2026-10-13.
No registration code is run. A matching pointer array is structural evidence.
"""
from pathlib import Path
import json,struct,hashlib
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
pe=next(x for x in json.loads((ROOT/'core'/'pe_inventory.json').read_text('utf-8')) if x['path'].endswith('GameAssembly.dll'))
b=Path(pe['path']).read_bytes();base=int(pe['image_base'],16)
assert hashlib.sha256(b).hexdigest()==pe['sha256']
def va(off):
    for s in pe['sections']:
        if s['raw_offset']<=off<s['raw_offset']+s['raw_bytes']:
            return base+int(s['virtual_address'],16)+off-s['raw_offset']
    raise ValueError('offset not mapped')
def offset(address,n=1):
    rv=address-base
    for s in pe['sections']:
        d=rv-int(s['virtual_address'],16)
        if 0<=d and d+n<=s['raw_bytes']:return s['raw_offset']+d
    raise ValueError('VA not backed')
meta=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\il2cpp_data\Metadata\global-metadata.dat').read_bytes()
names='string_literals string_literal_data strings events properties methods parameter_defaults field_defaults default_data marshaled_fields parameters fields generic_parameters generic_constraints generic_containers nested_types interfaces vtable_methods interface_offsets type_definitions images assemblies field_refs referenced_assemblies attribute_data attribute_ranges unresolved_types unresolved_ranges windows_runtime_types windows_runtime_strings exported_types'.split()
tables={n:struct.unpack_from('<II',meta,8+i*8) for i,n in enumerate(names)}
off,size=tables['type_definitions'];types=list(struct.iter_unpack('<IIiiiiii9i8HII',meta[off:off+size]))
def text(ix):
    off,size=tables['strings'];end=meta.index(0,off+ix,off+size)
    return meta[off+ix:end].decode('utf-8')
def read_type(table,index):
    pointer_offset=table+index*8;address=struct.unpack_from('<Q',b,pointer_offset)[0]
    off=offset(address,12);data,bits=struct.unpack_from('<QI',b,off)
    tag=(bits>>16)&255
    out={'type_index':index,'pointer_file_offset':pointer_offset,'address':hex(address),'file_offset':off,'raw_bytes12':b[off:off+12].hex(),'data':data,'bits':hex(bits),'attrs':bits&65535,'type_tag':hex(tag),'num_mods':(bits>>24)&31,'byref':bool(bits&(1<<29)),'pinned':bool(bits&(1<<30)),'valuetype_bit':bool(bits&(1<<31))}
    if tag in [0x11,0x12] and data<len(types):
        t=types[data];out['definition_index']=data;out['definition_name']='.'.join(x for x in [text(t[1]),text(t[0])] if x)
    return out
needle=struct.pack('<QI',38268,0x80110000);positions=[];p=0
while True:
    p=b.find(needle,p)
    if p<0:break
    positions.append(p);p+=1
candidates=[]
for p in positions:
    needle=struct.pack('<Q',va(p));q=0
    while True:
        q=b.find(needle,q)
        if q<0:break
        table=q-53178*8
        try:
            checks=[read_type(table,i) for i in [53178,53179,53187,59047,75036]]
            if checks[0].get('definition_index')==38268 and checks[1].get('definition_index')==38268 and checks[2].get('definition_index')==38268 and checks[3]['type_tag']=='0xa' and checks[4]['type_tag']=='0xc':
                candidates.append(table)
        except (ValueError,struct.error):pass
        q+=1
candidates=sorted(set(candidates));assert len(candidates)==1,candidates
table=candidates[0];class_checks=0;primitive_checks=0;issues=[]
needle=struct.pack('<Q',va(table));q=0;registrations=[]
while True:
    q=b.find(needle,q)
    if q<0:break
    start=q-56
    words=struct.unpack_from('<16Q',b,start)
    if words[10]==len(types)==words[12] and words[7]==va(table) and words[6]>83059:
        registrations.append((start,words))
    q+=1
assert len(registrations)==1,registrations
registration_offset,registration=registrations[0]
table_count=registration[6]
# Check every type pointer is present in a file-backed native table.
all_type_pointers=struct.unpack_from('<'+str(table_count)+'Q',b,table)
for pointer in all_type_pointers: offset(pointer,12)
expected={'Boolean':2,'Char':3,'SByte':4,'Byte':5,'Int16':6,'UInt16':7,'Int32':8,'UInt32':9,'Int64':10,'UInt64':11,'Single':12,'Double':13,'String':14,'IntPtr':24,'UIntPtr':25,'Object':28}
for i,t in enumerate(types):
    rt=read_type(table,t[2])
    if rt['type_tag'] in ['0x11','0x12']:
        class_checks+=1
        if rt['data']!=i:issues.append((i,t[2],rt))
    elif text(t[1])=='System' and text(t[0]) in expected:
        primitive_checks+=1
        if int(rt['type_tag'],16)!=expected[text(t[0])]:issues.append((i,t[2],rt))
assert not issues,issues[:5]
fp=json.loads((OUT/'fp_metadata.json').read_text('utf-8'))
indices=set([53178,53179,53187,75036,75037])
for field in fp['fields']:indices.add(field['type_index'])
for m in fp['methods']:
    indices.add(m['return_type_index']);indices.update(x['type_index'] for x in m['parameters'])
records=[read_type(table,i) for i in sorted(indices)]
field_offsets_table_offset=offset(registration[11],len(types)*8)
fp_offsets_va=struct.unpack_from('<Q',b,field_offsets_table_offset+38268*8)[0]
fp_offsets_offset=offset(fp_offsets_va,42*4)
field_offsets=struct.unpack_from('<42i',b,fp_offsets_offset)
fp_fields=[]
for field,native_offset in zip(fp['fields'],field_offsets):
    rt=read_type(table,field['type_index'])
    fp_fields.append({'name':field['name'],'metadata_field_index':field['index'],'native_offset':native_offset,'type_index':field['type_index'],'attrs':rt['attrs'],'type_tag':rt['type_tag'],'constant_literal':bool(rt['attrs']&0x40),'static':bool(rt['attrs']&0x10),'readonly':bool(rt['attrs']&0x20)})
out={'target_sha256':pe['sha256'],'layout_source':'https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/Il2CppClass.cs','admission':'unique structurally consistent native Il2CppMetadataRegistration and type pointer array; registration routine not executed','registration':{'file_offset':registration_offset,'address':hex(va(registration_offset)),'raw_bytes':b[registration_offset:registration_offset+128].hex(),'words':[hex(x) for x in registration]},'table_file_offset':table,'table_va':hex(va(table)),'table_count':table_count,'validation':{'all_native_type_pointers_file_backed':len(all_type_pointers),'all_class_and_value_type_byval_declarations_match':class_checks,'system_primitive_byval_tags_match':primitive_checks,'field_offsets_type_count_matches_metadata':len(types),'issues':issues},'types':records,'fp_field_offsets':{'table_pointer_va':hex(registration[11]),'table_pointer_file_offset':field_offsets_table_offset,'selected_pointer_file_offset':field_offsets_table_offset+38268*8,'selected_va':hex(fp_offsets_va),'selected_file_offset':fp_offsets_offset,'fields':fp_fields}}
(OUT/'native_types.json').write_text(json.dumps(out,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in out.items() if k!='types'}))
for x in records:
    print(x['type_index'],x['type_tag'],x.get('definition_name','primitive or referenced type'),hex(x['attrs']),x['byref'])

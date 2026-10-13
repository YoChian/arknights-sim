"""Decode AttributesData custom attribute declarations from v29 metadata.

Only declaration arguments are recovered here. Constructor/GetRange effects
must be corroborated against native code; no target constructors execute.
"""
from pathlib import Path
import json,struct,hashlib
from metadata_blob import Cursor,primitive_value
OUT=Path(__file__).parent
source=OUT/'export_native_fields.py';ns={'__file__':str(source)}
exec(source.read_text('utf-8').split('roots={')[0],ns)
types,fields,methods,parameters,meta,tables,text,fullname,native_type,rows,images=[ns[k] for k in ['types','fields','methods','parameters','meta','tables','text','fullname','native_type','rows','images']]
properties=rows('properties','<IiiII')
attribute_ranges=rows('attribute_ranges','<II')

def read_encoded_value(cursor):
    start=cursor.pos;tag=cursor.unpack('B');enum=None
    if tag==0x55:
        enum_index=cursor.sint();enum=native_type(enum_index)
        assert enum.get('is_enum')
        tag=int(native_type(types[enum['definition_index']][5])['type_tag'],16)
    value=primitive_value(cursor,tag)
    out={'type_tag':hex(tag),'value':value,'metadata_file_offset':start,'raw_bytes':meta[start:cursor.pos].hex()}
    if enum:out['enum_native_type']=enum
    if tag==12:out['float32_bits']=hex(int.from_bytes(struct.pack('<f',value),'little'))
    return out

def member(cursor,definition,kind):
    index=cursor.sint()
    if index<0:index=-(index+1);definition=cursor.uint()
    t=types[definition]
    start,count=t[8],t[19]
    if kind=='property':start,count=t[11],t[18]
    assert 0<=index<count
    absolute=start+index;record=fields[absolute] if kind=='field' else properties[absolute]
    return {'declaring_definition':definition,'declaring_type':fullname(definition),'member_index':absolute,'member_name':text(record[0])}

def attributes_for_field(owner,field_index):
    token=fields[field_index][2]
    img=next(x for x in images if x[2]<=owner<x[2]+x[3])
    possibilities=[i for i in range(img[8],img[8]+img[9]) if attribute_ranges[i][0]==token]
    if not possibilities:return {'field':text(fields[field_index][0]),'field_index':field_index,'token':hex(token),'attributes':[]}
    assert len(possibilities)==1
    index=possibilities[0];_,begin=attribute_ranges[index]
    end=attribute_ranges[index+1][1]
    blob_offset=tables['attribute_data'][0]+begin;blob_end=tables['attribute_data'][0]+end
    cursor=Cursor(meta,blob_offset,blob_end);count=cursor.uint()
    assert count<100
    ctor_indices=[cursor.unpack('i') for _ in range(count)]
    parsed=[]
    for ctor in ctor_indices:
        method=methods[ctor];definition=method[1]
        assert text(method[0])=='.ctor'
        args,fieldcount,propertycount=cursor.uint(),cursor.uint(),cursor.uint()
        assert args==method[9] and fieldcount<128 and propertycount<128
        arguments=[read_encoded_value(cursor) for _ in range(args)]
        named=[]
        for kind,n in [('field',fieldcount),('property',propertycount)]:
            for _ in range(n):
                value=read_encoded_value(cursor);named.append({'kind':kind,'value':value,**member(cursor,definition,kind)})
        parsed.append({'attribute_type':fullname(definition),'attribute_definition_index':definition,'ctor_metadata_method_index':ctor,'ctor_token':hex(method[5]),'ctor_parameter_names':[text(p[0]) for p in parameters[method[3]:method[3]+method[9]]],'arguments':arguments,'named_arguments':named})
    assert cursor.pos==blob_end,(text(fields[field_index][0]),cursor.pos,blob_end)
    return {'field':text(fields[field_index][0]),'field_index':field_index,'token':hex(token),'metadata_field_record_file_offset':tables['fields'][0]+field_index*12,'image':text(img[0]),'range_index':index,'range_record_file_offset':tables['attribute_ranges'][0]+index*8,'range_raw_bytes':meta[tables['attribute_ranges'][0]+index*8:tables['attribute_ranges'][0]+index*8+8].hex(),'attribute_blob_file_offset':blob_offset,'attribute_blob_end_offset':blob_end,'attribute_blob_raw_bytes':meta[blob_offset:blob_end].hex(),'exact_blob_consumption':True,'attributes':parsed}

def decode_default(field_index):
    record=next((r for r in ns['defaults'] if r[0]==field_index),None)
    if not record:return None
    _,type_index,data_index=record
    if data_index<0:return {'value':None,'data_index':data_index}
    nt=native_type(type_index);tag=int(nt['type_tag'],16)
    if nt.get('is_enum'):tag=int(native_type(types[nt['definition_index']][5])['type_tag'],16)
    p=tables['default_data'][0]+data_index
    cursor=Cursor(meta,p,tables['default_data'][0]+tables['default_data'][1])
    value=primitive_value(cursor,tag)
    return {'value':value,'native_type':nt,'metadata_file_offset':p,'raw_bytes':meta[p:cursor.pos].hex()}

selected=[];enemy_fields=[]
for owner in [4132,4501]:
    t=types[owner]
    for field_index in range(t[8],t[8]+t[19]):
        if owner==4132:selected.append(attributes_for_field(owner,field_index))
        if owner==4501:enemy_fields.append(attributes_for_field(owner,field_index))
constants={}
for owner in [38168,10717,10665,1624,10194,9892,38209,38210,38211,38212,38171,38184,9863,4688,38182,38183,4513]:
    t=types[owner]
    result=[]
    for field_index in range(t[8],t[8]+t[19]):
        rt=native_type(fields[field_index][1])
        if rt['attrs']&64:
            result.append({'field':text(fields[field_index][0]),'field_index':field_index,'default':decode_default(field_index)})
    constants[fullname(owner)]=result
enum_values={r['default']['value']:r['field'] for r in constants['Torappu.AttributeType']}
for item in selected:
    for a in item['attributes']:
        for v in a['arguments']:
            if v.get('enum_native_type',{}).get('definition_index')==38168:v['enum_name']=enum_values.get(v['value'])
out={'metadata_sha256':hashlib.sha256(meta).hexdigest(),'target_sha256':ns['registration']['target_sha256'],'attribute_data_table':tables['attribute_data'],'attribute_ranges_table':tables['attribute_ranges'],'attribute_fields':selected,'enemy_data_field_attributes':enemy_fields,'metadata_literal_constants':constants,'primary_sources':['https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/CustomAttributeDataReader.cs','https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/Il2CppExecutor.cs','https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Extensions/BinaryReaderExtensions.cs','https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/MetadataClass.cs'],'source_accessed':'2026-10-13','limits':['Declarative custom attributes parsed with exact end-of-blob and ctor-arity checks. Constructors/GetRange/clamping are not executed or presumed here.','Only required primitive/enum attribute tags are accepted; unsupported encodings fail instead of guessing.','Literal metadata constants differ from fields populated by runtime .cctor or configuration.']}
(OUT/'attribute_meta.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'fields':len(selected),'attribute_meta_fields':sum(any(a['attribute_definition_index']==4128 for a in f['attributes']) for f in selected),'critical':[(f['field'],f['attributes']) for f in selected if f['field'] in ['maxHp','atk','def','magicResistance','moveSpeed','attackSpeed','baseAttackTime']],'constants':{k:[{'field':r['field'],'value':r['default']['value'] if r['default'] else None} for r in v] for k,v in constants.items()}},ensure_ascii=False))

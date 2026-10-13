# V8 derivative of preserved v7 exporter SHA256 f1b7fa62c77d95af9100f1f7140e3fe9c6581b7cdb03e2c3daa046d6b7476f73
# V7 derivative; preserved v6 exporter SHA256 a7c9d5f6d051ce5779dd1d50cb14fd50ff9d883754960884161adf120c620fd9
# Targeting-only derivative of v4 verified exporter; prior source SHA256 fe497d6d0a2f5b94c8470bd3e9c45d985af27f59159a8dcc941d8e026750246c
"""Read-only native type/field/size evidence for enemy and movement recovery.

Reuses the already validated v3 metadata registration. Generic-definition
offsets are not silently promoted to closed generic value-type layouts.
"""
from pathlib import Path
import json,struct,hashlib

OUT=Path(__file__).parent
PREVIOUS=OUT.parents[1]/'native_v3'/'fixedpoint'
SOURCE=PREVIOUS/'inspect_native_types.py'
ns={'__file__':str(SOURCE)}
exec(SOURCE.read_text('utf-8').split("needle=struct.pack('<QI',38268")[0],ns)
b,meta,types,tables,text,offset,va=[ns[x] for x in ['b','meta','types','tables','text','offset','va']]
registration=json.loads((PREVIOUS/'native_types.json').read_text('utf-8'))
assert hashlib.sha256(b).hexdigest()==registration['target_sha256']
assert hashlib.sha256(meta).hexdigest()=='d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f'
TYPE_TABLE=registration['table_file_offset']
FIELD_TABLE=registration['fp_field_offsets']['table_pointer_file_offset']
SIZE_TABLE=offset(int(registration['registration']['words'][13],16),len(types)*8)
def rows(name,fmt):
    start,size=tables[name];width=struct.calcsize(fmt);assert size%width==0
    return list(struct.iter_unpack(fmt,meta[start:start+size]))
fields=rows('fields','<IiI');methods=rows('methods','<IiiiiI4H');parameters=rows('parameters','<IIi')
nested=rows('nested_types','<i');images=rows('images','<IiiIiIiIiI');defaults=rows('field_defaults','<iii')
default_by_field={x[0]:x for x in defaults};parents={}
for i,t in enumerate(types):
    if t[21]:
        for child in nested[t[12]:t[12]+t[21]]:
            assert child[0] not in parents;parents[child[0]]=i
def fullname(index):
    t=types[index]
    return fullname(parents[index])+'.'+text(t[0]) if index in parents else '.'.join(x for x in [text(t[1]),text(t[0])] if x)
def image(index):return next(text(x[0]) for x in images if x[2]<=index<x[2]+x[3])
tags={1:'Void',2:'Boolean',3:'Char',4:'SByte',5:'Byte',6:'Int16',7:'UInt16',8:'Int32',9:'UInt32',10:'Int64',11:'UInt64',12:'Single',13:'Double',14:'String',24:'IntPtr',25:'UIntPtr',28:'Object'}
generic_instances={}
def native_type_address(address,depth=0):
    off=offset(address,12);data,bits=struct.unpack_from('<QI',b,off);tag=(bits>>16)&255
    out={'address':hex(address),'file_offset':off,'raw_bytes12':b[off:off+12].hex(),'data':data,'bits':hex(bits),'attrs':bits&65535,'type_tag':hex(tag),'byref':bool(bits&(1<<29)),'valuetype_bit':bool(bits&(1<<31))}
    if tag in [0x11,0x12] and data<len(types):
        out.update(definition_index=data,name=fullname(data),is_value_type=bool(types[data][25]&1),is_enum=bool(types[data][25]&2))
    elif tag in tags:out['name']=tags[tag]
    elif depth>=8:out['name']='recursive/complex type at '+hex(address)
    elif tag in [0xf,0x1d]:
        out['element']=native_type_address(data,depth+1);out['name']=out['element']['name']+('*' if tag==0xf else '[]')
    elif tag==0x14:
        array_off=offset(data,32);etype,rank,numsizes,numlobounds,sizes,lobounds=struct.unpack_from('<QBBB5xQQ',b,array_off)
        assert 1<=rank<=32 and numsizes<=rank and numlobounds<=rank
        if numsizes:offset(sizes,4*numsizes)
        if numlobounds:offset(lobounds,4*numlobounds)
        out['element']=native_type_address(etype,depth+1)
        out['array_type_record']={'va':hex(data),'file_offset':array_off,'bytes32':b[array_off:array_off+32].hex(),'rank':rank,'numsizes':numsizes,'numlobounds':numlobounds,'sizes_pointer':hex(sizes),'lobounds_pointer':hex(lobounds),'source':'https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/Il2CppClass.cs Il2CppArrayType (accessed 2026-10-13); x64 native record/element pointers verified'}
        out['name']=out['element']['name']+'['+','*(rank-1)+']'
    elif tag==0x15:
        gc_off=offset(data,32);type_ptr,inst_ptr,method_ptr,cached=struct.unpack_from('<4Q',b,gc_off)
        generic=native_type_address(type_ptr,depth+1)
        inst_off=offset(inst_ptr,16);argc,argv=struct.unpack_from('<2Q',b,inst_off)
        assert 0<argc<64
        arg_off=offset(argv,argc*8);argptrs=struct.unpack_from('<'+str(argc)+'Q',b,arg_off)
        arguments=[native_type_address(p,depth+1) for p in argptrs]
        name=generic['name']+'<'+','.join(a['name'] for a in arguments)+'>'
        gc={'class_va':hex(data),'class_file_offset':gc_off,'raw_bytes32':b[gc_off:gc_off+32].hex(),'definition':generic,'class_inst_va':hex(inst_ptr),'class_inst_file_offset':inst_off,'class_inst_bytes16':b[inst_off:inst_off+16].hex(),'argument_pointer_file_offset':arg_off,'argument_pointers':[hex(p) for p in argptrs],'arguments':arguments,'method_inst_pointer':hex(method_ptr),'cached_class_pointer':hex(cached),'name':name,'layout_status':'Generic definition field offsets are not a concrete closed layout; require instantiated native member accesses for offsets/defaults'}
        out.update(name=name,generic_instance=gc,definition_index=generic.get('definition_index'),is_value_type=generic.get('is_value_type',False))
        generic_instances[hex(data)]=gc
    elif tag in [0x13,0x1e]:out['name']=('VAR' if tag==0x13 else 'MVAR')+'#'+str(data)
    else:out['name']='unresolved tag '+hex(tag)
    return out
def native_type(index):
    assert 0<=index<registration['table_count']
    ptr_off=TYPE_TABLE+index*8;address=struct.unpack_from('<Q',b,ptr_off)[0]
    out=native_type_address(address);out.update(type_index=index,pointer_record_file_offset=ptr_off)
    return out

root_names=['UnityEngine.Physics2D', 'UnityEngine.PhysicsScene2D', 'UnityEngine.SimulationMode2D', 'UnityEngine.Rigidbody2D', 'UnityEngine.RigidbodyType2D', 'UnityEngine.Collider2D', 'UnityEngine.CircleCollider2D', 'UnityEngine.BoxCollider2D', 'UnityEngine.CapsuleCollider2D', 'UnityEngine.ContactFilter2D', 'UnityEngine.Transform', 'UnityEngine.Bounds', 'Torappu.Battle.Box2dPhysicsUtil', 'Torappu.Battle.PhysicsRange', 'Torappu.Battle.BObject', 'Torappu.Battle.Entity', 'Torappu.Battle.VisualObject']
roots={i for i in range(len(types)) if fullname(i) in root_names}
assert len(roots)==len(root_names), sorted(set(root_names)-{fullname(i) for i in roots})
selected=set(roots)
def add_base(index):
    parent_index=types[index][4]
    if parent_index<0:return
    parent=native_type(parent_index)
    definition=parent.get('definition_index')
    if definition is not None and definition not in selected:
        selected.add(definition);add_base(definition)
for index in list(selected):add_base(index)
# Include concrete vector/value definitions referenced by primary fields.
for index in list(selected):
    t=types[index]
    for field in fields[t[8]:t[8]+t[19]]:
        rt=native_type(field[1]);di=rt.get('definition_index')
        if di is not None and rt.get('is_value_type') and any(s in rt['name'] for s in ['Vector','GridPosition','FP','Direction','Checkpoint','MotionMode','Obscured']):
            selected.add(di);add_base(di)
resolved=[]
for index in sorted(selected):
    t=types[index];fs,fc=t[8],t[19]
    ptr_off=FIELD_TABLE+index*8;pointer=struct.unpack_from('<Q',b,ptr_off)[0]
    field_off=offset(pointer,fc*4) if fc else None
    actual_offsets=struct.unpack_from('<'+str(fc)+'i',b,field_off) if fc else []
    native_fields=[]
    for ordinal,(field,location) in enumerate(zip(fields[fs:fs+fc],actual_offsets)):
        rt=native_type(field[1]);attrs=rt['attrs'];row={'name':text(field[0]),'index':fs+ordinal,'token':hex(field[2]),'metadata_file_offset':tables['fields'][0]+(fs+ordinal)*12,'offset':location,'offset_hex':hex(location),'offset_record_file_offset':field_off+ordinal*4,'native_type':rt,'static':bool(attrs&16),'literal':bool(attrs&64),'readonly':bool(attrs&32),'layout_space':'literal no storage' if attrs&64 else 'static_fields' if attrs&16 else 'instance including object/boxed header'}
        if fs+ordinal in default_by_field:
            _,ti,data_index=default_by_field[fs+ordinal];start=tables['default_data'][0]+data_index
            row['metadata_default_raw']={'type_index':ti,'data_index':data_index,'file_offset':start if data_index>=0 else None,'bytes16':meta[start:start+16].hex() if data_index>=0 else None,'limits':'Raw blob only; v29 int32/string compression must be decoded by a verified reader before interpretation'}
        native_fields.append(row)
    size_ptr_off=SIZE_TABLE+index*8;size_pointer=struct.unpack_from('<Q',b,size_ptr_off)[0];size_off=offset(size_pointer,16)
    instance_size,native_size,static_size,thread_size=struct.unpack_from('<4I',b,size_off)
    native_methods=[]
    for method_index in range(t[9],t[9]+t[17]):
        method=methods[method_index];assert method[1]==index
        native_methods.append({'name':text(method[0]),'metadata_method_index':method_index,'metadata_record_file_offset':tables['methods'][0]+method_index*32,'token':hex(method[5]),'flags':hex(method[6]),'iflags':hex(method[7]),'virtual_slot':method[8],'return_type':native_type(method[2]),'parameters':[{'name':text(p[0]),'type':native_type(p[2])} for p in parameters[method[3]:method[3]+method[9]]]})
    resolved.append({'definition_index':index,'name':fullname(index),'image':image(index),'metadata_record_file_offset':tables['type_definitions'][0]+index*92,'byval_type':native_type(t[2]),'value_type':bool(t[25]&1),'enum':bool(t[25]&2),'generic_container_index':t[6],'base_type':native_type(t[4]) if t[4]>=0 else None,'field_pointer_record_file_offset':ptr_off,'field_array_va':hex(pointer),'field_array_file_offset':field_off,'sizes':{'pointer_record_file_offset':size_ptr_off,'record_va':hex(size_pointer),'record_file_offset':size_off,'bytes16':b[size_off:size_off+16].hex(),'instance_with_header':instance_size,'native_size_raw':native_size,'static_size':static_size,'thread_static_size':thread_size,'limits':'UINT32_MAX native size is unsupported/unavailable, not an allocation size'},'fields':native_fields,'methods':native_methods})
by_definition={t['definition_index']:t for t in resolved}
for t in resolved:
    ancestors=[];current=t
    while current.get('base_type') and current['base_type'].get('definition_index') in by_definition:
        current=by_definition[current['base_type']['definition_index']];ancestors.append(current['definition_index'])
        assert len(ancestors)<32
    t['inheritance_chain_definition_indices']=ancestors
    t['inherited_instance_layout']=[{'owner':ancestor['name'],'name':f['name'],'offset':f['offset'],'offset_hex':f['offset_hex'],'type':f['native_type']['name'],'offset_record_file_offset':f['offset_record_file_offset']} for ancestor in reversed([by_definition[i] for i in ancestors]) for f in ancestor['fields'] if not f['static']]
map_sources=[]
for module in sorted(set(t['image'] for t in resolved)):
    map_path=OUT.parents[1]/'core'/(module.removesuffix('.dll')+'_candidate_method_map.json')
    if not map_path.exists():continue
    map_bytes=map_path.read_bytes();map_sources.append({'path':str(map_path),'sha256':hashlib.sha256(map_bytes).hexdigest()})
    wanted={m['metadata_method_index']:m for t in resolved if t['image']==module for m in t['methods']}
    for candidate in json.loads(map_bytes):
        dest=wanted.get(candidate['metadata_method_index'])
        if dest is None:continue
        dest['native_candidate']=candidate
        if candidate.get('candidate_va'):
            address=int(candidate['candidate_va'],16);entry=candidate['table_entry_file_offset']
            assert struct.unpack_from('<Q',b,entry)[0]==address
            assert b[offset(address,16):offset(address,16)+16].hex()==candidate['first_16_bytes']
            dest['native_candidate']['pointer_and_first16_currently_verified']=True
out={'target_sha256':registration['target_sha256'],'metadata_sha256':hashlib.sha256(meta).hexdigest(),'registration_reference_path':str(PREVIOUS/'native_types.json'),'registration_reference_sha256':hashlib.sha256((PREVIOUS/'native_types.json').read_bytes()).hexdigest(),'helper_source_path':str(SOURCE),'helper_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'method_map_sources':map_sources,'roots':sorted(roots),'types':resolved,'generic_instances':list(generic_instances.values()),'limits':['Static registration/type/offset/size records; no runtime process or game execution','Declared generic-definition offsets are not asserted as concrete closed Undefinable<T> ABI','Object instance offsets include16-byte object header; verified value-type member instructions must corroborate unboxed offsets','Methods metadata identities/pinned candidate pointers do not themselves prove merge or movement algorithms']}
(OUT/'native_fields.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
slim=[{'definition_index':t['definition_index'],'name':t['name'],'value_type':t['value_type'],'generic_container_index':t['generic_container_index'],'sizes':t['sizes'],'base_type':t['base_type']['name'] if t['base_type'] else None,'base_definition_indices':t['inheritance_chain_definition_indices'],'instance':[{k:f[k] for k in ['name','offset_hex','offset_record_file_offset']}|{'type':f['native_type']['name']} for f in t['fields'] if not f['static']],'inherited_instance_layout':t['inherited_instance_layout']} for t in resolved]
(OUT/'field_offsets.json').write_text(json.dumps({'target_sha256':registration['target_sha256'],'types':slim,'limits':out['limits']},ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'types':len(resolved),'fields':sum(len(t['fields']) for t in resolved),'generic_instances':len(generic_instances)}))
for t in resolved:
    if t['definition_index'] in [4501,4502,4503,4508,4657,4658,4648,4649]:
        print(t['definition_index'],t['name'],t['sizes']['instance_with_header'],[(f['offset_hex'],f['name'],f['native_type']['name']) for f in t['fields'] if not f['static']])

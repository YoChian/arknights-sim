"""Source-bound Unity Physics2D candidate arrays and selected raw bodies.

The adjacent names/function arrays suggest a pairing, but no direct registration
loop was located by the bounded .text LEA search. The pairing remains explicitly
unproven. Raw candidate bodies are not promoted to resolved engine interfaces.
"""
from pathlib import Path
import bisect
import hashlib
import json
import struct
import sys

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
sys.path.insert(0,str(BASE/'tools/python'))
import capstone

inventory=json.loads((OUT/'engine_inventory.json').read_text('utf-8'))['engine']
path=Path(inventory['source_pin']['path']);blob=path.read_bytes()
assert hashlib.sha256(blob).hexdigest()==inventory['source_pin']['sha256']
image_base=int(inventory['image_base'],16)
sections=inventory['sections']


def off(address,length=1):
    for s in sections:
        delta=address-image_base-int(s['rva'],16)
        if 0<=delta and delta+length<=s['raw_size']:
            return s['file_offset']+delta
    raise ValueError('not file backed')


def va(offset):
    for s in sections:
        delta=offset-s['file_offset']
        if 0<=delta<s['raw_size']:return image_base+int(s['rva'],16)+delta
    raise ValueError('not file backed')


def text(address):
    try:start=off(address)
    except ValueError:return None
    end=blob.find(b'\0',start,min(start+400,len(blob)))
    if end<0:return None
    raw=blob[start:end]
    if raw.startswith(b'UnityEngine.') and all(32<=x<127 for x in raw):return raw.decode('ascii')
    return None


pe=struct.unpack_from('<I',blob,0x3c)[0]
exception_rva,exception_size=struct.unpack_from('<II',blob,pe+24+112+3*8)
exception_off=off(image_base+exception_rva,exception_size)
triples=list(struct.iter_unpack('<III',blob[exception_off:exception_off+exception_size]))
starts=[x[0] for x in triples]
by_start={x[0]:x for x in triples}
parents={}
for row in triples:
    unwind=off(image_base+row[2],4)
    flags=blob[unwind]>>3;count=blob[unwind+2]
    if flags&4:
        parent=struct.unpack_from('<III',blob,unwind+4+((count+1)//2)*4)
        assert by_start.get(parent[0])==parent
        parents[row[0]]=parent[0]


def root(start):
    seen=set()
    while start in parents:
        assert start not in seen
        seen.add(start);start=parents[start]
    return start


groups={}
for row in triples:groups.setdefault(root(row[0]),[]).append(row)
engine=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64)


def function_at(address):
    index=bisect.bisect_right(starts,address-image_base)-1
    assert index>=0
    row=triples[index]
    if address-image_base in by_start:
        function_root=root(address-image_base)
        group=groups[function_root]
        boundary='exact PE unwind/CHAININFO siblings'
    else:
        following=min((x for x in callbacks if x>address),default=address+512)
        limit=min(512,following-address);start=off(address,limit)
        instructions=[]
        for inst in engine.disasm(blob[start:start+limit],address):
            if inst.mnemonic=='int3':break
            instructions.append(inst)
            if inst.mnemonic in ('ret','jmp'):break
        assert instructions and instructions[-1].mnemonic in ('ret','jmp'),hex(address)
        function_root=address-image_base
        group=[(function_root,instructions[-1].address+instructions[-1].size-image_base,0)]
        boundary='bounded leaf ending RET/JMP; not an inferred previous unwind function'
    result={'address':hex(image_base+function_root),'entry_va':hex(address),'boundary':boundary,'ranges':[]}
    for begin,end,unwind in group:
        start=off(image_base+begin,end-begin);raw=blob[start:start+end-begin]
        result['ranges'].append({'start':hex(image_base+begin),'end_exclusive':hex(image_base+end),
            'file_offset':start,'unwind_rva':hex(unwind),'sha256':hashlib.sha256(raw).hexdigest(),
            'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str}
                            for i in engine.disasm(raw,image_base+begin)]})
    return result


anchor=next(x for x in inventory['bounded_physics_strings'] if x['text']=='UnityEngine.Physics2D::get_autoSyncTransforms')
pointer=struct.pack('<Q',int(anchor['va'],16))
hits=[];cursor=0
while True:
    cursor=blob.find(pointer,cursor)
    if cursor<0:break
    hits.append(cursor);cursor+=1
assert len(hits)==1
begin=end=hits[0]
while text(struct.unpack_from('<Q',blob,begin-8)[0]):begin-=8
while text(struct.unpack_from('<Q',blob,end+8)[0]):end+=8
count=(end-begin)//8+1
assert count==507 and struct.unpack_from('<Q',blob,end+8)[0]==0
function_table=end+16
names=[text(struct.unpack_from('<Q',blob,begin+8*i)[0]) for i in range(count)]
callbacks=list(struct.unpack_from('<'+str(count)+'Q',blob,function_table))
assert all(any(s['name']=='.text' and image_base+int(s['rva'],16)<=a<image_base+int(s['rva'],16)+s['raw_size'] for s in sections) for a in callbacks)
assert struct.unpack_from('<Q',blob,function_table+8*count)[0]==0
array_addresses={va(begin):'names',va(function_table):'callbacks'}
references=[]
text_section=next(s for s in sections if s['name']=='.text')
end_text=text_section['file_offset']+text_section['raw_size']
for prefix in (b'\x48\x8d',b'\x4c\x8d'):
    cursor=text_section['file_offset']
    while True:
        cursor=blob.find(prefix,cursor,end_text)
        if cursor<0:break
        if cursor+7<=end_text and blob[cursor+2]&0xc7==5:
            target=va(cursor)+7+struct.unpack_from('<i',blob,cursor+3)[0]
            if target in array_addresses:references.append({'instruction_va':hex(va(cursor)),
                'array':array_addresses[target],'target_va':hex(target),'bytes':blob[cursor:cursor+7].hex()})
        cursor+=1
registration=[function_at(int(x['instruction_va'],16)) for x in references]
pairing_proven=bool(len(references)==2 and {x['array'] for x in references}=={'names','callbacks'}
                    and registration[0]['address']==registration[1]['address'])
needed={'UnityEngine.Physics2D::get_autoSyncTransforms','UnityEngine.Physics2D::set_autoSyncTransforms',
        'UnityEngine.Physics2D::SyncTransforms','UnityEngine.Physics2D::get_queriesHitTriggers',
        'UnityEngine.Physics2D::get_simulationMode','UnityEngine.Physics2D::set_simulationMode',
        'UnityEngine.Physics2D::Simulate_Internal_Injected',
        'UnityEngine.PhysicsScene2D::OverlapCircleArray_Internal_Injected',
        'UnityEngine.PhysicsScene2D::OverlapBoxArray_Internal_Injected',
        'UnityEngine.ContactFilter2D::CheckConsistency_Injected','UnityEngine.Collider2D::get_bounds_Injected'}
rows=[]
for index,name in enumerate(names):
    if name not in needed:continue
    address=callbacks[index]
    rows.append({'name':name,'index':index,'name_pointer_file_offset':begin+8*index,
        'name_pointer_bytes8':blob[begin+8*index:begin+8*(index+1)].hex(),
        'callback_pointer_file_offset':function_table+8*index,
        'callback_pointer_bytes8':blob[function_table+8*index:function_table+8*(index+1)].hex(),
        'callback_va':hex(address),'raw':function_at(address)})
assert {x['name'] for x in rows}==needed
output={'engine_pin':inventory['source_pin'],'names_table_file_offset':begin,'names_table_va':hex(va(begin)),
        'callback_table_file_offset':function_table,'callback_table_va':hex(va(function_table)),
        'name_count':count,'parallel_array_references':references,'registration_functions':registration,
        'parallel_array_pairing_proven':pairing_proven,
        'selected_candidate_callbacks':rows,'limits':['507 adjacent name/function arrays and zero sentinels are observed; matching-index callback identity is a candidate until registration pairing is proven.',
            'No direct LEA reference to either array start was located in the bounded .text scan. UnityPlayer also contains .tvm0/.Ovo sections; protection behavior is unknown.',
            'No candidate engine callback executed or used to implement overlap/synchronization/CheckConsistency.']}
(OUT/'engine_binding_candidates.json').write_text(json.dumps(output,indent=2),'utf-8')
print('parallel pairing proven',pairing_proven,'entries',count)
for row in rows:print(row['name'],row['callback_va'])

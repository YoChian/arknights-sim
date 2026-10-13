"""Source-bound wrapper and Bounds raw evidence; no target execution."""
from pathlib import Path
import hashlib
import json

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
SOURCE=BASE/'native_v5/lifecycle/prepare.py'
ns={'__file__':str(SOURCE)}
exec(compile(SOURCE.read_text('utf-8').split('selection=json.loads')[0],str(SOURCE),'exec'),ns)
maps=[]
for name in ['Assembly-CSharp','Torappu.Common','UnityEngine.CoreModule','UnityEngine.Physics2DModule']:
    maps+=json.loads((BASE/'core'/f'{name}_candidate_method_map.json').read_text('utf-8'))
byidx={m['metadata_method_index']:m for m in maps}
indices=[280860,280866,280868,318493,318494,318495,318496,318497,318518,
         318514,318515,318570,318577,221678,221679]
records=[]
for index in indices:
    row=byidx[index]
    address=int(row['candidate_va'],16);r=address-ns['base']
    ranges=ns['groups'].get(r)
    if not ranges:
        following=min(int(m['candidate_va'],16) for m in maps if m['candidate_va'] and int(m['candidate_va'],16)>address)
        limit=min(512,following-address)
        off=ns['rva'](r,limit);instructions=[]
        for inst in ns['engine'].disasm(ns['b'][off:off+limit],address):
            if inst.mnemonic=='int3':break
            instructions.append(inst)
            if inst.mnemonic in ('ret','jmp'):break
        assert instructions and instructions[-1].mnemonic in ('ret','jmp')
        ranges=[(r,instructions[-1].address+instructions[-1].size-ns['base'],0)]
    record={'declaring_type':row['type'],'method':row['method'],'metadata_method_index':index,
            'token':row['token'],'candidate_va':hex(address),'ranges':[]}
    for start,end,unwind in ranges:
        off=ns['rva'](start,end-start);blob=ns['b'][off:off+end-start]
        record['ranges'].append({'start':hex(ns['base']+start),'end_exclusive':hex(ns['base']+end),
            'unwind_rva':hex(unwind),'file_offset':off,'sha256':hashlib.sha256(blob).hexdigest(),
            'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str}
                            for i in ns['engine'].disasm(blob,ns['base']+start)]})
    records.append(record)
result={'target_sha256':ns['pe']['sha256'],'source_helper_path':str(SOURCE),
        'source_helper_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'functions':records,
        'limits':['Exact PE unwind/CHAININFO siblings or bounded RET/JMP leaf. Raw identities use explicit metadata index; same-address aliases are not interchangeable.',
                  'Internal-call resolution is static evidence, not execution or proof of live engine state.']}
(OUT/'raw_helpers.json').write_text(json.dumps(result,indent=2),'utf-8')
for r in records:
    print(r['declaring_type'],r['method'],r['candidate_va'])
    for section in r['ranges']:
        for inst in section['instructions']:
            if inst['mnemonic'] in ('call','jmp','lea','subps','addps','addss','subss'):
                print(inst['address'],inst['mnemonic'],inst['operands'])

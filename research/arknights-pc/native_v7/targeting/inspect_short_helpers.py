# V7 derivative of preserved v6 helper SHA256 2748641598f9c63df9c2d0f8e2017b28267143dcdd59e4cc2b961baeda96504d
"""Read-only exact PE sibling ranges for targeting getter/UID checks."""
from pathlib import Path
import hashlib, json

OUT=Path(__file__).parent
BASE=OUT.parents[1]
SOURCE=BASE/'native_v5/lifecycle/prepare.py'
ns={'__file__':str(SOURCE)}
exec(compile(SOURCE.read_text('utf-8').split('selection=json.loads')[0],str(SOURCE),'exec'),ns)
maps=[]
for name in ['Assembly-CSharp','mscorlib','Torappu.Common']:
    maps+=json.loads((BASE/'core'/f'{name}_candidate_method_map.json').read_text('utf-8'))
byidx={m['metadata_method_index']:m for m in maps}
fields=json.loads((OUT/'native_fields.json').read_text('utf-8'))
indices=[63134,76379,75910,62954,63041,64279,64292,220346,220367,220518,220541,220545]
selected=[byidx[idx] for idx in indices]
for address,name in [(0x185528350,'WeightedTarget_Entity_cctor_canonical_Object'),
                     (0x1844dc660,'EnumInt_conversion_caller_bound'),
                     (0x186727990,'SideTypes_slot_single_bit_equals_caller_bound'),
                     (0x185ed91c0,'FP_relational_helper_91c0'),
                     (0x185ed91f0,'FP_relational_helper_91f0')]:
    selected.append({'candidate_va':hex(address),'metadata_method_index':None,'token':'raw_call_target',
                     'type':'CallerBoundGeneric','method':name})
output=[]
for m in selected:
    idx=m['metadata_method_index']
    address=int(m['candidate_va'],16);r=address-ns['base']
    ranges=ns['groups'].get(r)
    if not ranges:
        limit=min(512,min(int(m['candidate_va'],16) for m in maps if m['candidate_va'] and int(m['candidate_va'],16)>address)-address)
        off=ns['rva'](r,limit)
        ins=[]
        for i in ns['engine'].disasm(ns['b'][off:off+limit],address):
            if i.mnemonic=='int3':break
            ins.append(i)
            if i.mnemonic in ['ret','jmp']:break
        assert ins and ins[-1].mnemonic in ['ret','jmp']
        ranges=[(r,ins[-1].address+ins[-1].size-ns['base'],0)]
    rec={'name':m['type']+'.'+m['method'],'metadata_method_index':idx,'token':m['token'],
         'candidate_va':m['candidate_va'],'ranges':[]}
    for begin,end,uw in ranges:
        off=ns['rva'](begin,end-begin);blob=ns['b'][off:off+end-begin]
        rec['ranges'].append({'start':hex(ns['base']+begin),'end_exclusive':hex(ns['base']+end),
            'unwind_rva':hex(uw),'file_offset':off,'sha256':hashlib.sha256(blob).hexdigest(),
            'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,
                             'operands':i.op_str} for i in ns['engine'].disasm(blob,ns['base']+begin)]})
    output.append(rec)
(OUT/'raw_helpers.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],
    'helper_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'functions':output,
    'limits':['Exact recursive CHAININFO siblings or bounded leaf ending RET/JMP.',
              'Static normal path only. No live hotfix/target execution.']},indent=2),'utf-8')
for rec in output:
    print(rec['name'],rec['candidate_va'])
    for group in rec['ranges']:
        for i in group['instructions']:
            if i['mnemonic'] in ['mov','movzx','xor','jb','seta','ret','jmp']:
                print(i['address'],i['mnemonic'],i['operands'])

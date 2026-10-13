"""Read-only exact PE sibling ranges for targeting getter/UID checks."""
from pathlib import Path
import hashlib, json

OUT=Path(__file__).parent
BASE=OUT.parents[1]
SOURCE=BASE/'native_v5/lifecycle/prepare.py'
ns={'__file__':str(SOURCE)}
exec(compile(SOURCE.read_text('utf-8').split('selection=json.loads')[0],str(SOURCE),'exec'),ns)
maps=[]
for name in ['Assembly-CSharp','mscorlib']:
    maps+=json.loads((BASE/'core'/f'{name}_candidate_method_map.json').read_text('utf-8'))
byidx={m['metadata_method_index']:m for m in maps}
fields=json.loads((OUT/'native_fields.json').read_text('utf-8'))
indices=[75084,75085,75086,241404]
for t in fields['types']:
    if t['name']=='Torappu.Battle.AdvancedSelector':
        indices += [m['metadata_method_index'] for m in t['methods'] if m['name'] in ['get_ignoreHitRange','get_forceIgnoreCamouflage']]
output=[]
for idx in indices:
    m=byidx[idx]
    address=int(m['candidate_va'],16);r=address-ns['base']
    ranges=ns['groups'].get(r)
    if not ranges:
        following=min(int(m['candidate_va'],16) for m in maps if m['candidate_va'] and int(m['candidate_va'],16)>address)
        assert following-address<=512
        off=ns['rva'](r,following-address)
        ins=list(ns['engine'].disasm(ns['b'][off:off+following-address],address))
        while ins and ins[-1].mnemonic in ['int3','nop']:ins.pop()
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

"""Bound factory and reused dependency native bytes; original CHAININFO."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v6/skill/raw_followups.py';ns={'__file__':str(source)}
exec(source.read_text(encoding='utf-8').split('engine=capstone.')[0],ns)
capstone=ns['capstone'];engine=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64)
b,base,rva,triples,by_start,root,parents=[ns[k] for k in ['b','base','rva','triples','by_start','root','parents']]
records=[]
for name in ['results_round1.json','reused_results.json','dependency_results.json']:
    records+=json.loads((OUT/name).read_text(encoding='utf-8'))
selected={int(r['result']['address'],16):r.get('selection',{'name':r.get('name')}) for r in records}
selected.update({0x185ed91e0:{'name':'FP.op_LessThanOrEqual','basis':'Exact BornState.OnTick call and fixedpoint metadata folded pointer record'},
                 0x1866e4c50:{'name':'MathUtil.GT Single','basis':'Exact BornState.OnEnter call; previous Float static epsilon evidence'},
                 0x180a7c370:{'name':'Enemy.get_delayToBorn','basis':'Exact BornState.OnEnter call; native fields offset310/314'},
                 0x180ac9550:{'name':'Unit.InitCommonAbilities','metadata_method_index':77671,'token':'0x6012f68','basis':'Metadata pointer and Unit.OnInit exact call'},
                 0x180686740:{'name':'Buff.OnOwnerPostBorn','metadata_method_index':65152,'token':'0x600fe81','basis':'Metadata pointer and Unit.OnBorn exact dispatch'}})
out=[]
for address,e in selected.items():
    start=address-base;spans=[]
    if start in by_start:
        assert root(start)==start, f'candidate begins inside a chained fragment: {address:x}'
        for a,z,u in triples:
            if root(a)!=start:continue
            off=rva(a,z-a);raw=b[off:off+z-a]
            spans.append({'start':hex(base+a),'end_exclusive':hex(base+z),'unwind_rva':hex(u),
                'chain_parent_start':hex(base+parents[a]) if a in parents else None,
                'source_file_offset':off,'source_sha256':ns['hashlib'].sha256(raw).hexdigest(),
                'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str} for i in engine.disasm(raw,base+a)]})
        bounds='Original PE .pdata root plus all recursive UNWIND_INFO CHAININFO siblings'
    else:
        assert address in (0x185ed91e0,0x1866e4c50),f'unbounded leaf requires review: {address:x}'
        off=rva(start,32);decoded=[]
        for i in engine.disasm(b[off:off+32],address):
            assert not i.mnemonic.startswith('j') and i.mnemonic!='call','branching leaf cannot use first-RET bound'
            decoded.append({'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str})
            if i.mnemonic=='ret':break
        assert decoded[-1]['mnemonic']=='ret'
        count=sum(len(bytes.fromhex(i['bytes'])) for i in decoded)
        spans=[{'start':hex(address),'end_exclusive':hex(address+count),'unwind_rva':None,
            'chain_parent_start':None,'source_file_offset':off,
            'source_sha256':ns['hashlib'].sha256(b[off:off+count]).hexdigest(),'instructions':decoded}]
        bounds='Reviewed straight-line metadata/caller leaf ending at first RET; no branch/padding heuristic'
    out.append({'selection':e,'address':hex(address),'bounds':bounds,'ranges':spans})
(OUT/'raw_helpers.json').write_text(json.dumps({'target_path':ns['pe']['path'],'target_sha256':ns['pe']['sha256'],
    'source':'No Java/game execution; all original byte ranges and recursive chain parents preserved',
    'functions':out},indent=2),encoding='utf-8')
print([(r['address'],len(r['ranges'])) for r in out])

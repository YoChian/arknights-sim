"""Bound NPC restore bytes by original unwind/CHAININFO, no Java/game calls."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v6/skill/raw_followups.py';ns={'__file__':str(source)}
exec(source.read_text().split('engine=capstone.')[0],ns)
capstone=ns['capstone'];engine=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64)
b,base,rva,triples,by_start,root=[ns[k] for k in ['b','base','rva','triples','by_start','root']]
selected=json.loads((OUT/'selection.json').read_text())+json.loads((OUT/'selection_extra.json').read_text())
selected += [{'address':hex(a),'method':name,'type':'Shared generic/native helper','basis':'Exact caller MethodInfo + original PE call target'} for a,name in [(0x18536e450,'StateNode.SwitchState'),(0x18536e540,'StateNode.get_data'),(0x18499c9d0,'HierachyStateMachine.SwitchState')]]
out=[]
for e in selected:
 address=int(e['address'],16);start=address-base;assert start in by_start
 spans=[]
 for a,z,u in triples:
  if root(a)!=start:continue
  off=rva(a,z-a);raw=b[off:off+z-a]
  spans.append({'start':hex(base+a),'end_exclusive':hex(base+z),'unwind_rva':hex(u),'source_file_offset':off,'source_sha256':ns['hashlib'].sha256(raw).hexdigest(),'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str} for i in engine.disasm(raw,base+a)]})
 out.append({'selection':e,'address':hex(address),'ranges':spans})
(OUT/'raw_helpers.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],'functions':out},indent=2),encoding='utf-8')
for f in out:
 print(f['selection']['method'],f['address'],sum(len(r['instructions']) for r in f['ranges']))

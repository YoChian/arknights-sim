"""Read exact PE unwind/CHAININFO ranges for preparation helpers; no execution."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v6/skill/raw_followups.py'
ns={'__file__':str(source)}
exec(source.read_text().split('engine=capstone.')[0],ns)
capstone=ns['capstone'];engine=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64)
b,base,rva,triples,by_start,root=[ns[k] for k in ['b','base','rva','triples','by_start','root']]
addresses=[0x18252a520,0x18252a610,0x180ac8420,0x180ac82d0,0x1866e4b90,0x18252b300,0x1806180e0,0x1805f6260,0x1805f6330,0x1805f6180,0x1805f6700,0x1806192c0,0x180ad08a0,0x1805db9c0,0x18210a2a0,0x18210a200,0x18210a350,0x182529ce0,0x180a344b0,0x180a37070,0x180a33dd0]
out=[]
for address in addresses:
 start=address-base
 if start not in by_start:
  assert address==0x1866e4b90
  off=rva(start,64);raw=b[off:off+64];inst=[];size=0
  for i in engine.disasm(raw,address):
   inst.append({'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str});size=i.address+i.size-address
   assert i.mnemonic not in ['call','jmp'] and not i.mnemonic.startswith('j')
   if i.mnemonic=='ret':break
  assert inst[-1]['mnemonic']=='ret' and size<=64
  out.append({'address':hex(address),'ranges':[{'start':hex(address),'end_exclusive':hex(address+size),'source_file_offset':off,'source_sha256':ns['hashlib'].sha256(raw[:size]).hexdigest(),'instructions':inst,'range_provenance':'Metadata exact entry; straightline leaf through first RET; no .pdata entry'}]});continue
 spans=[]
 for a,z,u in triples:
  if root(a)!=start:continue
  off=rva(a,z-a);raw=b[off:off+z-a]
  spans.append({'start':hex(base+a),'end_exclusive':hex(base+z),'unwind_rva':hex(u),'source_file_offset':off,'source_sha256':ns['hashlib'].sha256(raw).hexdigest(),'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str} for i in engine.disasm(raw,base+a)]})
 out.append({'address':hex(address),'ranges':spans})
(OUT/'raw_preparation.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],'functions':out},indent=2),encoding='utf-8')
for f in out:
 print(f['address'])
 for r in f['ranges']:
  for i in r['instructions']:print(i['address'],i['mnemonic'],i['operands'])

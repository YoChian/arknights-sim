"""Bound shared virtual trampoline ranges by exact PE unwind entries."""
from pathlib import Path
import hashlib,json,struct,sys
OUT=Path(__file__).parent;BASE=OUT.parents[1]
sys.path.insert(0,str(BASE/'tools/python'));import capstone
inventory=json.loads((BASE/'core/pe_inventory.json').read_text());pe=next(p for p in inventory if p['path'].endswith('GameAssembly.dll'))
b=Path(pe['path']).read_bytes();assert hashlib.sha256(b).hexdigest()==pe['sha256'];base=int(pe['image_base'],16)
def rva(r,n):
 for s in pe['sections']:
  delta=r-int(s['virtual_address'],16)
  if 0<=delta and delta+n<=s['raw_bytes']:return s['raw_offset']+delta
 raise ValueError('not file backed')
o=struct.unpack_from('<I',b,0x3c)[0];er,ez=struct.unpack_from('<II',b,o+24+112+3*8);eo=rva(er,ez)
triples=[struct.unpack_from('<III',b,eo+i*12) for i in range(ez//12)];by_start={t[0]:t for t in triples};parents={}
for t in triples:
 u=rva(t[2],4);flags=b[u]>>3;count=b[u+2]
 if flags&4:
  p=struct.unpack_from('<III',b,u+4+((count+1)//2)*4);assert by_start[p[0]]==p;parents[t[0]]=p[0]
def root(start):
 seen=set()
 while start in parents:
  assert start not in seen;seen.add(start);start=parents[start]
 return start
engine=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64);out=[]
for address in [0x1805d7cc0,0x18095fc50,0x180961cd0,0x18095dfe0,0x18095edd0,0x180eff930,0x1866e6620,0x1866fc8d0,0x1866fae80,0x180647eb0,0x1806614a0]:
 start=address-base;assert start in by_start
 ranges=[]
 for a,z,u in triples:
  if root(a)!=start:continue
  fileoff=rva(a,z-a);raw=b[fileoff:fileoff+z-a]
  ranges.append({'start':hex(base+a),'end_exclusive':hex(base+z),'unwind_rva':hex(u),'chained':a in parents,'file_offset':fileoff,'sha256':hashlib.sha256(raw).hexdigest(),'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str} for i in engine.disasm(raw,base+a)]})
 out.append({'address':hex(address),'ranges':ranges})
result={'target_path':pe['path'],'target_sha256':pe['sha256'],'source':'Exact .pdata + recursive CHAININFO range groups; no next-function/padding heuristic','functions':out}
(OUT/'raw_followups.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
for f in out:
 print(f['address'])
 for r in f['ranges']:
  for i in r['instructions']:print(i['address'],i['mnemonic'],i['operands'])

"""Exact decoded direct callers of SkillData.InitIfNot, static PE only."""
from pathlib import Path
import json,struct,bisect
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=OUT/'raw_preparation.py';ns={'__file__':str(source)}
exec(source.read_text().split('addresses=')[0],ns)
b,base,triples,engine=[ns[k] for k in ['b','base','triples','engine']]
pe=ns['ns']['pe'];starts=[x[0] for x in triples];target=0x18252a520;found=[]
for section in pe['sections']:
 if section['name'] not in ['il2cpp','.text']:continue
 start=section['raw_offset'];end=start+section['raw_bytes'];p=start
 while True:
  p=b.find(b'\xe8',p,end)
  if p<0:break
  address=base+int(section['virtual_address'],16)+p-start
  if p+5<=end and address+5+struct.unpack_from('<i',b,p+1)[0]==target:
   index=bisect.bisect_right(starts,address-base)-1;t=triples[index] if index>=0 else None
   if t and t[0]<=address-base<t[1]:
    root=ns['root'](t[0]);off=ns['rva'](t[0],t[1]-t[0])
    valid=any(i.address==address and i.mnemonic=='call' for i in engine.disasm(b[off:off+t[1]-t[0]],base+t[0]))
    if valid:found.append({'call_address':hex(address),'root_address':hex(base+root),'source_file_offset':p,'bytes5':b[p:p+5].hex()})
  p+=1
maps=json.loads((BASE/'core/Assembly-CSharp_candidate_method_map.json').read_text());by_address={m['candidate_va']:m for m in maps if m.get('candidate_va')}
for row in found:row['method_candidate']=by_address.get(row['root_address'])
(OUT/'skill_init_xrefs.json').write_text(json.dumps({'target':hex(target),'direct_call_matches':found,'limits':'Only direct E8 matching exact decoded instruction in pdata fragment; excludes virtual/indirect/inlined calls.'},indent=2),encoding='utf-8')
print(json.dumps(found))

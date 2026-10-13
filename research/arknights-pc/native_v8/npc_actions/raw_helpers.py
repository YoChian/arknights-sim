"""Exact original helper ranges, with embedded UID-dispatch tables separated."""
from pathlib import Path
import hashlib,json,struct
OUT=Path(__file__).parent;s=OUT/'prepare.py';n={'__file__':str(s)}
exec(compile(s.read_text('utf8').split('selection=json.loads')[0],str(s),'exec'),n)
targets={
 'ObjectPtr_Entity.value':0x185159d80,'ObjectPtr_Entity.IsValid':0x185159fc0,
 'ObjectExtensions.IsDestroyedOrNull':0x1866e81e0,
 'MathUtil.GE_FP':0x1866e4ba0,'MathUtil.cctor':0x1866e6e50,
 'Buff.get_onEventPriority':next(int(r['candidate_va'],16) for r in n['rows'] if r['token']=='0x600fe43'),
 'ContextPtrStack_Pop_raw':0x185733450,
 'ContextPtrStack_Push_raw':0x185367ff0,
 'Blackboard.TryGetString':0x1823203b0,
}
old_fields=json.loads((OUT.parents[1]/'native_v7/npc/native_fields.json').read_text('utf8'))
for t in old_fields['types']:
 if t['name'].startswith('Torappu.Battle.Action.Nodes.'):
  for m in t['methods']:
   if m['name']=='get_allowedSource':
    targets[t['name']+'.get_allowedSource']=int(m['native_candidate']['candidate_va'],16)
out=[]
for name,va in targets.items():
 ranges=n['groups'].get(va-n['base']);assert ranges,name
 f={'name':name,'address':hex(va),'ranges':[]}
 for a,z,u in ranges:
  off=n['rva'](a,z-a);body=n['b'][off:off+z-a]
  f['ranges'].append({'start':hex(n['base']+a),'end_exclusive':hex(n['base']+z),
   'unwind_rva':hex(u),'source_file_offset':off,'source_sha256':hashlib.sha256(body).hexdigest(),
   'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str}
    for i in n['engine'].disasm(body,n['base']+a)]})
 out.append(f)
va=0x1800c9210;off=n['rva'](va-n['base'],6);body=n['b'][off:off+5]
ins=list(n['engine'].disasm(body,va));assert len(ins)==1 and ins[0].mnemonic=='jmp' and ins[0].op_str=='0x185159fc0' and n['b'][off+5]==0xcc
out.append({'name':'IsValid_direct_call_trampoline','address':hex(va),'ranges':[{
 'start':hex(va),'end_exclusive':hex(va+5),'source_file_offset':off,'source_sha256':hashlib.sha256(body).hexdigest(),
 'boundary':'single five-byte tail JMP, followed by INT3; not PE-unwind-derived',
 'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str} for i in ins]}]})
for name,va in [('CRT_Floor_dispatch',0x1804d3200),('CRT_Floor_SSE4',0x1804eefb0),('CRT_Floor_scalar_finite_path',0x1804d3220)]:
 off=n['rva'](va-n['base'],512);decoded=[];terminal=False;end=None
 for i in n['engine'].disasm(n['b'][off:off+512],va):
  if i.mnemonic=='int3':end=i.address;break
  decoded.append(i)
  if i.mnemonic in ('ret','jmp'):terminal=True
 assert end and terminal,(name,decoded)
 body=n['b'][off:off+end-va]
 out.append({'name':name,'address':hex(va),'ranges':[{'start':hex(va),'end_exclusive':hex(end),
  'boundary':'CRT leaf decoded to first INT3 after RET/JMP; conditional outside NaN tail is not admitted',
  'source_file_offset':off,'source_sha256':hashlib.sha256(body).hexdigest(),
  'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str} for i in decoded]}]})
(OUT/'raw_helpers.json').write_text(json.dumps({'target_sha256':n['pe']['sha256'],'functions':out},indent=2)+'\n',encoding='utf8')
print('raw helpers',len(out),'ranges',sum(len(f['ranges']) for f in out))
for f in out:
 if f['name']=='MathUtil.GE_FP':
  for r in f['ranges']:
   for i in r['instructions']:print(i['address'],i['mnemonic'],i['operands'])

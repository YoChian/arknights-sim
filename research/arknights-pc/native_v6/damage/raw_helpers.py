"""Static arithmetic/admission helpers with exact PE unwind components."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent
source=OUT/'prepare.py'
ns={'__file__':str(source)}
exec(compile(source.read_text().split('selection=json.loads')[0],str(source),'exec'),ns)
targets={'AttackInfo.GetFinalAtk':0x180648250,'AttackInfo.ctor':0x180648380,
         'BuffContainer._CheckBuffsActionValid':0x18067e3a0,
         'Entity.IfReasonIsDeath':0x1806f4e80,
         'Modifier.get_attackType':0x1808b3a00,'Modifier.get_source':0x1808b4a60,
         'BuffContainer.OnTargetKilled':0x180679d00,'Buff._IsActionValid':0x18068c060,
         'Unit.CheckReborn':0x180ac68b0,'Buff.OnTargetKilled':0x180687760,
         'MathUtil.LE_FP_0x6000277':0x1866e5700,'FP.op_LessThan_shared_with_TimeSpan':0x185ed91f0,
         'FP..cctor':0x1866fd010}
labels=dict(x.split('\t',1) for x in (ns['ROOT']/'native_v2/labels.tsv').read_text().splitlines())
out=[]
for name,va in targets.items():
 r=va-ns['base'];ranges=ns['groups'].get(r)
 if not ranges:
  o=ns['rva'](r,128)
  for i in ns['engine'].disasm(ns['b'][o:o+128],va):
   if i.mnemonic=='ret':
    ranges=[(r,i.address+i.size-ns['base'],0)];break
  assert ranges,name
 record={'name':name,'address':hex(va),'ranges':[]}
 for begin,end,unwind in ranges:
  offset=ns['rva'](begin,end-begin);body=ns['b'][offset:offset+end-begin]
  record['ranges'].append({'start':hex(ns['base']+begin),'end':hex(ns['base']+end-1),
   'unwind_rva':hex(unwind),'source_file_offset':offset,'source_sha256':hashlib.sha256(body).hexdigest(),
   'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,
                    'operands':i.op_str,'candidate_callee':labels.get(i.op_str)}
                   for i in ns['engine'].disasm(body,ns['base']+begin)]})
 out.append(record)
(OUT/'raw_helpers.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],'functions':out},indent=2),encoding='utf8')
print('helper entries',len(out))
for f in out:
 if not f['name'].startswith('MathUtil.LE_FP'):continue
 print(f['name'])
 for r in f['ranges']:
  for i in r['instructions']:
   if i['mnemonic'] in ('call','jmp','ret') or (i['mnemonic'] in ('mov','test') and any(x in i['operands'] for x in ('0x10','0x18','0x20','0x28'))):
    print(i['address'],i['mnemonic'],i['operands'],i['candidate_callee'])

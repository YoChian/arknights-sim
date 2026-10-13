from pathlib import Path
import json
p=Path(r'D:\Repo\.rea-tools\arknights-pc\native_v9\buff_container');ns={'__file__':str(p/'prepare.py')};exec((p/'prepare.py').read_text('utf8').split('selection=json.loads')[0],ns)
records=[]
for a in [0x185a17960,0x185a17d40,0x185a16f20,0x185a19b40,0x180690a40,0x18067ad60,0x18067b400,0x18067b160,0x18068edb0]:
 s=a-ns['base'];pieces=ns['groups'].get(s,[(s,s+128,0)]);record={'address':hex(a),'ranges':[]}
 for start,end,unwind in pieces:
  o=ns['rva'](start,end-start);ins=list(ns['engine'].disasm(ns['b'][o:o+end-start],ns['base']+start))
  if unwind==0:
   cut=next((i for i,x in enumerate(ins) if x.mnemonic=='int3'),len(ins));ins=ins[:cut]
  lines=[f'{hex(x.address)} {x.mnemonic} {x.op_str}' for x in ins];record['ranges'].append({'start':hex(start+ns['base']),'end':hex(end+ns['base']),'lines':lines})
 records.append(record)
 print('\n'.join(lines) if a in [0x185a17960,0x185a17d40,0x185a16f20,0x185a19b40,0x180690a40,0x18068edb0] else f'{hex(a)} CALLS '+str([x for rr in record['ranges'] for x in rr['lines'] if 'call ' in x]))
(p/'raw_initial.json').write_text(json.dumps(records,indent=2),'utf8')

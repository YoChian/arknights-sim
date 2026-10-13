from pathlib import Path
import json,hashlib
out=Path(r'D:\Repo/.rea-tools/arknights-pc/native_v9/buff_container');ns={'__file__':str(out/'prepare.py')};exec((out/'prepare.py').read_text('utf8').split('selection=json.loads')[0],ns)
records=[]
for a in [0x1806758e0,0x1806860a0,0x1806767d0,0x180686740,0x180679d00,0x180687760,0x1806851c0,0x18068cff0,0x18068ee40,0x18068ed30,0x1866e5420,0x1866fed50,0x1866faa10,0x185ed91f0,0x184916d00,0x185a17130,0x185366bb0,0x185367f40]:
 s=a-ns['base'];pieces=ns['groups'].get(s)
 if pieces is None:
  o=ns['rva'](s,512);ins=list(ns['engine'].disasm(ns['b'][o:o+512],a));end=None;straight=True
  for x in ins:
   if x.mnemonic in ('jmp','ret') and straight:end=x.address+x.size-ns['base'];break
   if x.mnemonic=='int3':end=x.address-ns['base'];break
   if x.mnemonic=='call' or x.mnemonic.startswith('j'):straight=False
  assert end is not None and end>s
  pieces=[(s,end,0)]
 rec={'address':hex(a),'metadata_candidates':[r for r in ns['rows'] if r['candidate_va']==hex(a)],'ranges':[]}
 for begin,end,u in pieces:
  off=ns['rva'](begin,end-begin);blob=ns['b'][off:off+end-begin];ins=list(ns['engine'].disasm(blob,begin+ns['base']))
  rec['ranges'].append(dict(start=hex(begin+ns['base']),end=hex(end+ns['base']-1),unwind_rva=hex(u),source_file_offset=off,source_sha256=hashlib.sha256(blob).hexdigest(),bytes_hex=blob.hex(),instructions=[dict(address=hex(x.address),bytes=x.bytes.hex(),mnemonic=x.mnemonic,operands=x.op_str) for x in ins]))
 records.append(rec)
 print(hex(a),len([x for rr in rec['ranges'] for x in rr['instructions']]))
 if a in [0x1806860a0,0x1806758e0,0x180687760,0x180679d00,0x1866fed50,0x1866faa10,0x185ed91f0]:
  print('\n'.join(f"{x['address']} {x['mnemonic']} {x['operands']}" for rr in rec['ranges'] for x in rr['instructions'] if x['mnemonic'] in ['call','jmp'] or ('edx,' in x['operands'] or ('[rbx' in x['operands'] and x['mnemonic']=='cmp'))))
(out/'raw_helpers.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],'functions':records},indent=2),'utf8')



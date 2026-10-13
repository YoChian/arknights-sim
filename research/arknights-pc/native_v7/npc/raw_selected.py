from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent
source=OUT/'prepare.py'
ns={'__file__':str(source)}
exec(compile(source.read_text().split('selection=json.loads')[0],str(source),'exec'),ns)
data=json.loads((OUT/'input.json').read_text())
out=[]
for entry in data['targets']:
 rec={'display_name':entry['display_name'],'address':entry['address'],'ranges':[]}
 for r in entry['ranges']:
  start,end=int(r['start'],16),int(r['end'],16)
  offset=r['source_file_offset'];body=ns['b'][offset:offset+end-start+1]
  assert hashlib.sha256(body).hexdigest()==r['source_sha256']
  rec['ranges'].append({**r,'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),
      'mnemonic':i.mnemonic,'operands':i.op_str} for i in ns['engine'].disasm(body,start)]})
 out.append(rec)
(OUT/'raw.json').write_text(json.dumps(out,indent=2),encoding='utf8')
print('entries',len(out),'exact ranges',sum(len(x['ranges']) for x in out))

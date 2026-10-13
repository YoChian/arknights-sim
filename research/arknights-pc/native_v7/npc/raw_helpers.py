"""Small source-bound identities/gates, without Java or target execution."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent
source=OUT/'prepare.py';ns={'__file__':str(source)}
exec(compile(source.read_text('utf8').split('selection=json.loads')[0],str(source),'exec'),ns)
rows=json.loads((ns['ROOT']/'core/Assembly-CSharp_candidate_method_map.json').read_text('utf8'))
wait=next(r for r in rows if r['token']=='0x600fab4')
targets={'Nodes.GetActionTarget':0x180fceed0,'Enemy.get_originRoute':0x180a7f790,
 'Enemy.get_originCursorIndex':0x180a7f610,'Entity.IfReasonIsDeath':0x1806f4e80,
 'AsyncUtil.WaitForFixedSeconds_FP':0x180647eb0,'WaitForFixedSeconds_FP.MoveNext':int(wait['candidate_va'],16),
 'Buff.get_source':0x18068f8b0,'Buff.get_owner':0x18068f400}
out=[]
for name,va in targets.items():
 ranges=ns['groups'].get(va-ns['base']);assert ranges,name
 record={'name':name,'address':hex(va),'ranges':[]}
 for begin,end,unwind in ranges:
  offset=ns['rva'](begin,end-begin);body=ns['b'][offset:offset+end-begin]
  range_record={'start':hex(ns['base']+begin),'end_exclusive':hex(ns['base']+end),
   'unwind_rva':hex(unwind),'source_file_offset':offset,'source_sha256':hashlib.sha256(body).hexdigest(),
   'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,
                    'operands':i.op_str} for i in ns['engine'].disasm(body,ns['base']+begin)]}
  if name=='Nodes.GetActionTarget':
   table_va=0x180fcf100
   range_record['instructions']=[i for i in range_record['instructions'] if int(i['address'],16)<table_va]
   table_offset=ns['rva'](table_va-ns['base'],44);table=ns['b'][table_offset:table_offset+44]
   range_record['embedded_jump_table']={'start':hex(table_va),'bytes':table.hex(),
    'source_file_offset':table_offset,'source_sha256':hashlib.sha256(table).hexdigest(),
    'entry_format':'11 little-endian UInt32 image-relative code RVAs; these bytes are data, not Capstone instructions'}
  record['ranges'].append(range_record)
 out.append(record)
(OUT/'raw_helpers.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],'functions':out},indent=2)+'\n',encoding='utf8')
print('helpers',len(out),'ranges',sum(len(f['ranges']) for f in out))

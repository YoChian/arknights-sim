"""Source-bound action flow and source-pointer helpers, without executing the target."""
from pathlib import Path
import hashlib,json
OUT=Path(__file__).parent
s=OUT/'prepare.py';ns={'__file__':str(s)}
exec(compile(s.read_text('utf8').split('selection=json.loads')[0],str(s),'exec'),ns)
targets={
 'ActionUtil.RunActions':0x181190690,
 'ActionUtil.CheckExecute':0x18118fb90,
 'ActionNode.get_executeCondition':0x180fcc600,
 'AssignValueToBB.get_allowedSource':0x1810161a0,
 'ClearAllBuffs.get_allowedSource':0x18101d250,
 'IfNot.get_executeCondition':0x181146450,
 'IfNot.Execute':0x181146300,
 'ObjectPtr_Entity.Get_value_generic_candidate':0x185159d80,
}
out=[]
for name,va in targets.items():
 groups=ns['groups'].get(va-ns['base']);assert groups,name
 matches=[r for r in ns['rows'] if r['candidate_va'] and int(r['candidate_va'],16)==va]
 record={'name':name,'address':hex(va),'metadata_candidates':matches,'ranges':[]}
 for a,z,u in groups:
  off=ns['rva'](a,z-a);body=ns['b'][off:off+z-a]
  record['ranges'].append({'start':hex(ns['base']+a),'end_exclusive':hex(ns['base']+z),
   'unwind_rva':hex(u),'source_file_offset':off,'source_sha256':hashlib.sha256(body).hexdigest(),
   'instructions':[{'address':hex(i.address),'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,
                    'operands':i.op_str} for i in ns['engine'].disasm(body,ns['base']+a)]})
 out.append(record)
(OUT/'raw_dispatch.json').write_text(json.dumps({'target_sha256':ns['pe']['sha256'],
 'method':'exact recursive PE UNW_FLAG_CHAININFO ranges; Capstone static decoding; no execution',
 'functions':out},indent=2)+'\n',encoding='utf8')
print('dispatch',len(out),'ranges',sum(len(f['ranges']) for f in out),
 'bytes',sum(int(r['end_exclusive'],16)-int(r['start'],16) for f in out for r in f['ranges']))

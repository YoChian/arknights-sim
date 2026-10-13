from pathlib import Path
import json,struct
p=Path(r'D:\Repo\.rea-tools\arknights-pc');out=p/'native_v9/buff_container';out.mkdir(parents=True,exist_ok=True)
source=p/'native_v8/npc_actions/prepare.py'
(out/'prepare.py').write_text(source.read_text('utf8'),'utf8')
helper=p/'native_v6/targeting/inspect_generic_identities.py'
ns={'__file__':str(helper)}
exec(helper.read_text('utf8').split('records = []')[0],ns)
slots=[(0x18882b720,0x185a17960),(0x18882b958,0x185a17d40),(0x18882b2a8,0x185a16f20),(0x18882bdc0,0x185a19b40)]
records=[]
for slot,target in slots:
 off=ns['offset'](slot,8);enc=struct.unpack_from('<Q',ns['b'],off)[0];kind=enc>>29;idx=(enc&0x1fffffff)>>1
 assert kind==6
 spec_off=ns['offset'](ns['words'][9]+idx*12,12);mi,ci,mti=struct.unpack_from('<3i',ns['b'],spec_off);m=ns['ns']['methods'][mi]
 records.append(dict(slot_va=hex(slot),slot_file_offset=off,slot_raw_bytes8=ns['b'][off:off+8].hex(),method_spec_index=idx,spec_bytes=ns['b'][spec_off:spec_off+12].hex(),metadata_method_index=mi,declaring_type=ns['ns']['fullname'](m[1]),method=ns['ns']['text'](m[0]),token=hex(m[5]),class_generic_inst=ns['generic_inst'](ci),method_generic_inst=ns['generic_inst'](mti),caller_bound_target=hex(target)))
(out/'generic_identities.json').write_text(json.dumps(records,indent=2),'utf8')
print(json.dumps([{k:r[k] for k in ('method','declaring_type','metadata_method_index','caller_bound_target')} for r in records],indent=2))
rows=[]
for image in ['Assembly-CSharp','Torappu.Common','ThirdPartyAssembly','mscorlib']:
 rows.extend(json.loads((p/'core'/f'{image}_candidate_method_map.json').read_text('utf8')))
ids=[65283,65284,65285,65286,65288,65312,65313,65314,65358,65362,65103]
sel=[{k:r[k] for k in ('type','method','metadata_method_index','token')}|{'address':r['candidate_va'],'reason':'Buff membership removal/registration gates and iteration mutation closure'} for r in rows if r['metadata_method_index'] in ids and r['candidate_va']]
for r in records:
 sel.append(dict(type=r['declaring_type'],method=r['method'],address=r['caller_bound_target'],metadata_method_index=r['metadata_method_index'],token=r['token'],raw_call_target=True,reason='Actual caller-bound closed generic DoubleBufferedList<ObjectPtr<Buff>> helper; identity in generic_identities.json'))
(out/'selection.json').write_text(json.dumps(sel,indent=2),'utf8')

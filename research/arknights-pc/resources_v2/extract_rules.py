from pathlib import Path
import json,hashlib,struct
from ark_bundle import load,text_bytes
OUT=Path(__file__).parent
inv=json.loads((OUT/'anon_inventory.json').read_text('utf-8'))
names=['level_rogue6_1-1','enemy_databasea5b667','character_table9fc534','skill_tableafb859','roguelike_topic_tablebd71d3','gamedata_const61fefd','level_script_table91d938']
records=[]
for name in names:
 row=next(r for r in inv['records'] if any(a['name']==name for a in r['assets']))
 env=load(row['source'])
 obj=next(o for o in env.objects if o.type.name=='TextAsset' and o.read().m_Name==name)
 raw=text_bytes(obj.read());signed=OUT/'samples'/(name+'.signed.bytes');signed.parent.mkdir(exist_ok=True);signed.write_bytes(raw)
 body=raw[128:]
 # Validate only root/vtable framing here. Full typed verification is separate.
 if len(body)<12:raise ValueError('truncated potential FlatBuffer')
 root=struct.unpack_from('<I',body,0)[0]
 if not 4<=root<=len(body)-4:raise ValueError(f'invalid FlatBuffer root for {name}')
 vt=root-struct.unpack_from('<i',body,root)[0]
 if not 0<=vt<=len(body)-4:raise ValueError('invalid vtable pointer')
 vlen,objlen=struct.unpack_from('<HH',body,vt)
 if vlen<4 or vlen%2 or vt+vlen>len(body) or root+objlen>len(body):raise ValueError('invalid vtable bounds')
 path=OUT/'samples'/(name+'.flat.bin');path.write_bytes(body)
 containers=[c for c in row['containers'] if Path(c).stem==name]
 rec={'source':row['source'],'source_sha256':row['sha256'],'container':containers,'text_asset_name':name,'signed_bytes':len(raw),'signed_sha256':hashlib.sha256(raw).hexdigest(),'body_path':str(path),'body_bytes':len(body),'body_sha256':hashlib.sha256(body).hexdigest(),'prefix_bytes_removed':128,'flat_root_offset':root,'vtable_offset':vt,'vtable_bytes':vlen,'table_object_bytes':objlen,'vtable_fields':(vlen-4)//2}
 records.append(rec);print(json.dumps(rec,ensure_ascii=False),flush=True)
(OUT/'sample_provenance.json').write_text(json.dumps(records,ensure_ascii=False,indent=2),'utf-8')

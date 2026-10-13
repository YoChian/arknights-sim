from pathlib import Path
import json,hashlib
from ark_bundle import load,text_bytes
OUT=Path(__file__).parent
inv=json.loads((OUT/'anon_inventory.json').read_text('utf-8'));rows=[]
for suffix,containers in [('131ad7aecd4e8a32bd57e95c7496c178.bin',['dyn/gamedata/excel/roguelike_table.bytes']),('66f966a296f61b58d4149b5ca08f4b49.bin',['dyn/gamedata/[uc]lua/base/hotfix/uipatch.lua.bytes'])]:
 row=next(r for r in inv['records'] if r['source'].endswith(suffix));env=load(row['source'])
 for c in containers:
  data=env.container[c].read();b=text_bytes(data);path=OUT/'samples'/(data.m_Name+'.opaque.bytes');path.write_bytes(b)
  rows.append({'source':row['source'],'container':c,'name':data.m_Name,'path':str(path),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()})
index=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\StreamingAssets\AB\Windows\074c396967a291d157f01a3e40c79119.idx');b=index.read_bytes();path=OUT/'samples'/'resource_index.opaque.bytes';path.write_bytes(b)
rows.append({'source':str(index),'name':'resource_index','path':str(path),'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()})
(OUT/'cipher_sample_provenance.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2),'utf-8');print(json.dumps(rows,ensure_ascii=False))

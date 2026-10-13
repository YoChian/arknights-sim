from pathlib import Path
import json,hashlib,collections
from ark_bundle import load,text_bytes,STATS
ROOT=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\StreamingAssets\AB\Windows')
OUT=Path(__file__).parent
rows=[];errors=[]
for i,p in enumerate(sorted((ROOT/'anon').glob('*.bin'))):
 try:
  before=dict(STATS);env=load(p);r={'source':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'objects':dict(collections.Counter(o.type.name for o in env.objects)),'containers':list(env.container),'assets':[],'decoder_stats':{k:STATS[k]-before[k] for k in STATS}}
  for o in env.objects:
   if o.type.name=='TextAsset':
    d=o.read();b=text_bytes(d)
    a={'path_id':o.path_id,'name':d.m_Name,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest(),'head160':b[:160].hex(),'ascii_strings_sample':[]}
    import re
    a['ascii_strings_sample']=[s.decode('ascii') for s in re.findall(rb'[ -~]{8,}',b[:20000])[:15]]
    r['assets'].append(a)
  rows.append(r)
 except Exception as ex:errors.append({'source':str(p),'error':str(ex)})
 if (i+1)%15==0:print(json.dumps({'processed':i+1,'parsed':len(rows),'errors':len(errors)},ensure_ascii=False),flush=True)
(OUT/'anon_inventory.json').write_text(json.dumps({'records':rows,'errors':errors,'decoder_total_stats':STATS},ensure_ascii=False,indent=2),'utf-8')
print(json.dumps({'count':len(rows),'errors':errors,'textasset_count':sum(len(r['assets']) for r in rows),'decoder_total_stats':STATS},ensure_ascii=False),flush=True)

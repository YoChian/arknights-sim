from pathlib import Path
import json,collections
from ark_bundle import load,STATS
OUT=Path(__file__).parent
ROOT=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\StreamingAssets\AB\Windows')
rows=[]
for rel in ['config/common.ab','config/buff_template_holder.ab','battle/enm_pfb_0.ab','scenes/obt/roguelike/ro6/level_rogue6_1-1/level_rogue6_1-1.ab']:
 prev=dict(STATS);e=load(ROOT/rel)
 counts=collections.Counter(o.type.name for o in e.objects)
 # Read every MonoBehaviour type tree in these samples. This uses shipped trees,
 # not a fabricated C# schema or assembly execution.
 read=0;fail=[]
 for o in e.objects:
  if o.type.name=='MonoBehaviour':
   try:o.read_typetree();read+=1
   except Exception as ex:fail.append({'path_id':o.path_id,'error':str(ex)})
 rows.append({'source':str(ROOT/rel),'decoder_stats':{k:STATS[k]-prev[k] for k in STATS},'object_types':dict(counts),'mono_behaviour_typetrees_read':read,'typetree_failures':fail[:10],'typetree_failure_count':len(fail)})
(OUT/'nontext_verification.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2),'utf-8');print(json.dumps(rows,ensure_ascii=False))

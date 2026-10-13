"""Pin selected real NPC prefabs/DB/refs; no instantiated objects or Init."""
from pathlib import Path
import sys,json,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1];ROOT=Path(r'D:\Repo\arknights-sim')
sys.path.insert(0,str(ROOT))
from arknights_probe.data import Dataset
from arknights_probe.enemy_data import resolve_enemy
dataset=Dataset.from_manifest(ROOT/'data/manifest.json')
path=BASE/'native_v5/resources/rule_prefab_subtrees.json';trees=json.loads(path.read_text())
selected=[]
for key in ['enemy_2133_shdopl','enemy_3001_upeopl']:
 prefab=next(p for p in trees['prefabs'] if p['name']==key)
 component=next(c for c in prefab['rule_components'] if c['class_name']=='Torappu.Battle.Enemy')
 fields=component['fields']
 ref=dataset.enemy_refs.get(key)
 row={'key':key,'prefab':prefab,'enemy_component':component,'level_reference':ref,
      'reference_scope':'original map EnemyDataDbReference' if ref is not None else
           'no original map ref: caller must supply source-bound Scheduler NPC dictionary data; standalone DB level is not proof of loader',
      'scalar_fields':{k:v for k,v in fields.items() if type(v) in [int,float,str,bool] or v is None},
      'selected_db_levels':dataset.tables['enemies']['enemies'][key]}
 if ref is not None:
  resolved=resolve_enemy(dataset.tables['enemies'],ref)
  row['resolved_values']=resolved.values
 selected.append(row)
pins=[{'path':str(path),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()}]
for prefab in selected:
 p=prefab['prefab']['source_pin'];pins.append(p)
out={'format':'native_v9_enemy_factory_inputs_v1','sources':pins,'selected':selected,
     'dataset_manifest':str(ROOT/'data/manifest.json'),'dataset_manifest_sha256':hashlib.sha256((ROOT/'data/manifest.json').read_bytes()).hexdigest(),
     'script_source_pin':trees['script_source_pin']}
(OUT/'resource_inputs.json').write_text(json.dumps(out,indent=2,ensure_ascii=False),encoding='utf-8')
print(json.dumps([{'key':r['key'],'ref':r['level_reference'],
  'fields':{k:v for k,v in r['scalar_fields'].items() if any(s in k.lower() for s in ['delay','side','born','defer','init','always','state'])},
  'component_keys':list(r['enemy_component'].keys()),'db_level_container_type':type(r['selected_db_levels']).__name__}
  for r in selected],indent=2))

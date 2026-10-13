"""Pin minimal actual altar table rows and instantiated Mono rule components."""
from pathlib import Path
import json,hashlib,sys
OUT=Path(__file__).parent;BASE=OUT.parents[1]
paths=[BASE/'resources_v2/normalized/skill_tableafb859.json',BASE/'resources_v2/normalized/character_table9fc534.json',BASE/'native_v5/resources/altar_context.json',BASE/'native_v5/resources/rule_prefab_subtrees.json']
skills,characters,altar,trees=[json.loads(p.read_text()) for p in paths]
prefabs=[p for p in trees['prefabs'] if p['name'] in ('sktok_ore','trap_011_ore')]
output={'format':'altar_skill_preparation_inputs_v1','sources':[{'path':str(p),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in paths],
 'skill':skills['skills']['sktok_ore'],'character':characters['characters']['trap_011_ore'],
 'predefine':altar['altar_predefine'],'prefabs':prefabs,
 'limits':'Direct source rows, no runtime evaluation/selection/global-modifier assertion.'}
(OUT/'resource_inputs.json').write_text(json.dumps(output,indent=2,ensure_ascii=False),encoding='utf-8')
print(json.dumps({'prefab_count':len(prefabs),'skill_duration':output['skill']['levels'][0]['duration'],'sp':output['skill']['levels'][0]['spData']}))
# Unity TagManager is an ordinary SerializedFile object; this reads only.
sys.path.insert(0,str(BASE/'tools/python'));import UnityPy
path=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\globalgamemanagers')
env=UnityPy.load(str(path));found=[]
for obj in env.objects:
 if obj.type.name=='TagManager':
  tree=obj.read_typetree();found.append({'path_id':obj.path_id,'type':'TagManager','serialized':tree})
result={'source':{'path':str(path),'bytes':path.stat().st_size,'sha256':hashlib.sha256(path.read_bytes()).hexdigest()},'TagManager':found,'limits':'No Unity NameToLayer runtime calls; only serialized layer names read.'}
(OUT/'tag_manager_inputs.json').write_text(json.dumps(result,indent=2,ensure_ascii=False),encoding='utf-8')
print(json.dumps(result,ensure_ascii=False))

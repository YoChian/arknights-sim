"""Only restore-specific actual NPC prefab fields/route declarations."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
paths=[BASE/'native_v5/resources/rule_prefab_subtrees.json',BASE/'native_v7/npc/resource_inputs.json',BASE/'resources_v2/normalized/level_rogue6_1-1.json']
trees,previous,level=[json.loads(p.read_text()) for p in paths]
prefabs=[p for p in trees['prefabs'] if p['name'] in ['enemy_2133_shdopl','enemy_3001_upeopl']]
out={'sources':[{'path':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in paths],'prefabs':prefabs,
 'level_routes':level['routes'],'level_extra_routes':level['extraRoutes'],
 'scope':'Original prefab rules and route declarations; no animation/tween behavior or route clone inferred from field names.'}
(OUT/'resource_inputs.json').write_text(json.dumps(out,indent=2,ensure_ascii=False),encoding='utf-8')
print(json.dumps({'prefabs':[p['name'] for p in prefabs],'main_routes':len(level['routes']),'extra_routes':len(level['extraRoutes'])}))

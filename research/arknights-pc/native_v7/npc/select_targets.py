from pathlib import Path
import json
OUT=Path(__file__).parent
ROOT=OUT.parents[1]
rows=json.loads((ROOT/'core/Assembly-CSharp_candidate_method_map.json').read_text('utf8'))
wanted=[('SummonEnemiesFollowMyRouteWithBuff','Execute'),('SummonEnemiesFollowMyRouteWithBuff','GatherBuffs'),
 ('ForceSetToSourcePosition','Execute'),('SetDisappear','Execute'),('FinishBuffsById','Execute'),
 ('InstantKill','Execute'),('ModifyLifePoint','Execute'),('AssignValueToBB','Execute'),
 ('ClearAllBuffs','Execute'),('FilterByBlackboardValue','Execute'),
 ('Torappu.Battle.BObject','SetDisappeared'),('Torappu.Battle.Enemy','OnDisappearChanged'),
 ('Torappu.Battle.Buff','OnOwnerFinish'),('Torappu.Battle.Buff','OnOwnerDying'),
 ('Torappu.Battle.Buff','OnTakeDamage'),('Torappu.Battle.Entity','CheckCanSwitchToDisappearState'),
 ('Torappu.Battle.Entity','OnBeforeDisappearChanged'),('Torappu.Battle.Entity','OnDisappearChanged')]
selection=[]
for type_name,method in wanted:
 matches=[r for r in rows if (r['type'],r['method'])==(type_name,method)]
 assert len(matches)==1,(type_name,method)
 r=matches[0]
 selection.append({'type':type_name,'method':method,'address':r['candidate_va'],
                   'metadata_method_index':r['metadata_method_index'],'token':r['token']})
(OUT/'selection.json').write_text(json.dumps(selection,indent=2)+'\n',encoding='utf8')
print('selected',len(selection))

from pathlib import Path
import json
OUT=Path(__file__).parent
ROOT=OUT.parents[1]
maps=[]
for image in ['Assembly-CSharp','Torappu.Common']:
 maps.extend(json.loads((ROOT/f'core/{image}_candidate_method_map.json').read_text('utf8')))
prior=json.loads((OUT/'prior_native_results.json').read_text('utf8'))
prior_addresses={f['address'] for f in prior['functions']}
requests={
 'Torappu.Battle.BattleFormula':['CalculateDamageNoEvent','CalculateDamageInternal'],
 'Torappu.Battle.Entity':['OnHpZero','OnAppliedModifier','set_hp','get_maxMinusHp','get_isUndeadable','_VerifyAbilityDamageMiss'],
 'Torappu.Battle.Enemy':['OnHpZero','SwitchToDeadState'],
 'Torappu.Battle.Unit':['OnHpZero'],
 'DefaultGameMode':['OnEntityApplyModifier','OnFinalizeEntityDamage'],
 'BuffContainer':['OnBeforeApplyingModifier','OnApplyingModifier','OnAppliedModifier','OnBeingCalculateDamage',
                  'OnTakeDamage','OnBeforeTrySetHpZero','OnOwnerBeforeDead','OnOwnerDying','OnOwnerHpFull'],
 'Torappu.Battle.Modifier':['NewTrySetHpZero','get_isCancelled','get_isDamage','get_cancelReason','Cancel','_ctor'],
}
selection=[]
for owner,names in requests.items():
 for name in names:
  rows=[x for x in maps if x['type']==owner and x['method']==name]
  if name=='_ctor':rows=[x for x in maps if x['type']==owner and x['method']=='.ctor']
  assert rows,(owner,name)
  for row in rows:
   if row['candidate_va'] in prior_addresses:continue
   selection.append({'type':row['type'],'method':row['method'],'address':row['candidate_va'],
                     'metadata_method_index':row['metadata_method_index'],'token':row['token']})
inventory=json.loads((OUT/'method_inventory.json').read_text('utf8'))
dead=next(x for x in inventory['definitions'] if x['name']=='Torappu.Battle.Enemy.States.DeadState')
for m in dead['methods']:
 if m['method'] not in ('OnEnter','OnExit','_PlayAnimation'):continue
 row=m['candidate']
 selection.append({'type':row['type'],'method':row['method'],'address':row['candidate_va'],
                   'metadata_method_index':m['metadata_method_index'],'token':m['token'],
                   'exact_declaring_owner':dead['name'],'type_definition_index':dead['definition_index']})
(OUT/'selection.json').write_text(json.dumps(selection,indent=2),encoding='utf8')
print('entries',len(selection))
for s in selection:print(s['type'],s['method'],s['address'])

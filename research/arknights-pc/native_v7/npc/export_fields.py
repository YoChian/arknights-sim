"""Reuse the original static registration reader with separate NPC output."""
from pathlib import Path
import json
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
source=ROOT/'native_v4/resources/export_native_fields.py'
text=source.read_text('utf8')
ns={'__file__':str(source)}
exec(compile(text.split('roots={')[0],str(source),'exec'),ns)
names={'Torappu.Battle.Action.Nodes.'+x for x in ['SummonEnemiesFollowMyRouteWithBuff',
 'ForceSetToSourcePosition','SetDisappear','FinishBuffsById','InstantKill','ModifyLifePoint',
 'AssignValueToBB','ClearAllBuffs','FilterByBlackboardValue']}
names.update({'Torappu.Battle.Action.Nodes.SummonEnemiesFollowMyRouteWithBuff.<>c__DisplayClass35_0',
 'Torappu.Battle.Scheduler.SpawnSummonedEnemyTrackedInGameModeParams',
 'Torappu.Battle.Scheduler.<SpawnSummonedEnemyTrackedInGameMode>d__129',
 'Torappu.Battle.Scheduler','Torappu.Battle.BObject','Torappu.Battle.Entity','Torappu.Battle.Enemy',
 'Torappu.Battle.Buff','Torappu.Battle.Buff.BuffContainer','Torappu.Battle.BasicTalent','Torappu.Battle.Talent',
 'Torappu.Battle.Enemy.Options','Torappu.Battle.Context.Snapshot',
 'Torappu.Battle.Action.Nodes.ActionTargetType'})
indices={i for i in range(len(ns['types'])) if ns['fullname'](i) in names}
found={ns['fullname'](i) for i in indices}
assert found==names,names-found
a=text.index('roots={');z=text.index('selected=set(roots)',a)
text=text[:a]+'roots='+repr(indices)+'\n'+text[z:]
exec(compile(text,str(source),'exec'),{'__file__':str(OUT/'export_fields.py')})

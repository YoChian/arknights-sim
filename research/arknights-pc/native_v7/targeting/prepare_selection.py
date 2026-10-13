"""Select unresolved targeting prerequisites; root executes Ghidra serially."""
import json
from pathlib import Path

OUT=Path(__file__).parent
BASE=OUT.parents[1]
maps=[]
for image in ['Assembly-CSharp','Torappu.Common']:
    maps+=json.loads((BASE/'core'/f'{image}_candidate_method_map.json').read_text('utf-8'))
byidx={m['metadata_method_index']:m for m in maps}
reasons={
    78269:'Actual SideTypes same/opposite arrays and ALL side bitmask initialization',
    62955:'Actual Battle.Layers side-specific Unity layer/mask initialization',
    75087:'TargetSelector owner Ability purpose mask getter; actual altar fixed branch',
    66789:'HitRangeManager provider registration semantics; determine empty-provider default',
    66790:'HitRangeManager provider unregistration identity/reference semantics',
    66792:'TargetSelector validation target HitRangeManager gate actual source data/providers',
    66793:'HitRangeManager construction/default provider container',
    66788:'HitRangeManager reset preserves/clears provider context',
    74636:'FilterUtil ALL dictionary delegate binding; do not infer from filter enum alone',
    74621:'ALL weighted queue secondary extra-mode weight mutation/gate',
    220527:'Torappu.FP static +68 value copied to FilterUtil default smallEnoughGap',
    66404:'Native Entity mapLayer context getter',
    66516:'Native heal-free getter; trace underlying status flags/ownership',
    66517:'Native ally-target-free getter; trace underlying status flags/ownership',
    66527:'Native camouflage getter; trace underlying status flags/ownership',
}
selection=[]
for idx,reason in reasons.items():
    row=byidx[idx]
    assert row['candidate_va'],row
    selection.append({'type':row['type'],'method':row['method'],'address':row['candidate_va'],
        'metadata_method_index':idx,'token':row['token'],'reason':reason})
for address,name,reason in [
    ('0x1851b2800','PriorityQueue_WeightedTarget_Entity_ctor','FilterUtil.cctor allocation Type slot1888a2040=PriorityQueue<WeightedTarget<Entity>>, methodInfo18896e700'),
    ('0x1851b0a00','PriorityQueue_WeightedTarget_Entity_Clear','Filter<Entity> actual methodInfo18896eb80; queue clear, not SortedSet'),
    ('0x1851afeb0','PriorityQueue_WeightedTarget_Entity_Add','Filter<Entity> actual methodInfo18896e940; ordering and same-weight insertion behavior'),
    ('0x1851b1b10','PriorityQueue_WeightedTarget_Entity_RemoveLast','Filter<Entity> raw call at1844f94da, methodInfo slot from RIP44758e6 at1844f94d3; cap removes tail'),
    ('0x1851b36f0','PriorityQueue_WeightedTarget_Entity_get_Item','Filter<Entity> actual methodInfo18896f000; indexed rank/heap output semantics'),
    ('0x185528950','WeightedTarget_Entity_ctor','Filter<Entity> constructs stack WeightedTarget with FP weight and Entity; fields/layout and comparator identity require metadata support'),
    ('0x1848dd0d0','PriorityQueue_WeightedTarget_Entity_get_count','Filter<Entity> actual methodInfo18896f240; count body may shared alias, identity by encoded caller slot'),
]:
    selection.append({'type':'UnresolvedCall','method':name,'address':address,'metadata_method_index':None,
        'token':None,'raw_call_target':True,'reason':reason})
(OUT/'selection.json').write_text(json.dumps(selection,indent=2),'utf-8')
print(len(selection),'entries')

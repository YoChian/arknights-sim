"""Prepare deterministic DSL inputs and explicitly external timeline fixtures."""
from pathlib import Path
import json,sys,random,struct,hashlib

OUT=Path(__file__).parent;REPO=OUT.parents[1]
sys.path.insert(0,str(REPO))
from arknights_probe.data import Dataset
from arknights_probe.timeline import compile_timeline,zero_enemy_fixture,ASSET_DEFAULT_DT_RAW
from arknights_probe.fp import FP,binary32

def bits(value):return f'{struct.unpack("<I",struct.pack("<f",value))[0]:08x}'
def event(label):return {'op':'event','label':label}
def marker(kind='null'):return {'op':'marker','value':kind}
def child(ops):return {'op':'child','ops':ops}
def wait(delay):return {'op':'wait','delay':delay}
def while_(values,label='p'):return {'op':'while','values':values,'label':label}
def queue(items):return {'op':'queue','items':items}
def item(time,label,frames=1,valid=True):return {'time':time,'label':label,'frames':frames,'isValid':valid}

cases=[]
def case(name,ops,delta=.25,max_frames=1024):
    cases.append({'name':name,'ops':ops,'delta_bits':bits(delta),'max_frames':max_frames})
case('empty_root',[])
case('event_only_prime_frame0',[event('prime')])
case('plain_null_marker',[event('before'),marker(),event('after')])
case('ordinary_list_is_not_iterator',[event('before'),marker('list'),event('after')])
case('new_empty_child_suspends_parent',[event('before'),child([]),event('after')])
case('three_empty_siblings',[child([]),event('a'),child([]),event('b'),child([]),event('c')])
case('nested_empty_leaf',[event('root'),child([event('child'),child([]),event('child_after')]),event('root_after')])
case('filled_child_finishes_same_frame',[child([event('child_before'),marker(),event('child_after')]),event('root_after')])
case('filled_then_new_empty',[child([marker(),event('filled_after')]),child([]),event('root_after')])
case('deep_nested_nonempty',[child([child([child([marker(),event('leaf_after')]),event('middle_after')]),event('outer_after')]),event('root_after')])
case('wait_while_initial_false',[event('before'),while_([False]),event('after')])
case('wait_while_true_true_false',[while_([True,True,False]),event('after')])
case('two_wait_while_initial_false',[while_([False],'a'),while_([False],'b'),event('after')])
for delay in [-.25,0,.125,.375,.625,.875,1.125]:
    case('wait_boundary_'+str(delay),[event('before'),wait(delay),event('after')])
case('serial_zero_time_empty_executors',[queue([item(0,'a',0),item(0,'b',0),item(0,'c',0)]),event('after')])
case('serial_zero_time_single_frame_executors',[queue([item(0,'a'),item(0,'b'),item(0,'c')]),event('after')])
case('serial_planned_difference_with_executor_drift',[queue([item(1,'a',2),item(2,'b',2)]),event('after')])
case('serial_invalid_advances_planned_time',[queue([item(.5,'invalid',1,False),item(.75,'valid')]),event('after')])
case('serial_all_invalid_first_empty_boundary',[event('before'),queue([item(0,'invalid',1,False)]),event('after')])
case('serial_preview_negative_times',[queue([item(-3,'p0'),item(binary32(-2.7),'p1'),item(0,'spawn')]),event('after')],delta=FP(ASSET_DEFAULT_DT_RAW).as_float())

rng=random.Random(0x434f524f)
def generated_ops(depth,prefix):
    operations=[]
    for index in range(rng.randrange(0,6)):
        label=f'{prefix}.{index}'
        choice=rng.randrange(6 if depth else 5)
        if choice==0:operations.append(event(label))
        elif choice==1:operations.append(marker(rng.choice(['null','list','object'])))
        elif choice==2:operations.append(wait(rng.choice([-.25,0,.125,.375,.625,.875])))
        elif choice==3:operations.append(while_([True]*rng.randrange(3)+[False],label))
        elif choice==4:
            times=sorted(rng.choices([-.5,0,.25,.5,.75,1.0],k=rng.randrange(5)))
            operations.append(queue([item(t,f'{label}.q{i}',rng.randrange(3),rng.choice([True,True,False])) for i,t in enumerate(times)]))
        else:operations.append(child(generated_ops(depth-1,label)))
    return operations
for i in range(80):case(f'generated_{i:02}',generated_ops(3,str(i)))

waits=[]
for delta in [.25,.125,FP(ASSET_DEFAULT_DT_RAW).as_float(),binary32(1/30),binary32(1/60)]:
    delta_bits=int(bits(delta),16)
    values={bits(x) for x in [-1,0,delta/2,delta*1.5,delta*2.5,delta*3.5,.3,1,7,20,80]}
    for value in list(values):
        value_bits=int(value,16)
        if value_bits and value_bits<0xff7fffff:values.update([f'{value_bits-1:08x}',f'{value_bits+1:08x}'])
    for delay_bits in sorted(values):waits.append({'delay_bits':delay_bits,'delta_bits':f'{delta_bits:08x}'})

empty=lambda fragments:{'preDelay':0,'postDelay':0,'fragments':[{'preDelay':0,'items':[]} for _ in range(fragments)]}
kernels=[]
def kernel(name,waves,raw=ASSET_DEFAULT_DT_RAW,**extra):
    kernels.append({'name':name,'waves':waves,'dt_raw':str(raw),'delta_bits':bits(FP(raw).as_float()),'max_frames':10000,**extra})
kernel('zero_waves',[])
kernel('one_empty_wave',[empty(1)])
kernel('two_empty_waves_three_fragments',[empty(2),empty(1)])
dataset=Dataset.from_manifest(REPO/'data/manifest.json')
for mode,selections in [('NORMAL',{'t1':0,'t2':5,'c1':4}),('NORMAL',{'t1':1,'t2':6,'c1':1}),('FOUR_STAR',{'t1':0,'t2':5,'c1':4})]:
    runtime=zero_enemy_fixture(dataset)
    for value in runtime.values():value['successfulCountedCreation']=False
    source='independent_reference_fixture_no_counted_enemy_creation_external_final_complete'
    compiled=compile_timeline(dataset,mode=mode,group_selections=selections,enemy_runtime=runtime,input_source=source)
    waves=[]
    for wave in compiled.waves:
        fragments=[]
        for fragment in wave['fragments']:
            items=[]
            for q in fragment['items']:
                action=q['action'];label=f"{q['path']}|{q['occurrence']}|{action['key']}"
                kind={'SPAWN':'spawn_request','ACTIVATE_PREDEFINED':'activate_predefined_request','PREVIEW_CURSOR':'preview_cursor_request'}[action['actionType']]
                items.append({'time':q['time'],'label':label,'kind':kind,'isValid':q['isValid'],'frames':1})
            fragments.append({'preDelay':fragment['preDelay'],'items':items})
        waves.append({'preDelay':wave['preDelay'],'postDelay':wave['postDelay'],'fragments':fragments})
    kernel('map_'+mode+('_boxes' if selections['t1'] else '_empty_choices'),waves,mode=mode,group_selections=selections,enemy_runtime=runtime,input_source=source)

output={'schema':1,'seed':0x434f524f,'scope':'static coroutine translation; map kernels use independently labeled external no-counted-creation input','cases':cases,'kernels':kernels,'waits':waits}
(OUT/'reference_input.json').write_text(json.dumps(output,indent=2),encoding='utf-8')
native=Path(r'D:\Repo\.rea-tools\arknights-pc\native_v3\timeline')
selectors=[('results_round4.json','RuntimeHandler_MoveNext_0x600faf6'),('results_round3.json','Torappu_Battle_CoroutineSimulator_StartCoroutine_0x600fae9'),('results_round3.json','_WaitWhileFixed_d__4_MoveNext_0x600faae'),('results_round5.json','_WaitForFixedSeconds_d__0_MoveNext_0x600fa96'),('results_round5.json','_ExecuteActionQueue_d__21_MoveNext_0x6011a02'),('results_round5.json','UnresolvedCall_CeilToInt_call_target')]
evidence=[]
for filename,name in selectors:
    path=native/filename;report=json.loads(path.read_text('utf-8'));function=next(x for x in report['functions'] if x['name']==name)
    assert function['decompile_completed']
    evidence.append({'report_path':str(path),'report_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'target_sha256':report['target_sha256'],'function':function})
(OUT/'native_evidence.json').write_text(json.dumps({'scope':'retained static native function records; no game execution','records':evidence},indent=2),encoding='utf-8')
print(json.dumps({'cases':len(cases),'kernels':len(kernels),'waits':len(waits),'native_records':len(evidence)}))

"""Compare authored C# bounded timer/wait/buff kernels with Python; never run game."""
from pathlib import Path
import hashlib,json,subprocess,sys
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
sys.path.insert(0,str(ROOT))
from arknights_probe.devices import PrecisePeriodicTimer,ImmediateBuffLifecycle,PreDelayAbility
from arknights_probe.fp import FP

cases=[];expected=[]
for period in [1<<32,1<<31,143165440]:
    for remaining in [-2*period,-period,-1,0,42949,42950,period]:
        for delta in [0,143165440]:
            timer=PrecisePeriodicTimer(FP.from_raw(period),FP.from_raw(remaining))
            count=timer.tick(FP.from_raw(delta))
            cases.append(f'T|{period}|{remaining}|{delta}')
            expected.append(f'{count}|{timer.remaining.raw}')
for delay,dt in [(0,1),(-1,1),(0.6,0.03333330154418945),(2.5,1),(3.5,1),(0.5,1),(1.5,1),(5.5,1)]:
    fired=[];ability=PreDelayAbility(pre_delay_float32=delay,delta_float32=dt,deterministic_simulator=True,spell=lambda targets:fired.append(targets))
    ability.begin(('snapshot',),wait_for_attack_event=False,interrupt_if_target_dead=False)
    tick=0
    while ability.active:
        tick+=1;ability.tick();assert tick<100
    assert fired==[('snapshot',)]
    cases.append(f'W|{delay!r}|{dt!r}');expected.append(f'{ability.wait_frames}|{tick}')
for life in [-42950,-42949,0,42949,42950]:
    for started in [False,True]:
        for marked in [False,True]:
            result=ImmediateBuffLifecycle(FP.from_raw(life),started=started,marked_finished=marked).is_finished
            cases.append(f'B|{life}|{int(started)}|{int(marked)}');expected.append(str(int(result)))
timer=PrecisePeriodicTimer.reset(FP.from_int32(1))
increments=[str(frame) for frame in range(1,362) if timer.tick(FP.from_raw(143165440))]
cases.append('S|361');expected.append(','.join(increments))
csc=Path(r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe')
source=OUT/'DeviceReference.cs';exe=OUT/'DeviceReference.exe'
compiled=subprocess.run([str(csc),'/nologo','/r:System.Numerics.dll',f'/out:{exe}',str(source)],capture_output=True,text=True,check=True)
process=subprocess.run([str(exe)],input='\n'.join(cases)+'\n',capture_output=True,text=True,check=True)
actual=process.stdout.splitlines();assert len(actual)==len(expected)
checks=[{'input':i,'csharp':a,'python':e,'match':a==e} for i,a,e in zip(cases,actual,expected)]
out={'healthy':all(c['match'] for c in checks),'checks':checks,'count':len(checks),'client_runtime_compared':False,'hotfix_runtime_compared':False,'reference_kind':'Authored bounded C# implementation check; not a client/runtime oracle','limits':['C# Divide uses rational BigInteger rounding on small bounded fixtures. Native saturation, NaN/sentinels and overflow outside this reference scope are not certified.','Wait checks use specified deterministic simulator start; no Unity coroutine branch executed.'],'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'compiler_path':str(csc),'compiler_stdout':compiled.stdout}
(OUT/'reference_comparison.json').write_text(json.dumps(out,indent=2),encoding='utf-8')
print(json.dumps({'healthy':out['healthy'],'checks':len(checks),'mismatches':[c for c in checks if not c['match']]}))
if not out['healthy']:raise SystemExit(1)

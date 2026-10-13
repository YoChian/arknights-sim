"""Compile/execute only our C# reference and compare bounded Python traces."""
from pathlib import Path
import hashlib, json, subprocess, sys
OUT=Path(__file__).parent
REPO=Path(r'D:\Repo\arknights-sim'); EVID=REPO/'evidence/skill_runtime'
sys.path.insert(0,str(REPO))
from arknights_probe.fp import FP,ZERO
from arknights_probe.frame_runtime import SharedCoroutineSimulator,CoroutineOwner
from arknights_probe.skill_runtime import explicit_altar_fixture_context,AltarSkillRuntime

dt=FP(143165440)
cases=[]
for name,delay,duration,cooldown,frames in [
 ('normal',.6,1.,1.,1000),('zero',0.,0.,0.,800),
 ('short',.1,.25,.25,850),('long',1.5,1.,1.,900),
 ('duration_cd_different',.6,1.,2.,1000),('zero_pre_long_duration',0.,2.,2.,1000)]:
 cases.append({'name':name,'frames':frames,'delay':FP.from_float32(delay).raw,
               'duration':FP.from_float32(duration).raw,'cooldown':FP.from_float32(cooldown).raw})
EVID.mkdir(exist_ok=True)
inp=EVID/'reference_input.tsv'
inp.write_text('\n'.join('\t'.join(map(str,[c['name'],c['frames'],dt.raw,c['delay'],c['duration'],c['cooldown'],71582720])) for c in cases)+'\n')
csc=r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe'
subprocess.run([csc,'/nologo','/r:System.Numerics.dll',f'/out:{EVID / "SkillCycleReference.exe"}',str(EVID/'SkillCycleReference.cs')],check=True)
native=subprocess.run([str(EVID/'SkillCycleReference.exe'),str(inp)],check=True,capture_output=True,text=True).stdout
native=native.replace('\r',''); (EVID/'reference_output.tsv').write_text(native)
expected=[]
for c in cases:
 clock={'frame':0,'time':ZERO};sim=SharedCoroutineSimulator(source='self-authored bounded reference',deterministic=True)
 context=explicit_altar_fixture_context(source='explicit fixture',prepared_time_source='supplied post-init time fields',pre_delay=FP(c['delay']),duration=FP(c['duration']),cooldown=FP(c['cooldown']),delta_play_time_float=dt.as_float(),half_default_frame=FP(71582720),sp_recovery_per_second=FP.from_int32(1))
 kernel=AltarSkillRuntime(context,simulator=sim,unity_owner=CoroutineOwner(True,True),clock=lambda:(clock['frame'],clock['time']),select_targets=lambda:(),spell=lambda targets:None)
 kernel.initialize()
 for frame in range(1,c['frames']+1):
  clock['frame']=frame;clock['time']+=dt;kernel.fixed_tick(dt);sim.tick()
 for e in kernel.events:
  if e['kind']=='sp_recovered':kind,value='sp',e['sp_raw']
  elif e['kind']=='skill_start':kind,value='start',e['sp_raw']
  elif e['kind']=='sp_recovery_modifier':kind,value='modifier',int(e['registered'])
  elif e['kind']=='spell':kind,value='spell',0
  elif e['kind']=='skill_end':kind,value='finish',0
  else:continue
  expected.append('\t'.join(map(str,[c['name'],e['frame'],kind,value])))
expected='\n'.join(expected)+'\n'
(EVID/'python_output.tsv').write_text(expected)
assert expected==native,'cross-language trace mismatch'
report={'format':'skill_cycle_cross_language_check_v1','source':'self-authored C# bounded rational/tick-phase reference; not real client oracle','cases':cases,'frames_total':sum(c['frames'] for c in cases),'event_rows':len(native.splitlines()),'all_equal':True,'client_runtime_compared':False,'hotfix_runtime_compared':False,'files':[{'path':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in [EVID/'SkillCycleReference.cs',inp,EVID/'reference_output.tsv',EVID/'python_output.tsv']]}
(EVID/'reference_report.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
(OUT/'reference_report.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps({k:report[k] for k in ['cases','frames_total','event_rows','all_equal','client_runtime_compared']}))

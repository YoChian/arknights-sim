"""Independent C# arithmetic translation check, no real client execution."""
from pathlib import Path
import json,hashlib,struct,subprocess,sys
ROOT=Path(__file__).resolve().parents[2];OUT=Path(__file__).parent
sys.path.insert(0,str(ROOT))
from arknights_probe.skill_preparation import prepare_specified_ability,prepare_altar_skill
from arknights_probe.data import Dataset
values=[('actual',.6,1.),('clamp_above',2.,1.),('equal',1.,1.),('zero_pre',0.,1.),
 ('zero_cd',.6,0.),('zero_both',0.,0.),('quarter',.25,.5),('rounds_up',.60000001,1.),
 ('rounds_down',.59999999,1.),('tiny_zero',2**-33,1.),('tiny_one',2**-32,1.),
 ('tiny_clamp',2**-32,2**-33),('small',.001,.002),('large',12345.125,20000.),
 ('large_clamp',20000.,12345.125),('exact_half',.5,1.5),('max_scale_ignored',.7,1.),
 ('single_neighbor',.6000000834465027,1.)]
bits=lambda v:struct.unpack('<I',struct.pack('<f',v))[0]
(OUT/'reference_input.tsv').write_text(''.join(f'{name}\t{bits(pre):08x}\t{bits(cd):08x}\n' for name,pre,cd in values),encoding='utf-8')
csc=Path(r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe');exe=OUT/'Reference.exe'
p=subprocess.run([str(csc),'/nologo','/optimize+','/platform:x64','/out:'+str(exe),str(OUT/'Reference.cs')],capture_output=True,text=True);assert p.returncode==0,p.stdout+p.stderr
p=subprocess.run([str(exe),str(OUT/'reference_input.tsv')],capture_output=True,text=True);assert p.returncode==0,p.stdout+p.stderr
actual=p.stdout.replace('\r','');(OUT/'reference_output.tsv').write_text(actual,encoding='utf-8')
expected=[]
for name,pre,cd in values:
 a,d,c=prepare_specified_ability(pre_delay=pre,cooldown=cd,time_mode=2,animation_key='',animation_keys=('Idle','Born','Die'),wait_for_attack_event=False,max_anim_scale=-1.,native_default_no_hotfix=True)
 expected.append(f'{name}\t{a.raw}\t{d.raw}\t{c.raw}\n')
expected=''.join(expected);(OUT/'python_output.tsv').write_text(expected,encoding='utf-8')
report={'format':'skill_preparation_cross_language_v1','all_equal':actual==expected,'vectors':len(values),'client_runtime_compared':False,'source':'Self-authored C# translation of default SPECIFIED/no animation override arithmetic, compared with Python implementation','limits':['Checks translation agreement only, not a live client oracle.','Hotfixes, valid animation scaling, Unity Init/attachment, owner state and event integration are not executed.'],
 'files':[{'path':str(f.resolve()),'sha256':hashlib.sha256(f.read_bytes()).hexdigest()} for f in [OUT/'Reference.cs',exe,OUT/'reference_input.tsv',OUT/'reference_output.tsv',OUT/'python_output.tsv']]}
(OUT/'reference_report.json').write_text(json.dumps(report,indent=2),encoding='utf-8');assert report['all_equal'];print(json.dumps(report))
result=prepare_altar_skill(Dataset.from_manifest(ROOT/'data/manifest.json'),native_default_no_hotfix=True,no_external_skill_modifier=True)
(OUT/'actual_preparation.json').write_text(json.dumps(result.as_dict(),indent=2),encoding='utf-8')

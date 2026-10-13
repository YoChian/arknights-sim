from pathlib import Path
import hashlib,json,subprocess
OUT=Path(__file__).parent
REPO=Path(r'D:\Repo\arknights-sim')
EVIDENCE=REPO/'evidence/damage';EVIDENCE.mkdir(exist_ok=True)
SCALE=1<<32
cases=[]
attacks=[-(1<<63),-SCALE,-1,0,1,3,42950,42951,SCALE,500*SCALE,(1<<63)-1]
scales=[-(1<<32),0,1,1<<31,1<<32,3<<32,(1<<63)-1]
for a in attacks:
 for s in scales:
  for hp in [1*SCALE,500*SCALE,1000*SCALE]:
   cases.append(dict(id=len(cases),attack_raw=a,scale_raw=s,hp_raw=hp,max_hp_raw=hp))
for remain in [-1,0,1,42949,42950,42951,42952,SCALE]:
 for hp in [1*SCALE,500*SCALE,1000*SCALE]:
  cases.append(dict(id=len(cases),attack_raw=hp-remain,scale_raw=SCALE,hp_raw=hp,max_hp_raw=hp))
inputs=OUT/'reference_inputs.json';inputs.write_text(json.dumps({'cases':cases},indent=2),encoding='utf8')
source=EVIDENCE/'NativeDamageReference.cs';exe=OUT/'NativeDamageReference.exe'
compiler=Path(r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe')
r=subprocess.run([str(compiler),'/nologo','/reference:System.Web.Extensions.dll','/reference:System.Numerics.dll',
                  '/out:'+str(exe),str(source)],text=True,capture_output=True)
assert r.returncode==0,(r.stdout,r.stderr)
r=subprocess.run([str(exe),str(inputs)],text=True,capture_output=True)
assert r.returncode==0,(r.stdout,r.stderr)
results=json.loads(r.stdout);assert len(results['cases'])==len(cases)
vectors=[{'input':a,'expected':e} for a,e in zip(cases,results['cases'])]
target=EVIDENCE/'reference_vectors.json'
target.write_text(json.dumps({'reference_kind':results['reference_kind'],'game_code_loaded':False,'vectors':vectors},indent=2),encoding='utf8')
summary={'case_count':len(cases),'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
         'vectors_sha256':hashlib.sha256(target.read_bytes()).hexdigest(),
         'reference_kind':results['reference_kind'],'game_code_loaded':False,
         'compile_return_code':0,'run_return_code':0}
(EVIDENCE/'reference_comparison.json').write_text(json.dumps(summary,indent=2),encoding='utf8')
print(json.dumps(summary))

"""Compare own C# timer port with selected Python component; not client oracle."""
from pathlib import Path
from dataclasses import replace
import hashlib,json,subprocess,sys
HERE=Path(__file__).parent;ROOT=HERE.parents[1]
sys.path.insert(0,str(ROOT))
from arknights_probe.data import Dataset
from arknights_probe.enemy_factory import prepare_enemy
from arknights_probe.fp import FP
from tests.test_enemy_factory import FactoryFixture

dt=143165440
vectors=[('upeopl_actual',0,dt,5),('shdopl_actual',4294967296,dt,34)]
for raw in [1,42949,42950,42951,dt,dt+1,dt+42949,dt+42950,dt+42951,
            -1,0,-42950,2**63-1,-2**63]:
    for delta in [1,dt]:
        vectors.append((f'raw_{raw}_{delta}',raw,delta,4))
input_path=HERE/'reference_input.csv'
input_path.write_text('\n'.join(','.join(map(str,row)) for row in vectors)+'\n',encoding='utf-8')
compiler=Path(r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe')
exe=HERE/'BirthReference.exe'
compiled=subprocess.run([str(compiler),'/nologo','/checked-',f'/out:{exe}',str(HERE/'BirthReference.cs')],
                        capture_output=True,text=True,timeout=60)
assert compiled.returncode==0,compiled.stdout+compiled.stderr
csharp=subprocess.run([str(exe),str(input_path)],capture_output=True,text=True,timeout=60)
assert csharp.returncode==0,csharp.stderr
got=[line.split(',') for line in csharp.stdout.splitlines() if line]
dataset=Dataset.from_manifest(ROOT/'data/manifest.json')
upeopl=prepare_enemy(dataset,'enemy_3001_upeopl')
shdopl=prepare_enemy(dataset,'enemy_2133_shdopl')
expected=[]
for label,remaining,delta,ticks in vectors:
    prepared=shdopl if label=='shdopl_actual' else upeopl
    f=FactoryFixture(prepared);actor=f.spawn()
    # Non-asset rows isolate the raw countdown boundary with explicit fixtures.
    if not label.endswith('_actual'):actor.born_remaining=FP(remaining)
    else:assert actor.born_remaining.raw==remaining
    moves=0
    for frame in range(1,ticks+1):
        moves+=int(f.tick(actor,FP(delta)))
        expected.append([label,str(frame),str(actor.state_id),str(actor.born_remaining.raw),str(moves)])
assert got==expected, next((g,e) for g,e in zip(got,expected) if g!=e)
(HERE/'reference_output.csv').write_text(csharp.stdout,encoding='utf-8')
result={'healthy':True,'cross_language_vectors':len(vectors),'frame_records':len(got),
        'compiler_path':str(compiler),'reference_executable_sha256':hashlib.sha256(exe.read_bytes()).hexdigest(),
        'validation':'Own C# implementation comparison of source-derived raw countdown/state dispatch, not a native/client oracle',
        'actual_asset_rows':2,'boundary_fixture_rows':len(vectors)-2,'client_runtime_compared':False}
(HERE/'reference_checks.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
print(json.dumps(result))

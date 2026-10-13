"""Compile/run own C# model and compare bounded Python execution vectors."""
from pathlib import Path
import json, struct, subprocess, sys, hashlib
HERE=Path(__file__).resolve().parent; ROOT=HERE.parents[1]
sys.path.insert(0,str(ROOT)); sys.path.insert(0,str(ROOT/'tests'))
from test_npc_restore import Fixture, actor
from arknights_probe.fp import FP
from arknights_probe.npc_restore import color_segment

vectors=[]
for dt in [.03333330154418945,.11999999731779099,.12000000476837158,
           .06666667014360428,.20000000298023224,.6000000238418579]:
    for clear in [-1,0,1,2,8,9,10,15]:
        p=[-.5,0.,.5,1.,1.3][len(vectors)%5]
        vectors.append(dict(delta_float=dt,clear_frame=clear,progress=p))
source=HERE/'RestoreReference.cs'; exe=HERE/'RestoreReference.exe'
input_path=HERE/'reference_input.csv'; output_path=HERE/'reference_output.csv'
input_path.write_text(''.join(f"{v['delta_float']:.17g},{v['clear_frame']},{v['progress']:.17g}\n" for v in vectors))
subprocess.run([r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe',
               '/nologo','/optimize+',f'/out:{exe}',str(source)],check=True)
subprocess.run([str(exe),str(input_path),str(output_path)],check=True)
csharp=output_path.read_text().splitlines()
results=[]
for v,row in zip(vectors,csharp,strict=True):
    f,a=Fixture(FP.from_float32(v['delta_float'])),actor()
    f.runtime.set_disappeared(a,True)
    if v['clear_frame']==0:f.runtime.set_disappeared(a,False)
    for n in range(1,25):
        if n==v['clear_frame']:f.runtime.set_disappeared(a,False)
        f.tick(a)
    def first(kind,predicate=lambda e:True):
        return next((e['frame'] for e in f.runtime.events if e['kind']==kind and predicate(e)),-1)
    hidden=first('set_active',lambda e:e['value'] is False)
    transition=first('switch_default_requested'); move=first('move_tick')
    rgb=color_segment((.123456789,.9,-.4,.7),v['progress'],'rgb')[:3]
    alpha=color_segment((.123456789,.9,-.4,.7),v['progress'],'alpha')[3]
    bits=[format(struct.unpack('<I',struct.pack('<f',x))[0],'08x') for x in (*rgb,alpha)]
    actual=','.join(map(str,[hidden,transition,move,int(a.game_active),*bits]))
    assert actual==row,(v,actual,row)
    results.append(dict(input=v,csharp=row,python=actual,match=True))
report={'kind':'self-authored cross-language implementation check; NOT client oracle',
        'vector_count':len(results),'matches':len(results),'csharp_source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'vectors':results}
(HERE/'reference_results.json').write_text(json.dumps(report,indent=2))
print(json.dumps({k:report[k] for k in ['kind','vector_count','matches']}))

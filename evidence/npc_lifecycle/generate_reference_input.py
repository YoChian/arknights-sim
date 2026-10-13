"""Declared control-flow/accounting fixtures; no game RNG or live context."""
import itertools
import json
from pathlib import Path
import struct

ROOT=Path(__file__).resolve().parent
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
rows=[]
for reason,flags,override in itertools.product((2,7),itertools.product((False,True),repeat=6),(-5,0,3,-2147483648,2147483647)):
    summon,dont,always,unharmful,invalid,is_override=flags
    i=len(rows)
    rows.append(dict(id=i,reason=reason,is_summon=summon,dont_count=dont,always_count=always,
        unharmful=unharmful,invalid=invalid,is_override=is_override,override_count=override,
        counters=[2147483647 if i%9==0 else 0,0,0,2 if i%7==0 else 0,0]))
lifetime=[]
epsilon=f32(1e-5)
after_epsilon=struct.unpack('<f',struct.pack('<I',struct.unpack('<I',struct.pack('<f',epsilon))[0]+1))[0]
for reason,delay,flag,ground,dummy in itertools.product((2,7),(-.1,0.,epsilon,after_epsilon,.3,1.),(False,True),(False,True),(False,True)):
    i=len(lifetime)
    lifetime.append(dict(id=i,reason=reason,delay=f32(delay),recycle_flag=flag,ground=ground,dummy=dummy,
        owner_available=i%5!=0,specific=i%2==0,animation_found=i%3==0,animation_length=f32(.6),
        source_exists=i%4==0,unharmful=i%4!=0,dont_block=i%3!=1,delta=f32(0.03333330154418945)))
output={'scope':'source-owned declared fixtures for translated native branches; not client input or runtime output',
        'accounting':rows,'lifetime':lifetime}
(ROOT/'reference_input.json').write_text(json.dumps(output,indent=2)+'\n','utf-8')
print(json.dumps({'accounting':len(rows),'lifetime':len(lifetime)}))

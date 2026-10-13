"""Deterministic boundary and varied raw vectors for the owned C# reference."""
from pathlib import Path
import json, random, struct, math

ROOT=Path(__file__).parent
ONE=1<<32;MIN=-(1<<63);MAX=(1<<63)-1
raw=set([0,1,-1,MIN,MIN+1,MIN+2,MAX,MAX-1,MAX-2])
for v in [ONE//2,ONE,ONE+ONE//2,ONE*2,ONE*3,ONE*20,ONE*80,ONE//30,ONE//60]:
    for sign in [-1,1]:
        raw.update([sign*v-1,sign*v,sign*v+1])
# Around binary32 midpoint at high int64 magnitude: direct int64->float32
# must not round first to binary64.
for shift in [31,35,39]:
    midpoint=((1<<23)<<shift)+(1<<(shift-1))
    raw.update([midpoint-1,midpoint,midpoint+1,-midpoint-1,-midpoint,-midpoint+1])
raw=sorted(raw)
randomizer=random.Random(0x46503232)
pair_values=[(x,y) for x in raw for y in raw]
pair_values += [(randomizer.randrange(MIN,MAX+1),randomizer.randrange(MIN,MAX+1)) for _ in range(512)]
f32_bits=set([0,0x80000000,1,0x80000001,0x7fffff,0x800000,0x7f800000,0xff800000,0x7fc00000])
f64_bits=set([0,1,0x8000000000000000,0x7ff0000000000000,0xfff0000000000000,0x7ff8000000000000])
for f in [1/30,1/60,0.1,0.2,0.5,1.0,7.0,20.0,80.0,math.pi,2**-32,2**-33,2**31,math.nextafter(2**31,0),2**-40,-2**31]:
    for sign in [1,-1]:
        bits=struct.unpack('<I',struct.pack('<f',f*sign))[0]
        f32_bits.update([bits-1,bits,bits+1])
        bits=struct.unpack('<Q',struct.pack('<d',f*sign))[0]
        f64_bits.update([bits-1,bits,bits+1])
output={'schema':1,'seed':0x46503232,'pairs':[[str(x),str(y)] for x,y in pair_values],'raw_values':[str(x) for x in raw], 'float32_bits':[f'{x:08x}' for x in sorted(f32_bits)], 'double_bits':[f'{x:016x}' for x in sorted(f64_bits)]}
(ROOT/'reference_input.json').write_text(json.dumps(output,indent=2),encoding='utf-8')
print(json.dumps({'raw_values':len(raw),'pairs':len(pair_values),'float32':len(f32_bits),'double':len(f64_bits)}))

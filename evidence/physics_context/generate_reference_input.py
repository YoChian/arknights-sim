"""Explicit boundary/query-input fixtures. Fixture RNG is not game RNG."""
from pathlib import Path
import json
import random
import struct


def bits(value):
    return f"0x{struct.unpack('<I',struct.pack('<f',value))[0]:08x}"


def generate():
    rng=random.Random(810718)
    values=[0.,-0.,1e-30,1e-16,.001,.1,.5,1.,-1.,9.,-9.,float(1<<24),-float(1<<24),1e20,3e38,-3e38]
    boxes=[]
    for i in range(300):
        row={"id":f"box{i}"}
        for key in ("minimum_center","minimum_extents","maximum_center","maximum_extents"):
            row[key]=[bits(rng.choice(values) if i<80 else rng.uniform(-1e5,1e5)) for _ in range(3)]
        boxes.append(row)
    radii=[]
    special=[(0.,0.,0.),(-0.,0.,0.),(3.,4.,12.),(.1,0.,0.),(1e-30,1e-30,1e-30),
             (1e-16,1e-16,1e-16),(1e20,0.,0.),(3e38,3e38,3e38),(-1e20,1e20,0.),
             (1e-20,0.,0.),(2.0**-149,0.,0.)]
    for i in range(200):
        value=special[i] if i<len(special) else tuple(rng.uniform(-1e6,1e6)*(1e-20 if i%3==0 else 1) for _ in range(3))
        radii.append({"id":f"radius{i}","transformed_radius_vector":[bits(x) for x in value]})
    masks=[-1,-0x80000000,0x7fffffff,0,1,512,1024,1<<28,0x10000600]
    masks += [rng.randrange(-0x80000000,0x80000000) for _ in range(6)]
    filters=[{"id":f"filter{i}:{flag}","layer_mask":value,"queries_hit_triggers":flag} for i,value in enumerate(masks) for flag in (False,True)]
    return {"scope":"explicit scalar finite/boundary fixtures; no transform or overlap outputs are generated","boxes":boxes,"radii":radii,"filters":filters}


if __name__=="__main__":
    (Path(__file__).parent/"reference_input.json").write_text(json.dumps(generate(),indent=2),'utf-8')

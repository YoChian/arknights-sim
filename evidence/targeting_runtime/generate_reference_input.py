"""Reproducible explicit test data. Python fixture RNG is not game RNG."""
import json
from pathlib import Path
import random


def generate():
    r=random.Random(700718)
    one=1<<32;gap=4294967;big=1000000*one
    boundaries=[0,1,-1,gap-1,gap,gap+1,one-1,one,one+1,
        big-50000,big-42950,big-42949,big-1,big,big+1,big+42949,big+42950,big+50000,
        big+one,big+one+gap-1,big+one+gap,big+2*one,
        -big-1,-big,-big+1,-big-one,-big-one-gap,
        -(1<<63),-(1<<63)+1,(1<<63)-1]
    comparisons=[]
    for i,a in enumerate(boundaries):
        for k,b in enumerate(boundaries):
            comparisons.append({"id":f"edge{i}:{k}","uid":0xffffffff if i%2 else 1,
                "raw":str(a),"other_uid":0x80000000 if k%2 else 2,"other_raw":str(b)})
    for i in range(600):
        a=r.randrange(-(1<<63),(1<<63));b=r.choice([a,a+r.randrange(-50000,50001),r.randrange(-(1<<63),(1<<63))])
        b=max(-(1<<63),min((1<<63)-1,b))
        comparisons.append({"id":f"pair{i}","uid":r.randrange(1,1<<32),"raw":str(a),
            "other_uid":r.randrange(1,1<<32),"other_raw":str(b)})
    queues=[]
    for i in range(120):
        n=r.choice([0,1,2,3,5,16,64,127,128]);items=[]
        for k in range(n):
            value=r.choice(boundaries) if i%3==0 else r.randrange(0,100)*gap+r.randrange(gap)
            items.append({"uid":k+1 if i%2 else 0xffffffff-k,"raw":str(value),"alive":r.random()>.13})
        r.shuffle(items);queues.append({"id":f"queue{i}","items":items})
    statuses=[]
    for i in range(400):
        flag=r.choice([7,9,15,17,63]);active=r.choice([-32768,-1,0,1,32767]);immune=r.choice([-32768,-1,0,1,32767])
        bits=r.choice([0,1<<flag,(1<<64)-1,r.randrange(1<<64)])
        statuses.append({"id":f"status{i}","flag":flag,"active":active,"immune":immune,"base_bits":str(bits)})
    return {"scope":"explicit static-boundary fixtures; generator RNG unrelated to game", 
        "comparisons":comparisons,"queues":queues,"statuses":statuses}


if __name__=="__main__":
    (Path(__file__).parent/"reference_input.json").write_text(json.dumps(generate(),indent=2),"utf-8")

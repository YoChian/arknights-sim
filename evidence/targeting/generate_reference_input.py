"""Generate explicit source-owned contexts, never game RNG or runtime outputs."""
import json
import random
from pathlib import Path


def generate():
    rng = random.Random(624812)  # only reproducible test-context generation
    diamond = [(2,0),(1,-1),(1,0),(1,1),(0,-2),(0,-1),(0,0),(0,1),(0,2),(-1,-1),(-1,0),(-1,1),(-2,0)]
    shapes = [[], [(0,0)], diamond, [(0,1),(1,0),(1,1),(1,2),(2,1)],
              [(32767,32767),(-32767,-32767)], [(0,0),(0,0),(0,1)],
              [(r,c) for r in range(-2,3) for c in range(-4,5)]]
    geometry = [{"id":f"shape{i}-dir{d}","grids":g,"direction":d}
                for i,g in enumerate(shapes) for d in range(4)]
    for i in range(120):
        grids = [(r,c) for r in range(-6,7) for c in range(-6,7) if rng.random() < .45]
        rng.shuffle(grids)
        geometry.append({"id":f"grid{i}","grids":grids,"direction":rng.randrange(4)})
    collectors=[]
    for i in range(100):
        context={"source_side":rng.choice([0,1,2,4]),"source_map_layer":0,
            "source_purpose_mask":rng.randrange(4),"opposite_side_mask":rng.choice([1,2,3,4]),
            "ability_ignores_camouflage":bool(rng.randrange(2)),"deterministic":bool(rng.randrange(2)),
            "has_custom_validator":bool(rng.randrange(2))}
        entities=[]
        for uid in [0,1,2,9,0x7fffffff,0x80000000,0xffffffff]+list(range(10,90)):
            entities.append({"uid":uid,"side":rng.choice([0,1,2,4]),"motion":rng.randrange(3),
                "category":rng.choice([0,1,2,3]),"map_layer":rng.choice([0,0,0,1]),
                "alive":rng.random()>.1,"destroyed":rng.random()<.05,
                "ally_target_free":rng.random()<.2,"heal_free":rng.random()<.2,
                "camouflage":rng.random()<.2,"hit_range":rng.random()>.15,
                "custom_validator":rng.random()>.2,"excluded":rng.random()<.1})
        colliders=[]
        for _ in range(rng.randrange(1,5)):
            hits=[rng.choice(entities+[None]) for _ in range(rng.randrange(5,70))]
            colliders.append({"destroyed":rng.random()<.1,"hits":hits})
        collectors.append({"id":f"context{i}","context":context,"colliders":colliders})
    for deterministic in [False,True]:
        for n in [0,1,127,128,129,200]:
            context={"source_side":4,"source_map_layer":0,"source_purpose_mask":1,
                "opposite_side_mask":3,"ability_ignores_camouflage":False,
                "deterministic":deterministic,"has_custom_validator":False}
            hits=[{"uid":u,"side":2,"motion":0,"category":1,"map_layer":0,"alive":True,
                "destroyed":False,"ally_target_free":False,"heal_free":False,"camouflage":False,
                "hit_range":True,"custom_validator":True,"excluded":False} for u in range(n,0,-1)]
            collectors.append({"id":f"cap{n}-det{deterministic}","context":context,
                "colliders":[{"destroyed":False,"hits":hits}]})
    return {"scope":"explicit fixtures; generation random.Random is unrelated to game RNG",
            "geometry":geometry,"collectors":collectors}


if __name__ == "__main__":
    (Path(__file__).parent / "reference_input.json").write_text(json.dumps(generate(),indent=2),"utf-8")

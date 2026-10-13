"""Create inputs only; no Python movement results enter the C# reference."""
from pathlib import Path
import json
import random
import struct

ROOT = Path(__file__).resolve().parent


def bits(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


def vector(x, y):
    return [bits(x), bits(y)]


def generate():
    rng = random.Random(912835)  # fixture construction only; never battle RNG
    rounding = [{"position": vector(x, -x), "enabled": mode}
        for mode in [False, True]
        for x in [0., -0., .00005, .00015, .00025, 1.23445, 1.23455, 12345.1234,
                  1e-20, 1e6] + [rng.uniform(-1e4, 1e4) for _ in range(150)]]
    avoidance, controllers = [], []
    for index in range(80):
        grid = [[[rng.choice([False, True]), rng.choice([False, False, True])]
                 for _ in range(5)] for _ in range(4)]
        grid[1][2] = [index % 4 != 0, False]
        avoidance.append({"grid": grid, "offset_position": vector(rng.uniform(1.51, 2.49), rng.uniform(.51, 1.49)),
            "foot_position": vector(rng.uniform(1.3, 2.7), rng.uniform(.3, 1.7)), "half_body_width": bits(.2)})
        context = {"new_steering": bool(index % 2), "initial_steering": bits(8), "max_force": bits(10),
                   "half_body_width": bits(.2), "foot_offset": vector(0, -.1)}
        steps = [{"direction": vector(0, 0) if i % 7 == 0 else vector(rng.uniform(-1, 1), rng.uniform(-1, 1)),
            "position": vector(rng.uniform(1.6, 2.4), rng.uniform(.6, 1.4)),
            "offset_position": vector(rng.uniform(1.6, 2.4), rng.uniform(.6, 1.4)),
            "speed": bits([0, 1e-6, .1, 1, 1.9][i % 5]), "can_move": i % 11 != 0,
            "delta": bits([0, .03333330154418945, .05, .1][i % 4])}
            for i in range(30)]
        controllers.append({"grid": grid, "context": context, "steps": steps})
    return {"scope": "explicit generated fixture inputs; no client/default RNG claim",
            "rounding": rounding, "avoidance": avoidance, "controllers": controllers}


if __name__ == "__main__":
    result = generate()
    (ROOT / "reference_input.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"rounding": len(result["rounding"]), "avoidance": len(result["avoidance"]),
                      "controller_frames": sum(len(c["steps"]) for c in result["controllers"])}))

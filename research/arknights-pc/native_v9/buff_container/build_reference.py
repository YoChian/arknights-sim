"""Generate bounded mutation plans; C# calculates expected iterator traces."""
from pathlib import Path
import json, random, subprocess, shutil

OUT = Path(__file__).parent
EVIDENCE = Path(r"D:\Repo\arknights-sim\evidence\buff_container")
rng = random.Random(48173)
vectors = []
for case in range(192):
    ops = []
    ids = []
    depth = 0
    next_id = 1
    for step in range(48):
        kind = rng.choice(["add", "begin", "scan", "remove", "invalidate", "clear", "live"] +
                          (["next", "end"] if depth else []))
        if kind == "add":
            ops.append([kind, next_id, rng.choice([-2000, 0, 0, 1000, 2000])])
            ids.append(next_id)
            next_id += 1
        elif kind == "begin":
            if depth >= 4:
                continue
            ops.append([kind, rng.randrange(2)])
            depth += 1
        elif kind == "end":
            ops.append([kind])
            depth -= 1
        elif kind in ("remove", "invalidate"):
            if ids:
                ops.append([kind, rng.choice(ids)])
        elif kind == "scan":
            ops.append([kind, rng.randrange(2)])
        else:
            ops.append([kind])
    ops.extend([["end"] for _ in range(depth)])
    ops += [["scan", 0], ["scan", 1], ["live"]]
    vectors.append({"id": case, "operations": ops})
source = {"seed": 48173, "vectors": vectors}
(OUT / "reference_inputs.json").write_text(json.dumps(source, indent=2), "utf8")
compiler = Path(r"C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe")
exe = OUT / "NativeBuffContainerReference.exe"
subprocess.run([str(compiler), "/nologo", "/reference:System.Web.Extensions.dll", "/out:" + str(exe),
                str(OUT / "NativeBuffContainerReference.cs")], check=True)
subprocess.run([str(exe), str(OUT / "reference_inputs.json"), str(OUT / "reference_vectors.json")], check=True)
EVIDENCE.mkdir(exist_ok=True, parents=True)
for filename in ["NativeBuffContainerReference.cs", "reference_inputs.json", "reference_vectors.json"]:
    shutil.copyfile(OUT / filename, EVIDENCE / filename)
print(json.dumps({"vectors": len(vectors), "reference": str(EVIDENCE / "reference_vectors.json")}))

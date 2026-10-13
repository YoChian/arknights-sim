"""Read only the exact prepared PE ranges; never execute the native target."""
from pathlib import Path
import hashlib
import json
import sys

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[1]
sys.path.insert(0, str(ROOT / "tools/python"))
import capstone

INPUT = Path(sys.argv[1]) if len(sys.argv) > 1 else OUT / "input_round1.json"
source = json.loads(INPUT.read_text("utf-8"))
inventory = json.loads((ROOT / "core/pe_inventory.json").read_text("utf-8"))
pe = next(x for x in inventory if x["path"].endswith("GameAssembly.dll"))
engine = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
labels = dict(line.split("\t", 1) for line in (ROOT / "native_v2/labels.tsv").read_text("utf-8").splitlines())
records = []
with Path(pe["path"]).open("rb") as stream:
    digest = hashlib.file_digest(stream, "sha256").hexdigest()
    assert digest == source["target_sha256"] == pe["sha256"]
    for target in source["targets"]:
        components = []
        for piece in target["ranges"]:
            start, end = int(piece["start"], 16), int(piece["end"], 16)
            stream.seek(piece["source_file_offset"])
            data = stream.read(end - start + 1)
            assert hashlib.sha256(data).hexdigest() == piece["source_sha256"]
            instructions = []
            for instruction in engine.disasm(data, start):
                instructions.append({"address": hex(instruction.address), "bytes": instruction.bytes.hex(),
                    "mnemonic": instruction.mnemonic, "operands": instruction.op_str,
                    "direct_target_candidate_label": labels.get(instruction.op_str) if instruction.mnemonic in ("call", "jmp") else None})
            components.append({**piece, "instructions": instructions})
        records.append({"display_name": target["display_name"], "address": target["address"],
                        "metadata_method_index": target["metadata_method_index"], "components": components})
result = {"target_sha256": digest, "source_input": str(INPUT), "source_input_sha256": hashlib.sha256(INPUT.read_bytes()).hexdigest(),
          "scope": "exact source-owned PE unwind/leaf ranges; raw instruction evidence only; no execution", "functions": records}
destination = OUT / ("raw_" + INPUT.stem.removeprefix("input_") + ".json")
destination.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"output": str(destination), "functions": len(records)}))

"""Exact PE unwind bodies of selected small default-branch helpers."""
import hashlib
import json
from pathlib import Path

OUT = Path(__file__).resolve().parent
BASE = OUT.parents[1]
SOURCE = BASE / "native_v5/lifecycle/prepare.py"
ns = {"__file__": str(SOURCE)}
exec(compile(SOURCE.read_text("utf-8").split("selection=json.loads")[0], str(SOURCE), "exec"), ns)
blob, imagebase = ns["b"], int(ns["pe"]["image_base"],16)
targets = {
    0x180708ee0: "Entity.get_unfinished",
    0x180703fa0: "Entity.get_finishReason",
    0x184257960: "Unresolved recycle cleanup call target; class identity not assumed",
    0x180634dc0: "BattleController.UnregisterBObject",
    0x1809196f0: "Scheduler._CheckFinalNotFinish raw corroboration; earlier import verification not recorded",
}
records = []
for address, name in targets.items():
    root = address-imagebase
    assert root in ns["groups"], hex(address)
    ranges = []
    for start, end, unwind in ns["groups"][root]:
        off = ns["rva"](start, end-start)
        raw = blob[off:off+end-start]
        instructions = [{"address":hex(i.address),"bytes":i.bytes.hex(),
                         "mnemonic":i.mnemonic,"operands":i.op_str}
                        for i in ns["engine"].disasm(raw,imagebase+start)]
        ranges.append({"start":hex(imagebase+start),"end_exclusive":hex(imagebase+end),
                       "unwind_rva":hex(unwind),"source_file_offset":off,
                       "source_sha256":hashlib.sha256(raw).hexdigest(),"instructions":instructions})
    records.append({"name":name,"address":hex(address),"ranges":ranges,
                    "candidate_aliases":[x for x in ns["rows"] if x["candidate_va"]==hex(address)]})
output={"target_sha256":ns["pe"]["sha256"],"source_helper_path":str(SOURCE),
        "source_helper_sha256":hashlib.sha256(SOURCE.read_bytes()).hexdigest(),"functions":records,
        "limits":["Original static bytes only; no initialized runtime or hotfix state.",
                  "Same-address aliases do not by themselves identify the specialized generic class."]}
(OUT/"raw_helpers.json").write_text(json.dumps(output,ensure_ascii=False,indent=2)+"\n","utf-8")
for record in records:
    print(record["name"],record["address"])
    for r in record["ranges"]:
        for i in r["instructions"]:print(i["address"],i["mnemonic"],i["operands"])

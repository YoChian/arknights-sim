"""Cross-language migration checks, never a real-client behavior oracle."""
from pathlib import Path
import hashlib
import json
import math
import struct
import unittest

from arknights_probe.coroutines import (
    CoroutineRunner, NEXT_FRAME, fixed_seconds, float_wait_frames, serial_queue, wait_while,
)
from arknights_probe.fp import FP, binary32
from arknights_probe.data import Dataset
from arknights_probe.timeline import CompiledTimeline, TimelineEnv, compile_timeline

ROOT=Path(__file__).resolve().parents[1]
DIRECTORY=ROOT/"evidence"/"timeline_reference"
REFERENCE_PINS={
    "TimelineReference.cs":"45a18746d122f825a30c64effff20b86b70d90a3512c1c1c846e2256db4200c0",
    "reference_input.json":"9efe2c16f1940a232c3a04a39ea4c2666feb52f276546192afd60c95c8f80e24",
    "reference_vectors.json":"23a59a0b04445d306fd76300b2bd536a4294f3f4675c7a6e374f467a9861811b",
    "native_evidence.json":"d7489ea915597e63be2aee50b7fb105cec310cefb6613eb211ed3a2ca92d5d10",
}


def from_bits(bits):
    return struct.unpack("<f",bytes.fromhex(bits)[::-1])[0]


def bits(value):
    return f'{struct.unpack("<I",struct.pack("<f",value))[0]:08x}'


class ReferenceContext:
    def __init__(self,delta):
        self.frame,self.delta,self.events=0,delta,[]

    def log(self,kind,label):
        self.events.append({"frame":self.frame,"kind":kind,"label":label})


def dsl_sequence(operations,context):
    """Assemble native primitives from fixture DSL; the production runner runs it."""
    for operation in operations:
        kind=operation["op"]
        if kind=="event":
            context.log("event",operation["label"])
        elif kind=="child":
            yield dsl_sequence(operation["ops"],context)
        elif kind=="marker":
            marker=operation.get("value","null")
            yield None if marker=="null" else [] if marker=="list" else NEXT_FRAME
        elif kind=="wait":
            yield fixed_seconds(operation["delay"],context.delta)
        elif kind=="while":
            values=iter(operation["values"])
            final=operation["values"][-1]
            def predicate(values=values,final=final,label=operation["label"]):
                result=next(values,final)
                context.log("predicate",label+":"+str(result).lower())
                return result
            yield wait_while(predicate)
        elif kind=="queue":
            def execute(item):
                context.log(item.get("kind","execute"),item["label"])
                for _ in range(item.get("frames",1)):
                    yield NEXT_FRAME
            yield serial_queue(operation["items"],execute,context.delta)
        else:
            raise AssertionError("Unknown reference DSL operation: "+kind)


def run_python_case(spec):
    context=ReferenceContext(from_bits(spec["delta_bits"]))
    runner=CoroutineRunner(dsl_sequence(spec["ops"],context));trace=[]
    for frame in range(spec["max_frames"]):
        context.frame=frame
        active=runner.tick()
        trace.append({"frame":frame,"calls":runner.ticks,"active":active,
                      "depth":len(runner.stack),"event_count":len(context.events)})
        if not active:
            break
    return {"name":spec["name"],"trace":trace,"events":context.events,
            "completed":not runner.active,"delta_bits":spec["delta_bits"]}


def run_python_kernel(spec,dataset):
    if "mode" in spec:
        compiled=compile_timeline(dataset,mode=spec["mode"],group_selections=spec["group_selections"],
                                  enemy_runtime=spec["enemy_runtime"],input_source=spec["input_source"])
    else:
        compiled=CompiledTimeline(spec["waves"],{}, {},[],"NORMAL",
            {"input_source":"synthetic_reference_external_no_enemy_fixture","enemy_runtime":{},
             "enabled_hidden":[],"disabled_hidden":[]})
    labels={}
    for wave in spec["waves"]:
        for fragment in wave["fragments"]:
            for item in fragment["items"]:
                path,occurrence,key=item["label"].split("|",2)
                labels[(item["kind"],path,key,bits(item["time"]))]=item["label"]
    env=TimelineEnv(dataset,compiled,dt_raw=int(spec["dt_raw"]))
    _,info=env.reset()
    assert info["live_fixed_delta_validated"] is False
    assert info["seed_consumed"] is False
    # This is an explicit fixture input, not an automatic battle resolution.
    env.step({"type":"external_final_complete","source":"independent_CSharp_reference_fixture"})

    def projected_events():
        result=[]
        for event in env.events:
            kind=event["kind"]
            if kind in {"spawn_request","activate_predefined_request","preview_cursor_request"}:
                label=labels[(kind,event["path"],event["key"],bits(event["planned_float_time"]))]
            elif kind=="wave_kernel_complete":
                kind,label="wave_complete",str(event["wave"])
            elif kind=="scheduler_kernel_complete":
                kind,label="kernel_complete",""
            else:
                continue
            result.append({"frame":event["frame"],"kind":kind,"label":label})
        return result

    trace=[]
    for frame in range(spec["max_frames"]):
        if frame:
            env.step({"type":"tick"})
        events=projected_events()
        trace.append({"frame":env.current_frame,"calls":env.runner.ticks,"active":env.runner.active,
                      "depth":len(env.runner.stack),"event_count":len(events),"time_raw":str(env.time.raw)})
        if not env.runner.active:
            break
    return {"name":spec["name"],"trace":trace,"events":events,"completed":not env.runner.active,
            "delta_bits":spec["delta_bits"]}


class TimelineReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.inputs=json.loads((DIRECTORY/"reference_input.json").read_text("utf-8"))
        cls.reference=json.loads((DIRECTORY/"reference_vectors.json").read_text("utf-8"))
        cls.dataset=Dataset.from_manifest(ROOT/"data/manifest.json")

    def test_reference_scope_and_static_native_evidence(self):
        for name,digest in REFERENCE_PINS.items():
            self.assertEqual(hashlib.sha256((DIRECTORY/name).read_bytes()).hexdigest(),digest,name)
        self.assertEqual(self.reference["oracle_scope"],
            "independent C# IEnumerator translation of static native paths; not game runtime")
        self.assertEqual(self.reference["pointer_bits"],64)
        evidence=json.loads((DIRECTORY/"native_evidence.json").read_text("utf-8"))
        self.assertEqual(len(evidence["records"]),6)
        for record in evidence["records"]:
            self.assertEqual(record["target_sha256"],
                "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5")
            self.assertTrue(record["function"]["decompile_completed"])

    def test_independent_csharp_nested_coroutine_matrix(self):
        self.assertEqual(len(self.inputs["cases"]),106)
        self.assertEqual(len(self.reference["cases"]),106)
        for spec,reference in zip(self.inputs["cases"],self.reference["cases"]):
            with self.subTest(case=spec["name"]):
                actual=run_python_case(spec)
                self.assertEqual(actual,reference)
                self.assertTrue(actual["completed"])

    def test_independent_binary32_wait_matrix(self):
        self.assertEqual(len(self.reference["waits"]),155)
        for reference in self.reference["waits"]:
            delay,delta=from_bits(reference["delay_bits"]),from_bits(reference["delta_bits"])
            self.assertEqual(bits(binary32(delay/delta)),reference["quotient_bits"])
            self.assertEqual(float_wait_frames(delay,delta),reference["frames"])

    def test_empty_child_first_false_and_completed_old_child_boundaries(self):
        lookup={x["name"]:x for x in self.reference["cases"]}
        self.assertEqual(lookup["event_only_prime_frame0"]["events"],
                         [{"frame":0,"kind":"event","label":"prime"}])
        self.assertEqual([x["frame"] for x in lookup["new_empty_child_suspends_parent"]["events"]],[0,1])
        self.assertEqual([x["frame"] for x in lookup["three_empty_siblings"]["events"]],[1,2,3])
        filled=lookup["filled_child_finishes_same_frame"]["events"]
        self.assertEqual([x["frame"] for x in filled],[0,1,1])
        self.assertEqual(lookup["empty_root"]["trace"],
                         [{"frame":0,"calls":1,"active":False,"depth":0,"event_count":0}])

    def test_waitwhile_always_yields_before_predicate(self):
        lookup={x["name"]:x for x in self.reference["cases"]}
        false=lookup["wait_while_initial_false"]["events"]
        self.assertEqual(false,[{"frame":0,"kind":"event","label":"before"},
            {"frame":1,"kind":"predicate","label":"p:false"},
            {"frame":1,"kind":"event","label":"after"}])
        sequence=lookup["wait_while_true_true_false"]["events"]
        self.assertEqual([x["frame"] for x in sequence],[1,2,3,3])
        self.assertEqual([x["label"] for x in sequence],["p:true","p:true","p:false","after"])

    def test_serial_planned_delta_and_same_time_suspensions(self):
        lookup={x["name"]:x for x in self.reference["cases"]}
        for name in ["serial_zero_time_empty_executors","serial_zero_time_single_frame_executors"]:
            self.assertEqual([x["frame"] for x in lookup[name]["events"]],[0,1,2,3])
        self.assertEqual([x["frame"] for x in lookup["serial_planned_difference_with_executor_drift"]["events"]],[4,10,12])
        self.assertEqual([x["frame"] for x in lookup["serial_invalid_advances_planned_time"]["events"]],[3,4])

    def test_independent_csharp_frame0_kernels_and_real_map_external_fixtures(self):
        self.assertEqual(len(self.reference["kernels"]),6)
        for spec,reference in zip(self.inputs["kernels"],self.reference["kernels"]):
            with self.subTest(kernel=spec["name"]):
                actual=run_python_kernel(spec,self.dataset)
                self.assertEqual(actual,reference)
                self.assertTrue(actual["completed"])
                self.assertEqual(actual["trace"][0]["frame"],0)
                self.assertEqual(actual["trace"][0]["time_raw"],"0")
        expected={"zero_waves":1,"one_empty_wave":5,"two_empty_waves_three_fragments":10}
        for kernel in self.reference["kernels"]:
            if kernel["name"] in expected:
                self.assertEqual(kernel["trace"][-1]["frame"],expected[kernel["name"]])

    def test_diagnostic_unsupported_wait_inputs_fail_closed(self):
        # This is a documented diagnostic restriction, not native parity.
        for delay,delta in [(math.nan,.25),(math.inf,.25),(1,0),(1,-.25),(1,math.nan),(1,math.inf),(1e20,.25)]:
            with self.assertRaises(ValueError):
                float_wait_frames(delay,delta)
        for delay,expected in [(.125,1),(.375,2),(.625,2),(.875,4)]:
            self.assertEqual(float_wait_frames(delay,.25),expected)


if __name__=="__main__":
    unittest.main()

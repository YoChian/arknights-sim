"""Verify immutable previous sources, reviewed v8 sources and both compositions."""
import contextlib
import io
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import verify_v7_snapshot as previous
from arknights_probe import Dataset
from arknights_probe.data import read_json, require
from arknights_probe.npc_component import run_npc_component_fixtures
from arknights_probe.physics_altar import PhysicsPlannedAltarProbe
from arknights_probe.v8_validation import verify_v8_evidence


def main():
    artifacts = ROOT / "artifacts"
    console = io.StringIO()
    with contextlib.redirect_stdout(console):
        status = previous.main()
    (artifacts / "verification_v8_previous_console.txt").write_text(console.getvalue(), encoding="utf8")
    require(status == 0, "Previous source/component verification failed")
    base = read_json(artifacts / "verification_v7.json")
    evidence = verify_v8_evidence()
    npc = run_npc_component_fixtures()
    npc_path = artifacts / "npc_component.json"
    npc_path.write_text(json.dumps(npc, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    probe = PhysicsPlannedAltarProbe(Dataset.from_manifest(ROOT / "data/manifest.json"))
    probe.step(10000)
    physics_path = artifacts / "altar_physics_contract.json"
    physics_path.write_text(json.dumps(probe.artifact(), ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    report = dict(
        healthy=base["healthy"] and evidence["healthy"],
        tests_run=base["tests_run"], failures=base["failures"], errors=base["errors"], skipped=base["skipped"],
        v8_component_evidence=evidence,
        previous_verification=str(artifacts / "verification_v7.json"),
        npc_component=dict(artifact=str(npc_path),
            hidden_before_signal=npc["hidden_before_signal"],
            damage_signal_snapshot=npc["damage_signal_fixture"]["snapshot"],
            death_signal_snapshot=npc["death_signal_fixture"]["snapshot"],
            external_inputs=npc["damage_signal_fixture"]["external_inputs"]),
        physics_altar=dict(artifact=str(physics_path), snapshot=probe.snapshot(),
            queries=len(probe.physics_records),
            first_query_epoch=probe.physics_records[0]["plans"][0]["epoch"],
            damage_applications=sum(x["applied"] for x in probe.damage_results),
            external_inputs=probe.artifact()["external_inputs"]),
        scope="bounded_NPC_actions_summon_restore_and_epoch_bound_external_Unity_query_compositions",
        battle_ready=False, autonomous_route_ready=False, runtime_battle_validated=False, reward=None)
    path = artifacts / "verification_v8.json"
    path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    print(json.dumps({"healthy":report["healthy"], "tests_run":report["tests_run"],
        "file_pins_checked":evidence["file_pins_checked"],
        "native_selected_entries":evidence["native_selected_entries"],
        "native_ranges_checked":evidence["original_native_ranges_checked"],
        "npc_damage_life":report["npc_component"]["damage_signal_snapshot"]["life"],
        "npc_death_life":report["npc_component"]["death_signal_snapshot"]["life"],
        "physics_altar_recycle_frame":probe.snapshot()["frame"], "report":str(path)},
        ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

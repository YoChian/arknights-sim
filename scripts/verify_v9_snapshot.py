"""Verify immutable older evidence and the selected v9 NPC composition."""
import contextlib
import io
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import verify_v8_snapshot as previous
from arknights_probe.data import read_json, require
from arknights_probe.npc_pipeline import run_npc_pipeline_fixtures
from arknights_probe.v9_validation import verify_v9_evidence


def main():
    artifacts = ROOT / "artifacts"
    console = io.StringIO()
    with contextlib.redirect_stdout(console):
        status = previous.main()
    (artifacts / "verification_v9_previous_console.txt").write_text(console.getvalue(), encoding="utf8")
    require(status == 0, "Previous source/component verification failed")
    base = read_json(artifacts / "verification_v8.json")
    evidence = verify_v9_evidence()
    npc = run_npc_pipeline_fixtures()
    npc_path = artifacts / "npc_pipeline.json"
    npc_path.write_text(json.dumps(npc, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    report = dict(healthy=base["healthy"] and evidence["healthy"],
        tests_run=base["tests_run"], failures=base["failures"], errors=base["errors"], skipped=base["skipped"],
        v9_component_evidence=evidence, previous_verification=str(artifacts / "verification_v8.json"),
        npc_pipeline=dict(artifact=str(npc_path),
            before_reaction=npc["before_reaction"],
            after_reaction=npc["after_reaction"],
            damage_fixture=npc["damage_fixture"]["snapshot"],
            death_before_recycle=npc["death_before_recycle"],
            death_fixture=npc["death_fixture"]["snapshot"],
            external_inputs=npc["damage_fixture"]["external_inputs"]),
        scope="selected_prepared_NPC_factory_buff_membership_damage_reaction_finish_recycle_and_scheduler",
        battle_ready=False, autonomous_route_ready=False, runtime_battle_validated=False, reward=None)
    path = artifacts / "verification_v9.json"
    path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    print(json.dumps(dict(healthy=report["healthy"], tests_run=report["tests_run"],
        file_pins_checked=evidence["file_pins_checked"],
        native_selected_entries=evidence["native_selected_entries"],
        native_ranges_checked=evidence["original_native_ranges_checked"],
        damage_after=npc["after_reaction"], death_after=npc["death_fixture"]["snapshot"],
        report=str(path)), ensure_ascii=False, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

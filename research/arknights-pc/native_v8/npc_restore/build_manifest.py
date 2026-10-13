"""Freeze owned v8 artifacts and exact dependencies without repinning old ones."""
from pathlib import Path
import hashlib,json
OUT=Path(__file__).parent;BASE=OUT.parents[1];ROOT=Path(r'D:\Repo\arknights-sim')
EVIDENCE=ROOT/'evidence/npc_restore'
files=set(p for p in OUT.rglob('*') if p.is_file() and '__pycache__' not in p.parts)
files.update(p for p in EVIDENCE.rglob('*') if p.is_file() and '__pycache__' not in p.parts
             and p.name!='native_manifest.json')
files.update(ROOT/p for p in ['arknights_probe/npc_restore.py','tests/test_npc_restore.py',
    'arknights_probe/fp.py','arknights_probe/frame_runtime.py','arknights_probe/coroutines.py',
    'evidence/v7/manifest.json'])
files.update(BASE/p for p in ['core/pe_inventory.json','core/Assembly-CSharp_candidate_method_map.json',
    'core/DOTween_candidate_method_map.json','native_v3/fixedpoint/inspect_native_types.py',
    'native_v3/fixedpoint/native_types.json','native_v4/resources/export_native_fields.py',
    'native_v4/resources/inspect_attribute_meta.py','native_v4/resources/metadata_blob.py',
    'native_v6/targeting/inspect_generic_identities.py','native_v6/skill/raw_followups.py',
    'native_v6/skill/native_manifest.json','native_v7/npc/manifest.json',
    'native_v7/npc/selection.json','native_v7/npc/results_round2.json','native_v7/npc/results_round3.json',
    'native_v5/core/raw_round5.json','native_v5/core/input_round5.json',
    'native_v5/lifecycle/round2/States_ConstructStateMachine_0x6012b48.c',
    'native_v6/skill/existing/33274_Torappu_StateMachine_Tick.c',
    'native_v6/skill/round3/33275_Torappu_StateMachine_SwitchState.c',
    'native_v6/skill/round3/33284_Torappu_StateMachine__SwitchStateInternal.c',
    'native_v6/skill/round3/33286_Torappu_StateMachine__CheckValidState.c',
    'native_v4/movement/round2/Torappu_Battle_BasicCursor_Reset_0x6011211.c',
    'native_v4/movement/round2/Torappu_Battle_DirectionCursor_Reset_0x6011280.c',
    'native_v4/movement/round2/Torappu_Battle_BasicCursor__CreateCheckpoint_0x6011215.c'])
files.update((BASE/'native_v7/npc/round2').glob('*On*DisappearChanged*.c'))
files.update((BASE/'native_v7/npc/round2').glob('*SetDisappear*.c'))
files.add(BASE/'native_v7/npc/round2/ForceSetToSourcePosition_Execute_0x6017cff.c')
files.update((BASE/'native_v7/npc/round3').glob('*ReassignRoute*.c'))
resources=json.loads((OUT/'resource_inputs.json').read_text())
for item in resources['sources']:
    p=Path(item['path']);assert hashlib.sha256(p.read_bytes()).hexdigest()==item['sha256'];files.add(p)
for prefab in resources['prefabs']:
    item=prefab['source_pin'];p=Path(item['path'])
    assert hashlib.sha256(p.read_bytes()).hexdigest()==item['sha256'];files.add(p)
audit=json.loads((OUT/'source_audit.json').read_text())
reference=json.loads((EVIDENCE/'reference_results.json').read_text())
assert audit['healthy'] and reference['matches']==reference['vector_count']==48
records=[]
for p in sorted(files):
    assert p.is_file(),p
    data=p.read_bytes();records.append({'path':str(p),'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()})
manifest={'format':'native_v8_npc_restore_manifest_v1','target_path':audit['target_path'],
    'target_sha256':audit['target_sha256'],
    'metadata_sha256':'d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f',
    'files':records,'native_ranges':audit['native_ranges'],
    'fresh_selected_entries':16,'fresh_imported_ranges':36,'raw_functions':19,'raw_ranges_verified':39,
    'unit_tests':21,'self_authored_csharp_vectors':48,'client_runtime_compared':False,
    'scope':'explicit nohotfix deterministic Enemy MOVE/DisappearState and prepared empty-CP route restore; Unity/Tween/FSM/Move/Buff providers external'}
path=EVIDENCE/'native_manifest.json';path.write_text(json.dumps(manifest,indent=2))
print(json.dumps({'manifest':str(path),'file_pins':len(records),
    'module_sha256':next(r['sha256'] for r in records if r['path'].endswith('arknights_probe\\npc_restore.py'))}))

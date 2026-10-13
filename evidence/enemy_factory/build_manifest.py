"""Freeze selected factory code, source ranges, resource and reference pins."""
from pathlib import Path
import hashlib,json
HERE=Path(__file__).parent;ROOT=HERE.parents[1]
OUT=Path(r'D:\Repo\.rea-tools\arknights-pc\native_v9\enemy_factory')
BASE=OUT.parents[1]
pins={}
def add(path):
    p=Path(path).resolve()
    if p.is_file():pins[str(p)]={'path':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()}
for directory in [OUT,HERE]:
    for p in directory.rglob('*'):
        if '__pycache__' not in p.parts and p.name not in ['native_manifest.json','validation.json']:add(p)
for p in [ROOT/'arknights_probe/enemy_factory.py',ROOT/'tests/test_enemy_factory.py',
          ROOT/'data/manifest.json',ROOT/'arknights_probe/data.py',ROOT/'arknights_probe/enemy_data.py',
          ROOT/'arknights_probe/fp.py',ROOT/'arknights_probe/lifecycle.py',ROOT/'arknights_probe/npc_actions.py',
          ROOT/'arknights_probe/npc_summon.py',BASE/'core/pe_inventory.json',
          BASE/'native_v4/resources/export_native_fields.py',BASE/'native_v6/skill/raw_followups.py',
          BASE/'native_v8/npc_restore/talent_prefix_constants.json',BASE/'native_v3/fixedpoint/fp_results.json']:
    assert p.exists(),p;add(p)
resource=json.loads((OUT/'resource_inputs.json').read_text(encoding='utf-8'))
for pin in resource['sources']+[resource['script_source_pin']]:
    add(pin['path']);assert pins[pin['path']]['sha256']==pin['sha256']
data=json.loads((ROOT/'data/manifest.json').read_text(encoding='utf-8'))
# Every source referenced by the local dataset is already reviewed/pinned.
def walk(value):
    if isinstance(value,dict):
        if isinstance(value.get('path'),str) and Path(value['path']).is_file():add(value['path'])
        for v in value.values():walk(v)
    elif isinstance(value,list):
        for v in value:walk(v)
walk(data)
fields=json.loads((OUT/'native_fields.json').read_text(encoding='utf-8'))
for key in ['registration_reference_path','helper_source_path']:add(fields[key])
walk(fields['method_map_sources'])
for name in ['reused_results.json','dependency_results.json']:
    for r in json.loads((OUT/name).read_text(encoding='utf-8')):add(r['result_source'])
add(BASE/'native_v9/core/results_round1.json')
add(BASE/'native_v9/core/input_round1.json')
add(BASE/'native_v9/core/raw_round1.json')
target=Path(r'D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll')
metadata=target.parent/'Arknights_Data/il2cpp_data/Metadata/global-metadata.dat'
assert metadata.exists();add(target);add(metadata)
audit=json.loads((OUT/'source_audit.json').read_text(encoding='utf-8'))
reference=json.loads((HERE/'reference_checks.json').read_text(encoding='utf-8'))
assert audit['healthy'] and reference['healthy']
manifest={'schema':'enemy_factory_native_v9_v1','scope':'source-bound staged shdopl/upeopl inputs and selected birth; mandatory Unity/controller/ability/registry/FSM/movement providers',
          'files':list(pins.values()),'native_ranges':audit['native_ranges'],
          'validation':{'unit_tests':16,'cross_language_vectors':reference['cross_language_vectors'],
                        'frame_records':reference['frame_records'],'raw_functions':audit['raw_functions'],
                        'verified_native_ranges':audit['verified_native_ranges'],
                        'fresh_entries':audit['fresh_entries'],'reused_entries':audit['reused_entries'],
                        'client_runtime_compared':False},
          'remaining_external_context':audit['limits'],'client_runtime_compared':False,
          'battle_ready':False,'autonomous_route_ready':False,'runtime_battle_validated':False}
manifest_path=HERE/'native_manifest.json'
manifest_path.write_text(json.dumps(manifest,indent=2),encoding='utf-8')
for p in manifest['files']:assert hashlib.sha256(Path(p['path']).read_bytes()).hexdigest()==p['sha256'],p['path']
(HERE/'validation.json').write_text(json.dumps({'healthy':True,'file_pins':len(pins),
    'native_ranges':len(audit['native_ranges']),'source_audit':audit['healthy'],
    'own_reference_check':reference['healthy'],'client_runtime_compared':False},indent=2),encoding='utf-8')
print(json.dumps({'manifest':str(manifest_path),'file_pins':len(pins),'native_ranges':len(audit['native_ranges']),
                  'module_sha256':pins[str((ROOT/'arknights_probe/enemy_factory.py').resolve())]['sha256'],
                  'tests':16,'vectors':reference['cross_language_vectors'],'frame_records':reference['frame_records']}))

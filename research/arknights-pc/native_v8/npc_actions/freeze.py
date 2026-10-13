from pathlib import Path
import hashlib,json,shutil
OUT=Path(__file__).parent;ROOT=OUT.parents[1]
REPO=Path(r'D:\Repo\arknights-sim');E=REPO/'evidence/npc_actions'
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
shutil.copyfile(OUT/'REPORT.md',E/'REPORT.md')
paths=set()
for root in [OUT,E]:
 for p in root.rglob('*'):
  if p.is_file() and p.name!='manifest.json' and p.suffix in ['.py','.c','.cs','.md','.json','.exe']:
   paths.add(p)
paths.update([REPO/'arknights_probe/npc_actions.py',REPO/'tests/test_npc_actions.py',
 REPO/'arknights_probe/fp.py',REPO/'evidence/fp/native_types.json',REPO/'evidence/fp/native_report.json',
 ROOT/'native_v7/npc/manifest.json',ROOT/'native_v7/npc/raw_dispatch.json',
 ROOT/'native_v7/npc/raw_helpers.json',ROOT/'native_v7/npc/native_fields.json',
 ROOT/'native_v7/npc/identity_proofs.json',ROOT/'native_v7/npc/resource_inputs.json',
 ROOT/'native_v7/npc/results_round2.json',ROOT/'native_v7/npc/results_round3.json',
 ROOT/'native_v8/npc_restore/talent_prefix_constants.json',
 ROOT/'native_v8/core/results_round1.json',ROOT/'native_v8/core/results_round2.json',
 ROOT/'core/pe_inventory.json',ROOT/'core/Assembly-CSharp_candidate_method_map.json',
 ROOT/'core/Torappu.Common_candidate_method_map.json',
 ROOT/'native_v6/damage/results_round2.json'])
for p in paths:assert p.is_file(),p
audit=json.loads((OUT/'audit_summary.json').read_text('utf8'))
manifest={'scope':'bounded_NPC_action_event_component',
 'target_sha256':audit['target_sha256'],'metadata_sha256':audit['metadata_sha256'],
 'tests':28,'independent_csharp_vectors':187,'client_runtime_compared':False,
 'game_launched':False,'complete_npc_simulator':False,'full_buff_container_implemented':False,
 'event10_source':'explicit external ON_TAKE_DAMAGE signal',
 'external_dependencies':audit['external_dependencies'],
 'files':[{'path':str(p.resolve()),'sha256':sha(p)} for p in sorted(paths,key=lambda p:str(p).lower())]}
text=json.dumps(manifest,ensure_ascii=False,indent=2)+'\n'
for p in [OUT/'manifest.json',E/'manifest.json']:p.write_text(text,encoding='utf8')
for p in manifest['files']:assert sha(p['path'])==p['sha256']
print(json.dumps({'files':len(manifest['files']),'manifest_path':str(E/'manifest.json'),
 'manifest_sha256':sha(E/'manifest.json'),'module_sha256':sha(REPO/'arknights_probe/npc_actions.py'),
 'tests_sha256':sha(REPO/'tests/test_npc_actions.py')},indent=2))

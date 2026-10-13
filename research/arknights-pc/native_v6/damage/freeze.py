"""Pin this task's finished evidence and code; do not freeze sibling owners."""
from pathlib import Path
import hashlib,json
OUT = Path(__file__).parent
REPO = Path(r'D:\Repo\arknights-sim')
EVIDENCE = REPO/'evidence/damage'

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

(EVIDENCE/'REPORT.md').write_bytes((OUT/'REPORT.md').read_bytes())
paths = [REPO/'arknights_probe/damage.py', REPO/'tests/test_damage.py']
paths += [x for x in sorted(EVIDENCE.iterdir()) if x.is_file() and x.name != 'manifest.json']
paths += [x for x in sorted(OUT.iterdir()) if x.is_file() and x.suffix in ('.py','.json','.md')
          and x.name != 'manifest.json']
paths += sorted(OUT.glob('prior/*.c')) + sorted(OUT.glob('round1/*.c')) + sorted(OUT.glob('round2/*.c'))
data = {'scope': 'static_default_PURE_NONE_ordinary_damage_component',
        'files': [{'path': str(p), 'sha256': sha(p)} for p in paths],
        'target_sha256': '583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5',
        'metadata_sha256': 'd3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f',
        'reference_cases': 255, 'damage_unit_tests': 15,
        'native_counts': json.loads((OUT/'audit_summary.json').read_text('utf8'))['counts'],
        'supported_target_prefabs': ['enemy_1034_laxe'],
        'supported_source_prefabs': ['trap_011_ore'],
        'source_passive_buff': 'frosts_effect, template empty, explicitly initialized empty action slots',
        'supported_finished_transient_templates': ['ore_s','ore_buff'],
        'unfinished_transient_buff_actions_supported': False,
        'hp_snap_rule': 'signed HP.raw < 42950; equality is nonalive without OnHpZero',
        'supported_death_reason': 2,
        'specific_dead_animation_supported': False,
        'scene_callback_registration_proven': False,
        'npc_box_actions_supported': False, 'complete_scene_supported': False,
        'client_runtime_compared': False, 'game_launched': False,
        'external_dependencies': ['Existing frozen LifecycleRuntime actor/state and pool callback semantics',
                                  'SharedCoroutineSimulator/CoroutineOwner supplied by parent frame runtime',
                                  'Already recovered FP and WaitForFixedSeconds arithmetic',
                                  'Caller closes live object identity, source initialization, dynamic rules and selector context']}
text = json.dumps(data, ensure_ascii=False, indent=2)+'\n'
(OUT/'manifest.json').write_text(text, encoding='utf8')
(EVIDENCE/'manifest.json').write_text(text, encoding='utf8')
assert all(sha(Path(x['path'])) == x['sha256'] for x in data['files'])
print(json.dumps({'pinned_files': len(paths), 'module_sha256': sha(paths[0]), 'tests_sha256': sha(paths[1]),
                  'manifest_sha256': sha(EVIDENCE/'manifest.json')}, ensure_ascii=False))

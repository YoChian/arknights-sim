"""Create the reviewed v9 pins once; retained v8 pins must still match."""
import hashlib
import json
from pathlib import Path

OUT = Path(__file__).resolve().parent
SIM = OUT.parents[1]
BASE = SIM.parent / '.rea-tools' / 'arknights-pc'
NATIVE = BASE / 'native_v9' / 'npc_lifecycle'
DESTINATION = OUT / 'native_evidence.json'


def read(path):
    return json.loads(Path(path).read_text('utf-8'))


def sha(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def main():
    if DESTINATION.exists():
        raise FileExistsError('Fixed lifecycle pins already exist; review changes manually')
    entries = {}

    def add(path, expected=None):
        path = Path(path).resolve()
        actual = sha(path)
        if expected is not None and actual != expected:
            raise ValueError('Retained source changed: ' + str(path))
        if str(path) in entries and entries[str(path)] != actual:
            raise ValueError('Conflicting reviewed source pin: ' + str(path))
        entries[str(path)] = actual

    prior_path = BASE / 'native_v8' / 'npc_actions' / 'manifest.json'
    prior = read(prior_path)
    assert len(prior['files']) == 75
    for entry in prior['files']:
        add(entry['path'], entry['sha256'])
    add(prior_path)

    for path in sorted(NATIVE.iterdir()):
        if path.is_file():
            add(path)
    for name in ('generate_reference_input.py', 'NpcLifecycleReference.cs',
                 'NpcLifecycleReference.exe', 'reference_input.json', 'reference_vectors.json',
                 'reference_comparison.json', 'verify_evidence.py', 'write_manifest_once.py', 'REPORT.md'):
        add(OUT / name)
    for name in ('npc_lifecycle.py', 'fp.py', 'coroutines.py', 'frame_runtime.py',
                 'npc_actions.py', 'lifecycle.py', 'env.py', 'data.py'):
        add(SIM / 'arknights_probe' / name)
    for name in ('test_npc_lifecycle.py', 'test_npc_lifecycle_reference.py'):
        add(SIM / 'tests' / name)

    core = BASE / 'native_v9' / 'core'
    for batch in (1, 2):
        for kind in ('results', 'raw', 'input'):
            add(core / f'{kind}_round{batch}.json')
    for name in ('prepare.py', 'ArknightsFocused.java', 'raw_selected.py'):
        add(core / name)

    fields = read(NATIVE / 'native_fields.json')
    for path_key, hash_key in (('registration_reference_path', 'registration_reference_sha256'),
                              ('helper_source_path', 'helper_source_sha256')):
        add(fields[path_key], fields[hash_key])
    for entry in fields['method_map_sources']:
        add(entry['path'], entry['sha256'])
    helpers = read(NATIVE / 'raw_helpers.json')
    add(helpers['source_helper_path'], helpers['source_helper_sha256'])
    reused = read(NATIVE / 'reused_native.json')
    for entry in reused['decompiled_functions'] + reused['raw_functions']:
        add(entry['source_path'], entry['source_sha256'])

    target_sha = fields['target_sha256']
    target = next(item for item in read(BASE / 'core' / 'pe_inventory.json')
                  if item['path'].endswith('GameAssembly.dll'))
    assert target['sha256'] == target_sha
    add(target['path'], target_sha)
    metadata = Path(target['path']).parent / 'Arknights_Data' / 'il2cpp_data' / 'Metadata' / 'global-metadata.dat'
    add(metadata, fields['metadata_sha256'])

    audit = read(NATIVE / 'source_audit.json')
    comparison = read(OUT / 'reference_comparison.json')
    assert audit['all_original_bytes_match'] and comparison['all_passed']
    counts = {key: value for key, value in audit.items()
              if key not in ('checks', 'limits', 'target_sha256')}
    counts.update({key: value for key, value in comparison.items()
                   if key not in ('scope', 'actual_test_command', 'all_passed',
                                  'runtime_battle_validated', 'battle_ready')})
    counts.update({'retained_v8_pins_preserved': 75,
                   'types': len(fields['types']),
                   'fields': sum(len(item['fields']) for item in fields['types']),
                   'generic_contexts': len(fields['generic_instances'])})
    manifest = {
        'scope': 'selected initialized NPC Finish7/death2; first-reset event6/conditional8; decoded accounting and reference identity',
        'target_sha256': target_sha,
        'metadata_sha256': fields['metadata_sha256'],
        'counts': counts,
        'event_binding_reconstructed': True,
        'backend': 'supplied fresh event pool, constant config, selected direct synchronous callback handlers',
        'reference_scope': comparison['scope'],
        'external_dependencies': [
            'initialized actor/controller/coroutine-owner instance predicates',
            'actual Buff membership via supplied callbacks',
            'animation lookup and specific animation duration receipt',
            'registry, visual, tween and mode phase providers',
            'pool recycle outcome receipt, not Unity engine pool execution',
            'decoded counters and ordered future membership snapshots; not ObscuredInt crypto',
            'full EventPool bootstrap, ordering/reentrancy and repeated-reset deduplication',
            'dynamic damage/HP post-write, scene progression and complete map win request'],
        'native_pool_executed': False,
        'native_animation_executed': False,
        'full_map_win_generated': False,
        'runtime_battle_validated': False,
        'battle_ready': False,
        'game_launched': False,
        'files': [{'path': path, 'sha256': digest} for path, digest in sorted(entries.items())]
    }
    DESTINATION.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n', 'utf-8')
    print(json.dumps({'manifest': str(DESTINATION), 'files': len(entries), 'counts': counts}, indent=2))


if __name__ == '__main__':
    main()

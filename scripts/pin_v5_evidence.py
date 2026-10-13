"""Explicitly pin the reviewed v5 components; never called by verification."""
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NATIVE = Path(r'D:\Repo\.rea-tools\arknights-pc\native_v5')


def main():
    files = [ROOT / 'arknights_probe' / name for name in (
        'runtime_movement.py', 'lifecycle.py', 'devices.py', 'route_runtime.py', 'scene.py')]
    files += [ROOT / 'tests' / name for name in ('test_runtime_movement.py',
        'test_lifecycle.py', 'test_devices.py', 'test_route_runtime.py', 'test_scene.py')]
    files += [ROOT / 'scripts/probe_route_lifecycle.py']
    for folder in ('runtime_movement', 'lifecycle', 'devices'):
        files += [path for path in (ROOT / 'evidence' / folder).glob('*')
                  if path.suffix in ('.json', '.cs', '.md')]
    child_manifests = [ROOT / 'evidence' / name for name in (
        'runtime_movement/native_evidence.json', 'lifecycle/manifest.json',
        'devices/native_manifest.json')]
    for child_file in child_manifests:
        document = json.loads(child_file.read_text(encoding='utf8'))
        for row in document['files']:
            path = Path(row['path'])
            if not path.is_absolute():
                path = child_file.parent / path
            observed = hashlib.sha256(path.read_bytes()).hexdigest()
            if observed != row['sha256']:
                raise ValueError(f'Reviewed child evidence changed: {path}')
            files.append(path.resolve())
    files += [NATIVE / 'resources' / name for name in (
        'rule_prefab_subtrees.json', 'scene_templates.json', 'move_controller_inputs.json')]
    files += [NATIVE / 'core/frame_order_evidence.json']
    batches = []
    for tag, entries in (('round1', 107), ('round2', 69), ('round3', 24)):
        path = NATIVE / 'core' / f'results_{tag}.json'
        files.append(path)
        batches.append({'path': str(path), 'entries': entries})
    pins = [{'path': str(path), 'sha256': hashlib.sha256(path.read_bytes()).hexdigest()}
            for path in sorted(set(files))]
    manifest = {'scope': 'reviewed_v5_component_file_pins', 'client_runtime_compared': False,
                'files': pins, 'native_batches': batches,
                'frame_order_evidence': str(NATIVE / 'core/frame_order_evidence.json')}
    output = ROOT / 'evidence/scene/manifest.json'
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(manifest, indent=2), encoding='utf8')
    print(json.dumps({'manifest': str(output), 'file_pins': len(pins)}))


if __name__ == '__main__':
    main()

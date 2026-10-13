"""Verify explicitly reviewed v5 file pins without refreshing them."""
from pathlib import Path

from .data import read_json, require, sha256

ROOT = Path(__file__).resolve().parents[1]


def verify_v5_evidence():
    manifest = read_json(ROOT / 'evidence/scene/manifest.json')
    checked = []
    for row in manifest['files']:
        path = Path(row['path'])
        observed = sha256(path)
        require(observed == row['sha256'], f'V5 evidence changed: {path}')
        checked.append({'path': str(path), 'sha256': observed})
    # Native imported ranges and independent reference implementations answer
    # different questions. Preserve both checks and their limits.
    frames = read_json(Path(manifest['frame_order_evidence']))
    for row in frames['files']:
        path = Path(row['path'])
        require(sha256(path) == row['sha256'], f'Frame evidence changed: {path}')
    batches = []
    for row in manifest['native_batches']:
        document = read_json(Path(row['path']))
        functions = document['functions']
        require(len(functions) == row['entries'], 'V5 native batch size changed')
        require(all(f['decompile_completed'] and f['imported_memory_matches_source']
                    for f in functions), 'Incomplete native imported/decompiled evidence')
        require(all(r['match'] for f in functions for r in f['imported_range_checks']),
                'Native imported source range mismatch')
        batches.append({'entries': len(functions),
                        'ranges': sum(len(f['ranges']) for f in functions)})
    return {'healthy': True, 'scope': 'v5_reviewed_static_component_evidence',
            'file_pins_checked': len(checked), 'frame_source_pins_checked': len(frames['files']),
            'native_batches': batches, 'native_selected_entries': sum(r['entries'] for r in batches),
            'native_imported_ranges': sum(r['ranges'] for r in batches),
            'client_runtime_compared': False, 'full_scene_ready': False}

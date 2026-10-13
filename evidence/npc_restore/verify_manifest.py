"""Read-only owned snapshot verification; no C# recompilation after freezing."""
from pathlib import Path
import hashlib,json
path=Path(__file__).resolve().parent/'native_manifest.json'
manifest=json.loads(path.read_text())
for item in manifest['files']:
    p=Path(item['path']);assert p.is_file(),p
    assert hashlib.sha256(p.read_bytes()).hexdigest()==item['sha256'],p
target=Path(manifest['target_path'])
assert hashlib.sha256(target.read_bytes()).hexdigest()==manifest['target_sha256']
with target.open('rb') as source:
    for span in manifest['native_ranges']:
        source.seek(span['source_file_offset'])
        count=int(span['end_exclusive'],16)-int(span['start'],16)
        assert hashlib.sha256(source.read(count)).hexdigest()==span['source_sha256'],span['start']
print(json.dumps({'healthy':True,'file_pins':len(manifest['files']),
    'original_native_ranges':len(manifest['native_ranges']),
    'unit_tests':manifest['unit_tests'], 'self_authored_csharp_vectors':manifest['self_authored_csharp_vectors'],
    'client_runtime_compared':False}))

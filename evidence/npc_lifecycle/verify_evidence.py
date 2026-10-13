"""Verify fixed, reviewed lifecycle pins without replacing them."""
import hashlib
import json
from pathlib import Path

def verify(root=None):
    root=root or Path(__file__).resolve().parent
    manifest=json.loads((root/'native_evidence.json').read_text('utf-8'))
    for entry in manifest['files']:
        path=Path(entry['path'])
        if not path.is_absolute():raise ValueError('Absolute source pin required')
        with path.open('rb') as stream:actual=hashlib.file_digest(stream,'sha256').hexdigest()
        if actual!=entry['sha256']:raise ValueError('Changed lifecycle pin requires review: '+str(path))
    return {'scope':manifest['scope'],'files_verified':len(manifest['files']),
        'counts':manifest['counts'],'runtime_battle_validated':False,'battle_ready':False}

if __name__=='__main__':print(json.dumps(verify(),ensure_ascii=False,indent=2))

"""Disassemble exact selected PE ranges without loading or executing the game."""
from pathlib import Path
import hashlib
import json
import sys

HERE = Path(__file__).resolve().parent
namespace = {'__file__': str(HERE / 'prepare.py')}
prefix = (HERE / 'prepare.py').read_text(encoding='utf8').split('selection=json.loads')[0]
exec(compile(prefix, str(HERE / 'prepare.py'), 'exec'), namespace)
tag = sys.argv[1]
if not tag.startswith('round') or not tag[5:].isdigit():
    raise ValueError('Expected round number')
payload = json.loads((HERE / f'input_{tag}.json').read_text(encoding='utf8'))
blob, base, rva, engine = [namespace[name] for name in ('b', 'base', 'rva', 'engine')]
result = []
for target in payload['targets']:
    parts = []
    for source in target['ranges']:
        start, end = int(source['start'], 16), int(source['end'], 16) + 1
        offset = rva(start - base, end - start)
        data = blob[offset:offset + end - start]
        assert hashlib.sha256(data).hexdigest() == source['source_sha256']
        instructions = [{'address': hex(i.address), 'bytes': i.bytes.hex(),
                         'mnemonic': i.mnemonic, 'operands': i.op_str}
                        for i in engine.disasm(data, start)]
        decoded = sum(len(bytes.fromhex(i['bytes'])) for i in instructions)
        # An unwind span can also contain embedded table/alignment bytes.
        # Preserve a decoder stop instead of labeling those bytes instructions.
        parts.append({**source, 'instructions': instructions, 'decoded_bytes': decoded,
                      'range_bytes': len(data), 'fully_decoded': decoded == len(data),
                      'undecoded_tail_hex': data[decoded:].hex()})
    result.append({'display_name': target['display_name'], 'address': target['address'], 'ranges': parts})
path = HERE / f'raw_{tag}.json'
path.write_text(json.dumps(result, indent=2), encoding='utf8')
print(json.dumps({'functions': len(result), 'path': str(path)}))

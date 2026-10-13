"""Verify owned preparation pins and exact original byte ranges; read only."""
from pathlib import Path
import hashlib,json
OUT=Path(__file__).parent;m=json.loads((OUT/'native_manifest.json').read_text())
for row in m['files']:
 assert hashlib.sha256(Path(row['path']).read_bytes()).hexdigest()==row['sha256'],row['path']
p=Path(m['target_path']);assert hashlib.sha256(p.read_bytes()).hexdigest()==m['target_sha256']
with p.open('rb') as source:
 for row in m['native_ranges']:
  source.seek(row['source_file_offset']);size=int(row['end_exclusive'],16)-int(row['start'],16)
  assert hashlib.sha256(source.read(size)).hexdigest()==row['source_sha256'],row['start']
report={'healthy':True,'files':len(m['files']),'selected_entries':len(m['native_selected_entries']),'original_ranges':len(m['native_ranges']),'client_runtime_compared':False}
(OUT/'verification.json').write_text(json.dumps(report,indent=2),encoding='utf-8');print(json.dumps(report))

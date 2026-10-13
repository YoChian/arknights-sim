from pathlib import Path
import urllib.request,json,hashlib,zipfile
OUT=Path(__file__).parent
def fetch(url):
 req=urllib.request.Request(url,headers={'User-Agent':'Codex-offline-resource-audit'})
 with urllib.request.urlopen(req,timeout=60) as f:return f.read()
sha=json.loads(fetch('https://api.github.com/repos/MooncellWiki/OpenArknightsFBS/commits/main'))['sha']
schema_dir=OUT/'schemas';schema_dir.mkdir(exist_ok=True)
record={'schema_repository':'MooncellWiki/OpenArknightsFBS','schema_commit':sha,'schemas':[]}
for name in ['prts___levels','enemy_database','character_table','skill_table','roguelike_topic_table','resource_manifest','gamedata_const','level_script_table']:
 url=f'https://raw.githubusercontent.com/MooncellWiki/OpenArknightsFBS/{sha}/FBS/{name}.fbs'
 b=fetch(url);path=schema_dir/(name+'.fbs');path.write_bytes(b)
 record['schemas'].append({'path':str(path),'url':url,'sha256':hashlib.sha256(b).hexdigest(),'bytes':len(b)})
release=json.loads(fetch('https://api.github.com/repos/google/flatbuffers/releases/latest'))
record['flatc_release']=release['tag_name']
candidates=[a for a in release['assets'] if 'Windows' in a['name'] and 'flatc' in a['name']]
if not candidates:raise ValueError('No official Windows flatc asset found')
asset=next((a for a in candidates if '64' in a['name']),candidates[0])
blob=fetch(asset['browser_download_url']);actual=hashlib.sha256(blob).hexdigest()
if asset.get('digest') and asset['digest']!='sha256:'+actual:raise ValueError('release asset digest mismatch')
tool_dir=OUT/'tools';tool_dir.mkdir(exist_ok=True)
zip_path=tool_dir/asset['name'];zip_path.write_bytes(blob)
record['flatc_asset']={'name':asset['name'],'url':asset['browser_download_url'],'sha256':actual,'bytes':len(blob),'release_digest':asset.get('digest')}
with zipfile.ZipFile(zip_path) as z:
 names=[n for n in z.namelist() if Path(n).name=='flatc.exe']
 if len(names)!=1:raise ValueError('flatc.exe identity not unique')
 (tool_dir/'flatc.exe').write_bytes(z.read(names[0]))
(OUT/'download_provenance.json').write_text(json.dumps(record,ensure_ascii=False,indent=2),'utf-8')
print(json.dumps(record,ensure_ascii=False))

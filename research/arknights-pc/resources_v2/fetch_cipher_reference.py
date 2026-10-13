from pathlib import Path
import urllib.request,json,hashlib
OUT=Path(__file__).parent
def get(url):
 with urllib.request.urlopen(urllib.request.Request(url,headers={'User-Agent':'Codex-offline-resource-audit'}),timeout=45) as r:return r.read()
commit=json.loads(get('https://api.github.com/repos/djpadbit/Arknights-RE/commits/master'))['sha'];url=f'https://raw.githubusercontent.com/djpadbit/Arknights-RE/{commit}/pyknights/converter.py';b=get(url)
(OUT/'tools'/'author_resource_converter.py').write_bytes(b)
provenance={'repository':'djpadbit/Arknights-RE','commit':commit,'url':url,'sha256':hashlib.sha256(b).hexdigest(),'bytes':len(b),'usage':'Parse only the published CrypticConverterA and SignConverter literal constants with ast; never execute this module.'}
(OUT/'cipher_reference_provenance.json').write_text(json.dumps(provenance,ensure_ascii=False,indent=2),'utf-8');print(json.dumps(provenance))

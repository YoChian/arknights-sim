"""Read-only probes using the two explicitly published resource tokens.
Reference: djpadbit/Arknights-RE/pyknights/converter.py (asset decoder only).
No game services, account protocols, or target execution are involved.
"""
from pathlib import Path
import json,hashlib,struct
from cryptography.hazmat.primitives import hashes,serialization,padding
from cryptography.hazmat.primitives.asymmetric import padding as rsa_padding
from cryptography.hazmat.primitives.ciphers import Cipher,algorithms,modes
OUT=Path(__file__).parent
import ast
reference_tree=ast.parse((OUT/'tools'/'author_resource_converter.py').read_text('utf-8'))
published={}
for cls in reference_tree.body:
 if isinstance(cls,ast.ClassDef) and cls.name in ['CrypticConverterA','SignConverter']:
  for assignment in cls.body:
   if isinstance(assignment,ast.Assign):
    for target in assignment.targets:
     if isinstance(target,ast.Name) and target.id in ['TOKEN','OLD_TOKEN','PUBLIC_KEY']:
      published[target.id]=ast.literal_eval(assignment.value)
PUB=published['PUBLIC_KEY'].encode('ascii')
TOKENS={'author_current':published['TOKEN'],'author_old':published['OLD_TOKEN']}
key=serialization.load_pem_public_key(PUB)
sig=[]
for r in json.loads((OUT/'sample_provenance.json').read_text('utf-8')):
 b=(OUT/'samples'/(r['text_asset_name']+'.signed.bytes')).read_bytes()
 try:key.verify(b[:128],b[128:],rsa_padding.PKCS1v15(),hashes.MD5());ok=True
 except Exception:ok=False
 sig.append({'name':r['text_asset_name'],'published_rsa_signature_verified':ok})
probes=[]
inputs=json.loads((OUT/'cipher_sample_provenance.json').read_text('utf-8'))

for r in inputs:
 raw=Path(r['path']).read_bytes()
 try:key.verify(raw[:128],raw[128:],rsa_padding.PKCS1v15(),hashes.MD5());ok=True
 except Exception:ok=False
 sig.append({'name':r['name'],'published_rsa_signature_verified':ok})
 for prefix in [128,0]:
  b=raw[prefix:]
  if len(b)<32 or (len(b)-16)%16:continue
  for token_name,token in TOKENS.items():
   rec={'name':r['name'],'prefix_bytes':prefix,'published_token':token_name}
   try:
    iv=bytes(x^y for x,y in zip(token[16:],b[:16]));dec=Cipher(algorithms.AES(token[:16]),modes.CBC(iv)).decryptor();plain=dec.update(b[16:])+dec.finalize();unpad=padding.PKCS7(128).unpadder();plain=unpad.update(plain)+unpad.finalize();rec['valid_pkcs7']=True
    text=None
    try:text=plain.decode('utf-8');rec['utf8']=True
    except UnicodeDecodeError:rec['utf8']=False
    if text is not None:
     try:j=json.loads(text);rec['json_type']=type(j).__name__;rec['json_keys']=list(j)[:30] if isinstance(j,dict) else None
     except ValueError:pass
    flat=False
    if len(plain)>=12:
     root=struct.unpack_from('<I',plain,0)[0]
     if 4<=root<=len(plain)-4:
      vt=root-struct.unpack_from('<i',plain,root)[0]
      if 0<=vt<=len(plain)-4:
       vl,sz=struct.unpack_from('<HH',plain,vt);flat=vl>=4 and vl%2==0 and vt+vl<=len(plain) and sz>=4 and root+sz<=len(plain)
    rec['valid_flatbuffer_root_bounds']=flat
    if text is not None or flat:
     path=OUT/'samples'/(r['name']+'.published-decoded.bin');path.write_bytes(plain);rec['output_path']=str(path);rec['output_bytes']=len(plain);rec['sha256']=hashlib.sha256(plain).hexdigest();rec['preview']=text[:120] if text else plain[:32].hex()
   except Exception as ex:rec['error']=str(ex)
   probes.append(rec)
(OUT/'published_cipher_probe.json').write_text(json.dumps({'reference':json.loads((OUT/'cipher_reference_provenance.json').read_text('utf-8')),'signature_checks':sig,'cipher_probes':probes},ensure_ascii=False,indent=2),'utf-8');print(json.dumps({'signature_checks':sig,'cipher_probes':probes},ensure_ascii=False))

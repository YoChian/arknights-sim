from pathlib import Path
OUT=Path(__file__).parent
path=OUT/'probe_published_resource_cipher.py'
text=path.read_text('utf-8')
text='\n'.join(line for line in text.split('\n') if not line.startswith(('PUB=','TOKENS=')))
insert='''import ast
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
'''
text=text.replace('key=serialization.load_pem_public_key(PUB)',insert+'key=serialization.load_pem_public_key(PUB)')
text=text.replace("inputs.append({'name':'resource_index','path':r'D:\\Hypergryph Launcher\\games\\Arknights\\Arknights_Data\\StreamingAssets\\AB\\Windows\\074c396967a291d157f01a3e40c79119.idx'})",'')
text=text.replace(" raw=Path(r['path']).read_bytes()",''' raw=Path(r['path']).read_bytes()
 try:key.verify(raw[:128],raw[128:],rsa_padding.PKCS1v15(),hashes.MD5());ok=True
 except Exception:ok=False
 sig.append({'name':r['name'],'published_rsa_signature_verified':ok})''')
text=text.replace("'reference':'https://github.com/djpadbit/Arknights-RE/blob/master/pyknights/converter.py'", "'reference':json.loads((OUT/'cipher_reference_provenance.json').read_text('utf-8'))")
path.write_text(text,'utf-8')
print('Probe now parses published constants from pinned source; no literal token values in probe or output.')

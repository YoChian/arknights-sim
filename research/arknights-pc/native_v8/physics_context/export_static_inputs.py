"""Verified enum defaults and serialized initial physics settings, no runtime."""
from pathlib import Path
import hashlib
import json
import sys

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
SOURCE=BASE/'native_v4/resources/inspect_attribute_meta.py'
sys.path.insert(0,str(SOURCE.parent))
ns={'__file__':str(SOURCE)}
exec(SOURCE.read_text('utf-8').split('selected=[]')[0],ns)
types,fields,text,fullname,native_type=[ns[k] for k in ('types','fields','text','fullname','native_type')]
rows=[]
for tid in (50477,50480):
    t=types[tid];entries=[]
    for fi in range(t[8],t[8]+t[19]):
        if native_type(fields[fi][1])['attrs']&64:
            entries.append({'name':text(fields[fi][0]),'field_index':fi,'default':ns['decode_default'](fi)})
    rows.append({'type_definition_index':tid,'name':fullname(tid),'entries':entries})
inventory=json.loads((OUT/'engine_inventory.json').read_text('utf-8'))
settings=next(x for x in inventory['serialized_settings'] if x['type']=='Physics2DSettings')
output={'metadata_sha256':hashlib.sha256(ns['meta']).hexdigest(),'decoder_source_path':str(SOURCE),
    'decoder_source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'enum_constants':rows,
    'settings_source_pin':inventory['settings_source_pin'],'Physics2DSettings':settings,
    'native_results_buffer_capacity':128,
    'native_results_buffer_origin':'Box2dPhysicsUtil.cctor0x1809a6990 allocates Collider2D[0x80]',
    'legacy_filter_constructor':{'useTriggers':'Physics2D.get_queriesHitTriggers()',
        'useLayerMask':True,'useDepth':True,'useOutsideDepth':False,
        'useNormalAngle':False,'useOutsideNormalAngle':False,
        'minDepth_bits':'0xff800000','maxDepth_bits':'0x7f800000',
        'followup':'ContactFilter2D.CheckConsistency_Injected; final engine outcome not reconstructed'},
    'engine_file_version':'2021.3.39.0','engine_product_version':'2021.3.39f1 (0)',
    'engine_version_origin':'Win32 VERSIONINFO read via PowerShell FileInfo.VersionInfo, not engine execution',
    'limits':['Enum literals and asset initial values; not live simulation mode, trigger setting or auto-sync state.',
        'ContactFilter declaration precedes an unresolved engine CheckConsistency call; no default final filter is invented.']}
(OUT/'static_inputs.json').write_text(json.dumps(output,indent=2),'utf-8')
print(json.dumps({r['name']:{e['name']:e['default']['value'] for e in r['entries']} for r in rows}))

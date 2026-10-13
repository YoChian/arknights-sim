"""Bounded read-only PE/string inventory; not an engine implementation claim."""
from pathlib import Path
import hashlib
import json
import struct
import sys

OUT=Path(__file__).resolve().parent
BASE=OUT.parents[1]
sys.path.insert(0,str(BASE/'resources_v2'))
from ark_bundle import load

GAME=Path(r'D:\Hypergryph Launcher\games\Arknights')


def pin(path):
    return {'path':str(path),'bytes':path.stat().st_size,'sha256':hashlib.sha256(path.read_bytes()).hexdigest()}


def inventory(path):
    blob=path.read_bytes();pe=struct.unpack_from('<I',blob,0x3c)[0]
    assert blob[:2]==b'MZ' and blob[pe:pe+4]==b'PE\0\0'
    machine,count,stamp,_,_,optional_size,characteristics=struct.unpack_from('<HHIIIHH',blob,pe+4)
    optional=pe+24;magic=struct.unpack_from('<H',blob,optional)[0];assert magic==0x20b
    image_base=struct.unpack_from('<Q',blob,optional+24)[0]
    sections=[]
    for i in range(count):
        off=optional+optional_size+i*40
        name=blob[off:off+8].split(b'\0')[0].decode('ascii')
        virtual_size,rva,size,fileoff=struct.unpack_from('<4I',blob,off+8)
        sections.append({'name':name,'rva':hex(rva),'virtual_size':virtual_size,'file_offset':fileoff,'raw_size':size})
    def va(off):
        matches=[s for s in sections if s['file_offset']<=off<s['file_offset']+s['raw_size']]
        return hex(image_base+int(matches[0]['rva'],16)+off-matches[0]['file_offset']) if matches else None
    records=[];seen=set()
    needles=[b'UnityEngine.Physics2D::',b'UnityEngine.PhysicsScene2D::',b'UnityEngine.Collider2D::',
             b'UnityEngine.CircleCollider2D::',b'UnityEngine.Rigidbody2D::',b'UnityEngine.Transform::',b'SyncTransforms']
    for needle in needles:
        start=0
        while True:
            offset=blob.find(needle,start)
            if offset<0:break
            start=offset+1
            begin=offset
            if needle==b'SyncTransforms':
                while begin>0 and offset-begin<128 and 32<=blob[begin-1]<127:begin-=1
            end=blob.find(b'\0',offset,min(len(blob),offset+512))
            if end<0:continue
            raw=blob[begin:end]
            if any(x<32 or x>126 for x in raw) or begin in seen:continue
            seen.add(begin)
            text=raw.decode('ascii')
            if needle==b'UnityEngine.Transform::' and not any(x in text for x in ('position','Position','lossyScale','Matrix','rotation','Rotation')):continue
            records.append({'file_offset':begin,'va':va(begin),'text':text,'raw_sha256':hashlib.sha256(raw).hexdigest()})
    return {'source_pin':pin(path),'machine':hex(machine),'image_base':hex(image_base),
            'pe_timestamp':stamp,'characteristics':hex(characteristics),'sections':sections,
            'bounded_physics_strings':records,
            'limits':['Exact strings are inventory evidence, not proof of registration, resolved target address or a call being executed.','No whole-engine decompilation or target execution.']}


def run():
    source=GAME/'Arknights_Data'/'globalgamemanagers'
    env=load(source)
    settings=[{'path_id':o.path_id,'type':o.type.name,
               'serialized_sha256':hashlib.sha256(o.get_raw_data()).hexdigest(),'fields':o.read_typetree()}
              for o in env.objects if o.type.name in ('Physics2DSettings','PhysicsManager','TimeManager')]
    output={'engine':inventory(GAME/'UnityPlayer.dll'),'game_assembly':inventory(GAME/'GameAssembly.dll'),
            'settings_source_pin':pin(source),'serialized_settings':settings,
            'limits':['Settings are shipped initial asset values; runtime setters/hotfixes can change them.','Serialized physics layer matrix is not an overlap algorithm or live engine observation.']}
    (OUT/'engine_inventory.json').write_text(json.dumps(output,indent=2),'utf-8')
    print(json.dumps({'engine_sha256':output['engine']['source_pin']['sha256'],
                     'engine_physics_strings':len(output['engine']['bounded_physics_strings']),
                     'game_physics_strings':len(output['game_assembly']['bounded_physics_strings']),
                     'sync_strings':[(r['va'],r['text']) for carrier in ['engine','game_assembly'] for r in output[carrier]['bounded_physics_strings'] if 'SyncTransforms' in r['text']],
                     'settings_types':[(x['type'],x['path_id']) for x in settings]},indent=2))


if __name__=='__main__':run()

"""Read-only adapter for the sampled Arknights PC compression-code-4 blocks.

Unlike standard LZ4: low token nibble encodes literals, high encodes matches,
and the two-byte match offset is big endian. All source/output bounds are
checked and the declared uncompressed length must match exactly.
No game file, dependency module, or global configuration is modified.
"""
from pathlib import Path
import sys
TOOLS=Path(__file__).resolve().parent.parent/'tools'/'python'
sys.path.insert(0,str(TOOLS))
import UnityPy
from UnityPy.helpers import CompressionHelper
STATS={'blocks':0,'compressed_bytes':0,'uncompressed_bytes':0}

class DecodeError(ValueError):pass

def decode_code4(data, uncompressed_size):
    src=memoryview(data); i=0; dst=bytearray()
    if not 0<=uncompressed_size<=64*1024*1024:
        raise DecodeError('invalid or excessive declared block size')
    def length(base):
        nonlocal i
        n=base
        if base==15:
            while True:
                if i>=len(src):raise DecodeError('truncated extended length')
                v=src[i];i+=1;n+=v
                if n>uncompressed_size:raise DecodeError('extended length exceeds declared output')
                if v!=255:break
        return n
    while i<len(src):
        token=src[i];i+=1
        literals=length(token&15)
        if literals>len(src)-i:raise DecodeError('literal reads past input')
        if literals>uncompressed_size-len(dst):raise DecodeError('literal writes past output')
        dst.extend(src[i:i+literals]);i+=literals
        if i==len(src):break
        if len(src)-i<2:raise DecodeError('truncated match offset')
        offset=(src[i]<<8)|src[i+1];i+=2
        if not 1<=offset<=len(dst):raise DecodeError('invalid or out-of-history match offset')
        match=length(token>>4)+4
        if match>uncompressed_size-len(dst):raise DecodeError('match writes past output')
        period=bytes(dst[-offset:])
        dst.extend((period*((match+offset-1)//offset))[:match])
    if i!=len(src) or len(dst)!=uncompressed_size:
        raise DecodeError(f'length mismatch input={i}/{len(src)} output={len(dst)}/{uncompressed_size}')
    STATS['blocks']+=1;STATS['compressed_bytes']+=len(src);STATS['uncompressed_bytes']+=len(dst)
    return bytes(dst)

def load(path):
    CompressionHelper.DECOMPRESSION_MAP[4]=decode_code4
    return UnityPy.load(str(path))

def text_bytes(obj):
    value=obj.m_Script
    return value.encode('utf-8',errors='surrogateescape') if isinstance(value,str) else bytes(value)

if __name__=='__main__':
    import json,collections,hashlib
    records=[]
    for arg in sys.argv[1:]:
        p=Path(arg);e=load(p)
        r={'path':str(p),'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'object_types':dict(collections.Counter(o.type.name for o in e.objects)),'containers':list(e.container),'assets':[]}
        for o in e.objects:
            if o.type.name=='TextAsset':
                d=o.read();b=text_bytes(d)
                r['assets'].append({'path_id':o.path_id,'name':d.m_Name,'bytes':len(b),'header':b[:32].hex(),'preview':b[:250].decode('utf-8',errors='replace')})
        records.append(r)
    print(json.dumps(records,ensure_ascii=False,indent=2))

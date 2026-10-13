"""Original prefix literal and StringComparison enum for NPC BB binding."""
from pathlib import Path
import json,struct,sys,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v4/resources/inspect_attribute_meta.py';sys.path.insert(0,str(source.parent));ns={'__file__':str(source)}
exec(source.read_text().split('selected=[];enemy_fields=[]')[0],ns)
native=ns['ns'];b,meta,offset,tables=[native[k] for k in ['b','meta','offset','tables']]
owner=next(i for i in range(len(ns['types'])) if ns['fullname'](i)=='System.StringComparison');t=ns['types'][owner];values=[]
for index in range(t[8],t[8]+t[19]):
 f=ns['fields'][index]
 if ns['native_type'](f[1])['attrs']&64:values.append({'name':ns['text'](f[0]),'field_index':index,'literal':ns['decode_default'](index)})
slot=0x1887fb958;off=offset(slot,8);encoded=struct.unpack_from('<Q',b,off)[0];assert encoded>>29==5
index=(encoded&0x1fffffff)>>1;start,size=tables['string_literals'];assert index*8+8<=size
length,data_index=struct.unpack_from('<II',meta,start+index*8);data,size=tables['string_literal_data'];assert data_index+length<=size
raw=meta[data+data_index:data+data_index+length]
out={'target_sha256':native['registration']['target_sha256'],'metadata_sha256':hashlib.sha256(meta).hexdigest(),'string_comparison':{'owner':'System.StringComparison','definition_index':owner,'constants':values},'talent_prefix':{'slot_va':hex(slot),'slot_file_offset':off,'raw_bytes8':b[off:off+8].hex(),'usage_kind':5,'string_literal_index':index,'literal_record_file_offset':start+index*8,'literal_data_file_offset':data+data_index,'bytes':raw.hex(),'value':raw.decode('utf-8')},'limits':'Only metadata enum constants and original encoded literal; no runtime String.Format or StartsWith called.'}
(OUT/'talent_prefix_constants.json').write_text(json.dumps(out,indent=2),encoding='utf-8');print([(r['name'],r['literal']['value']) for r in values],out['talent_prefix']['value'])

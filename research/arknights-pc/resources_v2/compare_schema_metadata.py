from pathlib import Path
import csv,json,struct,hashlib
from verify_and_normalize import schema
OUT=Path(__file__).parent
BASE=OUT.parent
META=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\il2cpp_data\Metadata\global-metadata.dat')
b=META.read_bytes()
names='string_literals string_literal_data strings events properties methods parameter_defaults field_defaults default_data marshaled_fields parameters fields generic_parameters generic_constraints generic_containers nested_types interfaces vtable_methods interface_offsets type_definitions images assemblies'.split()
header={name:struct.unpack_from('<II',b,8+i*8) for i,name in enumerate(names)}
so,sl=header['strings'];fo,fl=header['fields'];to,tl=header['type_definitions'];no,nl=header['nested_types']
assert fl%12==0 and tl%92==0
def text(i):
 assert 0<=i<sl
 p=so+i;q=b.find(b'\0',p,so+sl);assert q>=p
 return b[p:q].decode('utf-8')
types=[]
for i in range(tl//92):
 x=struct.unpack_from('<IIiiiiii9i8HII',b,to+i*92);fs=x[8];fc=x[19]
 fields=[text(struct.unpack_from('<I',b,fo+12*j)[0]) for j in range(fs,fs+fc)] if fc else []
 ns=text(x[1]);name=text(x[0]);full=ns+'.'+name if ns else name
 nested=[struct.unpack_from('<i',b,no+4*j)[0] for j in range(x[12],x[12]+x[21])] if x[21] else []
 types.append({'index':i,'name':name,'namespace':ns,'full_name':full,'fields':fields,'nested_indices':nested})
for t in types:
 for j in t['nested_indices']:
  types[j]['parent']=t['full_name']
  types[j]['nested_full_name']=t['full_name']+'.'+types[j]['name']
mapping={'clz_Torappu_LevelData':'Torappu.LevelData','clz_Torappu_LevelData_Options':'Torappu.LevelData.Options','clz_Torappu_MapData':'Torappu.MapData','clz_Torappu_TileData':'Torappu.TileData','clz_Torappu_RouteData':'Torappu.RouteData','clz_Torappu_LevelData_WaveData_FragmentData_ActionData':'Torappu.LevelData.WaveData.FragmentData.ActionData','clz_Torappu_Resource_ResourceManifest':'Torappu.Resource.ResourceManifest','clz_Torappu_RoguelikeTopicTable':'Torappu.RoguelikeTopicTable','clz_Torappu_CharacterData':'Torappu.CharacterData'}
# Rebuild arbitrarily deep nested names from validated nested index links.
parents={j:t['index'] for t in types for j in t['nested_indices']}
def fullname(i):
 t=types[i];return fullname(parents[i])+'.'+t['name'] if i in parents else t['full_name']
byfull={fullname(t['index']):t for t in types}
tables={}
for p in (OUT/'schemas').glob('*.fbs'):
 ts,_,_=schema(p);tables.update(ts)
rows=[]
for schema_name,meta_name in mapping.items():
 t=byfull.get(meta_name);expected=[n for n,_ in tables[schema_name]];r={'schema_type':schema_name,'metadata_type':meta_name,'schema_fields':expected}
 if t:
  observed=t['fields'];r.update(metadata_index=t['index'],metadata_fields=observed,exact_field_order_match=expected==observed,all_schema_names_present=all(n in observed for n in expected),metadata_only_fields=[n for n in observed if n not in expected],schema_only_fields=[n for n in expected if n not in observed])
  filtered=[n for n in observed if n in expected];r['schema_field_order_is_metadata_subsequence']=filtered==expected
 else:r['missing_metadata_type']=True
 rows.append(r)
result={'metadata_path':str(META),'metadata_sha256':hashlib.sha256(b).hexdigest(),'metadata_version':struct.unpack_from('<I',b,4)[0],'type_row_size':92,'source_layout_validation':'Shared prior core inspection validated declaration links; this pass reads the same nonstandard 92-byte records and declared nested type index links.','comparisons':rows,'limitations':'Names/order comparison does not prove runtime defaults, ignored-field attributes, accessor offsets, enum values, or battle behavior.'}
(OUT/'schema_metadata_comparison.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),'utf-8')
print(json.dumps(result,ensure_ascii=False)[:14000])

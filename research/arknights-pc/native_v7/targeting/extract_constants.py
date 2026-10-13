"""Source-bound Layers strings, ALL delegate and typed defaults; no runtime."""
from pathlib import Path
import hashlib,json,struct

OUT=Path(__file__).parent;BASE=OUT.parents[1]
HELPER=OUT/'export_native_fields.py';ns={'__file__':str(HELPER)}
exec(HELPER.read_text('utf-8').split('roots=')[0],ns)
b,meta,offset=ns['b'],ns['meta'],ns['offset']


def slot(address):
    o=offset(address,8);v=struct.unpack_from('<Q',b,o)[0]
    return {'slot_va':hex(address),'slot_file_offset':o,'raw8':b[o:o+8].hex(),
            'kind':v>>29,'index':(v&0x1fffffff)>>1}


string_start,string_size=ns['tables']['string_literals']
string_data,_=ns['tables']['string_literal_data']
layer_slots=[('ALLY',0x188821d30),('ENEMY',0x188931568),('NEUTRAL',0x1888d2b10)]
strings=[]
for expected,address in layer_slots:
    r=slot(address);assert r['kind']==5
    off=string_start+r['index']*8
    length,data_index=struct.unpack_from('<Ii',meta,off)
    raw=meta[string_data+data_index:string_data+data_index+length]
    value=raw.decode('utf-8');assert value==expected
    r.update(value=value,string_literal_record_file_offset=off,
        record_raw8=meta[off:off+8].hex(),string_data_file_offset=string_data+data_index,
        string_raw=raw.hex())
    strings.append(r)
all_delegate=slot(0x1889053a8);assert all_delegate['kind']==3
method=ns['methods'][all_delegate['index']]
all_delegate.update(metadata_method_index=all_delegate['index'],declaring_type=ns['fullname'](method[1]),
    method_name=ns['text'](method[0]),token=hex(method[5]))
assert all_delegate['metadata_method_index']==74639
tag_path=BASE/'native_v7/skill_preparation/tag_manager_inputs.json'
tag=json.loads(tag_path.read_text('utf-8'))
layers=tag['TagManager'][0]['serialized']['layers'];assert len(layers)==32
derived={s['value']:layers.index(s['value']) for s in strings}
output={'target_sha256':hashlib.sha256(b).hexdigest(),'metadata_sha256':hashlib.sha256(meta).hexdigest(),
    'layer_initializer_va':'0x1805e15a0','layer_string_records':strings,
    'tag_manager_path':str(tag_path),'tag_manager_sha256':hashlib.sha256(tag_path.read_bytes()).hexdigest(),
    'layer_indices':derived,'layer_masks':{n:1<<v for n,v in derived.items()},
    'side_same_masks':[1,2,4],'side_opposite_masks':[2,5,2],
    'side_cctor_va':'0x180b06970','side_raw_note':'OPPOSITE_SIDES store is at180b06b6a; decompiler erroneously marked tail PIC branch unreachable.',
    'side_match_helper_va':'0x186727990',
    'side_match_rule':'(1 << slot) == sourceSide; no bit-membership test. Same falls back to sourceSide and opposite to 0 for composite sides.',
    'ALL_delegate':all_delegate,
    'default_small_enough_gap_raw':4294967,'small_gap_origin':'FP.EN3 initialized by native One/1000 division, FilterUtil copies static+68',
    'big_enough_gap_int':1000000,'big_gap_origin':'WeightedTarget canonical cctor185528350 stores0xf4240 atstatic+8',
    'fp_equality_epsilon_raw':42950,'epsilon_origin':'MathUtil.cctor1866e6e50 copiesFP.EN5/static+78 toMathUtil static0',
    'source_purpose_mask':0,'purpose_origin':'TargetSelector.get_sourcePurposeMask1809fc980 normalnohotfixreturn0, independentofAbilityStandard purpose',
    'ability_can_select_camouflage':False,'scope':'Serialized/native static initial values, not proof of live hotfix/NameToLayer/global overrides'}
(OUT/'constants.json').write_text(json.dumps(output,indent=2),'utf-8')
print(json.dumps({'layers':derived,'masks':output['layer_masks'],'ALL':all_delegate['method_name']},indent=2))

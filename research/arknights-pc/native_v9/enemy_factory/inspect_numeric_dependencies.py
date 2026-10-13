"""Pin BORN's two different comparisons and exact original field offsets."""
from pathlib import Path
import hashlib,json,struct
OUT=Path(__file__).parent;BASE=OUT.parents[1]
source=BASE/'native_v6/skill/raw_followups.py';ns={'__file__':str(source)}
exec(source.read_text(encoding='utf-8').split('engine=capstone.')[0],ns)
b,base,rva=[ns[k] for k in ['b','base','rva']]
addr=0x186e3fd88;off=rva(addr-base,4);epsilon=struct.unpack_from('<f',b,off)[0]
assert b[off:off+4].hex()=='acc52737'
raw=json.loads((OUT/'raw_helpers.json').read_text(encoding='utf-8'))
fields=json.loads((OUT/'native_fields.json').read_text(encoding='utf-8'))
lookup={t['name']:t for t in fields['types']}
observed={}
for owner,names in {
    'Torappu.Battle.BObject':['<instanceUid>k__BackingField','<inited>k__BackingField','<borned>k__BackingField','<isDisappeared>k__BackingField'],
    'Torappu.Battle.Enemy':['_delayToBorn','_onlyDelayToBornOnTileStart','_idleWhenBorn','_alwaysCheckCurrentPoint'],
    'Torappu.Battle.BasicTalent':['_overwriteTalentKey'],
}.items():
    observed[owner]=[{k:f[k] for k in ['name','offset','offset_hex','native_type']} for f in lookup[owner]['fields'] if f['name'] in names]
le=next(f for f in raw['functions'] if f['address']=='0x185ed91e0')
gt=next(f for f in raw['functions'] if f['address']=='0x1866e4c50')
out={'target_sha256':ns['pe']['sha256'],'metadata_sha256':fields['metadata_sha256'],
     'birth_enter_single_gt':{'function':gt,'operation':'COMISS(a, binary32(b+epsilon)); SETA',
        'epsilon':{'address':hex(addr),'source_file_offset':off,'raw_bytes':b[off:off+4].hex(),'value':epsilon,'source_sha256':hashlib.sha256(b[off:off+4]).hexdigest()}},
     'birth_tick_fp_le':{'function':le,'operation':'signed Int64 comparison: remaining <= FP.from_int32(0), no EN5 epsilon'},
     'selected_fields':observed,
     'notes':['BObject +0x24 is inited, +0x25 borned, +0x26 isDisappeared.',
              'Enemy.Options.unharmful is a separate value-struct Boolean; MarkUnharmful does not change disappearance or HP.',
              'Enemy delay getter default flagfalse reads Single+0x310 only under explicit null hotfix slots.',
              'BasicTalent.get_talentKey virtual slot19 is the exact Enemy._AssignTalent 0x13 dispatch; no Talent override.']}
(OUT/'numeric_dependencies.json').write_text(json.dumps(out,indent=2),encoding='utf-8')
print(json.dumps({'epsilon':epsilon,'comparison':'signed <=0','fields':observed}))

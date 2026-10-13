"""Read immutable metadata associations and reuse prior native evidence."""
from pathlib import Path
import hashlib,json
OUT=Path(__file__).parent
ROOT=OUT.parents[1]
source=ROOT/'native_v4/resources/export_native_fields.py'
ns={'__file__':str(source)}
exec(compile(source.read_text('utf8').split('roots={')[0],str(source),'exec'),ns)
candidate=json.loads((ROOT/'core/Assembly-CSharp_candidate_method_map.json').read_text('utf8'))
by_index={x['metadata_method_index']:x for x in candidate}
wanted={'Torappu.Battle.Entity','Torappu.Battle.Enemy','Torappu.Battle.Enemy.States.DyingState',
        'Torappu.Battle.Enemy.States.DeadState','Torappu.Battle.BattleFormula',
        'Torappu.Battle.BuffContainer','Torappu.Battle.Modifier',
        'Torappu.Battle.DefaultGameMode','Torappu.Battle.Entity.SpController'}
definitions=[]
for di,t in enumerate(ns['types']):
 name=ns['fullname'](di)
 if name not in wanted:continue
 methods=[]
 for mi in range(t[9],t[9]+t[17]):
  m=ns['methods'][mi]
  methods.append({'metadata_method_index':mi,'method':ns['text'](m[0]),'owner':name,
                  'token':hex(m[5]),'virtual_slot':m[8],
                  'candidate':by_index.get(mi)})
 definitions.append({'name':name,'definition_index':di,'methods':methods})
result={'target_sha256':hashlib.sha256(ns['b']).hexdigest(),
        'metadata_sha256':hashlib.sha256(ns['meta']).hexdigest(),'definitions':definitions}
(OUT/'method_inventory.json').write_text(json.dumps(result,indent=2),encoding='utf8')
for d in definitions:
 if '.States.' in d['name']:
  print(d['name'],d['definition_index'])
  for m in d['methods']:print(m['method'],m['metadata_method_index'],m['candidate']['candidate_va'] if m['candidate'] else None)
# Prior Ghidra imports retain exact source-range hashes and aliases.
existing=[]
for round in (1,2,3):
 d=json.loads((ROOT/f'native_v5/core/results_round{round}.json').read_text('utf8'))
 for f in d['functions']:
  if any(x in f['display_name'].lower() for x in ('damage','modifier','hp','entity.ontick','enemy.finishme','enemy.ontick')):
   existing.append({'round':round,**f})
(OUT/'prior_native_results.json').write_text(json.dumps({'target_sha256':result['target_sha256'],'functions':existing},indent=2),encoding='utf8')
code=OUT/'prior'
code.mkdir(exist_ok=True)
for f in existing:
 (code/(f['name']+'.c')).write_text('\n'.join(x for x in f['pseudocode'].splitlines() if x.strip())+'\n',encoding='utf8')
print('prior entries',len(existing))

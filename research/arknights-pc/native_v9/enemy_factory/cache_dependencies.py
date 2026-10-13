"""Reuse recovered dependency C, selecting complete chain-range records."""
from pathlib import Path
import json
OUT=Path(__file__).parent;BASE=OUT.parents[1]
want={0x180974190:'BasicTalent.get_talentKey',0x180a884c0:'BornState.OnEnter',
      0x180a88620:'BornState.OnExit',0x180a887a0:'BornState.OnTick',
      0x180621070:'BattleController.CreateEnemy_route'}
found={}
for path in BASE.glob('native_v*/**/results*.json'):
    if 'enemy_factory' in path.parts:continue
    try:data=json.loads(path.read_text(encoding='utf-8'))
    except (ValueError,UnicodeError):continue
    if not isinstance(data,dict):continue
    for r in data.get('functions',[]):
        address=int(r['address'],16)
        if address in want and r.get('decompile_completed') and r.get('imported_memory_matches_source'):
            if address not in found or len(r['ranges'])>len(found[address]['result']['ranges']):
                found[address]={'address':r['address'],'name':want[address],'result_source':str(path),'result':r}
out=[]
for address,name in want.items():
    if address not in found:
        print('not already recovered:',hex(address),name);continue
    row=found[address];c=OUT/'dependencies'/f'{hex(address)}_{name.replace(".","_")}.c'
    c.parent.mkdir(exist_ok=True);c.write_text(row['result']['pseudocode'],encoding='utf-8')
    row['c_file']=str(c);out.append(row)
(OUT/'dependency_results.json').write_text(json.dumps(out,indent=2),encoding='utf-8')
print([(r['name'],r['address'],len(r['result']['ranges'])) for r in out])

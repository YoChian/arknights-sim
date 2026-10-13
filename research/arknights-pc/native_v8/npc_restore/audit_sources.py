"""Verify fresh native groups and save explicit observations/limits."""
from pathlib import Path
import json,hashlib
OUT=Path(__file__).parent;BASE=OUT.parents[1]
target=Path(r'D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll')
b=target.read_bytes();sha=hashlib.sha256(b).hexdigest()
raw=json.loads((OUT/'raw_helpers.json').read_text());assert raw['target_sha256']==sha
ranges=[]
for f in raw['functions']:
    for r in f['ranges']:
        count=int(r['end_exclusive'],16)-int(r['start'],16);offset=r['source_file_offset']
        assert hashlib.sha256(b[offset:offset+count]).hexdigest()==r['source_sha256']
        ranges.append({'address':f['address'],**{k:r[k] for k in ['start','end_exclusive','source_file_offset','source_sha256']}})
records=json.loads((OUT/'results_round1.json').read_text())
for e in records:
    r=e['result'];assert r['decompile_completed'] and r['imported_memory_matches_source']
    assert all(c['match'] for c in r['imported_range_checks'])
    matches={x['start']:x for x in ranges if x['address']==r['address']}
    for span in r['ranges']:
        other=matches[span['start']]
        assert int(span['end'],16)+1==int(other['end_exclusive'],16)
        assert span['source_sha256']==other['source_sha256']
observations=[
 {'claim':'state11 exact nested owner, not another DisappearState', 'source':'selection.json + native_fields.json + state_enum.json'},
 {'claim':'OnEnter default path constructs iterator, primes deterministic coroutine and stores id after AddModifier',
  'source':'raw_helpers.json 180a8d030 spans, esp 180a8d146..180a8d1cb',
  'decompiler_limit':'Ghidra warns PIC at 180a8d16e and incorrectly drops default tail; raw instructions resolve this. A completed decompile alone is insufficient.'},
 {'claim':'Hide/appear two 0.15f segments use Append, not Join; wait calls Single overload with .3f',
  'source':'76795/76781 C + dependency_identities.json'},
 {'claim':'Clear flag only faces + event23; state11 next Tick requests DEFAULT0; no tween/wait completion gate',
  'source':'v7 Enemy.OnDisappearChanged + 76779 + v6 StateMachine._SwitchStateInternal'},
 {'claim':'OnExit stops/invalidate coroutine, removes modifier, activates root GO, starts appearance; one-shot flag resets false',
  'source':'76778/76781/76782 C; original byte ranges pinned'},
 {'claim':'ForceSet uses source currentGridPosition, not continuous world or initial spawn point',
  'source':'v7 ForceSetToSourcePosition.Execute'},
 {'claim':'Route flags sticky OR; CP list rebuilt then Reset, host progress raw Int32 overwritten afterward; no copied wait',
  'source':'70159/70269 C + v7 Enemy.ReassignRoute + v4 BasicCursor/DirectionCursor Reset'},
 {'claim':'DisableCurrentStillPull clears disabled ListSet then copies current pull ListSet, does not kill pulls',
  'source':'76436 C'},
 {'claim':'Entity before-change sends event30 and dispatches Buff hooks; these are explicit providers',
  'source':'v7 Entity.OnBeforeDisappearChanged'},
 {'claim':'UID0 SetDisappeared setter no-op, existing SetDisappear action still returns success; Unity-null separate from alive',
  'source':'v7 BObject.SetDisappeared / SetDisappear.Execute / ForceSetToSourcePosition.Execute'}]
out={'healthy':True,'target_path':str(target),'target_sha256':sha,
     'fresh_selected_entries':len(records),'fresh_imported_ranges':sum(len(e['result']['ranges']) for e in records),
     'raw_functions':len(raw['functions']),'raw_ranges_verified':len(ranges),
     'observations':observations,'native_ranges':ranges,'client_runtime_compared':False}
(OUT/'source_audit.json').write_text(json.dumps(out,indent=2))
print(json.dumps({k:out[k] for k in ['healthy','fresh_selected_entries','fresh_imported_ranges','raw_functions','raw_ranges_verified']}))

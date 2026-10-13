from pathlib import Path
import json,struct,re,hashlib,sys
ROOT=Path(__file__).resolve().parents[2]
OUT=Path(__file__).parent
sys.path.insert(0,str(ROOT/'tools/python'))
import capstone
engine=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64)
rows=[]
for image in ['Assembly-CSharp','Torappu.Common','ThirdPartyAssembly','mscorlib']:
 rows.extend(json.loads((ROOT/'core'/f'{image}_candidate_method_map.json').read_text(encoding='utf8')))
pe=next(x for x in json.loads((ROOT/'core/pe_inventory.json').read_text(encoding='utf8')) if x['path'].endswith('GameAssembly.dll'))
b=Path(pe['path']).read_bytes()
assert hashlib.sha256(b).hexdigest()==pe['sha256']
base=int(pe['image_base'],16)
def rva(r,n):
 for s in pe['sections']:
  d=r-int(s['virtual_address'],16)
  if 0<=d and d+n<=s['raw_bytes']:return s['raw_offset']+d
 raise ValueError('not file backed')
off=struct.unpack_from('<I',b,0x3c)[0]
er,ez=struct.unpack_from('<II',b,off+24+112+3*8)
eo=rva(er,ez)
triples=[struct.unpack_from('<III',b,eo+i*12) for i in range(ez//12)]
by_start={t[0]:t for t in triples}
parents={}
for t in triples:
 o=rva(t[2],4);flags=b[o]>>3;count=b[o+2]
 if flags&4:
  parent=struct.unpack_from('<III',b,o+4+((count+1)//2)*4)
  assert parent[0] in by_start and by_start[parent[0]]==parent,(t,parent)
  parents[t[0]]=parent[0]
def root(start):
 seen=set()
 while start in parents:
  assert start not in seen
  seen.add(start);start=parents[start]
 return start
groups={}
for t in triples:groups.setdefault(root(t[0]),[]).append(t)
selection=json.loads((OUT/'selection.json').read_text(encoding='utf8'))
targets=[]
label_map=dict(line.split('\t',1) for line in (ROOT/'native_v2/labels.tsv').read_text(encoding='utf8').splitlines())
seed_labels={}
for s in selection:
 matches=[r for r in rows if (r['type'],r['method'])==(s['type'],s['method'])]
 if s.get('metadata_method_index') is not None:
  # The old candidate map gives nested types their short name. A separately
  # recovered declaring parent may supply a qualified label, but the exact
  # method index, token and pointer must still agree with the original map.
  matches=[r for r in rows if r['metadata_method_index']==s['metadata_method_index']
           and r['method']==s['method'] and ('token' not in s or r['token']==s['token'])]
 if s.get('raw_call_target'):
  address=int(s['address'],16)
  matches=[dict(type=s['type'],method=s['method'],token='call_target',candidate_va=s['address'],candidate_file_offset=rva(address-base,1),metadata_method_index=None)]
 if 'address' in s:matches=[r for r in matches if r['candidate_va']==s['address']]
 assert matches, s
 for row in matches:
  assert row['candidate_va'],row
  start=int(row['candidate_va'],16)-base
  if start in groups:
   pieces=groups[start]
   ranges=[{'start':hex(base+t[0]),'end':hex(base+t[1]-1),'unwind_rva':hex(t[2]),'chained':t[0] in parents} for t in pieces]
   provenance='All exact recursive UNW_FLAG_CHAININFO sibling ranges, not an assumed contiguous span'
  else:
   # A RET later in a byte stream does not make an interior instruction a
   # function entry. Reject candidates inside an existing unwind body.
   assert not any(t[0] < start < t[1] for t in triples), ('interior unwind address is not an entry',row)
   offset=rva(start,512);end=None;terminal=False;straight=True
   for ins in engine.disasm(b[offset:offset+512],base+start):
    if ins.mnemonic=='int3':
     end=ins.address-base;break
    if ins.mnemonic in ('ret','jmp') and straight:
     end=ins.address+ins.size-base;terminal=True;break
    if ins.mnemonic=='call' or ins.mnemonic.startswith('j'):straight=False
    if ins.mnemonic in ('ret','jmp'):terminal=True
   assert end is not None and end>start and terminal,('unbounded leaf',row)
   next_entry=min((int(x['candidate_va'],16)-base for x in rows if x['candidate_va'] and int(x['candidate_va'],16)-base>start),default=None)
   assert next_entry is None or end<=next_entry,('leaf crosses other candidate',row)
   pieces=[(start,end,0)]
   ranges=[{'start':hex(base+start),'end':hex(base+end-1),'leaf_boundary':'straight-line RET/tail JMP or decoded INT3 alignment with RET/JMP; does not cross next metadata candidate'}]
   provenance='Bounded leaf candidate ending at straight-line RET/tail JMP or decoded INT3 padding; separate from PE unwind-derived coverage'
  for rr,(begin,end,_) in zip(ranges,pieces):
   rr['source_sha256']=hashlib.sha256(b[rva(begin,end-begin):rva(begin,end-begin)+end-begin]).hexdigest()
   rr['source_file_offset']=rva(begin,end-begin)
  for begin,end,_ in pieces:
   offset=rva(begin,end-begin)
   for ins in engine.disasm(b[offset:offset+end-begin],base+begin):
    if ins.mnemonic in ('call','jmp') and ins.op_str in label_map:seed_labels[ins.op_str]=label_map[ins.op_str]
  targets.append(dict(name=re.sub('[^A-Za-z0-9_]','_',s['type']+'_'+row['method']+'_'+row['token']),
     display_name=s['type']+'.'+row['method'],candidate_map_type=row['type'],address=row['candidate_va'],end_address=hex(base+max(t[1] for t in pieces)-1),
     ranges=ranges,range_provenance=provenance,
     file_offset=row['candidate_file_offset'],token=row['token'],metadata_method_index=row['metadata_method_index']))
input={'target_sha256':pe['sha256'],'image_base':pe['image_base'],'targets':targets,
 'seed_labels':seed_labels,
 'labels_path':str(ROOT/'native_v2/labels.tsv'),
 'provenance':'Local metadata/native pointer-table candidate names; each entry corroborated by exact PE unwind start. Static analysis, no game execution.'}
(OUT/'input.json').write_text(json.dumps(input,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps({'selected_entries':len(targets),'input':str(OUT/'input.json')}))

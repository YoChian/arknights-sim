"""Verify every reachable FlatBuffer field with pinned schema and normalize maps.

This supports the table/enum/scalar/string/vector schema subset actually used
by the eight downloaded files. It rejects unknown schema constructs, bounds,
invalid booleans/UTF-8, and reports any populated fields absent from schema.
It verifies structural compatibility, not correctness of field names.
"""
from pathlib import Path
import re,json,struct,collections,math,subprocess
OUT=Path(__file__).parent
SCALARS={'bool':('B',1),'byte':('b',1),'ubyte':('B',1),'short':('h',2),'ushort':('H',2),'int':('i',4),'uint':('I',4),'long':('q',8),'ulong':('Q',8),'float':('f',4),'double':('d',8),'int8':('b',1),'uint8':('B',1),'int16':('h',2),'uint16':('H',2),'int32':('i',4),'uint32':('I',4),'int64':('q',8),'uint64':('Q',8)}

def schema(path):
 text=re.sub(r'//[^\n]*|/\*.*?\*/','',path.read_text('utf-8'),flags=re.S)
 if re.search(r'\b(struct|union|include)\b',text):raise ValueError('unsupported schema construct')
 tables={name:re.findall(r'(\w+)\s*:\s*(\[\w+\]|\w+)',body) for name,body in re.findall(r'\btable\s+(\w+)\s*\{(.*?)\}',text,re.S)}
 enums={name:base for name,base in re.findall(r'\benum\s+(\w+)\s*:\s*(\w+)',text)}
 root=re.search(r'root_type\s+(\w+)',text).group(1)
 return tables,enums,root

class Verifier:
 def __init__(self,b,tables,enums):self.b=b;self.tables=tables;self.enums=enums;self.seen=set();self.counts=collections.Counter();self.unknown=[]
 def bounds(self,p,n):
  if not 0<=p<=len(self.b) or not 0<=n<=len(self.b)-p:raise ValueError(f'out of bounds {p}+{n}/{len(self.b)}')
 def unpack(self,f,p):n=struct.calcsize('<'+f);self.bounds(p,n);return struct.unpack_from('<'+f,self.b,p)[0]
 def relative(self,p):
  n=self.unpack('I',p)
  if n<4:raise ValueError('invalid relative offset')
  q=p+n;self.bounds(q,4);return q
 def scalar(self,typ,p):
  f,n=SCALARS[self.enums.get(typ,typ)];v=self.unpack(f,p)
  if typ=='bool' and v not in [0,1]:raise ValueError('invalid bool')
  if isinstance(v,float) and not math.isfinite(v):raise ValueError('nonfinite scalar')
  self.counts['scalar']+=1
 def value(self,typ,p,depth):
  if typ.startswith('['):
   inner=typ[1:-1];q=self.relative(p);n=self.unpack('I',q);q+=4
   stride=SCALARS[self.enums.get(inner,inner)][1] if inner in SCALARS or inner in self.enums else 4
   self.bounds(q,n*stride);self.counts['vector']+=1
   for i in range(n):self.value(inner,q+i*stride,depth+1)
  elif typ=='string':
   q=self.relative(p);n=self.unpack('I',q);self.bounds(q+4,n+1)
   if self.b[q+4+n]!=0:raise ValueError('string not NUL terminated')
   self.b[q+4:q+4+n].decode('utf-8');self.counts['string']+=1
  elif typ in SCALARS or typ in self.enums:self.scalar(typ,p)
  elif typ in self.tables:self.table(typ,self.relative(p),depth+1)
  else:raise ValueError(f'unknown type {typ}')
 def table(self,typ,p,depth=0):
  if depth>128:raise ValueError('excessive recursion')
  if (typ,p) in self.seen:return
  self.seen.add((typ,p));vt=p-self.unpack('i',p);vlen=self.unpack('H',vt);size=self.unpack('H',vt+2)
  if vlen<4 or vlen%2 or size<4:raise ValueError('invalid table header')
  self.bounds(vt,vlen);self.bounds(p,size);fields=self.tables[typ];self.counts['table']+=1
  for i in range((vlen-4)//2):
   off=self.unpack('H',vt+4+2*i)
   if off==0:continue
   if not 4<=off<size:raise ValueError('field offset outside table')
   if i>=len(fields):self.unknown.append({'type':typ,'table_offset':p,'slot':i});continue
   name,ft=fields[i];width=SCALARS[self.enums.get(ft,ft)][1] if ft in SCALARS or ft in self.enums else 4
   if off+width>size:raise ValueError('field payload extends outside table')
   self.value(ft,p+off,depth+1)
 def run(self,root):self.table(root,self.unpack('I',0));return {'counts':dict(self.counts),'populated_unknown_fields':len(self.unknown),'unknown_sample':self.unknown[:20]}

def normalize(value,typ,tables):
 if value is None:return None
 if typ.startswith('['):
  inner=typ[1:-1];vals=[normalize(v,inner,tables) for v in value]
  if inner.startswith(('dict__','kvp__')):
   key=next(k for k,_ in tables[inner] if k.lower()=='key');val=next(k for k,_ in tables[inner] if k.lower()=='value')
   if len({str(v[key]) for v in vals})!=len(vals):raise ValueError('duplicate dictionary key')
   return {str(v[key]):v[val] for v in vals}
  return vals
 if typ in tables:
  fs=dict(tables[typ]);return {k:normalize(v,fs[k],tables) for k,v in value.items()}
 return value

def main():
 conversions=json.loads((OUT/'flatc_conversion.json').read_text('utf-8'));results=[]
 dest=OUT/'normalized';dest.mkdir(exist_ok=True)
 for c in conversions:
  if c['exit_code']!=0:continue
  b=(OUT/'samples'/(c['name']+'.flat.bin')).read_bytes();ts,es,root=schema(OUT/'schemas'/(c['schema']+'.fbs'))
  v=Verifier(b,ts,es).run(root)
  if v['populated_unknown_fields']:raise ValueError('schema misses populated fields: '+json.dumps(v))
  d=json.loads(Path(c['json_path']).read_text('utf-8'));n=normalize(d,root,ts)
  path=dest/(c['name']+'.json');path.write_text(json.dumps(n,ensure_ascii=False,indent=2),'utf-8')
  r={'name':c['name'],'root_type':root,'structural_verification':v,'normalized_path':str(path),'schema_semantics':'community-derived field names; structural compatibility verified; metadata comparison and runtime semantics remain separate'}
  results.append(r);print(json.dumps(r,ensure_ascii=False),flush=True)
 (OUT/'verification.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),'utf-8')

if __name__=='__main__':main()

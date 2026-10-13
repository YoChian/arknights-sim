from pathlib import Path
import json,subprocess,hashlib
OUT=Path(__file__).parent;E=Path(r'D:\Repo\arknights-sim\evidence\npc_actions')
cases=[]
def add(kind,**kwargs):cases.append(dict(id=len(cases),kind=kind,**kwargs))
for i in range(-32,33):add('floor',value=i/8)
for v in [-2147483648,2147483520,-1.0000001,-.000000001,1.0000001,16777215.1]:add('floor',value=v)
def wrap(v):return ((v+(1<<63))%(1<<64))-(1<<63)
for right in [-(1<<63),-(1<<63)+42950,-(1<<32),0,1<<32,(1<<63)-1]:
 for delta in [-42951,-42950,-42949,0,1]:add('ge',left=wrap(right+delta),right=right)
for condition in [-1,0,1,2,3]:
 for previous in [False,True]:add('condition',condition=condition,previous=previous)
for current in [0,1,0xffffffff]:
 for saved in [0,1,0xffffffff]:
  for exists in [False,True]:
   for alive in [False,True]:
    for null in [False,True]:add('uid',current=current,saved=saved,exists=exists,alive=alive,null=null)
for prefix in ['Dead','dead','dEaD','SUMMON']:
 rows=[dict(key='dead.value',value=-1,text=None),dict(key='DEAD.other',value=1.9,text=None),
       dict(key='dead.value',value=3,text=None),dict(key='deadly.value',value=100,text='excluded'),
       dict(key='summon.enemy_key',value=7,text='enemy_3001_upeopl'),dict(key='dead.TEXT',value=9,text='x')]
 add('bind',prefix=prefix,rows=rows)
inp=OUT/'reference_inputs.json';inp.write_text(json.dumps({'cases':cases},indent=2),encoding='utf8')
source=E/'NativeNpcActionsReference.cs';exe=OUT/'NativeNpcActionsReference.exe'
compiler=Path(r'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe')
r=subprocess.run([str(compiler),'/nologo','/reference:System.Web.Extensions.dll','/out:'+str(exe),str(source)],text=True,capture_output=True)
assert r.returncode==0,(r.stdout,r.stderr)
r=subprocess.run([str(exe),str(inp)],text=True,capture_output=True,encoding='utf8',errors='replace');assert r.returncode==0,(r.stdout,r.stderr)
result=json.loads(r.stdout);assert len(result['results'])==len(cases)
vectors={'reference_kind':result['reference_kind'],'game_code_loaded':False,
 'vectors':[{'input':a,'expected':b} for a,b in zip(cases,result['results'])]}
(E/'reference_vectors.json').write_text(json.dumps(vectors,indent=2)+'\n',encoding='utf8')
summary={'vectors':len(cases),'game_code_loaded':False,'compile_return_code':0,'run_return_code':0,
 'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
 'vectors_sha256':hashlib.sha256((E/'reference_vectors.json').read_bytes()).hexdigest()}
(E/'reference_comparison.json').write_text(json.dumps(summary,indent=2)+'\n',encoding='utf8')
print(summary)

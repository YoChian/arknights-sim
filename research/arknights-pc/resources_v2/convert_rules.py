from pathlib import Path
import subprocess,json
OUT=Path(__file__).parent
pairs={'enemy_databasea5b667':'enemy_database','character_table9fc534':'character_table','skill_tableafb859':'skill_table','roguelike_topic_tablebd71d3':'roguelike_topic_table','gamedata_const61fefd':'gamedata_const','level_script_table91d938':'level_script_table','level_rogue6_1-1':'prts___levels','resource_index':'resource_manifest'}
records=[]
for name,schema in pairs.items():
 cmd=[str(OUT/'tools'/'flatc.exe'),'--json','--raw-binary','--strict-json','--natural-utf8','--defaults-json','--no-warnings','-o',str(OUT/'decoded'),str(OUT/'schemas'/(schema+'.fbs')),'--',str(OUT/'samples'/(name+'.flat.bin'))]
 r=subprocess.run(cmd,capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=90)
 path=OUT/'decoded'/(name+'.flat.json')
 rec={'name':name,'schema':schema,'command':cmd,'exit_code':r.returncode,'stdout':r.stdout,'stderr':r.stderr,'json_path':str(path),'json_bytes':path.stat().st_size if path.exists() else None}
 if r.returncode==0:
  d=json.loads(path.read_text('utf-8'));rec['json_keys']=list(d)
 records.append(rec);print(json.dumps(rec,ensure_ascii=False),flush=True)
(OUT/'flatc_conversion.json').write_text(json.dumps(records,ensure_ascii=False,indent=2),'utf-8')

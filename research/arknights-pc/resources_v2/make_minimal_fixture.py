from pathlib import Path
import json,hashlib,collections
OUT=Path(__file__).parent
def read(name):return json.loads((OUT/'normalized'/(name+'.json')).read_text('utf-8'))
level=read('level_rogue6_1-1');db=read('enemy_databasea5b667')['enemies'];chars=read('character_table9fc534')['characters'];skills=read('skill_tableafb859')['skills'];rogue=read('roguelike_topic_tablebd71d3')
enemy_ids=[r['id'] for r in level['enemyDbRefs']]
assert all(k in db for k in enemy_ids)
selected_chars=['char_208_melan','char_123_fang','char_124_kroos','char_212_ansel']
assert all(k in chars for k in selected_chars)
skill_ids=sorted({s['skillId'] for k in selected_chars for s in chars[k]['skills'] if s.get('skillId')})
assert all(k in skills for k in skill_ids)
topic=rogue['details']['rogue_6'];stage={k:v for k,v in topic['stages'].items() if v['levelId'].lower().endswith('/level_rogue6_1-1')}
def defined(x):
 if isinstance(x,dict):
  if 'm_defined' in x:
   if not x['m_defined']:return None
   return defined(x.get('m_value'))
  return {k:d for k,v in x.items() if (d:=defined(v)) is not None}
 if isinstance(x,list):return [defined(v) for v in x]
 return x
fixture={'format':'local_resource_fixture_v1','level_asset':'level_rogue6_1-1','stage_records':stage,'level':level,'enemy_database_records':{k:db[k] for k in enemy_ids},'enemy_defined_values_preview':{k:[{'level':v['level'],'enemyData':defined(v['enemyData'])} for v in db[k]] for k in enemy_ids},'characters':{k:chars[k] for k in selected_chars},'skills':{k:skills[k] for k in skill_ids},'limitations':['This is a local data fixture, not a battle simulator or exact runtime reconstruction.','m_defined=false database fields must inherit defaults or a lower level; preview omits them rather than treating serialized placeholders as real values.','Random groups, hiddenGroup, branches, predefines and stage/rune selection affect the actual spawn count.','Skill scripts, combat ordering, shrine/trap effects, stats interpolation, targeting and path semantics require native/runtime corroboration.'],'source_provenance':json.loads((OUT/'sample_provenance.json').read_text('utf-8')),'schema_provenance':json.loads((OUT/'download_provenance.json').read_text('utf-8'))}
path=OUT/'minimal_fixture.json';path.write_text(json.dumps(fixture,ensure_ascii=False,indent=2),'utf-8')
grid=level['mapData']['map'];rows=grid['row_size'];cols=grid['column_size'];matrix=grid['matrix_data'];tiles=level['mapData']['tiles']
assert len(matrix)==rows*cols
assert all(0<=x<len(tiles) for x in matrix)
glyph={'tile_forbidden':'#','tile_road':'.','tile_wall':'W','tile_start':'S','tile_end':'E','tile_floor':'F','tile_hole':'O'}
render=[''.join(glyph.get(tiles[matrix[r*cols+c]]['tileKey'],'?') for c in range(cols)) for r in range(rows)]
actions=[a for w in level['waves'] for f in w['fragments'] for a in f['actions']]
summary={'fixture_path':str(path),'fixture_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'map_stage_names':[{'id':k,'name':v['name'],'difficulty':v['difficulty']} for k,v in stage.items()],'rows':rows,'cols':cols,'tile_count':len(tiles),'matrix_index_bounds_valid':True,'ascii_grid_row_order_as_stored':render,'glyph_legend':glyph,'options':level['options'],'randomSeed':level['randomSeed'],'routes':len(level['routes']),'waves':len(level['waves']),'fragments':sum(len(w['fragments']) for w in level['waves']),'actions_by_type':dict(collections.Counter(a['actionType'] for a in actions)),'raw_spawn_action_count_sum':sum(a['count'] for a in actions if a['actionType']=='SPAWN'),'raw_spawn_count_note':'not actual battle enemy count until random/hidden/branch controls are applied','enemy_ids':enemy_ids,'enemy_db_references_resolved':True,'character_samples':[{k:chars[c][k] for k in ['name','profession','subProfessionId']}|{'id':c} for c in selected_chars],'skill_ids':skill_ids,'table_counts':{'enemy_database':len(db),'characters':len(chars),'skills':len(skills),'rogue_topics':len(rogue['topics'])},'rogue6_rule_counts':{k:len(topic[k]) for k in ['stages','zones','difficulties','init','relics','choices','choiceScenes','recruitTickets']},'rogue6_name':rogue['topics']['rogue_6']['name'],'first_init_sample':topic['init'][0]}
(OUT/'fixture_summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),'utf-8')
print(json.dumps(summary,ensure_ascii=False))

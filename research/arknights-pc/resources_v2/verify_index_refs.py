from pathlib import Path
import json,collections
OUT=Path(__file__).parent
INDEX=json.loads((OUT/'normalized'/'resource_index.json').read_text('utf-8'))
manifest_path=Path(r'D:\Hypergryph Launcher\games\Arknights\Arknights_Data\StreamingAssets\AB\Windows\hot_update_list.json')
manifest=json.loads(manifest_path.read_text('utf-8'));entries={e['name']:e for e in manifest['abInfos']}
bundles=INDEX['bundles'];assets=INDEX['assetToBundleList'];inv=json.loads((OUT/'anon_inventory.json').read_text('utf-8'))
assert all(b['name'] in entries for b in bundles)
assert len({b['name'] for b in bundles})==len(bundles)
assert all(0<=a['bundleIndex']<len(bundles) for a in assets)
assert all(all(0<=i<len(bundles) for i in b['allDependencies']) for b in bundles)
byname={b['name']:i for i,b in enumerate(bundles)}
bypath={}
for a in assets:
 if a.get('path'):bypath.setdefault(a['path'].lower(),[]).append(a)
checked=0;mismatches=[]
for r in inv['records']:
 rel='anon/'+Path(r['source']).name;idx=byname[rel]
 for c in r['containers']:
  matches=bypath.get(c.lower(),[])
  if not any(a['bundleIndex']==idx for a in matches):mismatches.append({'container':c,'expected_bundle':rel,'index_matches':matches})
  checked+=1
targets=[]
for a in assets:
 if any(s in a.get('path','') for s in ['gamedata/excel/character_table','gamedata/excel/skill_table','gamedata/excel/roguelike_topic_table','gamedata/levels/obt/roguelike/ro6/level_rogue6_1-1','gamedata/levels/enemydata/enemy_database']):targets.append(a|{'bundle_name':bundles[a['bundleIndex']]['name']})
level_paths=[a['path'] for a in assets if a.get('path','').startswith('dyn/gamedata/levels/obt/roguelike/')]
res={'resource_version':manifest['versionId'],'bundle_count':len(bundles),'asset_mapping_count':len(assets),'all_bundle_names_in_hot_update_manifest':True,'all_asset_bundle_indices_in_range':True,'all_dependency_indices_in_range':True,'anon_container_paths_checked':checked,'container_index_mismatch_count':len(mismatches),'mismatch_sample':mismatches[:10],'rule_targets':targets,'roguelike_rule_asset_count':len(level_paths),'roguelike_rule_groups':dict(collections.Counter(p.split('/')[5] for p in level_paths)),'lua_mapping_count':sum('/[uc]lua/' in a.get('path','') for a in assets),'mapping_entries_without_path':sum(not a.get('path') for a in assets),'limitations':'Verified name/reference and dependency bounds; SCC grouping semantics and runtime asset loader behavior were not executed.'}
(OUT/'index_validation.json').write_text(json.dumps(res,ensure_ascii=False,indent=2),'utf-8');print(json.dumps(res,ensure_ascii=False))

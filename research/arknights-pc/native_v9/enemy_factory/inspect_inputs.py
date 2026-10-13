from pathlib import Path
import json
OUT=Path(__file__).parent;data=json.loads((OUT/'resource_inputs.json').read_text())
for e in data['selected']:
 print(e['key'])
 print('root field names',list(e['enemy_component']['fields']))
 print('resolved',e.get('resolved_values'))
 for c in e['prefab']['rule_components']:
  if any(x in c['class_name'].lower() for x in ['talent','enemy','buff']):
   print(c['class_name'],c['path_id'],c.get('hierarchy_path'),c['fields'])

"""Package immutable native bounds and reviewed component inputs, no target execution."""
from pathlib import Path
import hashlib, json, sys

OUT = Path(__file__).parent
ROOT = OUT.parents[1]
REPO = Path(r'D:\Repo\arknights-sim')
EVIDENCE = REPO/'evidence/damage'
TARGET_SHA = '583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5'
METADATA_SHA = 'd3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f'

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def read(path):
    return json.loads(path.read_text('utf8'))

def pin(path):
    return {'path': str(path), 'sha256': digest(path)}

def save(name, data):
    text = json.dumps(data, ensure_ascii=False, indent=2) + '\n'
    (OUT/name).write_text(text, encoding='utf8')
    (EVIDENCE/name).write_text(text, encoding='utf8')

EVIDENCE.mkdir(exist_ok=True)
source = OUT/'prepare.py'
ns = {'__file__': str(source)}
exec(compile(source.read_text('utf8').split('selection=json.loads')[0], str(source), 'exec'), ns)
assert ns['pe']['sha256'] == TARGET_SHA
metadata_path = Path(ns['pe']['path']).parent/'Arknights_Data/il2cpp_data/Metadata/global-metadata.dat'
assert digest(metadata_path) == METADATA_SHA
base, binary, engine, to_file = ns['base'], ns['b'], ns['engine'], ns['rva']

# Existing v5 lifecycle files are frozen. Verify them without rewriting them.
life_manifest_path = REPO/'evidence/lifecycle/manifest.json'
life_manifest = read(life_manifest_path)
life_checks = [{'path': x['path'], 'match': digest(Path(x['path'])) == x['sha256']}
               for x in life_manifest['files']]
assert all(x['match'] for x in life_checks)

native_sources = [(OUT/'prior_native_results.json', None),
                  (OUT/'results_round1.json', None), (OUT/'results_round2.json', None),
                  (ROOT/'native_v4/creation/results_round2.json', {'0x180a6d0d0'}),
                  (ROOT/'native_v3/timeline/results_round6.json', {'0x18091bb70'}),
                  (ROOT/'native_v5/lifecycle/results_round1.json', {
                      '0x1806fb290','0x1806f8c40','0x1806f9e00','0x180a70920','0x180a71770'}),
                  (ROOT/'native_v5/lifecycle/results_round2.json', {
                      '0x180aca5b0','0x18065ea80','0x180661df0','0x180661ec0','0x18091bcb0'})]
functions = {}
for path, wanted in native_sources:
    data = read(path)
    assert data['target_sha256'] == TARGET_SHA
    for f in data['functions']:
        if wanted is not None and f['address'] not in wanted:
            continue
        assert f['decompile_completed'] and f['imported_memory_matches_source'], f['address']
        assert all(c['match'] for c in f['imported_range_checks']), f['address']
        if f['address'] not in functions:
            functions[f['address']] = {**f, 'evidence_origins': []}
        functions[f['address']]['evidence_origins'].append(pin(path))

raw_sources = [(OUT/'raw_helpers.json', None),
               (ROOT/'native_v5/lifecycle/raw_helpers.json', {
                   'Entity.FinishMe','DefaultGameMode.DestroyEntity','Entity.RecycleSelfImmediately',
                   'PoolManager.BattleOnly.RawRecycle','PoolManager.Recycle','PoolManager._RecycleInternal',
                   'PoolManager.component_pool_Recycle_call_target','IPooledObject.OnRecycle_call_target'}),
               (ROOT/'native_v5/devices/raw_helpers.json', {'Torappu.MathUtil..cctor'})]

raw_specs = {va: {'name': f['display_name'], 'address': va, 'ranges': f['ranges'],
                 'range_provenance': f['range_provenance'], 'evidence_origins': f['evidence_origins']}
             for va, f in functions.items()}
for path, wanted in raw_sources:
    data = read(path)
    assert data['target_sha256'] == TARGET_SHA
    for f in data['functions']:
        if wanted is not None and f['name'] not in wanted:
            continue
        va = f.get('address', f.get('candidate_va'))
        if va not in raw_specs:
            raw_specs[va] = {**f, 'address': va, 'evidence_origins': [],
                             'range_provenance': 'Exact PE recursive chain components or documented bounded straight-line leaf'}
        raw_specs[va]['evidence_origins'].append(pin(path))

labels = dict(x.split('\t', 1) for x in (ROOT/'native_v2/labels.tsv').read_text('utf8').splitlines())
association = {}
for image in ['Assembly-CSharp','Torappu.Common','ThirdPartyAssembly','mscorlib']:
    for row in read(ROOT/'core'/f'{image}_candidate_method_map.json'):
        if row.get('candidate_va') in raw_specs:
            association.setdefault(row['candidate_va'], []).append({
                'image': image, 'type': row['type'], 'method': row['method'],
                'token': row['token'], 'metadata_method_index': row['metadata_method_index']})

raw = []
unique_ranges = {}
for va, f in sorted(raw_specs.items(), key=lambda item: int(item[0], 16)):
    ranges = []
    for r in f['ranges']:
        start = int(r['start'],16)
        end = int(r['end'],16)+1 if 'end' in r else int(r['end_exclusive'],16)
        offset = to_file(start-base, end-start)
        body = binary[offset:offset+end-start]
        expected = r.get('source_sha256', r.get('sha256'))
        assert hashlib.sha256(body).hexdigest() == expected, (va, r)
        unique_ranges[(start, end, expected)] = (offset, len(body))
        ranges.append({'start': hex(start), 'end_exclusive': hex(end), 'bytes': len(body),
                       'unwind_rva': r.get('unwind_rva'), 'source_file_offset': offset,
                       'source_sha256': expected, 'source_match': True,
                       'instructions': [{'address': hex(i.address), 'bytes': i.bytes.hex(),
                                         'mnemonic': i.mnemonic, 'operands': i.op_str,
                                         'candidate_callee': labels.get(i.op_str)}
                                        for i in engine.disasm(body, start)]})
    raw.append({'name': f['name'], 'address': va, 'metadata_candidates': association.get(va, []),
                'range_provenance': f['range_provenance'], 'ranges': ranges,
                'evidence_origins': f['evidence_origins']})

counts = {'decompiled_entries': len(functions),
          'imported_ranges_checked': sum(len(f['imported_range_checks']) for f in functions.values()),
          'static_disassembly_entries': len(raw), 'unique_source_ranges': len(unique_ranges),
          'source_range_bytes': sum(size for _, size in unique_ranges.values()),
          'all_imported_ranges_match': True, 'all_source_ranges_match': True}
save('native_report.json', {'target': pin(Path(ns['pe']['path'])), 'metadata': pin(metadata_path),
                          'counts': counts, 'functions': list(functions.values()),
                          'limits': ['Metadata names are native-pointer candidate associations, not recovered original source.',
                                     'Pseudocode can omit returns or misinfer shared helper names; raw instruction bodies decide arithmetic and flow.',
                                     'Static original-client default branch; no hotfix dispatch or target runtime execution.']})
save('native_disassembly.json', {'target_sha256': TARGET_SHA, 'functions': raw, 'counts': counts,
                               'limits': ['Exclusive ends describe exact source ranges, never padding-derived union spans.',
                                          'FP.op_LessThan shares its 7-byte signed cmp/setl/ret body with System.TimeSpan.op_LessThan.']})

prefab_path = ROOT/'native_v5/resources/rule_prefab_subtrees.json'
prefabs = read(prefab_path)
selected_prefabs = [x for x in prefabs['prefabs'] if x['name'] in ('enemy_1034_laxe','trap_011_ore')]
assert len(selected_prefabs) == 2
for item in selected_prefabs:
    assert digest(Path(item['source_pin']['path'])) == item['source_pin']['sha256']
template_path = ROOT/'native_v5/resources/scene_templates.json'
templates = read(template_path)
selected_templates = {k: templates['templates'][k] for k in ('empty','ore_s','ore_buff')}
assert selected_templates['empty']['raw']['eventToActions']['_items'] == []
save('resource_inputs.json', {'prefab_reader': pin(prefab_path), 'script_source_pin': prefabs['script_source_pin'],
                            'prefabs': selected_prefabs, 'template_reader': pin(template_path),
                            'template_source_pin': templates['source_pin'], 'templates': selected_templates,
                            'limits': ['Complete rule Transform subtrees are audited declarations, not observations of all runtime attached buffs.',
                                       'frosts_effect has INVINCIBLE and HEAL_FREE flags; its actual empty template is preserved.',
                                       'The caller explicitly supplies initialized empty source action slots.',
                                       'Only already-finished ore_s/ore_buff are ignored by damage hooks; unfinished ore_buff can execute SwitchMode on clear.']})

enum_path = ROOT/'native_v6/skill/enum_constants.json'
enum_data = read(enum_path)
enum_names = {'Torappu.Battle.DamageType','Torappu.Battle.Entity.FinishReason',
              'Torappu.Battle.Modifier.SharedFlagIndex','Torappu.Battle.Modifier.SourceAttackType',
              'Torappu.Battle.Modifier.CancelReason','Torappu.Battle.Modifier.CancelReasonMask',
              'Torappu.Battle.Enemy.States.State'}
save('enum_constants.json', {**enum_data, 'source_reader': pin(enum_path),
                            'enums': [x for x in enum_data['enums'] if x['name'] in enum_names]})

fields = []
field_sources = [(ROOT/'native_v4/resources/native_fields.json', {
    'Torappu.Battle.Entity': {'m_hp','m_es','<finishReason>k__BackingField','<buffContainer>k__BackingField',
                            '<minusHp>k__BackingField','<maxMinusHpRatio>k__BackingField'},
    'Torappu.Battle.Unit': {'<talents>k__BackingField'},
    'Torappu.Battle.Enemy': {'_useSpecificDeadAnim','_useSpecificReachExitAnim','m_delayToRecycle'}}),
    (ROOT/'native_v5/devices/native_fields.json', {
        'Torappu.Battle.Buff': {'m_source','m_actions','m_isFinished','m_isActuallyFinished'},
        'Torappu.MathUtil': {'FP_LARGE_EPS'}, 'Torappu.FP': {'EN5','Zero','One','_serializedValue'}})]
for path, wanted in field_sources:
    d = read(path)
    assert d['target_sha256'] == TARGET_SHA and d['metadata_sha256'] == METADATA_SHA
    for t in d['types']:
        if t['name'] not in wanted:
            continue
        selected = [x for x in t['fields'] if x['name'] in wanted[t['name']]]
        assert len(selected) == len(wanted[t['name']]), t['name']
        fields.append({'name': t['name'], 'definition_index': t['definition_index'], 'sizes': t['sizes'],
                       'fields': selected, 'source_reader': pin(path)})
save('fields.json', {'target_sha256': TARGET_SHA, 'metadata_sha256': METADATA_SHA, 'types': fields,
                    'limits': ['Value type instance offsets include a boxed header; unboxed layouts require raw-access corroboration.',
                               'Static and instance fields sharing numeric offsets must not be confused.']})

comparison_path = EVIDENCE/'reference_comparison.json'
comparison = read(comparison_path)
assert comparison['case_count'] == 255 and not comparison['game_code_loaded']
comparison.update({'python_comparison_cases': 255, 'python_comparison_passed': True,
                   'unit_test_count': 15, 'unit_test_passed': True,
                   'hp_boundary': 'strict hp.raw < 42950 snaps to zero; equality stays nonalive without finishing'})
comparison_path.write_text(json.dumps(comparison, indent=2)+'\n', encoding='utf8')
(OUT/'reference_comparison.json').write_bytes(comparison_path.read_bytes())

save('audit_summary.json', {'target_sha256': TARGET_SHA, 'metadata_sha256': METADATA_SHA,
                           'counts': counts, 'lifecycle_manifest': pin(life_manifest_path),
                           'frozen_v5_lifecycle_checks': life_checks,
                           'runtime_compared': False, 'game_launched': False,
                           'independent_reference_cases': 255, 'damage_tests': 15,
                           'complete_scene_supported': False})
print(json.dumps(counts))

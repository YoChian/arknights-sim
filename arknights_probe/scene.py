"""Account for a shipped scene's rule dependencies before running it.

Object/Transform declarations are an inventory, not proof that a component is
attached or enabled in a native frame. Hidden predefines can later activate;
absence of deployed operators never makes their rules safe to discard.
"""
from __future__ import annotations

import copy
import json
from collections import Counter
from pathlib import Path

from .data import Dataset, require, sha256
from .enemy_data import resolve_enemy
from .env import UnverifiedMechanism
from .timeline import CompiledTimeline


def _strings(value):
    if isinstance(value, str):
        yield value
    elif isinstance(value, dict):
        for child in value.values():
            yield from _strings(child)
    elif isinstance(value, list):
        for child in value:
            yield from _strings(child)


def _named_strings(value, names):
    if isinstance(value, dict):
        for key, child in value.items():
            if key in names and isinstance(child, str) and child:
                yield child
            yield from _named_strings(child, names)
    elif isinstance(value, list):
        for child in value:
            yield from _named_strings(child, names)


def _templates(document):
    result = {}
    entries = document['templates']
    if isinstance(entries, dict):
        entries = entries.values()
    for entry in entries:
        raw = entry['raw']
        key = raw['templateKey']
        require(key not in result, f'Duplicate buff template {key}')
        nodes, events = [], []
        for event in raw['eventToActions']['_items']:
            body = json.loads(event['value']['SerializedState'])
            require(isinstance(body, list), f'Invalid action nodes in {key}')
            nodes.extend(body)
            events.append({'event_number': event['key'], 'nodes': copy.deepcopy(body)})
        result[key] = {'nodes': nodes, 'events': events, 'raw': raw}
    return result


def audit_idle_scene(dataset: Dataset, compiled: CompiledTimeline,
                     rule_subtrees: dict, idle_templates: dict, *, source: str):
    """Return conservative dependencies; this API never grants execution rights.

    Includes every declared predefined object, selected main spawns, branch
    spawns, and enemy references used by summon blackboards. Component names
    and loaded templates are retained even when not yet translated, so future
    prefab changes cannot be silently treated as an inert enemy.
    """
    require(isinstance(source, str) and source.strip(), 'Scene audit needs source')
    require(isinstance(compiled, CompiledTimeline), 'Compiled timeline required')
    prefabs = {}
    for prefab in rule_subtrees['prefabs']:
        require(prefab['name'] not in prefabs, 'Duplicate subtree prefab')
        prefabs[prefab['name']] = prefab
    templates = _templates(idle_templates)
    selected = []
    for wi, wave in enumerate(compiled.waves):
        for fi, fragment in enumerate(wave['fragments']):
            for item in fragment['items']:
                action = item['action']
                if action['actionType'] == 'SPAWN':
                    selected.append({'key': action['key'], 'path': item['path'],
                        'route_index': action['routeIndex'], 'route_pool': 'routes',
                        'wave': wi, 'fragment': fi})
    branch = [{'branch': key, 'key': item['action']['key'], 'path': item['path'],
               'route_index': item['action']['routeIndex'], 'route_pool': 'extraRoutes'}
              for key, items in compiled.branches.items() for item in items
              if item['action']['actionType'] == 'SPAWN']
    activation = sorted({item['action']['key']
        for wave in compiled.waves for fragment in wave['fragments']
        for item in fragment['items'] if item['action']['actionType'] == 'ACTIVATE_PREDEFINED'})
    predefines = copy.deepcopy(dataset.level['predefines']['tokenInsts'])
    required = {x['key'] for x in selected + branch}
    required.update(x['inst']['characterKey'] for x in predefines)
    # A token's skill prefab is a separately exported subtree.
    required.update({'sktok_ore'} if 'trap_011_ore' in required else set())
    enemy_profiles, summon_dependencies = {}, []
    pending = list(sorted(required & dataset.enemy_refs.keys()))
    while pending:
        key = pending.pop(0)
        if key in enemy_profiles:
            continue
        resolved = resolve_enemy(dataset.tables['enemies'], dataset.enemy_refs[key])
        enemy_profiles[key] = {'skills': copy.deepcopy(resolved.skills),
            'sp_data': copy.deepcopy(resolved.sp_data),
            'talent_blackboard': copy.deepcopy(resolved.talent_blackboard)}
        for row in resolved.talent_blackboard:
            target = row.get('valueStr')
            if row['key'].endswith('enemy_key') and target:
                summon_dependencies.append({'owner': key, 'enemy_key': target,
                                              'blackboard_key': row['key']})
                required.add(target)
                require(target in dataset.enemy_refs, f'Summoned enemy data missing: {target}')
                pending.append(target)
    # Include child buff dependencies (e.g. a summonee finish buff restoring its
    # hidden host) rather than looking only at a prefab's direct buff list.
    buff_keys, declared_templates = set(), set()
    missing_prefabs = sorted(required - prefabs.keys())
    objects = []
    for key in sorted(required & prefabs.keys()):
        prefab = prefabs[key]
        components = prefab['rule_components']
        for component in components:
            buff_keys.update(set(_strings(component['fields'])) & templates.keys())
            declared_templates.update(_named_strings(component['fields'], {'templateKey', '_templateKey'}))
        objects.append({'key': key, 'source_pin': copy.deepcopy(prefab['source_pin']),
            'component_counts': dict(Counter(c['class_name'] for c in components)),
            'components': [{'class_name': c['class_name'], 'hierarchy_path': c['hierarchy_path'],
                            'path_id': c['path_id'], 'serialized_sha256': c['serialized_sha256'],
                            'enabled_serialized': c['fields'].get('m_Enabled')}
                           for c in components]})
    changed = True
    while changed:
        children = {value for key in buff_keys for value in _strings(templates[key]['nodes'])
                    if value in templates}
        changed = not children <= buff_keys
        buff_keys.update(children)
        for key in buff_keys:
            declared_templates.update(_named_strings(templates[key]['nodes'], {'templateKey', '_templateKey'}))
        newly_known = declared_templates & templates.keys()
        changed = changed or not newly_known <= buff_keys
        buff_keys.update(newly_known)
    missing_templates = sorted(declared_templates - templates.keys())
    buff_rules = [{'key': key, 'events': copy.deepcopy(templates[key]['events']),
        'node_types': sorted({node['$type'] for node in templates[key]['nodes'] if '$type' in node})}
        for key in sorted(buff_keys)]
    classes = sorted({c['class_name'] for obj in objects for c in obj['components']})
    return {'scope': 'shipped_scene_rule_dependency_audit', 'source': source,
        'mode': compiled.mode, 'group_selections': copy.deepcopy(compiled.group_selections),
        'selected_main_spawns': selected, 'conditional_branch_spawns': branch,
        'activation_aliases': activation, 'predefines': predefines,
        'required_prefabs': sorted(required), 'missing_prefabs': missing_prefabs,
        'enemy_profiles': enemy_profiles, 'summon_dependencies': summon_dependencies,
        'objects': objects, 'buff_rules': buff_rules, 'component_classes': classes,
        'required_buff_templates': sorted(declared_templates), 'missing_buff_templates': missing_templates,
        'execution_blockers': [
            *[f'missing_prefab:{key}' for key in missing_prefabs],
            *[f'missing_buff_template:{key}' for key in missing_templates],
            'native_component_attachment_and_target_predicate_closure',
            'full_scene_ability_and_buff_execution_bindings',
            'explicit_game_mode_global_modifiers_rng_and_initial_life_context',
            'automatic_predefine_branch_and_summon_lifecycle'],
        'idle_scene_ready': False, 'battle_ready': False,
        'client_runtime_compared': False,
        'limits': copy.deepcopy(rule_subtrees['limits'])}


def require_idle_scene_ready(audit: dict):
    """Guard until the complete scene has supported execution bindings."""
    require(audit.get('scope') == 'shipped_scene_rule_dependency_audit', 'Invalid scene audit')
    if audit.get('execution_blockers') or not audit.get('idle_scene_ready'):
        raise UnverifiedMechanism('Idle scene execution is not closed: ' +
                                  ', '.join(audit.get('execution_blockers', [])))


def input_pins(*paths: Path):
    return [{'path': str(path.resolve()), 'sha256': sha256(path)} for path in paths]

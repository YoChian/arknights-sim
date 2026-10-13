import copy
from pathlib import Path
import unittest

from arknights_probe.data import Dataset, read_json
from arknights_probe.prepare import DEFAULT_MANIFEST
from arknights_probe.timeline import compile_timeline
from arknights_probe.scene import audit_idle_scene, require_idle_scene_ready
from arknights_probe.env import UnverifiedMechanism

ROOT = Path(__file__).resolve().parents[1]
SOURCES = Path(r'D:\Repo\.rea-tools\arknights-pc\native_v5\resources')


class SceneAuditTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dataset = Dataset.from_manifest(DEFAULT_MANIFEST)
        cls.compiled = compile_timeline(cls.dataset, **read_json(
            ROOT / 'examples/timeline_normal_resolved.json'))
        cls.subtrees = read_json(SOURCES / 'rule_prefab_subtrees.json')
        cls.templates = read_json(SOURCES / 'scene_templates.json')

    def audit(self, subtrees=None):
        return audit_idle_scene(self.dataset, self.compiled,
            subtrees if subtrees is not None else self.subtrees, self.templates,
            source='shipped_inputs_static_audit_test')

    def test_summonee_is_required_without_counting_as_scheduled_spawn(self):
        audit = self.audit()
        self.assertNotIn('enemy_3001_upeopl', {x['key'] for x in audit['selected_main_spawns']})
        self.assertIn('enemy_3001_upeopl', audit['required_prefabs'])
        self.assertIn({'owner': 'enemy_2133_shdopl', 'enemy_key': 'enemy_3001_upeopl',
                       'blackboard_key': 'summon.enemy_key'}, audit['summon_dependencies'])
        self.assertIn('enemy_shdopl_finish', {x['key'] for x in audit['buff_rules']})
        self.assertIn('upeople_t', {x['key'] for x in audit['buff_rules']})

    def test_hidden_predefines_and_altar_are_retained(self):
        audit = self.audit()
        self.assertEqual(9, len(audit['predefines']))
        self.assertEqual(8, sum(p['hidden'] for p in audit['predefines']))
        self.assertIn('sktok_ore', audit['required_prefabs'])
        self.assertIn('trap_322_shrbox', audit['required_prefabs'])
        self.assertIn('trap_rarebox_t[inverse_damage]', {x['key'] for x in audit['buff_rules']})
        self.assertEqual([], audit['missing_buff_templates'])
        self.assertFalse(audit['idle_scene_ready'])
        with self.assertRaises(UnverifiedMechanism):
            require_idle_scene_ready(audit)

    def test_missing_prefab_is_an_explicit_execution_blocker(self):
        changed = copy.deepcopy(self.subtrees)
        changed['prefabs'] = [p for p in changed['prefabs'] if p['name'] != 'enemy_3001_upeopl']
        audit = self.audit(changed)
        self.assertEqual(['enemy_3001_upeopl'], audit['missing_prefabs'])
        self.assertIn('missing_prefab:enemy_3001_upeopl', audit['execution_blockers'])

    def test_unfamiliar_child_component_is_never_dropped(self):
        changed = copy.deepcopy(self.subtrees)
        prefab = next(p for p in changed['prefabs'] if p['name'] == 'enemy_1034_laxe')
        extra = copy.deepcopy(prefab['rule_components'][0])
        extra['class_name'] = 'Torappu.Battle.NewRuleForAudit'
        extra['fields']['m_Enabled'] = 0
        prefab['rule_components'].append(extra)
        audit = self.audit(changed)
        self.assertIn(extra['class_name'], audit['component_classes'])
        self.assertFalse(audit['battle_ready'])


if __name__ == '__main__':
    unittest.main()

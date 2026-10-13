"""Source-bound staged Enemy.Spawn/Init/Born, with named Unity boundaries.

This does not accept an externally initialized enemy or silently replace NPC
talents with an empty list. Allocation/Awake/reset/controllers/pose and live
ability dispatch are explicit receipts/providers. The shared actor itself is
NpcEntity, so Buff pointers and a lifecycle backend can retain its identity.
"""
from __future__ import annotations

from collections.abc import Callable, Mapping
from copy import deepcopy
from dataclasses import dataclass, field
import hashlib
import json
import math
from pathlib import Path
from types import MappingProxyType
from weakref import WeakValueDictionary

from .enemy_data import resolve_enemy
from .fp import FP, binary32
from .lifecycle import native_alive, SINGLE_EPSILON
from .npc_actions import DataPair, NpcBlackboard, NpcEntity, bind_talent_blackboard
from .npc_summon import SummonOptions

INPUTS = Path(r"D:\Repo\.rea-tools\arknights-pc\native_v9\enemy_factory\resource_inputs.json")
KEYS = frozenset(("enemy_2133_shdopl", "enemy_3001_upeopl"))
_SOURCE_PREPARATIONS = WeakValueDictionary()


class UnverifiedFactoryContext(ValueError):
    pass


def _need(condition, message):
    if not condition:
        raise UnverifiedFactoryContext(message)


def _bool(value, name):
    _need(type(value) is bool, name + " requires explicit Boolean")
    return value


def _uid(value):
    _need(type(value) is int and 0 <= value < (1 << 32), "native UID must be UInt32")
    return value


def _single(value):
    _need(type(value) in (int, float) and math.isfinite(value), "finite native Single required")
    result = binary32(value)
    _need(math.isfinite(result), "Single overflow outside factory scope")
    return result


def _vec(value):
    _need(type(value) is tuple and len(value) == 2, "native Vector2 tuple required")
    return tuple(_single(x) for x in value)


def _freeze(value):
    if isinstance(value, dict):
        return MappingProxyType({k: _freeze(v) for k, v in value.items()})
    if isinstance(value, list):
        return tuple(_freeze(v) for v in value)
    return value


@dataclass(frozen=True)
class PreparedTalent:
    key: str
    path_id: int
    template_keys: tuple[str, ...]
    blackboard_rows: tuple[DataPair, ...]
    source: str


@dataclass(frozen=True)
class PreparedEnemyInputs:
    enemy_key: str
    prefab_key: str
    prefab_bundle_sha256: str
    enemy_script_path_id: int
    reference: Mapping
    values: Mapping
    attributes: Mapping
    primitive_attributes: Mapping
    talent_blackboard_rows: tuple[DataPair, ...]
    talents: tuple[PreparedTalent, ...]
    common_ability_templates: tuple[str, ...]
    passive_ability_declarations: tuple[Mapping, ...]
    skills: tuple
    sp_data: object
    delay_to_born: float
    only_delay_on_start_tile: bool
    side_type_index: int
    height: float
    idle_when_born: bool
    always_check_current_point: bool
    prefab_fields: Mapping
    source: str


def prepare_enemy(dataset, enemy_key: str, *, inputs_path: Path | str = INPUTS,
                  native_default_no_hotfix: bool = True, no_global_numeric_modifiers: bool = True):
    """Resolve exact reviewed map ref/database and derive selected prefab input."""
    _need(native_default_no_hotfix is True and no_global_numeric_modifiers is True,
          "explicit native default and absent global numeric modifiers required")
    _need(enemy_key in KEYS, "only source-reviewed shdopl/upeopl preparation supported")
    path = Path(inputs_path)
    data = json.loads(path.read_text(encoding="utf-8"))
    _need(data.get("format") == "native_v9_enemy_factory_inputs_v1", "unknown source input format")
    row = next((x for x in data["selected"] if x["key"] == enemy_key), None)
    _need(row is not None, "selected Enemy source missing")
    # Derived source plus original AB hash and original MonoScript identity.
    for pin in data["sources"] + [data["script_source_pin"]]:
        with Path(pin["path"]).open("rb") as stream:
            actual = hashlib.file_digest(stream, "sha256").hexdigest()
        _need(actual == pin["sha256"], "source changed: " + pin["path"])
    trees = json.loads(Path(data["sources"][0]["path"]).read_text(encoding="utf-8"))
    source_prefab = next((p for p in trees["prefabs"] if p["name"] == enemy_key), None)
    _need(row["prefab"] == source_prefab and data["script_source_pin"] == trees["script_source_pin"],
          "derived prefab fields must equal pinned original resource extraction")
    _need(row["enemy_component"] in source_prefab["rule_components"], "Enemy component is not source-owned")
    _need(dataset.enemy_refs.get(enemy_key) == row["level_reference"], "reviewed original map ref changed")
    _need(dataset.tables["enemies"]["enemies"][enemy_key] == row["selected_db_levels"], "reviewed EnemyDB data changed")
    resolved = resolve_enemy(dataset.tables["enemies"], row["level_reference"])
    fields = row["enemy_component"]["fields"]
    _need(resolved.values["key"] == enemy_key and resolved.values["motion"] == "WALK", "unreviewed prefab/motion mapping")
    _need(fields["_onlyDelayToBornOnTileStart"] == 0 and fields["_idleWhenBorn"] == 0,
          "tile-dependent birth delay or idle-on-born is outside execution scope")
    raw_bb = resolved.talent_blackboard
    bb = tuple(DataPair(x["key"], x.get("value", 0.0), x.get("valueStr")) for x in (raw_bb or ()))
    components = row["prefab"]["rule_components"]
    talents = []
    for component in components:
        if component["class_name"] != "Torappu.Battle.Talent":
            continue
        f = component["fields"]
        # BasicTalent.get_talentKey(180974190) uses Unity Object.name if
        # overwrite is null/empty. Runtime discovery/name still needs a receipt.
        _need(f["_overwriteTalentKey"] == "", "overwrite talent key requires another getter path")
        key = component["hierarchy_path"].rsplit("/", 1)[-1]
        bound = bind_talent_blackboard(bb, key, culture="invariant")
        abilities = [c for c in components if c["class_name"] == "Torappu.Battle.Abilities.PassiveBuffAbility"
                     and c["hierarchy_path"] == component["hierarchy_path"]]
        templates = tuple(b["templateKey"] for a in abilities for b in a["fields"]["_buffs"])
        talents.append(PreparedTalent(key, component["path_id"], templates, tuple(bound.entries),
                                      str(path) + ": serialized Talent child; external discovery/init phase"))
    root_common = {p["m_PathID"] for p in fields["_commonAbilities"] if p["m_FileID"] == 0}
    common = tuple(b["templateKey"] for c in components if c["path_id"] in root_common
                   for b in c["fields"]["_buffs"])
    passives = tuple(_freeze(c) for c in components
                     if c["class_name"] == "Torappu.Battle.Abilities.PassiveBuffAbility")
    _need(len(talents) == 1 and all(t.template_keys for t in talents), "selected live talent dependency missing")
    prepared = PreparedEnemyInputs(enemy_key, resolved.values["key"], row["prefab"]["source_pin"]["sha256"],
        row["enemy_component"]["script_path_id"], _freeze(deepcopy(row["level_reference"])),
        _freeze(deepcopy(resolved.values)), _freeze(dict(resolved.attributes)),
        _freeze(deepcopy(resolved.attribute_values)), bb, tuple(talents), common, passives,
        tuple(_freeze(s) for s in resolved.skills), _freeze(resolved.sp_data),
        _single(fields["_delayToBorn"]), False, fields["_sideTypeIndex"], _single(fields["_height"]),
        False, bool(fields["_alwaysCheckCurrentPoint"]), _freeze(fields),
        str(path) + " sha256=" + hashlib.sha256(path.read_bytes()).hexdigest())
    _SOURCE_PREPARATIONS[id(prepared)] = prepared
    return prepared


@dataclass(frozen=True)
class UnityAllocationReceipt:
    token: str
    uid: int
    prefab_key: str
    prefab_bundle_sha256: str
    enemy_script_path_id: int
    unity_exists: bool
    awake_and_reusable_reset_completed: bool
    controller_instances_ready: bool
    source: str


@dataclass(frozen=True)
class FactoryPhaseReceipt:
    actor_token: str
    actor_uid: int
    phase: str
    source: str


@dataclass(frozen=True)
class CursorPreparationReceipt:
    actor_token: str
    actor_uid: int
    cursor: object
    source: str


@dataclass(frozen=True)
class RegistrationReceipt:
    actor_token: str
    actor_uid: int
    registered: bool
    source: str


@dataclass(frozen=True)
class PreparedFactoryRoute:
    route: object
    motion_mode: int
    spawn_position: tuple[float, float]
    spawn_offset: tuple[float, float]
    start_grid: tuple[int, int]
    end_grid: tuple[int, int]
    current_grid: tuple[int, int]
    origin_tile_hidden: bool
    source: str

    def validate(self):
        _need(self.route is not None and bool(self.source), "prepared native Route getter source required")
        _need(type(self.motion_mode) is int and self.motion_mode == 0,
              "only reviewed WALK-route/no-motion-correction branch supported")
        _vec(self.spawn_position); _vec(self.spawn_offset)
        for value in (self.start_grid, self.end_grid, self.current_grid):
            _need(type(value) is tuple and len(value) == 2 and all(type(n) is int and -(1 << 31) <= n < (1 << 31) for n in value),
                  "prepared GridPosition tuples required")
        _need(_bool(self.origin_tile_hidden, "originTile.isHidden") is False,
              "hidden-origin Enemy.Born path not implemented")


@dataclass(eq=False)
class FactoryEnemy(NpcEntity):
    prepared: PreparedEnemyInputs | None = None
    stage: str = "allocated"
    state_id: int = -1
    hp: FP = FP(0)
    max_hp: FP = FP(0)
    born_remaining: FP = FP(0)
    borned: bool = False
    initialized: bool = False
    enabled: bool = False
    registered: bool = False
    created_time: FP = FP(0)
    options: object = None
    cursor: object = None
    attributes: dict = field(default_factory=dict)
    talent_blackboards: dict = field(default_factory=dict)
    life_point_reduce: int = 0
    prefab_side_index: int = 0
    route: PreparedFactoryRoute | None = None

    def sync_alive(self):
        self.alive = self.unity_exists and native_alive(self.state_id, self.hp)
        return self.alive


@dataclass(frozen=True)
class EnemyFactoryContext:
    source: str
    native_default_no_hotfix: bool
    no_global_numeric_modifiers: bool
    controller_state_nonzero: bool
    default_game_mode: bool
    enable_delay_update_tile: bool
    is_dummy: bool

    def __post_init__(self):
        _need(bool(self.source), "factory context provenance required")
        for name in self.__dataclass_fields__:
            if name != "source":
                _bool(getattr(self, name), name)
        _need(self.native_default_no_hotfix and self.no_global_numeric_modifiers and self.default_game_mode,
              "unknown native modifier/hotfix/game-mode path")
        _need(not self.is_dummy, "dummy talents/abilities path not supported")


@dataclass(frozen=True)
class EnemyFactoryCallbacks:
    external_phase: Callable[[FactoryEnemy, str, object], FactoryPhaseReceipt]
    build_cursor: Callable[[FactoryEnemy, PreparedFactoryRoute], CursorPreparationReceipt]
    emit_born: Callable[[FactoryEnemy], None]
    buff_owner_born: Callable[[FactoryEnemy], None]
    register_unit: Callable[[FactoryEnemy], RegistrationReceipt]
    enemy_on_born: Callable[[FactoryEnemy], None]
    # Admission only: must not execute OnExit/OnEnter or change state. Those
    # hooks are named external phases around the local state write below.
    fsm_transition: Callable[[FactoryEnemy, int, int], bool]
    move_tick: Callable[[FactoryEnemy, FP], None]

    def __post_init__(self):
        _need(all(callable(getattr(self, key)) for key in self.__dataclass_fields__),
              "all external phases/birth/FSM/movement callbacks must be explicit")


class EnemyFactoryRuntime:
    def __init__(self, context: EnemyFactoryContext, callbacks: EnemyFactoryCallbacks, clock: Callable):
        _need(isinstance(context, EnemyFactoryContext) and isinstance(callbacks, EnemyFactoryCallbacks)
              and callable(clock), "typed context/callbacks/shared clock required")
        self.context, self.callbacks, self.clock = context, callbacks, clock
        self.actors: dict[str, FactoryEnemy] = {}
        self.events: list[dict] = []

    def _event(self, actor, kind, **details):
        frame, time = self.clock()
        _need(type(frame) is int and isinstance(time, FP), "clock returns (frame,FP fixedPlayTime)")
        self.events.append(dict(frame=frame, time_raw=time.raw, uid=actor.uid, token=actor.token,
                                kind=kind, stage=actor.stage, state=actor.state_id, **details))

    def _own(self, actor):
        _need(isinstance(actor, FactoryEnemy) and self.actors.get(actor.token) is actor,
              "actor must be the same allocated runtime-owned identity")

    def _phase(self, actor, phase, payload=None):
        receipt = self.callbacks.external_phase(actor, phase, payload)
        _need(isinstance(receipt, FactoryPhaseReceipt) and receipt.actor_token == actor.token
              and receipt.actor_uid == actor.uid and receipt.phase == phase and bool(receipt.source),
              "incomplete/mismatched external phase receipt: " + phase)
        self._event(actor, "external_phase", phase=phase, provider_source=receipt.source)

    def allocate(self, prepared: PreparedEnemyInputs, receipt: UnityAllocationReceipt):
        _need(isinstance(prepared, PreparedEnemyInputs) and prepared.enemy_key in KEYS
              and _SOURCE_PREPARATIONS.get(id(prepared)) is prepared,
              "same source-derived prepare_enemy result required; constructed/replaced inputs are not accepted")
        _need(isinstance(receipt, UnityAllocationReceipt) and bool(receipt.token) and bool(receipt.source),
              "Unity allocation/pool provenance required")
        _uid(receipt.uid)
        _bool(receipt.unity_exists, "Unity allocation exists")
        _need((receipt.prefab_key, receipt.prefab_bundle_sha256, receipt.enemy_script_path_id)
              == (prepared.prefab_key, prepared.prefab_bundle_sha256, prepared.enemy_script_path_id),
              "allocation receipt belongs to another prefab/MonoScript")
        if not receipt.unity_exists:
            return None
        _need(receipt.awake_and_reusable_reset_completed is True and receipt.controller_instances_ready is True,
              "actual allocation/Awake/reset/controller preparation remains external")
        _need(receipt.token not in self.actors, "cannot reallocate an existing identity")
        actor = FactoryEnemy(receipt.token, receipt.uid, True, False, True, False, None, prepared=prepared)
        self.actors[actor.token] = actor
        self._event(actor, "allocated_external_unity", provider_source=receipt.source)
        return actor

    def spawn(self, actor: FactoryEnemy, route: PreparedFactoryRoute, options):
        self._own(actor); route.validate()
        _need(actor.stage == "allocated" and actor.state_id == -1 and not actor.initialized and not actor.borned,
              "spawn cannot accept an already initialized/MOVE actor")
        _need(isinstance(options, SummonOptions), "typed native Enemy.Options value required")
        for name in ("unharmful", "always_count_as_killed", "dont_count_as_finished", "is_summon",
                     "disable_born_tween_color", "no_log_in_enemy_stats_when_finished"):
            _bool(getattr(options, name), "Enemy.Options." + name)
        _need(type(options.spawned_count) is int and 0 <= options.spawned_count < (1 << 31),
              "Enemy.Options.spawnedCount requires scoped nonnegative Int32")
        _need(options.hidden_group_key is None and options.action_extra_meta is None and options.action_data is None,
              "non-null Options action/hidden-group metadata needs another source closure")
        p = actor.prepared
        actor.options, actor.route = options, route
        actor.stage = "options_assigned"
        self._event(actor, "options_assigned", unharmful=options.unharmful)
        _, actor.created_time = self.clock()
        actor.attributes = dict(p.attributes)
        actor.max_hp = p.attributes["maxHp"]
        actor.life_point_reduce = 0 if options.unharmful else p.values["lifePointReduce"]
        actor.prefab_side_index = p.side_type_index
        actor.talent_blackboards = {t.key: NpcBlackboard(t.blackboard_rows, culture="invariant") for t in p.talents}
        actor.stage = "data_assigned"
        self._event(actor, "data_assigned", enemy_key=p.enemy_key, life_point_reduce=actor.life_point_reduce,
                    delay_to_born=p.delay_to_born, talent_keys=list(actor.talent_blackboards))
        self._phase(actor, "assign_skill_and_talent", {"skills":p.skills, "talents":p.talents})
        position = tuple(binary32(a+b) for a,b in zip(_vec(route.spawn_position), _vec(route.spawn_offset)))
        self._phase(actor, "entity_attributes_sp_timers", {"attributes":actor.attributes,"sp_data":p.sp_data})
        actor.grid_position = route.current_grid
        self._phase(actor, "bobject_position_height", {"position":position,"height":p.height,"side_index":p.side_type_index})
        self._phase(actor, "entity_on_init_hit_range_clear")
        self._phase(actor, "unit_on_init_modes_common_dynamic_abilities", {
            "common_templates":p.common_ability_templates,"passive_declarations":p.passive_ability_declarations})
        self._phase(actor, "enemy_on_init_controllers_skills_talent_attach", p.talents)
        self._phase(actor, "unit_on_post_init_animator")
        actor.enabled = True
        actor.initialized = True
        actor.stage = "bobject_initialized"
        self._event(actor, "initialized_written")
        # Entity.Init writes full HP after the BObject.Init virtual hooks.
        actor.hp = actor.max_hp
        actor.sync_alive()  # No running state yet, despite positive HP.
        self._event(actor, "full_hp_written", hp_raw=actor.hp.raw)
        self._phase(actor, "entity_origin_tile", route)
        cursor = self.callbacks.build_cursor(actor, route)
        _need(isinstance(cursor, CursorPreparationReceipt) and cursor.actor_token == actor.token
              and cursor.actor_uid == actor.uid and cursor.cursor is not None and bool(cursor.source),
              "native DirectionCursor construction requires a source-bound receipt")
        actor.cursor = cursor.cursor
        self._event(actor, "cursor_prepared", provider_source=cursor.source)
        self._phase(actor, "enemy_tile_cache_delayed" if self.context.enable_delay_update_tile else "enemy_tile_update", route)
        actor.stage = "enemy_initialized"
        self._need_birth(actor)
        return actor

    def _need_birth(self, actor):
        p = actor.prepared
        # Actual selected prefab branch: origin exists/nonhidden (input),
        # Enemy.Born delegates BObject.Born -> OnBorn before borned write.
        self._phase(actor, "enemy_born_origin_nonhidden", actor.route)
        _need(self.callbacks.fsm_transition(actor, -1, 6) is True and actor.state_id == -1,
              "native Start(BORN6) admission adapter must not execute state hooks")
        actor.state_id = 6
        actor.stage = "born_state_entered"
        actor.sync_alive()
        self._phase(actor, "born_state_animation", {"delay_to_born_float32":p.delay_to_born})
        # OnEnter plays animation before the getter-based timer assignment.
        actor.born_remaining = FP.from_float32(p.delay_to_born) if p.delay_to_born > SINGLE_EPSILON else FP(0)
        self._event(actor, "born_state_entered", remaining_raw=actor.born_remaining.raw)
        self.callbacks.emit_born(actor)
        self._event(actor, "entity_born_event0")
        self.callbacks.buff_owner_born(actor)
        actor.sync_alive()
        self._event(actor, "buff_owner_born_dispatched")
        if self.context.controller_state_nonzero:
            receipt = self.callbacks.register_unit(actor)
            _need(isinstance(receipt, RegistrationReceipt) and receipt.actor_token == actor.token
                  and receipt.actor_uid == actor.uid and receipt.registered is True and bool(receipt.source),
                  "UnitManager/mode/global registration requires explicit matching receipt")
            actor.registered = True
            self._event(actor, "registered_external", provider_source=receipt.source)
        else:
            self._event(actor, "registration_skipped_controller_state_zero")
        self._phase(actor, "unit_on_born_start_common_and_dynamic_abilities")
        self._phase(actor, "unit_on_born_controller_event_and_owner_post_born")
        self.callbacks.enemy_on_born(actor)
        self._event(actor, "enemy_on_born_move_face_start_effect_script_logger")
        actor.borned = True
        actor.stage = "born"
        actor.sync_alive()
        self._phase(actor, "bobject_borned_written")
        self._event(actor, "borned_written", state_after_callbacks=actor.state_id)
        # Do not overwrite a synchronous passive state transition with MOVE.

    def tick_birth(self, actor: FactoryEnemy, dt: FP):
        self._own(actor)
        _need(actor.borned and actor.initialized and actor.stage == "born", "native Enemy Born must finish before state Tick")
        _need(isinstance(dt, FP) and dt.raw > 0, "positive native FP state delta required")
        if not actor.unity_exists:
            return False
        if actor.state_id == 6:
            actor.born_remaining = actor.born_remaining - dt
            if actor.born_remaining.raw <= 0:
                _need(self.callbacks.fsm_transition(actor, 6, 1) is True and actor.state_id == 6,
                      "DEFAULT/MOVE admission adapter must not execute state hooks")
                self._phase(actor, "born_state_exit_animation", {
                    "finish_start_effect":True, "enable_delay_update_tile":self.context.enable_delay_update_tile})
                actor.state_id = 1
                actor.sync_alive()
                self._phase(actor, "move_state_enter")
                self._event(actor, "birth_completed", remaining_raw=actor.born_remaining.raw)
            return False
        _need(actor.state_id == 1, "passive/interrupted birth state needs a separate proven state executor")
        self.callbacks.move_tick(actor, dt)
        self._event(actor, "move_tick")
        return True

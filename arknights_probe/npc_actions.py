"""Bounded native NPC actions, with explicit lifecycle/mode/restore providers.

This executes shipped action lists and synchronous reentrancy. It does not
create a Unity object, choose a target, run a tween, or supply a live Buff
container. The caller must name the dispatched initialized Buff. Native
multi-Buff traversal/deferred mutation remains outside this component.
"""
from __future__ import annotations

from collections.abc import Callable, Iterable
from contextlib import contextmanager
from dataclasses import dataclass
import json
import math
from pathlib import Path

from .fp import FP, binary32, wrap64

EVENT_BUFF_START = 0
EVENT_OWNER_KILLED = 3
EVENT_OWNER_FINISH = 4
EVENT_TAKE_DAMAGE = 10
EVENT_OWNER_REACH_EXIT = 34
DEATH_REASONS = frozenset((2, 3, 5, 8))
OTHER_FINISH_REASON = 7
GE_EPSILON_RAW = 42950


def native_fp_ge(left: FP, right: FP) -> bool:
    """MathUtil.GE(FP,FP): signed >= after wrapped subtraction of EN5."""
    _require(isinstance(left, FP) and isinstance(right, FP), "FP operands are required")
    return left.raw >= wrap64(right.raw - GE_EPSILON_RAW)


class UnverifiedNpcContext(ValueError):
    pass


def _require(value: bool, message: str):
    if not value:
        raise UnverifiedNpcContext(message)


def _ascii(value: str, name="key") -> str:
    _require(type(value) is str and value.isascii(), name + " requires an explicit ASCII string")
    return value


def _uid(value: int):
    _require(type(value) is int and 0 <= value <= 0xffffffff, "UID must be an explicit UInt32")


@dataclass(eq=False)
class NpcEntity:
    """Mutable external BObject identity snapshot; UID changes model recycling.

    unity_exists represents the supplied IsDestroyedOrNull predicate. alive
    is independent: native ObjectPtr validity does not test Entity.alive.
    """
    token: str
    uid: int
    unity_exists: bool
    alive: bool
    is_enemy: bool = True
    is_tile_unit: bool = False
    grid_position: tuple[int, int] | None = None

    def __post_init__(self):
        _uid(self.uid)
        _require(bool(self.token), "Entity identity source is required")
        for x in (self.unity_exists, self.alive, self.is_enemy, self.is_tile_unit):
            _require(type(x) is bool, "Entity predicate inputs must be explicit Boolean values")


@dataclass(frozen=True)
class EntityPtr:
    entity: NpcEntity | None
    captured_uid: int

    def __post_init__(self):
        _uid(self.captured_uid)

    @classmethod
    def capture(cls, entity: NpcEntity | None):
        return cls(entity, entity.uid if entity is not None else 0)

    def resolve(self) -> NpcEntity | None:
        e = self.entity
        if e is None or not e.unity_exists:
            return None
        _uid(e.uid)
        # The original equality admits matching zero UIDs. Alive is not used.
        return e if e.uid == self.captured_uid else None


@dataclass(frozen=True)
class DataPair:
    key: str
    value: float = 0.0
    value_str: str | None = None

    def __post_init__(self):
        _ascii(self.key)
        v = binary32(self.value)
        _require(math.isfinite(v), "Nonfinite Blackboard values are outside this component")
        object.__setattr__(self, "value", v)
        _require(self.value_str is None or type(self.value_str) is str, "valueStr must be String or null")


class NpcBlackboard:
    """Ordered List<DataPair>; copy construction preserves duplicate rows.

    Assign lowercases a key and replaces the first case-insensitive match.
    String Assign replaces the numeric payload with zero; numeric Assign
    replaces valueStr with null. Native lookup scans past nonnumeric matches.
    General CurrentCulture casing is gated: these ASCII operations use an
    explicit invariant-culture fixture, rather than assuming live culture.
    """
    def __init__(self, entries: Iterable[DataPair] = (), *, culture: str = "invariant"):
        _require(culture == "invariant", "Only explicit invariant ASCII Blackboard culture is supported")
        self.culture = culture
        self.entries = list(entries)
        _require(all(isinstance(x, DataPair) for x in self.entries), "Blackboard requires ordered DataPair rows")

    def clone(self):
        return NpcBlackboard(self.entries, culture=self.culture)

    def _assign(self, row: DataPair):
        for i, old in enumerate(self.entries):
            if old.key.lower() == row.key.lower():
                self.entries[i] = row
                return
        self.entries.append(row)

    def assign_number(self, key: str, value: float):
        self._assign(DataPair(_ascii(key).lower(), value, None))

    def assign_string(self, key: str, value: str | None):
        self._assign(DataPair(_ascii(key).lower(), 0.0, value))

    def number(self, key: str, default: float = 0.0) -> float:
        k = _ascii(key).lower()
        if k:
            for row in self.entries:
                if row.key.lower() == k and not row.value_str:
                    return row.value
        return binary32(default)

    def fp(self, key: str, default: FP = FP(0)) -> FP:
        k = _ascii(key).lower()
        if k:
            for row in self.entries:
                if row.key.lower() == k and not row.value_str:
                    return FP.from_float32(row.value)
        return default

    def integer(self, key: str, default: int = 0) -> int:
        k = _ascii(key).lower()
        if k:
            for row in self.entries:
                if row.key.lower() == k and not row.value_str:
                    # Native CRT 0x1804d3200 dispatches ROUNDSD imm9 (floor)
                    # or a scalar floor fallback, then CVTTSD2SI.
                    n = math.floor(row.value)
                    _require(-(1 << 31) <= n < (1 << 31), "Blackboard integer conversion exceeds scoped Int32 range")
                    return n
        return default

    def string(self, key: str, default: str | None = None) -> str | None:
        k = _ascii(key).lower()
        if not k:
            return default
        for row in self.entries:
            if row.key.lower() == k and row.value_str:
                return row.value_str
        return default


def bind_talent_blackboard(entries: Iterable[DataPair], talent_key: str, *, culture="invariant") -> NpcBlackboard:
    """Enemy prefix '{0}.'; OrdinalIgnoreCase strip, numeric pass then string pass.

    This covers a non-Character Enemy's unscaled BasicTalent path. It does not
    activate its Ability, apply character skill scales, or merge talentDelta.
    """
    prefix = _ascii(talent_key, "talent key") + "."
    rows = list(entries)
    result = NpcBlackboard(culture=culture)
    for row in rows:
        if row.key.lower().startswith(prefix.lower()):
            result.assign_number(row.key[len(prefix):], row.value)
    for row in rows:
        if row.key.lower().startswith(prefix.lower()) and row.value_str:
            result.assign_string(row.key[len(prefix):], row.value_str)
    return result


@dataclass(eq=False)
class NpcBuff:
    """Initialized managed Buff fixture. Unlike an Entity, Buff is not Unity.

    unity_exists is retained as an explicit provider-availability gate. Only
    True is admitted; treating a missing registry entry as Unity destruction
    would invent ObjectPtr semantics for this managed class.
    """
    token: str
    uid: int
    template_key: str
    owner: NpcEntity
    source: EntityPtr
    blackboard: NpcBlackboard
    on_event_priority: int
    initialized: bool
    unity_exists: bool = True

    def __post_init__(self):
        _uid(self.uid)
        _require(type(self.initialized) is bool and self.initialized, "Dispatched Buff must be explicitly initialized")
        _require(type(self.on_event_priority) is int and -(1<<31) <= self.on_event_priority < (1<<31), "Native priority must be explicit Int32")
        _require(isinstance(self.owner, NpcEntity) and isinstance(self.source, EntityPtr), "Buff owner/source identity is required")
        _require(isinstance(self.blackboard, NpcBlackboard), "Buff Blackboard is required")
        _require(self.unity_exists is True, "Managed Buff availability must be explicit; unknown removal/registry state is rejected")


@dataclass(frozen=True)
class BuffPtr:
    buff: NpcBuff | None
    captured_uid: int

    def __post_init__(self):
        _uid(self.captured_uid)

    def resolve(self):
        b = self.buff
        if b is None:
            return None
        _require(b.unity_exists is True, "Managed Buff removal/registry state is outside ObjectPtr UID validation")
        return b if b.uid == self.captured_uid else None


def insert_buff_by_priority(current: tuple[BuffPtr, ...], incoming: BuffPtr) -> tuple[BuffPtr, ...]:
    """SortedDoubleBufferedBuffList.Add's immediate-list insertion only.

    High priorities come first. Equal valid priorities retain arrival order.
    Invalid incoming entries append; invalid existing entries are skipped
    while searching backward. This does not implement traversal snapshots or
    pending removals, so callers cannot use it as a whole BuffContainer.
    """
    new = incoming.resolve()
    if new is None:
        return current + (incoming,)
    i = len(current) - 1
    while i >= 0:
        old = current[i].resolve()
        if old is not None and old.on_event_priority >= new.on_event_priority:
            break
        i -= 1
    return current[:i+1] + (incoming,) + current[i+1:]


@dataclass(frozen=True)
class NpcSnapshot:
    source: NpcEntity | None = None
    target: NpcEntity | None = None
    buff: NpcBuff | None = None
    main_target: NpcEntity | None = None
    # Unimplemented modifier/projectile/ability fields are deliberately gated.


class NpcContext:
    def __init__(self, snapshot: NpcSnapshot = NpcSnapshot()):
        self._frames = [(EntityPtr.capture(snapshot.source), EntityPtr.capture(snapshot.target),
                         BuffPtr(snapshot.buff, snapshot.buff.uid if snapshot.buff else 0), snapshot.main_target)]
        self.depth = 0

    @property
    def current(self):
        source, target, buff, main_target = self._frames[-1]
        return NpcSnapshot(source.resolve(), target.resolve(), buff.resolve(), main_target)

    @contextmanager
    def change_guard(self, **changes):
        # _DuplicateAll takes a resolved Snapshot, then pushes new ObjectPtrs
        # from those resolved values. A stale underlying pointer duplicates
        # as null, rather than becoming valid again if its UID is later reused.
        snapshot = self.current
        frame = [EntityPtr.capture(snapshot.source), EntityPtr.capture(snapshot.target),
                 BuffPtr(snapshot.buff, snapshot.buff.uid if snapshot.buff else 0), snapshot.main_target]
        for key, value in changes.items():
            if key in ("source", "target"):
                frame[0 if key == "source" else 1] = EntityPtr.capture(value)
            elif key == "buff":
                frame[2] = BuffPtr(value, value.uid if value else 0)
            elif key == "main_target":
                frame[3] = value
            else:
                raise UnverifiedNpcContext("Unknown context slot")
        self._frames.append(tuple(frame))
        self.depth += 1
        try:
            yield self.current
        finally:
            self._frames.pop()
            self.depth -= 1


def resolve_action_target(snapshot: NpcSnapshot, target_type: str | int) -> NpcEntity | None:
    table = {0:"TARGET", 1:"SOURCE", 2:"BUFF_SOURCE", 3:"BUFF_OWNER", 6:"MAIN_TARGET"}
    if type(target_type) is int:
        _require(target_type in table, "Unsupported action target slot")
        target_type = table[target_type]
    if target_type == "TARGET":
        return snapshot.target
    if target_type == "SOURCE":
        return snapshot.source
    if target_type == "MAIN_TARGET":
        return snapshot.main_target
    _require(snapshot.buff is not None, "BUFF_SOURCE/OWNER requires a valid captured Buff")
    if target_type == "BUFF_SOURCE":
        return snapshot.buff.source.resolve()
    if target_type == "BUFF_OWNER":
        # This is a direct container.owner, independent of Buff source UID.
        return snapshot.buff.owner
    raise UnverifiedNpcContext("Modifier/projectile/mainBuff/ability target resolution is not supported")


@dataclass(frozen=True)
class RestoreRequest:
    target: NpcEntity
    source: NpcEntity
    snapshot: NpcSnapshot
    release_blocker: bool = True
    disable_current_still_pull: bool = True
    reassign_route: bool = True


@dataclass(frozen=True)
class SummonRequest:
    host: NpcEntity
    buff_source: NpcEntity
    enemy_key: str
    host_grid_position: tuple[int, int]
    blackboard: NpcBlackboard
    snapshot: NpcSnapshot


@dataclass(frozen=True)
class LifeRequest:
    delta: int
    source: NpcEntity | None
    branch: int
    is_reach_exit: bool
    snapshot: NpcSnapshot


@dataclass
class NpcCallbacks:
    restore_to: Callable[[RestoreRequest], bool] | None = None
    set_disappeared: Callable[[NpcEntity, bool], None] | None = None
    finish_buffs: Callable[[NpcEntity, str], None] | None = None
    finish_no_reason: Callable[[NpcEntity], None] | None = None
    modify_life: Callable[[LifeRequest], bool] | None = None
    clear_buffs: Callable[[NpcEntity], None] | None = None
    schedule_summon: Callable[[SummonRequest], None] | None = None


@dataclass(frozen=True)
class ActionNode:
    name: str
    execute: Callable[[], bool]
    execute_condition: int = 1
    allowed_source: int = 0x3f


@dataclass(frozen=True)
class ActionRunResult:
    result: bool
    executed: tuple[str, ...]
    stopped_before: str | None
    snapshot: NpcSnapshot


def check_execute(condition: int, previous: bool) -> bool:
    if condition == 0:
        return True
    if condition == 1:
        return previous
    if condition == 2:
        return not previous
    return False


def run_action_list(nodes: Iterable[ActionNode], snapshot: NpcSnapshot = NpcSnapshot(), *, source_type=1) -> ActionRunResult:
    previous = True
    ran = []
    for node in nodes:
        if (node.allowed_source & source_type) != source_type or not check_execute(node.execute_condition, previous):
            return ActionRunResult(False, tuple(ran), node.name, snapshot)
        previous = node.execute()
        _require(type(previous) is bool, "Action callback must supply an explicit Boolean result")
        ran.append(node.name)
    return ActionRunResult(previous, tuple(ran), None, snapshot)


def _resource_templates():
    p = Path(__file__).resolve().parents[1] / "evidence/npc_actions/resource_inputs.json"
    return json.loads(p.read_text("utf8"))["templates"]


class NpcActionRuntime:
    """A selected initialized Buff/event dispatcher, not a scene event registry."""
    def __init__(self, context: NpcContext, callbacks: NpcCallbacks, *,
                 no_hotfix: bool, mode: str, dispatch_source: str):
        _require(no_hotfix is True, "Ordinary NPC actions require explicit no-hotfix context")
        _require(mode == "default_noncoop", "NPC life node's coop/Rogue dynamic mode must use a separate proven backend")
        _require(bool(dispatch_source), "Explicit external Buff dispatch source is required")
        self.context, self.callbacks = context, callbacks
        self.dispatch_source = dispatch_source
        self.trace: list[tuple] = []
        self.templates = _resource_templates()

    def _callback(self, name: str):
        callback = getattr(self.callbacks, name)
        _require(callable(callback), name + " requires an explicit verified/fixture provider")
        return callback

    def _events(self, buff: NpcBuff):
        _require(buff.initialized and buff.unity_exists, "Buff validity/membership must be supplied")
        _require(buff.template_key in self.templates, "Unknown Buff template is outside the NPC action closure")
        return {x["key"]: json.loads(x["value"]["SerializedState"])
                for x in self.templates[buff.template_key]["raw"]["eventToActions"]["_items"]}

    def run_buff_event(self, buff: NpcBuff, event: int, *, set_owner_as_target=True) -> ActionRunResult:
        actions = self._events(buff).get(event, ())
        if not actions:
            return ActionRunResult(True, (), None, self.context.current)
        _require(buff.owner.unity_exists, "Native RunActions requires an existing container owner")
        _require(not buff.owner.is_tile_unit, "Tile-unit set_tile context is outside this component")
        changes = {"buff":buff, "source":buff.source.resolve()}
        if set_owner_as_target:
            changes["target"] = buff.owner
        with self.context.change_guard(**changes) as snapshot:
            self.trace.append(("event", buff.token, event, self.context.depth))
            nodes = tuple(self._node(action, buff.blackboard, snapshot) for action in actions)
            result = run_action_list(nodes, snapshot)
            self.trace.append(("return", buff.token, event, result.result, result.stopped_before))
            return result

    def owner_finish(self, buff: NpcBuff, reason: int, *, finish_source: NpcEntity | None = None) -> tuple[ActionRunResult, ...]:
        """Buff.OnOwnerFinish event selection; caller owns lifecycle and membership."""
        _require(type(reason) is int, "Explicit FinishReason is required")
        events = self._events(buff)
        order = []
        if reason in DEATH_REASONS:
            order.append(3)
            if reason != 8 and finish_source is not None and finish_source.unity_exists:
                order.append(29)
        elif reason == 1:
            order.append(34)
        order.append(4)
        results = []
        for event in order:
            if events.get(event):
                # Native OnOwnerFinish pushes m_mainTarget (+0x50), not source.
                with self.context.change_guard(main_target=finish_source):
                    results.append(self.run_buff_event(buff, event))
        return tuple(results)

    def _node(self, action: dict, bb: NpcBlackboard, snapshot: NpcSnapshot):
        name = action["$type"].split("+")[-1]
        if name == "IfNot":
            return ActionNode(name, lambda: True, 2)
        def entity(which: str):
            return resolve_action_target(snapshot, which)
        def execute():
            if name == "FilterByBlackboardValue":
                _require(action["_condType"] == "GE" and not action["_anotherBuff"] and not action["_anotherKeyToCompare"] and not action["_blackboardKeyFromBb"], "Unsupported Blackboard filter shape")
                target = entity(action["_targetType"])
                if target is None or not target.unity_exists:
                    return False
                left = bb.fp(action["_blackboardKey"])
                right = FP.from_int32(action["_valueToCompare"])
                return native_fp_ge(left, right)
            if name == "ForceSetToSourcePosition":
                target, source = entity(action["_targetType"]), entity(action["_sourceType"])
                if target is None or not target.unity_exists or not target.is_enemy:
                    return False
                _require(source is not None and source.unity_exists, "Restore source existence requires proof")
                result = self._callback("restore_to")(RestoreRequest(target, source, snapshot))
                _require(type(result) is bool, "Restore provider must return an explicit native action result")
                return result
            if name == "SetDisappear":
                target = entity(action["_targetType"])
                if target is None or not target.is_enemy or not target.unity_exists:
                    return False
                self._callback("set_disappeared")(target, action["_isDisappear"])
                return True
            if name == "FinishBuffsById":
                _require(not action["_loadFromBlackboard"] and not action["_checkBuffSource"] and not action["_finishHostBuff"] and not action["_excludeThisBuff"] and not action["_decCntIfStack"], "Only the reviewed FinishBuffsById shape is supported")
                target = entity(action["_targetType"])
                if target is not None and target.unity_exists:
                    self._callback("finish_buffs")(target, action["_buffKey"])
                return True
            if name == "InstantKill":
                _require(action["_noReason"] and not action["_killSource"] and not action["_withdrawIfRallyPoint"] and not action["_markReachExit"], "Only noReason Finish7 is supported")
                target = entity(action["_targetType"])
                if target is None or not target.unity_exists:
                    return False
                # The callback must deliver synchronous OnFinish before returning.
                self._callback("finish_no_reason")(target)
                return target.alive
            if name == "AssignValueToBB":
                _require(not action["_copyFromKey"] and not action["_assignString"], "Only literal numeric lock assignment is supported")
                if not action["_blackboardKey"]:
                    return False
                bb.assign_number(action["_blackboardKey"], action["_value"])
                return True
            if name == "ClearAllBuffs":
                _require(not action["_retainedBuffsWhenClear"] and not action["_alsoRemoveDurableBuff"], "Unsupported Buff clear shape")
                target = entity(action["_targetType"])
                if target is None or not target.unity_exists or not target.alive:
                    return False
                self._callback("clear_buffs")(target)
                return True
            if name == "ModifyLifePoint":
                source = entity(action["_sourceType"])
                delta = bb.integer(action["_blackboardKey"])
                if action["_isSub"]:
                    delta = ((-delta + (1<<31)) & 0xffffffff) - (1<<31)
                result = self._callback("modify_life")(LifeRequest(delta, source, 0, action["_isReachExit"], snapshot))
                _require(type(result) is bool, "ModifyLifePoint provider must return Boolean")
                return result
            if name == "SummonEnemiesFollowMyRouteWithBuff":
                host = entity(action["_source"])
                source = entity(action["_buffSource"])
                if host is None or not host.unity_exists or not host.is_enemy:
                    return False
                _require(source is not None and source.unity_exists, "Summon Buff source must resolve")
                _require(host.grid_position is not None, "Explicit host root GridPosition is required")
                key = action["_enemyKey"] or bb.string("enemy_key")
                _require(bool(key), "Summon enemy_key must be bound or supplied")
                _require(all(row.key == "enemy_key" for row in bb.entries), "Only the reviewed enemy_key Blackboard is admitted; count/random/delay overrides require separate recovery")
                _require(action["_summonCount"] == 1 and action["_delayTime"] == 0.0, "Only reviewed count1/delay0 NPC plan is supported")
                self._callback("schedule_summon")(SummonRequest(host, source, key, host.grid_position, bb.clone(), snapshot))
                return True
            raise UnverifiedNpcContext("Unsupported NPC action: " + name)
        return ActionNode(name, execute)

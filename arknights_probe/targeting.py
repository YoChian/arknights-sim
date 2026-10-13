"""Recovered altar targeting pieces with explicit physics/status context.

Range declarations produce native collider boxes, not hit decisions. Unity
Physics2D overlap results and runtime status/provider outcomes must be supplied;
missing context is never interpreted as an empty range or a rejected target.
"""
from __future__ import annotations

from dataclasses import dataclass
from collections.abc import Mapping
from types import MappingProxyType
from .fp import FP, binary32
from .movement import LocalVector2


class UnverifiedTargetContext(ValueError):
    """A required range, status, provider or physics branch is unknown."""


def _require(condition, message):
    if not condition:
        raise UnverifiedTargetContext(message)


def _uint(value, name, maximum=0xffffffff):
    _require(type(value) is int and 0 <= value <= maximum, name + " must be an explicit bounded unsigned integer")
    return value


def _bool(value, name):
    _require(type(value) is bool, name + " must be an explicit bool")
    return value


def _source(value):
    _require(isinstance(value, str) and bool(value.strip()), "Input provenance/context source is required")
    return value


@dataclass(frozen=True)
class RangeBox:
    """Native ObscuredRect values before Unity transform/bounds calculation."""
    minimum: LocalVector2
    size: LocalVector2

    @property
    def center(self) -> LocalVector2:
        return LocalVector2(binary32(binary32(self.size.x * binary32(.5)) + self.minimum.x),
                            binary32(binary32(self.size.y * binary32(.5)) + self.minimum.y))

    def as_dict(self):
        return {"minimum": [self.minimum.x, self.minimum.y],
                "size": [self.size.x, self.size.y], "center": [self.center.x, self.center.y]}


def rotate_range_grid(grid: tuple[int, int], current: int, target: int = 0) -> tuple[int, int]:
    """GridPosition.RotateVector 28061; row/column, current -> target."""
    _require(type(grid) is tuple and len(grid) == 2 and all(type(x) is int and abs(x) <= 32767 for x in grid),
             "Range grid requires bounded native row/column integers")
    _uint(current, "Current direction", 3)
    _uint(target, "Target direction", 3)
    row, col = grid
    turn = (target - current + 4) % 4
    return ((row, col), (-col, row), (-row, -col), (col, -row))[turn]


def construct_range_boxes(grids, *, direction: int) -> tuple[RangeBox, ...]:
    """RangeData native rectangle cover, including intentional overlaps.

    Sort is signed row then column; coordinates are bounded so subtraction
    cannot overflow. _TryFindBoundingBox grows right, then grows up using the
    ALL set, removing visited entries only from the REMAINING set. It can reuse
    previously covered cells. No assumed one-cell collider expansion is added.
    """
    _require(isinstance(grids, (list, tuple)) and len(grids) <= 4096, "Finite explicit range grid collection required")
    rotated = sorted(rotate_range_grid(tuple(grid), direction, 0) for grid in grids)
    all_cells, remaining = set(rotated), set(rotated)
    boxes = []
    for anchor in rotated:
        if anchor not in remaining:
            continue
        row, col = anchor
        end_row, end_col = row, col
        remaining.discard(anchor)
        while (row, end_col + 1) in all_cells:
            end_col += 1
            remaining.discard((row, end_col))
        while all((end_row + 1, c) in all_cells for c in range(col, end_col + 1)):
            end_row += 1
            for c in range(col, end_col + 1):
                remaining.discard((end_row, c))
        boxes.append(RangeBox(LocalVector2(binary32(col - .5), binary32(row - .5)),
                              LocalVector2(end_col - col + 1, end_row - row + 1)))
    return tuple(boxes)


@dataclass(frozen=True)
class SourceMotionSnapshot:
    """_InitSourceSnapshot captures motion independently of later PtrObjRef validity."""
    motion: int

    def __post_init__(self):
        _uint(self.motion, "Captured source motion", 2)


def resolve_source_motion(*, reference_valid: bool, current_motion: int | None,
                          captured: SourceMotionSnapshot | None) -> tuple[bool, int]:
    """75075: valid reference -> live motion; otherwise captured motion or E_NUM."""
    if _bool(reference_valid, "Source reference validity"):
        _require(current_motion is not None, "Native-valid source must resolve to current motion")
        return True, _uint(current_motion, "Current source motion", 2)
    if captured is None:
        return False, 2
    _require(isinstance(captured, SourceMotionSnapshot), "Explicit source snapshot required")
    return True, captured.motion


@dataclass(frozen=True)
class WorldBounds2D:
    """XY of a supplied native SafeBounds, not a collider-overlap simulation."""
    minimum: LocalVector2
    maximum: LocalVector2
    source: str

    def __post_init__(self):
        _source(self.source)
        _require(isinstance(self.minimum, LocalVector2) and isinstance(self.maximum, LocalVector2), "Explicit world bounds vectors required")
        _require(self.minimum.x <= self.maximum.x and self.minimum.y <= self.maximum.y, "Inverted world bounds")

    def contains(self, world_point: LocalVector2) -> bool:
        # MapUtil.InBounds 78322 checks four inclusive inequalities, no epsilon.
        _require(isinstance(world_point, LocalVector2), "Explicit world-space point required")
        return (self.minimum.x <= world_point.x <= self.maximum.x and
                self.minimum.y <= world_point.y <= self.maximum.y)


@dataclass(frozen=True)
class TargetSnapshot:
    """Frozen entity state for this synchronous selection call.

    Nullable booleans mean unknown; a needed predicate rejects rather than
    guessing false. Category and motion are the native virtual/getter results,
    not inferred from enemy IDs, Born state or declared grid coordinates.
    """
    uid: int
    side: int
    motion: int
    category: int
    map_layer: int
    alive: bool | None
    destroyed: bool
    ally_target_free: bool | None
    heal_free: bool | None
    camouflage: bool | None
    source: str

    def __post_init__(self):
        _uint(self.uid, "BObject.instanceUid")
        _uint(self.side, "Entity side", 7)
        _uint(self.motion, "changeableMotionMode", 2)
        _uint(self.category, "Entity category", 7)
        _uint(self.map_layer, "Map layer", 0x7fffffff)
        _bool(self.destroyed, "Unity object destroyed")
        for name in ("alive", "ally_target_free", "heal_free", "camouflage"):
            _require(getattr(self, name) is None or type(getattr(self, name)) is bool,
                     name + " requires explicit bool or unknown None")
        _source(self.source)


@dataclass(frozen=True)
class ColliderOverlapSnapshot:
    """Ordered Physics2D result for one range collider, after collider->Entity lookup."""
    hits: tuple[TargetSnapshot | None, ...]
    destroyed: bool
    source: str

    def __post_init__(self):
        _require(type(self.hits) is tuple and all(t is None or isinstance(t, TargetSnapshot) for t in self.hits), "Explicit ordered collider-to-Entity overlap results required")
        _bool(self.destroyed, "Range collider destroyed")
        _source(self.source)


@dataclass(frozen=True)
class OverlapQuerySnapshot:
    colliders: tuple[ColliderOverlapSnapshot, ...]
    layer_mask: int
    source: str

    def __post_init__(self):
        _require(type(self.colliders) is tuple and all(isinstance(c, ColliderOverlapSnapshot) for c in self.colliders), "Ordered range-collider query snapshot required")
        _uint(self.layer_mask, "Physics2D query layer mask")
        _source(self.source)


@dataclass(frozen=True)
class PredicateSnapshot:
    """A supplied native provider/delegate result keyed by unsigned instanceUid."""
    outcomes: Mapping[int, bool | None]
    source: str

    def __post_init__(self):
        _source(self.source)
        _require(isinstance(self.outcomes, Mapping), "Explicit predicate outcomes required")
        copied = {}
        for uid, value in self.outcomes.items():
            _uint(uid, "Predicate UID")
            _require(value is None or type(value) is bool, "Predicate outcome must be bool or unknown None")
            copied[uid] = value
        object.__setattr__(self, "outcomes", MappingProxyType(copied))

    def resolve(self, uid: int, name: str) -> bool:
        return _bool(self.outcomes.get(uid), f"{name} for UID {uid}; provider context is unknown")


@dataclass(frozen=True)
class AltarSelectorContext:
    """Actual sktok_ore prefab branch with supplied owner/runtime masks.

    Fixed prefab: side BOTH, motion ALL, category DEFAULT, ignoreTargetFree,
    no profession/unit/abnormal/taunt/owner-exclude filter, ALL postfilter.
    Absolute target-side/physics-layer masks must come from native initialization;
    this component does not invent BattleConsts/GameLayers static arrays.
    """
    source_side: int
    source_map_layer: int
    source_purpose_mask: int
    absolute_target_side_mask: int
    query_layer_mask: int
    collider_count: int
    opposite_side_mask: int
    ability_ignores_camouflage: bool
    deterministic: bool
    hit_range: PredicateSnapshot
    has_custom_validator: bool
    custom_validator: PredicateSnapshot | None
    excluded_uids: frozenset[int]
    source: str

    def __post_init__(self):
        for name in ("source_side", "absolute_target_side_mask", "opposite_side_mask"):
            _uint(getattr(self, name), name, 7)
        _uint(self.source_map_layer, "Owner map layer", 0x7fffffff)
        _uint(self.source_purpose_mask, "Ability purpose mask", 3)
        _uint(self.query_layer_mask, "Initialized Physics2D layer mask")
        _uint(self.collider_count, "Actual cached range-collider count", 4096)
        _bool(self.ability_ignores_camouflage, "Ability force-ignore camouflage")
        _bool(self.deterministic, "Battle deterministic branch")
        _bool(self.has_custom_validator, "Custom validator presence")
        _require(isinstance(self.hit_range, PredicateSnapshot), "Entity.IsInHitRange provider snapshot required")
        _require(not self.has_custom_validator or isinstance(self.custom_validator, PredicateSnapshot), "Present custom validator needs explicit results")
        _require(self.has_custom_validator or self.custom_validator is None, "Absent validator must not carry results")
        _require(type(self.excluded_uids) is frozenset, "Explicit frozen AdvancedSelector exclusion set required")
        for uid in self.excluded_uids:
            _uint(uid, "Excluded UID")
        _source(self.source)


@dataclass(frozen=True)
class AllPostFilterSnapshot:
    """Explicit ALL filter output; no guessed stable createdTime ordering.

    This adapter accepts an explicit complete permutation of admitted targets.
    It does not prove native ALL preserves membership: its SortedSet comparator,
    near-equal/tie and extra-mode behavior remain external. A changed membership
    or mutable-target callback requires a broader closure.
    """
    input_uids: tuple[int, ...]
    output_uids: tuple[int, ...]
    source: str

    def __post_init__(self):
        _require(type(self.input_uids) is tuple and type(self.output_uids) is tuple, "Explicit ALL input/output order tuples required")
        for uid in self.input_uids + self.output_uids:
            _uint(uid, "ALL UID")
        _source(self.source)


@dataclass(frozen=True)
class TargetSelection:
    hits: tuple[TargetSnapshot, ...]
    collector_uids: tuple[int, ...]
    decisions: tuple[dict, ...]
    capped: bool
    context_source: str
    query_source: str
    postfilter_source: str

    def as_dict(self):
        return {"hit_uids": [t.uid for t in self.hits], "collector_uids": list(self.collector_uids),
                "decisions": [dict(d) for d in self.decisions], "capped_at_128": self.capped,
                "context_source": self.context_source, "query_source": self.query_source,
                "postfilter_source": self.postfilter_source,
                "scope": "sktok_ore static admission with external Physics2D overlaps, HitRange/provider and ALL order snapshots",
                "physics_overlap_generated": False, "native_all_order_generated": False,
                "runtime_battle_validated": False, "battle_ready": False,
                "remaining_gaps": ["Unity Physics2D target-collider geometry/touch tolerance/query order and synchronization",
                                   "ALL SortedSet createdTime weight/gap/tie and extra-mode ordering",
                                   "live source masks, hit-range providers, camouflage/status and hotfix state"]}


def _altar_admission(target: TargetSnapshot, context: AltarSelectorContext) -> str | None:
    # Box2d uses VerifyTargetWithoutCheckingTargetSide; side was selected by
    # Physics2D's layer mask. Reapplying an entity-side test here is incorrect.
    if not (3 & (1 << target.motion)):
        return "motion_mask"
    if not (1 & target.category):
        return "category_mask"
    # ignoreTargetFree=true/onlyIgnoreSome=false skips targetFree immunity path.
    # ignoreAllyTargetFree=false still applies when source-side is nonzero.
    if context.source_side and target.side == context.source_side:
        if _bool(target.ally_target_free, f"isAllyTargetFree for UID {target.uid}"):
            return "ally_target_free"
    if context.source_purpose_mask & 2:
        if _bool(target.heal_free, f"isHealFree for UID {target.uid}"):
            return "heal_free"
    # TargetSelector.ValidateTarget default ignoreMapLayer/ignoreHitRange=false.
    if target.map_layer != context.source_map_layer:
        return "map_layer"
    if not context.hit_range.resolve(target.uid, "Entity.IsInHitRange"):
        return "hit_range_provider"
    if not context.ability_ignores_camouflage:
        camouflage = _bool(target.camouflage, f"isCamouflage for UID {target.uid}")
        if camouflage and (target.side & context.opposite_side_mask) == target.side:
            return "enemy_camouflage"
    if context.has_custom_validator and not context.custom_validator.resolve(target.uid, "Custom target validator"):
        return "custom_validator"
    if target.uid in context.excluded_uids:
        return "advanced_exclusion_set"
    return None


def select_altar_targets(query: OverlapQuerySnapshot, context: AltarSelectorContext,
                         postfilter: AllPostFilterSnapshot) -> TargetSelection:
    """Box2d collection -> optional unsigned UID sort -> explicit ALL filter.

    Hit order inside each collider and range-collider order are physics inputs.
    Deduplication happens only after admission, and the 128th admitted target
    ends collection *before* deterministic sorting. Unknown required predicates
    and mismatched postfilter snapshots reject the whole call.
    """
    _require(isinstance(query, OverlapQuerySnapshot) and isinstance(context, AltarSelectorContext), "Explicit targeting/physics context required")
    _require(isinstance(postfilter, AllPostFilterSnapshot), "ALL postfilter ordering is not closed; explicit output/source snapshot required")
    _require(query.layer_mask == context.query_layer_mask, "Overlap query used a different initialized native layer mask")
    _require(len(query.colliders) == context.collider_count, "Overlap snapshot omitted or added cached range colliders")
    selected, seen, state_by_uid, decisions = [], set(), {}, []
    capped = False
    for collider_index, collider in enumerate(query.colliders):
        if collider.destroyed:
            decisions.append({"collider_index": collider_index, "hit_index": None, "uid": None, "reason": "range_collider_destroyed"})
            continue
        for hit_index, target in enumerate(collider.hits):
            reason = None
            uid = target.uid if target is not None else None
            if target is not None and target.uid:
                if target.uid in state_by_uid:
                    _require(state_by_uid[target.uid] == target, "One UID has conflicting mutable snapshots within synchronous selection")
                state_by_uid[target.uid] = target
            if target is None:
                reason = "collider_has_no_live_entity"
            elif target.destroyed:
                reason = "entity_destroyed"
            elif target.uid == 0:
                reason = "instance_uid_invalid"
            elif not _bool(target.alive, f"Entity.alive for UID {target.uid}"):
                reason = "entity_not_alive"
            else:
                if target.uid in seen:
                    reason = "duplicate_admitted_uid"
                else:
                    reason = _altar_admission(target, context)
            decisions.append({"collider_index": collider_index, "hit_index": hit_index, "uid": uid,
                              "reason": reason or "admitted"})
            if reason is None:
                selected.append(target)
                seen.add(target.uid)
                if len(selected) == 128:
                    capped = True
                    break
        if capped:
            break
    if context.deterministic:
        selected.sort(key=lambda t: t.uid)  # exact UInt32 order, dedup keys unique
    collector = tuple(t.uid for t in selected)
    _require(postfilter.input_uids == collector, "ALL snapshot input order does not match collector output")
    _require(len(postfilter.output_uids) == len(collector) and len(set(postfilter.output_uids)) == len(collector)
             and set(postfilter.output_uids) == set(collector),
             "Immutable ALL scope requires a complete UID permutation, without lost/unknown/duplicate targets")
    by_uid = {t.uid: t for t in selected}
    return TargetSelection(tuple(by_uid[uid] for uid in postfilter.output_uids), collector,
                           tuple(decisions), capped, context.source, query.source, postfilter.source)

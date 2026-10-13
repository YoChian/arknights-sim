"""Source-backed physics declarations/query arguments; external Unity results.

This module performs no overlap, collider world-bounds update, TransformVector,
CheckConsistency, Simulate, or SyncTransforms operation. It binds their explicit
snapshots to recovered native query parameters and battle-frame phases.
"""
from __future__ import annotations

from collections.abc import Mapping
from dataclasses import dataclass
import hashlib
import json
import math
from pathlib import Path
import struct
from types import MappingProxyType

from .fp import binary32
from .targeting import TargetSnapshot, ColliderOverlapSnapshot, OverlapQuerySnapshot

NATIVE_BUFFER_CAPACITY = 128
PHASES = ("objects_fixed", "map_fixed", "scripts_and_operations", "manual_simulate",
          "after_physics_callbacks", "coroutines", "registered_ticks", "global_environment", "objects_late")


class UnverifiedPhysicsContext(ValueError):
    pass


def _need(value, message):
    if not value:
        raise UnverifiedPhysicsContext(message)


def _source(value):
    _need(isinstance(value, str) and bool(value.strip()), "Physics input needs explicit source attribution")


def _int(value, lower, upper, name):
    _need(type(value) is int and lower <= value <= upper, f"{name} outside native integer scope")


def _bool(value, name):
    _need(type(value) is bool, f"Explicit {name} bool required")


def _float(value):
    _need(type(value) in (int, float), "Explicit finite Single value required")
    try:
        result = binary32(value)
    except (OverflowError, ValueError):
        raise UnverifiedPhysicsContext("Single overflow is outside the finite query scope") from None
    _need(math.isfinite(result), "Nonfinite geometric query input is outside scope")
    _need(result == 0 or abs(result) >= 2.0**-126,
          "Subnormal geometric input/intermediate needs verified native MXCSR/FTZ/DAZ context")
    return result


def _vector(value, width):
    _need(type(value) is tuple and len(value) == width, f"Explicit {width}-component tuple required")
    return tuple(_float(x) for x in value)


def _bits(value):
    return f"0x{struct.unpack('<I', struct.pack('<f', value))[0]:08x}"


def _freeze(value):
    if isinstance(value, dict):
        return MappingProxyType({k: _freeze(v) for k, v in value.items()})
    if isinstance(value, list):
        return tuple(_freeze(v) for v in value)
    return value


@dataclass(frozen=True)
class PrefabColliderDeclaration:
    path_id: int
    collider_type: str
    layer: int
    active_self: bool
    enabled: bool
    is_trigger: bool
    transform_chain: tuple[int, ...]
    fields: Mapping
    source: str


@dataclass(frozen=True)
class PrefabPhysicsDeclaration:
    name: str
    root_transform_path_id: int
    transforms: Mapping
    colliders: tuple[PrefabColliderDeclaration, ...]
    rigidbodies: tuple[Mapping, ...]
    source: str
    circle_overlap_fixed_components: tuple[Mapping, ...] = ()

    def infer_world_pose(self):
        raise UnverifiedPhysicsContext("Prefab local pose does not establish instantiated parent/world pose or engine collider bounds")


def load_prefab_physics_catalog(path: Path | str) -> Mapping[str, PrefabPhysicsDeclaration]:
    """Load pinned derived declarations; the owning evidence manifest pins JSON.

    AB source pins are checked as well. Runtime layers, body attachment, flags
    and world transforms are not filled from these serialized initial values.
    """
    path = Path(path).resolve()
    raw = path.read_bytes()
    data = json.loads(raw)
    _need(data.get("format") == "selected_prefab_physics_declarations_v1", "Unknown physics declaration format")
    pins = data["input_pins"] + [r["source_pin"] for r in data["prefabs"]]
    for pin in {x["path"]: x for x in pins}.values():
        with Path(pin["path"]).open("rb") as stream:
            actual = hashlib.file_digest(stream, "sha256").hexdigest()
        _need(actual == pin["sha256"], f"Serialized source changed: {pin['path']}")
    source = f"{path} sha256={hashlib.sha256(raw).hexdigest()}; serialized declaration only"
    catalog = {}
    for row in data["prefabs"]:
        _need(not row["unresolved_references"], "Prefab hierarchy has unresolved references")
        nodes = {n["transform"]["path_id"]: n for n in row["nodes"]}
        _need(len(nodes) == len(row["nodes"]), "Duplicate serialized Transform identity")
        by_go = {n["game_object"]["path_id"]: n["transform"]["path_id"] for n in row["nodes"]}
        root = row["root_transform_path_id"]
        _need(root in nodes, "Missing root Transform")
        colliders = []
        for col in row["colliders"]:
            chain = []
            current = by_go[col["game_object_path_id"]]
            while True:
                _need(current not in chain and len(chain) < 128, "Cyclic/oversized Transform parent chain")
                chain.append(current)
                father = nodes[current]["transform"]["fields"]["m_Father"]
                _need(father["m_FileID"] == 0, "External instantiated parent is unknown")
                if father["m_PathID"] == 0:
                    _need(current == root, "Collider hierarchy terminates outside this prefab root")
                    break
                _need(father["m_PathID"] in nodes, "Missing local Transform parent")
                current = father["m_PathID"]
            fields = col["fields"]
            _int(col["game_object_layer"], 0, 31, "Serialized layer")
            _need(col["active_self"] in (0, 1), "Unknown serialized GameObject active flag")
            _need(fields["m_Enabled"] in (0, 1), "Unknown serialized collider enabled flag")
            _bool(fields["m_IsTrigger"], "serialized collider trigger")
            colliders.append(PrefabColliderDeclaration(col["path_id"], col["type"], col["game_object_layer"],
                bool(col["active_self"]), bool(fields["m_Enabled"]), fields["m_IsTrigger"],
                tuple(reversed(chain)), _freeze(fields), source + "; " + row["name"] + "/" + str(col["path_id"])))
        _need(row["name"] not in catalog, "Duplicate prefab name")
        catalog[row["name"]] = PrefabPhysicsDeclaration(row["name"], root, _freeze(nodes), tuple(colliders),
            tuple(_freeze(x) for x in row["rigidbodies"]), source,
            tuple(_freeze(x) for x in row["rule_components"] if x["class_name"] == "CircleColliderOverlapFixed"))
    return MappingProxyType(catalog)


@dataclass(frozen=True)
class PhysicsEpoch:
    frame: int
    phase: str
    transform_revision: int
    scene_revision: int
    simulation_mode: int
    auto_sync_transforms: bool
    queries_hit_triggers: bool
    hotfixes_absent: bool
    source: str

    def __post_init__(self):
        _int(self.frame, 0, 0x7fffffff, "Frame within non-wrapped probe scope")
        _need(self.phase in PHASES, "Unknown battle physics phase")
        _int(self.transform_revision, 0, 0x7fffffff, "Transform revision")
        _int(self.scene_revision, 0, 0x7fffffff, "Scene revision")
        _int(self.simulation_mode, 0, 2, "SimulationMode2D")
        for key in ("auto_sync_transforms", "queries_hit_triggers", "hotfixes_absent"):
            _bool(getattr(self, key), key)
        _need(self.hotfixes_absent, "Active hotfix path has not been reconstructed")
        _need(self.simulation_mode == 2 or self.phase not in ("manual_simulate", "after_physics_callbacks"),
              "BC does not manually simulate on the facade automatic branch")
        _source(self.source)

    def as_dict(self):
        return dict(self.__dict__)


def battle_physics_phases(*, simulation_mode: int, hotfixes_absent: bool, source: str):
    """Recovered BC.OnTick subsequence, not a complete engine event loop.

    Cost/deck/UI/dialog and other calls are outside these query phase labels.
    Revision numbers are caller diagnostic stamps, not recovered Unity fields.
    No simulation or implicit engine synchronization is performed here.
    """
    _int(simulation_mode, 0, 2, "SimulationMode2D")
    _bool(hotfixes_absent, "no-hotfix context")
    _need(hotfixes_absent, "Unknown BC hotfix tick path")
    _source(source)
    return PHASES if simulation_mode == 2 else tuple(x for x in PHASES if x not in ("manual_simulate", "after_physics_callbacks"))


@dataclass(frozen=True)
class UnityBoundsSnapshot:
    collider_key: str
    center: tuple[float, float, float]
    extents: tuple[float, float, float]
    epoch: PhysicsEpoch
    source: str
    runtime_class: str

    def __post_init__(self):
        _source(self.collider_key)
        object.__setattr__(self, "center", _vector(self.center, 3))
        object.__setattr__(self, "extents", _vector(self.extents, 3))
        _need(isinstance(self.epoch, PhysicsEpoch), "Bounds need an explicit engine state epoch")
        _source(self.source)
        _source(self.runtime_class)

    def minimum(self):
        return tuple(_float(c-e) for c, e in zip(self.center, self.extents))

    def maximum(self):
        return tuple(_float(c+e) for c, e in zip(self.center, self.extents))


@dataclass(frozen=True)
class UnityVectorSnapshot:
    value: tuple[float, float, float]
    epoch: PhysicsEpoch
    source: str

    def __post_init__(self):
        object.__setattr__(self, "value", _vector(self.value, 3))
        _need(isinstance(self.epoch, PhysicsEpoch), "Vector needs an explicit engine state epoch")
        _source(self.source)


def range_query_transform_contract(saved_local: UnityVectorSnapshot, query_world: UnityVectorSnapshot,
                                   *, source: str) -> dict:
    """Normal-return DoFindTargets pose operations; no transform is executed.

    Both the MapToWorldPosition output and Unity local-position getter value
    remain explicit. The restored position uses the local setter, not world.
    The native exceptional path has no proven finally-based restoration.
    """
    _need(isinstance(saved_local, UnityVectorSnapshot) and isinstance(query_world, UnityVectorSnapshot),
          "Explicit saved-local and MapToWorld output snapshots required")
    _need(saved_local.epoch.frame == query_world.epoch.frame and saved_local.epoch.phase == query_world.epoch.phase,
          "Pose snapshots belong to different frame/query phases")
    _source(source)
    return {"operations": ["get_localPosition", "set_position_world", "FindTargets_DISPOSE", "set_localPosition_saved"],
            "saved_local_bits": [_bits(x) for x in saved_local.value],
            "query_world_bits": [_bits(x) for x in query_world.value],
            "query_epoch": query_world.epoch.as_dict(), "input_sources": [saved_local.source, query_world.source],
            "normal_return_only": True, "exception_restore_validated": False,
            "engine_transform_executed": False, "world_bounds_generated": False, "source": source}


def radius_from_transformed_vector(vector: tuple[float, float, float]) -> float:
    """Native GetWorldRadius magnitude after external TransformVector(r,0,0).

    MULSS, two ADDSS, CVTSS2SD, SQRTSD/P(D), then CVTSD2SS. The transform itself
    is not approximated by lossyScale or composed from prefab local transforms.
    """
    x, y, z = _vector(vector, 3)
    square = _float(_float(_float(x*x) + _float(y*y)) + _float(z*z))
    return _float(math.sqrt(square))


def legacy_filter_initial_bytes(layer_mask: int, queries_hit_triggers: bool) -> bytes:
    """28-byte pre-CheckConsistency native ContactFilter2D declaration."""
    _int(layer_mask, -0x80000000, 0x7fffffff, "LayerMask Int32")
    _bool(queries_hit_triggers, "queriesHitTriggers")
    return struct.pack("<6B2xiffff", int(queries_hit_triggers), 1, 1, 0, 0, 0,
                       layer_mask, -math.inf, math.inf, 0.0, 0.0)


@dataclass(frozen=True)
class ContactFilterSnapshot:
    payload: bytes
    source: str

    def __post_init__(self):
        _need(type(self.payload) is bytes and len(self.payload) == 28,
              "Explicit post-CheckConsistency 28-byte ContactFilter2D payload required")
        _need(all(x in (0, 1) for x in self.payload[:6]), "Invalid native bool flags")
        _source(self.source)

    def as_dict(self):
        flags = ("useTriggers", "useLayerMask", "useDepth", "useOutsideDepth", "useNormalAngle", "useOutsideNormalAngle")
        result = {key: bool(self.payload[i]) for i, key in enumerate(flags)}
        result["layerMask"] = struct.unpack_from("<i", self.payload, 8)[0]
        result.update({key + "_bits": "0x" + self.payload[off:off+4][::-1].hex() for key, off in
                       (("minDepth", 12), ("maxDepth", 16), ("minNormalAngle", 20), ("maxNormalAngle", 24))})
        return result | {"payload_hex": self.payload.hex(), "source": self.source}


@dataclass(frozen=True)
class PhysicsQueryPlan:
    collider_key: str
    kind: str
    epoch: PhysicsEpoch
    layer_mask: int
    arguments: tuple[tuple[str, tuple[float, ...]], ...]
    input_sources: tuple[str, ...]
    source: str

    def __post_init__(self):
        _source(self.collider_key)
        _need(self.kind in ("OverlapAreaNonAlloc", "OverlapCircleNonAlloc"), "Unrecovered query branch")
        _need(isinstance(self.epoch, PhysicsEpoch), "Explicit query epoch required")
        _int(self.layer_mask, -0x80000000, 0x7fffffff, "Query layer mask")
        expected = (("pointA", 2), ("pointB", 2), ("boxCenter", 2), ("boxSize", 2), ("angle", 1)) if self.kind == "OverlapAreaNonAlloc" else (("center", 2), ("radius", 1))
        _need(type(self.arguments) is tuple and len(self.arguments) == len(expected), "Invalid query argument shape")
        normalized = []
        for (name, value), (key, width) in zip(self.arguments, expected):
            _need(name == key, "Unexpected native query argument order")
            normalized.append((name, _vector(value, width)))
        object.__setattr__(self, "arguments", tuple(normalized))
        if self.kind == "OverlapAreaNonAlloc":
            args = dict(normalized)
            a, b = args["pointA"], args["pointB"]
            center = tuple(_float(_float(x+y)*0.5) for x, y in zip(a, b))
            size = tuple(_float(abs(_float(x-y))) for x, y in zip(a, b))
            _need(tuple(map(_bits, center)) == tuple(map(_bits, args["boxCenter"])) and
                  tuple(map(_bits, size)) == tuple(map(_bits, args["boxSize"])) and
                  _bits(args["angle"][0]) == "0x00000000", "Area-to-box arguments differ from recovered conversion")
        else:
            _need(dict(normalized)["radius"][0] >= 0, "GetWorldRadius magnitude cannot be negative")
        _need(type(self.input_sources) is tuple and bool(self.input_sources), "Explicit query input sources required")
        for value in self.input_sources:
            _source(value)
        _source(self.source)

    def as_dict(self):
        return {"collider_key": self.collider_key, "kind": self.kind, "epoch": self.epoch.as_dict(),
                "layer_mask": self.layer_mask, "physics_scene_handle": 0, "buffer_capacity": NATIVE_BUFFER_CAPACITY,
                "argument_bits": {name: [_bits(x) for x in values] for name, values in self.arguments},
                "initial_filter_hex": legacy_filter_initial_bytes(self.layer_mask, self.epoch.queries_hit_triggers).hex(),
                "arithmetic_scope": "binary32 nearest-even, finite normal-or-zero intermediates; live MXCSR not validated",
                "filter_consistency_reconstructed": False, "input_sources": list(self.input_sources), "source": self.source}

    @property
    def fingerprint(self):
        return hashlib.sha256(json.dumps(self.as_dict(), sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def plan_box_overlap(minimum_bounds: UnityBoundsSnapshot, maximum_bounds: UnityBoundsSnapshot,
                     *, layer_mask: int, source: str) -> PhysicsQueryPlan:
    """Actual box branch reads bounds twice, then OverlapArea -> angle-zero box."""
    _need(isinstance(minimum_bounds, UnityBoundsSnapshot) and isinstance(maximum_bounds, UnityBoundsSnapshot),
          "Both actual Unity bounds getter snapshots are required")
    _need(minimum_bounds.collider_key == maximum_bounds.collider_key and minimum_bounds.epoch == maximum_bounds.epoch,
          "Bounds getter snapshots belong to different collider/epoch")
    _need(minimum_bounds.runtime_class == maximum_bounds.runtime_class == "UnityEngine.BoxCollider2D",
          "Native utility only takes the exact BoxCollider2D class on this branch")
    a = minimum_bounds.minimum()[:2]
    b = maximum_bounds.maximum()[:2]
    center = tuple(_float(_float(x+y)*0.5) for x, y in zip(a, b))
    size = tuple(_float(abs(_float(x-y))) for x, y in zip(a, b))
    return PhysicsQueryPlan(minimum_bounds.collider_key, "OverlapAreaNonAlloc", minimum_bounds.epoch, layer_mask,
                            (("pointA", a), ("pointB", b), ("boxCenter", center), ("boxSize", size), ("angle", (0.0,))),
                            (minimum_bounds.source, maximum_bounds.source), source)


def plan_circle_overlap(collider_key: str, radius_vector: UnityVectorSnapshot, *, runtime_class: str, has_circle_overlap_fixed: bool,
                        bounds: UnityBoundsSnapshot | None, world_position: UnityVectorSnapshot | None,
                        layer_mask: int, source: str) -> PhysicsQueryPlan:
    """Cached GetComponent<CircleColliderOverlapFixed> existence controls center.

    A true marker lookup uses bounds.center; otherwise Transform.position.
    Rigidbody presence does not control this branch. The cache state is explicit.
    """
    _need(isinstance(radius_vector, UnityVectorSnapshot), "Actual TransformVector(radius,0,0) snapshot required")
    _need(runtime_class == "UnityEngine.CircleCollider2D", "Native utility only takes the exact CircleCollider2D class")
    _bool(has_circle_overlap_fixed, "native cached CircleColliderOverlapFixed presence")
    if has_circle_overlap_fixed:
        _need(isinstance(bounds, UnityBoundsSnapshot) and world_position is None, "Marker branch needs bounds.center snapshot only")
        _need(bounds.collider_key == collider_key and bounds.epoch == radius_vector.epoch and bounds.runtime_class == runtime_class,
              "Circle bounds epoch/key/class mismatch")
        center, center_source = bounds.center[:2], bounds.source
    else:
        _need(bounds is None and isinstance(world_position, UnityVectorSnapshot), "No-marker branch needs actual Transform.position only")
        _need(world_position.epoch == radius_vector.epoch, "Circle position epoch mismatch")
        center, center_source = world_position.value[:2], world_position.source
    radius = radius_from_transformed_vector(radius_vector.value)
    return PhysicsQueryPlan(collider_key, "OverlapCircleNonAlloc", radius_vector.epoch, layer_mask,
                            (("center", center), ("radius", (radius,))), (radius_vector.source, center_source), source)


@dataclass(frozen=True)
class PhysicalColliderHit:
    collider_instance_id: int | None
    target: TargetSnapshot | None
    source: str

    def __post_init__(self):
        if self.collider_instance_id is None:
            _need(self.target is None, "Null Unity collider cannot produce a live Entity snapshot")
        else:
            _int(self.collider_instance_id, -0x80000000, 0x7fffffff, "Unity collider instance ID")
        _need(self.target is None or isinstance(self.target, TargetSnapshot), "Explicit collider-to-Entity component result required")
        _source(self.source)


@dataclass(frozen=True)
class ExternalOverlapResult:
    plan_fingerprint: str
    epoch: PhysicsEpoch
    returned_count: int
    hits: tuple[PhysicalColliderHit, ...]
    filter_after_consistency: ContactFilterSnapshot
    source: str

    def __post_init__(self):
        _source(self.plan_fingerprint)
        _need(isinstance(self.epoch, PhysicsEpoch), "Explicit returned query epoch required")
        _int(self.returned_count, 0, NATIVE_BUFFER_CAPACITY, "Native returned count")
        _need(type(self.hits) is tuple and len(self.hits) == self.returned_count and
              all(isinstance(x, PhysicalColliderHit) for x in self.hits), "Returned array prefix/count is incomplete")
        _need(isinstance(self.filter_after_consistency, ContactFilterSnapshot), "Engine CheckConsistency outcome is unknown")
        _source(self.source)


@dataclass(frozen=True)
class BoundPhysicsQueries:
    plans: tuple[PhysicsQueryPlan, ...]
    results: tuple[ExternalOverlapResult, ...]
    snapshot: OverlapQuerySnapshot
    source: str

    def as_targeting_snapshot(self):
        return self.snapshot

    def as_dict(self):
        return {"scope": "recovered native query arguments/frame contract, explicit external Unity snapshots",
                "plans": [x.as_dict() | {"fingerprint": x.fingerprint} for x in self.plans],
                "results": [{"returned_count": x.returned_count, "unity_collider_ids": [h.collider_instance_id for h in x.hits],
                             "entity_uids": [h.target.uid if h.target is not None else None for h in x.hits],
                             "buffer_may_be_truncated": x.returned_count == NATIVE_BUFFER_CAPACITY,
                             "filter_after_consistency": x.filter_after_consistency.as_dict(),
                             "collider_entity_sources": [h.source for h in x.hits], "source": x.source} for x in self.results],
                "source": self.source, "physics_overlap_generated": False, "physics_world_bounds_generated": False,
                "engine_sync_generated": False, "runtime_battle_validated": False, "battle_ready": False}


def bind_external_query_results(plans: tuple[PhysicsQueryPlan, ...], results: tuple[ExternalOverlapResult, ...],
                                *, source: str) -> BoundPhysicsQueries:
    """Bind ordered query receipts; do not manufacture hits or deduplicate them."""
    _need(type(plans) is tuple and type(results) is tuple and len(plans) == len(results) and bool(plans),
          "Complete ordered per-collider query plans/results required")
    _source(source)
    _need(all(isinstance(x, PhysicsQueryPlan) for x in plans) and all(isinstance(x, ExternalOverlapResult) for x in results),
          "Typed native plan/Unity result snapshots required")
    _need(len({x.collider_key for x in plans}) == len(plans), "Duplicate cached range collider identity")
    first = plans[0]
    _need(all(x.layer_mask == first.layer_mask and x.epoch == first.epoch for x in plans),
          "Mixed layer masks or physics epochs in one frozen range query")
    snapshots = []
    for plan, result in zip(plans, results):
        _need(result.plan_fingerprint == plan.fingerprint and result.epoch == plan.epoch,
              "Unity result belongs to another query plan/pose/frame/phase")
        snapshots.append(ColliderOverlapSnapshot(tuple(h.target for h in result.hits), False, result.source))
    snapshot = OverlapQuerySnapshot(tuple(snapshots), first.layer_mask & 0xffffffff, source)
    return BoundPhysicsQueries(plans, results, snapshot, source)

"""Native altar logical targeting with external Unity Physics2D query results.

Normal/no-hotfix SideTypes, Layers, purpose/getters, HitRange aggregation and
ALL weighted PriorityQueue are reconstructed. Runtime fields/counts/providers
remain explicit inputs. No geometric AABB approximation generates overlaps.
"""
from __future__ import annotations

from collections.abc import Mapping
from dataclasses import dataclass, replace
from types import MappingProxyType

from .fp import FP
from .targeting import (TargetSnapshot, OverlapQuerySnapshot, PredicateSnapshot,
    UnverifiedTargetContext, _require, _uint, _bool, _source)

SMALL_GAP = FP.from_raw(4294967)  # FP.EN3 = native One/1000
BIG_GAP = FP.from_int32(1000000)  # WeightedTarget.cctor static+8
EQUALITY_EPSILON = FP.from_raw(42950)  # MathUtil.cctor copies FP.EN5
SIDE_SAME = (1,2,4)
SIDE_OPPOSITE = (2,5,2)
LAYER_INDICES = MappingProxyType({1:10,2:9,4:28})  # actual TagManager + Layers.cctor strings


def same_side_mask(source_side: int) -> int:
    _uint(source_side,"Source side",7)
    # 0x186727990 compares equality with one bit, rather than membership.
    return next((SIDE_SAME[i] for i in range(3) if source_side == (1<<i)),source_side)


def opposite_side_mask(source_side: int) -> int:
    _uint(source_side,"Source side",7)
    return next((SIDE_OPPOSITE[i] for i in range(3) if source_side == (1<<i)),0)


def convert_target_side(source_side: int, relative_side: int) -> int:
    _uint(source_side,"Source side",7)
    _uint(relative_side,"Relative target side",7)
    if source_side == 0:
        return relative_side
    if relative_side == 1:
        return same_side_mask(source_side)
    if relative_side == 2:
        return opposite_side_mask(source_side)
    if relative_side == 3:
        return same_side_mask(source_side) | opposite_side_mask(source_side)
    return 7


def side_layer_mask(absolute_side: int) -> int:
    _uint(absolute_side,"Absolute side mask",7)
    return sum(1 << layer for side,layer in LAYER_INDICES.items() if absolute_side & side)


def _counts(values: Mapping, name: str):
    _require(isinstance(values,Mapping),name+" must be explicit logical enum -> signed Int16 count mapping")
    out={}
    for key,value in values.items():
        _uint(key,name+" enum",63)
        _require(type(value) is int and -32768 <= value <= 32767,name+" must retain signed Int16 values")
        out[key]=value
    return MappingProxyType(out)


@dataclass(frozen=True)
class AbnormalStatus:
    """Explicit native Attributes +20/+28 counters and data+28 base flag bits.

    Missing requested counters are unknown, rather than zero. The immune array
    suppresses positive dynamic counts; a base-data flag can still be true.
    CheckAbnormalImmune reads this same immune array directly.
    """
    active_counts: Mapping[int,int]
    immune_counts: Mapping[int,int]
    base_flags: int
    source: str

    def __post_init__(self):
        object.__setattr__(self,"active_counts",_counts(self.active_counts,"Active counts"))
        object.__setattr__(self,"immune_counts",_counts(self.immune_counts,"Immune counts"))
        _uint(self.base_flags,"Native UInt64 base flag bits",0xffffffffffffffff)
        _source(self.source)

    @classmethod
    def zeroed_prepared_fixture(cls,source: str):
        """Explicit zero-count/base-mask scene fixture, not a recovered live registry."""
        keys=(7,9,15,17)
        return cls({k:0 for k in keys},{k:0 for k in keys},0,source)

    def immune(self,flag: int) -> bool:
        _uint(flag,"Abnormal enum",63)
        _require(flag in self.immune_counts,f"Immune counter {flag} is unknown")
        return self.immune_counts[flag] > 0

    def flag(self,flag: int) -> bool:
        _uint(flag,"Abnormal enum",63)
        if not self.immune(flag):
            _require(flag in self.active_counts,f"Active counter {flag} is unknown")
            if self.active_counts[flag] > 0:
                return True
        # Native TEST + SETG: bit63 alone is negative and does not return true.
        mask=self.base_flags & (1 << flag)
        return 0 < mask < (1 << 63)

    @property
    def camouflage(self) -> bool:
        return self.flag(17) and not self.immune(9)


@dataclass(frozen=True)
class HitRangeManager:
    """Ordered frozen native provider-registry snapshot; empty dictionary admits.

    Providers are (native providerId, PredicateSnapshot-or-null) entries. Real
    provider geometry remains external. This reproduces aggregation, not the
    algorithms of unknown providers or mutable Dictionary enumeration.
    """
    providers: tuple[tuple[str,PredicateSnapshot | None],...]
    source: str

    def __post_init__(self):
        _require(type(self.providers) is tuple,"Explicit ordered provider registry tuple required")
        seen=set()
        for item in self.providers:
            _require(type(item) is tuple and len(item)==2,"Provider entry is (id, snapshot-or-null)")
            key,value=item
            _source(key)
            _require(key not in seen,"Provider registry cannot contain duplicate dictionary keys")
            seen.add(key)
            _require(value is None or isinstance(value,PredicateSnapshot),"Explicit provider implementation outcomes required")
        _source(self.source)

    def is_in_hit_range(self,uid: int) -> bool:
        _uint(uid,"HitRange target UID")
        for _,provider in self.providers:
            if provider is not None and not provider.resolve(uid,"IHitRangeProvider.IsInHitRange"):
                return False
        return True

    def register(self,key: str,provider: PredicateSnapshot | None):
        """Native Register: a present non-null provider is not overwritten."""
        _source(key)
        _require(provider is None or isinstance(provider,PredicateSnapshot),"Explicit provider snapshot required")
        values=list(self.providers)
        for i,(old_key,old) in enumerate(values):
            if old_key==key:
                if old is not None:return self
                values[i]=(key,provider)
                return HitRangeManager(tuple(values),self.source)
        return HitRangeManager(tuple(values+[(key,provider)]),self.source)


@dataclass(frozen=True)
class RuntimeTargetData:
    created_time: FP
    attributes: AbnormalStatus
    hit_range: HitRangeManager
    source: str
    postfilter_alive: bool | None = None

    def __post_init__(self):
        _require(isinstance(self.created_time,FP),"Explicit native createdTime FP field required")
        _require(isinstance(self.attributes,AbnormalStatus),"Explicit native attribute status state required")
        _require(isinstance(self.hit_range,HitRangeManager),"Explicit HitRange provider registry required")
        _require(self.postfilter_alive is None or type(self.postfilter_alive) is bool,"ALL recheck must be explicit bool or frozen-call reuse")
        _source(self.source)


@dataclass(frozen=True)
class RuntimeAltarContext:
    source_side: int
    source_map_layer: int
    collider_count: int
    deterministic: bool
    is_sandbox: bool
    custom_validator: PredicateSnapshot | None
    excluded_uids: frozenset[int]
    hotfixes_absent: bool
    source: str

    def __post_init__(self):
        _uint(self.source_side,"Owner native side field",7)
        _uint(self.source_map_layer,"Owner native mapLayer field",0x7fffffff)
        _uint(self.collider_count,"Actual cached collider count",4096)
        _bool(self.deterministic,"Battle deterministic flag")
        _bool(self.is_sandbox,"BattleController.isSandBox")
        _require(not self.is_sandbox,"Sandbox secondary weight transformation is outside this closed branch")
        _require(_bool(self.hotfixes_absent,"Relevant hotfix delegates absent"),"Runtime hotfix delegates cannot use normal native targeting closure")
        _require(self.custom_validator is None or isinstance(self.custom_validator,PredicateSnapshot),"Explicit immutable custom validator outcomes required")
        _require(type(self.excluded_uids) is frozenset,"Explicit AdvancedSelector exclusion set required")
        for uid in self.excluded_uids:_uint(uid,"Excluded UID")
        _source(self.source)

    @property
    def absolute_target_side_mask(self):
        return convert_target_side(self.source_side,3)  # actual prefab BOTH

    @property
    def query_layer_mask(self):
        return side_layer_mask(self.absolute_target_side_mask)

    @property
    def source_purpose_mask(self):
        return 0  # normal TargetSelector getter, independent of Ability purpose=1

    @property
    def opposite_side_mask(self):
        return opposite_side_mask(self.source_side)


def _floor(value: FP) -> FP:
    return FP.from_raw((value.raw >> 32) << 32)


def _abs(value: FP) -> FP:
    return -value if value.raw < 0 else value


def _equal(a: FP,b: FP) -> bool:
    return _abs(a-b).raw < EQUALITY_EPSILON.raw


def weighted_target_compare(uid_a: int,weight_a: FP,uid_b: int,weight_b: FP) -> int:
    """Ordinary ALL constructor priorWeight=FP0, then native weight bins and UID.

    Large weights compare integer floors first and their fractional bins only
    when floors match. Small weights use floor(weight/EN3). Exact threshold and
    mixed-large/small pairs retain unbinned weights. FP operators retain native
    signed/overflow behavior; no float createdTime conversion is performed.
    """
    _uint(uid_a,"Weighted target UID");_uint(uid_b,"Weighted target UID")
    _require(isinstance(weight_a,FP) and isinstance(weight_b,FP),"FP weights required")
    a,b=weight_a,weight_b
    aa,ab=_abs(a),_abs(b)
    if aa.raw > BIG_GAP.raw and ab.raw > BIG_GAP.raw:
        fa,fb=_floor(a),_floor(b)
        if _equal(fa,fb):
            a,b=_floor((a-fa)/SMALL_GAP),_floor((b-fb)/SMALL_GAP)
        else:
            a,b=fa,fb
    elif aa.raw < BIG_GAP.raw and ab.raw < BIG_GAP.raw:
        a,b=_floor(a/SMALL_GAP),_floor(b/SMALL_GAP)
    if _equal(a,b):
        return (uid_a>uid_b)-(uid_a<uid_b)  # Entity.CompareTo UInt32
    return (a.raw>b.raw)-(a.raw<b.raw)


def order_created_targets(items, *, is_sandbox: bool, hotfixes_absent: bool, source: str):
    """PriorityQueue.Add linear scan inserts BEFORE first compare<=0, keeps ties."""
    _source(source)
    _require(not _bool(is_sandbox,"Explicit sandbox state"),"Sandbox ALL weight adjustments not supported")
    _require(_bool(hotfixes_absent,"Explicit no-hotfix scope"),"Unknown hotfix comparison path")
    _require(type(items) is tuple and len(items)<=128,"Explicit bounded ALL input tuple required")
    queue=[]
    for item in items:
        _require(type(item) is tuple and len(item)==2,"ALL entry is (UInt32 UID, FP createdTime)")
        uid,weight=item
        _uint(uid,"ALL UID")
        _require(isinstance(weight,FP),"Native createdTime FP required")
        index=0
        while index<len(queue) and weighted_target_compare(uid,weight,*queue[index])>0:
            index+=1
        queue.insert(index,item)
    return tuple(uid for uid,_ in queue)


@dataclass(frozen=True)
class RuntimeSelection:
    hits: tuple[TargetSnapshot,...]
    collector_uids: tuple[int,...]
    decisions: tuple[dict,...]
    all_decisions: tuple[dict,...]
    capped: bool
    context: RuntimeAltarContext
    query_source: str
    runtime_sources: tuple[str,...]

    def as_dict(self):
        return {"hit_uids":[t.uid for t in self.hits],"collector_uids":list(self.collector_uids),
            "decisions":[dict(x) for x in self.decisions],"ALL_decisions":[dict(x) for x in self.all_decisions],
            "capped_at_128":self.capped,"source_side":self.context.source_side,
            "absolute_target_side_mask":self.context.absolute_target_side_mask,
            "query_layer_mask":self.context.query_layer_mask,"source_purpose_mask":0,
            "context_source":self.context.source,"query_source":self.query_source,
            "runtime_sources":list(self.runtime_sources),
            "scope":"ordinary native altar admission/ALL weighted queue with external Physics2D and explicit runtime state",
            "physics_overlap_generated":False,"native_all_order_generated":True,
            "native_masks_derived":True,"runtime_battle_validated":False,"battle_ready":False,
            "remaining_gaps":["Unity collider/world transform/Physics2D query membership and order",
                "live hotfix/static override/engine state","dynamic buff/provider registration and mutable callbacks",
                "sandbox extra-mode weights"]}


def _admission(target: TargetSnapshot,data: RuntimeTargetData,context: RuntimeAltarContext):
    if not (3 & (1<<target.motion)):return "motion_mask",target
    if not (1 & target.category):return "category_mask",target
    ally=None
    if context.source_side and target.side==context.source_side:
        ally=data.attributes.flag(15)
        if ally:return "ally_target_free",target
    if target.map_layer!=context.source_map_layer:return "map_layer",target
    if not data.hit_range.is_in_hit_range(target.uid):return "hit_range_provider",target
    camouflage=data.attributes.camouflage  # ordinary Ability.canSelectCamouflageTarget=false
    if camouflage and (target.side & context.opposite_side_mask)==target.side:
        return "enemy_camouflage",target
    if context.custom_validator is not None and not context.custom_validator.resolve(target.uid,"Custom target validator"):
        return "custom_validator",target
    if target.uid in context.excluded_uids:return "advanced_exclusion_set",target
    return None,replace(target,ally_target_free=ally,heal_free=None,camouflage=camouflage)


def select_altar_targets_runtime(query: OverlapQuerySnapshot,context: RuntimeAltarContext,
                                 targets: Mapping[int,RuntimeTargetData]) -> RuntimeSelection:
    """Conditional collector followed by native ALL, without an order adapter.

    Core snapshot fields are explicit native field/getter inputs. Status booleans
    on the v6 TargetSnapshot are ignored and computed from Attributes. ALL can
    drop a member using the explicit second-phase alive snapshot; None reuses
    the core alive value under the frozen synchronous-call contract.
    """
    _require(isinstance(query,OverlapQuerySnapshot) and isinstance(context,RuntimeAltarContext),"Explicit native/physics contexts required")
    _require(isinstance(targets,Mapping),"Explicit runtime data by UID required")
    copied=dict(targets)
    for uid,data in copied.items():
        _uint(uid,"Runtime data UID")
        _require(isinstance(data,RuntimeTargetData),"RuntimeTargetData required")
    _require(query.layer_mask==context.query_layer_mask,"External query layer mask differs from derived native mask")
    _require(len(query.colliders)==context.collider_count,"External query must account for all cached colliders")
    selected=[];seen=set();states={};decisions=[];cap=False
    for ci,col in enumerate(query.colliders):
        if col.destroyed:
            decisions.append({"collider_index":ci,"hit_index":None,"uid":None,"reason":"range_collider_destroyed"})
            continue
        for hi,target in enumerate(col.hits):
            uid=target.uid if target is not None else None
            if target is not None and target.uid:
                if target.uid in states:_require(states[target.uid]==target,"Conflicting mutable core snapshots for one UID")
                states[target.uid]=target
            if target is None:reason="collider_has_no_live_entity"
            elif target.destroyed:reason="entity_destroyed"
            elif target.uid==0:reason="instance_uid_invalid"
            elif not _bool(target.alive,f"Entity.alive UID{uid}"):reason="entity_not_alive"
            elif uid in seen:reason="duplicate_admitted_uid"
            else:
                _require(uid in copied,f"Missing runtime data for UID{uid}")
                reason,target=_admission(target,copied[uid],context)
            decisions.append({"collider_index":ci,"hit_index":hi,"uid":uid,"reason":reason or "admitted"})
            if reason is None:
                selected.append(target);seen.add(uid)
                if len(selected)==128:cap=True;break
        if cap:break
    if context.deterministic:selected.sort(key=lambda t:t.uid)
    collector=tuple(t.uid for t in selected)
    all_items=[];all_decisions=[];alive_by_uid={}
    for target in selected:
        data=copied[target.uid]
        alive=target.alive if data.postfilter_alive is None else data.postfilter_alive
        if not _bool(alive,f"ALL Entity.alive UID{target.uid}"):
            all_decisions.append({"uid":target.uid,"reason":"not_alive_at_ALL"})
            continue
        all_items.append((target.uid,data.created_time));alive_by_uid[target.uid]=target
        all_decisions.append({"uid":target.uid,"reason":"queued","weight_raw":data.created_time.raw,"prior_weight_raw":0})
    order=order_created_targets(tuple(all_items),is_sandbox=context.is_sandbox,
        hotfixes_absent=context.hotfixes_absent,source=context.source)
    sources=tuple(dict.fromkeys(source for u in collector for source in (
        copied[u].source,copied[u].attributes.source,copied[u].hit_range.source,
        *(provider.source for _,provider in copied[u].hit_range.providers if provider is not None))))
    return RuntimeSelection(tuple(alive_by_uid[u] for u in order),collector,tuple(decisions),
        tuple(all_decisions),cap,context,query.source,sources)

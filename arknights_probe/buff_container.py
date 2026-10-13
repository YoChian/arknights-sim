"""Native NPC Buff membership and nested, shared-snapshot event traversal.

The input is a prepared post-Reset Buff, not a substitute Unity initializer.
Override decisions, attribute writes, owner notifications, and pool operations
are explicit providers. The container owns registration, traversal and removal.
"""
from __future__ import annotations

from collections.abc import Callable, Iterable
from contextlib import contextmanager
from dataclasses import dataclass
from typing import Any

from .fp import FP, wrap64, MAX_VALUE_RAW
from .npc_actions import (
    BuffPtr, NpcBuff, NpcEntity, NpcActionRuntime, EntityPtr,
    UnverifiedNpcContext, insert_buff_by_priority, DEATH_REASONS,
)


class UnverifiedBuffContainer(UnverifiedNpcContext):
    pass


def _require(value, message):
    if not value:
        raise UnverifiedBuffContainer(message)


def lifetime_is_zero(value: FP) -> bool:
    """MathUtil.IsZero(FP): TSMath.Abs(value) < EN5 (signed raw)."""
    _require(isinstance(value, FP), "Explicit post-Reset FP lifetime required")
    absolute = MAX_VALUE_RAW if value.raw == -(1 << 63) else abs(value.raw)
    return absolute < 42950


class BuffIterator:
    """Reusable iterator; nested iterators share the owner's frozen buffer."""
    def __init__(self, owner: SortedDoubleBufferedBuffList, backwards: bool):
        self.owner, self.backwards = owner, backwards
        self.disposed = True
        self.index = -1
        self.buffer: list[BuffPtr] = []

    def reset(self, buffer: list[BuffPtr]):
        self.buffer = buffer
        self.index = len(buffer) if self.backwards else -1
        self.disposed = False

    def move_next(self) -> bool:
        _require(not self.disposed, "Disposed iterator cannot be advanced by this component")
        self.index += -1 if self.backwards else 1
        return self.index >= 0 if self.backwards else self.index < len(self.buffer)

    @property
    def current(self) -> BuffPtr:
        _require(0 <= self.index < len(self.buffer), "Enumerator Current is out of range")
        return self.buffer[self.index]

    def dispose(self):
        if self.disposed:
            self.owner.trace.append(("duplicate_dispose", self.backwards))
            return
        self.disposed = True
        _require(self.owner.depth > 0, "Iterator nesting counter underflow")
        self.owner.depth -= 1
        (self.owner.backward_pool if self.backwards else self.owner.forward_pool).append(self)


class SortedDoubleBufferedBuffList:
    """Live list + one shared snapshot, not a queue of deferred mutations.

    Add/Remove change live immediately. GetEnumerator copies live only when
    nesting was zero; every nested forward/backward iterator reads that same
    snapshot. Dispose decrements depth and pushes the iterator into a LIFO pool.
    It neither commits pending changes nor clears the snapshot.
    """
    def __init__(self):
        self.live: list[BuffPtr] = []
        self.snapshot: list[BuffPtr] = []
        self.depth = 0
        self.forward_pool: list[BuffIterator] = []
        self.backward_pool: list[BuffIterator] = []
        self.trace: list[tuple] = []

    def add(self, pointer: BuffPtr):
        _require(isinstance(pointer, BuffPtr), "Buff ObjectPtr required")
        self.live[:] = insert_buff_by_priority(tuple(self.live), pointer)

    def remove(self, buff: NpcBuff) -> bool:
        # Original backwards scan compares current UID of valid entries.
        for i in range(len(self.live) - 1, -1, -1):
            old = self.live[i].resolve()
            if old is not None and old.uid == buff.uid:
                del self.live[i]
                return True
        return False

    def clear(self):
        self.live.clear()

    def clear_invalid_if_not_loop(self):
        if self.depth == 0:
            self.live[:] = [p for p in self.live if p.resolve() is not None]

    def get_enumerator(self, *, backwards=False) -> BuffIterator:
        _require(self.depth < 65535, "UInt16 iterator depth overflow is outside this bounded component")
        if self.depth == 0:
            self.snapshot[:] = self.live
        self.depth += 1
        pool = self.backward_pool if backwards else self.forward_pool
        iterator = pool.pop() if pool else BuffIterator(self, backwards)
        iterator.reset(self.snapshot)
        return iterator

    @contextmanager
    def iterate(self, *, backwards=False):
        iterator = self.get_enumerator(backwards=backwards)
        try:
            yield iterator
        finally:
            iterator.dispose()


@dataclass(frozen=True)
class BuffInitShape:
    """Explicit post-Reset receipt; resource overrideKey alone is insufficient.

    filters_passed covers upstream anti/status/ground/levitate creation checks.
    Lifetime is initialized FP, not a guess from resource lifeTime: INFINITY
    may transform a resource zero. Unknown override/stack policy uses a provider.
    """
    key: str
    lifetime: FP
    receipt: str
    override_key: str = ""
    filters_passed: bool = True
    suppression_flags: tuple[str, ...] = ()
    resistance_mask: int = 0
    derived_buff_count: int = 0
    abnormal_anti_mask: int = 0
    durable: bool = False
    status_resistable: bool = False
    can_slow_down: bool = False
    ep_break: bool = False
    trigger_count: int = 0
    remaining_time: FP | None = None

    def __post_init__(self):
        _require(type(self.key) is str and self.key.isascii() and bool(self.key), "Prepared Buff key required")
        _require(isinstance(self.lifetime, FP) and bool(self.receipt), "Prepared lifetime and initializer receipt required")
        _require(type(self.override_key) is str and self.override_key.isascii(), "Explicit runtime override key required")
        _require(self.filters_passed is True, "Unproven creation filters cannot register a Buff")
        _require(not self.suppression_flags, "Silence/stun/freeze/levitate/ground-bound suppression requires another backend")
        _require(self.resistance_mask == 0 and self.derived_buff_count == 0 and self.abnormal_anti_mask == 0,
                 "Resistance/derived/anti side effects require a separate proven backend")
        _require(self.durable is False, "Durable Buffs are outside this registration closure")
        _require(self.status_resistable is False and self.can_slow_down is False and self.ep_break is False,
                 "Delta preprocessing requires a separate status/EP/slowdown backend")
        _require(self.trigger_count == 0, "Trigger timer requires a separate proven backend")
        _require(self.remaining_time is None or isinstance(self.remaining_time, FP), "Prepared remainingTime FP required")


@dataclass
class BuffState:
    buff: NpcBuff
    shape: BuffInitShape
    registered_uid: int
    started: bool = False
    marked_finished: bool = False
    actually_finished: bool = False
    need_remove: bool = False
    manually_enabled: bool = False
    actually_enabled: bool = False
    late_enabled: bool = False
    existing_time: FP = FP(0)

    @property
    def is_finished(self):
        return self.marked_finished or (self.started and lifetime_is_zero(self.shape.lifetime))


@dataclass
class BuffContainerHooks:
    """Required side effects; providers may synchronously reenter the container.

    override_transition must implement an explicitly named override backend;
    it may call container.set_enabled(). It never supplies dispatch membership.
    opaque_event is only admitted for the shipped upeople_t_1 death audio node.
    """
    attribute_modifier: Callable[[NpcBuff, bool], None]
    owner_buff_started: Callable[[NpcBuff], None]
    owner_buff_finished: Callable[[NpcBuff, bool], None]
    recycle: Callable[[NpcBuff, bool], None]
    override_transition: Callable[[str, NpcBuff, Any], None] | None = None
    opaque_event: Callable[[NpcBuff, int, Any], None] | None = None
    owner_buff_late_enabled: Callable[[NpcBuff], None] | None = None


class NpcBuffContainer:
    """Selected ordinary container, sharing the exact external Entity identity."""
    def __init__(self, owner: NpcEntity, actions: NpcActionRuntime, hooks: BuffContainerHooks, *, no_hotfix: bool):
        _require(no_hotfix is True, "Explicit ordinary no-hotfix context required")
        _require(isinstance(owner, NpcEntity) and owner.unity_exists and not owner.is_tile_unit,
                 "Existing non-Tile owner identity required")
        _require(isinstance(actions, NpcActionRuntime), "Recovered NpcActionRuntime required")
        for key in ("attribute_modifier", "owner_buff_started", "owner_buff_finished", "recycle"):
            _require(callable(getattr(hooks, key)), key + " provider must be explicit")
        self.owner, self.actions, self.hooks = owner, actions, hooks
        self.buffs = SortedDoubleBufferedBuffList()
        self.uid_map: dict[int, NpcBuff] = {}
        # Records of opaque runtime override groups, not a policy engine.
        self.override_keys: dict[str, NpcBuff] = {}
        self.states: dict[NpcBuff, BuffState] = {}
        self.trace: list[tuple] = []
        self.current_modifier = None

    def state(self, buff: NpcBuff) -> BuffState:
        _require(buff in self.states, "Buff in snapshot lacks an initializer receipt")
        return self.states[buff]

    def _validate_buff(self, buff: NpcBuff, shape: BuffInitShape):
        _require(buff.owner is self.owner and buff.initialized and buff.unity_exists, "Prepared Buff owner/availability mismatch")
        _require(buff.template_key in self.actions.templates, "Unreviewed template cannot register")
        _require(buff.on_event_priority == self.actions.templates[buff.template_key]["raw"]["onEventPriority"],
                 "Priority override requires a separate initialization backend")
        _require(not shape.override_key or callable(self.hooks.override_transition), "Runtime override requires an explicit backend")
        if buff.template_key == "upeople_t_1":
            _require(callable(self.hooks.opaque_event), "Death audio CreateBuff initializer requires an explicit provider")

    def add_initialized(self, buff: NpcBuff, shape: BuffInitShape, *, owner_active: bool) -> NpcBuff | None:
        _require(type(owner_active) is bool, "Explicit BObject+0x24 active snapshot required")
        self._validate_buff(buff, shape)
        _require(buff not in self.states and buff.uid not in self.uid_map, "Duplicate Buff/UID cannot register")
        self.check_finished()
        state = BuffState(buff, shape, buff.uid)
        self.states[buff] = state
        self.buffs.add(BuffPtr(buff, buff.uid))
        self.uid_map[buff.uid] = buff
        self.trace.append(("register", buff.token, buff.uid))
        if owner_active:
            self.start(buff)
        # _FilterBuffAbnormalAnti is an exact no-work branch for anti mask zero.
        if not state.is_finished:
            if shape.override_key:
                self.override_keys.setdefault(shape.override_key, buff)
                self.hooks.override_transition("register", buff, self)
            else:
                self.set_enabled(buff, True)
            return buff
        if not state.started:
            return buff
        self._finish_and_remove(state)
        return None

    def add_initialized_many(self, prepared: Iterable[tuple[NpcBuff, BuffInitShape]], *, owner_active: bool) -> tuple[int, ...]:
        # Entity.AddBuffs stores zero for rejected creations, without compaction.
        results = []
        for buff, shape in prepared:
            value = self.add_initialized(buff, shape, owner_active=owner_active)
            results.append(value.uid if value is not None else 0)
        return tuple(results)

    def _run_event(self, buff: NpcBuff, event: int):
        if buff.template_key == "upeople_t_1" and event == 3:
            _require(callable(self.hooks.opaque_event), "Death audio provider missing")
            with self.actions.context.change_guard(buff=buff, source=buff.source.resolve(), target=buff.owner) as snapshot:
                self.trace.append(("external_audio_event", buff.token, event))
                self.hooks.opaque_event(buff, event, snapshot)
            return
        self.actions.run_buff_event(buff, event)

    def start(self, buff: NpcBuff):
        state = self.state(buff)
        if not state.started:
            self.trace.append(("start_actions", buff.token))
            self._run_event(buff, 0)
            # Native sets m_started after actions; do not set before reentry.
            state.started = True
            self.trace.append(("started", buff.token))
            # Selected templates have neither event36 nor45. Do not silently
            # accept another template's other-Buff status/action pipeline.
            self._check_other_start_empty()
            self.hooks.owner_buff_started(buff)

    def _check_other_start_empty(self):
        for event in (36,):
            with self.buffs.iterate() as iterator:
                while iterator.move_next():
                    buff = iterator.current.resolve()
                    if buff is not None and not self.state(buff).is_finished and self.state(buff).actually_enabled:
                        _require(not self.actions._events(buff).get(event), "Other-Buff-start Context pipeline is outside selected empty-action scope")

    def set_enabled(self, buff: NpcBuff, enabled: bool):
        state = self.state(buff)
        _require(type(enabled) is bool, "Native manually-enabled Boolean required")
        # Setter ignores a request to enable a marked-finished Buff.
        if enabled and state.marked_finished:
            return
        state.manually_enabled = enabled
        if state.actually_enabled == enabled:
            return
        state.actually_enabled = enabled
        if enabled:
            state.late_enabled = True
        self.trace.append(("enabled", buff.token, enabled))
        self.hooks.attribute_modifier(buff, enabled)
        self._run_event(buff, 24 if enabled else 25)

    def mark_finish(self, buff: NpcBuff, *, update_override_map=True):
        state = self.state(buff)
        if not state.marked_finished:
            self.set_enabled(buff, False)
            state.marked_finished = True
            self.trace.append(("mark_finish", buff.token))
            if update_override_map and state.shape.override_key:
                self.hooks.override_transition("mark", buff, self)

    def remove_uid(self, uid: int):
        value = self.uid_map.get(uid)
        if value is not None:
            self.mark_finish(value, update_override_map=True)

    def finish_buffs_by_id(self, key: str, *, excluded_buff: NpcBuff | None = None,
                           dec_stack=False, update_override_map=True):
        _require(type(key) is str and key.isascii(), "Explicit ASCII buffKey required")
        _require(dec_stack is False, "Stack decrement uses another native branch")
        # Entity.RemoveBuffs with decStack=false ignores the caller's updateMap
        # parameter; the container overload always calls MarkFinish(true).
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is not None and buff is not excluded_buff and self.state(buff).shape.key == key:
                    self.mark_finish(buff, update_override_map=True)

    def _finish(self, state: BuffState, *, update_override_map: bool,
                recycle_next_frame: bool, is_owner_finished: bool):
        buff = state.buff
        self.mark_finish(buff, update_override_map=update_override_map)
        if state.actually_finished:
            return
        state.actually_finished = True
        self.trace.append(("actually_finished", buff.token))
        self._run_event(buff, 1)
        self.hooks.attribute_modifier(buff, False)
        self.hooks.owner_buff_finished(buff, is_owner_finished)
        self.trace.append(("recycle_request", buff.token, recycle_next_frame))
        self.hooks.recycle(buff, recycle_next_frame)

    def _finish_and_remove(self, state: BuffState):
        buff = state.buff
        self.buffs.remove(buff)
        # Native reads the Buff's current UID for dictionary.Remove.
        self.uid_map.pop(buff.uid, None)
        self.trace.append(("remove_live", buff.token, buff.uid))
        self._finish(state, update_override_map=True, recycle_next_frame=False, is_owner_finished=False)

    def check_finished(self):
        saw_invalid = False
        with self.buffs.iterate(backwards=True) as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is None:
                    saw_invalid = True
                elif self.state(buff).is_finished:
                    state = self.state(buff)
                    self._finish_and_remove(state)
                    if state.shape.override_key:
                        self.hooks.override_transition("remove", buff, self)
        if saw_invalid:
            self.buffs.clear_invalid_if_not_loop()

    def on_owner_finish(self, reason: int, finish_source: NpcEntity | None = None):
        _require(type(reason) is int, "Explicit FinishReason required")
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is None:
                    continue
                # No isFinishedOrDisabled filter in this ordinary native loop.
                self.state(buff)
                self.trace.append(("owner_finish", buff.token, reason))
                if buff.template_key == "upeople_t_1":
                    if reason in DEATH_REASONS:
                        with self.actions.context.change_guard(main_target=finish_source):
                            self._run_event(buff, 3)
                    # Its shipped 4/29/34 lists are all absent.
                else:
                    self.actions.owner_finish(buff, reason, finish_source=finish_source)
        self.check_finished()

    def _ordinary_owner_event(self, event: int):
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is not None:
                    state = self.state(buff)
                    if not state.is_finished and state.actually_enabled:
                        self.trace.append(("owner_event", buff.token, event))
                        self._run_event(buff, event)
        self.check_finished()

    def on_owner_born(self):
        """Event12 only. Native OnOwnerBorn never calls Buff.OnStart."""
        self._ordinary_owner_event(12)

    def on_owner_post_born(self):
        self._ordinary_owner_event(35)

    def tick(self, delta: FP):
        """Two native passes for infinite, no-trigger, no-status selected Buffs.

        Caller owns whether Entity executes its active Buff Tick phase. Buff
        OnTick itself starts an unstarted, unfinished Buff even when disabled;
        it has no extra owner-active check. Born/event12 cannot replace this.
        Finite remainingTime, triggers and delta preprocessing are strict gates.
        """
        _require(isinstance(delta, FP) and delta.raw >= 0, "Explicit nonnegative tick FP required")
        _require(callable(self.hooks.owner_buff_late_enabled), "Late-enable owner notification provider required")
        for pointer in self.buffs.live:
            buff = pointer.resolve()
            if buff is not None:
                shape = self.state(buff).shape
                remaining = shape.remaining_time if shape.remaining_time is not None else shape.lifetime
                _require(remaining.raw <= 0, "Finite remainingTime tick is outside this component")
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is None:
                    continue
                state = self.state(buff)
                if state.need_remove:
                    self._finish_and_remove(state)
                else:
                    if not state.is_finished and not state.started:
                        self.start(buff)
                    if not state.is_finished:
                        state.existing_time = FP(wrap64(state.existing_time.raw + delta.raw))
        # A new outermost snapshot here can include Buffs added during OnStart.
        # When nested within another event, both passes reuse its old snapshot.
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is not None:
                    state = self.state(buff)
                    if not state.is_finished and state.actually_enabled and state.late_enabled:
                        state.late_enabled = False
                        self._run_event(buff, 32)
                        self.hooks.owner_buff_late_enabled(buff)
        self.check_finished()

    def on_take_damage(self, packet):
        """Read/write Modifier adapter; selected actions leave it unchanged.

        The caller owns Entity reaction/cancellation/HP. Unlike Entity routing,
        this native container has no cancelled/amount/damage-kind/bypass filter.
        Unknown actions which read/write Modifier are excluded at registration.
        """
        for key in ("source", "target", "shared_flags", "skip_sp_recovery", "cancel_reason", "final_delta"):
            _require(hasattr(packet, key), "Modifier adapter missing " + key)
        _require(isinstance(packet.source, EntityPtr) and isinstance(packet.target, EntityPtr), "Packet ObjectPtr<Entity> required")
        _require(isinstance(packet.final_delta, FP), "Packet FP final_delta required")
        old_modifier = self.current_modifier
        try:
            # BeginChangeGuard snapshots/recaptures surrounding Entity/Buff refs.
            with self.actions.context.change_guard():
                with self.buffs.iterate() as iterator:
                    while iterator.move_next():
                        buff = iterator.current.resolve()
                        if buff is None:
                            continue
                        state = self.state(buff)
                        if state.is_finished or not state.actually_enabled:
                            continue
                        self.current_modifier = packet
                        self.trace.append(("take_damage", buff.token))
                        self._run_event(buff, 10)
        finally:
            self.current_modifier = old_modifier
        self.check_finished()
        return packet

    def on_target_killed(self, target: NpcEntity):
        # Selected templates have no ON_TARGET_KILLED action. Preserve actual
        # traversal/cleanup, with a strict gate on expanding that Context shape.
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is not None and not self.state(buff).is_finished and self.state(buff).actually_enabled:
                    _require(not self.actions._events(buff).get(9), "Target-killed action Context requires another backend")
                    self.trace.append(("target_killed_empty", buff.token, target.token))
        self.check_finished()

    def clear(self, is_owner_finished: bool = False):
        _require(type(is_owner_finished) is bool, "Owner-finished snapshot required")
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is not None:
                    self._finish(self.state(buff), update_override_map=False,
                                 recycle_next_frame=True, is_owner_finished=is_owner_finished)
        # Native second pass handles Buffs which survived a reentrant finish.
        with self.buffs.iterate() as iterator:
            while iterator.move_next():
                buff = iterator.current.resolve()
                if buff is not None and not self.state(buff).actually_finished:
                    self.hooks.attribute_modifier(buff, False)
                    self.hooks.recycle(buff, False)
        self.buffs.clear()
        # The native dictionary Clear has no Buff actions. Notify the explicit
        # backend at that boundary, so it cannot silently retain a stale group.
        for representative in tuple(self.override_keys.values()):
            self.hooks.override_transition("clear", representative, self)
        self.override_keys.clear()
        self.uid_map.clear()
        self.trace.append(("clear_live",))


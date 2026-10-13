"""Selected native registry and deterministic coroutine phases.

This is an execution component, not BattleController initialization or a full
map. Owner existence/activation and omitted controller modules must come from
an explicitly supplied context. Source addresses are recorded in v6 evidence.
"""
from __future__ import annotations

from collections.abc import Callable, Iterator
from dataclasses import dataclass

from .coroutines import CoroutineRunner
from .fp import FP


class UnverifiedFrameContext(ValueError):
    pass


def _bool(value, name):
    if type(value) is not bool:
        raise UnverifiedFrameContext(f"{name} must be explicit bool")
    return value


@dataclass
class CoroutineOwner:
    """Unity Object-null and GameObject.activeInHierarchy, not Entity.alive."""
    exists: bool
    active_in_hierarchy: bool

    def available(self):
        return _bool(self.exists, "owner.exists") and _bool(
            self.active_in_hierarchy, "owner.active_in_hierarchy")


@dataclass
class _Handler:
    handle: int
    owner: CoroutineOwner
    runner: CoroutineRunner

    def move_next(self):
        if not self.runner.active or not self.owner.available():
            return False
        return self.runner.tick()

    def stop(self):
        # RuntimeHandler.Stop clears the stack; it does not call IDisposable.
        self.handle = 0
        self.runner.stack.clear()


class SharedCoroutineSimulator:
    """Start primes immediately; SimulateTick copies the active list first."""
    def __init__(self, *, source: str, deterministic: bool):
        if not source or not _bool(deterministic, "deterministic"):
            raise UnverifiedFrameContext("explicit deterministic simulator context required")
        self.source = source
        self.next_handle = 0
        self.handlers: list[_Handler] = []
        self.by_handle: dict[int, _Handler] = {}

    def start(self, owner: CoroutineOwner, iterator: Iterator | None):
        if iterator is None:
            return 0
        if not isinstance(owner, CoroutineOwner):
            raise UnverifiedFrameContext("Unity owner context required")
        if self.next_handle >= (1 << 64) - 1:
            raise UnverifiedFrameContext("handle wrap is outside the supported context")
        self.next_handle += 1
        allocated_handle = self.next_handle
        handler = _Handler(allocated_handle, owner, CoroutineRunner(iterator))
        if handler.move_next():
            self.handlers.append(handler)
            self.by_handle[handler.handle] = handler
        # An immediately completed coroutine still returns the allocated id.
        return allocated_handle

    def stop(self, handle: int):
        handler = self.by_handle.pop(handle, None)
        if handler is None:
            return False
        handler.stop()
        self.handlers.remove(handler)
        return True

    def tick(self):
        for handler in tuple(self.handlers):
            if not handler.move_next():
                old_handle = handler.handle
                handler.stop()
                if handler in self.handlers:
                    self.handlers.remove(handler)
                self.by_handle.pop(old_handle, None)


@dataclass(eq=False)
class RegisteredObject:
    instance_uid: int
    borned: bool
    fixed_tick: Callable[[FP], None]
    late_tick: Callable[[FP], None]

    def validate(self):
        if type(self.instance_uid) is not int or not 0 <= self.instance_uid < (1 << 32):
            raise UnverifiedFrameContext("native BObject.instanceUid must be UInt32")
        _bool(self.borned, "BObject.borned")
        if not callable(self.fixed_tick) or not callable(self.late_tick):
            raise UnverifiedFrameContext("fixed/late callbacks required")

    @property
    def valid_and_borned(self):
        self.validate()
        return self.borned and self.instance_uid != 0


class NativeObjectRegistry:
    """PriorityQueue<BObject> uses ascending CompareTo(instanceUid).

    Add inserts before the first comparison <= 0, including equal ids. Each
    phase makes a fresh validAndBorned snapshot, with no recheck in its loop.
    This API covers BObject; CharacterManager's extra registry is separate.
    """
    def __init__(self):
        self.objects: list[RegisteredObject] = []

    def register(self, obj: RegisteredObject):
        obj.validate()
        for index, other in enumerate(self.objects):
            if obj.instance_uid <= other.instance_uid:
                self.objects.insert(index, obj)
                return
        self.objects.append(obj)

    def unregister(self, obj: RegisteredObject):
        for index, other in enumerate(self.objects):
            if obj is other:
                del self.objects[index]
                return True
        return False

    def _snapshot(self):
        return tuple(obj for obj in self.objects if obj.valid_and_borned)

    def fixed_tick(self, dt: FP):
        for obj in self._snapshot():
            obj.fixed_tick(dt)

    def late_tick(self, dt: FP):
        for obj in self._snapshot():
            obj.late_tick(dt)


class SelectedFrameLoop:
    """Objects.fixed -> explicit intervening modules -> coroutines -> late.

    The intervening callbacks are deliberate context inputs, not silently
    emulated Map/Physics/dialog/global buffs. This component cannot certify a
    full BattleController frame or the game's initial clock.
    """
    def __init__(self, *, dt: FP, registry: NativeObjectRegistry,
                 simulator: SharedCoroutineSimulator, before_coroutines: tuple,
                 after_coroutines: tuple, source: str):
        if not isinstance(dt, FP) or dt.raw <= 0 or not source:
            raise UnverifiedFrameContext("positive FP dt and source required")
        if not isinstance(before_coroutines, tuple) or not isinstance(after_coroutines, tuple):
            raise UnverifiedFrameContext("explicit intervening module callbacks required")
        if not all(callable(x) for x in before_coroutines + after_coroutines):
            raise UnverifiedFrameContext("module entries must be callable")
        self.dt, self.registry, self.simulator = dt, registry, simulator
        self.before, self.after, self.source = before_coroutines, after_coroutines, source
        self.frame, self.time_raw = 0, 0

    def tick(self):
        self.frame += 1
        self.time_raw = (FP.from_raw(self.time_raw) + self.dt).raw
        self.registry.fixed_tick(self.dt)
        for callback in self.before:
            callback(self.dt)
        self.simulator.tick()
        for callback in self.after:
            callback(self.dt)
        self.registry.late_tick(self.dt)

"""Frame-driven static scheduler subset with explicit external battle inputs.

This executes declarations as spawn/activation *requests*, not combat. Enemy
creation success and membership are explicit fixtures; damage, path movement,
hotfixes, mode hooks, actual run RNG and victory are outside this component.
"""
from __future__ import annotations

import copy
from dataclasses import dataclass
import math

from .coroutines import CoroutineRunner, NEXT_FRAME, fixed_seconds, serial_queue, wait_while
from .data import Dataset, require, number
from .env import UnverifiedMechanism
from .fp import FP, binary32
from .queue_sort import native_queue_sort, NATIVE_SORT_EVIDENCE

ASSET_DEFAULT_DT_RAW = 143165440
SUPPORTED_MODES = {"NORMAL", "FOUR_STAR"}
TIMELINE_EVIDENCE = {
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "RuntimeHandler.MoveNext": "0x18065ff70",
    "StartCoroutine": "0x18065d200",
    "DefaultWaveHandler.ExecuteActionQueue.MoveNext": "0x18094e650",
    "Scheduler._DealFragment.MoveNext": "0x180951a70",
    "Scheduler._DealWave.MoveNext": "0x180951ed0",
    "Scheduler._DoSpawn.MoveNext": "0x1809547a0",
    "Scheduler._DoActivatePredefined.MoveNext": "0x180952770",
    "Scheduler._DealAction": "0x180919fb0",
    "Scheduler.CheckActionEnabled": "0x180912b50",
    "client_runtime_compared": False,
}


@dataclass(frozen=True)
class CompiledTimeline:
    waves: list
    branches: dict
    group_selections: dict
    hidden_groups: list
    mode: str
    source: dict


def compile_timeline(dataset: Dataset, *, mode: str, group_selections: dict,
                     enemy_runtime: dict, input_source: str,
                     enabled_hidden: list | None = None,
                     disabled_hidden: list | None = None) -> CompiledTimeline:
    """Strict original-index external group choices; no implied RNG draw.

    ``enemy_runtime`` pins extraSpawnDelay, notCountInTotal and successful
    counted creation per ID. The enemy creation-input adapter can derive delay
    and counting flags from reviewed DB/prefab evidence; post-Init eligibility
    still needs an explicit fixture or observed source.
    """
    require(mode in SUPPORTED_MODES, "mode must be NORMAL or FOUR_STAR")
    require(isinstance(input_source, str) and bool(input_source.strip()), "External inputs need input_source")
    require(isinstance(group_selections, dict), "group_selections must be a dictionary")
    require(isinstance(enemy_runtime, dict), "enemy_runtime must be a dictionary")
    hidden = set()
    for rune in dataset.level.get("runes", []):
        if rune.get("difficultyMask") == mode and rune.get("key") == "level_hidden_group_enable":
            for entry in rune.get("blackboard", []):
                if entry.get("key") == "key":
                    hidden.add(entry["valueStr"])
    for values in (enabled_hidden or [], disabled_hidden or []):
        require(isinstance(values, list) and all(isinstance(x, str) and x for x in values), "Hidden overrides need lists of nonempty keys")
    hidden.update(enabled_hidden or [])
    hidden.difference_update(disabled_hidden or [])
    groups = {}
    for wi, wave in enumerate(dataset.level["waves"]):
        for fi, fragment in enumerate(wave["fragments"]):
            for ai, action in enumerate(fragment["actions"]):
                key = action.get("randomSpawnGroupKey")
                if key:
                    require(action["actionType"] in {"SPAWN", "ACTIVATE_PREDEFINED", "EMPTY"}, "Unsupported grouped action")
                    require(key not in groups or groups[key][0] == (wi, fi), "Repeated group keys across fragments need qualified selections")
                    groups.setdefault(key, ((wi, fi), []))[1].append(ai)
    require(set(group_selections) == set(groups), f"Supply exactly all group selections: {sorted(groups)}")
    for key, (_, indexes) in groups.items():
        require(type(group_selections[key]) is int and group_selections[key] in indexes, f"{key}: selection must be an original actionIndex in {indexes}")

    def actions_to_items(actions, fragment_delay, path, from_branch=False):
        items = []
        for ai, original in enumerate(actions):
            action = copy.deepcopy(original)
            require(action.get("randomType") == "ALWAYS" and action.get("refreshType") == "ALWAYS", f"{path}/{ai}: random/refresh variants unimplemented")
            group = action.get("randomSpawnGroupKey")
            if group and group_selections[group] != ai:
                continue
            # Native preprocess deletes empty key only after the winner choice.
            if not action.get("key") or action["actionType"] == "EMPTY":
                continue
            if action.get("hiddenGroup") and action["hiddenGroup"] not in hidden:
                continue
            kind = action["actionType"]
            require(kind in {"SPAWN", "ACTIVATE_PREDEFINED"}, f"Unsupported action {kind}")
            if action.get("autoDisplayEnemyInfo"):
                raise UnverifiedMechanism("DISPLAY_ENEMY_INFO executor has not been restored")
            base = binary32(binary32(fragment_delay) + binary32(action["preDelay"]))
            if kind == "SPAWN":
                key = action["key"]
                require(key in enemy_runtime, f"{key}: supply explicit enemy_runtime fixture")
                runtime = enemy_runtime[key]
                require(isinstance(runtime, dict), f"{key}: runtime must be a dictionary")
                require(set(runtime) == {"extraSpawnDelay", "notCountInTotal", "successfulCountedCreation"}, f"{key}: supply all three enemy runtime fields")
                extra = number(runtime["extraSpawnDelay"], key + ".extraSpawnDelay", 0)
                require(type(runtime["notCountInTotal"]) is bool and type(runtime["successfulCountedCreation"]) is bool, "Enemy creation/count flags must be boolean")
                action["external_enemy_runtime"] = copy.deepcopy(runtime)
                base = max(binary32(0), binary32(base - binary32(extra)))
                count = action["count"]
            else:
                count = 1
            require(math.isfinite(base), "Queue delay overflows the supported finite binary32 domain")
            require(count <= 100000 and len(items) + count <= 100000, "Queue exceeds offline diagnostic size limit")
            action["useExtraRoute"] = from_branch
            for i in range(count):
                time = binary32(binary32(binary32(i) * binary32(action["interval"])) + base) if kind == "SPAWN" else base
                items.append({"time": time, "action": copy.deepcopy(action), "path": f"{path}/{ai}", "occurrence": i, "isValid": True})
            if kind == "SPAWN" and action.get("autoPreviewRoute"):
                # Native creates two preview queue entries. Never erase them:
                # their executor yields affect later serial execution timing.
                preview = {"actionType": "PREVIEW_CURSOR", "key": "", "routeIndex": action["routeIndex"], "useExtraRoute": from_branch, "blockFragment": False}
                for i in range(2):
                    preview_time = binary32(binary32(binary32(i) * binary32(.3)) + binary32(base - binary32(3)))
                    items.append({"time": preview_time, "action": copy.deepcopy(preview), "path": f"{path}/{ai}/autoPreviewRoute", "occurrence": i, "isValid": True})
        require(len(items) <= 100000, "Queue exceeds offline diagnostic size limit")
        # Native midpoint Quicksort exchanges equal time keys, even for small
        # queues. Preserve append order and never add an index tie-breaker.
        return native_queue_sort(items, key=lambda item: item["time"])

    waves = []
    for wi, wave in enumerate(dataset.level["waves"]):
        require(wave["maxTimeWaitingForNextWave"] == -1, "Only this map's indefinite wave gates are supported")
        fragments = [{"preDelay": fragment["preDelay"], "items": actions_to_items(fragment["actions"], fragment["preDelay"], f"/waves/{wi}/fragments/{fi}/actions")}
                     for fi, fragment in enumerate(wave["fragments"])]
        waves.append({"preDelay": wave["preDelay"], "postDelay": wave["postDelay"], "fragments": fragments})
    branches = {}
    for key, branch in dataset.level.get("branches", {}).items():
        phases = branch["phases"]
        require(len(phases) == 1 and phases[0]["preDelay"] == 0 and len(phases[0]["actions"]) == 1,
                "Only one-phase one-action zero-delay external branches supported")
        require(not phases[0]["actions"][0].get("randomSpawnGroupKey"), "Branch random group preprocessing unimplemented")
        branches[key] = actions_to_items(phases[0]["actions"], 0, f"/branches/{key}/phases/0/actions", True)
    return CompiledTimeline(waves, branches, copy.deepcopy(group_selections), sorted(hidden), mode,
                            {"input_source": input_source, "enemy_runtime": copy.deepcopy(enemy_runtime),
                             "enabled_hidden": list(enabled_hidden or []), "disabled_hidden": list(disabled_hidden or [])})


class TimelineEnv:
    """Main wave scheduling kernel; external events are not model battle actions."""
    def __init__(self, dataset: Dataset, compiled: CompiledTimeline, *, dt_raw: int = ASSET_DEFAULT_DT_RAW):
        require(type(dt_raw) is int and 0 < dt_raw < (1 << 63), "dt_raw must be positive signed int64")
        self.dataset, self.compiled = dataset, copy.deepcopy(compiled)
        self.dt = FP.from_raw(dt_raw)
        self.delta_float = self.dt.as_float()
        self.clock_origin = "serialized_TimeManager_initial_value" if dt_raw == ASSET_DEFAULT_DT_RAW else "explicit_external_dt_raw"
        self._reset = False

    def reset(self, *, seed: int | None = None):
        require(seed is None or type(seed) is int, "seed must be an integer or None")
        self.seed = seed  # Metadata only; no inferred RNG consumption.
        self.current_frame, self.time = 0, FP.from_raw(0)
        self.events, self.alive, self.resolved, self.activated = [], {}, {}, []
        self.wave_index, self.fragment_index, self.phase = -1, -1, "created"
        self.pending, self.block_counter = [], 0
        self.wave_ids, self.final_ids = set(), set()
        self.gate_overrides = {}
        self.final_external_complete = False
        self.branch_runners, self.triggered_branches = {}, set()
        self._reset = True
        self.runner = CoroutineRunner(self._main())
        self.runner.tick()  # Native StartCoroutine advances immediately.
        return self.observe(), self.info()

    def info(self):
        return copy.deepcopy({"scope": "static_main_wave_scheduler_kernel_with_external_battle_inputs",
                "battle_ready": False, "runtime_battle_validated": False,
                "reward_defined": False, "seed_consumed": False,
                "clock_origin": self.clock_origin, "dt_raw": self.dt.raw,
                "live_fixed_delta_validated": False, "clock_anchor": "scheduler_start_after_excluded_mode_hooks",
                "group_choice_origin": "explicit_original_action_indices", "mode": self.compiled.mode,
                "hidden_groups": self.compiled.hidden_groups, "external_inputs": self.compiled.source,
                "sort_scope": "static_native_midpoint_quicksort_equal_keys_exchange",
                "sort_evidence": NATIVE_SORT_EVIDENCE,
                "wait_rounding": "binary32_division_then_nearest_ties_even_native_0x18059e290",
                "excluded": ["game mode before/after schedule hooks", "attack/damage/movement", "victory", "hotfix dispatch", "automatic branch triggers", "run RNG seed/consumption"],
                "native_evidence": TIMELINE_EVIDENCE})

    def _event(self, kind, **detail):
        record = {"kind": kind, "frame": self.current_frame, "time_raw": self.time.raw, **copy.deepcopy(detail)}
        self.events.append(record)
        return record

    def _execute(self, item):
        action = item["action"]
        kind = action["actionType"]
        if self.pending and self.pending[0] is item:
            self.pending.pop(0)
        detail = {"path": item["path"], "planned_float_time": item["time"], "key": action["key"],
                  "route_index": action["routeIndex"], "route_pool": "extraRoutes" if action["useExtraRoute"] else "routes"}
        if kind == "SPAWN":
            identifier = f"enemy_request_{sum(e['kind'] == 'spawn_request' for e in self.events) + 1}"
            runtime = action["external_enemy_runtime"]
            tracked = action["managedByScheduler"] and not runtime["notCountInTotal"] and runtime["successfulCountedCreation"]
            wave_block = not action["dontBlockWave"] and (not action["useExtraRoute"] or action["forceBlockWaveInBranch"])
            record = self._event("spawn_request", id=identifier, tracked=tracked, wave_block=wave_block, **detail)
            if tracked:
                self.alive[identifier] = record
                self.final_ids.add(identifier)
                if wave_block:
                    self.wave_ids.add(identifier)
        elif kind == "PREVIEW_CURSOR":
            self._event("preview_cursor_request", **detail)
        elif kind == "ACTIVATE_PREDEFINED":
            self.activated.append(action["key"])
            self._event("activate_predefined_request", **detail)
        else:
            raise UnverifiedMechanism(f"Unimplemented action executor {kind}")
        if action.get("blockFragment"):
            self.block_counter -= 1
        yield NEXT_FRAME

    def _fragment(self, fragment):
        self.phase = "fragment_queue"
        self.fragment_start_time_raw = (self.time + FP.from_float32(fragment["preDelay"])).raw
        self.pending = list(fragment["items"])
        self.block_counter = sum(bool(item["action"].get("blockFragment")) for item in self.pending)
        if self.pending:
            yield serial_queue(list(self.pending), self._execute, self.delta_float)
        self.phase = "fragment_gate"
        yield wait_while(lambda: self.block_counter > 0)

    def _wave_blocked(self):
        if self.wave_index in self.gate_overrides:
            return self.gate_overrides[self.wave_index]
        return bool(self.wave_ids)

    def _wave(self, wave):
        self.phase = "wave_predelay"
        self.wave_start_time_raw = self.time.raw
        yield fixed_seconds(wave["preDelay"], self.delta_float)
        for fi, fragment in enumerate(wave["fragments"]):
            self.fragment_index = fi
            yield self._fragment(fragment)
        self.phase = "wave_gate"
        yield wait_while(self._wave_blocked)
        self.wave_ids.clear()
        self.phase = "wave_postdelay"
        yield fixed_seconds(wave["postDelay"], self.delta_float)
        self._event("wave_kernel_complete", wave=self.wave_index)

    def _main(self):
        for wi, wave in enumerate(self.compiled.waves):
            self.wave_index = wi
            yield self._wave(wave)
        self.phase = "final_external_gate"
        yield wait_while(lambda: bool(self.final_ids) or any(r.active for r in self.branch_runners.values()) or not self.final_external_complete)
        self.phase = "kernel_complete"
        self._event("scheduler_kernel_complete")

    def observe(self):
        require(self._reset, "reset first")
        return {"current_frame": self.current_frame, "time_raw": self.time.raw, "phase": self.phase,
                "wave": self.wave_index, "fragment": self.fragment_index,
                "pending_events": [{"path": x["path"], "planned_float_time": x["time"], "kind": x["action"]["actionType"]} for x in self.pending],
                "alive_tracked": copy.deepcopy(list(self.alive.values())), "wave_blocking_ids": sorted(self.wave_ids),
                "block_fragment": self.block_counter, "activated_requests": list(self.activated),
                "branch_active": sorted(k for k, r in self.branch_runners.items() if r.active),
                "final_external_complete": self.final_external_complete,
                "kernel_terminated": not self.runner.active and not any(r.active for r in self.branch_runners.values())}

    def step(self, action: dict):
        require(self._reset, "reset first")
        require(isinstance(action, dict), "action must be a dictionary")
        kind = action.get("type")
        start = len(self.events)
        if kind == "tick":
            require(set(action) <= {"type", "frames"}, "Unknown tick fields")
            frames = action.get("frames", 1)
            require(type(frames) is int and 1 <= frames <= 100000, "frames must be 1..100000")
            for _ in range(frames):
                if not self.runner.active and not any(r.active for r in self.branch_runners.values()):
                    break
                self.current_frame += 1
                self.time = self.time + self.dt
                if self.runner.active:
                    self.runner.tick()
                for runner in list(self.branch_runners.values()):
                    if runner.active:
                        runner.tick()
        elif kind == "external_resolve":
            require(set(action) == {"type", "id", "outcome", "source"}, "Resolve needs id, outcome, source")
            require(action["outcome"] in {"killed", "missed"}, "Resolution outcome must be killed/missed terminal fixture; use separate release/recycle inputs")
            require(isinstance(action["source"], str) and bool(action["source"]), "Resolution needs source")
            identifier = action["id"]
            require(identifier in self.alive, f"No alive tracked request {identifier}")
            self.alive.pop(identifier)
            self.wave_ids.discard(identifier)
            self.final_ids.discard(identifier)
            self.resolved[identifier] = self._event("external_terminal_fixture", id=identifier, outcome=action["outcome"], source=action["source"], final_recycle_completion_included=True)
        elif kind == "external_release_wave":
            require(set(action) == {"type", "id", "source"}, "Wave release needs id and source")
            require(isinstance(action["source"], str) and bool(action["source"]), "Wave release needs source")
            require(action["id"] in self.wave_ids, "Request does not block the current wave")
            self.wave_ids.remove(action["id"])
            self._event("external_wave_release", id=action["id"], source=action["source"], final_membership_changed=False)
        elif kind == "external_recycle":
            require(set(action) == {"type", "id", "source"}, "Recycle needs id and source")
            require(isinstance(action["source"], str) and bool(action["source"]), "Recycle needs source")
            require(action["id"] in self.final_ids, "Request has no final tracked membership")
            self.final_ids.remove(action["id"])
            self.alive.pop(action["id"], None)
            self._event("external_recycle", id=action["id"], source=action["source"], wave_membership_changed=False)
        elif kind == "external_wave_gate":
            require(set(action) == {"type", "wave", "blocked", "source"}, "Gate needs wave, blocked, source")
            require(type(action["wave"]) is int and 0 <= action["wave"] < len(self.compiled.waves), "Invalid wave")
            require(type(action["blocked"]) is bool and isinstance(action["source"], str) and bool(action["source"]), "Invalid external gate")
            self.gate_overrides[action["wave"]] = action["blocked"]
            self._event("external_wave_gate", wave=action["wave"], blocked=action["blocked"], source=action["source"])
        elif kind == "external_final_complete":
            require(set(action) == {"type", "source"} and isinstance(action["source"], str) and bool(action["source"]), "Final completion needs source")
            self.final_external_complete = True
            self._event("external_final_completion", source=action["source"])
        elif kind == "external_trigger_branch":
            require(not self.observe()["kernel_terminated"], "Cannot trigger a branch after scheduler kernel termination")
            require(set(action) == {"type", "branch", "source"} and isinstance(action["source"], str) and bool(action["source"]), "Branch trigger needs source")
            key = action["branch"]
            require(key in self.compiled.branches and key not in self.triggered_branches, "Unknown or already triggered branch")
            self.triggered_branches.add(key)
            self._event("external_branch_trigger", branch=key, source=action["source"])
            def branch():
                for item in self.compiled.branches[key]:
                    yield self._execute(item)
            runner = CoroutineRunner(branch())
            self.branch_runners[key] = runner
            runner.tick()
        else:
            raise UnverifiedMechanism(f"Unsupported input {kind}; no model combat actions are implemented")
        observation = self.observe()
        return observation, None, observation["kernel_terminated"], False, {**self.info(), "events": copy.deepcopy(self.events[start:])}


def zero_enemy_fixture(dataset: Dataset):
    """Explicit review fixture, never a claim about merged real enemy attributes."""
    return {key: {"extraSpawnDelay": 0.0, "notCountInTotal": False, "successfulCountedCreation": True} for key in dataset.enemy_refs}

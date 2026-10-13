"""A deterministic declaration inspection interface.

reset/step use a familiar shape, but reward is None and steps count declarations,
not seconds or frames. No battle outcome or training reward is fabricated.
"""
from __future__ import annotations

from copy import deepcopy
from .data import Dataset


class UnverifiedMechanism(RuntimeError):
    pass


class DeclarationProbeEnv:
    def __init__(self, dataset: Dataset):
        self.dataset = dataset
        self._reset = False

    def reset(self, *, seed: int = 0, options: dict | None = None) -> tuple[dict, dict]:
        if type(seed) is not int or not 0 <= seed <= 0xFFFFFFFF:
            raise ValueError("seed must be uint32; native PRNG equivalence is not claimed")
        options = options or {}
        if set(options) - {"branch"}:
            raise ValueError("Unknown reset option")
        branch = options.get("branch")
        if branch is None:
            self.records = self.dataset.declarations
        elif branch in self.dataset.branch_declarations:
            self.records = self.dataset.branch_declarations[branch]
        else:
            raise ValueError(f"Unknown branch: {branch}")
        self.seed, self.branch, self.cursor = seed, branch, 0
        self._reset = True
        return self._observation(), self._info()

    def _info(self) -> dict:
        return {"scope": "declaration_probe", "time_unit": "declaration_index",
                "reward_semantics": "undefined", "native_seed_equivalence": False,
                "branch_activation_simulated": False, "schema_status": self.dataset.provenance.get("schema_status"),
                "battle_ready": False}

    def _observation(self) -> dict:
        next_record = self.records[self.cursor] if self.cursor < len(self.records) else None
        return {"seed": self.seed, "branch": self.branch, "cursor": self.cursor,
                "remaining": len(self.records) - self.cursor,
                "next_declaration": deepcopy(next_record),
                "action_mask": {"next": next_record is not None}}

    def step(self, action: dict) -> tuple[dict, None, bool, bool, dict]:
        if not self._reset:
            raise RuntimeError("Call reset first")
        if action != {"type": "next"}:
            raise UnverifiedMechanism("Only declaration advance is supported; deployment, battle tick, skills and rewards are unverified")
        if self.cursor >= len(self.records):
            raise RuntimeError("Probe is exhausted; call reset")
        consumed = deepcopy(self.records[self.cursor])
        self.cursor += 1
        info = self._info()
        info["inspected_declaration"] = consumed
        return self._observation(), None, self.cursor == len(self.records), False, info

    def compile_battle_schedule(self):
        raise UnverifiedMechanism(
            "DeclarationProbeEnv does not compile battle schedules. Use the independent conditional TimelineEnv "
            "with explicit choices/enemy runtime/gate inputs; full combat, live RNG, mode hooks and automatic branch triggers remain unverified")

    def close(self):
        self._reset = False

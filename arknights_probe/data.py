"""Load hash-pinned, normalized local data and check structural references.

Field names originate from a community FlatBuffers schema. Structural validity
and reference integrity do not establish the client's runtime semantics.
"""
from __future__ import annotations

import hashlib
import json
import math
from collections import Counter
from pathlib import Path
from typing import Any


class DataError(ValueError):
    """Invalid data, a broken reference, or a changed source snapshot."""


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def read_json(path: Path) -> Any:
    def pairs(items):
        result = {}
        for key, value in items:
            require(key not in result, f"{path}: duplicate JSON key {key!r}")
            result[key] = value
        return result

    with path.open(encoding="utf-8") as stream:
        return json.load(stream, object_pairs_hook=pairs,
                         parse_constant=lambda x: (_ for _ in ()).throw(DataError(f"Nonfinite JSON: {x}")))


def require(condition: bool, message: str) -> None:
    if not condition:
        raise DataError(message)


def integer(value: Any, label: str, minimum: int = 0) -> int:
    require(type(value) is int and value >= minimum, f"{label}: expected integer >= {minimum}")
    return value


def number(value: Any, label: str, minimum: float | None = None) -> float:
    require(type(value) in (int, float) and math.isfinite(value), f"{label}: expected finite number")
    if minimum is not None:
        require(value >= minimum, f"{label}: must be >= {minimum}")
    return float(value)


def obj(value: Any, label: str) -> dict:
    require(isinstance(value, dict), f"{label}: expected object")
    return value


def array(value: Any, label: str) -> list:
    require(isinstance(value, list), f"{label}: expected array")
    return value


class Dataset:
    def __init__(self, level: dict, tables: dict[str, dict] | None = None,
                 provenance: dict | None = None):
        self.level = obj(level, "level")
        self.tables = tables or {}
        self.provenance = provenance or {"schema_status": "not_provided"}
        self.warnings: list[str] = []
        self.declarations: list[dict] = []
        self.branch_declarations: dict[str, list[dict]] = {}
        self.table_reference_gaps: list[dict] = []
        self._validate()

    @classmethod
    def from_manifest(cls, path: str | Path) -> "Dataset":
        manifest_path = Path(path).resolve()
        manifest = obj(read_json(manifest_path), "manifest")
        require(manifest.get("format_version") == 1, "Unsupported manifest version")
        loaded = {}
        for role, spec in obj(manifest.get("files"), "manifest.files").items():
            spec = obj(spec, f"files.{role}")
            source = Path(spec["path"])
            if not source.is_absolute():
                source = manifest_path.parent / source
            require(source.is_file(), f"Missing {role}: {source}")
            require(sha256(source) == spec["sha256"], f"Source changed: {role} ({source})")
            loaded[role] = read_json(source)
        require("level" in loaded, "Manifest has no level")
        return cls(loaded.pop("level"), loaded, manifest.get("provenance"))

    def position(self, value: Any, label: str) -> tuple[int, int]:
        value = obj(value, label)
        row = integer(value.get("row"), label + ".row")
        col = integer(value.get("col"), label + ".col")
        require(row < self.rows and col < self.cols, f"{label}: out of bounds ({row}, {col})")
        return row, col

    def tile(self, row: int, col: int) -> dict:
        """Native MapData logical GridPosition access; row zero is bottom."""
        require(type(row) is int and type(col) is int and 0 <= row < self.rows and 0 <= col < self.cols,
                f"Tile out of bounds: {row}, {col}")
        return self.matrix_tile(self.rows - row - 1, col)

    def matrix_tile(self, row: int, col: int) -> dict:
        """Raw serialized matrix view; row zero is the first stored row."""
        require(type(row) is int and type(col) is int and 0 <= row < self.rows and 0 <= col < self.cols,
                f"Tile out of bounds: {row}, {col}")
        return self.tiles[self.matrix[row * self.cols + col]]

    def _validate_route(self, route: Any, label: str) -> None:
        route = obj(route, label)
        require(route.get("motionMode") in {"WALK", "FLY", "E_NUM"}, f"{label}: unknown motionMode")
        self.position(route.get("startPosition"), label + ".startPosition")
        self.position(route.get("endPosition"), label + ".endPosition")
        for flag in ("allowDiagonalMove", "visitEveryTileCenter", "visitEveryNodeCenter", "visitEveryCheckPoint"):
            require(type(route.get(flag)) is bool, f"{label}.{flag}: expected boolean")
        for i, cp in enumerate(array(route.get("checkpoints", []), label + ".checkpoints")):
            cp = obj(cp, f"{label}.checkpoints[{i}]")
            require(isinstance(cp.get("type"), str), f"{label}: missing checkpoint type")
            number(cp.get("time"), f"{label}.checkpoints[{i}].time", 0)
            # WAIT positions are preserved; they do not claim a movement target.
            self.position(cp.get("position"), f"{label}.checkpoints[{i}].position")

    def _declaration(self, action: Any, path: str, route_pool: list) -> dict:
        action = obj(action, path)
        kind = action.get("actionType")
        require(kind in {"SPAWN", "ACTIVATE_PREDEFINED", "EMPTY"}, f"{path}: unsupported actionType {kind!r}")
        integer(action.get("count"), path + ".count")
        number(action.get("preDelay"), path + ".preDelay", 0)
        number(action.get("interval"), path + ".interval", 0)
        ri = integer(action.get("routeIndex"), path + ".routeIndex")
        require(ri < len(route_pool), f"{path}: invalid route reference {ri}")
        require(isinstance(action.get("key"), str), f"{path}: key must be string")
        if kind == "SPAWN":
            require(action["key"] in self.enemy_refs, f"{path}: enemy {action['key']} missing enemyDbRefs")
            require(route_pool[ri]["motionMode"] != "E_NUM", f"{path}: SPAWN uses placeholder route")
        elif kind == "ACTIVATE_PREDEFINED" and action["key"]:
            require(action["key"] in self.aliases, f"{path}: predefined alias {action['key']} not found")
        for flag in ("managedByScheduler", "blockFragment", "dontBlockWave", "forceBlockWaveInBranch"):
            require(type(action.get(flag)) is bool, f"{path}.{flag}: expected boolean")
        integer(action.get("weight"), path + ".weight")
        return {"path": path, "action": action, "route_pool": "extraRoutes" if route_pool is self.extra_routes else "routes"}

    def _validate(self) -> None:
        map_data = obj(self.level.get("mapData"), "mapData")
        grid = obj(map_data.get("map"), "mapData.map")
        self.rows = integer(grid.get("row_size"), "row_size", 1)
        self.cols = integer(grid.get("column_size"), "column_size", 1)
        require(self.rows * self.cols <= 100000, "Map exceeds probe size limit")
        self.tiles = array(map_data.get("tiles"), "mapData.tiles")
        self.matrix = array(grid.get("matrix_data"), "mapData.map.matrix_data")
        require(len(self.matrix) == self.rows * self.cols, "Map matrix dimensions do not match")
        for i, tile_index in enumerate(self.matrix):
            integer(tile_index, f"matrix[{i}]")
            require(tile_index < len(self.tiles), f"matrix[{i}]: invalid tile reference {tile_index}")
        for i, tile in enumerate(self.tiles):
            tile = obj(tile, f"tiles[{i}]")
            require(isinstance(tile.get("tileKey"), str), f"tiles[{i}]: missing tileKey")
            require(tile.get("passableMask") in {"ALL", "FLY_ONLY", "NONE"}, f"tiles[{i}]: unknown passableMask")
        self.routes = array(self.level.get("routes"), "routes")
        self.extra_routes = array(self.level.get("extraRoutes", []), "extraRoutes")
        for name, routes in (("routes", self.routes), ("extraRoutes", self.extra_routes)):
            for i, route in enumerate(routes):
                self._validate_route(route, f"{name}[{i}]")
        self.enemy_refs = {}
        for i, ref in enumerate(array(self.level.get("enemyDbRefs"), "enemyDbRefs")):
            ref = obj(ref, f"enemyDbRefs[{i}]")
            key = ref.get("id")
            require(isinstance(key, str) and key and key not in self.enemy_refs, f"enemyDbRefs[{i}]: duplicate or missing id")
            integer(ref.get("level"), f"enemyDbRefs[{i}].level")
            self.enemy_refs[key] = ref
        self.aliases = set()
        for name in ("predefines", "hardPredefines"):
            predefined = obj(self.level.get(name, {}), name)
            local_aliases = set()
            for bucket in ("characterInsts", "tokenInsts"):
                for i, item in enumerate(array(predefined.get(bucket, []), f"{name}.{bucket}")):
                    self.position(item.get("position"), f"{name}.{bucket}[{i}].position")
                    alias = item.get("alias")
                    require(isinstance(alias, str) and alias not in local_aliases, f"{name}: duplicate or missing alias")
                    local_aliases.add(alias)
                    if "characters" in self.tables:
                        character_key = obj(item.get("inst"), f"{name}.{bucket}[{i}].inst").get("characterKey")
                        require(character_key in self.tables["characters"].get("characters", {}),
                                f"{name}.{bucket}[{i}]: character {character_key} missing table")
            self.aliases.update(local_aliases)
        for wi, wave in enumerate(array(self.level.get("waves"), "waves")):
            wave = obj(wave, f"waves[{wi}]")
            number(wave.get("preDelay"), f"waves[{wi}].preDelay", 0)
            number(wave.get("postDelay"), f"waves[{wi}].postDelay", 0)
            number(wave.get("maxTimeWaitingForNextWave"), f"waves[{wi}].maxTimeWaitingForNextWave", -1)
            for fi, fragment in enumerate(array(wave.get("fragments"), f"waves[{wi}].fragments")):
                number(fragment.get("preDelay"), f"waves[{wi}].fragments[{fi}].preDelay", 0)
                for ai, action in enumerate(array(fragment.get("actions"), "fragment.actions")):
                    path = f"/waves/{wi}/fragments/{fi}/actions/{ai}"
                    self.declarations.append(self._declaration(action, path, self.routes))
        for key, branch in obj(self.level.get("branches", {}), "branches").items():
            records = []
            for pi, phase in enumerate(array(branch.get("phases"), f"branches.{key}.phases")):
                number(phase.get("preDelay"), f"branches.{key}.phases[{pi}].preDelay", 0)
                for ai, action in enumerate(array(phase.get("actions"), "phase.actions")):
                    records.append(self._declaration(action, f"/branches/{key}/phases/{pi}/actions/{ai}", self.extra_routes))
            self.branch_declarations[key] = records
        integer(self.level.get("randomSeed"), "randomSeed")
        if "enemies" in self.tables:
            database = obj(self.tables["enemies"].get("enemies"), "enemies.enemies")
            for key, ref in self.enemy_refs.items():
                require(key in database, f"Enemy {key} missing database")
                levels = array(database[key], f"enemies.{key}")
                require(any(x.get("level") == ref["level"] for x in levels), f"Enemy {key} missing level {ref['level']}")
        if "topics" in self.tables:
            topics = obj(self.tables["topics"].get("topics"), "topics.topics")
            for tag in map_data.get("tags", []):
                if tag.startswith("rogue_"):
                    require(tag in topics, f"Map tag {tag} missing roguelike topic")
        if "characters" in self.tables and "skills" in self.tables:
            characters = obj(self.tables["characters"].get("characters"), "characters.characters")
            skills = obj(self.tables["skills"].get("skills"), "skills.skills")
            for key, character in characters.items():
                for skill in character.get("skills", []):
                    skill_id = skill.get("skillId")
                    if skill_id and skill_id not in skills:
                        # A table snapshot can be incomplete outside this level. Preserve
                        # the gap instead of silently supplying an invented skill.
                        self.table_reference_gaps.append({"character": key, "missing_skill": skill_id})
        self.warnings = [
            "Structural checks do not verify field semantics or runtime behavior.",
            "Main-wave and branch array order is preserved; it is not a battle execution timeline.",
            "E_NUM route placeholders are retained and cannot be navigated.",
            "Dataset preserves declarations; conditional TimelineEnv and independent Rogue preprocessing are separate components.",
            "Live RNG state/consumption, complete enemy attributes/creation, mode hooks, automatic branch triggers and combat remain unverified.",
        ]

    def summary(self) -> dict:
        actions = [record["action"] for record in self.declarations]
        blockers = sorted({key for action in actions for key in ("hiddenGroup", "randomSpawnGroupKey") if action.get(key)})
        tags = self.level["mapData"].get("tags", [])
        topics = self.tables.get("topics", {}).get("topics", {})
        level_id = self.provenance.get("level_id")
        stage_records = []
        for tag in tags:
            detail = self.tables.get("topics", {}).get("details", {}).get(tag, {})
            for key, stage in detail.get("stages", {}).items():
                if level_id and stage.get("levelId", "").rsplit("/", 1)[-1].lower() == level_id.lower():
                    stage_records.append({k: stage.get(k) for k in ("id", "name", "levelId", "difficulty", "description")})
        return {
            "scope": "data_and_declaration_probe",
            "schema_status": self.provenance.get("schema_status", "unknown"),
            "dimensions": {"rows": self.rows, "cols": self.cols},
            "logical_coordinate_mapping": "matrix_row = height - logical_row - 1; matrix_col = logical_col",
            "coordinate_access_status": "recovered_from_static_native_code",
            "tile_types": dict(Counter(t["tileKey"] for t in self.tiles)),
            "routes": len(self.routes), "extra_routes": len(self.extra_routes),
            "route_modes": dict(Counter(r["motionMode"] for r in self.routes)),
            "waves": len(self.level["waves"]), "main_declarations": len(actions),
            "declaration_types": dict(Counter(a["actionType"] for a in actions)),
            "spawn_count_sum_including_alternatives": sum(a["count"] for a in actions if a["actionType"] == "SPAWN"),
            "branches": {key: len(value) for key, value in self.branch_declarations.items()},
            "enemy_references": len(self.enemy_refs),
            "topics": {tag: topics.get(tag, {}).get("name") for tag in tags},
            "stage_records": stage_records,
            "table_counts": {"characters": len(self.tables.get("characters", {}).get("characters", {})),
                             "skills": len(self.tables.get("skills", {}).get("skills", {})),
                             "enemy_database_ids": len(self.tables.get("enemies", {}).get("enemies", {}))},
            "table_reference_gaps": self.table_reference_gaps,
            "client_level_seed": self.level["randomSeed"],
            "declaration_control_group_keys": blockers,
            "conditional_timeline_available": True,
            "conditional_timeline_status": "static_scheduler_kernel_with_explicit_external_group_choices_enemy_runtime_and_gate_inputs",
            "schedule_blockers": ["live RNG state and enumeration/consumption order", "complete enemy attribute inheritance and creation",
                                  "game mode hooks and live gate outcomes", "automatic branch triggers", "combat lifecycle/damage"],
            "warnings": self.warnings,
        }

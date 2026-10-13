"""Read-only selected prefab Transform/Collider/Rigidbody declarations.

No object instantiation and no Unity query. The parent chain terminates at the
serialized prefab root; its runtime instantiation parent/pose remain unknown.
"""
from pathlib import Path
import hashlib
import json
import sys

OUT = Path(__file__).resolve().parent
BASE = OUT.parents[1]
V2 = BASE / "resources_v2"
sys.path.insert(0, str(V2))
from ark_bundle import load

GAME = Path(r"D:\Hypergryph Launcher\games\Arknights\Arknights_Data\StreamingAssets\AB\Windows")
BUILTINS = {"BoxCollider2D", "CircleCollider2D", "PolygonCollider2D", "EdgeCollider2D",
            "CapsuleCollider2D", "CompositeCollider2D", "Rigidbody2D"}
NAMES = {"enemy_1034_laxe", "enemy_2133_shdopl", "enemy_3001_upeopl", "sktok_ore", "trap_011_ore"}


def pin(path):
    return {"path": str(path), "bytes": path.stat().st_size,
            "sha256": hashlib.sha256(path.read_bytes()).hexdigest()}


def object_record(obj):
    return {"path_id": obj.path_id, "type": obj.type.name,
            "serialized_sha256": hashlib.sha256(obj.get_raw_data()).hexdigest(),
            "fields": obj.read_typetree()}


def run():
    fixture_path = BASE / "native_v4" / "resources" / "prefab_inputs.json"
    index_path = V2 / "normalized" / "resource_index.json"
    fixture = json.loads(fixture_path.read_text("utf-8"))
    index = json.loads(index_path.read_text("utf-8"))
    mappings = [p["asset_mapping"] for p in fixture["prefabs"] if p["asset_mapping"]["name"] in NAMES]
    assert {a["name"] for a in mappings} == NAMES
    script_path = GAME / "anon" / "88b3c3ecaaefa6003de730686dd5ac53.bin"
    script_env = load(script_path)
    scripts = {(o.assets_file.name, o.path_id): o.read_typetree()
               for o in script_env.objects if o.type.name == "MonoScript"}
    loaded = {}
    records = []
    for mapping in mappings:
        source = GAME / index["bundles"][mapping["bundleIndex"]]["name"]
        if source not in loaded:
            loaded[source] = load(source)
        env = loaded[source]
        root = env.container[mapping["path"]].deref()
        objects = root.assets_file.objects
        root_fields = root.read_typetree()
        root_transforms = [objects[x["component"]["m_PathID"]] for x in root_fields["m_Component"]
                           if objects[x["component"]["m_PathID"]].type.name == "Transform"]
        assert len(root_transforms) == 1
        todo = [(root_transforms[0], mapping["name"])]
        nodes, colliders, bodies, rules, unresolved = [], [], [], [], []
        visited = set()
        while todo:
            transform, hierarchy_path = todo.pop()
            assert transform.path_id not in visited and len(visited) < 2048
            visited.add(transform.path_id)
            tf = transform.read_typetree()
            go_ptr = tf["m_GameObject"]
            assert go_ptr["m_FileID"] == 0
            go = objects[go_ptr["m_PathID"]]
            go_fields = go.read_typetree()
            nodes.append({"hierarchy_path": hierarchy_path, "game_object": object_record(go),
                          "transform": object_record(transform)})
            for entry in go_fields["m_Component"]:
                ptr = entry["component"]
                if ptr["m_FileID"] != 0 or ptr["m_PathID"] not in objects:
                    unresolved.append({"hierarchy_path": hierarchy_path, "component_pointer": ptr})
                    continue
                obj = objects[ptr["m_PathID"]]
                if obj.type.name in BUILTINS:
                    row = object_record(obj)
                    row.update(hierarchy_path=hierarchy_path, game_object_path_id=go.path_id,
                               game_object_layer=go_fields["m_Layer"], active_self=go_fields["m_IsActive"])
                    (bodies if obj.type.name == "Rigidbody2D" else colliders).append(row)
                elif obj.type.name == "MonoBehaviour":
                    fields = obj.read_typetree()
                    ptr = fields["m_Script"]
                    cab = obj.assets_file.name if ptr["m_FileID"] == 0 else obj.assets_file.externals[ptr["m_FileID"]-1].name
                    identity = scripts.get((cab, ptr["m_PathID"]))
                    if identity is None:
                        unresolved.append({"hierarchy_path": hierarchy_path, "script_pointer": ptr, "external_cab": cab})
                    elif identity["m_Namespace"].startswith("Torappu.Battle") or identity["m_ClassName"] == "CircleColliderOverlapFixed":
                        row = object_record(obj)
                        row.update(hierarchy_path=hierarchy_path,
                                   class_name=".".join(x for x in (identity["m_Namespace"],identity["m_ClassName"]) if x),
                                   assembly=identity["m_AssemblyName"], script_path_id=ptr["m_PathID"], script_external_cab=cab)
                        rules.append(row)
            for ptr in tf["m_Children"]:
                if ptr["m_FileID"] != 0 or ptr["m_PathID"] not in objects:
                    unresolved.append({"hierarchy_path": hierarchy_path, "child_transform_pointer": ptr})
                    continue
                child = objects[ptr["m_PathID"]]
                child_fields = child.read_typetree()
                child_go = objects[child_fields["m_GameObject"]["m_PathID"]].read_typetree()
                todo.append((child, hierarchy_path+"/"+child_go["m_Name"]))
        records.append({"name": mapping["name"], "asset_mapping": mapping, "source_pin": pin(source),
                        "asset_file": root.assets_file.name, "root_path_id": root.path_id,
                        "root_transform_path_id": root_transforms[0].path_id,
                        "nodes": nodes, "colliders": colliders, "rigidbodies": bodies,
                        "rule_components": rules, "unresolved_references": unresolved})
    output = {"format": "selected_prefab_physics_declarations_v1", "input_pins": [pin(fixture_path), pin(index_path), pin(script_path), pin(V2/"ark_bundle.py")],
              "prefabs": records, "limits": ["Serialized prefab declarations only; no object allocation/instantiation/query.",
                  "Full local descendant/parent Transform chain supplied; runtime root parent, world pose and physics state remain external.",
                  "No AABB intersection or third-party physics engine used."]}
    (OUT/"prefab_physics_inputs.json").write_text(json.dumps(output, ensure_ascii=False, indent=2), "utf-8")
    print(json.dumps([{"name": r["name"], "nodes": len(r["nodes"]), "colliders": [(c["hierarchy_path"], c["type"], c["game_object_layer"]) for c in r["colliders"]],
                       "bodies": len(r["rigidbodies"]), "unresolved": len(r["unresolved_references"])} for r in records], ensure_ascii=False, indent=2))


if __name__ == "__main__":
    run()

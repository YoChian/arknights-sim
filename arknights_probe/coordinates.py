"""Coordinate indexing recovered from this PC GameAssembly snapshot.

This proves tile access, not full enemy navigation or runtime replay fidelity.
"""

NATIVE_COORDINATE_EVIDENCE = {
    "kind": "static_native_decompilation",
    "target_sha256": "583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5",
    "report_path": r"D:\Repo\.rea-tools\arknights-pc\native_v2\focused_results_round2.json",
    "report_sha256": "1dd60f0a4101063b9d6095a0f23acb080fefd9c40c0ed22def1e68662652761a",
    "get_item_addresses": ["0x18241d270", "0x18241d1e0"],
    "get_height_address": "0x18241d300",
    "get_width_address": "0x18241d330",
    "formula": "tile_index = matrix[height - logical_row - 1, logical_col]; tile = tiles[tile_index]",
    "limits": "Analyst symbol candidates matched metadata/pointer tables and PE unwind entries; static evidence only. "
              "No claim about full pathfinding, movement, collision or hot-patch runtime behavior.",
}

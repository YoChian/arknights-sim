# Native v6 targeting handoff

Current implementation: `D:\Repo\arknights-sim\arknights_probe\targeting.py`. Tests: `test_targeting.py` (23) and `test_targeting_reference.py` (2), all pass. Reviewed evidence: `D:\Repo\arknights-sim\evidence\targeting\native_evidence.json`; detailed report in that directory. Root integration owns CLI/verification/docs; this investigator has not changed them or any v5 pins.

The real `sktok_ore/Selector` is AdvancedSelector + AutoLoadBoxRange, not GridPositionRange. Real x-1 grids produce three overlapping local BoxCollider2D declarations. Continuous target bodies and Unity Physics2D decide overlaps. The module requires the caller to supply **each cached collider's ordered collider→Entity result**, absolute query/source/opposite masks, live predicates with provenance, and **external ALL order**. There is no generated Physics2D overlap or native ALL comparator in this stage.

`construct_range_boxes(grids,direction=1)` returns RangeBox(minimum,size), `.center` preserves Single multiply/add. `select_altar_targets(OverlapQuerySnapshot,AltarSelectorContext,AllPostFilterSnapshot)` returns hit snapshots in supplied ALL order, collector_uids, per-query exclusions, cap and provenance. Real x-1 has three initial colliders; an actual-cache fixture must explicitly account for all three, even if two return empty results. A one-collider snapshot is only a separate explicit cache fixture, not proof that the real x-1 cache has one collider.

The collector stops at the 128th admission **before** deterministic unsigned UID sorting; rejected targets are not deduped. Immutable snapshot and complete postfilter permutation are deliberate adapter restrictions. Missing provider/status/mask/count/order or conflicting mutable UID context fails closed. `battle_ready=false`, `runtime_battle_validated=false`.

51 unique requested function addresses from selection.json + selection_extra.json have complete imported-source coverage in root v6 round1-3; two BObject.CompareTo entries were already parent selections, so this is selected-coverage count, not 51 additional Ghidra jobs. Six additional short getter/UInt32 helpers were restored by exact PE ranges in raw_helpers.json, without Java.

Corrections retained for future review:

- `selection_extra.json` originally asked whether SafeBounds had edge epsilon; final native result has **no epsilon**. MapUtil.InBounds is inclusive XY; it is a point diagnostic, not Physics2D overlap.
- `0x186b59040` is Behaviour.get_isActiveAndEnabled, not GameObject.activeInHierarchy. Transform helper `0x186b74fb0` used here is get_localPosition, not get_position.
- BObject.instanceUid and helper `0x185ee3720` are **UInt32**. A provisional Int32 helper label in earlier root selections was incorrect. Raw JB/SETA and exact metadata241404/0x6000cbf prove unsigned comparison.
- Virtual dispatch is `(klassOffset-0x140)/16`; the collector's raw helper argument40 is **Entity.alive**, not validAndBorned. Do not infer all virtual identities from shared addresses.
- methodInfo slots prove actual List<Entity>.Sort and Filter<Entity> generic identities. The first alias at a shared generic address does not establish these types.
- ALL is a native weighted SortedSet path; neither stable collector order nor a Python createdTime sort is established. External permutation adapter is explicitly restrictive, not proof of native membership preservation.

Independent C# reference: 148 geometry cases and 112 collector contexts; all exact tested Single bits/order/admission decisions match Python. Source-owned inputs, external Physics2D/status and reversal ALL fixture; not a client oracle.

Next native work should close target Collider2D/UBody world geometry and Unity nonalloc query semantics/order/synchronization, then ALL delegate/gap/CompValue comparison/extra-mode closure. `REPORT.md` records exact known helpers and remaining targets. Do not broaden to automatic altar hits using grid membership.

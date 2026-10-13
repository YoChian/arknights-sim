# Targeting v7 handoff

Current implementation and scope: [REPORT.md](REPORT.md). The separate module is `D:\Repo\arknights-sim\arknights_probe\targeting_runtime.py`; v6 pinned sources and reports were left unchanged.

Completed: exact PriorityQueue/WeightedTarget generic identities, canonical sharing/caller proof, native ALL Add/CompareTo/constructors, raw constants/FP overload checks, actual side-to-layer static derivation, purpose and createdTime/mapLayer getters, native abnormal counter/base-mask getters, HitRange aggregation, independent C# comparisons, immutable runtime interface, and explicit rejection of sandbox/hotfix/unknown input branches.

Important corrections retained in the report: provisional SortedSet/CompValue labels; BattleConsts/GameLayers labels; first-set-bit side assumption corrected to exact one-bit equality; FP.Equals overload is metadata220346 `0x1866e46f0`, not the double overload220367 `0x1866e47c0`; inherited field+0x26 is BObject.isDisappeared, rather than Enemy.Options.unharmful. SideTypes cctor decompiler marked an OPPOSITE array tail unreachable, but source-bound raw instructions show its final store.

Next closure: recover the actual continuous Collider2D/UBody geometry/transform chain and provider registrations, then obtain an explicit offline physics adapter or authorized client observations. Grid declarations and movement half-widths are insufficient to prove overlap membership. No target execution was performed in this stage.

# Lifecycle handoff

New component is `D:\Repo\arknights-sim\arknights_probe\npc_lifecycle.py`; shared actor identity and all required flags/receipts are explicit. No v8 file was edited.

Finish7 synchronously runs Entity/Unit/Enemy OnFinish, event6, default immediate recycle, UID0, conditional event8 and pool receipt before the outer Enemy mode hook. Death2 yields the recovered Single delay through the shared simulator. Buff callbacks can use NpcBuffContainer.on_owner_finish/clear/on_target_killed through parent adapters; the child module does not own container traversal.

OnGameReset directly binds6 and conditionally8. Exact event delegate/generic identities are in subscription_identities.json; old reflection/unknown-binding statements are historical. Same-address LuaMsgHandlerCallback labels are corrected without editing old pins. Unresolved helper184257960 is recorded as cleanup, not falsely assigned VisualObject.OnRecycle.

22 tests and the C# comparisons pass. Fixed manifest will be `D:\Repo\arknights-sim\evidence\npc_lifecycle\native_evidence.json`. Generic Unity equality/full pool/EventPool/animation/bootstrap and complete map win remain unimplemented or providers; see REPORT.md for evidence and precise boundaries.

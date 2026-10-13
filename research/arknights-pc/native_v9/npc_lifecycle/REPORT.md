# Selected NPC finish and recycle closure

All observations below come from the pinned original PC GameAssembly and metadata. No game process, engine, service, injection or write to the client was used. `npc_lifecycle.py` is a new composition component and does not edit any v5–v8 module or remove the older ordinary lifecycle's NPC guard.

## Finish7 and death2 ordering

`Enemy.FinishMe` 0x180a6d0d0 (metadata76484, v4 creation round2) enters DeadState5 for reasons2/8, logs its snapshot/statistics and death bookkeeping, calls `Entity.FinishMe`, then still invokes the controller/mode enemy-finished wrapper. The new runtime supports reason2 and reason7 only. Repeating reason7 retains the outer snapshot/statistics/mode hooks; it does not silently re-run the guarded Entity finish or pool callback.

Original `Entity.FinishMe` 0x1806f3360 tests `unfinished`, sets finishReason, stops the state machine, clears the dialog-target flag, calls virtual OnFinish, and only then calls mode.DestroyEntity. The new raw getter evidence verifies `Entity.get_unfinished` 0x180708ee0 -> `get_finishReason` 0x180703fa0 -> integer zero comparison. Thus the base guard is finishReason==0, not an added alive/HP/UID predicate. Stopped state/alive/finishReason are synchronized to the same supplied NpcEntity/FactoryEnemy instance.

`Entity.OnFinish` 0x1806f8c40 captures the resolved context source before owner Buff callbacks. For death, it emits source OnTargetKilled and own event1, then calls BuffContainer.OnOwnerFinish(reason, source), BuffContainer.Clear(true), ClearAbilities/hold effects/EP cleanup and Entity event2. These Buff calls can be connected to the new container by the parent adapter; this component requires the provider and does not fabricate Buff membership.

`Unit.OnFinish` 0x180aca5b0 performs base Entity work, animator/mode/visual cleanup, then controller event6 unless isDummy. `Enemy.OnFinish` 0x180a70920 follows with level event3, tile/blocker and skill cleanup. The new runtime's named phase providers preserve this relative order, but their omitted visual/registry/level-script bodies are not asserted as implemented.

`DefaultGameMode.DestroyEntity` 0x180c18e70 selects RecycleSelfWithDelay for death reasons and exit1. Other reasons, including7, call RecycleSelfImmediately regardless of the stored delay. Reason7 therefore executes the logical OnRecycle chain synchronously inside the Buff action's call stack. Death2 uses the existing shared coroutine simulator and Single wait conversion; active Unity coroutine-owner availability is separate from Entity.alive.

## Death animation boundary

Enemy nested `Torappu.Battle.Enemy.States.DeadState` is metadata owner of method76666 at0x180a8b390; another character DeadState method76171 is not the same class. OnEnter releases the blocker, calls GetAnimationTime, optionally plays the specific animation, and calls _PlayAnimation76669 at0x180a8b6a0. The virtual call at klass+0x580 is metadata slot68 `get_delayToRecycle`; it is not a move/animation speed getter. If a specific dead animation exists and `_useSpecificDeadAnim` is true, m_delayToRecycle+0x4c8 receives the animation duration. The generic visual effect/Tween branch does not perform that duration assignment.

`DeadAnimationReceipt` therefore supplies the unclosed GetAnimationTime result and visual work. This component never invents an animation duration from a prefab name. Existing serialized selected NPCs' specific-dead-animation flag can be passed as a source input; an actual initialized animator/animation result remains external. All duration arithmetic entering the shared wait is explicitly Single. The independent reference checks epsilon and round-to-even frame boundaries, not a Unity animation timeline.

## OnRecycle and object identity

New `Unit.OnRecycle` 0x180acb160 confirms root/mode dynamic-ability recycling first, then UnregisterUnit, talent callbacks, shadow/graphic cleanup/GraphicFollow.ReleaseAll, and inlined Entity cleanup/ClearAbilities. `BObject.OnRecycle` 0x1806629d0 and the Entity-inline path call UnregisterBObject before clearing instanceUid+0x18. `BattleController.UnregisterBObject` 0x180634dc0 is separately checked in original raw bytes. The new wrapper does not claim those registry/visual bodies ran in Unity; it records the required providers and their order.

`Enemy.OnRecycle` 0x180a71770 then handles recycle Tween/cursor/route cleanup, invokes GroundBoundController.OnRecycle if that initialized controller exists, tests the controller singleton predicate, and emits event8 in that branch. A missing GroundBoundController does not receive an invented event8: final membership is retained. `controller_exists` is the supplied predicate at this post-cleanup check; it is not a claim about all earlier singleton calls or bootstrap.

The UID is already zero at event8. Native list operations address the Enemy object, so the selected logical backend matches the same supplied NpcEntity identity rather than comparing UID or the Python lifecycle wrapper. Different wrappers of the same entity match; different entities sharing a fixture UID do not. Managed/future list and cache membership are decoded logical snapshots, not a reconstruction of arbitrary Unity object equality, ListSet backing internals or Dictionary enumeration. The supplied future-group order preserves the recovered first-success removal branch. Returning to a pool does not itself prove Unity destruction: `PoolRecycleReceipt` separately supplies post-pool existence and activation.

## Scheduler events and accounting

The previous v5 report's “binding still unknown” is now resolved for a concrete reset entry. `Scheduler.OnGameReset`72077 at0x1809146a0 directly subscribes event6 to `_OnUnitDestroyed`72143 and, only when useRecycleToFinishScheduler is true, event8 to `_OnEnemyRecycled`72145. Exact MethodInfo usages:

| Slot | Original identity |
|---|---|
| 0x18896eae0 | kind3, method72143 Scheduler._OnUnitDestroyed |
| 0x18896e8a0 | kind3, method72145 Scheduler._OnEnemyRecycled |
| 0x1888797f0 | Torappu.EventPool.EventCallbackDelegate |
| 0x188811de0 | MethodSpec EventPool`1.On, class argument Torappu.Battle.BattleEvent |

The same-address decompiler label LuaMsgHandlerCallback.ctor does not identify the actual delegate. The raw RIP scan locates these references solely at OnGameReset within its stated MOV/LEA scan boundary. No reflection subscription is inferred from method attributes; the prior empty attribute arrays remain unchanged. The runtime represents the first reset of an explicit fresh pool and a constant config through selected synchronous handlers. Full EventPool ordering/reentrancy, repeated-reset removal/deduplication and complete BattleController startup remain outside it.

`_OnUnitDestroyed`0x18091bcb0 removes wave membership, cached membership and the first matching future group, and removes final immediately only when the recycling flag is false. isSummon requests runtime-route removal using spawnedCnt. dontCountAsFinished/isSummon suppress ordinary finished/killed/valid-finished accounting, but do not suppress list removal. Summons with unharmful=false and a non-death finish increment validMissed even when dontCountAsFinished=true. unharmful is not a general finish or damage-immunity gate.

Native fields are confirmed as finished+0x2c, killed+0x40, validFinished+0x54, validKilled+0x68 and validMissed+0x7c. Override-kill mode uses the override integer for death validKilled and clamps a negative wrapped sum to zero; positive overrides admit validFinished/non-death validMissed. The runtime applies unchecked Int32 numeric semantics to explicit decoded counters. It does not implement ObscuredInt encoding or anti-cheat state.

`_OnEnemyRecycled`0x18091bb70 only removes final after the Enemy/Unity-non-null check; it does not remove wave or increment counters. `_CheckFinalNotFinish`0x1809196f0 is exposed as a predicate over final/mode/blocking-key inputs, not as a complete map-win producer. One retained v3 decompile lacks an imported-memory verification field; its exact full original PE ranges are independently corroborated in new raw evidence. That distinction is preserved in source_audit rather than silently inventing the missing old check.

## API and verification

Module: `D:\Repo\arknights-sim\arknights_probe\npc_lifecycle.py`. Admit an initialized `NpcLifecycleActor` sharing its NpcEntity/FactoryEnemy; supply Options, live-instance controller/owner flags and sources explicitly. Configure SchedulerLedger with decoded counters, a route-removal provider, fresh-pool receipt and constant recycling flag. Call `NpcLifecycleRuntime.finish(actor, 7 or 2, finish_source=EntityPtr.capture(...))`; SharedCoroutineSimulator progresses positive death waits. NpcLifecycleHooks owns Buff calls and named omitted phases. No creation is substituted for an NPC.

22 tests passed:20 behavior and2 independent C# comparisons. The translated reference covers640 accounting cases /3200 counter outputs and96 lifecycle cases /2064 stage-frame-UID records. It is not a client oracle or a second full IEnumerator implementation. Source checks cover9 new decompiled entries,13 reused decompiled entries,7 reused raw helpers and5 new raw bodies:70 audited range records /19986 bytes, all matching original input (counts include repeated corroborated ranges). Static metadata output contains26 types/1296 fields/61 generic contexts.

Remaining dependencies are explicit: actual Unity pool/registry/visual/tween/animator callbacks, GetAnimationTime, live controller/owner predicates, full EventPool and mode/bootstrap, dynamic damage/HP post-write, scene progression and win request. `runtime_battle_validated=false`, `battle_ready=false`, and `full_map_win_generated=false`.

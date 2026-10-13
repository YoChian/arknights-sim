# NPC Buff membership and reentrant events

This component replaces the v8 explicit list of callback recipients with executable registration, UID lookup, priority ordering, shared snapshot iteration, finish marking, removal, and whole-container Clear. Nodes execute through the unchanged `NpcActionRuntime`; this module does not copy their implementations.

The recovered ordinary branches are static client evidence, not observations of a running client. The DLL and metadata hashes remain `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5` and `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`. No game code was executed, loaded, injected or modified; no network was used.

## List and mutation rules

`DoubleBufferedList<ObjectPtr<Buff>>.GetEnumerator` at `0x185a17960` and reversed enumerator at `0x185a17d40` increment UInt16 nesting at `+0x20`. Only the transition from zero copies live `+0x10` into snapshot `+0x18`. Nested forward and backward iterators share the same snapshot, with independent indices. Add, remove and clear mutate live immediately. There is no pending-add/remove commit queue.

The actual caller's encoded MethodInfo slots bind the closed Buff pointer list. Enumerator implementations are shared through the canonical `ObjectPtr<Object>` generic instantiation: the original function table binds the methods, and the Buff caller's direct ctor/reset calls independently match those addresses. These are candidate identities, not recovered source names.

Sorted Add (`0x180692370`) inserts into live, highest event priority first and new equal priority after existing equals. Invalid pointers append; backwards priority scanning skips invalid existing pointers. Remove (`0x180690a40`) scans live backwards, compares the current UID of valid objects, and removes one match. UID changes invalidate captured snapshot entries immediately. Removing live membership alone does not invalidate the captured object pointer.

Forward MoveNext (`0x184916b00`) increments index from -1 and compares with snapshot count; backwards (`0x18558e590`) starts at count and decrements. Dispose (`0x184916960`/`0x18558e3f0`) marks the iterator disposed before invoking its owner callback. Owner callbacks (`0x185a18c10`/`0x185a18a90`) decrement nesting and push the iterator into the relevant LIFO pool; they do not clear the snapshot or commit mutations. Reset restores the starting index and disposed flag. Repeated Dispose logs a native error without a second decrement. The Python API explicitly rejects invalid use after Dispose and nesting overflow.

## Registration, activation and events

`NewBuff` (`0x180668f20`) checks finished members, applies creation filters, obtains and resets a Buff, then inserts its ObjectPtr and UID dictionary entry. It calls OnStart immediately only when owner `BObject+0x24` is active. OnStart (`0x1806872e0`) runs event 0 **before** setting `m_started+0x1f9`, then delivers other-Buff/owner notifications. Enabling occurs after OnStart in the registration tail. The component starts at an explicit, prepared post-Reset receipt and implements that tail.

`set_isEnabled` writes manually-enabled `+0x1ff`, then `_UpdateIsEnabledIfNotFinished` (`0x18068dc50`) computes actually-enabled `+0x1fd`. The implemented no-suppression branch uses manually-enabled directly. Enabling writes actual/late enabled before AddModifier and event24; disabling writes actual false before RemoveModifier and event25. Modifier writes remain explicit providers. Selected templates have no events24/25/32/36/45.

`OnOwnerBorn` (`0x1806758e0`) calls Buff `0x1806860a0` event12; PostBorn (`0x1806767d0`) calls Buff `0x180686740` event35. Both filter finished or disabled members. **Neither calls OnStart.** The factory worker independently confirmed Unit.OnBorn's tail calls the latter exact Buff address: “AfterBorn” was an informal label, not another metadata method.

For the bounded infinite/no-trigger/no-delta-preprocessing shape, `tick(delta)` implements both passes of BuffContainer.Tick (`0x18067bb10`). First, needRemove causes finish/removal; otherwise Buff.OnTick (`0x180687830`) starts unfinished, unstarted Buffs, even when disabled. It accumulates existingTime; finite remainingTime and trigger/status/EP/slowdown paths are rejected. Second, Buff.OnLateTick (`0x1806851c0`) tests !finished, enabled and lateEnabled, clears lateEnabled before event32 and owner notification. A separate outermost second pass can see Buffs added during the first; nested passes still share the enclosing snapshot.

Exact fixed phase ordering is `Entity.OnTick 0x1806fadf0 → BObject.OnTick → StateMachine.Tick(this+0x38), return 0x1806faeab → BuffContainer.Tick, return 0x1806faecc → action/HP/EP/SP/ability branches`. Unit.OnTick `0x180acbdb0` calls Entity first. The NPC pipeline must execute FSM before Buff Tick; this component does not choose object or coroutine order.

OnOwnerFinish (`0x180675d90`) tests pointer validity only. It does **not** mark Buffs finished and does **not** filter finished/disabled members. It invokes the existing Buff.OnOwnerFinish dispatcher: death reasons select event3, reason7 does not, and event4 is delivered afterwards. Normal completion disposes the iterator then checks finished Buffs.

OnTakeDamage (`0x1806795e0`) begins a Context change guard, iterates valid and !finished/disabled Buffs, sets the current Modifier snapshot before each Buff call, then invokes Buff.OnTakeDamage (`0x1806873c0`). The latter checks only whether event10 has actions; there is no cancelled, amount, isDamage or bypass filter in this branch. It writes the returned Modifier back. Reviewed NPC nodes do not read/write Modifier, so this module accepts the root packet protocol and preserves the packet; it does not implement arbitrary Modifier nodes or HP application. Context modifier visibility to external callbacks is a scoped side channel, not a claim that the unchanged v8 Snapshot represents all native Context fields.

OnTargetKilled is bounded to selected templates' empty event9. Raw bodies bind `0x180679d00 → 0x180687760` and the original Context target push/pop. The component retains member filtering/cleanup; nonempty target-killed action Context shapes are rejected.

## Finish, removal and reentry

FinishBuffsById's no-stack branch actually calls Entity.RemoveBuffs `0x1806fbef0 → container 0x18067b160`. It compares buffKey exactly and calls MarkFinish(true). The caller's updateOverrideMap argument is ignored in this no-stack branch. MarkFinish (`0x180681cc0`) disables, sets `m_isFinished+0x1fa`, clears derived Buffs, and optionally updates override state. It does not execute event1, remove membership or request pool recycling.

`get_isFinished` (`0x18068ee40`) is marked-finished OR (started AND MathUtil.IsZero(lifetime)). IsZero uses FP.Abs and strict `< EN5`, where EN5 raw is 42950. FP.Abs maps Int64.MinValue to FP.MaxValue. Values exactly ±42950 are not zero; there is no guessed duration or epsilon-inclusive comparison.

`_CheckFinishedBuffs` (`0x18067e5b0`) traverses the reversed snapshot. `_FinishAndRemoveBuff` (`0x18067f8e0`) removes from live and the UID map **before** `_FinishBuff`. `_FinishBuff` (`0x18067f9d0`) marks, then tests/sets actually-finished `+0x1fb` **before** event1, attribute removal, owner notification and pool request. The actually-finished flag prevents duplicated finish side effects during reentry. Invalid entries are pruned from live only outside a loop.

Clear (`0x180664a90`) has two passes. The first calls `_FinishBuff(updateOverride=false,recycleNextFrame=true,isOwnerFinished=input)` on valid snapshot members. The second handles valid members which still are not actually finished: remove modifier and request immediate recycling, without another MarkFinish/event1. This includes a Buff added during a callback when the second pass takes a fresh snapshot. Then live, override and UID maps are cleared. Pool allocation/UID changes and the next-frame scheduler remain explicit providers; deferred requests do not invent immediate UID invalidation.

In the owned fixture, event10 on the actual registered additional finish Buff executes restoration, reappearance and host-passive marking, then Finish7 synchronously reenters actual child membership. Event4 restores a second time before Clear. InstantKill returns false, so the previous-result guard stops lock/Clear action nodes. Host passive remains registered but marked until its own cleanup phase. Reason2 reaches real Dead membership, subtracts one life and performs one restoration. The audio-only Dead Buff is retained with an explicit CreateBuff/audio provider. These counts are tested consequences of supplied UID/pool/mode callbacks, not universal live-run guarantees.

## API and explicit boundaries

`NpcBuffContainer(owner, actions, hooks, no_hotfix=True)` shares the same `NpcEntity` identity as factory/lifecycle. Methods are `add_initialized(buff, BuffInitShape, owner_active=bool)`, `add_initialized_many`, `on_owner_born`, `on_owner_post_born`, `tick(FP)`, `on_owner_finish(reason, finish_source=None)`, `on_take_damage(packet)`, `on_target_killed(target)`, `finish_buffs_by_id(key, excluded_buff=None, dec_stack=False)`, `remove_uid`, `check_finished`, and `clear(is_owner_finished=False)`.

The receipt provides runtime lifetime, remainingTime, actual override key and filter outcomes. Resource `lifeTime=0` for INFINITY does not prove a zero runtime lifetime; resource empty `overrideKey` with disableOverride=false does not prove a no-override runtime branch. Unknown creation filters, overrides/stack policy, derived Buffs, suppression/status changes, resistance/anti masks, durable Buffs, finite timer and trigger paths are rejected or remain explicitly named providers. `override_transition` receives register/mark/remove/clear boundary requests, may change enabled state through the container API, and never supplies event recipients. The container retains opaque override key receipts until Clear; its per-key clear notification is a provider protocol, not a native Buff action or a recovered override policy. Attribute writes, owner notifications and pool operations are required callbacks. `upeople_t_1` event3 uses an explicit audio/CreateBuff boundary; omitting that member is not an accepted shortcut.

## Verification

32 owned behavior tests pass, including ordinary real NPC action execution, synchronous Finish7 reentry, death2/-1, cancelled zero-amount event10, callbacks adding members during Clear, UID invalidation, exception disposal and strict scope gates. 192 deterministic mutation plans also match the independent C# reference. The C# program runs only source-owned code and is not a game oracle.

The original-byte audit checks 33 new decompiled entries / 70 ranges / 15,552 bytes; 18 reused entries / 38 ranges / 18,568 bytes; and 18 raw helpers / 24 ranges / 4,940 bytes. Counts are records, not a claim that every physical range is unique. Imported Ghidra and current original bytes match. All 75 files in the v8 NPC action manifest remain unchanged. `manifest.json` fixes the implementation, tests, evidence and their direct source dependencies.

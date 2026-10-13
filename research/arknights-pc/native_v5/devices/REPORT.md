# Device component recovery: installed PC artifact

The recovered timer, natural-SP, deterministic pre-delay, immediate-buff lifecycle and altar finish-action components are executable in `D:\Repo\arknights-sim\arknights_probe\devices.py`. They require supplied owner, selection and damage/mode contexts. They do not yet constitute a complete idle simulation of 猎犬病原.

Target `GameAssembly.dll` SHA256: `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`. Metadata SHA256: `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`. All analysis was static. No game process, constructor, hotfix interpreter or game service was used.

## Native evidence and implemented behavior

`native_manifest.json` pins 31 files, 104 selected decompilations from the parent's exclusive Ghidra rounds, 12 short helpers and the additional StartBattleCoroutine raw body. The verifier re-read 262 selected PE ranges, including recursively merged exact `UNW_FLAG_CHAININFO` siblings, and every body hash matched. Method tokens, metadata indices, PE offsets, range provenance and source hashes remain in the manifest. This count represents inspected native functions; it does not imply all behavior reachable from them is implemented.

| Component | Native evidence | Implemented boundary |
| --- | --- | --- |
| Periodic timer | UpdateMultiple `0x181e056c0`/25987; NextMultiple `0x181e05540`/25988; get_isReady raw `0x181e05930`/25982 | Subtract delta; ready when remaining `< FP_LARGE_EPS`; recover `max(0,floor(-remaining/period))+1`; advance period only when ready. Positive periods, nonnegative deltas and bounded int32 counts are required. |
| Natural SP | SpController.Reset `0x18070a360`/66745; OnTick `0x18070a1c0`/66751; get_isFull raw; DoSetSpInternal `0x1806f23c0`/66631 | Period `One/recoveryPerSec`. TIME mask required. Invalid/stopped/full early returns freeze timer. Recovery is an integer SP amount. A supplied owner setter controls clamps/admission; tests use an explicit clamping owner fixture. |
| Epsilon | MathUtil.LE `0x1866e5700`; IsZero `0x1866e5420`; cctor `0x1866e6e50`; earlier FP cctor | `FP_LARGE_EPS` is FP.EN5, `One / 100000`, raw **42950**. LE is strict `< b+EPS`. `FP.from_float32(0.00001)` gives a different raw value and is not substituted. |
| Deterministic pre-delay | EasyToStart `<OnWaitForPreDelay>d__16.MoveNext` `0x180f0eee0`/91868; AbilityStandard.CastDirectly `0x1805ce650`/63141; StartBattleCoroutine `0x180633110` raw round5; CoroutineSimulator.StartCoroutine `0x18065d200` from v3 round3 | Explicit `deterministic_simulator=True` required. StartBattleCoroutine's native/no-hotfix deterministic branch calls simulator StartCoroutine, which synchronously invokes RuntimeHandler.MoveNext. `begin` therefore primes immediately. Event-wait and target-death conditional waits are rejected. |
| Immediate buff | Buff.OnStart `0x1806872e0`/65143; NewBuff `0x180668f20`/65310; _FinishBuff `0x18067f9d0`/65369; get_isFinished raw | Takes an already verified FP lifetime and born-owner/admitted-buff path. OnStart actions precede `m_started=true`; a started near-zero-life buff is then synchronously finished. Finish idempotency flags are set before finish actions. Lifetime creation/override, sibling hooks and admission remain caller responsibilities. |
| Altar finish actions | Serialized `ore_s`/`ore_buff`, event1; FixedValueDamage.Execute `0x181057850`/96874; SwitchMode native result | On `ore_s` finish, request PURE/NONE damage only when target lacks `ore_immune`. Independently, `ore_buff` requests mode1 with FSM restart when target has `ore_listener`. Requests preserve target order supplied by the caller; they are not HP-loss or completed-mode-transition assertions. |

`Entity.DoSetSpInternal` clamps the supplied SP to `[0,maxSp]` after its virtual admission/force gate. `NaturalSpController` does not guess the gate or replace the owner setter. `BattleFormula.CalculateDamage` still calls target `OnBeingCalculateDamage` before `CalculateDamageNoEvent`; Entity.ApplyModifier and damage/finish hooks remain effective. PURE damage does not justify skipping those hooks.

## Verified component timing

With an explicit owner reset at frame0, recovery rate1, initial SP0 and delta raw143165440, SP increments at frames30,60,90,120,150,180,210. The first ten increments remain at multiples of30; residual error reaches the strict epsilon boundary and the eleventh increment is at331. This is a timer fixture, not the altar's full activation frame.

With a supplied `AT_BEGINING` target membership snapshot, pre-delay binary32(0.6), default delta and the explicit deterministic simulator branch, `begin` consumes one wait marker immediately. The spell callback runs on the eighteenth subsequent tick. Delay0 still waits one subsequent tick. The snapshot preserves object references/membership; target validity and damage admission must still be evaluated by the caller's closed path.

`tests/test_devices.py`: **16 passed**. Coverage includes epsilon boundaries, multiple periods, cumulative dt drift, SP early-return freezing/clamp callback, synchronous buff flag/event order, independent immunity/listener branches, immediate prime/snapshot timing, zero-delay and ties-even waits, missing-context rejection, and original native-range/file integrity.

`evidence/devices/DeviceReference.cs` and `run_reference.py`: **71 bounded C# versus Python checks passed**. This authored reference checks timer arithmetic, wait conversion/relative delivery and buff finished predicates across languages. It is an implementation check; it does not execute native client code and is not a client or hotfix oracle. Overflow/sentinel behavior beyond the bounded reference fixtures is not certified.

## Remaining for a complete idle scene

1. Actual allocated selector range kind/geometry, source-relative side snapshot, category/motion masks, target validity, abnormal flags and target-count ordering must be assembled. The signed resource provides the 13-cell `x-1` declaration but does not by itself prove continuous-position target inclusion.
2. AUTO CastSkill goes through Character skill-state/FSM transitions for the shipped altar (`_switchToState=true`). Init/born frame, state switching, interruption, cast admission, post-delay and cooldown remain separate closure work. Timer SP7 and a .6 wait alone do not establish an altar damage frame.
3. Buff.Reset lifetime/override mapping, owner-born/admission and all attached event hooks must be supplied. ImmediateBuffLifecycle accepts a verified duration; it does not instantiate or infer the full BuffConfig path.
4. Damage formula/hook ordering, Modifier construction flags, shields, undeadable/invincibility gates, Enemy HP/death and resulting scheduler events are not collapsed into `hp -= 500`. A request can be rejected or modified.
5. Ore-listener rage switching/modifiers, shdopl summon/return/damage behavior, upeopl death life-point penalty, shsdgo/skzjxd/duck passives and box inverse-damage/logging must be represented or explicitly rejected. Absence of deployed operators does not make these attached components inert.
6. Actual client's hotfix pointer state and deterministic flag were not observed. The separate Unity.MonoBehaviour.StartCoroutine branch was identified but not executed or modeled.

`verify_device_evidence(check_native_bytes=True)` reports `complete_idle_scene_supported=false` and these remaining boundaries. The complete scene must continue to fail closed where an active component lacks implementation.

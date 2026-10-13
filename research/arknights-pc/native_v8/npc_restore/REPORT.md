# NPC hidden / appear / route restore, v8

This is a bounded executable component for the shipped default/no-hotfix,
deterministic branch. It does not run the game or construct Unity objects.
The module is `D:\Repo\arknights-sim\arknights_probe\npc_restore.py`.

## Original evidence

Target `GameAssembly.dll` SHA256:
`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`.
Metadata SHA256:
`d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`.
`selection.json` and `selection_extra.json` identify exact method definitions,
tokens, owners and native pointers. DisappearState is Enemy.States definition
11377, including its nested coroutine 11375 and capture objects 11373/11376.
The similarly named other DisappearState is not used.

All 16 fresh Ghidra entries completed with imported-memory/original-range
matches. They cover 36 original PE ranges. `raw_helpers.json` independently
uses exact `.pdata` roots and recursive UNWIND_INFO CHAININFO for all 16 plus
three shared generic helpers: 19 functions / 39 ranges. `source_audit.json`
rechecks every range against the original file. This count does not imply
all functions called by them have been restored.

`DisappearState.OnEnter` 0x180a8d030 has a misleading Ghidra PIC warning at
0x180a8d16e: the C listing drops the default iterator-construction tail.
Raw instructions establish constructor -> write barrier ->
StartBattleCoroutine 0x180633110 -> stored CoroutineId. The missing C tail
is not used as evidence. The deterministic immediate-prime branch and shared
IEnumerator semantics reuse v5/v6 evidence; the Unity coroutine branch is
outside this component.

## Observed behavior and implementation

| Behavior | Native source | Bounded execution |
|---|---|---|
| BObject setter changes only nonzero UID, sends before-change hooks before writing flag | v7 SetDisappeared 0x180662be0 | Existing UID0 action succeeds with setter no-op; no alive gate |
| True flag requests state11; false flag faces from cursor and sends event23 without immediately leaving state11 | v7 Enemy.OnDisappearChanged 0x180a70650 | Explicit face/event providers; next state11 Tick sees cleared flag |
| OnEnter attaches state modifier and starts hide coroutine | 76777 0x180a8d030 | Modifier provider before immediate coroutine prime |
| Hide captures animator.color; RGB fade then alpha fade, both 0.15f; waits Single .3f | 76795 0x180a9da10, 76785/76786 | Two sequential Append requests, explicit Tween backend; float wait binary32 division and nearest-even/max1 |
| After wait, Kill(tween,true), then root GO SetActive(false) | same MoveNext | External completion-setter dispatch, then activation callback |
| Clear flag makes OnTick request DEFAULT0 | 76779 0x180a8d370 | No wait or tween-completion gate |
| DEFAULT0 resolves the registered default state, which Enemy construction sets to Move1 | v6 _SwitchStateInternal 0x182648540 + v5 States.ConstructStateMachine 0x180a9b3e0 | Requires explicit default-Move registration and admitted transition adapter |
| OnExit stops/invalidate coroutine, removes modifier, activates root GO, runs appearance | 76778 0x180a8d1f0 | Does not tick Move in the same state-Tick call; external Move/FSM hooks remain supplied |
| Appearance uses Entity.GetBodyColor snapshot, black/alpha1 initial color, alpha then RGB Append; no wait | 76781 0x180a8d440 + 76800/76801 | Body color and animator current color are separate explicit snapshots |
| disableAppearTweenColor=true kills old hide tween complete, restores body RGB/alpha1; clears one-shot flag | 76782 0x180a8dab0 + _DoAppear | No normal-branch implicit kill of old hide tween |
| ForceSet uses source current grid, optionally releases blocker, rechecks target Unity null, snapshots current pull list, reassigns source route/index | v7 ForceSetToSourcePosition 0x18107c4b0 | Grid/Unblock/kill provider; no continuous-world or original-spawn substitution |
| Route change preserves existing visit flags by OR, rebuilds every CP, Reset, then writes source index without clamp/new OnBegin | 70159 0x180875fa0 / 70269 0x180894bb0 / v7 Enemy.ReassignRoute / v4 Reset | Exact empty-CP Reset closure; nonempty CP creation/Reset must use explicit provider |
| DisableCurrentStillPull clears disabled set then adds current sources | 76436 0x180a6c480 | Copies unique ObjectPtr identity snapshot, does not kill pulls or suppress future new sources |

`dependency_identities.json` binds DOTween.Sequence/To/Kill/**Append** through
original codegen pointer-table records and exact metadata. This resolves the
sequential/parallel distinction. It does not recover DOTween easing, Tween
Update scheduling, callback order across different tweens or simulation of
the actual backend.

`state_enum.json` reads original literal values (DEFAULT0/MOVE1/DISAPPEAR11).
`native_fields.json`/`field_offsets.json` preserve 33 definitions, 1254 fields
and 54 generic instantiations, including inheritance/layout. Generic definition
layouts are not silently treated as concrete closed-generic layouts.
`resource_inputs.json` pins two NPC-related original prefab rule subtrees,
38 main and 2 extra level routes. No built-in physics geometry is inferred
from MonoBehaviour rule subtrees. `talent_prefix_constants.json` independently
pins StringComparison.OrdinalIgnoreCase=5 and original `{0}.` talent prefix
literal for the sibling NPC action component.

## API and explicit context

`NpcRestoreRuntime(context, simulator, clock, callbacks)` accepts the existing
SharedCoroutineSimulator. `clock()` returns `(frame,time_raw)`.

`NpcRestoreContext(source, native_default_no_hotfix=True, deterministic=True,
delta_play_time_float=FP(143165440).as_float(), default_move_registered=True,
active_hierarchy_matches_self=True)` rejects missing or different branches.
The final flag constrains the fixture to unparented objects or active parent
chains, since GameObject.SetActive tests activeSelf whereas coroutine owner
availability tests activeInHierarchy. Arbitrary inactive parent chains are
not emulated.

`NpcRestoreActor` requires identity/UID/Unity-null predicates, Enemy/giant
classification, grid, flag/state, activation, prepared cursor, separate
`body_color` and `render_color`. It intentionally has no alive gate.

`RestoreRoute(token, checkpoint_count, visit_every_tile_center,
visit_every_node_center, source, runtime_ready=True)` is an already prepared
runtime route reference. `RestoreCursor` carries route/index and current
visit/cache/CP state. No Route.Duplicate or native path generation is assumed.
Nonempty routes require `rebuild_and_reset_cursor` to create every CP and run
native Reset/OnBegin. The raw source index is then assigned without a second
OnBegin; old source wait/visited state is not copied. Existing visited-map
snapshots must be rectangular Boolean arrays matching the current Map.

Required callbacks: `set_active`, `set_grid_position`, `apply_state_modifier`,
`tween_start`, `tween_kill`, `face_from_cursor`, `move_tick`,
`before_disappear`, `disappear_changed`, `set_color`, `state_transition`.
`state_transition(actor,old,new)` explicitly supplies admitted transitions
and external Move hooks, returns exact True, runs before Disappear.OnEnter
for 1->11 and after Disappear.OnExit for 11->1. It is not native full-FSM
initialization, priority/CanSwitch policy or arbitrary reentrancy emulation.
Before-change provider supplies event30 and Buff on-disappear hooks; after
provider supplies event23. Modifier effects are external, not assumed inert.

`tween_start(actor,TweenRequest)` must return `TweenTicket(token,source)`.
The request supplies precise ordered segment fields and native setter
arithmetic. The backend explicitly drives progress and complete=True kill.
`set_disappeared(actor,bool)->bool`, `restore_to(target,source,
release_blocker=True,disable_still_pull=True,assign_route=True)->bool`, and
`tick(actor,FP)->bool` are the integration surface. Tick returns true only
when this call dispatched the supplied Move callback. `sync_owner(actor)`
must be used when external Unity existence/activation changes occur before
shared coroutine phases.

Empty blocker/no block Tween paths are verified no-ops. Nonempty blockers
and block Tweens require explicit native-backed providers. Unsupported states,
unprepared routes, unknown CP initialization, inactive-parent context, missing
modifier attachment and unknown Tween backend tickets fail closed. A failed
provider can leave partially performed native-order side effects; it must
terminate the probe, not be treated as a successful native tick.

## Validation and remaining limits

21 unit tests cover prime/order, hide wait, early/later flag clearing, state
Tick boundary, distinct color snapshots, one-shot bypass, UID0/no-change,
route identity/sticky flags/reset/index, ListSet snapshot, rejection gates,
release-destroys-target recheck, and 48 stored C# vectors recomputed with the
current Python module. `evidence/npc_restore/check_reference.py` compiles and
runs a self-authored C# IEnumerator reference; 48/48 vectors match on float
waiting/early-appear timing and Single color-product bits. **This is a
cross-language implementation check, not a real client oracle.**

For explicit dt raw143165440 with frame0 prime, hide deactivation occurs on
the ninth simulator tick. Clearing before a state Tick activates/appears on
that Tick; this bounded state dispatch first calls Move on the next Tick.
These are controlled component results, not whole Enemy/BattleController
or map timings. They must not be extrapolated into autonomous idle results.

Still external: actual DOTween update/easing/renderer/kill behavior; Unity
activation/event/physics registration; all Buff before-change dispatch and
state modifier effects; complete FSM gates, Move entry/exit and other-state
paths; nonempty checkpoint construction and map allocation; actual Unblock/
block Tween callbacks; source pointer/UID validity provided by npc_actions;
NPC finish/native mode pool integration. This module does not silently skip
active NPC talents or replace their Buff traversal with an empty list.
No target program or runtime constructor was executed, and no game files,
prior pinned snapshots or root integration files were modified.

The final child manifest is
`D:\Repo\arknights-sim\evidence\npc_restore\native_manifest.json`.

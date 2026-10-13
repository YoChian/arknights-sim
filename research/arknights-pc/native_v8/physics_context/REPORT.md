# Physics context and actual query boundary

`D:\Repo\arknights-sim\arknights_probe\physics_context.py` now exposes the shipped collider/body/local-transform declarations, the recovered scalar query arguments, the normal battle-frame query subsequence, and a strict external Unity result adapter. It does not simulate collisions or compute Unity world bounds. `physics_overlap_generated=false`, `runtime_battle_validated=false`, and `battle_ready=false`.

GameAssembly SHA256 is `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`; metadata SHA256 is `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`. UnityPlayer SHA256 is `ad54c51f443c5960a3df7c629f96b6aff57bc79d643db33f644927099c306fad`. Its Win32 file/product version is 2021.3.39.0 / 2021.3.39f1 (0). Version resources and all artifact reads are static; no client or engine was started.

## Actual serialized inputs

The extractor reads five exact resource-index mappings, includes built-in components and all local Transform descendants/parent links, and pins each AB/raw component. It exports 59 Transform nodes, seven colliders, four Rigidbody2D components and zero unresolved local references. The serialized root's eventual instantiated parent/world pose remains unknown.

| Prefab | Nodes | Root collider | Root layer | Rigidbody2D |
| --- | ---: | --- | ---: | --- |
| enemy_1034_laxe | 13 | Trigger CircleCollider2D, radius f32(0.1) | 9 | Dynamic=0, simulated=true, gravityScale=0 |
| enemy_2133_shdopl | 16 | Trigger CircleCollider2D, radius f32(0.1) | 9 | Dynamic=0, simulated=true, gravityScale=0 |
| enemy_3001_upeopl | 16 | Trigger CircleCollider2D, radius f32(0.1) | 28 | Dynamic=0, simulated=true, gravityScale=0 |
| sktok_ore | 2 | No serialized collider | — | None |
| trap_011_ore | 12 | Trigger CircleCollider2D, radius 0.25 | 9 | Kinematic=1, simulated=true |

Each enemy additionally has a non-trigger CapsuleCollider2D on `ColliderHolder`, layer19. Its width is f32(0.2). Laxe's height/offsetY are 0.40155452489852905 / -0.100777268409729; shdopl/upeopl use 0.40000003576278687 / -0.10000002384185791. These actual shapes are retained; movement half-widths and grid range declarations are not substituted for them. Skill range boxes are created later by the already recovered PhysicsRange/AutoLoadBoxRange path, rather than serialized on sktok_ore.

`static_inputs.json` records literal metadata enums: SimulationMode2D FixedUpdate=0, Update=1, Script=2; RigidbodyType2D Dynamic=0, Kinematic=1, Static=2. Physics2DSettings pathID15 in globalgamemanagers has initial simulationMode0, queriesHitTriggers=true and autoSyncTransforms=true. All three are initial asset values, rather than a live settings observation. The layer collision matrix is retained as data and is not used as an overlap algorithm.

## Recovered call boundary

The earlier PhysicsRange.DoFindTargets body `0x1809b6a30` saves Transform.localPosition (`0x186b74fb0`), obtains MapToWorldPosition, sets Transform.position (`0x186b75b30`), queries, and restores the saved position with the local setter (`0x186b75890`). Restoration is proven on normal return; no finally-based exceptional restoration was established. The module's pose contract only describes these operations and does not execute them or compose a runtime parent matrix.

Box2dPhysicsUtil._OverlapCollider `0x1809a6560` uses exact managed-class comparisons. Slots `0x188891d40` and `0x188958a18` decode to CircleCollider2D and BoxCollider2D. The Box branch reads Collider.bounds twice (`0x186bc29f0`), takes min from the first reading and max from the second, then calls Physics2D.OverlapAreaNonAlloc `0x186bc4460`. Bounds min/max are three Single subtractions/additions at `0x186b214b0`/`0x186b21470`. The area helper `0x186bc59b0` calculates center=f32(f32(A+B)*0.5), size=abs(f32(A-B)), angle0, and enters `PhysicsScene2D::OverlapBoxArray_Internal_Injected`. This is the actual query argument conversion; it does not establish any hit.

**Identity correction:** the initial investigation mislabeled the Circle center cache as a Rigidbody lookup. Exact slot `0x1888e14d8` resolves MethodSpec290350, methodDef282694 `UnityEngine.Component.GetComponent`, methodInst26066 whose type argument is **CircleColliderOverlapFixed (typeDef24)**. A cached true marker-existence result uses bounds.center; false uses Transform.position. Rigidbody presence does not control this branch. Extraction now explicitly checks this namespace-empty marker as well as Torappu.Battle scripts: none of the five serialized subtrees contains it. This bounded absence does not prove a live cache value, because runtime attachment/destruction/cache lifetime remain unclosed. The public Circle planner requires explicit `has_circle_overlap_fixed`; it has no default derived from Rigidbody declarations.

GetWorldRadius `0x1809a5fe0` reads Circle.radius and calls TransformVector(radius,0,0) through `0x186b744a0`. It then computes f32 component squares and two f32 additions, converts the sum to double, takes sqrt, and converts back to Single. The transform is external. The module only evaluates the magnitude of a supplied TransformVector result; it never replaces this path with radius*max(lossyScale).

Both query wrappers build ContactFilter2D via `0x186bc32d0`, using supplied layer mask, depth [-infinity,+infinity], and Physics2D.queriesHitTriggers. Flags useLayerMask/useDepth are initially true and outside-depth/normal-angle flags false. The constructor then calls the unresolved engine `CheckConsistency_Injected`. Thus a post-consistency 28-byte filter snapshot is mandatory; the initial payload is exposed separately and is not silently treated as final. Box2dPhysicsUtil.cctor `0x1809a6990` allocates the shared Collider2D result buffer with length 0x80=128. A full result prefix is valid but may be truncated; it is reported accordingly. Default physics-scene handle0 is present in the wrappers.

## Frame/synchronization contract

BC.OnTick `0x18062c440` orders ObjectManager fixed ticks, Map tick and scripts/operations before the optional manual Physics2D.Simulate, then after-physics callbacks, coroutines, registered ticks, global environment and late object ticks. This is a recovered subsequence; cost/deck/UI/dialog and the wider Unity event loop are not implemented here. The facade getter `0x1867460c0` returns simulationMode!=2; its setter `0x186746110` maps true->0 and false->2. Manual Simulate occurs only on mode2, before coroutines. An object-fixed query can therefore occur before that frame's manual Simulate.

PhysicsEpoch requires explicit mode, auto-sync, trigger and no-hotfix state, plus frame/phase/revision stamps. The revision numbers are caller diagnostic identifiers, not recovered native Unity fields. A result must match its exact query fingerprint and epoch. No actual synchronization or Simulate result is inferred merely because a phase is named or autoSyncTransforms is true.

UnityPlayer inventory contains SyncTransforms and autoSyncTransforms strings. A bounded array inspection observes 507 Physics2D names followed by a zero sentinel and an adjacent 507-entry .text-address array with its own sentinel. Matching-index callback addresses remain **candidates**: no registration pairing loop was located by the bounded direct-LEA .text search. Additional .tvm0/.Ovo sections are observed; their behavior is unknown. `engine_binding_candidates.json` retains raw candidate bodies and `parallel_array_pairing_proven=false`; those bodies are not used to implement CheckConsistency, sync or overlap. Absence of a SyncTransforms string in the bounded GameAssembly inventory does not prove absence of implicit engine synchronization.

## Supported API and verification

`load_prefab_physics_catalog` returns immutable declarations and verifies original input/AB pins. Runtime exact class, bounds getter values, TransformVector output, query pose and cached marker state remain explicit. `plan_box_overlap` and `plan_circle_overlap` generate arguments under the stated arithmetic scope. `ExternalOverlapResult` requires a full ordered returned prefix, post-consistency filter and query fingerprint/epoch. `bind_external_query_results` preserves Unity collider and Entity duplicates before the existing native logical collector; `.as_targeting_snapshot()` composes with v7 targeting. It neither creates hits nor reorders them.

The scalar scope is binary32 nearest-even with finite normal-or-zero inputs/intermediates. Subnormal contexts fail closed because live MXCSR/FTZ/DAZ was not recovered. This scope is recorded on every query plan; a live floating-point environment comparison has not occurred.

21 behavior tests and four separate C# scalar-reference tests pass. Reference inputs cover 300 two-bounds/area conversions, 200 transformed-radius magnitudes, 30 initial filter payloads and three simulation modes. The reference executes no Unity/game code and supplies its own boundary fixtures; it is not an engine/client oracle. Float32 bit checks cover supported cases, while overflow/subnormal cases verify rejection. Marker/class identity is checked against raw metadata separately, because two translations can share a mistaken type assumption.

Reviewed source/test/reference/native/resource pins are in `D:\Repo\arknights-sim\evidence\physics_context\native_evidence.json`; the verifier never refreshes them. Remaining unclosed: instantiated world hierarchy and transforms, actual collider bounds updates and body motion, final CheckConsistency behavior, engine query geometry/touch/order/truncation, registration-to-callback resolution, implicit transform sync/Simulate behavior, live physics settings/MXCSR, component/cache mutation and collider-to-Entity attachment lifetime. This is a composable query-context component, not an autonomous physical battle simulator.

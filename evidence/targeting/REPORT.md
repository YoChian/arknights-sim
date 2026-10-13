# Conditional altar targeting component

`arknights_probe/targeting.py` reconstructs bounded range declarations and the ordinary native admission/collector branch of the real `sktok_ore` selector. It requires ordered **external Physics2D-to-Entity overlap snapshots**, owner/provider/status context, and an **external ALL postfilter snapshot**. It does not generate physical overlaps or native ALL order. `battle_ready=false`, `runtime_battle_validated=false`.

The source binary is GameAssembly SHA256 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`; metadata SHA256 `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`. Reviewed file hashes are in `native_evidence.json`. The read-only verifier fails on a changed file and never repins it. `native_v6/targeting/recovered_functions.json` indexes exact selected native entries and imported-source ranges. These are static normal-path observations; live XLua/hotfix state was not inspected.

## Actual component and continuous range declaration

The ability's serialized selector PPtr points to AdvancedSelector pathID `5133488200763406096`. Its same GameObject has AutoLoadBoxRange pathID `-8567466267385104624`. This is **not GridPositionRange**. The real prefab uses side mask BOTH=3, motion mask ALL=3, category DEFAULT=1, postFilter ALL=0, ignoreTargetFree=true, onlyIgnoreSome=false, ignoreAllyTargetFree=false, ignoreHealFree=false, ignoreHitRange=false, forceIgnoreCamouflage=false, no profession/unit/abnormal filters, no owner exclusion, no final taunt sort, and `_extendable=false`. Resources and their component hashes are retained in `prefab_selector.json` and the pinned v5 resource files.

RangeData.ConstructBoundingBoxes metadata31684/VA `0x182426880` rotates declared grids to UP0 and sorts signed row then column. GridPosition.RotateVector metadata28061/VA `0x182103a90` uses `(target-current+4)%4`; the row/column sort lambda metadata31691/VA `0x18242fbd0` compares row then column. `_TryFindBoundingBox` metadata31686/VA `0x182427070` extends right and then up using the **complete cell set**, removing visited cells only from the remaining set. Previously covered cells can therefore appear in another rectangle. The module bounds grid coordinates to ±32767 to avoid the native comparator's subtraction-overflow branch.

The real `x-1` declaration has 13 grids, direction RIGHT=1. The native construction gives these **three overlapping local collider rectangles**, in order:

| minimum (x,y) | size (x,y) | center (x,y) |
| --- | --- | --- |
| (-0.5,-2.5) | (1,5) | (0,0) |
| (-1.5,-1.5) | (3,3) | (0,0) |
| (-2.5,-0.5) | (5,1) | (0,0) |

AutoLoadBoxRange.FetchCollidersById metadata73932/VA `0x1809a4d60` reads these bounding rectangles and creates trigger BoxCollider2D components with `offset=rect.center`, `size=rect.size`. ObscuredRect center metadata31692/VA `0x18241e4d0` uses separate Single multiply/add operations. Module results preserve these binary32 stages. This does **not** determine whether an enemy's continuous body collider intersects the range. In particular, no lookup of the enemy's current grid cell or Manhattan distance substitutes for the Physics2D query.

PhysicsRange.DoFindTargets metadata74138/VA `0x1809b6a30` saves Transform.localPosition, assigns Transform.position from MapToWorld(query map position), runs Box2d collection, then restores localPosition. The Unity helper identities are corroborated by native method tables: `0x186b74fb0=get_localPosition`, `0x186b75b30=set_position`, `0x186b75890=set_localPosition`. This branch still calls Unity Physics2D when deterministic mode is enabled; deterministic mode changes collected-entity sorting, not collision generation.

Box2d overlap metadata73947/VA `0x1809a6560` uses world Collider.bounds and Unity Physics2D.OverlapAreaNonAlloc (`0x186bc4460`) for boxes, and OverlapCircleNonAlloc (`0x186bc4560`) for circles. The module accepts completed external query results, including order, destroyed range colliders and collider-to-Entity null results. It does not claim to reproduce query buffer truncation, touch tolerance, body geometry or physics synchronization.

`WorldBounds2D.contains` separately translates MapUtil.InBounds metadata78322/VA `0x180b00a90`: four **inclusive XY** inequalities, no epsilon. It requires explicit world bounds and is only a diagnostic point test. SafeBounds metadata73943/VA `0x1809a60e0` uses existing Collider.bounds if **Behaviour.isActiveAndEnabled** (`0x186b59040`) is true; otherwise it constructs Bounds from TransformPoint(offset) and AbsVector(TransformVector(size)). It adds no edge epsilon. Transform evaluation is still external.

## Collector, validation and order

Box2dPhysicsUtil.FindTargets metadata73944/VA `0x1809a5850` iterates cached range colliders and each engine result in supplied order. It excludes missing/destroyed entities, checks uid validity, then native Entity.alive, verifies masks/admission, runs validators and deduplicates **previously admitted** UInt32 UIDs. A rejected UID is not added to the dedup set. The **128th admitted entity immediately ends collection before sorting**, so a low UID arriving later does not replace an earlier high UID.

The raw virtual call uses slot40: Entity.get_alive; it is not BObject.validAndBorned. UID validity metadata65018/VA `0x180663060` is uid!=0. `BObject.instanceUid` is UInt32, not Int32. Entity.CompareTo metadata66718/VA `0x1806f1750` calls System.UInt32.CompareTo metadata241404/VA `0x185ee3720`; the raw JB/SETA instructions prove unsigned order. After dedup all admitted keys are unique, so the native collection sort's equal-key behavior cannot change this scoped UID order. Caller methodInfo slot `0x188938418` proves zero-argument List<Entity>.Sort, through exact methodSpec271522 and Entity genericInst478; shared machine addresses alone were not used as type identities.

Admission uses TargetOptions.VerifyTargetWithoutCheckingTargetSide metadata75074/VA `0x1809fa670`. It checks the native changeableMotionMode bit and category result. It **does not reapply an Entity side test** after the Physics2D layer query. The actual ignoreTargetFree=true/onlyIgnoreSome=false branch skips that immunity/source-motion branch, while same-source-side ally-target-free and HEAL-purpose heal-free exclusion remain relevant. The module requires a Boolean result whenever one can change admission. Read-only getters whose returned values cannot affect this bounded immutable branch are not modeled as callbacks.

TargetSelector.ValidateTarget metadata75097/VA `0x1809fc1c0` checks owner/target map layer, target Entity.IsInHitRange, then camouflage against the native opposite-side mask unless the ability ignores camouflage, then a registered custom validator. AdvancedSelector.ValidateTarget metadata74241/VA `0x1809c3b50` subsequently checks its exclusion set. The caller supplies these dynamic outcomes with sources. Unknown required outcomes cause `UnverifiedTargetContext`, rather than an empty target list. Raw normal-path getter evidence confirms inherited ignoreMapLayer=false; Advanced.ignoreHitRange is base false OR field+0xf6; Advanced.forceIgnoreCamouflage reads field+0xcf, both zero in the real prefab.

TargetOptions captures source motion independently from PtrObjRef validity. `_TryGetSourceMotionMode` metadata75075/VA `0x1809fa900` uses live source motion if its reference remains valid, otherwise captured motion; absent source and absent snapshot returns E_NUM=2/false. `resolve_source_motion` preserves this limited rule separately.

The input contract includes explicit initialized absolute side mask, Physics2D layer mask and opposite-side mask. BattleConsts' conversion arrays and GameLayers' runtime static values are not guessed. Query mask and cached collider count must match the caller context. Entity positions/status and all callbacks are frozen for the synchronous call; conflicting snapshots for one UID reject. The module does not calculate camouflage, HP/alive, category, map layer or source masks from enemy IDs.

## ALL postfilter boundary

Native FilterUtil.Filter metadata74633/VA `0x1809d8270` replaces requested count with candidate count for ALL=0; `_Filter_All` metadata74639/VA `0x1809da080` returns the Entity virtual **createdTime FP** weight. The instantiated weighted helper `0x1844f9140` clears a shared SortedSet, obtains weights, invokes `_SecondFilterInExtraMode`, and copies ranked entries back. Generic identity is proven by methodInfo slot `0x188904ab8` → methodSpec293295 → Filter<Entity> metadata74619; the prior-weight overload at `0x1844f9740` is independently identified through methodSpec293296. FilterUtil.cctor metadata74719/VA `0x1809e1dc0` initializes the SortedSets and default weight-gap values.

This is sufficient to disprove an unqualified "ALL preserves collector order" assumption. The exact weight-gap constant, SortedSet comparison including ties, dictionary binding for ALL and extra-mode adjustment remain unclosed. `AllPostFilterSnapshot` therefore requires an explicit input UID order matching the collector, a complete external output permutation, and a provenance source. The adapter restricts accepted contexts to permutations; it does **not prove** the game always preserves membership. Native membership changes, equal-key collapse or callbacks mutating an entity are outside this scope. No Python createdTime sort or native order claim is substituted.

## Verification

25 tests pass: 23 behavioral tests and 2 source-owned C# reference comparisons. The reference covers 148 bounded grid sets/directions and 112 collector contexts, checking exact box Single bit patterns and order, admission reasons, dedup, 128 cap and unsigned UID ordering. Its Physics2D and status values are fixtures; its ALL output is an explicitly supplied reversed permutation. The program never loads the game or Unity. It checks a cross-language reconstruction, **not a native/client oracle** and not live physics or native ALL behavior. `reference_input.json`, `TargetingReference.cs`, `reference_vectors.json`, generator and test files are pinned.

From `D:\Repo\arknights-sim`:

```powershell
python -X utf8 -m unittest tests.test_targeting tests.test_targeting_reference -q
python -X utf8 evidence\targeting\verify_evidence.py
```

## Concrete next closure dependencies

1. **Target collider geometry and mapping.** Export the actual Enemy/UBody GameObject tree and Collider2D component identity, shape, size/radius, offset, enabled/isTrigger, Unity layer, Transform parent scale/rotation/local position; identify collider→Entity cache registration/removal and instance-ID behavior. Existing rule-prefab summaries retain Enemy and animator/range PPtrs and component hashes, but do not themselves establish the Unity body collider's continuous world shape.
2. **Unity Physics2D runtime.** Establish native engine broadphase/touch/contact-offset semantics, nonalloc shared-buffer capacity/truncation, order within each range collider query, layer-mask values, query trigger settings and when Transform.position changes are synchronized before OverlapAreaNonAlloc. Native ordinary and deterministic modes both query Physics2D.
3. **ALL weighting/ranking.** Recover `_CreateFilterFuncs` ALL delegate binding, `_SecondFilterInExtraMode` metadata74621/VA `0x1809e1aa0`, the exact FP static+0x68 gap used by FilterUtil.cctor, SortedSet<CompValue>.CompareTo and rank insertion/removal/copy helpers. Establish same/near-equal createdTime ties and whether the selected comparator can merge entries. Freeze live createdTime/status during selection or recover mutation rules.
4. **Provider/status/context initialization.** Close BattleConsts same/opposite-side static arrays, GameLayers initialization; HitRangeManager/providers reached by Entity.IsInHitRange metadata66720/VA `0x1806f5d10`; live camouflage/category/alive/free/ability/custom-validator/exclusion sources; actual extension/cache reset and hotfix delegates. External inputs remain mandatory until then.

GridPositionRange functions were inspected but are not used for the real altar prefab. A grid-range simulator would answer a different component's rules. This stage closes the conditional collector component and range declarations; the complete gameplay/training environment remains incomplete.

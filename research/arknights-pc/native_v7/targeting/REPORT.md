# Altar targeting: native logical inputs and ALL queue

The new `D:\Repo\arknights-sim\arknights_probe\targeting_runtime.py` reconstructs the ordinary, no-hotfix altar logical admission and ALL queue. It derives side/layer/purpose values and status flags, aggregates supplied HitRange providers, and generates the ALL output without the v6 external order adapter. Unity Physics2D overlap results and changing runtime state remain explicit inputs. `battle_ready=false` and `runtime_battle_validated=false`.

## Source identity and corrections

GameAssembly SHA256: `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`. Metadata SHA256: `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`. The v6 module and its reviewed pins are preserved.

Exact encoded TypeInfo/MethodInfo records in `generic_identities.json` prove `PriorityQueue<WeightedTarget<Entity>>`, rather than the provisional v6 report labels `SortedSet<CompValue<Entity>>`. The queue permits equal entries. The same records correct provisional `BattleConsts` to `SideTypes`, and `GameLayers` to `Battle.Layers`. These were prose/candidate labels; v6 only accepted an external ALL adapter and did not implement the mistaken container.

`generic_dispatch.json` relates canonical `WeightedTarget<Object>` sharing to the observed Entity caller context. A CompareTo address anchor identifies the unique file-backed generic pointer array; two constructor addresses independently corroborate it. MetadataRegistration generic-function records are 16 bytes, MethodSpec records 12 bytes. Open generic definition offsets of zero are not treated as concrete instance layout.

The final raw check also corrects an initial v7 first-set-bit assumption: helper `0x186727990` shifts one by the slot and performs `CMP/SETE`, so the test is `(1 << slot) == sourceSide`. Composite sides have no matching slot: Same returns the input and Opposite returns zero. Both Python and the separate C# reference were corrected before freezing. The altar's actual source side 2 is unaffected.

## Closed ordinary branch

| Rule | Exact evidence | Result |
| --- | --- | --- |
| Same/opposite arrays | SideTypes cctor `0x180b06970`, raw final OPPOSITE store `0x180b06b6a` | Same `[1,2,4]`; opposite `[2,5,2]`; exact one-bit matching |
| Serialized side and relative side | Actual `sktok_ore` Trap/AdvancedSelector prefab | Owner side ENEMY=2, target relative BOTH=3; converted absolute mask 7 |
| Unity layer names | Layers cctor `0x1805e15a0`; exact UTF-8 usage slots in `constants.json`; serialized TagManager pathID3 | ALLY=10, ENEMY=9, NEUTRAL=28; combined mask `0x10000600` (268436992) |
| Source purpose | TargetSelector getter `0x1809fc980` | Normal branch returns 0; AbilityStandard's separately stored purpose 1 is not substituted |
| Owner/target map layer | Entity getter `0x180706fc0` | Reads Entity+0x170; caller supplies the field, rather than assuming zero |
| Created time | Enemy getter `0x180a7bf00`, Character getter `0x180a39d50` | Reads FP fields +0x4b0/+0x390; caller supplies exact raw values |
| HitRange aggregation | ctor `0x18071f130`, Register `0x18071eef0`, IsInHitRange `0x18071e930` | Empty registry passes; null providers skipped; non-null provider outcomes are ANDed with short-circuiting; registration retains existing non-null entries |
| Abnormal status | Attributes.GetAbnormalFlag `0x180649280`, CheckAbnormalImmune `0x1806488d0`, enum helper `0x1844dc660` | Signed Int16 immune/active counters, then UInt64 base-mask fallback; a positive immune count suppresses dynamic counts but does not suppress a base flag |
| High base-mask bit | GetAbnormalFlag raw `TEST/SETG` | A bit-63-only masked value is signed negative and does not produce true |
| Camouflage | Entity getter flag17 and not immune9; ordinary Ability getter `0x1805d78a0` returns false | Enemy-side camouflage rejection is computed from native status inputs |
| ALL filter delegate | exact MethodInfo slot `0x1889053a8` resolves methodDef74639 `_Filter_All` | Uses createdTime; alive is rechecked before queuing |
| ALL queue | PriorityQueue.Add `0x1851afeb0` | Linear scan; insert before first comparison <=0; equal entries retained; no sorted-set dedup |
| Weighted constructor | `0x185528950` -> `0x185528bb0` | Ordinary priorWeight=FP0 |
| Weighted comparison | canonical CompareTo `0x1855279c0`, cctor `0x185528350` | Gap raw4294967 (FP.EN3); big threshold 1000000; small weights use floor(weight/gap); large pairs compare integer floors then fractional bins; mixed/exact-threshold pairs remain unbinned |
| Equality/ties | FP MathUtil.Equals `0x1866e46f0`, floor `0x1866ff410`, abs `0x1866fed50`, v5 MathUtil cctor | Equality uses abs(unchecked difference) <42950 (FP.EN5); final Entity tie comparison is UInt32 UID |
| Extra mode | SecondFilterInExtraMode `0x1809e1aa0` | Explicit `is_sandbox=false` closes the ordinary branch; sandbox is rejected |

The inherited v6 collector consumes all cached-collider snapshots in explicit order, rejects invalid/destroyed/dead entries, applies logical admission, deduplicates admitted UInt32 UIDs, caps collection at 128, and sorts admitted UIDs when deterministic. The subsequent ALL phase can remove a member with an explicitly supplied second-phase alive value. Reusing the collection alive value is restricted to a frozen synchronous-call snapshot. Membership is not forced into a permutation of the original collector.

No new direct `Enemy.Options.unharmful` exclusion is added. The inherited BObject field +0x26 is `isDisappeared`; it must not be relabeled as the unrelated enemy option. Core alive/destroyed fields remain explicit inputs.

## API used by the parent probe

`RuntimeAltarContext` requires source side, source map layer, actual collider count, deterministic flag, sandbox flag, custom validator, exclusion set, no-hotfix flag, and source attribution. `RuntimeTargetData` requires raw FP created time, `AbnormalStatus`, `HitRangeManager`, and source attribution. `select_altar_targets_runtime(query, context, targets)` returns hits, collector UIDs, rejection decisions, ALL decisions, and provenance.

```python
context = RuntimeAltarContext(
    source_side=2, source_map_layer=0, collider_count=3,
    deterministic=True, is_sandbox=False, custom_validator=None,
    excluded_uids=frozenset(), hotfixes_absent=True,
    source="actual altar side + explicit normal scene fixture",
)
data = RuntimeTargetData(
    created_time=FP.from_raw(0),
    attributes=AbnormalStatus.zeroed_prepared_fixture("explicit zero counts/base fixture"),
    hit_range=HitRangeManager((), "explicit empty registry fixture"),
    source="explicit native field snapshot",
)
# query contains three explicitly supplied Physics2D collider-result snapshots.
# Its mask must equal context.query_layer_mask; no overlap geometry is generated.
result = select_altar_targets_runtime(query, context, {2: data})
```

An empty provider registry and zero status counters are named prepared fixtures. Their API availability does not prove that live laxe/altar registrations are empty. A missing requested counter or provider outcome fails closed; values are not silently defaulted to zero/true. The owner map layer and createdTime raw0 above are fixtures, rather than prefab-derived constants.

## Verification and remaining boundary

21 behavior tests and four independent C# comparison tests pass. The separate compiled C# translation covers 1500 comparator pairs, 120 queue cases (3786 output identities), 400 signed-counter/base-mask cases, and all 64 source/relative-side combinations. Cases include UInt32 UID boundaries, negative FP weights, overflow-sensitive Int64 extremes, gap boundaries, the exact big threshold, equality epsilon, ties, member removal, and collection cap. The test-data generator's Python RNG is solely a fixture generator and is unrelated to the game's RNG. The C# FP division routine reuses the separately verified FP translation; this comparison is not an independent verification of that division algorithm and is not a native/client oracle.

The reviewed manifest is `D:\Repo\arknights-sim\evidence\targeting_runtime\native_evidence.json`. It pins new source/reference artifacts, the stable batches used, raw helper/metadata identity records, serialized inputs, and reused v6 evidence. The verifier checks hashes without updating them. File drift requires review before a new manifest is written.

Still external or rejected: Unity Collider2D/UBody geometry and complete world-transform hierarchy, overlap/touch behavior and query order, live NameToLayer/serialized-static overrides, active hotfix delegates, moving runtime mapLayer/createdTime values, dynamic buff-counter updates, actual HitRange provider algorithms/registration lifetime, mutable or reentrant callbacks, and sandbox secondary weights. This stage closes the logical ordinary targeting path under explicit frozen context; it does not establish live battle equivalence or a trainable full-game simulator.

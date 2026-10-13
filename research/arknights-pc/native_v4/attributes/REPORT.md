# Enemy data and initial attribute recovery

Target: immutable local `GameAssembly.dll`, SHA256 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`.
Metadata SHA256 `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`. Analysis was static/read-only;
no game, injection, account service, or hotfix interpreter was run.

## Evidence coverage

Three isolated Ghidra imports restored 48 unique entry addresses
(43 for this attribute closure and
5 movement entries handed to the movement agent).
All 80 exact PE/recursive UNW_FLAG_CHAININFO or
separately bounded leaf ranges match original bytes in imported memory.
Decompiler completion is not used as a coverage certificate. Constructor PIC
warnings after write-barrier calls were checked against full raw disassembly.
Metadata/native names remain candidate associations, including shared aliases.

`raw_disassembly_round3.json` additionally captures the actual EnemyDB.TryGet
reference caller (0x18200bb60), its id/level overload (0x18200bd90), and the
three-piece Entity.get_alive method. `numeric_helpers.json` records CRT round
helper dependencies/literals and the shared DataPair numeric gate. The native
array sort and earlier timeline evidence remain unchanged.

## Recovered behavior

- Exact nonnegative DB level is required. Inheritance follows stored list order
  and stops at the first level above the requested one. Negative level applies
  only the first entry. No sorting, nearest-level fallback, or zero-placeholder
  interpretation is introduced.
- Actual `EnemyDB.TryGet` resolves the database first, then applies non-null
  `overwrittenData` with `ApplyDefinedData`. All-undefined wrappers can still
  carry a Blackboard layer. Source `prefabKey` maps to runtime `key` through the
  actual v29 custom attribute `AssignName=key`.
- Runtime attributes decode to 34 numeric and 11 Boolean values. Defaults are
  taken from AttributesData construction and Obscured default-decrypt paths.
  In particular undefined MR means constructor 0, while undefined base attack
  time means constructor 1. Defined zero or false overwrites the prior value.
- Assignment and Reset both pass numeric ints through Single. Large ints can
  lose precision. Writeback uses double ties-to-even Round, signed int32 SSE
  conversion, then Reset reads Single, converts FP32.32 and clamps to actual
  metadata ranges. `attribute_meta.json` has exact per-field constructor bytes.
- Blackboard layers replace all equal keys and append each new pair. Nonempty
  valueStr selects String and clears numeric value; null/empty selects numeric.
  Skills replace by prefabKey and inherit existing Blackboard entries only
  when the incoming skill has a nonempty Blackboard. Non-null spData replaces.
- Entity.Init starts HP from virtual get_maxHp(slot81). get_alive requires a
  running registered StateMachine plus HP greater than MathUtil's EN5 threshold,
  raw 42950, in the ordinary path. HP>0 alone is insufficient.

## Prototype API and verification

`arknights_probe.enemy_data.resolve_enemy(database, reference)` returns
`ResolvedEnemyData`: `attribute_values`/`numeric` are decoded primitives;
`database_attribute_values` preserves the pre-modifier snapshot;
`unclamped_attributes` and `attributes` are FP values before/after Reset clamp.
Top fields, talent_blackboard, skills, sp_data and layer provenance are retained.
`read_attribute`, `write_attribute`, `clamp_attribute`, `refresh_attributes`
are available for the separately recovered rune preprocessing order.

Ten EnemyData unit tests pass, including all 10 real references/20 DB rows,
undefined defaults, nonzero inheritance, explicit zero/false overwrite,
Blackboard key order, skill replacement, Single precision and int32 overflow.
The independent source-owned C# numeric reference passes 629 cases (340 actual
numeric values plus rounding/FP/extreme cases). .NET serialization's shortened
Single decimals are compared using exact IEEE bits. This reference is a static
implementation comparison, **not a live game oracle**.

useDb=false remains an explicit gate. Lua overrides, Rogue manager/global
modifiers, runtime effect providers and custom override ranges are excluded by
the upper-layer reconstruction context; they were not proved absent in a real
run. `attributes` is the Reset raw/cached view and is never advertised as the
final dynamic `_CalculateAttributeValue` result. Finite numeric/SSE assumptions
are inherited from the fixedpoint reconstruction.

Evidence copies and file/module/test SHA256 pins are under
`D:/Repo/arknights-sim/evidence/enemy_data/manifest.json`.

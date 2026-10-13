# Static runtime movement component, 2026-10-13

`arknights_probe.runtime_movement` now performs the recovered default WALK
position update over an explicit cached-tile context. It reuses the v4 native
weighted FIFO path builder; it does not substitute BFS or integrate positions
in FP. Positions, geometry and controller arithmetic are binary32. WAIT and
the caller's clock are signed Q32.32 FP.

The component can request an exit after moving through a small fixed fixture
without an external death/terminal event. It does not own creation, the FSM,
HP, mode life loss, recycling or scheduler completion. Its exit request must
be consumed once by the lifecycle owner. `battle_ready` and
`runtime_battle_validated` remain false. This is not an assertion that the full
local map can run with no player actions.

## Recovered inputs and APIs

`initialize_cached_tile` consumes **processed** TileData, its actual Tile/HoleTile
class and an explicit Map-built WALK goto mask. `Tile.Init` (70688,
`0x1808bf100`) sets origin options, calls its virtual preprocessing hook, then
copies cached options. Base preprocessing (70740, `0x1808c1440`) is a default
no-op. `SetData` (70729, `0x1808c2f00`) alone does not initialize the cache.

TileData `advancedBuildableMask` is offset `+0x28`, distinct from playerSideMask
at `+0x24`. The constructor (31576, `0x18242f990`) sets its default to 1. The
map JSON omits this field; treating it as zero or using the adjacent player
mask would be incorrect. Scene prefab `_data` defaults likewise are not the
processed map data.

The cache supports the actual base Tile and HoleTile overrides: ordinary cost
1, obstacle-cost override 1000, HoleTile cost 1,000,000. HoleTile's cost is not
controlled by the ordinary override bool. `build_cached_walk_grid` preserves
these effective costs for weighted routing and obstacle avoidance. Rows are
logical bottom-origin rows; display/storage row reversal is the previously
verified MapData accessor behavior.

`rewrite_cached_tile` transcribes Rewrite/TryUpdate/Refresh option branches
(70739 `0x1808c2cd0`, 70734 `0x1808c3820`, 70737 `0x1808c1ba0`). It requires
explicit keep/build/pass, batching and ignore-route-check flags. If a relevant
passability/cost change needs the global all-routes-reachable decision, an
unknown decision rejects execution. A rejected rewrite restores **origin**
options, not the previous cached options. The caller owns passable-map update,
route recomputation, route reachability, device-mode timing and occupancy.

The real altar's logical `(5,6)` TokenMode requests passableMask 2, build mask
0, advanced mask 0, ordinary move cost, and `forceSetHeightType=false`.
Therefore its proposed cache blocks WALK and preserves the tile's existing
height type. The proposed state cannot be adopted merely from the resource
declaration: global route validation can reject it. The real Token flags are
`keepPass=false`, `keepBuild=false`, `ignoreBlockAnyRoutes=false`. Token's
**OnSwitchMode** (77463, `0x180ab5b40`) owns this rewrite after base mode
processing; Trap.OnInit (77519, `0x180ab8f60`) does not directly rewrite it.
The caller must establish the actual initialization/mode callback order.
TokenMode also rewrites visual height to binary32(0.4); this component does
not reconstruct visual/animation height, foot-offset capture or device damage.

`MovementContext` has nine mandatory fields: source, deterministic,
new_steering, foot_offset, initial_steering, max_force, half_body_width,
conveyor_present, always_check_current_point. No bool is supplied implicitly.
The real ten enemy controller prefabs have steering 8, maximum force 10 and
binary32(0.2) half width; these differ from native constructor 2.5/4/0.2.
BattleOptions.STEERING_ENABLED is static `+0xbd`, not DynamicConfig. Its native
constructor (62950, `0x1805da9c0`) initializes false; startup setters and hotfix
dispatch remain outside this component. False selects the recovered 100/100
factor/limit branch; true selects the explicit controller parameters.

The real Enemy `_alwaysCheckCurrentPoint` field is bool `+0x33d`. Only
`enemy_2137_shsdgo` is true among the ten references. Other nine are false.
These are resource inputs, not a single assumed flag for every enemy.

## Tick, cursor and float stages

`NativeRouteMover` takes an already resolved local-map spawn position and
cursor offset. Native creation consumes RNG even for a zero spawn-random
range; this component never chooses or seeds that stream.

`move_by_cursor` uses the native default prediction-before-controller order
(`Enemy._MoveByCursor`, 76491 `0x180a78fc0`). A reached prediction snaps to its
target, preserves existing controller velocity and applies deterministic
assignment when selected. Otherwise DirectionCursor supplies a direction,
MoveController updates acceleration/avoidance/velocity, the move is reflected
if it enters an unpassable tile, then the position is assigned. Unsupported
outside-map go-back and conveyor contexts are rejected.

`NativeMoveController` preserves individual binary32 multiply/add/divide
stages and the native order of vector dot operations. It uses the recovered
three-call PeriodicTicker, not elapsed seconds. Its blocked or speed-at/below
1e-5 early branch retains velocity and ticker state. Avoidance uses eight
neighbors in the original order, the locator grid for lookup and separately
supplied cached foot offset for edge calculations. An unpassable current
tile returns the raw nearest-passable neighbor delta; ties retain the first
neighbor. The retained native call `0x1807b31e0` is **unchecked int Abs**, not
Sign. This corrects the early tentative helper name. The C# reference tests
cover the actual abs behavior.

`NativeDirectionCursor` supports the v4 compiler's default MOVE and
WAIT_FOR_SECONDS scope. WAIT ticks use FP; OnTick advances at most one
checkpoint, while GetNextDirection can skip multiple already reached points.
Prediction scans future position checkpoints past WAIT without advancing the
index. The BasicCursor constructor (70158, `0x180876c80`) derives the additional
`visitEveryNodeStably` flag from **zero checkpoint count**, independently of
the three false JSON visitation flags. That path caches nextGrid and uses its
native 0.25 proximity branch. It is tested on an asymmetric obstacle map.
AlwaysCheckCurrentPoint affects whether an invalid/unreachable current MOVE
path node skips the checkpoint; it is a required input.

`tick(FP, ...)` applies physical movement only when the caller reports that the
pre-tick FSM dispatch took MoveState's recovered default branch. This is not
derived from `alive`. Unit/FSM processing precedes Enemy cursor ticking;
Enemy.OnTick (76531, `0x180a72340`) ticks the cursor when its post-Unit alive
gate passes, including during Born. Born -> Move does not execute MoveState
within the same FSM tick. EnemyStateMachine.OnTick (76640, `0x180a908b0`) also
reassigns the Transform **local** position in deterministic mode after state
dispatch, even during a Born/nonmoving tick. The external lifecycle owner
provides status, targeting, FSM and mode-exit gate outcomes.

Deterministic assignment is Single -> Double, multiply by 10^4, round to even,
divide by 10^4, then Double -> Single. It is not Python `round(x,4)`.
`DeterministicUtil._TruncateInternal` is `0x180af56e0`; Math.Round is
`0x185ebaf20`; the finite CRT rounding branch `0x18000cec0` and disjoint
split/floor/ceil components are retained with exact source-byte hashes.
Supported finite coordinates have abs < 1e11, below the native 1e16 round
limit after scaling. Nonfinite/overflow/exception paths are excluded.

VisualObject.SetPosition(Vector2) is 77880 `0x180ad3dc0`.
`0x180ad3e60` (77879) is the **GridPosition** overload, correcting the earlier
candidate label. Enemy inherits slot 13 `_AssignLocalPosInternal` through
BObject (65044 `0x180662d90`) to VisualObject (77885 `0x180ad3fd0`). The
`0x186b74fb0` Unity helper is Transform.get_localPosition (283263), not world
get_position; the setter is `0x186b75890` (283264). Local-map x/y and grid
row/column conversion therefore must not be replaced by world coordinates.

## Validation and provenance

The 21 component tests and 3 cross-language reference tests pass. The latter
compare exact binary32 bit patterns for 320 deterministic-rounding inputs,
80 avoidance cases and 80 controllers over 30 inputs each: **2,400 controller
frames**, including velocity, last avoidance force, timer consumption and
still flag. The 21 tests also cover FP WAIT ordering, Born no-move behavior,
prediction velocity retention, geometric versus permitted exit, consuming an
exit once, subclass costs, origin rollback, unknown reachability refusal,
asymmetric zero-checkpoint paths and prefab always-check flag differences.

`RuntimeMovementReference.cs` is an independent local C# translation. It was
compiled with Framework64 v4.0.30319 `csc.exe`, x64, optimize enabled. It
references only framework libraries and does not load GameAssembly, execute
game code, use a game process or call a network service. Explicit float stages
are retained. The input generator uses Python Random solely to construct
finite test fixtures, not as battle RNG.

This reference checks translation consistency. It does **not** independently
validate the native recovery, real cached scene construction, route compilation,
spawn RNG consumption/order, FSM/status/targeting inputs, device callback
timing, Unity transforms/animation, lifecycle or an actual client trace.
Previous v4 path/geometry reference evidence remains separately pinned.

`native_evidence.json` pins the implementation, tests, reference inputs/source,
v4 dependency evidence, v5 resource/metadata records and exact consolidated
native results. The 36 movement-specific requests are 24/9/3 across v5
rounds 1/2/3; all completed and every imported range matched the original PE.
Other entries in these shared reports belong to the parent/devices/lifecycle
investigation; their report totals are not counts of this component's requests.
`verify_evidence.py` only checks reviewed pins and never updates them.

The pinned `deterministic_consts.json` has a historical `evidence_link` path
annotation saying `movement/raw_helpers.json` and “DeterministicUtil .cctor”.
The actual raw evidence is `movement/raw_raw_helpers.json`, **System.Math
.cctor** `0x185ebb460`; FieldInfo slot `0x1888a2778` points to the validated
private Double[16] blob (10^0 through 10^15). The JSON bytes remain unchanged
to preserve its pin. Ticker.Next's exact leaf is `0x181e04370..0x181e04381`,
not the earlier capture that extended through alignment padding to `...390`.

## Remaining boundary

No complete live hotfix/Unity context is established. Caller-supplied cached
tiles must include accepted device rewrites and Map constraints; mutable
occupancy and route rebuilding are not owned here. Foot offsets must come
from actual animation/start context or be declared fixtures. Non-default
FSM/target branches, fear/attract, abnormal status transitions, physical force
modifiers, body separation, conveyors, height/hanging behavior, outside-map
go-back, spatial index and device effects remain outside the movement scope.
This module cannot promote an incomplete full-map scene into a verified
training battle.

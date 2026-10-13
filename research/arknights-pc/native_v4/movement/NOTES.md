# Movement reconstruction work log

Scope: shipped PC `GameAssembly.dll` static reconstruction. No client execution or runtime oracle. This stage owns only movement components, tests and evidence; scheduling and mode integration remain separate.

## Initial round 2 findings (followups below supersede pending items)

All 47 selected exact entry bodies decompiled. Each imported range is checked against its original source bytes; ranges use complete recursive PE `UNW_FLAG_CHAININFO` groups, or explicitly bounded leaves. Interrupted round 1 artifacts are retained and are not evidence of a completed analysis.

- Enemy `_MoveByCursor` uses Unity `Vector2` / `Single` positions and a `Single` delta. Ordinary position movement must **not** be rewritten as FP vector arithmetic. FP remains relevant to attributes and the checkpoint timer.
- The cursor prediction call at virtual offset `0x1e0` is slot 10, **DirectionCursor.PredictReached**, not `GetNextDirection`. Its implementation is requested for the next parent batch. The negative prediction path invokes `GetNextDirection` and `MoveController.CalculateMoveDelta`.
- `MoveController.CalculateMoveDelta` includes velocity state, steering and obstacle force, magnitude clamping and a `canMove` check. A straight `position += speed * direction * dt` substitute is not yet justified.
- `WaitForSecondsCheckpoint.OnBegin` (`0x1808a8a20`) converts `CheckpointData.time` from binary32 to FP. `OnTick` (`0x1808a8a90`) computes `max(FP(0), remaining-dt)`. `get_isReached` (`0x1808a89c0`) compares signed raw `remaining <= 0`. WAIT is a countdown, not the scheduler's nearest-even frame wait. At asset-initial `dt_raw=143165440`, a 60-second countdown takes 1801 decrements; scheduler float waiting returns 1800 frames. Cursor invocation ordering is a separate question.
- `DirectionCursor.OnTick` (`0x180895d70`) ticks the current checkpoint with FP delta, then when its `checkReached` argument is true, checks locator position and advances once. `BasicCursor._MoveNext` ends the old checkpoint and begins the next; movement selection may advance checkpoints in its own loop.
- `DirectionCursor.CheckReached` (`0x180894d60`) checks the end grid and an exact binary32 squared-distance constant `0.0025000002`; it is not a configurable guessed epsilon. Mode permission is still required by `Enemy._CheckEnemyCanExit`, whose default body invokes a game-mode interface.
- `MoveCheckpoint.CheckReached(Vector2)` enforces `max(binary32(0.05), reachDistance)` through `MathUtil.CheckDistance`. Nonvalid/unreachable next-map positions can be skipped unless `alwaysCheckCurrentPoint` is set. The distance helper is requested before implementation.
- All 28 real WALK routes set `allowDiagonalMove=true` and all three visit-center flags false. MOVE and WAIT_FOR_SECONDS are the only checkpoint kinds. Nonzero fixed spawn offsets exist, despite every random range being zero. `Route.GetSpawnOffset` still calls a map RNG helper with the zero range; position equivalence does not prove no RNG consumption.
- `SPFA._GenerateNextMapImpl` (`0x1808a5860`) is reverse FIFO weighted relaxation, using a four-neighbor order and strict less-than distance updates. WALK cost comes from **Tile.get_moveCost**, virtual slot 16 (`0x1808adc40`), not a guessed unit-weight BFS. FLY has separate cost 1. Exact direction order, masks and node helpers are requested.
- `SPFA._PostprocessAndMakeNextMapSmoothly` (`0x1808a5fe0`) modifies next pointers in row-ascending / column-ascending order, repeatedly skipping nodes while native raycast checks permit. It reads already modified successors. Bresenham checks obstacle-like status and directional goto masks, including adjacent corner cells, so ordinary line-of-sight is insufficient.
- `Map.MapToWorldPosition` maps `(localX,localY,0)` through `anchorTransform.TransformPoint`; the inverse uses `InverseTransformPoint`. Local map coordinates, logical grid coordinates and scene world coordinates must remain distinct. The current offline component does not reconstruct Unity scene transforms.

## Followups and current runnable components

Parent creation round 2 completed 50 entries, and attributes round 3 completed 24 entries including five requested controller bodies. Source-owned raw helper followups independently retain the complete PE ranges and source SHA. `evidence/movement/native_evidence.json` pins the reports, raw helper sources, resource enum/field reports and C# reference files.

Corrections to the early candidate identification are retained explicitly: `VisualObject.SetPosition` at `0x180ad3e60` takes **GridPosition**, while the Enemy's actual Vector2 call is `0x180ad3dc0` / metadata method 77880. Vector3/local assignment occurs via slot 13 `_AssignLocalPosInternal`; Enemy inherits BObject's `0x180662d90` override. `CalculateTotalForce` is nonvirtual; controller virtual slots 7 and 8 are `_CalculateSteeringForce` and `CalculateIsHanging`. Names inferred from first shared aliases or nearby metadata were not used as implementation evidence.

The compiled components now include:

- `WaitCheckpoint`: binary32 to FP countdown, clamps at zero. It is not a scheduler rounded wait or a complete cursor.
- `LocalVector2`: binary32 storage/arithmetic, native squared-magnitude/sqrt/normalization, clamp magnitude, `MathUtil.CheckDistance`, component-based `IsZero` and safe normalization.
- `grid_to_local` / `local_to_grid`: exact `(column,row)` local axes with no half-cell shift, nearest-even grid attribution via the already recovered `0x18059e290` helper.
- `WalkRouteSpec`: strict declaration profile for all 28 WALK routes; nondefault visit flags, nonzero random ranges, randomized reach offsets, unknown fields and other checkpoint kinds fail closed.
- `NativeTileSnapshot` / `NativeWalkPathGrid`: native weighted FIFO, exact four-neighbor order and reverse direction indices, Bresenham corner/goto checks, row-major smoothing and next-turn calculation, all over explicit cached tile state.
- `compile_walk_route`: backward default MOVE map assembly, WAIT `None` map slots, following-map next-turn and distance-to-final contributions. Unreachable targets are rejected rather than substituting cursor skip behavior.

The native cached obstacle cost flag is `Tile.Options.overrideObstacleLikeMoveCost`, yielding 1000 versus 1. It is a separate field from `get_isObstacleLike`, which the smoothing raycast checks. Four-neighbor order is UP/RIGHT/DOWN/LEFT and the source-owned `SharedConsts.REVERSE_FOUR_WAYS` InitializeArray blob is exactly `[2,3,0,1]`; the metadata field name is its matching SHA256.

An independent C# x64 translation confirms 60 geometry cases / 480 output assertions, 29 graph fixtures / 1080 exact node snapshots and 348 raycasts. This is a translation check, **not a live native/client oracle**. A clearly labeled resource-declaration-only frozen tile fixture compiles all 28 real routes into conditional path outputs. Its goto masks, costs and obstacle flags are explicit fixture values; prefab/device rewrites and dynamic boxes are excluded. Native runtime Tile.Init equivalence is not claimed. Twenty movement/reference unit tests pass.

Raw spawn RNG followup confirms the default `BattleRandomWrapper.RandomVector2` path tailcalls `0x181a96a20`, where x then y each invoke RNG virtual NextDouble before binary32 multiply/add, even for zero ranges. Runtime dispatch/hotfix state and total game consumption order remain unknown; the route scope still does not attest live spawn RNG consumption.

## Required context before a complete mover

`PredictReached` geometry is recovered, but the complete cursor/controller tick integration is not implemented. `CalculateIsHanging` uses a PeriodicTicker and live offset/foot/body positions to obtain an obstacle correction; steering also depends on DynamicConfig and prefab coefficients. `BObject._AssignLocalPosInternal` invokes base local assignment and spatial-index updates. Deterministic mode routes positions through four-digit Double rounding, whose complete runtime mode and base assignment path still need closure. Native tile prefab/options initialization, altar rewrite ordering, boxes/dynamic masks, buffs/status, game-mode exit permission and recycle completion remain required context. Unsupported checkpoint kinds, dynamic obstacles, forced movement and unproved contexts must fail closed. No gameplay path may fall back silently to the topology BFS probe. Autonomous leak or complete battle training readiness remains false.

# Movement stage v5, 2026-10-13

Current component: `D:\Repo\arknights-sim\arknights_probe\runtime_movement.py`.
Current evidence and independent reference report:
`D:\Repo\arknights-sim\evidence\runtime_movement\REPORT.md`.
The v4 `movement.py`/evidence remain unchanged as historical float/path/WAIT
components; v5 closes a conditional default WALK physical tick over explicit
cached tile state, and does not claim a complete battle environment.

Java/Ghidra ran only in the parent-owned combined batches. Movement selected
24 entries in core round1, 9 in round2 and 3 in round3. Each selected metadata
index completed and all imported PE ranges match the source. Renamed `.c`
views under recovered_round* are derivatives; provenance is pinned to the
parent's actual `core/results_round*.json` reports, including CHAININFO ranges.
Short helper recovery uses local read-only Capstone/PE byte evidence without
executing the game.

Completed APIs include processed Tile/HoleTile cache initialization,
conditional rewrite/rollback, effective-cost snapshots, MOVE/FP WAIT cursor,
zero-checkpoint stable cursor, controller float stages/avoidance/ticker,
predict-before-controller position update/reflection, deterministic assignment
and explicit FSM/cursor/exit relative tick order. All nine MovementContext
fields are mandatory; controller prefab settings and per-enemy always-check
flags are inputs, not inferred universal defaults. The lifecycle owner consumes
an exit request and owns mode life/recycle/scheduler completion.

Corrections retained for audit:

* `0x1807b31e0` is unchecked integer **Abs**, not Sign. The tentative name in
  raw input remains historical; MOV/NEG/CMOVS establishes the result.
* BattleOptions static slot `0x1889333a0`, field `+0xbd`, is STEERING_ENABLED,
  not DynamicConfig. The cctor initializes false; live setters/hotfix remain
  unknown. Native ctor 2.5/4 differs from real controller prefab 8/10.
* TileData `+0x28` is advancedBuildableMask (native default 1), not player mask
  (`+0x24`) and not omitted JSON zero. Tile.Init processed data is required;
  raw prefab `_data` cannot be treated as the cached map.
* Token, not Trap's own fields, owns rewrite configuration. Token.OnSwitchMode
  `0x180ab5b40` performs the proposed altar rewrite; Trap.OnInit body does not.
  Native route-reachability rejection restores origin options. Proposed altar
  passableMask 2 cannot bypass that gate.
* VisualObject.SetPosition `0x180ad3e60` is GridPosition (77879); actual Vector2
  is `0x180ad3dc0` (77880). Enemy slot13 dispatches BObject `0x180662d90` to
  VisualObject `0x180ad3fd0`. Unity helper `0x186b74fb0` is **local**Position,
  not world Position, per exact method-map identity.
* BasicCursor ctor `0x180876c80` additionally derives visitEveryNodeStably from
  zero CP count. JSON's three false visitation flags do not disable this.
* Born-to-Move does not dispatch another state's tick in the same frame.
  Born can still tick the cursor after Unit, and deterministic EnemyFSM tail
  rounds its local position even when it did not move.
* deterministic_consts.json's old evidence_link annotation is not changed:
  the actual file is movement/raw_raw_helpers.json and owner is System.Math
  cctor `0x185ebb460`. Slot is `0x1888a2778`, not the earlier +8 typo.
  The exact Ticker.Next leaf ends `0x181e04381`, excluding padding to `...390`.

Validation: 21 behavioral component tests + 3 independent C# arithmetic
reference tests, 320 rounding cases, 80 avoidance cases, 2,400 controller
frames with exact Single bits/counter/still checks. The independent C# program
does not load or execute the game and is not a client oracle. Full cached-map,
spawn RNG, status/targeting, animation/foot, dynamic route updates/device effects
and lifecycle context are not validated by that reference.

Remaining: integration must provide accepted native tile/device options,
goto masks, actual foot-offset context, pre-tick FSM/default-branch decision,
native status gates and mode permission. Conveyors, outside-map go-back and
other unsupported contexts fail closed. Full scene/device/targeting/status
readiness stays false. No BFS substitute, FP position approximation, fabricated
death or automatic completion is introduced.

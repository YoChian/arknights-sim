# Physics v8 handoff

Current source/evidence/API: [REPORT.md](REPORT.md). New module: `D:\Repo\arknights-sim\arknights_probe\physics_context.py`. All v5-v7 pins remain unchanged.

Closed: five real built-in collider/body/local Transform subtrees, literal enums/asset initial settings, exact box/circle/generic marker identities, scalar query arguments, ordinary BC tick subsequence and strict external receipt binding. Marker correction is essential: CircleColliderOverlapFixed existence controls Circle center; Rigidbody does not. Runtime-class and marker inputs are explicit and unsupported classes/unknown/nonfinite/subnormal contexts fail closed.

Unclosed: Unity world bounds/transform update, dynamic body state, final engine CheckConsistency, Physics2D hit generation/order and synchronization. The 507 adjacent engine arrays are candidates, with pairing explicitly unproven. Do not use their names as verified callback identity or claim an AABB/third-party Box2D experiment reproduces Unity.

Next evidence should target registration pairing and the actual physics/pose/sync closure or an explicitly authorized retained client query snapshot. Any future engine execution is a new scope decision; none occurred in this stage.

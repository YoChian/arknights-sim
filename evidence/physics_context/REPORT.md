# Independent scalar query reference

`PhysicsContextReference.cs` is a separately expressed C# translation of Bounds min/max, area-to-box arithmetic, transformed-vector magnitude, initial ContactFilter2D bytes and the facade simulation-mode branch. It loads no Unity or game assembly and generates no overlap/pose/world-bounds/filter-consistency result.

The source-owned fixtures cover 300 box cases, 200 radius cases, 30 initial filter payloads and three mode cases. Four reference tests and 21 behavior tests pass. Inputs are exact Single bit patterns; supported scalar outputs are checked bit-for-bit. Nonfinite and subnormal inputs/intermediates are outside the component's current scope and test its strict rejection. The separate C# process's floating-point environment does not prove the client's MXCSR/FTZ/DAZ setting.

The generator's `random.Random(810718)` solely selects boundary fixtures and is unrelated to game RNG. Input vectors supplied to the magnitude routine represent an external TransformVector result; the reference does not independently derive those vectors from a prefab or engine transform. Initial filter bytes precede an unresolved CheckConsistency call and are not assumed to be the final engine filter.

The native lookup cache was initially mistaken for Rigidbody presence; raw MethodSpec decoding proved CircleColliderOverlapFixed. That correction is separately documented in the static report because cross-language numerical agreement cannot validate an untested class identity assumption.

Run from `D:\Repo\arknights-sim`:

```powershell
python -X utf8 -m unittest tests.test_physics_context tests.test_physics_context_reference -q
python -X utf8 evidence\physics_context\verify_evidence.py
```

`native_evidence.json` contains fixed reviewed hashes. The verifier does not replace changed pins. Detailed scope is `D:\Repo\.rea-tools\arknights-pc\native_v8\physics_context\REPORT.md`.

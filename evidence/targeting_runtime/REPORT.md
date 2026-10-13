# Independent targeting rule comparison

`TargetingRuntimeReference.cs` is a separate C# translation of recovered ordinary native rules. It runs without loading Unity or any game assembly. `reference_vectors.json` is its output on the reproducible, explicit `reference_input.json` fixtures. This is a cross-language implementation check, not a native or live-client oracle.

Coverage: 1500 weighted-comparator pairs; 120 linear PriorityQueue cases with 3786 output identities; 400 signed Int16 active/immune counts and UInt64 base masks; all 64 source/relative-side combinations with actual serialized layer indices. Four reference tests and 21 behavior tests pass. The C# comparison and the Python implementation were both corrected after raw evidence proved exact one-bit side equality. Shared assumptions can therefore survive a cross-language comparison; the source-bound native check remains essential.

The C# FP division and LeadingZeroes routines reuse the already translated `evidence/fp/FPReference.cs` algorithm (source SHA256 `ec50d0338883c6a4eb690d6da1fa7bedcc2b5cc58eaa5c10a12058014f126ec6`). This reference does not independently validate FP division. Its comparator, queue, side conversion, and flag aggregation are separately expressed in C#. The fixture generator's `random.Random(700718)` only selects test inputs and has no connection to the game's RNG.

The queue fixtures include supplied alive states for ALL membership rechecks. Their alive events are not independently simulated. Physics2D overlaps, provider implementations, counter mutation, source map layer, and live createdTime values are not verified by these vectors.

Run from `D:\Repo\arknights-sim`:

```powershell
python -X utf8 -m unittest tests.test_targeting_runtime tests.test_targeting_runtime_reference -q
python -X utf8 evidence\targeting_runtime\verify_evidence.py
```

The reviewed hashes are fixed in `native_evidence.json`. The read-only verifier never regenerates them. The static finding report is `D:\Repo\.rea-tools\arknights-pc\native_v7\targeting\REPORT.md`.

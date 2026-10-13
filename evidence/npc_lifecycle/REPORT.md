# Independent lifecycle reference

NpcLifecycleReference.cs loads no game or Unity assembly. Its separately expressed default-branch accounting and stage/frame/UID records compare against npc_lifecycle.py on declared fixtures. This is a cross-language transcription check, not a client oracle or independent implementation of all nested IEnumerator behavior. The existing shared runner is checked by the previous independent coroutine reference; this new reference derives the bounded Single frame count.

Tests passed:20 behavior tests and2 reference tests. Reference coverage:640 option/status/Int32 counter cases with3200 outputs,96 lifecycle cases with2064 exact stage-frame-UID records. Cases include epsilon-adjacent delays, ordinary versus summon accounting, negative/overflowed overrides, synchronous reason7 versus delayed death2, owner cancellation, missing GroundBoundController, dummy units, config subscriptions and stale source pointers. Behavior tests additionally retain the old ordinary NPC guard and verify wrappers of the same actual identity.

The fixtures do not assert client animation lengths, initialized Unity controller existence, source context, raw pool outcomes or damage generation. For full source boundaries and addresses see `D:\Repo\.rea-tools\arknights-pc\native_v9\npc_lifecycle\REPORT.md`.

```powershell
python -X utf8 -m unittest tests.test_npc_lifecycle tests.test_npc_lifecycle_reference -q
python -X utf8 evidence\npc_lifecycle\verify_evidence.py
```

Reviewed manifest pins never refresh automatically. A changed source or fixture requires explicit review before updating them. Runtime battle and complete-map readiness remain false.

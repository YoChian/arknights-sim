# Selected NPC damage reaction

This component executes only the selected default, no-hotfix `Entity.OnTakeDamage` and `Unit.OnTakeDamage` reaction. It accepts a decoded HP damage modifier, not a physics hit or an `ApplyModifier` request. The full calculation, earlier Applying/Output hooks, HP write, OnApplied hooks and damage completion remain outside this component.

- Reused original `Entity.OnTakeDamage` 0x1806fa4c0 and modifier cancellation functions from v6; selected `Unit.OnTakeDamage` 0x180acbc80 and `Enemy.MarkUnharmful` 0x180a6f4d0 were recovered in v9 round1. Exact original byte ranges and full source file hashes are retained in `native_functions.json`.
- Disappeared targets call Cancel(0) and return before Buff/mode/entity callbacks. The selected zero shared-flags shape excludes IgnoreCancel.
- Otherwise, an explicit IsUnhurtableWithModifier result may Cancel(1); an explicit ability-miss result may Cancel(6). Cancel retains the first cancellation. SP recovery type bit4 is rejected; its amount/controller implementation is not guessed.
- Cancellation does **not** suppress BuffContainer.OnTakeDamage, mode finalization or Entity event12. BuffContainer's own membership/finished/enabled gates are executed by its separate v9 module.
- Unit invokes its animator provider after the base call if the modifier is not cancelled. There is no new alive or UID gate at that point, even if Buff callbacks synchronously finished and recycled the owner.
- `Enemy.MarkUnharmful` changes the first Boolean in Enemy.Options. It does not set BObject.isDisappeared or grant damage immunity. The new reaction module does not read Options.unharmful as an immunity flag.

Gate results, mode finalization and animation are explicit sourced inputs/providers. The positive decoded value is restricted to at least EN5, with no ignore-cancel/shared branches. HP is never written by this module. Seven behavior tests cover disappearance, cancellation order, cancelled Buff delivery, bypass scope, synchronous recycle and rejected unclosed branches. These are tests of our own implementation, not client runtime comparisons.

`battle_ready=false`, `autonomous_route_ready=false`, `runtime_battle_validated=false`; reward remains None.

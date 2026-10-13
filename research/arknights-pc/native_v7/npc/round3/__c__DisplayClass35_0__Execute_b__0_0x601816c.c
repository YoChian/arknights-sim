void __c__DisplayClass35_0__Execute_b__0_0x601816c(longlong param_1,longlong param_2)
{
  code *pcVar1;
  if ((*(longlong *)(param_1 + 0x10) != 0) && (param_2 != 0)) {
    Torappu_Battle_Entity_AddBuffs_0x60103f3
              (param_2,*(undefined8 *)(*(longlong *)(param_1 + 0x10) + 0x80),
               *(undefined8 *)(param_1 + 0x18),0,*(undefined8 *)(param_1 + 0x20),0,0,0);
    return;
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

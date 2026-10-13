
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_States_DisappearState___c__DisplayClass21_0___DoDisappear_b__3_0x6012bf3
               (longlong param_1,float param_2)

{
  code *pcVar1;
  longlong *plVar2;
  undefined8 uStack_28;
  undefined4 uStack_20;
  float fStack_1c;
  
  if (DAT_188c9297d == '\0') {
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c9297d = '\x01';
  }
  param_2 = param_2 * *(float *)(param_1 + 0x1c);
  if (*(longlong *)(param_1 + 0x20) != 0) {
    plVar2 = (longlong *)FUN_18536e540(*(longlong *)(param_1 + 0x20),_DAT_188957b60);
    if (plVar2 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar2);
      }
      plVar2 = (longlong *)(**(code **)(*plVar2 + 0xb60))(plVar2,*(undefined8 *)(*plVar2 + 0xb68));
      if (plVar2 != (longlong *)0x0) {
        uStack_28 = 0;
        uStack_20 = 0;
        fStack_1c = param_2;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
        (**(code **)(*plVar2 + 0x1a0))(plVar2,&uStack_28,*(undefined8 *)(*plVar2 + 0x1a8));
        return;
      }
    }
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


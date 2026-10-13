
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_States_DisappearState___c__DisplayClass21_0___DoDisappear_b__1_0x6012bf2
               (longlong param_1,float param_2)

{
  undefined4 uVar1;
  code *pcVar2;
  longlong *plVar3;
  float fVar4;
  float fVar5;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  undefined4 uStack_4c;
  
  if (DAT_188c9297c == '\0') {
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c9297c = '\x01';
  }
  fVar4 = *(float *)(param_1 + 0x18) * param_2;
  fVar5 = *(float *)(param_1 + 0x10) * param_2;
  param_2 = *(float *)(param_1 + 0x14) * param_2;
  uVar1 = *(undefined4 *)(param_1 + 0x1c);
  if (*(longlong *)(param_1 + 0x20) != 0) {
    plVar3 = (longlong *)FUN_18536e540(*(longlong *)(param_1 + 0x20),_DAT_188957b60);
    if (plVar3 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar3);
      }
      plVar3 = (longlong *)(**(code **)(*plVar3 + 0xb60))(plVar3,*(undefined8 *)(*plVar3 + 0xb68));
      if (plVar3 != (longlong *)0x0) {
        fStack_58 = fVar5;
        fStack_54 = param_2;
        fStack_50 = fVar4;
        uStack_4c = uVar1;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar3);
        }
        (**(code **)(*plVar3 + 0x1a0))(plVar3,&fStack_58,*(undefined8 *)(*plVar3 + 0x1a8));
        return;
      }
    }
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


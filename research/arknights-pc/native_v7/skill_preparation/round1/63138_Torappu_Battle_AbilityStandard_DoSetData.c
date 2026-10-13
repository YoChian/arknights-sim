
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_DoSetData_0x600f6a3
               (longlong *param_1,undefined8 param_2,undefined4 *param_3)

{
  longlong *plVar1;
  code *pcVar2;
  undefined4 uVar3;
  longlong lVar4;
  uint uVar5;
  longlong lVar6;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c8fd25 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd25 = '\x01';
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x80);
  uStack_28 = *param_3;
  uStack_24 = param_3[1];
  uStack_20 = param_3[2];
  uStack_1c = param_3[3];
  uStack_18 = param_3[4];
  uStack_14 = param_3[5];
  uStack_10 = param_3[6];
  uStack_c = param_3[7];
  if (lVar4 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp2626_0x60014a2(lVar4,param_1,param_2,&uStack_28,0);
    return;
  }
  Torappu_Battle_Ability_DoSetData_0x600f650(param_1,param_2,&uStack_28,0);
  lVar4 = param_1[0x20];
  uVar5 = 0;
  if (lVar4 != 0) {
    lVar6 = 0x20;
    do {
      if (*(int *)(lVar4 + 0x18) <= (int)uVar5) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        uVar3 = (**(code **)(*param_1 + 0x710))(param_1,*(undefined8 *)(*param_1 + 0x718));
        *(undefined4 *)((longlong)param_1 + 0x10c) = uVar3;
        return;
      }
      lVar4 = param_1[0x20];
      if (lVar4 == 0) break;
      if (*(uint *)(lVar4 + 0x18) <= uVar5) {
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      plVar1 = *(longlong **)(lVar6 + lVar4);
      if (DAT_188c8fcc1 == '\0') {
        FUN_18048bf00(&DAT_1889733f0);
        DAT_188c8fcc1 = '\x01';
      }
      lVar4 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x30);
      if (lVar4 == 0) {
        lVar4 = param_1[0x11];
      }
      else {
        lVar4 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar4,param_1,0);
      }
      if (plVar1 == (longlong *)0x0) break;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar1);
      }
      (**(code **)(*plVar1 + 0x1a0))(plVar1,lVar4);
      lVar4 = param_1[0x20];
      uVar5 = uVar5 + 1;
      lVar6 = lVar6 + 8;
    } while (lVar4 != 0);
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


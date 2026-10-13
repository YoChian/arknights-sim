
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 Torappu_Battle_Ability_FinishIfNot_0x600f67b(longlong *param_1,int param_2,char param_3)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  
  if (DAT_188c8fd05 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fd05 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x250);
  if (lVar1 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp2641_0x60014b1(lVar1,param_1,param_2,param_3,0);
    return uVar5;
  }
  if (DAT_188c8fcd3 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fcd3 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xc0);
  if (lVar1 == 0) {
    cVar4 = (char)param_1[0xc];
  }
  else {
    cVar4 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
  }
  if (cVar4 == '\0') {
    return 0;
  }
  lVar1 = param_1[0xd];
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 0x3f0))(param_1,*(undefined8 *)(*param_1 + 0x3f8));
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 0x490))(param_1,param_2,*(undefined8 *)(*param_1 + 0x498));
  if (DAT_188c8fcf5 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fcf5 = '\x01';
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x1d0);
  if (lVar2 == 0) {
    if (param_3 == '\0') {
      if (param_2 == 3) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar4 = (**(code **)(*param_1 + 0x520))(param_1,*(undefined8 *)(*param_1 + 0x528));
        if (cVar4 != '\0') {
          if (param_1[0xe] == 0) goto LAB_1805d5b5f;
          Torappu_PeriodicTimer_Reset_0x6006575(param_1[0xe],0,0);
        }
      }
    }
    else {
      if (param_1[0xe] == 0) {
LAB_1805d5b5f:
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        uVar5 = (*pcVar3)();
        return uVar5;
      }
      Torappu_PeriodicTimer_Reset_0x6006575(param_1[0xe],1,0);
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp2644_0x60014b4(lVar2,param_1,param_2,param_3,0);
  }
  if (param_1[4] != 0) {
    lVar2 = param_1[4];
    (**(code **)(lVar2 + 0x18))
              (*(undefined8 *)(lVar2 + 0x40),param_1,param_2,param_3,*(undefined8 *)(lVar2 + 0x28));
  }
  if (lVar1 != 0) {
    (**(code **)(lVar1 + 0x18))
              (*(undefined8 *)(lVar1 + 0x40),param_1,param_2,param_3,*(undefined8 *)(lVar1 + 0x28));
  }
  return 1;
}


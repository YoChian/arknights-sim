
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_UpdateCooldownWhenFinish_0x600f664
               (longlong *param_1,int param_2,char param_3)

{
  code *pcVar1;
  char cVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  if (DAT_188c8fcf5 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fcf5 = '\x01';
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x1d0);
  if (lVar4 == 0) {
    if (param_3 != '\0') {
      lVar4 = param_1[0xe];
      if (lVar4 == 0) {
LAB_1805d7313:
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      cVar2 = '\x01';
Torappu_PeriodicTimer_Reset_0x6006575:
      if (cRam0000000188ca0cfd == '\0') {
        FUN_18048bf00(&DAT_18885a700,cVar2,0);
        cRam0000000188ca0cfd = '\x01';
      }
      if (cVar2 == '\0') {
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar3 = func_0x0001866fdac0(0,0);
      }
      else {
        uVar3 = *(undefined8 *)(lVar4 + 0x10);
      }
      if (lVar4 != 0) {
        *(undefined8 *)(lVar4 + 0x18) = uVar3;
        return;
      }
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if (param_2 == 3) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      cVar2 = (**(code **)(*param_1 + 0x520))(param_1);
      if (cVar2 != '\0') {
        lVar4 = param_1[0xe];
        if (lVar4 == 0) goto LAB_1805d7313;
        cVar2 = '\0';
        goto Torappu_PeriodicTimer_Reset_0x6006575;
      }
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp2644_0x60014b4(lVar4,param_1,param_2,param_3,0);
  }
  return;
}


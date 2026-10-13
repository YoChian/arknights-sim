
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_UnitAnimator_GetAnimationTime_0x600fa32
                    (longlong *param_1,longlong param_2,undefined4 *param_3,undefined4 *param_4)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  longlong *plVar5;
  ulonglong uVar6;
  longlong alStack_18 [2];
  
  if (DAT_188c8ffa1 == '\0') {
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188805280);
    DAT_188c8ffa1 = '\x01';
  }
  alStack_18[0] = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188805280 + 0xb8) + 0xe8);
  if (lVar1 == 0) {
    uVar4 = Torappu_Battle_UnitAnimator_get_hooker_0x600fa22(param_1,0);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b63a70(uVar4,0,0);
    if (cVar3 != '\0') {
      plVar5 = (longlong *)Torappu_Battle_UnitAnimator_get_hooker_0x600fa22(param_1,0);
      if (plVar5 == (longlong *)0x0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar6 = (*pcVar2)();
        return uVar6;
      }
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar5);
      }
      uVar6 = (**(code **)(*plVar5 + 0x180))
                        (plVar5,param_2,alStack_18,*(undefined8 *)(*plVar5 + 0x188));
      if (((char)uVar6 != '\0') && (param_2 = alStack_18[0], alStack_18[0] == 0)) {
        *param_3 = 0;
        *param_4 = 0x3f800000;
        return uVar6 & 0xffffffffffffff00;
      }
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar6 = (**(code **)(*param_1 + 0x420))
                      (param_1,param_2,param_3,param_4,*(undefined8 *)(*param_1 + 0x428));
  }
  else {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp2681_0x60014d9
                      (lVar1,param_1,param_2,param_3,param_4,0);
  }
  return uVar6;
}


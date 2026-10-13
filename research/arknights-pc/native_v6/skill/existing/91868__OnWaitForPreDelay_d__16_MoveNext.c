
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _OnWaitForPreDelay_d__16_MoveNext_0x60166dd(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  longlong lVar6;
  
  if (DAT_188c95703 == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_188820148);
    FUN_18048bf00(&DAT_188833ce0);
    DAT_188c95703 = '\x01';
  }
  iVar1 = *(int *)(param_1 + 0x10);
  lVar2 = *(longlong *)(param_1 + 0x20);
  if (iVar1 != 0) {
    if (((iVar1 == 1) || (iVar1 == 2)) || (iVar1 == 3)) {
      *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    }
    return 0;
  }
  *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar5 = Torappu_Battle_BattleController_get_fixedPlayTime_0x600fbd5(0);
  if (lVar2 != 0) {
    *(undefined8 *)(lVar2 + 0x130) = uVar5;
    cVar4 = Torappu_Battle_Abilities_EasyToStartAbility_get_waitForAttackEvent_0x60166c4(lVar2,0);
    if (cVar4 == '\0') {
      if (*(char *)(lVar2 + 0x119) == '\0') {
        uVar5 = FUN_180005610(100,lVar2);
        uVar5 = Torappu_Battle_AsyncUtil_WaitForFixedSeconds_0x600fa85(uVar5,0);
        *(undefined8 *)(param_1 + 0x18) = uVar5;
        func_0x00018048b9e0(param_1 + 0x18,uVar5);
        *(undefined4 *)(param_1 + 0x10) = 2;
      }
      else {
        lVar6 = func_0x00018045cfe0(_DAT_188833ce0);
        if (lVar6 == 0) goto LAB_180f0f10e;
        XLua___XLua_Gen_Delegate8__ctor_0x60010f4(lVar6,lVar2,_DAT_188820148,0);
        uVar5 = FUN_180005610(100,lVar2);
        uVar5 = Torappu_Battle_AsyncUtil_WaitWhileForFixedSeconds_0x600fa86(lVar6,uVar5,0);
        *(undefined8 *)(param_1 + 0x18) = uVar5;
        func_0x00018048b9e0(param_1 + 0x18,uVar5);
        *(undefined4 *)(param_1 + 0x10) = 1;
      }
    }
    else {
      uVar5 = *(undefined8 *)(lVar2 + 0x120);
      if (DAT_188c956f9 == '\0') {
        FUN_18048bf00(&DAT_18880dc70);
        FUN_18048bf00(&DAT_188851668);
        DAT_188c956f9 = '\x01';
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_18880dc70 + 0xb8) + 0x20);
      if (lVar6 == 0) {
        lVar6 = func_0x00018045cfe0(_DAT_188851668);
        if (lVar6 == 0) goto LAB_180f0f10e;
        func_0x00018050cf60(lVar6,0);
        *(undefined4 *)(lVar6 + 0x10) = 0;
        *(longlong *)(lVar6 + 0x20) = lVar2;
        func_0x00018048b9e0(lVar6 + 0x20,lVar2);
        *(undefined4 *)(lVar6 + 0x28) = 0x13;
        *(undefined8 *)(lVar6 + 0x30) = uVar5;
      }
      else {
        lVar6 = XLua_DelegateBridge___Gen_Delegate_Imp4429_0x6001bad(lVar6,lVar2,0x13,uVar5,0);
      }
      *(longlong *)(param_1 + 0x18) = lVar6;
      func_0x00018048b9e0(param_1 + 0x18,lVar6);
      *(undefined4 *)(param_1 + 0x10) = 3;
    }
    return 1;
  }
LAB_180f0f10e:
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  uVar5 = (*pcVar3)();
  return uVar5;
}


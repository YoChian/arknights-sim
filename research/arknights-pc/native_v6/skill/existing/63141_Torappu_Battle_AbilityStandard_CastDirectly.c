
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_AbilityStandard_CastDirectly_0x600f6a6
          (longlong *param_1,undefined8 param_2,undefined1 param_3)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  longlong lStack_28;
  
  if (DAT_188c8fd28 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18896aa50);
    FUN_18048bf00(&DAT_188886158);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_18896e2a0);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c8fd28 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x98);
  if (lVar1 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp112_0x6000ad0(lVar1,param_1,param_2,param_3,0);
    return uVar5;
  }
  uVar5 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b638d0(uVar5,0,0);
  if (cVar3 == '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar3 = (**(code **)(*param_1 + 0x260))(param_1,*(undefined8 *)(*param_1 + 0x268));
    if (cVar3 == '\0') {
      uStack_48 = (undefined4)param_1[10];
      uStack_44 = *(undefined4 *)((longlong)param_1 + 0x54);
      uStack_40 = (undefined4)param_1[0xb];
      uStack_3c = *(undefined4 *)((longlong)param_1 + 0x5c);
      cVar3 = FUN_18449ab40(&uStack_48,_DAT_18896aa50);
      if (cVar3 == '\0') {
        return 0;
      }
    }
    cVar3 = Torappu_Battle_AbilityStandard__CheckGameObjectActiveBeforeCast_0x600f6a4(param_1,0);
    if (cVar3 == '\0') {
      return 0;
    }
    FUN_180005610(0x2b,param_1);
    Torappu_Battle_AbilityStandard_set_firstAttack_0x600f69e(param_1,param_3,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar5 = (**(code **)(*param_1 + 0x5d0))(param_1,*(undefined8 *)(*param_1 + 0x5d8));
    FUN_1845638c0(&uStack_48,0,_DAT_18896e2a0);
    FUN_184559920(&uStack_38,uVar5,&uStack_48,_DAT_188886158);
    *(undefined4 *)(param_1 + 0x1c) = uStack_38;
    *(undefined4 *)((longlong)param_1 + 0xe4) = uStack_34;
    *(undefined4 *)(param_1 + 0x1d) = uStack_30;
    *(undefined4 *)((longlong)param_1 + 0xec) = uStack_2c;
    param_1[0x1e] = lStack_28;
    func_0x00018048b9e0(param_1 + 0x1d,0);
    iVar4 = FUN_180005610(0x45,param_1);
    if (((iVar4 != 0) && (iVar4 = FUN_180005610(0x45,param_1), iVar4 != 2)) ||
       (cVar3 = FUN_180005540(0x59,param_1,0), cVar3 != '\0')) {
      Torappu_Battle_Ability_RegisterFinishCallbackOnce_0x600f67f(param_1,param_2,0);
      if (param_1[0xe] == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar5 = (*pcVar2)();
        return uVar5;
      }
      Torappu_PeriodicTimer_Reset_0x6006575(param_1[0xe],1,0);
      Torappu_Battle_Ability_StartCastingInternal_0x600f681(param_1,0);
      uVar5 = Torappu_Battle_AbilityStandard__DoCast_0x600f6c7(param_1,0);
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      Torappu_Battle_BattleController_StartBattleCoroutine_0x600fce8(&uStack_48,param_1,uVar5,0);
      return 1;
    }
  }
  return 0;
}


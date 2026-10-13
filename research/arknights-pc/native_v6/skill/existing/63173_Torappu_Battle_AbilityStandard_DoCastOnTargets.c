
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_AbilityStandard_DoCastOnTargets_0x600f6c6
          (longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  code *pcVar1;
  char cVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  int iVar7;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  if (DAT_188c8fd44 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_18896aa50);
    FUN_18048bf00(0x1888e4030);
    FUN_18048bf00(&DAT_1888e4270);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c8fd44 = '\x01';
  }
  uStack_68 = 0;
  uStack_60 = 0;
  iVar7 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x180);
  if (lVar5 != 0) {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp42_0x6000a8a
                      (lVar5,param_1,param_2,param_3,param_4,0);
    return uVar6;
  }
  uVar6 = 0;
  lVar5 = *(longlong *)(param_1 + 0xd8);
  while (lVar5 != 0) {
    if (*(int *)(lVar5 + 0x18) <= iVar7) {
      return uVar6;
    }
    if (*(longlong *)(param_1 + 0xd8) == 0) break;
    FUN_184ad2ef0(&uStack_58,*(longlong *)(param_1 + 0xd8),iVar7,_DAT_1888e4270);
    uStack_48 = uStack_58;
    uStack_44 = uStack_54;
    uStack_40 = uStack_50;
    uStack_3c = uStack_4c;
    cVar2 = FUN_18449ab40(&uStack_48,_DAT_18896aa50);
    if (cVar2 != '\0') {
      if (*(longlong *)(param_1 + 0xd8) == 0) break;
      FUN_184ad2ef0(&uStack_38,*(longlong *)(param_1 + 0xd8),iVar7,_DAT_1888e4270);
      uStack_68 = CONCAT44(uStack_34,uStack_38);
      uStack_60 = CONCAT44(uStack_2c,uStack_30);
      uVar3 = FUN_185159d80(&uStack_68,_DAT_1889355a8);
      uVar6 = 1;
      FUN_18000da30(0x4c,param_1,uVar3,param_2,param_3,param_4);
      uVar4 = FUN_180005610(0xf,param_1);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b63a70(uVar4,0,0);
      if (cVar2 != '\0') {
        lVar5 = FUN_180005610(0xf,param_1);
        if (lVar5 == 0) break;
        Torappu_Battle_TargetSelector_OnCastedOnTarget_0x6012561(lVar5,uVar3,0);
      }
      cVar2 = Torappu_Battle_AbilityStandard_CheckFinished_0x600f6ca(param_1,0);
      if (cVar2 != '\0') {
        return 1;
      }
    }
    iVar7 = iVar7 + 1;
    lVar5 = *(longlong *)(param_1 + 0xd8);
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  uVar6 = (*pcVar1)();
  return uVar6;
}


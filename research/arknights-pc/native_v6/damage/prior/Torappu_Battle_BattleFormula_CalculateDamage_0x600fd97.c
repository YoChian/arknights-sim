/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
Torappu_Battle_BattleFormula_CalculateDamage_0x600fd97
          (longlong param_1,longlong param_2,char param_3,char param_4,undefined4 *param_5)
{
  longlong lVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char cVar11;
  undefined8 uVar12;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  if (DAT_188c90245 == '\0') {
    FUN_18048bf00(&DAT_18892fda0);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c90245 = '\x01';
  }
  if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x20);
  if (lVar1 == 0) {
    if (param_4 != '\0') {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar11 = FUN_186b63a70(param_2,0,0);
      if (cVar11 != '\0') {
        if (param_2 == 0) goto LAB_1806575d4;
        Torappu_Battle_Entity_OnCalculateDamage_0x6010465(param_2,param_1,param_5,0);
      }
    }
    if (param_3 != '\0') {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar11 = FUN_186b63a70(param_1,0,0);
      if (cVar11 != '\0') {
        if (param_1 == 0) goto LAB_1806575d4;
        Torappu_Battle_Entity_OnBeingCalculateDamage_0x6010467(param_1,param_5,0);
      }
    }
    uVar3 = *param_5;
    uVar4 = param_5[1];
    uVar5 = param_5[2];
    uVar6 = param_5[3];
    uVar7 = param_5[4];
    uVar8 = param_5[5];
    uVar9 = param_5[6];
    uVar10 = param_5[7];
    uVar12 = *(undefined8 *)(param_5 + 8);
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uStack_38 = uVar3;
    uStack_34 = uVar4;
    uStack_30 = uVar5;
    uStack_2c = uVar6;
    uStack_28 = uVar7;
    uStack_24 = uVar8;
    uStack_20 = uVar9;
    uStack_1c = uVar10;
    uStack_18 = uVar12;
    uVar12 = Torappu_Battle_BattleFormula_CalculateDamageNoEvent_0x600fd98
                       (param_1,param_2,&uStack_38,0);
    if (param_4 != '\0') {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar11 = FUN_186b63a70(param_2,0,0);
      if (cVar11 != '\0') {
        if (param_2 == 0) {
LAB_1806575d4:
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          uVar12 = (*pcVar2)();
          return uVar12;
        }
        Torappu_Battle_Entity_OnAfterCalculateDamage_0x6010466(param_2,param_1,param_5,0);
      }
    }
  }
  else {
    uVar12 = XLua_DelegateBridge___Gen_Delegate_Imp12109_0x60039ad
                       (lVar1,param_1,param_2,param_3,param_4,param_5,0);
  }
  return uVar12;
}

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_BattleFormula_CalculateDamageNoEvent_0x600fd98
               (undefined8 param_1,longlong param_2,int *param_3)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uStack_48;
  undefined8 uStack_40;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  undefined8 uStack_28;
  if (DAT_188c90246 == '\0') {
    FUN_18048bf00(&DAT_18892fda0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c90246 = '\x01';
  }
  if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18892fda0);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x28);
  if (lVar1 != 0) {
    uStack_48 = *(undefined8 *)param_3;
    uStack_40 = *(undefined8 *)(param_3 + 2);
    iStack_38 = param_3[4];
    iStack_34 = param_3[5];
    iStack_30 = param_3[6];
    iStack_2c = param_3[7];
    uStack_28 = *(undefined8 *)(param_3 + 8);
    XLua_DelegateBridge___Gen_Delegate_Imp12110_0x60039ae(lVar1,param_1,param_2,&uStack_48,0);
    return;
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18885a700);
  }
  uVar4 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x38);
  uVar5 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x38);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(param_2,0,0);
  if (cVar3 != '\0') {
    iStack_38 = param_3[4];
    iStack_34 = param_3[5];
    iStack_30 = param_3[6];
    iStack_2c = param_3[7];
    uStack_28 = *(undefined8 *)(param_3 + 8);
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    if (DAT_188c9024f == '\0') {
      FUN_18048bf00(&DAT_18892fda0);
      FUN_18048bf00(&DAT_18885a700);
      DAT_188c9024f = '\x01';
    }
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x70);
    if (lVar1 == 0) {
      if (*param_3 == 1) {
        if (param_2 == 0) goto LAB_1806573b7;
        uVar4 = Torappu_Battle_Entity_get_defPenetrateRatio_0x60103a7(param_2,0);
      }
      else if (*param_3 == 2) {
        if (param_2 == 0) goto LAB_1806573b7;
        uVar4 = Torappu_Battle_Entity_get_magicResistPenetrate_0x60103a9(param_2,0);
      }
      else {
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = func_0x0001866fdac0(0,0);
      }
    }
    else {
      uVar4 = XLua_DelegateBridge___Gen_Delegate_Imp12117_0x60039b5
                        (lVar1,param_2,param_1,*param_3,0);
    }
    iStack_38 = param_3[4];
    iStack_34 = param_3[5];
    iStack_30 = param_3[6];
    iStack_2c = param_3[7];
    uStack_28 = *(undefined8 *)(param_3 + 8);
    if (DAT_188c90250 == '\0') {
      FUN_18048bf00(&DAT_18892fda0);
      FUN_18048bf00(&DAT_18885a700);
      DAT_188c90250 = '\x01';
    }
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18892fda0);
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x78);
    if (lVar1 == 0) {
      if (*param_3 == 1) {
        if (param_2 == 0) {
LAB_1806573b7:
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        uVar5 = Torappu_Battle_Entity_get_defPenetrateFixed_0x60103a8(param_2,0);
      }
      else if (*param_3 == 2) {
        if (param_2 == 0) goto LAB_1806573b7;
        uVar5 = Torappu_Battle_Entity_get_magicResistPenetrateFixed_0x60103aa(param_2,0);
      }
      else {
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar5 = func_0x0001866fdac0(0,0);
      }
    }
    else {
      uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp12117_0x60039b5
                        (lVar1,param_2,param_1,*param_3,0);
    }
  }
  if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uStack_48 = *(undefined8 *)param_3;
  uStack_40 = *(undefined8 *)(param_3 + 2);
  iStack_38 = param_3[4];
  iStack_34 = param_3[5];
  iStack_30 = param_3[6];
  iStack_2c = param_3[7];
  uStack_28 = *(undefined8 *)(param_3 + 8);
  Torappu_Battle_BattleFormula_CalculateDamageInternal_0x600fd99(&uStack_48,uVar4,uVar5,param_1,0);
  return;
}

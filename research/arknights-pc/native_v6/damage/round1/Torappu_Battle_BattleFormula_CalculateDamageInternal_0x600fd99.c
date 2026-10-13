/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_BattleFormula_CalculateDamageInternal_0x600fd99
               (int *param_1,undefined8 param_2,undefined8 param_3,longlong param_4)
{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uStack_58;
  undefined8 uStack_50;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  undefined8 uStack_38;
  if (DAT_188c90247 == '\0') {
    FUN_18048bf00(&DAT_18892fda0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888915d8);
    DAT_188c90247 = '\x01';
  }
  if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18892fda0);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x30);
  if (lVar2 != 0) {
    uStack_58 = *(undefined8 *)param_1;
    uStack_50 = *(undefined8 *)(param_1 + 2);
    iStack_48 = param_1[4];
    iStack_44 = param_1[5];
    iStack_40 = param_1[6];
    iStack_3c = param_1[7];
    uStack_38 = *(undefined8 *)(param_1 + 8);
    XLua_DelegateBridge___Gen_Delegate_Imp12111_0x60039af
              (lVar2,&uStack_58,param_2,param_3,param_4,0);
    return;
  }
  uVar4 = AttackInfo_GetFinalAtk_0x600fdac(param_1,0);
  iVar1 = *param_1;
  if (iVar1 == 1) {
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18892fda0);
    }
    uVar5 = **(undefined8 **)(_DAT_18892fda0 + 0xb8);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = func_0x0001866fb870(uVar4,uVar5,0);
    uVar6 = func_0x0001866fdac0(0,0);
    if (param_4 == 0) goto LAB_180657047;
    uVar7 = Torappu_Battle_Entity_get_def_0x601039c(param_4,0);
    uVar7 = func_0x0001866fba10(uVar7,param_3,0);
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = Torappu_TSMath_Max_0x600033b(uVar6,uVar7,0);
    uVar7 = func_0x0001866fdac0(1,0);
    uVar7 = func_0x0001866fba10(uVar7,param_2,0);
    uVar6 = func_0x0001866fb870(uVar6,uVar7,0);
    uVar4 = func_0x0001866fba10(uVar4,uVar6,0);
  }
  else if (iVar1 == 2) {
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18892fda0);
    }
    uVar5 = **(undefined8 **)(_DAT_18892fda0 + 0xb8);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = func_0x0001866fb870(uVar4,uVar5,0);
    uVar6 = func_0x0001866fdac0(0,0);
    uVar7 = func_0x0001866fdac0(100,0);
    uVar8 = func_0x0001866fdac0(0,0);
    if (param_4 == 0) goto LAB_180657047;
    uVar9 = Torappu_Battle_Entity_get_magicResistance_0x601039d(param_4,0);
    uVar9 = func_0x0001866fba10(uVar9,param_3,0);
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = Torappu_TSMath_Max_0x600033b(uVar8,uVar9,0);
    uVar9 = func_0x0001866fdac0(1,0);
    uVar9 = func_0x0001866fba10(uVar9,param_2,0);
    uVar8 = func_0x0001866fb870(uVar8,uVar9,0);
    uVar7 = func_0x0001866fba10(uVar7,uVar8,0);
    uVar6 = Torappu_TSMath_Max_0x600033b(uVar6,uVar7,0);
    uVar4 = func_0x0001866fb870(uVar4,uVar6,0);
    uVar6 = func_0x0001866fdad0(0x3c23d70a,0);
    uVar4 = func_0x0001866fb870(uVar4,uVar6,0);
  }
  else {
    if (iVar1 == 3) {
      return;
    }
    if (iVar1 == 4) {
      return;
    }
    if (iVar1 != 5) {
      uVar4 = func_0x00018048bf20(0x18892d528);
      uVar4 = func_0x00018045cfe0(uVar4);
      FUN_180005cb0(uVar4);
      System_NotImplementedException__ctor_0x60009a4(uVar4,0);
      uVar5 = func_0x00018048bf20(0x188966018);
      FUN_18048c070(uVar4,uVar5);
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18892fda0);
    }
    uVar5 = **(undefined8 **)(_DAT_18892fda0 + 0xb8);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = func_0x0001866fb870(uVar4,uVar5,0);
    uVar6 = func_0x0001866fdac0(0,0);
    uVar7 = func_0x0001866fdac0(100,0);
    uVar8 = func_0x0001866fdac0(0,0);
    if (param_4 == 0) {
LAB_180657047:
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    uVar9 = Torappu_Battle_Entity_get_epDamageResistance_0x601039e(param_4,0);
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = Torappu_TSMath_Max_0x600033b(uVar8,uVar9,0);
    uVar7 = func_0x0001866fba10(uVar7,uVar8,0);
    uVar6 = Torappu_TSMath_Max_0x600033b(uVar6,uVar7,0);
    uVar4 = func_0x0001866fb870(uVar4,uVar6,0);
    uVar6 = func_0x0001866fdad0(0x3c23d70a,0);
    uVar4 = func_0x0001866fb870(uVar4,uVar6,0);
  }
  Torappu_TSMath_Max_0x600033b(uVar5,uVar4,0);
  return;
}

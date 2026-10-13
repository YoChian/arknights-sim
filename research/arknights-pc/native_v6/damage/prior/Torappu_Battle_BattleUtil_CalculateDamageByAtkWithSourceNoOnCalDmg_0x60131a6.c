/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 *
Torappu_Battle_BattleUtil_CalculateDamageByAtkWithSourceNoOnCalDmg_0x60131a6
          (undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined4 param_5,undefined4 param_6,undefined8 param_7,undefined4 param_8)
{
  longlong lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined8 in_stack_ffffffffffffff10;
  undefined4 uVar8;
  undefined8 in_stack_ffffffffffffff28;
  undefined4 uVar9;
  ulonglong auStack_c8 [5];
  undefined1 auStack_a0 [136];
  uVar8 = (undefined4)((ulonglong)in_stack_ffffffffffffff10 >> 0x20);
  uVar9 = (undefined4)((ulonglong)in_stack_ffffffffffffff28 >> 0x20);
  if (DAT_188c92d67 == '\0') {
    FUN_18048bf00(&DAT_18892fda0);
    FUN_18048bf00(&DAT_188937960);
    FUN_18048bf00(&DAT_1888ed178);
    DAT_188c92d67 = '\x01';
  }
  auStack_c8[4] = 0;
  auStack_c8[0] = 0;
  auStack_c8[1] = 0;
  auStack_c8[2] = 0;
  auStack_c8[3] = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188937960 + 0xb8) + 0xd0);
  if (lVar1 == 0) {
    AttackInfo__ctor_0x600fdaa(auStack_c8,param_2,param_5,param_7,0);
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = Torappu_Battle_BattleFormula_CalculateDamage_0x600fd97(param_4,param_3,1,0,auStack_c8,0)
    ;
    uVar4 = auStack_c8[0];
    uVar6 = AttackInfo_GetFinalAtk_0x600fdac(auStack_c8,0);
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    puVar7 = (undefined8 *)
             Torappu_Battle_Modifier_NewDamageModifierAfterCalculate_0x601155b
                       (auStack_a0,uVar5,uVar4 & 0xffffffff,param_6,param_3,param_4,param_8,uVar6,0)
    ;
  }
  else {
    puVar7 = (undefined8 *)
             XLua_DelegateBridge___Gen_Delegate_Imp12185_0x60039f9
                       (auStack_a0,lVar1,param_2,param_3,param_4,CONCAT44(uVar8,param_5),param_6,
                        param_7,CONCAT44(uVar9,param_8),0);
  }
  uVar5 = puVar7[1];
  uVar6 = puVar7[2];
  uVar2 = puVar7[3];
  *param_1 = *puVar7;
  param_1[1] = uVar5;
  uVar5 = puVar7[4];
  uVar3 = puVar7[5];
  param_1[2] = uVar6;
  param_1[3] = uVar2;
  uVar6 = puVar7[6];
  uVar2 = puVar7[7];
  param_1[4] = uVar5;
  param_1[5] = uVar3;
  uVar5 = puVar7[8];
  uVar3 = puVar7[9];
  param_1[6] = uVar6;
  param_1[7] = uVar2;
  uVar6 = puVar7[10];
  uVar2 = puVar7[0xb];
  param_1[8] = uVar5;
  param_1[9] = uVar3;
  uVar5 = puVar7[0xc];
  uVar3 = puVar7[0xd];
  param_1[10] = uVar6;
  param_1[0xb] = uVar2;
  uVar6 = puVar7[0xe];
  uVar2 = puVar7[0xf];
  param_1[0xc] = uVar5;
  param_1[0xd] = uVar3;
  uVar5 = puVar7[0x10];
  param_1[0xe] = uVar6;
  param_1[0xf] = uVar2;
  param_1[0x10] = uVar5;
  return param_1;
}

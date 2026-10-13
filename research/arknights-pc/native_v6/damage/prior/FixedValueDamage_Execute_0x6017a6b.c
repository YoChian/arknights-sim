/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong FixedValueDamage_Execute_0x6017a6b
                    (longlong param_1,longlong param_2,undefined4 param_3,longlong param_4)
{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined8 *puVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined8 in_stack_fffffffffffffe70;
  uint uVar15;
  undefined8 in_stack_fffffffffffffe78;
  undefined4 uVar16;
  undefined8 in_stack_fffffffffffffe80;
  undefined4 uVar17;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined1 auStack_c8 [160];
  uVar16 = (undefined4)((ulonglong)in_stack_fffffffffffffe78 >> 0x20);
  uVar15 = (uint)((ulonglong)in_stack_fffffffffffffe70 >> 0x20);
  uVar17 = (undefined4)((ulonglong)in_stack_fffffffffffffe80 >> 0x20);
  if (DAT_188c966f0 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_18895c7e0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_18887a850);
    FUN_18048bf00(0x1888e4030);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888915d8);
    FUN_18048bf00(&DAT_18890ece0);
    DAT_188c966f0 = '\x01';
  }
  uStack_d8 = 0;
  uStack_158 = 0;
  uStack_150 = 0;
  uStack_148 = 0;
  uStack_140 = 0;
  uStack_138 = 0;
  uStack_130 = 0;
  uStack_128 = 0;
  uStack_120 = 0;
  uStack_118 = 0;
  uStack_110 = 0;
  uStack_108 = 0;
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_e8 = 0;
  uStack_e0 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18887a850 + 0xb8) + 0x10);
  if (lVar5 != 0) {
    uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar5,param_1,param_2,param_3,param_4,0);
    return uVar7;
  }
  uVar4 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x34),0);
  lVar5 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x4c),0);
  uVar6 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x48),0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar7 = FUN_186b638d0(uVar4,0,0);
  if ((char)uVar7 != '\0') {
LAB_181057ee9:
    return uVar7 & 0xffffffffffffff00;
  }
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar7 = FUN_186b638d0(lVar5,0,0);
  if ((char)uVar7 != '\0') goto LAB_181057ee9;
  uVar9 = *(undefined8 *)(param_1 + 0x18);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar8 = func_0x0001866fdac0(0,0);
  if (param_2 == 0) goto LAB_181057f0a;
  uVar9 = Torappu_Blackboard_GetFpOrDefault_0x6007872(param_2,uVar9,uVar8,1,0);
  if (*(char *)(param_1 + 0x3a) != '\0') {
    uVar13 = Torappu_Blackboard_GetFloatOrDefault_0x6007871
                       (param_2,*(undefined8 *)(param_1 + 0x40),0x3f800000,0,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = func_0x0001866fdad0(uVar13,0);
    uVar9 = func_0x0001866fb870(uVar9,uVar8,0);
  }
  if ((*(char *)(param_1 + 0x68) != '\0') && (*(longlong *)(param_4 + 0x10) != 0)) {
    uVar8 = Torappu_Battle_Buff_get_ability_0x600fe47(*(undefined8 *)(param_4 + 0x10),0);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(uVar8,0,0);
    if (cVar2 != '\0') {
      if (*(longlong *)(param_4 + 0x10) == 0) goto LAB_181057f0a;
      uVar8 = Torappu_Battle_Buff_get_ability_0x600fe47(*(longlong *)(param_4 + 0x10),0);
      lVar10 = FUN_1800057a0(uVar8,_DAT_188974cb0);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = FUN_186b638d0(lVar10,0,0);
      if ((char)uVar7 != '\0') goto LAB_181057ee9;
      if (lVar10 == 0) goto LAB_181057f0a;
      uVar8 = Torappu_Battle_AbilityStandard_get_castTargets_0x600f691(lVar10,0);
      uVar7 = FUN_1844acab0(uVar8,_DAT_18895c7e0);
      if ((char)uVar7 != '\0') goto LAB_181057ee9;
      lVar10 = Torappu_Battle_AbilityStandard_get_castTargets_0x600f691(lVar10,0);
      if (lVar10 == 0) goto LAB_181057f0a;
      uVar13 = *(undefined4 *)(lVar10 + 0x18);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar8 = func_0x0001866fdac0(uVar13,0);
      uVar9 = Torappu_FP_op_Division_0x6000305(uVar9,uVar8,0);
    }
  }
  uVar8 = *(undefined8 *)(param_1 + 0x20);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar11 = func_0x0001866fdac0(1,0);
  uVar14 = 0;
  uVar8 = Torappu_Blackboard_GetFpOrDefault_0x6007872(param_2,uVar8,uVar11,0,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = FUN_186b63a70(uVar6,0,0);
  if ((cVar2 == '\0') || (*(char *)(param_1 + 0x32) != '\0')) {
    puVar12 = (undefined8 *)
              Torappu_Battle_BattleUtil_CalculateDamageByAtkNoSource_0x60131a4
                        (auStack_c8,uVar9,uVar4,*(undefined4 *)(param_1 + 0x10),
                         (ulonglong)uVar14 << 0x20,uVar8,
                         CONCAT44(uVar16,*(undefined4 *)(param_1 + 0x2c)),0);
  }
  else if (*(char *)(param_1 + 0x50) == '\0') {
    puVar12 = (undefined8 *)
              Torappu_Battle_BattleUtil_CalculateDamageByAtkWithSourceNoOnCalDmg_0x60131a6();
  }
  else {
    puVar12 = (undefined8 *)
              Torappu_Battle_BattleUtil_CalculateDamageByAtkWithSourceOnCalDmg_0x60131a7
                        (auStack_c8,uVar9,uVar6,uVar4,
                         CONCAT44(uVar14,*(undefined4 *)(param_1 + 0x10)),(ulonglong)uVar15 << 0x20,
                         uVar8,CONCAT44(uVar17,*(undefined4 *)(param_1 + 0x2c)),0);
  }
  uStack_158 = *puVar12;
  uStack_150 = puVar12[1];
  uStack_148 = puVar12[2];
  uStack_140 = puVar12[3];
  uStack_138 = puVar12[4];
  uStack_128 = puVar12[6];
  uStack_120 = puVar12[7];
  uStack_118 = puVar12[8];
  uStack_110 = puVar12[9];
  uStack_108 = puVar12[10];
  uStack_100 = puVar12[0xb];
  uStack_f8 = puVar12[0xc];
  uStack_f0 = puVar12[0xd];
  uStack_e8 = puVar12[0xe];
  uStack_e0 = puVar12[0xf];
  uStack_d8 = puVar12[0x10];
  uStack_130 = CONCAT71((int7)((ulonglong)puVar12[5] >> 8),*(undefined1 *)(param_1 + 0x28));
  if (*(char *)(param_1 + 0x30) != '\0') {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_Modifier_SetSharedFlag_0x6011550(&uStack_158,7,0);
    if (*(char *)(param_1 + 0x31) != '\0') {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      Torappu_Battle_Modifier_SetSharedFlag_0x6011550(&uStack_158,0xf,0);
    }
  }
  if (*(char *)(param_1 + 0x51) != '\0') {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_Modifier_SetSharedFlag_0x6011550(&uStack_158,5,0);
  }
  uVar16 = *(undefined4 *)(param_1 + 0x54);
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  Torappu_Battle_Modifier_SetIgnoreCancelReasonMask_0x6011558(&uStack_158,uVar16,0);
  if (*(char *)(param_1 + 0x58) != '\0') {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_Modifier_SetSharedFlag_0x6011550(&uStack_158,0xb,0);
  }
  if (*(char *)(param_1 + 0x59) != '\0') {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_Modifier_SetSharedFlag_0x6011550(&uStack_158,3,0);
  }
  uVar4 = *(undefined8 *)(param_1 + 0x60);
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  Torappu_Battle_Modifier_AddCustomKey_0x6011551(&uStack_158,uVar4,0);
  Torappu_Battle_BattleUtil_AddCustomKeyFromBlackboard_0x60131a9(&uStack_158,param_2,0,0);
  if (lVar5 != 0) {
    bVar3 = Torappu_Battle_Entity_ApplyModifier_0x601046a(lVar5,&uStack_158,0,0);
    uVar4 = uStack_120;
    if (*(char *)(param_1 + 0x38) != '\0') {
      if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar4 = Torappu_TSMath_Abs_0x600034b(uVar4,0);
      Torappu_Blackboard_Assign_0x600785c(param_2,_DAT_18890ece0,uVar4,0);
    }
    if (*(char *)(param_1 + 0x39) != '\0') {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar4 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(&uStack_158,0);
      if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar4 = Torappu_TSMath_Abs_0x600034b(uVar4,0);
      Torappu_Blackboard_Assign_0x600785c(param_2,_DAT_18890ece0,uVar4,0);
    }
    return (ulonglong)bVar3;
  }
LAB_181057f0a:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  uVar7 = (*pcVar1)();
  return uVar7;
}

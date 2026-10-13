
/* WARNING: Removing unreachable block (ram,0x00018330f795) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 Torappu_Battle_CastSkill_UseSkill_0x6011cc2(longlong *param_1,undefined4 param_2)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  code *pcVar4;
  undefined1 uVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  ulonglong uVar12;
  undefined4 uStack_44;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c91d0d == '\0') {
    uStack_30 = 0x180969334;
    FUN_18048bf00(&DAT_188855d90);
    DAT_188c91d0d = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    uStack_30 = 0x180969353;
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0xb0);
  if (lVar9 != 0) {
    if (cRam0000000188cafc31 == '\0') {
      FUN_18048bf00(0x18880c778,param_1,param_2,0);
      cRam0000000188cafc31 = '\x01';
    }
    if (*(longlong *)(lVar9 + 0x18) == 0) {
      FUN_18048c0b0();
code_r0x00018330f7ec:
      FUN_18048c0b0();
code_r0x00018330f7f2:
      FUN_18048c0b0();
    }
    else {
      auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
      uStack_30 = 0;
      puStack_28 = &stack0x00000008;
      puStack_20 = auStack_40;
      FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
      if (*(longlong *)(lVar9 + 0x18) == 0) goto code_r0x00018330f7fc;
      uVar3 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
      iVar7 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
        if (lVar1 == 0) goto code_r0x00018330f7ec;
        FUN_183cf8c20(lVar1,uVar3,param_1,0);
        uStack_44 = param_2;
        uVar10 = func_0x00018048b9c0(uRam000000018880c778,&uStack_44);
        FUN_183cfbf40(lVar1,uVar3,uVar10,0);
        iVar8 = FUN_183f22380(uVar3,2,1,iVar7,0);
        if (iVar8 == 0) {
code_r0x00018330f768:
          uVar5 = FUN_183f23100(uVar3,iVar7 + 1,0);
          FUN_183f22fd0(uVar3,iVar7 + -1,0);
          return uVar5;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar7 + -1,0);
          goto code_r0x00018330f768;
        }
        goto code_r0x00018330f7f2;
      }
    }
    FUN_18048c0b0();
code_r0x00018330f7fc:
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar4 = (code *)swi(3);
    uVar5 = (*pcVar4)();
    return uVar5;
  }
  if ((char)param_1[0x25] == '\0') {
    if (*(char *)((longlong)param_1 + 299) == '\0') {
      uStack_30 = 0x18096938b;
      lVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (lVar9 == 0) goto LAB_180969566;
      uStack_30 = 0x18096939e;
      cVar6 = Torappu_Battle_Character_CheckIsBornState_0x60128a8(lVar9,0);
      if (cVar6 != '\0') {
        return 0;
      }
    }
    if (cRam0000000188c91c4c == '\0') {
      FUN_18048bf00(&DAT_188925ba0,0,param_2,0);
      FUN_18048bf00(0x18896a750);
      cRam0000000188c91c4c = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x2c0);
    if (lVar9 != 0) {
      puStack_28 = (undefined1 *)0x0;
      uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp2812_0x600155c(lVar9,param_1,0,param_2);
      return uVar5;
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar6 = (**(code **)(*param_1 + 0x270))(param_1,param_2,*(undefined8 *)(*param_1 + 0x278));
    if (cVar6 == '\0') {
      return 0;
    }
    cVar6 = FUN_18000f7a0(0x34,param_1,0,param_2);
    if (cVar6 != '\0') {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      (**(code **)(*param_1 + 0x550))(param_1,*(undefined8 *)(*param_1 + 0x558));
      return 1;
    }
    uVar11 = 0;
    iVar7 = FUN_1844afc00(param_1[0x1b],uRam000000018896a750);
    if (0 < iVar7) {
      lVar9 = 0x20;
      uVar12 = uVar11;
      do {
        lVar1 = param_1[0x1b];
        if (lVar1 == 0) {
code_r0x000180959451:
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          uVar5 = (*pcVar4)();
          return uVar5;
        }
        if (*(uint *)(lVar1 + 0x18) <= (uint)uVar12) {
          FUN_18048c0a0();
          pcVar4 = (code *)swi(3);
          uVar5 = (*pcVar4)();
          return uVar5;
        }
        plVar2 = *(longlong **)(lVar9 + lVar1);
        if (plVar2 == (longlong *)0x0) goto code_r0x000180959451;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
        (**(code **)(*plVar2 + 0x1b0))(plVar2,*(undefined8 *)(*plVar2 + 0x1b8));
        uVar12 = (ulonglong)((uint)uVar12 + 1);
        uVar11 = uVar11 + 1;
        lVar9 = lVar9 + 8;
      } while ((longlong)uVar11 < (longlong)iVar7);
    }
    return 0;
  }
  uStack_30 = 0x1809693ca;
  cVar6 = Torappu_Battle_BasicSkill_get_isInChant_0x6011bd0(param_1,0);
  if (cVar6 == '\0') {
    if (DAT_188c91c17 == '\0') {
      uStack_30 = 0x1809693e6;
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c17 = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x118);
    if (lVar9 == 0) {
      *(undefined4 *)(param_1 + 0x22) = param_2;
    }
    else {
      uStack_30 = 0x18096941d;
      XLua_DelegateBridge___Gen_Delegate_Imp2739_0x6001513(lVar9,param_1,param_2,0);
    }
    if (*(char *)((longlong)param_1 + 0x12a) == '\0') {
      uStack_30 = 0x180969430;
      lVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (lVar9 == 0) goto LAB_180969566;
      uStack_30 = 0x180969443;
      cVar6 = Torappu_Battle_Character_CheckIsBornState_0x60128a8(lVar9,0);
      if (cVar6 != '\0') {
        return 0;
      }
    }
    uStack_30 = 0x18096945e;
    lVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
    if (lVar9 != 0) {
      uStack_30 = 0x180969471;
      Torappu_Battle_Character_SwitchToSkillState_0x60128a6(lVar9,0);
      return 1;
    }
    goto LAB_180969566;
  }
  if (DAT_188c91c45 == '\0') {
    uStack_30 = 0x180969493;
    FUN_18048bf00(&DAT_188925ba0);
    uStack_30 = 0x18096949f;
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91c45 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x288);
  if (lVar9 == 0) {
    lVar9 = param_1[0x1c];
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      uStack_30 = 0x1809694dc;
      func_0x00018048c140();
    }
    uStack_30 = 0x1809694e9;
    cVar6 = FUN_186b63a70(lVar9,0,0);
    if (cVar6 != '\0') {
      if (param_1[0x1c] == 0) goto LAB_180969566;
      uStack_30 = 0x180969500;
      cVar6 = Torappu_Battle_Skills_ChantBeforeSkill_get_isInExtraChant_0x6014b31(param_1[0x1c],0);
      goto LAB_18096950d;
    }
  }
  else {
    uStack_30 = 0x18096950d;
    cVar6 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar9,param_1,0);
LAB_18096950d:
    if (cVar6 != '\0') {
      uStack_30 = 0x180969541;
      Torappu_Battle_BasicSkill_DoStartSkill_0x6011bf1(param_1,0);
      return 1;
    }
  }
  uStack_30 = 0x18096951b;
  lVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
  if (lVar9 != 0) {
    uStack_30 = 0x18096952a;
    Torappu_Battle_Character_SwitchOutFromSkillState_0x60128a7(lVar9,0);
    return 1;
  }
LAB_180969566:
  uStack_30 = 0x18096956b;
  FUN_18048c0b0();
  pcVar4 = (code *)swi(3);
  uVar5 = (*pcVar4)();
  return uVar5;
}


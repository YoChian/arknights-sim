
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __DoCast_d__85_MoveNext_0x600f700(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  longlong *plVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  uint uVar9;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined8 uStack_30;
  longlong lStack_28;
  
  if (DAT_188c8fd6b == '\0') {
    FUN_18048bf00(&DAT_18895c7e0);
    FUN_18048bf00(&DAT_188811960);
    FUN_18048bf00(&DAT_18885a150);
    FUN_18048bf00(0x18885a5b8);
    FUN_18048bf00(&DAT_1888e4270);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_188935c68);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c8fd6b = '\x01';
  }
  iVar6 = *(int *)(param_1 + 0x10);
  plVar1 = *(longlong **)(param_1 + 0x20);
  uStack_58 = 0;
  uStack_50 = 0;
  if (iVar6 == 0) {
    uVar9 = 0;
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    if (plVar1 != (longlong *)0x0) {
      lVar7 = 0x20;
      while (lVar2 = plVar1[0x20], lVar2 != 0) {
        if (*(int *)(lVar2 + 0x18) <= (int)uVar9) {
          Torappu_Battle_AbilityStandard_OnEvent_0x600f6ad(plVar1,2,1,0);
          *(undefined1 *)((longlong)plVar1 + 0x116) = 1;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar1);
          }
          uVar8 = (**(code **)(*plVar1 + 0x620))(plVar1,*(undefined8 *)(*plVar1 + 0x628));
          *(undefined8 *)(param_1 + 0x18) = uVar8;
          func_0x00018048b9e0(param_1 + 0x18,uVar8);
          *(undefined4 *)(param_1 + 0x10) = 1;
          return 1;
        }
        if (*(uint *)(lVar2 + 0x18) <= uVar9) {
          FUN_18048c0a0();
          pcVar4 = (code *)swi(3);
          uVar8 = (*pcVar4)();
          return uVar8;
        }
        plVar3 = *(longlong **)(lVar7 + lVar2);
        if (plVar3 == (longlong *)0x0) break;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar3);
        }
        (**(code **)(*plVar3 + 0x1b0))(plVar3,*(undefined8 *)(*plVar3 + 0x1b8));
        uVar9 = uVar9 + 1;
        lVar7 = lVar7 + 8;
      }
    }
    goto LAB_1805e4479;
  }
  if (iVar6 == 1) {
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    if (plVar1 == (longlong *)0x0) goto LAB_1805e4479;
    *(undefined1 *)((longlong)plVar1 + 0x116) = 0;
    Torappu_Battle_AbilityStandard_set_spellCnt_0x600f69c(plVar1,0,0);
    lVar7 = Torappu_Battle_Ability_get_owner_0x600f630(plVar1,0);
    if (lVar7 == 0) goto LAB_1805e4479;
    Torappu_Battle_Entity_OnBeforeAbilitySpellOn_0x6010487(lVar7,plVar1,0);
  }
  else {
    if (iVar6 != 2) {
      if (iVar6 != 3) {
        return 0;
      }
      *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
      if (plVar1 != (longlong *)0x0) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar1);
        }
        (**(code **)(*plVar1 + 0x530))(plVar1,0,0,*(undefined8 *)(*plVar1 + 0x538));
        lVar7 = FUN_185337c50(_DAT_1888d3908);
        if ((lVar7 != 0) &&
           (lVar7 = Torappu_Battle_BattleController_get_eventPool_0x600fbf9(lVar7,0), lVar7 != 0)) {
          FUN_1848dca60(lVar7,0xf,plVar1,_DAT_188811960);
          return 0;
        }
      }
      goto LAB_1805e4479;
    }
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    if (plVar1 == (longlong *)0x0) goto LAB_1805e4479;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar1);
  }
  iVar6 = (**(code **)(*plVar1 + 0x590))(plVar1,*(undefined8 *)(*plVar1 + 0x598));
  if (iVar6 == 1) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar1);
    }
    cVar5 = (**(code **)(*plVar1 + 0x6d0))(plVar1,1,*(undefined8 *)(*plVar1 + 0x6d8));
    if (cVar5 == '\0') goto LAB_1805e4340;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar1);
  }
  iVar6 = (**(code **)(*plVar1 + 0x590))(plVar1,*(undefined8 *)(*plVar1 + 0x598));
  if (((iVar6 == 3) &&
      (iVar6 = Torappu_Battle_AbilityStandard_get_spellCnt_0x600f69b(plVar1,0), iVar6 == 0)) &&
     (cVar5 = FUN_180005540(0x59,plVar1,1), cVar5 == '\0')) goto LAB_1805e4340;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar1);
  }
  iVar6 = (**(code **)(*plVar1 + 0x590))(plVar1,*(undefined8 *)(*plVar1 + 0x598));
  if (iVar6 == 2) {
    uStack_58 = plVar1[0x1d];
    uStack_50 = plVar1[0x1e];
    lVar7 = FUN_185159d80(&uStack_58,_DAT_1889355a8);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar5 = FUN_186b638d0(lVar7,0,0);
    if (cVar5 == '\0') {
      if (lVar7 == 0) goto LAB_1805e4479;
      cVar5 = FUN_180005610(0x28,lVar7);
      if (cVar5 != '\0') goto LAB_1805e41f2;
    }
    cVar5 = FUN_180005540(0x59,plVar1,1);
    if (cVar5 == '\0') {
LAB_1805e4340:
      FUN_18000d950(0x3f,plVar1,3,0);
      return 0;
    }
    cVar5 = FUN_1844acab0(plVar1[0x1b],_DAT_18895c7e0);
    if (cVar5 == '\0') {
      if (plVar1[0x1b] == 0) goto LAB_1805e4479;
      FUN_184ad2ef0(&uStack_48,plVar1[0x1b],0,_DAT_1888e4270);
      uStack_58 = CONCAT44(uStack_44,uStack_48);
      uStack_50 = CONCAT44(uStack_3c,uStack_40);
      lVar7 = FUN_185159d80(&uStack_58,_DAT_1889355a8);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar5 = FUN_186b63a70(lVar7,0,0);
      if (cVar5 != '\0') {
        if (lVar7 == 0) {
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          uVar8 = (*pcVar4)();
          return uVar8;
        }
        uVar8 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(lVar7,0);
        FUN_18515a130(&uStack_48,lVar7,_DAT_188935c68);
        uStack_38 = 0;
        uStack_30 = 0;
        lStack_28 = 0;
        func_0x000184a62fb0(&uStack_38,uVar8,&uStack_48,_DAT_18885a150);
        *(undefined4 *)(plVar1 + 0x1c) = (undefined4)uStack_38;
        *(undefined4 *)((longlong)plVar1 + 0xe4) = uStack_38._4_4_;
        *(undefined4 *)(plVar1 + 0x1d) = (undefined4)uStack_30;
        *(undefined4 *)((longlong)plVar1 + 0xec) = uStack_30._4_4_;
        plVar1[0x1e] = lStack_28;
        func_0x00018048b9e0(plVar1 + 0x1d,0);
      }
    }
  }
LAB_1805e41f2:
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar1);
  }
  cVar5 = (**(code **)(*plVar1 + 0x650))(plVar1,*(undefined8 *)(*plVar1 + 0x658));
  if (cVar5 == '\0') {
    return 0;
  }
  cVar5 = Torappu_Battle_Ability_get_isCasting_0x600f63e(plVar1,0);
  if (cVar5 == '\0') {
    return 0;
  }
  iVar6 = Torappu_Battle_AbilityStandard_get_spellCnt_0x600f69b(plVar1,0);
  Torappu_Battle_AbilityStandard_set_spellCnt_0x600f69c(plVar1,iVar6 + 1,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar1);
  }
  cVar5 = (**(code **)(*plVar1 + 0x6e0))(plVar1,iVar6 + 1,*(undefined8 *)(*plVar1 + 0x6e8));
  if (cVar5 != '\0') {
    uVar8 = FUN_180005610(0x50,plVar1);
    *(undefined8 *)(param_1 + 0x18) = uVar8;
    func_0x00018048b9e0(param_1 + 0x18,uVar8);
    *(undefined4 *)(param_1 + 0x10) = 2;
    return 1;
  }
  Torappu_Battle_AbilityStandard_OnEvent_0x600f6ad(plVar1,5,1,0);
  uVar8 = Torappu_Battle_Ability_get_owner_0x600f630(plVar1,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar5 = FUN_186b638d0(uVar8,0,0);
  if (cVar5 == '\0') {
    lVar7 = Torappu_Battle_Ability_get_owner_0x600f630(plVar1,0);
    if (lVar7 == 0) {
LAB_1805e4479:
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      uVar8 = (*pcVar4)();
      return uVar8;
    }
    cVar5 = FUN_180005610(0x28,lVar7);
    if ((cVar5 != '\0') || ((char)plVar1[0x1a] != '\0')) {
      uVar8 = FUN_180005610(0x4f,plVar1);
      *(undefined8 *)(param_1 + 0x18) = uVar8;
      func_0x00018048b9e0(param_1 + 0x18,uVar8);
      *(undefined4 *)(param_1 + 0x10) = 3;
      return 1;
    }
  }
  FUN_18000d950(0x3f,plVar1,2,0);
  return 0;
}


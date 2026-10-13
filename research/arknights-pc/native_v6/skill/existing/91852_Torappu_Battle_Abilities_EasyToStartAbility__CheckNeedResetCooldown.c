
/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_Battle_Abilities_EasyToStartAbility__CheckNeedResetCooldown_0x60166cd
               (longlong *param_1)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c956fc == '\0') {
    puStack_30 = (undefined1 *)0x180f0befe;
    FUN_18048bf00(&DAT_188927d60);
    puStack_30 = (undefined1 *)0x180f0bf0a;
    FUN_18048bf00(&DAT_18880dc70);
    puStack_30 = (undefined1 *)0x180f0bf16;
    FUN_18048bf00(&DAT_18885a700);
    puStack_30 = (undefined1 *)0x180f0bf22;
    FUN_18048bf00(&DAT_1888c3c38);
    DAT_188c956fc = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18880dc70 + 0xb8) + 0x38);
  if (lVar8 == 0) {
    lVar8 = param_1[0x24];
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined1 *)0x180f0bf65;
      func_0x000180446d00(*param_1);
    }
    puStack_30 = (undefined1 *)0x180f0bf7b;
    uVar7 = (**(code **)(*param_1 + 0x250))(param_1,*(undefined8 *)(*param_1 + 600));
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      puStack_30 = (undefined1 *)0x180f0bf93;
      func_0x00018048c140();
    }
    puStack_30 = (undefined1 *)0x180f0bfa1;
    cVar3 = Torappu_MathUtil_Equals_0x6000284(lVar8,uVar7,0);
    if (cVar3 == '\0') {
      return false;
    }
    iVar5 = *(int *)((longlong)param_1 + 0x11c);
    if (iVar5 == 1) {
      puStack_30 = (undefined1 *)0x180f0c08e;
      lVar8 = Torappu_Battle_Ability_get_remainingTime_0x600f635(param_1,0);
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        puStack_30 = (undefined1 *)0x180f0c0a6;
        func_0x00018048c140();
      }
      if (cRam0000000188cc3714 == '\0') {
        puStack_30 = &UNK_1866e5232;
        FUN_18048bf00(0x1888ba140,0);
        puStack_30 = &UNK_1866e523e;
        FUN_18048bf00(&DAT_1888c3c38);
        cRam0000000188cc3714 = '\x01';
      }
      if (*(int *)(lRam00000001888ba140 + 0xe0) == 0) {
        puStack_30 = &UNK_1866e525d;
        func_0x00018048c140(lRam00000001888ba140);
      }
      uVar7 = *(undefined8 *)(*(longlong *)(lRam00000001888ba140 + 0xb8) + 0x48);
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        puStack_30 = &UNK_1866e5284;
        func_0x00018048c140();
      }
    }
    else {
      if (iVar5 != 2) {
        if (iVar5 != 3) {
          return false;
        }
        puStack_30 = (undefined1 *)0x180f0bfd0;
        lVar8 = Torappu_Battle_Ability_get_remainingTime_0x600f635(param_1,0);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          puStack_30 = (undefined1 *)0x180f0bfe8;
          func_0x00018048c140();
        }
        puStack_30 = (undefined1 *)0x180f0bff1;
        uVar7 = func_0x0001866fdac0(0,0);
        if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
          puStack_30 = (undefined1 *)0x180f0c009;
          func_0x00018048c140();
        }
        if (cRam0000000188cc3702 == '\0') {
          puStack_30 = &UNK_1866e572a;
          FUN_18048bf00(&DAT_18885a700);
          puStack_30 = &UNK_1866e5736;
          FUN_18048bf00(&DAT_1888c3c38);
          cRam0000000188cc3702 = '\x01';
        }
        if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
          puStack_30 = &UNK_1866e5755;
          func_0x00018048c140(_DAT_1888c3c38);
        }
        uVar1 = **(undefined8 **)(_DAT_1888c3c38 + 0xb8);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          puStack_30 = &UNK_1866e577b;
          func_0x00018048c140();
        }
        puStack_30 = &UNK_1866e5789;
        lVar9 = func_0x000184624db0(uVar7,uVar1,0);
        goto code_r0x000185ed91f0;
      }
      puStack_30 = (undefined1 *)0x180f0c030;
      lVar8 = Torappu_Battle_Ability_get_remainingTime_0x600f635(param_1,0);
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        puStack_30 = (undefined1 *)0x180f0c048;
        func_0x00018048c140();
      }
      puStack_30 = (undefined1 *)0x180f0c04f;
      uVar7 = Torappu_Battle_BattleController_get_deltaPlayTimeFP_0x600fc5b(0);
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        puStack_30 = (undefined1 *)0x180f0c067;
        func_0x00018048c140();
      }
      if (cRam0000000188cc3713 == '\0') {
        puStack_30 = &UNK_1866e5365;
        FUN_18048bf00(&DAT_1888c3c38);
        cRam0000000188cc3713 = '\x01';
      }
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        puStack_30 = &UNK_1866e5381;
        func_0x00018048c140();
      }
    }
    if (cRam0000000188cc3701 == '\0') {
      puStack_30 = &UNK_1866e57da;
      FUN_18048bf00(&DAT_18885a700);
      puStack_30 = &UNK_1866e57e6;
      FUN_18048bf00(&DAT_1888c3c38);
      cRam0000000188cc3701 = '\x01';
    }
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      puStack_30 = &UNK_1866e5805;
      func_0x00018048c140(_DAT_1888c3c38);
    }
    uVar1 = **(undefined8 **)(_DAT_1888c3c38 + 0xb8);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = &UNK_1866e582b;
      func_0x00018048c140();
    }
    puStack_30 = &UNK_1866e5839;
    lVar9 = func_0x0001866fba10(uVar7,uVar1,0);
code_r0x000185ed91f0:
    return lVar8 < lVar9;
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar7 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar9 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar9,uVar7,param_1,0);
      iVar6 = FUN_183f22380(uVar7,1,1,iVar5,0);
      if (iVar6 == 0) {
code_r0x0001832b39f4:
        uVar4 = FUN_183f23100(uVar7,iVar5 + 1,0);
        FUN_183f22fd0(uVar7,iVar5 + -1,0);
        return (bool)uVar4;
      }
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar5 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  uVar4 = (*pcVar2)();
  return (bool)uVar4;
}


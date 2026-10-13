
/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_Battle_CastSkill_get_spEnough_0x6011cb0(longlong param_1)

{
  undefined8 uVar1;
  code *pcVar2;
  undefined1 uVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong lVar10;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c91cfb == '\0') {
    puStack_30 = (undefined *)0x18096a3fe;
    FUN_18048bf00(&DAT_188855d90);
    puStack_30 = (undefined *)0x18096a40a;
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91cfb = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    puStack_30 = (undefined *)0x18096a429;
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0x20);
  if (lVar10 == 0) {
    if (*(char *)(param_1 + 0x144) != '\0') {
      puStack_30 = (undefined *)0x18096a457;
      uVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        puStack_30 = (undefined *)0x18096a46f;
        func_0x00018048c140();
      }
      puStack_30 = (undefined *)0x18096a47c;
      cVar4 = FUN_186b63a70(uVar9,0,0);
      if (cVar4 != '\0') {
        puStack_30 = (undefined *)0x18096a48f;
        lVar10 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
        if (lVar10 == 0) {
          puStack_30 = (undefined *)0x18096a4ce;
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          uVar3 = (*pcVar2)();
          return (bool)uVar3;
        }
        puStack_30 = (undefined *)0x18096a49e;
        cVar4 = Torappu_Battle_Character_get_isInSkillState_0x601288c(lVar10,0);
        if (cVar4 != '\0') {
          return true;
        }
      }
    }
    if (cRam0000000188c91c2d == '\0') {
      puStack_30 = &UNK_1809617de;
      FUN_18048bf00(&DAT_188925ba0,0);
      puStack_30 = &UNK_1809617ea;
      FUN_18048bf00(&DAT_18885a700);
      puStack_30 = &UNK_1809617f6;
      FUN_18048bf00(&DAT_1888c3c38);
      puStack_30 = &UNK_180961802;
      FUN_18048bf00(&DAT_188932ce8);
      cRam0000000188c91c2d = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x1c8);
    if (lVar10 == 0) {
      if (DAT_188c91c3d == '\0') {
        puStack_30 = &UNK_180961840;
        FUN_18048bf00(&DAT_188925ba0);
        DAT_188c91c3d = '\x01';
      }
      lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
      if (lVar10 == 0) {
        uVar9 = *(undefined8 *)(param_1 + 0xa8);
      }
      else {
        puStack_30 = &UNK_180961875;
        uVar9 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar10,param_1,0);
      }
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        puStack_30 = &UNK_18096188d;
        func_0x00018048c140();
      }
      puStack_30 = &UNK_18096189a;
      cVar4 = FUN_186b638d0(uVar9,0,0);
      if (cVar4 != '\0') {
        return false;
      }
      if (*(int *)(param_1 + 0x9c) < 0) {
        puStack_30 = &UNK_1809618b4;
        cVar4 = FUN_18095f390();
        if (cVar4 != '\0') {
          return true;
        }
        puStack_30 = &UNK_1809618cf;
        lVar10 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
        if (lVar10 != 0) {
          puStack_30 = &UNK_1809618e2;
          lVar10 = Torappu_Battle_Entity_get_sp_0x6010388(lVar10,0);
          puStack_30 = &UNK_1809618ef;
          lVar8 = Torappu_Battle_BasicSkill_get_data_0x6011bc1(param_1,0);
          if (lVar8 != 0) {
            puStack_30 = &UNK_180961902;
            uVar5 = Torappu_SkillData_get_spCost_0x600805e(lVar8,0);
            goto code_r0x000180961923;
          }
        }
      }
      else {
        puStack_30 = &UNK_18096190b;
        lVar10 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1);
        if (lVar10 != 0) {
          puStack_30 = &UNK_18096191a;
          lVar10 = Torappu_Battle_Entity_get_sp_0x6010388(lVar10,0);
          uVar5 = *(undefined4 *)(param_1 + 0x9c);
code_r0x000180961923:
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            puStack_30 = &UNK_180961938;
            func_0x00018048c140();
          }
          puStack_30 = &UNK_180961941;
          uVar9 = func_0x0001866fdac0(uVar5,0);
          if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
            puStack_30 = &UNK_180961959;
            func_0x00018048c140();
          }
          if (cRam0000000188cc3700 == '\0') {
            puStack_30 = &UNK_1866e4bca;
            FUN_18048bf00(&DAT_18885a700);
            puStack_30 = &UNK_1866e4bd6;
            FUN_18048bf00(&DAT_1888c3c38);
            cRam0000000188cc3700 = '\x01';
          }
          if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
            puStack_30 = &UNK_1866e4bf5;
            func_0x00018048c140(_DAT_1888c3c38);
          }
          uVar1 = **(undefined8 **)(_DAT_1888c3c38 + 0xb8);
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            puStack_30 = &UNK_1866e4c1b;
            func_0x00018048c140();
          }
          puStack_30 = &UNK_1866e4c29;
          lVar8 = func_0x0001866fba10(uVar9,uVar1,0);
          return lVar8 < lVar10;
        }
      }
      puStack_30 = &UNK_180961993;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar3 = (*pcVar2)();
      return (bool)uVar3;
    }
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar10 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar9 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar8 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar8 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar8,uVar9,param_1,0);
      iVar7 = FUN_183f22380(uVar9,1,1,iVar6,0);
      if (iVar7 == 0) {
code_r0x0001832b39f4:
        uVar3 = FUN_183f23100(uVar9,iVar6 + 1,0);
        FUN_183f22fd0(uVar9,iVar6 + -1,0);
        return (bool)uVar3;
      }
      if (*(longlong *)(lVar10 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar6 + -1,0);
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
  uVar3 = (*pcVar2)();
  return (bool)uVar3;
}


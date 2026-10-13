
/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_BasicSkill_get_ownerCanUseSkill_0x6011b90(longlong param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  longlong lVar9;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c91c04 == '\0') {
    puStack_30 = (undefined1 *)0x1809604ae;
    FUN_18048bf00(&DAT_188925ba0);
    puStack_30 = (undefined1 *)0x1809604ba;
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91c04 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x80);
  if (lVar9 == 0) {
    if (DAT_188c91c3d == '\0') {
      puStack_30 = (undefined1 *)0x1809604f9;
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar9 == 0) {
      uVar7 = *(undefined8 *)(param_1 + 0xa8);
    }
    else {
      puStack_30 = (undefined1 *)0x18096052e;
      uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar9,param_1,0);
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      puStack_30 = (undefined1 *)0x180960546;
      func_0x00018048c140();
    }
    puStack_30 = (undefined1 *)0x180960553;
    uVar8 = FUN_186b638d0(uVar7,0,0);
    if ((char)uVar8 == '\0') {
      puStack_30 = (undefined1 *)0x18096056a;
      cVar3 = Torappu_Battle_BasicSkill_get_ownerNotInAbnormalState_0x6011b91(param_1,0);
      if (cVar3 == '\0') {
        if (DAT_188c91c06 == '\0') {
          puStack_30 = (undefined1 *)0x180960586;
          FUN_18048bf00(&DAT_188925ba0);
          DAT_188c91c06 = '\x01';
        }
        lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x90);
        if (lVar9 == 0) {
          if (*(char *)(param_1 + 0x27) == '\0') {
            puStack_30 = (undefined1 *)0x1809605ba;
            lVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
            if (lVar9 == 0) goto LAB_180960721;
            puStack_30 = (undefined1 *)0x1809605cd;
            uVar8 = Torappu_Battle_Entity_get_isSkillActivatableInAbnormal_0x60103dc(lVar9,0);
            if ((char)uVar8 == '\0') goto LAB_180960706;
          }
          if (DAT_188c91c3d == '\0') {
            puStack_30 = (undefined1 *)0x1809605ea;
            FUN_18048bf00(&DAT_188925ba0);
            DAT_188c91c3d = '\x01';
          }
          lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
          if (lVar9 == 0) {
            lVar9 = *(longlong *)(param_1 + 0xa8);
          }
          else {
            puStack_30 = (undefined1 *)0x18096061f;
            lVar9 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar9,param_1,0);
          }
          if (lVar9 == 0) goto LAB_180960721;
          puStack_30 = (undefined1 *)0x180960632;
          uVar8 = Torappu_Battle_Entity_get_isSilenced_0x60103da(lVar9,0);
          uVar8 = uVar8 ^ 1;
        }
        else {
          puStack_30 = (undefined1 *)0x180960641;
          uVar8 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar9,param_1,0);
        }
        if ((char)uVar8 == '\0') goto LAB_180960706;
      }
      if (DAT_188c91c07 == '\0') {
        puStack_30 = (undefined1 *)0x18096065e;
        FUN_18048bf00(&DAT_188925ba0);
        DAT_188c91c07 = '\x01';
      }
      lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x98);
      if (lVar9 == 0) {
        if (DAT_188c91c3d == '\0') {
          puStack_30 = (undefined1 *)0x180960693;
          FUN_18048bf00(&DAT_188925ba0);
          DAT_188c91c3d = '\x01';
        }
        lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
        if (lVar9 == 0) {
          lVar9 = *(longlong *)(param_1 + 0xa8);
        }
        else {
          puStack_30 = (undefined1 *)0x1809606c8;
          lVar9 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar9,param_1,0);
        }
        if (lVar9 == 0) goto LAB_180960721;
        puStack_30 = (undefined1 *)0x1809606d7;
        uVar8 = Torappu_Battle_Entity_get_isSkillActivatable_0x60103db(lVar9,0);
      }
      else {
        puStack_30 = (undefined1 *)0x1809606e4;
        uVar8 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar9,param_1,0);
      }
      if ((char)uVar8 != '\0') {
        if (*(longlong *)(param_1 + 0xa8) != 0) {
          puStack_30 = (undefined1 *)0x1809606fe;
          uVar8 = FUN_180005610(0x9c);
          return uVar8 ^ 1;
        }
LAB_180960721:
        puStack_30 = (undefined1 *)0x180960726;
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar8 = (*pcVar2)();
        return uVar8;
      }
    }
LAB_180960706:
    return uVar8 & 0xffffffffffffff00;
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar9 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar7 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar1 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar1,uVar7,param_1,0);
      iVar6 = FUN_183f22380(uVar7,1,1,iVar5,0);
      if (iVar6 == 0) {
code_r0x0001832b39f4:
        bVar4 = FUN_183f23100(uVar7,iVar5 + 1,0);
        FUN_183f22fd0(uVar7,iVar5 + -1,0);
        return (ulonglong)bVar4;
      }
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar5 + -1,0);
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
  uVar8 = (*pcVar2)();
  return uVar8;
}


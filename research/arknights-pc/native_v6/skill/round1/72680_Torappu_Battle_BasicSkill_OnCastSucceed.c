
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnCastSucceed_0x6011be9(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  longlong *plVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  
  if (DAT_188c91c5a == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_18896a750);
    FUN_18048bf00(&DAT_188811960);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888d36c8);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c91c5a = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x338);
  if (lVar8 == 0) {
    if (DAT_188c91bfd == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91bfd = '\x01';
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x48);
    if (lVar8 == 0) {
      cVar5 = *(char *)(param_1 + 0x1c);
    }
    else {
      cVar5 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar8,param_1,0);
    }
    if (cVar5 == '\0') {
      Torappu_Battle_BasicSkill_set_registeredAsModifier_0x6011bbf(param_1,1,0);
    }
    *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + 1;
    if (DAT_188c91c3d == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar8 == 0) {
      lVar8 = *(longlong *)(param_1 + 0xa8);
    }
    else {
      lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar8,param_1,0);
    }
    if ((lVar8 != 0) &&
       (lVar8 = Torappu_Battle_Character_get_sharedData_0x6012885(lVar8,0), lVar8 != 0)) {
      *(int *)(lVar8 + 0x10) = *(int *)(lVar8 + 0x10) + 1;
      cVar5 = Torappu_Battle_BasicSkill_get_isUsedUp_0x6011bbd(param_1,0);
      if (cVar5 != '\0') {
        Torappu_Battle_BasicSkill_set_registeredAsModifier_0x6011bbf(param_1,1,0);
        uVar1 = *(undefined8 *)(param_1 + 0xa8);
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar5 = FUN_186b63a70(uVar1,0,0);
        if (cVar5 != '\0') {
          if ((*(longlong *)(param_1 + 0xa8) == 0) ||
             (lVar8 = Torappu_Battle_Entity_get_spController_0x6010350
                                (*(longlong *)(param_1 + 0xa8),0), lVar8 == 0)) goto LAB_18095bdb7;
          SpController_MarkInvalid_0x60104b9(lVar8,0);
        }
      }
      uVar9 = 0;
      iVar6 = FUN_1844afc00(*(undefined8 *)(param_1 + 0xd8),_DAT_18896a750);
      if (0 < iVar6) {
        lVar8 = 0x20;
        uVar10 = uVar9;
        do {
          lVar2 = *(longlong *)(param_1 + 0xd8);
          if (lVar2 == 0) goto LAB_18095bdb7;
          if (*(uint *)(lVar2 + 0x18) <= (uint)uVar10) {
            FUN_18048c0a0();
            pcVar4 = (code *)swi(3);
            (*pcVar4)();
            return;
          }
          plVar3 = *(longlong **)(lVar8 + lVar2);
          if (plVar3 == (longlong *)0x0) goto LAB_18095bdb7;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar3);
          }
          (**(code **)(*plVar3 + 0x1a0))(plVar3,*(undefined8 *)(*plVar3 + 0x1a8));
          uVar10 = (ulonglong)((uint)uVar10 + 1);
          uVar9 = uVar9 + 1;
          lVar8 = lVar8 + 8;
        } while ((longlong)uVar9 < (longlong)iVar6);
      }
      if (DAT_188c91c3d == '\0') {
        FUN_18048bf00(&DAT_188925ba0);
        DAT_188c91c3d = '\x01';
      }
      lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
      if (lVar8 == 0) {
        lVar8 = *(longlong *)(param_1 + 0xa8);
      }
      else {
        lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar8,param_1,0);
      }
      if (lVar8 != 0) {
        Torappu_Battle_Character_OnSkillCastSucceed_0x601290e(lVar8,0);
        cVar5 = FUN_185337b70(_DAT_1888d36c8);
        if (cVar5 != '\0') {
          lVar8 = FUN_185337c50(_DAT_1888d3908);
          if ((lVar8 == 0) ||
             (lVar8 = Torappu_Battle_BattleController_get_eventPool_0x600fbf9(lVar8,0), lVar8 == 0))
          goto LAB_18095bdb7;
          FUN_1848dca60(lVar8,0x19,param_1,_DAT_188811960);
        }
        return;
      }
    }
LAB_18095bdb7:
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar8 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        iVar7 = FUN_183f22380(uVar1,1,0,iVar6,0);
        if (iVar7 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar1,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar8 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar6 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


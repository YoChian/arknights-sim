
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnBorn_0x6011be5(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  longlong lVar10;
  ulonglong uVar11;
  longlong lVar12;
  
  if (DAT_188c91c56 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_1888746f8);
    FUN_18048bf00(&DAT_18896a750);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91c56 = '\x01';
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x318);
  if (lVar10 == 0) {
    cVar5 = Torappu_Battle_BasicSkill_get_isUsedUp_0x6011bbd(param_1,0);
    if (cVar5 != '\0') {
      Torappu_Battle_BasicSkill_set_registeredAsModifier_0x6011bbf(param_1,1,0);
    }
    if (DAT_188c91c3d == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar10 != 0) {
      XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar10,param_1,0);
    }
    uVar9 = 0;
    iVar6 = FUN_1844afc00(*(undefined8 *)(param_1 + 0x50),_DAT_1888746f8);
    lVar10 = 0x20;
    if (0 < iVar6) {
      lVar12 = 0x20;
      uVar8 = uVar9;
      uVar11 = uVar9;
      do {
        lVar1 = *(longlong *)(param_1 + 0x50);
        if (lVar1 == 0) goto LAB_18095b862;
        if (*(uint *)(lVar1 + 0x18) <= (uint)uVar11) goto LAB_18095b85c;
        lVar1 = *(longlong *)(lVar12 + lVar1);
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar5 = FUN_186b63a70(lVar1,0,0);
        if (cVar5 != '\0') {
          if (lVar1 == 0) goto LAB_18095b862;
          Torappu_Battle_Ability_Attach_0x600f653(lVar1);
        }
        uVar11 = (ulonglong)((uint)uVar11 + 1);
        uVar8 = uVar8 + 1;
        lVar12 = lVar12 + 8;
      } while ((longlong)uVar8 < (longlong)iVar6);
    }
    iVar6 = FUN_1844afc00(*(undefined8 *)(param_1 + 0xd8),_DAT_18896a750);
    uVar8 = uVar9;
    if (0 < iVar6) {
      do {
        lVar12 = *(longlong *)(param_1 + 0xd8);
        if (lVar12 == 0) {
LAB_18095b862:
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        if (*(uint *)(lVar12 + 0x18) <= (uint)uVar8) {
LAB_18095b85c:
          FUN_18048c0a0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        plVar2 = *(longlong **)(lVar10 + lVar12);
        if (plVar2 == (longlong *)0x0) goto LAB_18095b862;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
        (**(code **)(*plVar2 + 0x210))(plVar2,*(undefined8 *)(*plVar2 + 0x218));
        uVar9 = uVar9 + 1;
        lVar10 = lVar10 + 8;
        uVar8 = (ulonglong)((uint)uVar8 + 1);
      } while ((longlong)uVar9 < (longlong)iVar6);
    }
    return;
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar10 + 0x18) != 0) {
    uVar3 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar12 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar12 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar12,uVar3,param_1,0);
        iVar7 = FUN_183f22380(uVar3,1,0,iVar6,0);
        if (iVar7 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar3,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar10 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar6 + -1,0);
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


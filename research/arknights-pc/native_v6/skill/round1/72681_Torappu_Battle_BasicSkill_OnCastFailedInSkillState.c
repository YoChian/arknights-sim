
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnCastFailedInSkillState_0x6011bea(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  uint uVar8;
  longlong lVar9;
  
  if (DAT_188c91c5b == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_18896a750);
    DAT_188c91c5b = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x340);
  if (lVar7 == 0) {
    uVar8 = 0;
    iVar5 = FUN_1844afc00(*(undefined8 *)(param_1 + 0xd8),_DAT_18896a750);
    if (0 < iVar5) {
      lVar7 = 0x20;
      lVar9 = 0;
      do {
        lVar1 = *(longlong *)(param_1 + 0xd8);
        if (lVar1 == 0) {
LAB_18095b984:
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        if (*(uint *)(lVar1 + 0x18) <= uVar8) {
          FUN_18048c0a0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        plVar2 = *(longlong **)(lVar7 + lVar1);
        if (plVar2 == (longlong *)0x0) goto LAB_18095b984;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
        (**(code **)(*plVar2 + 0x1b0))(plVar2,*(undefined8 *)(*plVar2 + 0x1b8));
        uVar8 = uVar8 + 1;
        lVar9 = lVar9 + 1;
        lVar7 = lVar7 + 8;
      } while (lVar9 < iVar5);
    }
    return;
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar3 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar9 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar9,uVar3,param_1,0);
        iVar6 = FUN_183f22380(uVar3,1,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar3,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
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


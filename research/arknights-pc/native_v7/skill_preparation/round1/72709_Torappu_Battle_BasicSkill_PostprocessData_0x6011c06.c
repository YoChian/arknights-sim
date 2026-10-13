
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_PostprocessData_0x6011c06(longlong param_1,undefined8 param_2)

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
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c91c77 == '\0') {
    uStack_40 = 0x18095d9b3;
    FUN_18048bf00(&DAT_188925ba0);
    uStack_40 = 0x18095d9bf;
    FUN_18048bf00(&DAT_18896a750);
    DAT_188c91c77 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x420);
  if (lVar7 == 0) {
    uVar8 = 0;
    uStack_40 = 0x18095da03;
    iVar5 = FUN_1844afc00(*(undefined8 *)(param_1 + 0xd8),_DAT_18896a750);
    if (0 < iVar5) {
      lVar7 = 0x20;
      lVar9 = 0;
      do {
        lVar1 = *(longlong *)(param_1 + 0xd8);
        if (lVar1 == 0) {
LAB_18095dac2:
          uStack_40 = 0x18095dac7;
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        if (*(uint *)(lVar1 + 0x18) <= uVar8) {
          uStack_40 = 0x18095dac1;
          FUN_18048c0a0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        plVar2 = *(longlong **)(lVar7 + lVar1);
        if (plVar2 == (longlong *)0x0) goto LAB_18095dac2;
        if (DAT_188ccc7f0 != '\0') {
          uStack_40 = 0x18095da5f;
          func_0x000180446d00(*plVar2);
        }
        uStack_40 = 0x18095da78;
        (**(code **)(*plVar2 + 0x1c0))(plVar2,param_2,*(undefined8 *)(*plVar2 + 0x1c8));
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
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
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
        FUN_183cf8c20(lVar9,uVar3,param_2,0);
        iVar6 = FUN_183f22380(uVar3,2,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar3,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
          goto code_r0x0001832d231b;
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


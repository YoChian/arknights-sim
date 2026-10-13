
/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_OnTick_0x600f6c4(longlong param_1,undefined8 param_2)

{
  longlong *plVar1;
  undefined8 uVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  longlong lVar9;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c8fd42 == '\0') {
    uStack_30 = 0x1805d2b05;
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd42 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x170);
  if (lVar6 == 0) {
    uStack_30 = 0x1805d2b47;
    Torappu_Battle_Ability_OnTick_0x600f674(param_1,param_2,0);
    lVar6 = *(longlong *)(param_1 + 0x100);
    uVar8 = 0;
    if (lVar6 != 0) {
      lVar9 = 0x20;
      do {
        if (*(int *)(lVar6 + 0x18) <= (int)uVar8) {
          return;
        }
        lVar6 = *(longlong *)(param_1 + 0x100);
        if (lVar6 == 0) break;
        if (*(uint *)(lVar6 + 0x18) <= uVar8) {
          uStack_30 = 0x1805d2c05;
          FUN_18048c0a0();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        plVar1 = *(longlong **)(lVar9 + lVar6);
        if (plVar1 == (longlong *)0x0) break;
        if (DAT_188ccc7f0 != '\0') {
          uStack_30 = 0x1805d2b99;
          func_0x000180446d00(*plVar1);
        }
        uStack_30 = 0x1805d2bb2;
        (**(code **)(*plVar1 + 0x210))(plVar1,param_2,*(undefined8 *)(*plVar1 + 0x218));
        lVar6 = *(longlong *)(param_1 + 0x100);
        uVar8 = uVar8 + 1;
        lVar9 = lVar9 + 8;
      } while (lVar6 != 0);
    }
    uStack_30 = 0x1805d2bff;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (cRam0000000188caf41c == '\0') {
    FUN_18048bf00(&DAT_18885a700,param_1,param_2,0);
    cRam0000000188caf41c = '\x01';
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar9 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar9,uVar2,param_1,0);
        auStack_40[0] = param_2;
        uVar7 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
        FUN_183cfbf40(lVar9,uVar2,uVar7,0);
        iVar5 = FUN_183f22380(uVar2,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833f996e:
          FUN_183f22fd0(uVar2,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001833f996e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


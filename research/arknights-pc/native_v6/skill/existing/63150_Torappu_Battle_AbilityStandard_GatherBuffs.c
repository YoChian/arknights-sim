
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_GatherBuffs_0x600f6af(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  uint uVar7;
  undefined8 *puVar8;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c8fd2f == '\0') {
    puStack_30 = (undefined1 *)0x1805d02c5;
    FUN_18048bf00(&DAT_188974cb0);
    puStack_30 = (undefined1 *)0x1805d02d1;
    FUN_18048bf00(&DAT_188813250);
    puStack_30 = (undefined1 *)0x1805d02dd;
    FUN_18048bf00(&DAT_18893e6e0);
    DAT_188c8fd2f = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0xd8);
  if (lVar5 == 0) {
    puStack_30 = (undefined1 *)0x1805d0315;
    Torappu_Battle_Ability_GatherBuffs_0x600f66f(param_1,param_2,0);
    puStack_30 = (undefined1 *)0x1805d031f;
    lVar5 = FUN_186b59d80(param_1,0);
    if (lVar5 != 0) {
      puStack_30 = (undefined1 *)0x1805d0337;
      lVar5 = FUN_18451c870(lVar5,_DAT_188813250);
      uVar7 = 0;
      if (lVar5 != 0) {
        puVar8 = (undefined8 *)(lVar5 + 0x20);
        while( true ) {
          if (*(int *)(lVar5 + 0x18) <= (int)uVar7) {
            return;
          }
          if (*(uint *)(lVar5 + 0x18) <= uVar7) break;
          puStack_30 = (undefined1 *)0x1805d0369;
          lVar6 = func_0x00018048b9f0(*puVar8,_DAT_18893e6e0);
          if (lVar6 != 0) {
            puStack_30 = (undefined1 *)0x1805d037c;
            FUN_1805cadc0(lVar6,param_2,0);
          }
          uVar7 = uVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        puStack_30 = (undefined1 *)0x1805d03b8;
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
    }
    puStack_30 = (undefined1 *)0x1805d03be;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar5 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar5 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0);
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      lVar6 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
      if (lVar6 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar6,uVar1,param_1,0);
        FUN_183cf8c20(lVar6,uVar1,param_2,0);
        iVar4 = FUN_183f22380(uVar1,2,0,iVar3,0);
        if (iVar4 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar1,iVar3 + -1,0);
          return;
        }
        if (*(longlong *)(lVar5 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar3 + -1,0);
          goto code_r0x0001832d231b;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}



/* WARNING: Removing unreachable block (ram,0x0001832f4d7e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_Abilities_EasyToStartAbility_get_postDelay_0x60166c6(longlong param_1)

{
  undefined8 uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 uStackX_20;
  longlong alStack_58 [3];
  undefined8 uStack_40;
  undefined1 *puStack_38;
  undefined8 *puStack_30;
  
  if (DAT_188c956f6 == '\0') {
    puStack_30 = (undefined8 *)0x180f0c31e;
    FUN_18048bf00(&DAT_188927d60);
    puStack_30 = (undefined8 *)0x180f0c32a;
    FUN_18048bf00(&DAT_18880dc70);
    puStack_30 = (undefined8 *)0x180f0c336;
    FUN_18048bf00(&DAT_18885a700);
    puStack_30 = (undefined8 *)0x180f0c342;
    FUN_18048bf00(&DAT_1888915d8);
    DAT_188c956f6 = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18880dc70 + 0xb8) + 8);
  if (lVar5 == 0) {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = (undefined8 *)0x180f0c383;
      func_0x00018048c140();
    }
    puStack_30 = (undefined8 *)0x180f0c38c;
    lVar5 = func_0x0001866fdac0(0,0);
    uVar1 = *(undefined8 *)(param_1 + 0x120);
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      puStack_30 = (undefined8 *)0x180f0c3ab;
      func_0x00018048c140();
    }
    puStack_30 = (undefined8 *)0x180f0c3b2;
    uVar6 = Torappu_Battle_BattleController_get_fixedPlayTime_0x600fbd5(0);
    puStack_30 = (undefined8 *)0x180f0c3c4;
    uVar6 = func_0x0001866fba10(uVar6,*(undefined8 *)(param_1 + 0x130),0);
    puStack_30 = (undefined8 *)0x180f0c3d2;
    lVar7 = func_0x0001866fba10(uVar1,uVar6,0);
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      puStack_30 = (undefined8 *)0x180f0c3ea;
      func_0x00018048c140();
    }
    if (cRam0000000188cc376e == '\0') {
      puStack_30 = (undefined8 *)&UNK_1866ff775;
      FUN_18048bf00(&DAT_18885a700,lVar7,0);
      cRam0000000188cc376e = '\x01';
    }
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = (undefined8 *)&UNK_1866ff791;
      func_0x00018048c140();
    }
    if (lVar5 <= lVar7) {
      lVar5 = lVar7;
    }
    return lVar5;
  }
  if (cRam0000000188cafb95 == '\0') {
    FUN_18048bf00(0x18883f608);
    cRam0000000188cafb95 = '\x01';
  }
  alStack_58[0] = 0;
  alStack_58[1] = 0;
  if (*(longlong *)(lVar5 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832f4dd5:
    FUN_18048c0b0();
code_r0x0001832f4ddb:
    FUN_18048c0b0();
  }
  else {
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
    uStack_40 = 0;
    puStack_38 = &stack0x00000008;
    puStack_30 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar5 + 0x18) == 0) goto code_r0x0001832f4de5;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0);
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      lVar7 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
      if (lVar7 == 0) goto code_r0x0001832f4dd5;
      FUN_183cf8c20(lVar7,uVar1,param_1,0);
      iVar4 = FUN_183f22380(uVar1,1,1,iVar3,0);
      if (iVar4 == 0) {
code_r0x0001832f4d3c:
        FUN_184565cb0(lVar7,uVar1,iVar3 + 1,alStack_58,uRam000000018883f608);
        FUN_183f22fd0(uVar1,iVar3 + -1,0);
        return alStack_58[0];
      }
      if (*(longlong *)(lVar5 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar3 + -1,0);
        goto code_r0x0001832f4d3c;
      }
      goto code_r0x0001832f4ddb;
    }
  }
  FUN_18048c0b0();
code_r0x0001832f4de5:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  lVar5 = (*pcVar2)();
  return lVar5;
}


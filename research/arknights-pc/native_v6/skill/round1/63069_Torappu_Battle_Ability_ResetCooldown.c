
/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_ResetCooldown_0x600f65e(longlong param_1,char param_2)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c8fcef == '\0') {
    puStack_30 = (undefined *)0x1805d6985;
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fcef = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x1a0);
  if (lVar1 == 0) {
    lVar1 = *(longlong *)(param_1 + 0x70);
    if (lVar1 == 0) {
      puStack_30 = (undefined *)0x1805d69e3;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    if (cRam0000000188ca0cfd == '\0') {
      puStack_30 = &UNK_181e04865;
      FUN_18048bf00(&DAT_18885a700,param_2,0);
      cRam0000000188ca0cfd = '\x01';
    }
    if (param_2 == '\0') {
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        puStack_30 = &UNK_181e0488c;
        func_0x00018048c140();
      }
      puStack_30 = &UNK_181e04895;
      uVar6 = func_0x0001866fdac0(0,0);
    }
    else {
      uVar6 = *(undefined8 *)(lVar1 + 0x10);
    }
    if (lVar1 == 0) {
      puStack_30 = &UNK_181e048ae;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    *(undefined8 *)(lVar1 + 0x18) = uVar6;
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar6 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar6,param_1,0);
        FUN_183f22430(uVar6,param_2,0);
        iVar5 = FUN_183f22380(uVar6,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833006e0:
          FUN_183f22fd0(uVar6,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar4 + -1,0);
          goto code_r0x0001833006e0;
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


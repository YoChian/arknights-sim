
/* WARNING: Removing unreachable block (ram,0x0001835d3bbd) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_Enemy_States_DisappearState__DoDisappear_0x6012bed(undefined8 param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 unaff_RSI;
  
  if (DAT_188c92978 == '\0') {
    FUN_18048bf00(&DAT_188884f30);
    FUN_18048bf00(&DAT_1888e7798);
    DAT_188c92978 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x50);
  if (lVar6 == 0) {
    lVar6 = func_0x00018045cfe0(_DAT_1888e7798);
    if (lVar6 == 0) {
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      lVar6 = (*pcVar3)();
      return lVar6;
    }
    func_0x00018050cf60(lVar6,0);
    *(undefined4 *)(lVar6 + 0x10) = 0;
    *(undefined8 *)(lVar6 + 0x20) = param_1;
    func_0x00018048b9e0(lVar6 + 0x20,param_1);
    return lVar6;
  }
  if (cRam0000000188caf33d == '\0') {
    FUN_18048bf00(0x18895e4b8);
    FUN_18048bf00(0x188959b58);
    FUN_18048bf00(0x188906850);
    cRam0000000188caf33d = '\x01';
  }
  lVar8 = 0;
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001835d3c14:
    FUN_18048ba10(lVar6,unaff_RSI);
code_r0x0001835d3c1f:
    FUN_18048c0b0();
code_r0x0001835d3c24:
    FUN_18048c0b0();
  }
  else {
    FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
    if (*(longlong *)(lVar6 + 0x18) == 0) goto code_r0x0001835d3c2e;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar2 != 0) {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        iVar5 = FUN_183f22380(uVar1,1,1,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001835d3b40:
          uVar7 = uRam000000018895e4b8;
          if (*(int *)(lRam0000000188906850 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar7 = FUN_185eded20(uVar7,0);
          lVar6 = FUN_183cf3ce0(lVar2,uVar1,iVar4 + 1,uVar7,0);
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          unaff_RSI = uRam0000000188959b58;
          if ((lVar6 == 0) || (lVar8 = func_0x00018048b9f0(lVar6,uRam0000000188959b58), lVar8 != 0))
          {
            return lVar8;
          }
          goto code_r0x0001835d3c14;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001835d3b40;
        }
        goto code_r0x0001835d3c1f;
      }
      goto code_r0x0001835d3c24;
    }
  }
  FUN_18048c0b0();
code_r0x0001835d3c2e:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  lVar6 = (*pcVar3)();
  return lVar6;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 Torappu_Battle_BasicTalent_get_talentKey_0x6011e4b(longlong param_1)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  if (DAT_188c91e14 == '\0') {
    FUN_18048bf00(&DAT_188925de0);
    DAT_188c91e14 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x80);
  if (lVar8 == 0) {
    if (DAT_188c91e15 == '\0') {
      FUN_18048bf00(&DAT_188925de0);
      DAT_188c91e15 = '\x01';
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x88);
    if (lVar8 == 0) {
      uVar7 = *(undefined8 *)(param_1 + 0x18);
    }
    else {
      uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp77_0x6000aad(lVar8,param_1,0);
    }
    cVar3 = func_0x000185db9d60(uVar7,0);
    if (cVar3 != '\0') {
      if (cRam0000000188cc7c64 == '\0') {
        FUN_18048bf00(&DAT_188932ce8,0);
        cRam0000000188cc7c64 = '\x01';
      }
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      if (pcRam0000000188cc7d10 == (code *)0x0) {
        pcRam0000000188cc7d10 = (code *)FUN_18048c110(&UNK_18711b078);
      }
                    /* WARNING: Could not recover jumptable at 0x000186b638c1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar7 = (*pcRam0000000188cc7d10)(param_1);
      return uVar7;
    }
    if (DAT_188c91e15 == '\0') {
      FUN_18048bf00(&DAT_188925de0);
      DAT_188c91e15 = '\x01';
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x88);
    if (lVar8 == 0) {
      return *(undefined8 *)(param_1 + 0x18);
    }
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x000183611ec6:
    FUN_18048c0b0();
code_r0x000183611ecc:
    FUN_18048c0b0();
  }
  else {
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    FUN_185ca7f50(uStackX_20,acStackX_8,0);
    if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x000183611ed6;
    uVar7 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar1 == 0) goto code_r0x000183611ec6;
      FUN_183cf8c20(lVar1,uVar7,param_1,0);
      iVar5 = FUN_183f22380(uVar7,1,1,iVar4,0);
      if (iVar5 == 0) {
code_r0x000183611e45:
        uVar6 = FUN_183f23540(uVar7,iVar4 + 1,0);
        FUN_183f22fd0(uVar7,iVar4 + -1,0);
        if (acStackX_8[0] != '\0') {
          func_0x000185ca7ff0(uStackX_20,0);
        }
        return uVar6;
      }
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar4 + -1,0);
        goto code_r0x000183611e45;
      }
      goto code_r0x000183611ecc;
    }
  }
  FUN_18048c0b0();
code_r0x000183611ed6:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  uVar7 = (*pcVar2)();
  return uVar7;
}

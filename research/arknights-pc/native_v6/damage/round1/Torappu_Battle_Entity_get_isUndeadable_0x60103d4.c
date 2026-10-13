/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong Torappu_Battle_Entity_get_isUndeadable_0x60103d4(undefined8 param_1)
{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ulonglong uVar8;
  longlong lVar9;
  ulonglong auStackX_8 [3];
  byte bStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  ulonglong *puStack_30;
  undefined8 *puStack_28;
  if (DAT_188c9086b == '\0') {
    puStack_30 = (ulonglong *)0x180706c9e;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c9086b = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (ulonglong *)0x180706cbd;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x4f0);
  if (lVar9 == 0) {
    puStack_30 = (ulonglong *)0x180706ce1;
    lVar9 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
    if (lVar9 == 0) {
      puStack_30 = (ulonglong *)0x180706d10;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      uVar8 = (*pcVar3)();
      return uVar8;
    }
    if (cRam0000000188c901a3 == '\0') {
      puStack_30 = (ulonglong *)&UNK_1806492a4;
      FUN_18048bf00(0x18886fb08,6,0);
      cRam0000000188c901a3 = '\x01';
    }
    puStack_30 = (ulonglong *)&UNK_1806492b9;
    uVar5 = func_0x0001844dc660(6,uRam000000018886fb08);
    lVar1 = *(longlong *)(lVar9 + 0x28);
    if (lVar1 != 0) {
      if (*(uint *)(lVar1 + 0x18) <= uVar5) {
code_r0x00018064935b:
        puStack_30 = (ulonglong *)&UNK_180649360;
        FUN_18048c0a0();
        pcVar3 = (code *)swi(3);
        uVar8 = (*pcVar3)();
        return uVar8;
      }
      if (*(short *)(lVar1 + 0x20 + (longlong)(int)uVar5 * 2) < 1) {
        lVar1 = *(longlong *)(lVar9 + 0x20);
        if (lVar1 == 0) goto code_r0x000180649355;
        if (*(uint *)(lVar1 + 0x18) <= uVar5) goto code_r0x00018064935b;
        if (0 < *(short *)(lVar1 + 0x20 + (longlong)(int)uVar5 * 2)) {
          return CONCAT71((int7)(int3)(uVar5 >> 8),1);
        }
      }
      lVar9 = *(longlong *)(lVar9 + 0x50);
      if (lVar9 != 0) {
        if (cRam0000000188c901b1 == '\0') {
          puStack_30 = (ulonglong *)&UNK_18064931d;
          FUN_18048bf00(0x18886fb08);
          cRam0000000188c901b1 = '\x01';
        }
        uVar8 = *(ulonglong *)(lVar9 + 0x28);
        puStack_30 = (ulonglong *)&UNK_180649336;
        bVar4 = func_0x0001844dc660(6,uRam000000018886fb08);
        return (ulonglong)(0 < (longlong)(uVar8 & 1L << (bVar4 & 0x3f)));
      }
    }
code_r0x000180649355:
    puStack_30 = (ulonglong *)&UNK_18064935a;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    uVar8 = (*pcVar3)();
    return uVar8;
  }
  bStackX_20 = 0;
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
    auStackX_8[0] = auStackX_8[0] & 0xffffffffffffff00;
    uStack_38 = 0;
    puStack_30 = auStackX_8;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],auStackX_8,0);
    if (*(longlong *)(lVar9 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar1 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar1,uVar2,param_1,0);
      iVar7 = FUN_183f22380(uVar2,1,1,iVar6,0);
      if (iVar7 == 0) {
code_r0x0001832b39f4:
        bVar4 = FUN_183f23100(uVar2,iVar6 + 1,0);
        FUN_183f22fd0(uVar2,iVar6 + -1,0);
        if ((char)auStackX_8[0] != '\0') {
          bStackX_20 = bVar4;
          func_0x000185ca7ff0(auStack_48[0],0);
        }
        return (ulonglong)bVar4;
      }
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar6 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  uVar8 = (*pcVar3)();
  return uVar8;
}

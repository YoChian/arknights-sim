
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_BasicSkill_DoStartSkill_0x6011bf1(longlong param_1)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong lVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  uint uVar10;
  bool bVar11;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c91c62 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c62 = '\x01';
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x378);
  if (lVar3 == 0) {
    if (*(longlong *)(param_1 + 0xe8) == 0) {
      return _DAT_188925ba0;
    }
    lVar3 = *(longlong *)(param_1 + 0xe8);
    uVar9 = (**(code **)(lVar3 + 0x18))(*(undefined8 *)(lVar3 + 0x40),*(undefined8 *)(lVar3 + 0x28))
    ;
    *(undefined8 *)(param_1 + 0xe8) = 0;
    if (iRam0000000188cccdd8 != 0) {
      uVar10 = (uint)(param_1 + 0xe8U >> 0xc);
      puVar1 = (ulonglong *)((ulonglong)((uVar10 & 0x1fffff) >> 6) * 8 + 0x188d15560);
      do {
        uVar2 = *puVar1;
        LOCK();
        uVar9 = *puVar1;
        bVar11 = uVar2 == uVar9;
        if (bVar11) {
          *puVar1 = uVar2 | 1L << (uVar10 & 0x3f);
          uVar9 = uVar2;
        }
        UNLOCK();
      } while (!bVar11);
    }
    return uVar9;
  }
  if (*(longlong *)(lVar3 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar6 = (code *)swi(3);
    uVar9 = (*pcVar6)();
    return uVar9;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar3 + 0x18) + 0x30);
  acStackX_8[0] = '\0';
  FUN_185ca7f50(uStackX_20,acStackX_8,0);
  if (*(longlong *)(lVar3 + 0x18) != 0) {
    uVar4 = *(undefined8 *)(*(longlong *)(lVar3 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar4,*(undefined4 *)(lVar3 + 0x38),*(undefined4 *)(lVar3 + 0x14),0);
    if (*(longlong *)(lVar3 + 0x18) != 0) {
      lVar5 = *(longlong *)(*(longlong *)(lVar3 + 0x18) + 0x20);
      if (lVar5 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar5,uVar4,param_1,0);
        iVar8 = FUN_183f22380(uVar4,1,0,iVar7,0);
        if (iVar8 == 0) {
code_r0x0001833100e8:
          uVar9 = FUN_183f22fd0(uVar4,iVar7 + -1,0);
          if (acStackX_8[0] != '\0') {
            uVar9 = func_0x000185ca7ff0(uStackX_20,0);
          }
          return uVar9;
        }
        if (*(longlong *)(lVar3 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar3 + 0x18),iVar7 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar6 = (code *)swi(3);
  uVar9 = (*pcVar6)();
  return uVar9;
}


/* WARNING: Possible PIC construction at 0x000180a8b651: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x000180a8b656) */
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong DeadState_OnExit_0x6012b7c(longlong param_1,undefined4 param_2)
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
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  if (DAT_188c9291a == '\0') {
    puStack_30 = (undefined1 *)0x180a8b5e4;
    FUN_18048bf00(&DAT_188884ab8);
    puStack_30 = (undefined1 *)0x180a8b5f0;
    FUN_18048bf00(&DAT_188957260);
    puStack_30 = (undefined1 *)0x180a8b5fc;
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c9291a = '\x01';
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_188884ab8 + 0xb8) + 8);
  if (lVar3 == 0) {
    puStack_30 = (undefined1 *)0x180a8b62b;
    func_0x00018050cf60(param_1,param_2,_DAT_188957260);
    puStack_30 = (undefined1 *)0x180a8b63a;
    uVar9 = FUN_18536e540(param_1,_DAT_188957b60);
    if (uVar9 != 0) {
      *(undefined8 *)(uVar9 + 0x3f8) = *(undefined8 *)(param_1 + 0x18);
      if (iRam0000000188cccdd8 != 0) {
        uVar10 = (uint)(uVar9 + 0x3f8 >> 0xc);
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
    puStack_30 = (undefined1 *)0x180a8b690;
    FUN_18048c0b0();
    pcVar6 = (code *)swi(3);
    uVar9 = (*pcVar6)();
    return uVar9;
  }
  if (*(longlong *)(lVar3 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar6 = (code *)swi(3);
    uVar9 = (*pcVar6)();
    return uVar9;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar3 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
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
        FUN_183f25080(uVar4,param_2,0);
        iVar8 = FUN_183f22380(uVar4,2,0,iVar7,0);
        if (iVar8 == 0) {
code_r0x0001834c0f1e:
          uVar9 = FUN_183f22fd0(uVar4,iVar7 + -1,0);
          return uVar9;
        }
        if (*(longlong *)(lVar3 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar3 + 0x18),iVar7 + -1,0);
          goto code_r0x0001834c0f1e;
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

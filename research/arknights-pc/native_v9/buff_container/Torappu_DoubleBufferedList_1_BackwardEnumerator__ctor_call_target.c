
/* WARNING: Possible PIC construction at 0x00018558e6e7: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x00018558e6ec) */

ulonglong Torappu_DoubleBufferedList_1_BackwardEnumerator__ctor_call_target
                    (longlong param_1,longlong param_2,undefined8 param_3,longlong param_4)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  code *pcVar3;
  longlong lVar4;
  ulonglong uVar5;
  uint uVar6;
  bool bVar7;
  
  func_0x00018050cf60(param_1,0);
  if (param_2 == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    uVar5 = (*pcVar3)();
    return uVar5;
  }
  lVar4 = *(longlong *)(*(longlong *)(*(longlong *)(param_4 + 0x20) + 0xc0) + 0x18);
  if ((*(byte *)(lVar4 + 0x136) & 1) == 0) {
    lVar4 = FUN_1804463f0(lVar4);
  }
  uVar5 = FUN_180005310(0,lVar4,param_2);
  *(int *)(param_1 + 0x18) = (int)uVar5;
  *(longlong *)(param_1 + 0x10) = param_2;
  if (iRam0000000188cccdd8 != 0) {
    uVar6 = (uint)(param_1 + 0x10U >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar6 & 0x1fffff) >> 6) * 8 + 0x188d15560);
    do {
      uVar2 = *puVar1;
      LOCK();
      uVar5 = *puVar1;
      bVar7 = uVar2 == uVar5;
      if (bVar7) {
        *puVar1 = uVar2 | 1L << (uVar6 & 0x3f);
        uVar5 = uVar2;
      }
      UNLOCK();
    } while (!bVar7);
  }
  return uVar5;
}


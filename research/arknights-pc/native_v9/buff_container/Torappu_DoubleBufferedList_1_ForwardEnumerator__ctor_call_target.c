
/* WARNING: Possible PIC construction at 0x000184916cd1: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x000184916cd6) */

ulonglong Torappu_DoubleBufferedList_1_ForwardEnumerator__ctor_call_target
                    (longlong param_1,undefined8 param_2)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar3 = func_0x00018050cf60(param_1,0);
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(undefined8 *)(param_1 + 0x10) = param_2;
  if (iRam0000000188cccdd8 != 0) {
    uVar4 = (uint)(param_1 + 0x10U >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar4 & 0x1fffff) >> 6) * 8 + 0x188d15560);
    do {
      uVar2 = *puVar1;
      LOCK();
      uVar3 = *puVar1;
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *puVar1 = uVar2 | 1L << (uVar4 & 0x3f);
        uVar3 = uVar2;
      }
      UNLOCK();
    } while (!bVar5);
  }
  return uVar3;
}


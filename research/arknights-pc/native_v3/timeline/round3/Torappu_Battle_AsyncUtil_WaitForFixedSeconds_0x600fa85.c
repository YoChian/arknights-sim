
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_AsyncUtil_WaitForFixedSeconds_0x600fa85(undefined8 param_1)

{
  code *pcVar1;
  longlong lVar2;
  
  if (DAT_188c90174 == '\0') {
    FUN_18048bf00(&DAT_188879728);
    DAT_188c90174 = '\x01';
  }
  lVar2 = func_0x00018045cfe0(_DAT_188879728);
  if (lVar2 != 0) {
    func_0x00018050cf60(lVar2,0);
    *(undefined8 *)(lVar2 + 0x20) = param_1;
    *(undefined4 *)(lVar2 + 0x10) = 0;
    return lVar2;
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  lVar2 = (*pcVar1)();
  return lVar2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_PeriodicTimer_get_isReady_0x600656f(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  longlong lVar3;
  
  if (DAT_188ca0cf9 == '\0') {
    FUN_18048bf00(&DAT_1888c3c38);
    DAT_188ca0cf9 = '\x01';
  }
  uVar1 = *(undefined8 *)(param_1 + 0x18);
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  if (cRam0000000188cc370d == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_1888915d8);
    cRam0000000188cc370d = '\x01';
  }
  if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar3 = FUN_1866fed50(uVar1,0);
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_1888c3c38);
  }
  lVar2 = **(longlong **)(_DAT_1888c3c38 + 0xb8);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  return lVar3 < lVar2;
}


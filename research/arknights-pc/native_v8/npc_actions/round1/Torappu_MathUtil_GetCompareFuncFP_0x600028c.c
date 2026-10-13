
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 Torappu_MathUtil_GetCompareFuncFP_0x600028c(int param_1)

{
  if (DAT_188cc3717 == '\0') {
    FUN_18048bf00(&DAT_1888c3c38);
    DAT_188cc3717 = '\x01';
  }
  if (param_1 == 0) {
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_1888c3c38);
    }
    return *(undefined8 *)(*(longlong *)(_DAT_1888c3c38 + 0xb8) + 0x10);
  }
  if (param_1 == 1) {
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_1888c3c38);
    }
    return *(undefined8 *)(*(longlong *)(_DAT_1888c3c38 + 0xb8) + 0x18);
  }
  if (param_1 != 2) {
    if (param_1 != 3) {
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_1888c3c38);
      }
      return *(undefined8 *)(*(longlong *)(_DAT_1888c3c38 + 0xb8) + 0x30);
    }
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_1888c3c38);
    }
    return *(undefined8 *)(*(longlong *)(_DAT_1888c3c38 + 0xb8) + 0x28);
  }
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_1888c3c38);
  }
  return *(undefined8 *)(*(longlong *)(_DAT_1888c3c38 + 0xb8) + 0x20);
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 Torappu_PeriodicTimer_Update_0x600657d(longlong param_1,undefined8 param_2,char param_3)

{
  undefined8 uVar1;
  char cVar2;
  undefined1 uVar3;
  undefined8 uVar4;
  
  if (DAT_188ca0d04 == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    DAT_188ca0d04 = '\x01';
  }
  uVar4 = *(undefined8 *)(param_1 + 0x18);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar4 = func_0x0001866fba10(uVar4,param_2,0);
  *(undefined8 *)(param_1 + 0x18) = uVar4;
  if (param_3 == '\0') {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar1 = func_0x0001866fdac0(0,0);
    cVar2 = func_0x000185ed91e0(uVar4,uVar1,0);
  }
  else {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar1 = func_0x0001866fdac0(0,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = Torappu_MathUtil_LE_0x6000277(uVar4,uVar1,0);
  }
  if (cVar2 == '\0') {
    uVar3 = 0;
  }
  else {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = func_0x0001866fdac0(0,0);
    *(undefined8 *)(param_1 + 0x18) = uVar4;
    uVar3 = 1;
  }
  return uVar3;
}


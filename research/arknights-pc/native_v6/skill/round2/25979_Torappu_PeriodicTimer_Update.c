
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 Torappu_PeriodicTimer_Update_0x600657c(longlong param_1,undefined8 param_2)

{
  undefined8 uVar1;
  char cVar2;
  undefined8 uVar3;
  
  if (DAT_188ca0d03 == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    DAT_188ca0d03 = '\x01';
  }
  uVar1 = *(undefined8 *)(param_1 + 0x18);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar3 = func_0x0001866fba10(uVar1,param_2,0);
  *(undefined8 *)(param_1 + 0x18) = uVar3;
  uVar1 = func_0x0001866fdac0(0,0);
  cVar2 = func_0x000185ed91e0(uVar3,uVar1,0);
  if (cVar2 == '\0') {
    return 0;
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar1 = func_0x0001866fdac0(0,0);
  *(undefined8 *)(param_1 + 0x18) = uVar1;
  return 1;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_PeriodicTimer_Reset_0x6006576(longlong param_1,undefined8 param_2,char param_3)

{
  undefined8 uVar1;
  bool bVar2;
  
  if (DAT_188ca0cfe == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888915d8);
    DAT_188ca0cfe = '\x01';
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar1 = func_0x0001866fdac0(0,0);
  if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar1 = Torappu_TSMath_Max_0x600033b(uVar1,param_2,0);
  bVar2 = DAT_188ca0cfd == '\0';
  *(undefined8 *)(param_1 + 0x10) = uVar1;
  if (bVar2) {
    FUN_18048bf00(&DAT_18885a700);
    DAT_188ca0cfd = '\x01';
  }
  if (param_3 == '\0') {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar1 = func_0x0001866fdac0(0,0);
  }
  else {
    uVar1 = *(undefined8 *)(param_1 + 0x10);
  }
  *(undefined8 *)(param_1 + 0x18) = uVar1;
  return;
}


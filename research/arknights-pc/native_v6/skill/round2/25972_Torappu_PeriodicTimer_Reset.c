
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_PeriodicTimer_Reset_0x6006575(longlong param_1,char param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  
  if (DAT_188ca0cfd == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    DAT_188ca0cfd = '\x01';
  }
  if (param_2 == '\0') {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar2 = func_0x0001866fdac0(0,0);
  }
  else {
    uVar2 = *(undefined8 *)(param_1 + 0x10);
  }
  if (param_1 != 0) {
    *(undefined8 *)(param_1 + 0x18) = uVar2;
    return;
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


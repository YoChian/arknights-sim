
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_StateMachine__CheckValidState_0x6008207(longlong param_1,int param_2)

{
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  byte extraout_var;
  ulonglong in_RAX;
  ulonglong uVar4;
  
  if (DAT_188ca7592 == '\0') {
    in_RAX = FUN_18048bf00(&DAT_1888fe780);
    DAT_188ca7592 = '\x01';
  }
  lVar3 = _DAT_1888fe780;
  if (param_2 < 1) {
    return in_RAX & 0xffffffffffffff00;
  }
  lVar1 = *(longlong *)(param_1 + 0x30);
  if (lVar1 != 0) {
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_1888fe780 + 0x20) + 0xc0) + 0xa8) + 0x20)
        == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(_DAT_1888fe780 + 0x20) + 0xc0) + 0xa8)
      )();
    }
    FUN_1857c7a00(lVar1,param_2,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(lVar3 + 0x20) + 0xc0) + 0xa8));
    return (ulonglong)(extraout_var >> 7) ^ 1;
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar4 = (*pcVar2)();
  return uVar4;
}


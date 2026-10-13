
undefined8 _OnWaitForPostDelay_d__17_MoveNext_0x60166e3(longlong param_1)

{
  longlong *plVar1;
  code *pcVar2;
  undefined8 uVar3;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 1) {
      *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    }
    return 0;
  }
  plVar1 = *(longlong **)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  if (plVar1 != (longlong *)0x0) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar1);
    }
    uVar3 = (**(code **)(*plVar1 + 0x790))(plVar1,*(undefined8 *)(*plVar1 + 0x798));
    uVar3 = Torappu_Battle_AsyncUtil_WaitForFixedSeconds_0x600fa85(uVar3,0);
    *(undefined8 *)(param_1 + 0x18) = uVar3;
    func_0x00018048b9e0(param_1 + 0x18,uVar3);
    *(undefined4 *)(param_1 + 0x10) = 1;
    return 1;
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar3 = (*pcVar2)();
  return uVar3;
}


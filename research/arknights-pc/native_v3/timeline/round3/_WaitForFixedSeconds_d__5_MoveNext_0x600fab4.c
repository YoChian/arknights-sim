
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong _WaitForFixedSeconds_d__5_MoveNext_0x600fab4(longlong param_1)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  
  if (DAT_188c9017e == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_18886a5d0);
    DAT_188c9017e = '\x01';
  }
  uVar1 = *(uint *)(param_1 + 0x10);
  if (uVar1 == 0) {
    uVar4 = *(undefined8 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = Torappu_Battle_BattleController_get_deltaPlayTime_0x600fc5c(0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar3 = func_0x0001866fdad0(uVar5,0);
    uVar4 = Torappu_FP_op_Division_0x6000305(uVar4,uVar3,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar2 = Torappu_MathUtil_RoundToInt_0x600027c(uVar4,0);
    if (iVar2 < 1) {
      iVar2 = 1;
    }
    *(int *)(param_1 + 0x28) = iVar2;
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  else {
    if (uVar1 != 1) goto LAB_1806615f8;
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + 1;
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  }
  uVar1 = *(uint *)(param_1 + 0x28);
  if (*(int *)(param_1 + 0x2c) < (int)uVar1) {
    if (*(int *)(_DAT_18886a5d0 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18886a5d0);
    }
    *(undefined8 *)(param_1 + 0x18) = **(undefined8 **)(_DAT_18886a5d0 + 0xb8);
    func_0x00018048b9e0(param_1 + 0x18);
    *(undefined4 *)(param_1 + 0x10) = 1;
    return 1;
  }
LAB_1806615f8:
  return (ulonglong)(uVar1 >> 8) << 8;
}


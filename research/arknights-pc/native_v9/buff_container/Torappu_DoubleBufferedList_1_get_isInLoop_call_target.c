
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 Torappu_DoubleBufferedList_1_get_isInLoop_call_target(longlong param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  
  if (DAT_188cbd831 == '\0') {
    FUN_18048bf00(&DAT_18892adb8);
    DAT_188cbd831 = '\x01';
  }
  lVar8 = **(longlong **)(*(longlong *)(param_2 + 0x20) + 0xc0);
  if ((*(byte *)(lVar8 + 0x136) & 1) == 0) {
    lVar8 = FUN_1804463f0(lVar8);
  }
  lVar3 = *(longlong *)(*(longlong *)(lVar8 + 0xb8) + 0x10);
  if (lVar3 == 0) {
    return CONCAT71((int7)((ulonglong)*(longlong *)(lVar8 + 0xb8) >> 8),
                    *(short *)(param_1 + 0x20) != 0);
  }
  XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar3,0);
  if (*(longlong *)(*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 8) + 0x20)
      == 0) {
    (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 8))();
  }
  FUN_1844c6730(lVar3,param_1,
                *(undefined8 *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 8));
  XLua_DelegateBridge_Invoke_0x6003c9e(lVar3,1,0);
  lVar8 = _DAT_18892adb8;
  if (*(longlong *)(_DAT_18892adb8 + 0x38) == 0) {
    FUN_180446470(_DAT_18892adb8);
  }
  if (*(longlong *)(lVar3 + 0x18) == 0) {
    FUN_18048c0b0();
  }
  else {
    uVar6 = FUN_183e0e550(*(longlong *)(lVar3 + 0x18),0);
    iVar5 = FUN_183f21da0(uVar6,0);
    if (iVar5 < *(int *)(lVar3 + 0x40) + 2) {
      XLua_DelegateBridge_InvokeSessionEnd_0x6003c9f(lVar3,0);
      uVar6 = func_0x00018048bf20(0x1888506e8);
      uVar6 = func_0x00018045cfe0(uVar6);
      FUN_180005cb0(uVar6);
      uVar7 = func_0x00018048bf20(0x18887bcf0);
      FUN_185eb96e0(uVar6,uVar7,0);
      FUN_18048c070(uVar6,lVar8);
      pcVar4 = (code *)swi(3);
      uVar6 = (*pcVar4)();
      return uVar6;
    }
    lVar1 = *(longlong *)(lVar3 + 0x18);
    if (lVar1 == 0) goto code_r0x0001844c7ce7;
    lVar2 = *(longlong *)(lVar1 + 0x20);
    uVar6 = FUN_183e0e550(lVar1,0);
    iVar5 = *(int *)(lVar3 + 0x40);
    if (lVar2 != 0) {
      if (((undefined8 *)**(longlong **)(lVar8 + 0x38))[4] == 0) {
        (**(code **)**(longlong **)(lVar8 + 0x38))();
      }
      FUN_1845670a0(lVar2,uVar6,iVar5 + 2,&stack0x00000010,**(undefined8 **)(lVar8 + 0x38));
      XLua_DelegateBridge_InvokeSessionEnd_0x6003c9f(lVar3,0);
      return 0;
    }
  }
  FUN_18048c0b0();
code_r0x0001844c7ce7:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  uVar6 = (*pcVar4)();
  return uVar6;
}


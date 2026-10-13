
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Blackboard_GetIntOrDefault_0x6007874
                    (undefined8 param_1,undefined8 param_2,ulonglong param_3,undefined1 param_4)

{
  longlong lVar1;
  char cVar2;
  ulonglong uVar3;
  uint auStack_18 [4];
  
  if (DAT_188ca4fa4 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    DAT_188ca4fa4 = '\x01';
  }
  auStack_18[0] = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x100);
  if (lVar1 == 0) {
    cVar2 = Torappu_Blackboard_TryGetInt_0x600786b(param_1,param_2,auStack_18,0);
    uVar3 = (ulonglong)auStack_18[0];
    if (cVar2 == '\0') {
      uVar3 = param_3 & 0xffffffff;
    }
  }
  else {
    uVar3 = XLua_DelegateBridge___Gen_Delegate_Imp941_0x6000e0d
                      (lVar1,param_1,param_2,param_3 & 0xffffffff,param_4,0);
  }
  return uVar3;
}


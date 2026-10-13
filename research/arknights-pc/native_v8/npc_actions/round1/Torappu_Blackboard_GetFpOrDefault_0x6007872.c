
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Blackboard_GetFpOrDefault_0x6007872
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined1 param_4)

{
  longlong lVar1;
  undefined4 uVar2;
  char cVar3;
  undefined4 auStack_28 [2];
  undefined8 auStack_20 [3];
  
  if (DAT_188ca4fa2 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    DAT_188ca4fa2 = '\x01';
  }
  auStack_20[0] = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0xf0);
  if (lVar1 == 0) {
    if (DAT_188ca4f9c == '\0') {
      FUN_18048bf00(&DAT_188941920);
      FUN_18048bf00(&DAT_18885a700);
      DAT_188ca4f9c = '\x01';
    }
    auStack_28[0] = 0;
    lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0xb0);
    if (lVar1 == 0) {
      cVar3 = Torappu_Blackboard__TryGetNumber_0x6007880(param_1,param_2,auStack_28,0);
      uVar2 = auStack_28[0];
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      auStack_20[0] = func_0x0001866fdad0(uVar2,0);
    }
    else {
      cVar3 = XLua_DelegateBridge___Gen_Delegate_Imp936_0x6000e08
                        (lVar1,param_1,param_2,auStack_20,0);
    }
    if (cVar3 == '\0') {
      auStack_20[0] = param_3;
    }
  }
  else {
    auStack_20[0] =
         XLua_DelegateBridge___Gen_Delegate_Imp939_0x6000e0b
                   (lVar1,param_1,param_2,param_3,param_4,0);
  }
  return auStack_20[0];
}


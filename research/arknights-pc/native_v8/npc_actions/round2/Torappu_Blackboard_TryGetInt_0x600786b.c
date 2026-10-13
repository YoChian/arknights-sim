
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Blackboard_TryGetInt_0x600786b(undefined8 param_1,undefined8 param_2,int *param_3)

{
  longlong lVar1;
  float fVar2;
  undefined8 uVar3;
  double dVar4;
  float afStack_28 [8];
  
  if (DAT_188ca4f9d == '\0') {
    FUN_18048bf00(&DAT_188941920);
    DAT_188ca4f9d = '\x01';
  }
  afStack_28[0] = 0.0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0xb8);
  if (lVar1 == 0) {
    uVar3 = Torappu_Blackboard__TryGetNumber_0x6007880(param_1,param_2,afStack_28,0);
    fVar2 = afStack_28[0];
    if ((char)uVar3 == '\0') {
      *param_3 = 0;
      return uVar3;
    }
    if (DAT_188c8f78e == '\0') {
      FUN_18048bf00(&DAT_1888c37c0);
      DAT_188c8f78e = '\x01';
    }
    if (*(int *)(_DAT_1888c37c0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    dVar4 = (double)func_0x0001804d3200((double)fVar2);
    *param_3 = (int)dVar4;
    return CONCAT71((uint7)(uint3)((uint)(int)dVar4 >> 8),1);
  }
  uVar3 = XLua_DelegateBridge___Gen_Delegate_Imp845_0x6000dad(lVar1,param_1,param_2,param_3,0);
  return uVar3;
}


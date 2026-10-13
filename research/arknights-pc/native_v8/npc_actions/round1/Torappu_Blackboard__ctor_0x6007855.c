
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard__ctor_0x6007855(undefined8 param_1,undefined8 param_2)

{
  longlong lVar1;
  
  if (DAT_188ca4f87 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_1888610f0);
    FUN_18048bf00(&DAT_188860c88);
    FUN_18048bf00(&DAT_188932198);
    DAT_188ca4f87 = '\x01';
  }
  if (*(int *)(_DAT_188932198 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  FUN_1848f2320(param_1,_DAT_188860c88);
  FUN_184e36fe0(param_1,param_2,_DAT_1888610f0);
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 8);
  if (lVar1 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar1,param_1,param_2,0);
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Blackboard__TryGetNumber_0x6007880(longlong param_1,undefined8 param_2,undefined4 *param_3)

{
  longlong lVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  undefined8 uStack_38;
  undefined4 uStack_30;
  undefined8 uStack_28;
  
  if (DAT_188ca4fb0 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(0x188861e28);
    FUN_18048bf00(&DAT_188862058);
    DAT_188ca4fb0 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x160);
  if (lVar1 == 0) {
    cVar2 = func_0x000185db9d60(param_2,0);
    if (cVar2 != '\0') {
      *param_3 = 0;
      return 0;
    }
    iVar5 = 0;
    if (0 < *(int *)(param_1 + 0x18)) {
      do {
        FUN_184ad2e80(&uStack_38,param_1,iVar5,_DAT_188862058);
        iVar3 = func_0x000185db2fa0(uStack_38,param_2,1,0);
        if (iVar3 == 0) {
          FUN_184ad2e80(&uStack_38,param_1,iVar5,_DAT_188862058);
          cVar2 = func_0x000185db9d60(uStack_28,0);
          if (cVar2 != '\0') {
            FUN_184ad2e80(&uStack_38,param_1,iVar5,_DAT_188862058);
            *param_3 = uStack_30;
            return 1;
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < *(int *)(param_1 + 0x18));
    }
    *param_3 = 0;
    return 0;
  }
  uVar4 = XLua_DelegateBridge___Gen_Delegate_Imp233_0x6000b49(lVar1,param_1,param_2,param_3,0);
  return uVar4;
}


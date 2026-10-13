
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Blackboard_TryGetInternalData_0x600786f
          (longlong param_1,undefined8 param_2,undefined8 *param_3)

{
  longlong lVar1;
  int iVar2;
  undefined8 uVar3;
  int iVar4;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (DAT_188ca4fa0 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(0x188861e28);
    FUN_18048bf00(&DAT_188862058);
    DAT_188ca4fa0 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0xd8);
  iVar4 = 0;
  if (lVar1 == 0) {
    if (0 < *(int *)(param_1 + 0x18)) {
      do {
        FUN_184ad2e80(&uStack_38,param_1,iVar4,_DAT_188862058);
        iVar2 = func_0x000185db2fa0(CONCAT44(uStack_34,uStack_38),param_2,1,0);
        if (iVar2 == 0) {
          FUN_184ad2e80(&uStack_38,param_1,iVar4,_DAT_188862058);
          *(undefined4 *)param_3 = uStack_38;
          *(undefined4 *)((longlong)param_3 + 4) = uStack_34;
          *(undefined4 *)(param_3 + 1) = uStack_30;
          *(undefined4 *)((longlong)param_3 + 0xc) = uStack_2c;
          param_3[2] = uStack_28;
          func_0x00018048b9e0(param_3,0);
          return 1;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 0x18));
    }
    uVar3 = 0;
    *param_3 = 0;
    param_3[1] = 0;
    param_3[2] = 0;
  }
  else {
    uVar3 = XLua_DelegateBridge___Gen_Delegate_Imp937_0x6000e09(lVar1,param_1,param_2,param_3,0);
  }
  return uVar3;
}


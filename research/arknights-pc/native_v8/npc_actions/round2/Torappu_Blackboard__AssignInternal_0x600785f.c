
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard__AssignInternal_0x600785f(longlong param_1,undefined8 *param_2)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  
  if (DAT_188ca4f91 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_188860eb8);
    FUN_18048bf00(0x188861e28);
    FUN_18048bf00(&DAT_188862058);
    FUN_18048bf00(&DAT_188862290);
    DAT_188ca4f91 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x58);
  if (lVar1 != 0) {
    uStack_48 = *(undefined4 *)param_2;
    uStack_44 = *(undefined4 *)((longlong)param_2 + 4);
    uStack_40 = *(undefined4 *)(param_2 + 1);
    uStack_3c = *(undefined4 *)((longlong)param_2 + 0xc);
    uStack_38 = param_2[2];
    XLua_DelegateBridge___Gen_Delegate_Imp930_0x6000e02(lVar1,param_1,&uStack_48,0);
    return;
  }
  iVar3 = 0;
  if (0 < *(int *)(param_1 + 0x18)) {
    do {
      FUN_184ad2e80(&uStack_48,param_1,iVar3,_DAT_188862058);
      iVar2 = func_0x000185db2fa0(CONCAT44(uStack_44,uStack_48),*param_2,1,0);
      if (iVar2 == 0) {
        uStack_48 = *(undefined4 *)param_2;
        uStack_44 = *(undefined4 *)((longlong)param_2 + 4);
        uStack_40 = *(undefined4 *)(param_2 + 1);
        uStack_3c = *(undefined4 *)((longlong)param_2 + 0xc);
        uStack_38 = param_2[2];
        FUN_184ad3170(param_1,iVar3,&uStack_48,_DAT_188862290);
        return;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(param_1 + 0x18));
  }
  uStack_48 = *(undefined4 *)param_2;
  uStack_44 = *(undefined4 *)((longlong)param_2 + 4);
  uStack_40 = *(undefined4 *)(param_2 + 1);
  uStack_3c = *(undefined4 *)((longlong)param_2 + 0xc);
  uStack_38 = param_2[2];
  FUN_180012b80(param_1,&uStack_48,_DAT_188860eb8);
  return;
}


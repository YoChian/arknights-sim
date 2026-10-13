
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard_Assign_0x600785d(longlong param_1,longlong param_2,undefined8 param_3)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 auStack_58 [2];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  
  if (DAT_188ca4f8f == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_188860eb8);
    FUN_18048bf00(0x188861e28);
    FUN_18048bf00(&DAT_188862058);
    FUN_18048bf00(&DAT_188862290);
    DAT_188ca4f8f = '\x01';
  }
  uStack_60 = 0;
  auStack_58[0] = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x48);
  if (lVar1 == 0) {
    if (param_2 == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_68 = System_String_ToLower_0x6000343(param_2,0);
    func_0x00018048b9e0(&uStack_68,uStack_68);
    uStack_60 = uStack_60 & 0xffffffff00000000;
    auStack_58[0] = param_3;
    func_0x00018048b9e0(auStack_58,param_3);
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 0x18)) {
      do {
        FUN_184ad2e80(&uStack_48,param_1,iVar4,_DAT_188862058);
        iVar3 = func_0x000185db2fa0(CONCAT44(uStack_44,uStack_48),param_2,1,0);
        if (iVar3 == 0) {
          uStack_48 = (undefined4)uStack_68;
          uStack_44 = uStack_68._4_4_;
          uStack_40 = (undefined4)uStack_60;
          uStack_3c = uStack_60._4_4_;
          uStack_38 = auStack_58[0];
          FUN_184ad3170(param_1,iVar4,&uStack_48,_DAT_188862290);
          return;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 0x18));
    }
    uStack_48 = (undefined4)uStack_68;
    uStack_44 = uStack_68._4_4_;
    uStack_40 = (undefined4)uStack_60;
    uStack_3c = uStack_60._4_4_;
    uStack_38 = auStack_58[0];
    FUN_180012b80(param_1,&uStack_48,_DAT_188860eb8);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar1,param_1,param_2,param_3,0);
  }
  return;
}


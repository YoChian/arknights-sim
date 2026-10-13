
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard_Assign_0x600785a(longlong param_1,longlong param_2,undefined4 param_3)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 auStack_68 [2];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  
  if (DAT_188ca4f8c == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_188860eb8);
    FUN_18048bf00(0x188861e28);
    FUN_18048bf00(&DAT_188862058);
    FUN_18048bf00(&DAT_188862290);
    DAT_188ca4f8c = '\x01';
  }
  uStack_70 = 0;
  auStack_68[0] = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x30);
  if (lVar1 == 0) {
    if (param_2 == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_78 = System_String_ToLower_0x6000343(param_2,0);
    func_0x00018048b9e0(&uStack_78,uStack_78);
    iVar4 = 0;
    uStack_70 = CONCAT44(uStack_70._4_4_,param_3);
    auStack_68[0] = 0;
    func_0x00018048b9e0(auStack_68,0);
    if (0 < *(int *)(param_1 + 0x18)) {
      do {
        FUN_184ad2e80(&uStack_58,param_1,iVar4,_DAT_188862058);
        iVar3 = func_0x000185db2fa0(CONCAT44(uStack_54,uStack_58),param_2,1,0);
        if (iVar3 == 0) {
          uStack_58 = (undefined4)uStack_78;
          uStack_54 = uStack_78._4_4_;
          uStack_50 = (undefined4)uStack_70;
          uStack_4c = uStack_70._4_4_;
          uStack_48 = auStack_68[0];
          FUN_184ad3170(param_1,iVar4,&uStack_58,_DAT_188862290);
          return;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 0x18));
    }
    uStack_58 = (undefined4)uStack_78;
    uStack_54 = uStack_78._4_4_;
    uStack_50 = (undefined4)uStack_70;
    uStack_4c = uStack_70._4_4_;
    uStack_48 = auStack_68[0];
    FUN_180012b80(param_1,&uStack_58,_DAT_188860eb8);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp34_0x6000a82(lVar1,param_1,param_2,param_3,0);
  }
  return;
}


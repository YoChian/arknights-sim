
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_BasicSkill_GetValue_0x6011bed
                    (undefined8 param_1,undefined4 param_2,ulonglong *param_3,ulonglong *param_4,
                    ulonglong *param_5,ulonglong *param_6)

{
  longlong lVar1;
  ulonglong uVar2;
  
  if (DAT_188c91c5e == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_18885a700);
    DAT_188c91c5e = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x358);
  if (lVar1 == 0) {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar2 = func_0x0001866fdac0(0,0);
    *param_6 = uVar2;
    *param_5 = uVar2;
    *param_4 = uVar2;
    *param_3 = uVar2;
    uVar2 = uVar2 & 0xffffffffffffff00;
  }
  else {
    uVar2 = XLua_DelegateBridge___Gen_Delegate_Imp2925_0x60015cd
                      (lVar1,param_1,param_2,param_3,param_4,param_5,param_6,0);
  }
  return uVar2;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_AbilityStandard_UpdatePlaybackSpeed_0x600f6cc
                    (undefined8 param_1,undefined4 param_2,undefined4 *param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  
  if (DAT_188c8fd4a == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd4a = '\x01';
  }
  uVar2 = _DAT_188974cb0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x1b0);
  if (lVar1 == 0) {
    *param_3 = 0x3f800000;
    return uVar2 & 0xffffffffffffff00;
  }
  uVar2 = XLua_DelegateBridge___Gen_Delegate_Imp2655_0x60014bf(lVar1,param_1,param_2,param_3,0);
  return uVar2;
}


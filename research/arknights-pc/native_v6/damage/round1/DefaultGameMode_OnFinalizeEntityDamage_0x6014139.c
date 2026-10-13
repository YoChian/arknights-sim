/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void DefaultGameMode_OnFinalizeEntityDamage_0x6014139
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)
{
  longlong lVar1;
  if (DAT_188c93a04 == '\0') {
    FUN_18048bf00(&DAT_1888a8d10);
    DAT_188c93a04 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888a8d10 + 0xb8) + 0x2f0);
  if (lVar1 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp3877_0x6001985(lVar1,param_1,param_2,param_3,0);
  }
  return;
}

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void DefaultGameMode_OnApplyingGlobalModifier_0x6014119(undefined8 param_1,undefined8 param_2)
{
  longlong lVar1;
  if (DAT_188c939e4 == '\0') {
    FUN_18048bf00(&DAT_1888a8d10);
    DAT_188c939e4 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888a8d10 + 0xb8) + 0x1f0);
  if (lVar1 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar1,param_1,param_2,0);
  }
  return;
}

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
DefaultGameMode_OnEntityApplyModifier_0x6014138
          (undefined8 param_1,undefined8 param_2,undefined8 param_3)
{
  longlong lVar1;
  undefined8 uVar2;
  if (DAT_188c93a03 == '\0') {
    FUN_18048bf00(&DAT_1888a8d10);
    DAT_188c93a03 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888a8d10 + 0xb8) + 0x2e8);
  if (lVar1 == 0) {
    return 1;
  }
  uVar2 = XLua_DelegateBridge___Gen_Delegate_Imp3174_0x60016c6(lVar1,param_1,param_2,param_3,0);
  return uVar2;
}

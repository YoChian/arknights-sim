
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_AbilityStandard_CheckActiveBuffs_0x600f6c5
          (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  longlong lVar1;
  undefined8 uVar2;
  
  if (DAT_188c8fd43 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd43 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x178);
  if (lVar1 == 0) {
    return 1;
  }
  uVar2 = XLua_DelegateBridge___Gen_Delegate_Imp252_0x6000b5c(lVar1,param_1,param_2,param_3,0);
  return uVar2;
}


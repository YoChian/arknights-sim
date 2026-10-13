
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_Attach_0x600f653(longlong *param_1,undefined8 param_2)

{
  longlong lVar1;
  char cVar2;
  
  if (DAT_188c8fce7 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fce7 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x160);
  if (lVar1 == 0) {
    if (DAT_188c8fcd5 == '\0') {
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcd5 = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xd0);
    if (lVar1 == 0) {
      cVar2 = (char)param_1[0x12];
    }
    else {
      cVar2 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
    }
    if (cVar2 == '\0') {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
                    /* WARNING: Could not recover jumptable at 0x0001805d4ba8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 800))(param_1,param_2,*(undefined8 *)(*param_1 + 0x328));
      return;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar1,param_1,param_2,0);
  }
  return;
}


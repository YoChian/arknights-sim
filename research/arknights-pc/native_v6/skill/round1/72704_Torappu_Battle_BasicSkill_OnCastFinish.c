
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnCastFinish_0x6011c01
               (longlong *param_1,undefined8 param_2,undefined4 param_3,undefined1 param_4)

{
  longlong lVar1;
  char cVar2;
  
  if (DAT_188c91c72 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c72 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x3f8);
  if (lVar1 == 0) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar2 = (**(code **)(*param_1 + 0x2e0))(param_1,*(undefined8 *)(*param_1 + 0x2e8));
    if (cVar2 == '\0') {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      (**(code **)(*param_1 + 0x490))(param_1,*(undefined8 *)(*param_1 + 0x498));
    }
    else {
      *(undefined1 *)(param_1 + 0x13) = 1;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp3021_0x600162d(lVar1,param_1,param_2,param_3,param_4,0);
  }
  return;
}


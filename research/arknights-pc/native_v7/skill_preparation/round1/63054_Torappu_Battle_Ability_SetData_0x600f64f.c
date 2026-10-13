
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_SetData_0x600f64f
               (longlong *param_1,undefined8 param_2,undefined4 *param_3)

{
  longlong lVar1;
  undefined4 uVar2;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c8fce3 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    FUN_18048bf00(&DAT_188927d60);
    DAT_188c8fce3 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x140);
  if (lVar1 == 0) {
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar2 = Torappu_Battle_BattleController_GenNextUniqueId_0x600fbd9(0);
    if (DAT_188c8fcbf == '\0') {
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcbf = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x20);
    if (lVar1 == 0) {
      *(undefined4 *)(param_1 + 0x10) = uVar2;
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp1021_0x6000e5d(lVar1,param_1,uVar2,0);
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uStack_28 = *param_3;
    uStack_24 = param_3[1];
    uStack_20 = param_3[2];
    uStack_1c = param_3[3];
    uStack_18 = param_3[4];
    uStack_14 = param_3[5];
    uStack_10 = param_3[6];
    uStack_c = param_3[7];
    (**(code **)(*param_1 + 0x2f0))(param_1,param_2,&uStack_28,*(undefined8 *)(*param_1 + 0x2f8));
    return;
  }
  uStack_28 = *param_3;
  uStack_24 = param_3[1];
  uStack_20 = param_3[2];
  uStack_1c = param_3[3];
  uStack_18 = param_3[4];
  uStack_14 = param_3[5];
  uStack_10 = param_3[6];
  uStack_c = param_3[7];
  XLua_DelegateBridge___Gen_Delegate_Imp2626_0x60014a2(lVar1,param_1,param_2,&uStack_28,0);
  return;
}


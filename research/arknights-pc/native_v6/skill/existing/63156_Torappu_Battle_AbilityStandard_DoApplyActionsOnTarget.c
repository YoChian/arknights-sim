
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_DoApplyActionsOnTarget_0x600f6b5
               (longlong param_1,undefined8 param_2,undefined8 param_3)

{
  longlong lVar1;
  undefined8 uVar2;
  undefined1 auStack_f8 [240];
  
  if (DAT_188c8fd35 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd35 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x108);
  if (lVar1 == 0) {
    if (DAT_188c8fcc1 == '\0') {
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcc1 = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x30);
    if (lVar1 == 0) {
      uVar2 = *(undefined8 *)(param_1 + 0x88);
    }
    else {
      uVar2 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar1,param_1,0);
    }
    Torappu_Battle_Action_ActionUtil_RunActions_0x6018902(auStack_f8,param_3,2,uVar2,0);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar1,param_1,param_2,param_3,0);
  }
  return;
}


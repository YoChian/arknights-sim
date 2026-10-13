
/* WARNING: Removing unreachable block (ram,0x000181e04871) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_EasyToStartAbility_OnCastEnd_0x60166c8
               (longlong param_1,undefined4 param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  
  if (DAT_188c956f8 == '\0') {
    FUN_18048bf00(&DAT_18880dc70);
    DAT_188c956f8 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18880dc70 + 0xb8) + 0x18);
  if (lVar1 == 0) {
    Torappu_Battle_AbilityStandard_OnCastEnd_0x600f6bc(param_1,param_2,0);
    cVar3 = Torappu_Battle_Abilities_EasyToStartAbility__CheckNeedResetCooldown_0x60166cd(param_1);
    if (cVar3 != '\0') {
      lVar1 = *(longlong *)(param_1 + 0x70);
      if (lVar1 == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      if (cRam0000000188ca0cfd == '\0') {
        FUN_18048bf00(&DAT_18885a700,0,0);
        cRam0000000188ca0cfd = '\x01';
      }
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar4 = func_0x0001866fdac0(0,0);
      if (lVar1 == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      *(undefined8 *)(lVar1 + 0x18) = uVar4;
      return;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp2640_0x60014b0(lVar1,param_1,param_2,0);
  }
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_AbstractAnimatedAbility_ApplyAttackTime_0x6016689
               (longlong param_1,undefined8 param_2)

{
  longlong lVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined8 auStackX_10 [3];
  
  auStackX_10[0] = param_2;
  if (DAT_188c956ce == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    FUN_18048bf00(&DAT_18885a700);
    DAT_188c956ce = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0xa8);
  if (lVar1 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b(lVar1,param_1,auStackX_10[0],0);
    return;
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar3 = Torappu_FP_AsFloat_0x6000323(auStackX_10,0);
  *(undefined4 *)(param_1 + 0x178) = uVar3;
  *(undefined8 *)(param_1 + 0x1b0) = auStackX_10[0];
  if (*(longlong *)(param_1 + 0x70) != 0) {
    Torappu_PeriodicTimer_ResetButKeepProgress_0x6006578
              (*(longlong *)(param_1 + 0x70),auStackX_10[0],0);
    Torappu_Battle_AbilityStandard_DoUpdatePlaybackSpeed_0x600f6cb(param_1,0,0);
    return;
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


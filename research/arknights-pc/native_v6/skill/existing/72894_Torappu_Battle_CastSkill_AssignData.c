
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_CastSkill_AssignData_0x6011cbf
               (longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 *param_5)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c91d0a == '\0') {
    FUN_18048bf00(&DAT_188855d90);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91d0a = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0x98);
  uStack_18 = *param_5;
  uStack_14 = param_5[1];
  uStack_10 = param_5[2];
  uStack_c = param_5[3];
  if (lVar1 == 0) {
    Torappu_Battle_BasicSkill_AssignData_0x6011bd7(param_1,param_2,param_3,param_4,&uStack_18,0);
    uVar5 = *(undefined8 *)(param_1 + 0x120);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar4 = FUN_186b63a70(uVar5,0,0);
    if (cVar4 != '\0') {
      plVar2 = *(longlong **)(param_1 + 0x120);
      uVar5 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
      if (plVar2 == (longlong *)0x0) {
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar2);
      }
      (**(code **)(*plVar2 + 0x1f0))(plVar2,uVar5,*(undefined8 *)(*plVar2 + 0x1f8));
    }
    *(undefined1 *)(param_1 + 0x145) = *(undefined1 *)(param_1 + 0x131);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp3539_0x6001833
              (lVar1,param_1,param_2,param_3,param_4,&uStack_18,0);
  }
  return;
}


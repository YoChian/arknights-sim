/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
FinishBuffsById_Execute_0x601775e
          (longlong param_1,longlong param_2,undefined4 param_3,longlong param_4)
{
  code *pcVar1;
  char cVar2;
  undefined4 uVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  if (DAT_188c9641f == '\0') {
    FUN_18048bf00(&DAT_188877078);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188805040);
    FUN_18048bf00(&DAT_188848398);
    DAT_188c9641f = '\x01';
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188877078 + 0xb8) + 0x18);
  if (lVar4 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar4,param_1,param_2,param_3,param_4,0);
    return uVar5;
  }
  lVar4 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x1c),0);
  uVar5 = *(undefined8 *)(param_1 + 0x10);
  uVar6 = 0;
  if (*(char *)(param_1 + 0x18) != '\0') {
    if (param_2 == 0) goto LAB_18102a6d2;
    uVar5 = Torappu_Blackboard_GetStringOrDefault_0x6007875(param_2,_DAT_188848398,uVar5,1,0);
  }
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = FUN_186b638d0(lVar4,0,0);
  if (cVar2 == '\0') {
    if (*(char *)(param_1 + 0x29) != '\0') {
      lVar4 = FUN_1800057a0(lVar4,_DAT_188805040);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b638d0(lVar4,0,0);
      if (cVar2 != '\0') {
        return 0;
      }
      if (lVar4 == 0) goto LAB_18102a6d2;
      lVar4 = FUN_180005610(0xa7,lVar4);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b638d0(lVar4,0,0);
      if (cVar2 != '\0') {
        return 0;
      }
    }
    if (*(char *)(param_1 + 0x20) == '\0') {
      if (param_2 != 0) {
        uVar7 = 0;
        uVar3 = Torappu_Blackboard_GetIntOrDefault_0x6007874
                          (param_2,*(undefined8 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x38),0
                           ,0);
        if (*(char *)(param_1 + 0x2a) != '\0') {
          uVar6 = *(undefined8 *)(param_4 + 0x10);
        }
        if (lVar4 != 0) {
          Torappu_Battle_Entity_RemoveBuffs_0x60103f9
                    (lVar4,uVar5,*(undefined1 *)(param_1 + 0x19),*(undefined1 *)(param_1 + 0x1a),
                     CONCAT44(uVar7,uVar3),uVar6,0);
          return 1;
        }
      }
LAB_18102a6d2:
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      uVar5 = (*pcVar1)();
      return uVar5;
    }
    uVar6 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                      (param_4,*(undefined4 *)(param_1 + 0x24),0);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b638d0(uVar6,0,0);
    if (cVar2 == '\0') {
      if (lVar4 == 0) goto LAB_18102a6d2;
      Torappu_Battle_Entity_RemoveBuffsByBuffSource_0x60103fb
                (lVar4,uVar6,uVar5,*(undefined1 *)(param_1 + 0x28),0);
    }
  }
  return 1;
}

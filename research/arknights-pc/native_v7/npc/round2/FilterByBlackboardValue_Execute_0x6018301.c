/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong FilterByBlackboardValue_Execute_0x6018301
                    (longlong param_1,longlong param_2,undefined4 param_3,undefined8 param_4)
{
  undefined4 uVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  if (DAT_188c97194 == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_18886e828);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c97194 = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18886e828 + 0xb8) + 0x18);
  if (lVar5 != 0) {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar5,param_1,param_2,param_3,param_4,0);
    return uVar6;
  }
  uVar7 = *(undefined8 *)(param_1 + 0x28);
  uVar4 = *(undefined8 *)(param_1 + 0x20);
  if (DAT_188c97195 == '\0') {
    FUN_18048bf00(&DAT_18886e828);
    DAT_188c97195 = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18886e828 + 0xb8) + 0x20);
  if (lVar5 == 0) {
    if ((param_2 != 0) && (cVar3 = func_0x000185db9d60(uVar7,0), cVar3 == '\0')) {
      uVar4 = Torappu_Blackboard_GetStringOrDefault_0x6007875(param_2,uVar7,uVar4,1,0);
    }
  }
  else {
    uVar4 = XLua_DelegateBridge___Gen_Delegate_Imp127_0x6000adf(lVar5,param_1,param_2,uVar7,uVar4,0)
    ;
  }
  lVar5 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x10),0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar6 = FUN_186b638d0(lVar5,0,0);
  if (((char)uVar6 != '\0') || (uVar6 = func_0x000185db9d60(uVar4,0), (char)uVar6 != '\0')) {
LAB_18112d6f5:
    return uVar6 & 0xffffffffffffff00;
  }
  if (*(char *)(param_1 + 0x14) != '\0') {
    if ((lVar5 == 0) ||
       (lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar5,0), lVar5 == 0))
    goto LAB_18112d716;
    lVar5 = BuffContainer_GetFirstBuffByKey_0x600ff2d(lVar5,*(undefined8 *)(param_1 + 0x18),0);
    uVar6 = 0;
    if (lVar5 == 0) goto LAB_18112d6f5;
    param_2 = Torappu_Battle_Buff_get_blackboard_0x600fe37(lVar5,0);
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar7 = func_0x0001866fdad0(0,0);
  if (param_2 != 0) {
    uVar7 = Torappu_Blackboard_GetFpOrDefault_0x6007872(param_2,uVar4,uVar7,0,0);
    uVar4 = func_0x0001866fdac0(*(undefined4 *)(param_1 + 0x30),0);
    cVar3 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x38),0);
    if (cVar3 == '\0') {
      uVar4 = *(undefined8 *)(param_1 + 0x38);
      uVar1 = *(undefined4 *)(param_1 + 0x30);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar8 = func_0x0001866fdac0(uVar1,0);
      uVar4 = Torappu_Blackboard_GetFpOrDefault_0x6007872(param_2,uVar4,uVar8,0,0);
    }
    uVar1 = *(undefined4 *)(param_1 + 0x40);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar5 = Torappu_MathUtil_GetCompareFuncFP_0x600028c(uVar1,0);
    if (lVar5 != 0) {
      uVar6 = (**(code **)(lVar5 + 0x18))
                        (*(undefined8 *)(lVar5 + 0x40),uVar7,uVar4,*(undefined8 *)(lVar5 + 0x28));
      return uVar6;
    }
  }
LAB_18112d716:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar6 = (*pcVar2)();
  return uVar6;
}

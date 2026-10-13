/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
AssignValueToBB_Execute_0x601768d
          (longlong param_1,longlong param_2,undefined4 param_3,undefined8 param_4)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  if (DAT_188c9634f == '\0') {
    FUN_18048bf00(&DAT_188828748);
    FUN_18048bf00(&DAT_188878840);
    DAT_188c9634f = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188828748 + 0xb8) + 8);
  if (lVar1 == 0) {
    cVar3 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x10),0);
    if (cVar3 == '\0') {
      uVar5 = *(undefined4 *)(param_1 + 0x18);
      uVar4 = **(undefined8 **)(_DAT_188878840 + 0xb8);
      cVar3 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x20),0);
      if (cVar3 == '\0') {
        if (*(char *)(param_1 + 0x28) == '\0') {
          if (param_2 == 0) {
LAB_181016134:
            FUN_18048c0b0();
            pcVar2 = (code *)swi(3);
            uVar4 = (*pcVar2)();
            return uVar4;
          }
          uVar5 = Torappu_Blackboard_GetFloatOrDefault_0x6007871
                            (param_2,*(undefined8 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x18)
                             ,0,0);
          cVar3 = *(char *)(param_1 + 0x28);
        }
        else {
          if (param_2 == 0) goto LAB_181016134;
          uVar4 = Torappu_Blackboard_GetStringOrDefault_0x6007875
                            (param_2,*(undefined8 *)(param_1 + 0x20),uVar4,0,0);
          cVar3 = *(char *)(param_1 + 0x28);
        }
      }
      else {
        cVar3 = *(char *)(param_1 + 0x28);
        if (param_2 == 0) goto LAB_181016134;
      }
      if (cVar3 == '\0') {
        Torappu_Blackboard_Assign_0x600785a(param_2,*(undefined8 *)(param_1 + 0x10),uVar5);
      }
      else {
        Torappu_Blackboard_Assign_0x600785d(param_2,*(undefined8 *)(param_1 + 0x10),uVar4,0);
      }
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar1,param_1,param_2,param_3,param_4,0);
  }
  return uVar4;
}

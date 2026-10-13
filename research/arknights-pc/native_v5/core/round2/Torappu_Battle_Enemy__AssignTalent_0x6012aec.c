
/* WARNING: Removing unreachable block (ram,0x000180a77cef) */
/* WARNING: Removing unreachable block (ram,0x000180a77d02) */
/* WARNING: Removing unreachable block (ram,0x000180a77d0b) */
/* WARNING: Removing unreachable block (ram,0x000180a77d18) */
/* WARNING: Removing unreachable block (ram,0x000180a77d32) */
/* WARNING: Removing unreachable block (ram,0x000180a77d3b) */
/* WARNING: Removing unreachable block (ram,0x000180a77d44) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy__AssignTalent_0x6012aec(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  uint uVar7;
  longlong lVar8;
  
  if (DAT_188c928d4 == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_188833b88);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_1888944c0);
    FUN_18048bf00(&DAT_18895a068);
    FUN_18048bf00(&DAT_188916358);
    FUN_18048bf00(&DAT_1887fb958);
    DAT_188c928d4 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x7e0);
  if (lVar4 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar4,param_1,param_2,0);
    return;
  }
  uVar7 = 0;
  lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
  if (lVar4 != 0) {
    lVar8 = 0x20;
    do {
      if (*(int *)(lVar4 + 0x18) <= (int)uVar7) {
        return;
      }
      lVar4 = func_0x00018045cfe0(_DAT_188941920);
      if (lVar4 == 0) break;
      Torappu_Blackboard__ctor_0x6007854(lVar4,0);
      if (param_2 != 0) {
        lVar5 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
        if (lVar5 == 0) break;
        if (*(uint *)(lVar5 + 0x18) <= uVar7) goto LAB_180a77dbc;
        if (*(longlong *)(lVar8 + lVar5) == 0) break;
        uVar6 = FUN_180005610(0x13);
        cVar3 = func_0x000185db9d60(uVar6,0);
        if (cVar3 == '\0') {
          lVar5 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
          if (lVar5 == 0) break;
          if (*(uint *)(lVar5 + 0x18) <= uVar7) goto LAB_180a77dbc;
          if (*(longlong *)(lVar8 + lVar5) == 0) break;
          uVar6 = FUN_180005610(0x13);
          uVar6 = System_String_Format_0x600030c(_DAT_1887fb958,uVar6,0);
          Torappu_Blackboard_AssignByPrefix_0x600787c(lVar4,param_2,uVar6,0);
          lVar5 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
          if (lVar5 == 0) break;
          if (*(uint *)(lVar5 + 0x18) <= uVar7) goto LAB_180a77dbc;
          if (*(longlong *)(lVar8 + lVar5) == 0) break;
          uVar6 = FUN_180005610(0x13);
          uVar6 = System_String_Format_0x600030c(_DAT_1887fb958,uVar6,0);
          Torappu_Blackboard_AssignValueStrByPrefix_0x600787d(lVar4,param_2,uVar6);
        }
        else {
          Torappu_Blackboard_Assign_0x6007859(lVar4,param_2,0);
        }
      }
      Torappu_Blackboard_TryGetBool_0x600786c(lVar4);
      lVar5 = func_0x00018045cfe0(_DAT_1888944c0);
      if (lVar5 == 0) break;
      Torappu_TalentData__ctor_0x6008147(lVar5,0);
      *(longlong *)(lVar5 + 0x40) = lVar4;
      func_0x00018048b9e0(lVar5 + 0x40,lVar4);
      uVar6 = Torappu_Blackboard_GetStringOrDefault_0x6007875(lVar4,_DAT_188916358,0,0,0);
      *(undefined8 *)(lVar5 + 0x38) = uVar6;
      func_0x00018048b9e0(lVar5 + 0x38,uVar6);
      lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
      if (lVar4 == 0) break;
      if (*(uint *)(lVar4 + 0x18) <= uVar7) {
LAB_180a77dbc:
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      plVar1 = *(longlong **)(lVar8 + lVar4);
      if (*(int *)(_DAT_188833b88 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_188833b88);
      }
      if (plVar1 == (longlong *)0x0) break;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar1);
      }
      (**(code **)(*plVar1 + 0x290))(plVar1);
      uVar7 = uVar7 + 1;
      lVar8 = lVar8 + 8;
      lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1);
    } while (lVar4 != 0);
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


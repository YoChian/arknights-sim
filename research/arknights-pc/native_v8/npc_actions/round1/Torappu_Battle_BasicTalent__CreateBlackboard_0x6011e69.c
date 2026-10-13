
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_BasicTalent__CreateBlackboard_0x6011e69
                   (longlong *param_1,undefined8 param_2,longlong *param_3)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  bool bVar6;
  
  if (DAT_188c91e32 == '\0') {
    FUN_18048bf00(&DAT_188925de0);
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_18888d718);
    DAT_188c91e32 = '\x01';
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x170);
  if (lVar3 != 0) {
    lVar3 = XLua_DelegateBridge___Gen_Delegate_Imp3562_0x600184a(lVar3,param_1,param_2,param_3,0);
    return lVar3;
  }
  if (param_3 == (longlong *)0x0) {
    plVar5 = (longlong *)0x0;
  }
  else {
    lVar3 = *param_3;
    if (DAT_188ccc7f0 == '\0') {
      if ((*(byte *)(lVar3 + 0x130) < *(byte *)(_DAT_18886c268 + 0x130)) ||
         (bVar6 = true,
         *(longlong *)
          (*(longlong *)(lVar3 + 200) + -8 + (ulonglong)*(byte *)(_DAT_18886c268 + 0x130) * 8) !=
         _DAT_18886c268)) {
        bVar6 = false;
      }
      bVar6 = !bVar6;
    }
    else {
      cVar2 = func_0x0001804463e0(lVar3);
      bVar6 = cVar2 == '\0';
    }
    plVar5 = (longlong *)0x0;
    if (!bVar6) {
      plVar5 = param_3;
    }
  }
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = FUN_186b638d0(plVar5,0,0);
  if (cVar2 == '\0') {
    if (plVar5 == (longlong *)0x0) goto LAB_180973363;
    cVar2 = Torappu_Battle_Character_get_hasSkill_0x6012850(plVar5,0);
    if (cVar2 != '\0') {
      lVar3 = Torappu_Battle_Character_get_skill_0x601284d(plVar5,0);
      if (lVar3 != 0) {
        uVar4 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(lVar3,0);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar2 = (**(code **)(*param_1 + 0x1e0))(param_1,*(undefined8 *)(*param_1 + 0x1e8));
        if (cVar2 == '\0') {
          lVar3 = func_0x00018045cfe0(_DAT_188941920);
          if (lVar3 == 0) goto LAB_180973363;
          Torappu_Blackboard__ctor_0x6007855(lVar3,param_2,0);
        }
        else {
          lVar3 = Torappu_Battle_BasicTalent__GenerateBlackboardByTalentScale_0x6011e6a
                            (param_1,param_2,uVar4,0);
        }
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar2 = (**(code **)(*param_1 + 0x220))(param_1,*(undefined8 *)(*param_1 + 0x228));
        if (cVar2 != '\0') {
          if (lVar3 == 0) goto LAB_180973363;
          Torappu_Blackboard_AssignByPrefix_0x600787c(lVar3,uVar4,_DAT_18888d718,0);
        }
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar2 = (**(code **)(*param_1 + 0x230))(param_1,*(undefined8 *)(*param_1 + 0x238));
        if (cVar2 == '\0') {
          return lVar3;
        }
        if (lVar3 != 0) {
          Torappu_Blackboard_AssignValueStrByPrefix_0x600787d(lVar3,uVar4,_DAT_18888d718,0);
          return lVar3;
        }
      }
      goto LAB_180973363;
    }
  }
  lVar3 = func_0x00018045cfe0(_DAT_188941920);
  if (lVar3 != 0) {
    Torappu_Blackboard__ctor_0x6007855(lVar3,param_2,0);
    return lVar3;
  }
LAB_180973363:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  lVar3 = (*pcVar1)();
  return lVar3;
}


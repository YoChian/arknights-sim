
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_CastSkill_DoCast_0x6011cc0
                    (longlong *param_1,undefined8 param_2,undefined4 param_3)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined4 uVar4;
  longlong *plVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 uStack_28;
  undefined4 uStack_20;
  undefined1 auStack_18 [16];
  
  if (DAT_188c91d0b == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_188855d90);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1887f8d08);
    DAT_188c91d0b = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0xa0);
  if (lVar8 != 0) {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp2812_0x600155c(lVar8,param_1,param_2,param_3,0);
    return uVar6;
  }
  if (DAT_188c91c3d == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c3d = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
  if (lVar8 == 0) {
    plVar5 = (longlong *)param_1[0x15];
  }
  else {
    plVar5 = (longlong *)XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar8,param_1,0);
  }
  if (plVar5 == (longlong *)0x0) goto LAB_180968849;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar5);
  }
  uVar6 = (**(code **)(*plVar5 + 0x3c0))(plVar5,*(undefined8 *)(*plVar5 + 0x3c8));
  if ((char)uVar6 == '\0') {
LAB_180968810:
    return uVar6 & 0xffffffffffffff00;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  uVar6 = (**(code **)(*param_1 + 0x3b0))(param_1,*(undefined8 *)(*param_1 + 0x3b8));
  if ((char)uVar6 == '\0') goto LAB_180968810;
  if (*(char *)((longlong)param_1 + 0x12d) != '\0') {
    lVar8 = param_1[0x24];
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar8,0,0);
    if (cVar2 != '\0') {
      if (param_1[0x24] == 0) goto LAB_180968849;
      FUN_180005540(0xd,param_1[0x24],1);
    }
  }
  if (*(char *)((longlong)param_1 + 300) == '\0') {
LAB_1809685b1:
    lVar8 = param_1[0x24];
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar8,0,0);
    if (cVar2 == '\0') {
LAB_180968672:
      if (*(char *)((longlong)param_1 + 0x12e) == '\0') {
        lVar8 = param_1[0x24];
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar2 = FUN_186b63a70(lVar8,0,0);
        if (cVar2 != '\0') {
          if (param_1[0x24] == 0) goto LAB_180968849;
          uVar7 = FUN_180005610(8);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar2 = FUN_186b638d0(uVar7,0,0);
          if (cVar2 != '\0') goto LAB_180968759;
        }
      }
      lVar8 = Torappu_Battle_BasicSkill_get_ability_0x6011bb2(param_1,0);
      if (lVar8 == 0) goto LAB_180968849;
      bVar3 = FUN_180005660(0x22,lVar8,param_2,1);
    }
    else {
      if (param_1[0x24] == 0) goto LAB_180968849;
      uVar7 = FUN_180005610(8);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b63a70(uVar7,0,0);
      if (cVar2 == '\0') goto LAB_180968672;
      lVar8 = Torappu_Battle_BasicSkill_get_ability_0x6011bb2(param_1,0);
      if ((param_1[0x24] == 0) || (uVar7 = FUN_180005610(8), lVar8 == 0)) goto LAB_180968849;
      bVar3 = FUN_180012f30(0x21,lVar8,uVar7,param_2,1);
    }
    if (bVar3 != 0) {
      lVar8 = Torappu_Battle_BasicSkill_get_data_0x6011bc1(param_1,0);
      if (lVar8 != 0) {
        uVar4 = Torappu_SkillData_get_spCost_0x600805e(lVar8,0);
        Torappu_Battle_BasicSkill_ReduceSp_0x6011bff(param_1,uVar4,0);
        return (ulonglong)bVar3;
      }
      goto LAB_180968849;
    }
  }
  else {
    lVar8 = param_1[0x24];
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar8,0,0);
    if (cVar2 == '\0') goto LAB_1809685b1;
    if (param_1[0x24] == 0) goto LAB_180968849;
    uVar7 = FUN_180005610(8);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b638d0(uVar7,0,0);
    if (cVar2 == '\0') goto LAB_1809685b1;
  }
LAB_180968759:
  lVar8 = Torappu_Battle_BasicSkill_get_data_0x6011bc1(param_1,0);
  if (lVar8 != 0) {
    uVar7 = *(undefined8 *)(lVar8 + 0x18);
    lVar8 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
    if (lVar8 != 0) {
      puVar9 = (undefined8 *)
               Torappu_Battle_VisualObject_get_worldPosition_0x601302d(auStack_18,lVar8,0);
      uStack_28 = *puVar9;
      uVar4 = *(undefined4 *)(puVar9 + 1);
      uVar10 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uStack_20 = uVar4;
      Torappu_Battle_BattleController_PlayAudioAtPos_0x600fce5
                (_DAT_1887f8d08,uVar7,&uStack_28,uVar10,0);
      return 0;
    }
  }
LAB_180968849:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  uVar6 = (*pcVar1)();
  return uVar6;
}


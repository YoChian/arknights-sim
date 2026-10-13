/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_BasicTalent_AssignData_0x6011e56
               (longlong *param_1,longlong param_2,longlong *param_3,undefined8 *param_4)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong alStack_78 [2];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  if (DAT_188c91e1f == '\0') {
    FUN_18048bf00(&DAT_188925de0);
    FUN_18048bf00(&DAT_188833b88);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188905e60);
    DAT_188c91e1f = '\x01';
  }
  uStack_30 = 0;
  uStack_40 = 0;
  uStack_38 = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0xd8);
  if (lVar1 != 0) {
    uStack_68 = *(undefined4 *)param_4;
    uStack_64 = *(undefined4 *)((longlong)param_4 + 4);
    uStack_60 = *(undefined4 *)(param_4 + 1);
    uStack_5c = *(undefined4 *)((longlong)param_4 + 0xc);
    XLua_DelegateBridge___Gen_Delegate_Imp3560_0x6001848(lVar1,param_1,param_2,param_3,&uStack_68,0)
    ;
    return;
  }
  Torappu_Battle_BasicTalent_set_data_0x6011e51(param_1,param_2,0);
  if (param_2 == 0) goto LAB_1809724c4;
  uVar5 = *(undefined8 *)(param_2 + 0x38);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar3 = (**(code **)(*param_1 + 0x210))(param_1,*(undefined8 *)(*param_1 + 0x218));
  if (cVar3 == '\0') {
LAB_180972148:
    cVar3 = func_0x000185db9d60(uVar5,0);
    if (cVar3 != '\0') {
      uVar5 = Torappu_Battle_BasicTalent_get_parentMode_0x6011e4e(param_1,0);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b638d0(uVar5,0,0);
      if (cVar3 == '\0') {
        uVar5 = Torappu_Battle_BasicTalent_get_parentMode_0x6011e4e(param_1,0);
        if (param_3 == (longlong *)0x0) goto LAB_1809724c4;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_3);
        }
        uVar5 = (**(code **)(*param_3 + 0xc70))(param_3,uVar5,1,*(undefined8 *)(*param_3 + 0xc78));
      }
      else {
        if (param_3 == (longlong *)0x0) goto LAB_1809724c4;
        uVar5 = FUN_180005610(0xa1,param_3);
      }
    }
  }
  else {
    if (param_3 == (longlong *)0x0) goto LAB_1809724c4;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_3);
    }
    uVar4 = (**(code **)(*param_3 + 0xa70))(param_3,*(undefined8 *)(*param_3 + 0xa78));
    cVar3 = func_0x000185db9d60(uVar4,0);
    if (cVar3 != '\0') goto LAB_180972148;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_3);
    }
    uVar5 = (**(code **)(*param_3 + 0xa70))(param_3,*(undefined8 *)(*param_3 + 0xa78));
  }
  alStack_78[0] =
       Torappu_Battle_BasicTalent__CreateBlackboard_0x6011e69
                 (param_1,*(undefined8 *)(param_2 + 0x40),param_3,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar3 = (**(code **)(*param_1 + 0x240))(param_1,*(undefined8 *)(*param_1 + 0x248));
  if (((cVar3 != '\0') && (alStack_78[0] != 0)) &&
     (cVar3 = func_0x000185db9d60(uVar5,0), cVar3 == '\0')) {
    if (alStack_78[0] == 0) goto LAB_1809724c4;
    Torappu_Blackboard_Assign_0x600785d(alStack_78[0],_DAT_188905e60,uVar5,0);
  }
  if (*(int *)(_DAT_188833b88 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = Delta_IsNull_0x6013020(param_4,0);
  if (cVar3 == '\0') {
    Torappu_Blackboard_MergeTo_0x6007861(alStack_78,*param_4,0);
    cVar3 = func_0x000185db9d60(param_4[1],0);
    if (cVar3 == '\0') {
      uVar5 = param_4[1];
    }
  }
  lVar1 = param_1[7];
  uStack_40 = 0;
  uStack_38 = 0;
  uStack_48 = alStack_78[0];
  uStack_30 = 0;
  func_0x00018048b9e0(&uStack_48);
  if (param_3 != (longlong *)0x0) {
    uVar4 = Torappu_Battle_Entity_get_id_0x6010328(param_3,0);
    uVar6 = Torappu_Battle_Entity_get_tmplId_0x601032a(param_3,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar7 = (**(code **)(*param_1 + 0x270))(param_1,*(undefined8 *)(*param_1 + 0x278));
    uStack_40 = Torappu_Battle_Unit_GenerateTalentSignalId_0x6012f73(uVar4,uVar6,uVar7,0);
    func_0x00018048b9e0(&uStack_40,uStack_40);
    uStack_38 = uVar5;
    func_0x00018048b9e0(&uStack_38,uVar5);
    if (DAT_188c91e31 == '\0') {
      FUN_18048bf00(&DAT_188925de0);
      FUN_18048bf00(&DAT_1889167d8);
      DAT_188c91e31 = '\x01';
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x168);
    if (lVar8 == 0) {
      if (DAT_188c91e17 == '\0') {
        FUN_18048bf00(&DAT_188925de0);
        DAT_188c91e17 = '\x01';
      }
      lVar8 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x98);
      if (lVar8 == 0) {
        lVar8 = param_1[8];
      }
      else {
        lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3015_0x6001627(lVar8,param_1,0);
      }
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_3);
      }
      uStack_50 = (**(code **)(*param_3 + 0xc80))(param_3,lVar8,*(undefined8 *)(*param_3 + 0xc88));
      if (*(longlong *)(param_2 + 0x40) != 0) {
        uStack_50 = Torappu_Blackboard_GetFloatOrDefault_0x6007871
                              (*(undefined8 *)(param_2 + 0x40),_DAT_1889167d8,uStack_50,0,0);
      }
    }
    else {
      uStack_50 = XLua_DelegateBridge___Gen_Delegate_Imp2014_0x600123e
                            (lVar8,param_1,param_2,param_3,0);
    }
    uStack_30 = CONCAT44(3,uStack_50);
    if (lVar1 != 0) {
      uStack_68 = (undefined4)uStack_48;
      uStack_64 = uStack_48._4_4_;
      uStack_60 = (undefined4)uStack_40;
      uStack_5c = uStack_40._4_4_;
      uStack_58 = (undefined4)uStack_38;
      uStack_54 = uStack_38._4_4_;
      uStack_4c = 3;
      Torappu_Battle_Ability_SetData_0x600f64f(lVar1,param_3,&uStack_68,0);
      return;
    }
  }
LAB_1809724c4:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

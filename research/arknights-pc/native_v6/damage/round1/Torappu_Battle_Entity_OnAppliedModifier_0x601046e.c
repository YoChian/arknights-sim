/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnAppliedModifier_0x601046e(undefined8 param_1,undefined8 *param_2)
{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  longlong lVar6;
  undefined8 uStack_138;
  undefined4 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined8 uStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  if (DAT_188c908fd == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_188811960);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888d3908);
    FUN_18048bf00(&DAT_188958f28);
    DAT_188c908fd = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x988);
  if (lVar3 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar3,param_1,param_2,0);
    return;
  }
  lVar3 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
  if (lVar3 == 0) {
LAB_1806f6e8e:
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  BuffContainer_OnAppliedModifier_0x600ff64(lVar3,param_2,0);
  uStack_128 = *param_2;
  uStack_120 = param_2[1];
  uStack_118 = param_2[2];
  uStack_110 = param_2[3];
  uStack_108 = param_2[4];
  uStack_100 = param_2[5];
  uStack_f8 = param_2[6];
  uStack_f0 = param_2[7];
  uStack_e8 = param_2[8];
  uStack_e0 = param_2[9];
  uStack_d8 = param_2[10];
  uStack_d0 = param_2[0xb];
  uStack_c8 = param_2[0xc];
  uStack_c0 = param_2[0xd];
  uStack_b8 = *(undefined4 *)(param_2 + 0xe);
  uStack_b4 = *(undefined4 *)((longlong)param_2 + 0x74);
  uStack_b0 = *(undefined4 *)(param_2 + 0xf);
  uStack_ac = *(undefined4 *)((longlong)param_2 + 0x7c);
  uStack_a8 = param_2[0x10];
  uVar4 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_128);
  Torappu_Battle_Entity_EmitEvent_0x601049d(param_1,10,uVar4,0);
  lVar3 = FUN_185337c50(_DAT_1888d3908);
  if (lVar3 == 0) goto LAB_1806f6e8e;
  lVar3 = Torappu_Battle_BattleController_get_eventPool_0x600fbf9(lVar3,0);
  uStack_98 = *param_2;
  uStack_90 = param_2[1];
  uStack_88 = param_2[2];
  uStack_80 = param_2[3];
  uStack_78 = param_2[4];
  uStack_70 = param_2[5];
  uStack_68 = param_2[6];
  uStack_60 = param_2[7];
  uStack_58 = param_2[8];
  uStack_50 = param_2[9];
  uStack_48 = param_2[10];
  uStack_40 = param_2[0xb];
  uStack_38 = param_2[0xc];
  uStack_30 = param_2[0xd];
  uStack_28 = *(undefined4 *)(param_2 + 0xe);
  uStack_24 = *(undefined4 *)((longlong)param_2 + 0x74);
  uStack_20 = *(undefined4 *)(param_2 + 0xf);
  uStack_1c = *(undefined4 *)((longlong)param_2 + 0x7c);
  uStack_18 = param_2[0x10];
  uVar4 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_98);
  if (lVar3 == 0) goto LAB_1806f6e8e;
  FUN_1848dca60(lVar3,0xe,uVar4,_DAT_188811960);
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_Battle_Modifier_get_isHeal_0x6011531(param_2,0);
  if (cVar2 != '\0') {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,1,0);
    if (cVar2 == '\0') {
      puVar5 = (undefined8 *)
               Torappu_Battle_VisualObject_get_worldPosition_0x601302d(&uStack_138,param_1,0);
      uStack_138 = *puVar5;
      uStack_130 = *(undefined4 *)(puVar5 + 1);
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      Torappu_Battle_BattleController_PlayAudioAtPos_0x600fce5(_DAT_188958f28,0,&uStack_138,0,0);
    }
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar3 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
  cVar2 = Torappu_Battle_Modifier_get_isDamage_0x6011530(param_2,0);
  if (cVar2 != '\0') {
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar3,0,0);
    if (cVar2 != '\0') {
      if (lVar3 == 0) goto LAB_1806f6e88;
      if (DAT_188c90901 == '\0') {
        FUN_18048bf00(&DAT_188841368);
        DAT_188c90901 = '\x01';
      }
      if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_188841368);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x9a8);
      if (lVar6 == 0) {
        lVar6 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar3,0);
        if (lVar6 == 0) goto LAB_1806f6e88;
        BuffContainer_OnAfterOutputDamage_0x600ff68(lVar6,param_2,0);
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar6,lVar3,param_2,0);
      }
    }
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_Battle_Modifier_get_isHeal_0x6011531(param_2,0);
  if (cVar2 != '\0') {
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar3,0,0);
    if (cVar2 != '\0') {
      if (lVar3 == 0) goto LAB_1806f6e88;
      if (DAT_188c90902 == '\0') {
        FUN_18048bf00(&DAT_188841368);
        DAT_188c90902 = '\x01';
      }
      if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_188841368);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x9b0);
      if (lVar6 == 0) {
        lVar6 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar3,0);
        if (lVar6 == 0) goto LAB_1806f6e88;
        BuffContainer_OnAfterOutputHeal_0x600ff69(lVar6,param_2,0);
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar6,lVar3,param_2,0);
      }
    }
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_Battle_Modifier_get_isElementDamage_0x6011532(param_2,0);
  if (cVar2 != '\0') {
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar3,0,0);
    if (cVar2 != '\0') {
      if (lVar3 == 0) goto LAB_1806f6e88;
      if (DAT_188c90903 == '\0') {
        FUN_18048bf00(&DAT_188841368);
        DAT_188c90903 = '\x01';
      }
      if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_188841368);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x9b8);
      if (lVar6 == 0) {
        lVar3 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar3,0);
        if (lVar3 == 0) goto LAB_1806f6e88;
        BuffContainer_OnAfterOutputElementDamage_0x600ff6a(lVar3,param_2,0);
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar6,lVar3,param_2,0);
      }
    }
  }
  lVar3 = FUN_185337c50(_DAT_1888d3908);
  if ((lVar3 != 0) &&
     (lVar3 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar3,0), lVar3 != 0)) {
    Torappu_Battle_BattleLogger_LogModifier_0x60105a6(lVar3,param_2,0);
    lVar3 = FUN_185337c50(_DAT_1888d3908);
    if ((lVar3 != 0) &&
       (lVar3 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar3,0), lVar3 != 0)) {
      Torappu_Battle_BattleLogger_LogEpModifier_0x60105a7(lVar3,param_2,0);
      return;
    }
  }
LAB_1806f6e88:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

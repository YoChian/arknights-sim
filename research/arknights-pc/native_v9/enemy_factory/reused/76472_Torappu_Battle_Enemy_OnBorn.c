
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_OnBorn_0x6012ab9(longlong *param_1)

{
  code *pcVar1;
  char cVar2;
  longlong *plVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined8 *puVar6;
  longlong lStackX_18;
  undefined8 uStackX_20;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 *puStack_58;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  if (DAT_188c928a1 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_188847ca0);
    FUN_18048bf00(&DAT_188934168);
    FUN_18048bf00(&DAT_188906de8);
    FUN_18048bf00(&DAT_1888a36e8);
    FUN_18048bf00(&DAT_1888d3908);
    FUN_18048bf00(&DAT_188878840);
    FUN_18048bf00(&DAT_18896ad88);
    FUN_18048bf00(&DAT_1889538f0);
    DAT_188c928a1 = '\x01';
  }
  lStackX_18 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x648);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar5,param_1,0);
    return;
  }
  Torappu_Battle_Unit_OnBorn_0x6012f81(param_1,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 0x8b0))(param_1,*(undefined8 *)(*param_1 + 0x8b8));
  if (param_1[0x72] == 0) goto LAB_180a70649;
  Torappu_Battle_MoveController_OnStart_0x6011590(param_1[0x72],0);
  if (DAT_188c928a2 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c928a2 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x650);
  if (lVar5 == 0) {
    if ((char)param_1[0x67] == '\0') {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      plVar3 = (longlong *)
               (**(code **)(*param_1 + 0xf50))(param_1,*(undefined8 *)(*param_1 + 0xf58));
      if (plVar3 == (longlong *)0x0) goto LAB_180a70649;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar3);
      }
      uVar4 = (**(code **)(*plVar3 + 0x200))(plVar3,*(undefined8 *)(*plVar3 + 0x208));
      Torappu_Battle_Entity_FaceTo_0x60103e8(param_1,uVar4,1,0,0);
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar5,param_1,0);
  }
  if (DAT_188c92822 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c92822 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x250);
  if (lVar5 == 0) {
    lVar5 = Torappu_Battle_Enemy_get_data_0x6012a2f(param_1,0);
    if (lVar5 != 0) {
      lVar5 = Torappu_Battle_Enemy_get_data_0x6012a2f(param_1,0);
      if (lVar5 == 0) goto LAB_180a70649;
      cVar2 = func_0x000182417bf0(lVar5,0);
      goto LAB_180a703b1;
    }
  }
  else {
    cVar2 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar5,param_1,0);
LAB_180a703b1:
    if (cVar2 != '\0') {
      lVar5 = FUN_185337c50(_DAT_1888d3908);
      if (lVar5 == 0) goto LAB_180a70649;
      Torappu_Battle_BattleController_OnBossEnter_0x600fd08(lVar5,param_1,0);
    }
  }
  *(undefined4 *)(param_1 + 0x69) = 0;
  uVar4 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(param_1,0);
  uStackX_20._0_4_ = (undefined4)uVar4;
  *(undefined4 *)(param_1 + 0x82) = (undefined4)uStackX_20;
  uStackX_20._4_4_ = (undefined4)((ulonglong)uVar4 >> 0x20);
  *(undefined4 *)((longlong)param_1 + 0x414) = uStackX_20._4_4_;
  uStackX_20 = uVar4;
  if (param_1[0x75] != 0) {
    Torappu_PeriodicTicker_Reset_0x600656a(param_1[0x75],1,0);
    lVar5 = FUN_1844dc3f0(param_1,**(undefined8 **)(_DAT_188878840 + 0xb8),_DAT_188847ca0);
    param_1[0x70] = lVar5;
    func_0x00018048b9e0(param_1 + 0x70,lVar5);
    puVar6 = (undefined8 *)
             Torappu_Battle_LevelScript_EventParams_Allocate_0x601476e(&uStack_28,&lStackX_18,0);
    lVar5 = lStackX_18;
    uStack_70 = *puVar6;
    uStack_68 = puVar6[1];
    uStack_60 = 0;
    puStack_58 = &uStack_70;
    uVar4 = Torappu_Battle_Entity_get_id_0x6010328(param_1,0);
    if (lVar5 != 0) {
      Torappu_Battle_LevelScript_EventParams_SetSender_0x6014770(lVar5,uVar4,0);
      lVar5 = lStackX_18;
      uVar4 = Torappu_Battle_Entity_get_id_0x6010328(param_1,0);
      if (lVar5 != 0) {
        Torappu_Battle_LevelScript_EventParams_SetReceiver_0x6014771(lVar5,uVar4,0);
        lVar5 = lStackX_18;
        uStack_48 = 0;
        uStack_40 = 0;
        FUN_185159ec0(&uStack_48,param_1,_DAT_188934168);
        uStack_38 = (undefined4)uStack_48;
        uStack_34 = uStack_48._4_4_;
        uStack_30 = (undefined4)uStack_40;
        uStack_2c = uStack_40._4_4_;
        func_0x00018048b9e0(&uStack_38,0);
        if (lVar5 != 0) {
          uStack_28 = uStack_38;
          uStack_24 = uStack_34;
          uStack_20 = uStack_30;
          uStack_1c = uStack_2c;
          FUN_1845797d0(lVar5,_DAT_1889538f0,&uStack_28,_DAT_188906de8);
          lVar5 = FUN_185337c50(_DAT_1888d3908);
          if (lVar5 != 0) {
            lVar5 = Torappu_Battle_BattleController_get_levelScriptEventManager_0x600fc11(lVar5,0);
            if (lVar5 != 0) {
              Torappu_Battle_LevelScript_LevelScriptEventManager_RaiseLevelEvent_0x60147ec
                        (lVar5,_DAT_18896ad88,lStackX_18,0);
              FUN_18531eef0(&uStack_70,_DAT_1888a36e8);
              lVar5 = FUN_185337c50(_DAT_1888d3908);
              if (lVar5 != 0) {
                lVar5 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar5,0);
                uVar4 = Torappu_Battle_Enemy_get_data_0x6012a2f(param_1,0);
                if (lVar5 != 0) {
                  Torappu_Battle_BattleLogger_OnEnemyBorn_0x60105b7(lVar5,uVar4,0);
                  return;
                }
              }
              goto LAB_180a70649;
            }
            FUN_18048c0b0();
          }
          FUN_18048c0b0();
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
LAB_180a70649:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


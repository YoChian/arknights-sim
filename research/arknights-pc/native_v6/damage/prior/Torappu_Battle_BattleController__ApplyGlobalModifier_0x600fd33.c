/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
Torappu_Battle_BattleController__ApplyGlobalModifier_0x600fd33
          (longlong param_1,undefined8 *param_2,undefined8 param_3)
{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined4 *puVar11;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 auStack_b8 [4];
  undefined8 uStack_a8;
  undefined8 uStack_a0;
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
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  if (DAT_188c9015d == '\0') {
    uStack_40 = 0x1806355fd;
    FUN_18048bf00(&DAT_188927d60);
    DAT_188c9015d = '\x01';
  }
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    uStack_40 = 0x180635619;
    func_0x00018048c140();
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0xc38);
  if (lVar9 != 0) {
    uStack_40 = 0x1806357b3;
    uVar8 = XLua_DelegateBridge___Gen_Delegate_Imp2886_0x60015a6(lVar9,param_1,param_2,param_3);
    return uVar8;
  }
  if (DAT_188c9015e == '\0') {
    uStack_40 = 0x18063564c;
    FUN_18048bf00(&DAT_188927d60);
    DAT_188c9015e = '\x01';
  }
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    uStack_40 = 0x180635668;
    func_0x00018048c140();
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0xc40);
  if (lVar9 == 0) {
    plVar1 = *(longlong **)(param_1 + 0x170);
    if (plVar1 == (longlong *)0x0) {
      uStack_40 = 0x1806357c8;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    switch(*(undefined4 *)(*plVar1 + 0x11c)) {
    case 0x9b7:
    case 0x9b8:
    case 0x9b9:
    case 0x9ba:
    case 0x9bc:
    case 0x9bd:
    case 0x9be:
    case 0x9bf:
    case 0x9c1:
    case 0x9c2:
    case 0x9c3:
    case 0x9c5:
    case 0x9c7:
    case 0x9c8:
    case 0x9c9:
    case 0x9ca:
    case 0x9ce:
    case 0x9cf:
    case 0x9d0:
    case 0x9d1:
      uStack_40 = 0x180635750;
      FootballCupGameMode___xLuaBaseProxy_OnApplyingGlobalModifier_0x6014064(plVar1,param_2,0);
      break;
    case 0x9bb:
      uStack_40 = 0x1806356da;
      Act7FunGameMode_OnApplyingGlobalModifier_0x6013b9e(plVar1,param_2,0);
      break;
    case 0x9c0:
      uStack_40 = 0x1806356ed;
      CooperateGameMode_OnApplyingGlobalModifier_0x6013e02(plVar1,param_2,0);
      break;
    case 0x9c4:
      uStack_40 = 0x180635700;
      FootballCupGameMode_OnApplyingGlobalModifier_0x601403c(plVar1,param_2,0);
      break;
    case 0x9c6:
      uStack_40 = 0x180635710;
      GameCityGameMode_OnApplyingGlobalModifier_0x6014099(plVar1,param_2,0);
      break;
    case 0x9cb:
      uStack_40 = 0x180635720;
      RoguelikeGameMode_OnApplyingGlobalModifier_0x6014380(plVar1,param_2,0);
      break;
    case 0x9cc:
      uStack_40 = 0x180635730;
      RoguelikeDeifyGameMode_OnApplyingGlobalModifier_0x6014305(plVar1,param_2,0);
      break;
    case 0x9cd:
      uStack_40 = 0x180635740;
      RoguelikeDuelGameMode_OnApplyingGlobalModifier_0x6014323(plVar1,param_2,0);
      break;
    default:
      uStack_40 = 0x180635769;
      FUN_180005010(0x38,_DAT_188961dd0,plVar1,param_2);
    }
  }
  else {
    uStack_40 = 0x180635779;
    XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar9,param_1,param_2,0);
  }
  if (DAT_188c9015c == '\0') {
    FUN_18048bf00(&DAT_188927d60,param_2,param_3,0);
    FUN_18048bf00(&DAT_18892ea20);
    FUN_18048bf00(&DAT_188811960);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c6278);
    FUN_18048bf00(&DAT_1888c64b8);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188937ba8);
    FUN_18048bf00(&DAT_18895cfe8);
    FUN_18048bf00(&DAT_18894e1f0);
    DAT_188c9015c = '\x01';
  }
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188927d60);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0xc30);
  if (lVar9 != 0) {
    uVar8 = XLua_DelegateBridge___Gen_Delegate_Imp2886_0x60015a6(lVar9,param_1,param_2,param_3,0);
    return uVar8;
  }
  cVar3 = Torappu_Battle_BattleController_get_isPlaying_0x600fc14(param_1,0);
  if (cVar3 == '\0') {
    return 0;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar8 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(uVar8,0,0);
  if (cVar3 != '\0') {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar9 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    Torappu_Battle_Entity_OnOutputModifier_0x6010470(lVar9,param_2,0);
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_2,0);
  if (cVar3 != '\0') {
    return 0;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar4 = Torappu_Battle_Modifier_get_targetType_0x601152a(param_2,0);
  switch(uVar4) {
  case 2:
    lVar9 = Torappu_Battle_BattleController_get_costManager_0x600fbff(param_1,0);
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    iVar6 = Torappu_Battle_BattleCostManager_GetCost_0x600fd7f(lVar9,uVar4,0);
    lVar9 = Torappu_Battle_BattleController_get_costManager_0x600fbff(param_1,0);
    uVar8 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    iVar7 = Torappu_Battle_BattleCostManager_SetCost_0x600fd80(lVar9,iVar7 + iVar6,uVar4,0);
    break;
  case 3:
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    iVar6 = Torappu_Battle_BattleController_GetNumCharacterLimit_0x600fc2b(param_1,uVar4,0);
    uVar8 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
    iVar7 = iVar6 + iVar7;
    iVar5 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (cRam0000000188c9005a == '\0') {
      FUN_18048bf00(&DAT_188927d60);
      FUN_18048bf00(&DAT_1888c6278);
      FUN_18048bf00(&DAT_1888c64b8);
      FUN_18048bf00(&DAT_188937ba8);
      cRam0000000188c9005a = '\x01';
    }
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188927d60);
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0x400);
    if (lVar9 == 0) {
      cVar3 = Torappu_Battle_BattleController_get_isPlaying_0x600fc14(param_1,0);
      if (cVar3 == '\0') {
        iVar7 = Torappu_Battle_BattleController_GetNumCharacterLimit_0x600fc2b(param_1,iVar5,0);
      }
      else {
        if (iVar5 == 0) {
          iVar5 = Torappu_Battle_BattleController_get_playerSide_0x600fbbe(param_1,0);
        }
        lVar9 = *(longlong *)(param_1 + 0xc0);
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        else if (99 < iVar7) {
          iVar7 = 99;
        }
        if (*(int *)(_DAT_188937ba8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        puVar11 = (undefined4 *)
                  CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea2
                            (&uStack_f8,iVar7,0);
        if (lVar9 == 0) goto LAB_180637712;
        uStack_d8 = *puVar11;
        uStack_d4 = puVar11[1];
        uStack_d0 = puVar11[2];
        uStack_cc = puVar11[3];
        uStack_c8 = puVar11[4];
        FUN_184a919c0(lVar9,iVar5,&uStack_d8,_DAT_1888c64b8);
        if (*(longlong *)(param_1 + 0xc0) == 0) goto LAB_180637712;
        FUN_184aa2090(&uStack_d8,*(longlong *)(param_1 + 0xc0),iVar5,_DAT_1888c6278);
        uStack_e8 = uStack_c8;
        uStack_f8 = uStack_d8;
        uStack_f4 = uStack_d4;
        uStack_f0 = uStack_d0;
        uStack_ec = uStack_cc;
        iVar7 = CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3(&uStack_f8,0);
      }
    }
    else {
      iVar7 = XLua_DelegateBridge___Gen_Delegate_Imp2787_0x6001543(lVar9,param_1,iVar7,iVar5,0);
    }
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar7 = iVar7 - iVar6;
    goto code_r0x000180637539;
  case 4:
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    iVar6 = Torappu_Battle_BattleController_GetLifePoint_0x600fc3d(param_1,uVar4,0);
    uVar8 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
    if (0 < iVar7) {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x1000,0);
      if (cVar3 != '\0') {
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
        iVar5 = Torappu_Battle_BattleController_GetTempLifePoint_0x600fc3f(param_1,uVar4,0);
        uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
        Torappu_Battle_BattleController_SetTempLifePoint_0x600fc40(param_1,iVar5 + iVar7,uVar4,0);
        iVar7 = 0;
      }
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    iVar5 = Torappu_Battle_BattleController_GetTempLifePoint_0x600fc3f(param_1,uVar4,0);
    if ((0 < iVar5) && (iVar7 < 0)) {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
      iVar5 = Torappu_Battle_BattleController_GetTempLifePoint_0x600fc3f(param_1,uVar4,0);
      if (iVar5 < -iVar7) {
        iVar7 = iVar7 + iVar5;
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
        Torappu_Battle_BattleController_SetTempLifePoint_0x600fc40(param_1,0,uVar4,0);
      }
      else {
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
        Torappu_Battle_BattleController_SetTempLifePoint_0x600fc40(param_1,iVar5 + iVar7,uVar4,0);
        iVar7 = 0;
      }
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    iVar5 = Torappu_Battle_BattleController_GetLifePoint_0x600fc3d(param_1,uVar4,0);
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    Torappu_Battle_BattleController_SetLifePoint_0x600fc3e(param_1,iVar5 + iVar7,uVar4,0,0);
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    iVar7 = Torappu_Battle_BattleController_GetLifePoint_0x600fc3d(param_1,uVar4,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = func_0x0001866fdac0(iVar7 - iVar6,0);
    param_2[7] = uVar8;
    uVar10 = func_0x0001866fdad0(0,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = Torappu_MathUtil_LT_0x6000276(uVar8,uVar10,0);
    if (cVar3 != '\0') {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x200,0);
      if (cVar3 == '\0') {
        lVar9 = *(longlong *)(param_1 + 0x2d8);
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
        if (lVar9 == 0) goto LAB_180637712;
        FUN_184aa2090(&uStack_f8,lVar9,uVar4,_DAT_1888c6278);
        if (*(int *)(_DAT_188937ba8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uStack_c8 = uStack_e8;
        uStack_d8 = uStack_f8;
        uStack_d4 = uStack_f4;
        uStack_d0 = uStack_f0;
        uStack_cc = uStack_ec;
        iVar6 = CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3(&uStack_d8,0);
        uVar8 = param_2[7];
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar8 = Torappu_FP_op_UnaryNegation_0x6000308(uVar8,0);
        if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
        puVar11 = (undefined4 *)
                  CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea2
                            (&uStack_d8,iVar7 + iVar6,0);
        uStack_f8 = *puVar11;
        uStack_f4 = puVar11[1];
        uStack_f0 = puVar11[2];
        uStack_ec = puVar11[3];
        uStack_e8 = puVar11[4];
        FUN_184a919c0(lVar9,uVar4,&uStack_f8,_DAT_1888c64b8);
      }
      else {
        lVar9 = *(longlong *)(param_1 + 0x2d0);
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
        if (lVar9 == 0) goto LAB_180637712;
        FUN_184aa2090(&uStack_f8,lVar9,uVar4,_DAT_1888c6278);
        if (*(int *)(_DAT_188937ba8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uStack_c8 = uStack_e8;
        uStack_d8 = uStack_f8;
        uStack_d4 = uStack_f4;
        uStack_d0 = uStack_f0;
        uStack_cc = uStack_ec;
        iVar6 = CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3(&uStack_d8,0);
        uVar8 = param_2[7];
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar8 = Torappu_FP_op_UnaryNegation_0x6000308(uVar8,0);
        if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
        puVar11 = (undefined4 *)
                  CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea2
                            (&uStack_d8,iVar7 + iVar6,0);
        uStack_f8 = *puVar11;
        uStack_f4 = puVar11[1];
        uStack_f0 = puVar11[2];
        uStack_ec = puVar11[3];
        uStack_e8 = puVar11[4];
        FUN_184a919c0(lVar9,uVar4,&uStack_f8,_DAT_1888c64b8);
      }
    }
    goto code_r0x000180637546;
  default:
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    auStack_b8[0] = Torappu_Battle_Modifier_get_targetType_0x601152a(param_2,0);
    uVar8 = func_0x00018048b9c0(_DAT_18895cfe8,auStack_b8);
    uVar8 = System_String_Format_0x600030c(_DAT_18894e1f0,uVar8,0);
    if (*(int *)(_DAT_18892ea20 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    UnityEngine_DLog_LogError_0x6000031(uVar8,0);
    return 0;
  case 6:
    lVar9 = Torappu_Battle_BattleController_get_costManager_0x600fbff(param_1,0);
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    iVar6 = Torappu_Battle_BattleCostManager_GetMaxCost_0x600fd82(lVar9,uVar4,0);
    lVar9 = Torappu_Battle_BattleController_get_costManager_0x600fbff(param_1,0);
    uVar8 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    iVar7 = Torappu_Battle_BattleCostManager_SetMaxCost_0x600fd83(lVar9,iVar7 + iVar6,uVar4,0);
    break;
  case 7:
    lVar9 = Torappu_Battle_BattleController_get_costManager_0x600fbff(param_1,0);
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    iVar6 = Torappu_Battle_BattleCostManager_GetMinCost_0x600fd84(lVar9,uVar4,0);
    lVar9 = Torappu_Battle_BattleController_get_costManager_0x600fbff(param_1,0);
    uVar8 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar7 = Torappu_MathUtil_RoundToInt_0x600027c(uVar8,0);
    uVar4 = Torappu_Battle_Modifier_get_playerSide_0x6011547(param_2,0);
    if (lVar9 == 0) goto LAB_180637712;
    iVar7 = Torappu_Battle_BattleCostManager_SetMinCost_0x600fd85(lVar9,iVar7 + iVar6,uVar4,0,0);
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  iVar7 = iVar7 - iVar6;
code_r0x000180637539:
  uVar8 = func_0x0001866fdac0(iVar7,0);
  param_2[7] = uVar8;
code_r0x000180637546:
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar8 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(uVar8,0,0);
  if (cVar3 == '\0') {
    lVar9 = Torappu_Battle_BattleController_get_eventPool_0x600fbf9(param_1,0);
    uStack_a8 = *param_2;
    uStack_a0 = param_2[1];
    uStack_98 = param_2[2];
    uStack_90 = param_2[3];
    uStack_88 = param_2[4];
    uStack_80 = param_2[5];
    uStack_78 = param_2[6];
    uStack_70 = param_2[7];
    uStack_68 = param_2[8];
    uStack_60 = param_2[9];
    uStack_58 = param_2[10];
    uStack_50 = param_2[0xb];
    uStack_48 = param_2[0xc];
    uStack_40 = param_2[0xd];
    uStack_38 = *(undefined4 *)(param_2 + 0xe);
    uStack_34 = *(undefined4 *)((longlong)param_2 + 0x74);
    uStack_30 = *(undefined4 *)(param_2 + 0xf);
    uStack_2c = *(undefined4 *)((longlong)param_2 + 0x7c);
    uStack_28 = param_2[0x10];
    uVar8 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_a8);
    if (lVar9 == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    FUN_1848dca60(lVar9,0xe,uVar8,_DAT_188811960);
  }
  else {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar9 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
    if (lVar9 == 0) {
LAB_180637712:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar8 = (*pcVar2)();
      return uVar8;
    }
    Torappu_Battle_Entity_OnAppliedModifier_0x601046e(lVar9,param_2,0);
  }
  return 1;
}

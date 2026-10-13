/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
SummonEnemiesFollowMyRouteWithBuff_Execute_0x6018168
          (longlong param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4)
{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  char cVar11;
  undefined1 uVar12;
  longlong lVar13;
  longlong *plVar14;
  undefined8 uVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined4 *puVar19;
  longlong *plVar20;
  longlong lVar21;
  undefined8 uVar22;
  longlong *plVar23;
  uint uVar24;
  longlong *plVar25;
  bool bVar26;
  undefined4 uVar27;
  undefined4 extraout_XMM0_Da;
  longlong lStack_218;
  undefined4 uStack_210;
  undefined8 uStack_208;
  int iStack_200;
  undefined8 auStack_1f8 [2];
  undefined8 uStack_1e8;
  longlong *plStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  longlong lStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  longlong lStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_178;
  longlong *plStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  longlong lStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  longlong lStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined1 auStack_d8 [176];
  if (DAT_188c96dd4 == '\0') {
    FUN_18048bf00(&DAT_188897800);
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c4f88);
    FUN_18048bf00(&DAT_188893098);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888d3908);
    FUN_18048bf00(&DAT_1888cb898);
    FUN_18048bf00(&DAT_1887f9ef8);
    FUN_18048bf00(&DAT_1888b1328);
    FUN_18048bf00(&DAT_1888a1140);
    FUN_18048bf00(&DAT_188902ff8);
    FUN_18048bf00(&DAT_188952030);
    FUN_18048bf00(&DAT_1888b12e0);
    DAT_188c96dd4 = '\x01';
  }
  plVar25 = (longlong *)0x0;
  auStack_1f8[0] = 0;
  lVar13 = *(longlong *)(*(longlong *)(_DAT_1888cb898 + 0xb8) + 0x10);
  if (lVar13 != 0) {
    uVar15 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                       (lVar13,param_1,param_2,param_3,param_4,0);
    return uVar15;
  }
  lVar13 = func_0x00018045cfe0(_DAT_1888b1328);
  if (lVar13 == 0) goto LAB_1810dd823;
  func_0x00018050cf60(lVar13,0);
  *(longlong *)(lVar13 + 0x10) = param_1;
  func_0x00018048b9e0(lVar13 + 0x10,param_1);
  *(undefined8 *)(lVar13 + 0x20) = param_2;
  func_0x00018048b9e0(lVar13 + 0x20,param_2);
  plVar14 = (longlong *)
            Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                      (param_4,*(undefined4 *)(param_1 + 0x10),0);
  plVar23 = plVar25;
  if (plVar14 != (longlong *)0x0) {
    lVar16 = *plVar14;
    if (DAT_188ccc7f0 == '\0') {
      if ((*(byte *)(lVar16 + 0x130) < *(byte *)(_DAT_18881b6b0 + 0x130)) ||
         (bVar26 = true,
         *(longlong *)
          (*(longlong *)(lVar16 + 200) + -8 + (ulonglong)*(byte *)(_DAT_18881b6b0 + 0x130) * 8) !=
         _DAT_18881b6b0)) {
        bVar26 = false;
      }
      bVar26 = !bVar26;
    }
    else {
      cVar11 = func_0x0001804463e0(lVar16);
      bVar26 = cVar11 == '\0';
    }
    plVar23 = (longlong *)0x0;
    if (!bVar26) {
      plVar23 = plVar14;
    }
  }
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar11 = FUN_186b638d0(plVar23,0,0);
  if (cVar11 == '\0') {
    uVar15 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                       (param_4,*(undefined4 *)(param_1 + 0x7c),0);
    *(undefined8 *)(lVar13 + 0x18) = uVar15;
    func_0x00018048b9e0(lVar13 + 0x18,uVar15);
    uVar15 = *(undefined8 *)(lVar13 + 0x18);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar11 = FUN_186b638d0(uVar15,0,0);
    if (cVar11 == '\0') {
      lVar16 = func_0x00018045cfe0(_DAT_188897800);
      if (lVar16 != 0) {
        PinchUpdateExtendedDelegate__ctor_0x60054bb(lVar16,lVar13,_DAT_1887f9ef8,0);
        if (*(longlong *)(lVar13 + 0x20) != 0) {
          iStack_200 = Torappu_Blackboard_GetIntOrDefault_0x6007874
                                 (*(longlong *)(lVar13 + 0x20),_DAT_1888b12e0,
                                  *(undefined4 *)(param_1 + 0x20),0,0);
          lVar1 = *(longlong *)(lVar13 + 0x20);
          uVar27 = *(undefined4 *)(param_1 + 0x2c);
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar15 = func_0x0001866fdad0(uVar27,0);
          if (lVar1 != 0) {
            uVar15 = Torappu_Blackboard_GetFpOrDefault_0x6007872(lVar1,_DAT_1888a1140,uVar15,0,0);
            lVar1 = *(longlong *)(lVar13 + 0x20);
            uVar17 = func_0x0001866fdad0(*(undefined4 *)(param_1 + 0x24),0);
            if (lVar1 != 0) {
              uVar17 = Torappu_Blackboard_GetFpOrDefault_0x6007872(lVar1,_DAT_188902ff8,uVar17,0,0);
              uStack_208 = *(undefined8 *)(lVar13 + 0x20);
              lStack_218 = func_0x00018045cfe0(_DAT_188941920);
              if (lStack_218 != 0) {
                Torappu_Blackboard__ctor_0x6007855(lStack_218,uStack_208,0);
                plStack_1e0 = (longlong *)0x0;
                uStack_1d8 = 0;
                uStack_1d0 = 0;
                uStack_1c8 = 0;
                uStack_1c0 = 0;
                uStack_1b8 = 0;
                lStack_1b0 = 0;
                uStack_1a8 = 0;
                uStack_1a0 = 0;
                lStack_198 = 0;
                uStack_190 = 0;
                uStack_188 = 0;
                if (*(longlong *)(lVar13 + 0x20) != 0) {
                  uStack_1e8 = Torappu_Blackboard_GetStringOrDefault_0x6007875
                                         (*(longlong *)(lVar13 + 0x20),_DAT_188952030,
                                          *(undefined8 *)(param_1 + 0x18),1,0);
                  func_0x00018048b9e0(&uStack_1e8,uStack_1e8);
                  plStack_1e0 = plVar23;
                  func_0x00018048b9e0(&plStack_1e0,plVar23);
                  uStack_1d8 = CONCAT62(uStack_1d8._2_6_,*(undefined2 *)(param_1 + 0x28));
                  if (plVar23 != (longlong *)0x0) {
                    uVar18 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(plVar23,0);
                    uStack_208._0_4_ = (undefined4)uVar18;
                    uStack_208._4_4_ = (undefined4)((ulonglong)uVar18 >> 0x20);
                    uStack_1d8 = CONCAT44((undefined4)uStack_208,(undefined4)uStack_1d8);
                    uStack_1d0 = CONCAT44(uStack_1d0._4_4_,uStack_208._4_4_);
                    uStack_1b8 = CONCAT71(uStack_1b8._1_7_,*(undefined1 *)(param_1 + 0x30));
                    uStack_208 = uVar18;
                    uStack_1c8 = uVar15;
                    uStack_1c0 = uVar17;
                    if (*(char *)(param_1 + 0x58) == '\0') {
                      puVar19 = (undefined4 *)
                                Torappu_Battle_Enemy_get_options_0x6012a4d(auStack_d8,plVar23,0);
                      uVar12 = (undefined1)*puVar19;
                    }
                    else {
                      uVar12 = *(undefined1 *)(param_1 + 0x59);
                    }
                    uVar15 = uStack_1b8;
                    uStack_1b8._3_5_ = SUB85(uVar15,3);
                    uStack_1b8._0_3_ =
                         CONCAT12(*(undefined1 *)(param_1 + 0x6c),
                                  CONCAT11(uVar12,(undefined1)uStack_1b8));
                    lStack_1b0 = lStack_218;
                    func_0x00018048b9e0(&lStack_1b0);
                    uStack_1a8 = *(undefined8 *)(param_1 + 0x70);
                    uStack_1a0 = CONCAT44(uStack_1a0._4_4_,*(undefined4 *)(param_1 + 0x78));
                    uStack_1b8._0_4_ =
                         CONCAT13(*(undefined1 *)(param_1 + 0x6e),(undefined3)uStack_1b8);
                    func_0x00018048b9e0(&uStack_1a8);
                    lStack_198 = lVar16;
                    func_0x00018048b9e0(&lStack_198,lVar16);
                    uVar10 = uStack_188;
                    lVar1 = lStack_198;
                    uVar8 = uStack_1a0;
                    uVar7 = uStack_1a8;
                    lVar16 = lStack_1b0;
                    uVar6 = uStack_1b8;
                    uVar5 = uStack_1c0;
                    uVar4 = uStack_1c8;
                    uVar18 = uStack_1d0;
                    uVar17 = uStack_1d8;
                    plVar14 = plStack_1e0;
                    uVar15 = uStack_1e8;
                    uStack_190 = CONCAT71(uStack_190._1_7_,*(undefined1 *)(param_1 + 0x88));
                    uVar9 = uStack_190;
                    if (*(char *)(param_1 + 0x38) == '\0') {
                      lStack_218 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(plVar23,0);
                      plVar20 = (longlong *)
                                Torappu_Battle_VisualObject_get_worldPosition_0x601302d
                                          (&lStack_218,plVar23,0);
                      uVar27 = *(undefined4 *)(param_1 + 0x34);
                      uVar12 = *(undefined1 *)(param_1 + 0x2a);
                      lVar21 = *plVar20;
                      uStack_210 = (undefined4)plVar20[1];
                      if (*(int *)(_DAT_188893098 + 0xe0) == 0) {
                        func_0x00018048c140();
                      }
                      lStack_218 = lVar21;
                      lVar21 = Torappu_Battle_LitePhysicsUtil_FindNearestPassableTile_0x6012192
                                         (&lStack_218,uVar27,uVar12,0);
                      if (*(char *)(param_1 + 0x39) != '\0') {
                        if (*(longlong *)(lVar13 + 0x20) == 0) goto LAB_1810dd823;
                        uVar27 = Torappu_Blackboard_GetFloatOrDefault_0x6007871
                                           (*(longlong *)(lVar13 + 0x20),
                                            *(undefined8 *)(param_1 + 0x40),
                                            *(undefined4 *)(param_1 + 0x50),1,0);
                        if (*(longlong *)(lVar13 + 0x20) == 0) goto LAB_1810dd823;
                        Torappu_Blackboard_GetFloatOrDefault_0x6007871
                                  (*(longlong *)(lVar13 + 0x20),*(undefined8 *)(param_1 + 0x48),
                                   *(undefined4 *)(param_1 + 0x54),1,0);
                        *(undefined4 *)(param_1 + 0x54) = extraout_XMM0_Da;
                        *(undefined4 *)(param_1 + 0x50) = uVar27;
                      }
                      if (*(char *)(param_1 + 0x5a) == '\0') {
                        if (*(char *)(param_1 + 0x5b) != '\0') {
                          lVar21 = FUN_180005610(0x34,plVar23);
                        }
                        if (lVar21 == 0) goto LAB_1810dd823;
                        auStack_1f8[0] =
                             Torappu_Battle_VisualObject_get_gridPosition_0x6013030(lVar21,0);
                        if (*(int *)(_DAT_1888c4f88 + 0xe0) == 0) {
                          func_0x00018048c140();
                        }
                        lStack_218 = func_0x000182104010(auStack_1f8,0);
                      }
                      else if (*(char *)(param_1 + 0x5c) != '\0') {
                        lVar13 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                                           (param_4,*(undefined4 *)(param_1 + 0x60),0);
                        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                          func_0x00018048c140();
                        }
                        cVar11 = FUN_186b638d0(lVar13,0,0);
                        if (cVar11 != '\0') {
                          return 0;
                        }
                        if (lVar13 == 0) goto LAB_1810dd823;
                        lStack_218 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(lVar13,0)
                        ;
                      }
                      iVar3 = iStack_200;
                      if (0 < iStack_200) {
                        do {
                          if (*(char *)(param_1 + 100) != '\0') {
                            if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                              func_0x00018048c140();
                            }
                            lVar13 = Torappu_Battle_BattleController_get_randomImp_0x600fbd7(0);
                            if (lVar13 == 0) goto LAB_1810dd823;
                            uVar27 = FUN_18078faf0(lVar13,0,*(undefined4 *)(param_1 + 0x68),0);
                            if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                              func_0x00018048c140();
                            }
                            func_0x0001866fdad0(uVar27,0);
                          }
                          lVar13 = FUN_185337c50(_DAT_1888d3908);
                          if (lVar13 == 0) goto LAB_1810dd823;
                          Torappu_Battle_BattleController_get_scheduler_0x600fbf4(lVar13,0);
                          lVar13 = FUN_185337c50(_DAT_1888d3908);
                          if ((lVar13 == 0) ||
                             (lVar13 = Torappu_Battle_BattleController_get_scheduler_0x600fbf4
                                                 (lVar13,0), lVar13 == 0)) goto LAB_1810dd823;
                          uStack_178 = uVar15;
                          plStack_170 = plVar14;
                          uStack_168 = uVar17;
                          uStack_160 = uVar18;
                          uStack_158 = uVar4;
                          uStack_150 = uVar5;
                          uStack_148 = uVar6;
                          lStack_140 = lVar16;
                          uStack_138 = uVar7;
                          uStack_130 = uVar8;
                          lStack_128 = lVar1;
                          uStack_120 = uVar9;
                          uStack_118 = uVar10;
                          Torappu_Battle_Scheduler_SpawnSummonedEnemyTrackedInGameMode_0x60119b0
                                    (lVar13,&uStack_178,0);
                          if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                            func_0x00018048c140();
                          }
                          Torappu_Battle_BattleController_StartBattleCoroutine_0x600fce8
                                    (&lStack_218);
                          uVar24 = (int)plVar25 + 1;
                          plVar25 = (longlong *)(ulonglong)uVar24;
                        } while ((int)uVar24 < iVar3);
                      }
                      return 1;
                    }
                    lVar13 = FUN_185337c50(_DAT_1888d3908);
                    if (lVar13 != 0) {
                      uVar22 = Torappu_Battle_BattleController_get_scheduler_0x600fbf4(lVar13,0);
                      lVar13 = FUN_185337c50(_DAT_1888d3908);
                      if ((lVar13 != 0) &&
                         (lVar13 = Torappu_Battle_BattleController_get_scheduler_0x600fbf4(lVar13,0)
                         , lVar13 != 0)) {
                        uStack_178 = uVar15;
                        plStack_170 = plVar14;
                        uStack_168 = uVar17;
                        uStack_160 = uVar18;
                        uStack_158 = uVar4;
                        uStack_150 = uVar5;
                        uStack_148 = uVar6;
                        lStack_140 = lVar16;
                        uStack_138 = uVar7;
                        uStack_130 = uVar8;
                        lStack_128 = lVar1;
                        uStack_120 = uVar9;
                        uStack_118 = uVar10;
                        uVar15 = Torappu_Battle_Scheduler_SpawnSummonedEnemyTrackedInGameMode_0x60119b0
                                           (lVar13,&uStack_178,0);
                        if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                          func_0x00018048c140();
                        }
                        Torappu_Battle_BattleController_StartBattleCoroutine_0x600fce8
                                  (&lStack_218,uVar22,uVar15,0);
                        return 1;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
LAB_1810dd823:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar15 = (*pcVar2)();
      return uVar15;
    }
  }
  return 0;
}

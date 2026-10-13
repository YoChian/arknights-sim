/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 _SpawnSummonedEnemyTrackedInGameMode_d__129_MoveNext_0x6011a4b(longlong param_1)
{
  uint uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined8 uStackX_8;
  undefined4 uStackX_18;
  undefined4 uStackX_1c;
  uint uStack_78;
  int iStack_74;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  if (DAT_188c91b72 == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188924260);
    FUN_18048bf00(0x1888f7ea8);
    FUN_18048bf00(0x1888f8328);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888e0148);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c91b72 = '\x01';
  }
  lVar8 = *(longlong *)(param_1 + 0x20);
  uStackX_8 = 0;
  if (*(int *)(param_1 + 0x10) == 0) {
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    if (lVar8 != 0) {
      if (*(char *)(lVar8 + 0x110) == '\0') {
        return 0;
      }
      if (*(longlong *)(param_1 + 0x30) != 0) {
        uVar7 = Torappu_Battle_Enemy_get_originRoute_0x6012a80(*(longlong *)(param_1 + 0x30),0);
        *(undefined8 *)(param_1 + 0x90) = uVar7;
        func_0x00018048b9e0(param_1 + 0x90,uVar7);
        if ((char)*(undefined8 *)(param_1 + 0x84) == '\0') {
          if (*(longlong *)(param_1 + 0x30) == 0) goto LAB_18095022a;
          uVar5 = Torappu_Battle_Enemy_get_originCursorIndex_0x6012a81
                            (*(longlong *)(param_1 + 0x30),0);
        }
        else {
          uVar5 = (undefined4)((ulonglong)*(undefined8 *)(param_1 + 0x84) >> 0x20);
        }
        *(undefined4 *)(param_1 + 0x98) = uVar5;
        if (*(longlong *)(param_1 + 0x30) != 0) {
          *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(*(longlong *)(param_1 + 0x30) + 0x18);
          lVar8 = FUN_185337c50(_DAT_1888d3908);
          if ((lVar8 != 0) &&
             (lVar8 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar8,0), lVar8 != 0))
          {
            func_0x000180942250(lVar8,0);
            uVar7 = Torappu_Battle_AsyncUtil_WaitForFixedSeconds_0x600fa85
                              (*(undefined8 *)(param_1 + 0x50),0);
            *(undefined8 *)(param_1 + 0x18) = uVar7;
            func_0x00018048b9e0(param_1 + 0x18,uVar7);
            *(undefined4 *)(param_1 + 0x10) = 1;
            return 1;
          }
        }
      }
    }
    goto LAB_18095022a;
  }
  if (*(int *)(param_1 + 0x10) != 1) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  if (lVar8 == 0) goto LAB_18095022a;
  if (*(char *)(lVar8 + 0x110) != '\0') {
    if (*(char *)(param_1 + 0x5a) != '\0') {
      if (*(longlong *)(param_1 + 0x30) == 0) goto LAB_18095022a;
      if ((*(int *)(param_1 + 0x9c) != *(int *)(*(longlong *)(param_1 + 0x30) + 0x18)) ||
         (cVar3 = FUN_180005610(0x28,*(undefined8 *)(param_1 + 0x30)), cVar3 == '\0'))
      goto LAB_1809501c9;
    }
    iVar13 = *(int *)(lVar8 + 0x24) + 1;
    *(int *)(lVar8 + 0x24) = iVar13;
    uVar1 = *(uint *)(param_1 + 0x70);
    _uStack_78 = CONCAT44(iVar13,(uint)CONCAT21(0x100,*(undefined1 *)(param_1 + 0x59)));
    uStack_70 = 1;
    if (*(longlong *)(param_1 + 0x30) == 0) goto LAB_18095022a;
    bVar4 = Torappu_Battle_Entity_get_changeableMotionMode_0x6010347
                      (*(longlong *)(param_1 + 0x30),0);
    if (((int)(uVar1 & 1 << (bVar4 & 0x1f)) < 1) || (*(char *)(param_1 + 0x80) != '\0')) {
      if ((*(longlong *)(param_1 + 0x90) == 0) ||
         (lVar9 = *(longlong *)(*(longlong *)(param_1 + 0x90) + 0x18), lVar9 == 0))
      goto LAB_18095022a;
      lVar9 = Torappu_RouteData_Duplicate_0x6007b13(lVar9,0);
      if ((*(longlong *)(param_1 + 0x30) == 0) ||
         (iVar6 = Torappu_Battle_Entity_get_changeableMotionMode_0x6010347
                            (*(longlong *)(param_1 + 0x30),0), lVar9 == 0)) goto LAB_18095022a;
      *(uint *)(lVar9 + 0x10) = (uint)(iVar6 == 0);
      uVar7 = DisappearCheckpoint_GetNextDirection_0x601123e(0);
      uStackX_18 = (undefined4)uVar7;
      uStackX_1c = (undefined4)((ulonglong)uVar7 >> 0x20);
      *(undefined4 *)(lVar9 + 0x2c) = uStackX_18;
      *(undefined4 *)(lVar9 + 0x30) = uStackX_1c;
      *(undefined1 *)(lVar9 + 0x43) = 1;
      if (*(char *)(param_1 + 0x80) != '\0') {
        *(undefined8 *)(lVar9 + 0x38) = 0;
        func_0x00018048b9e0(lVar9 + 0x38,0);
        *(undefined1 *)(lVar9 + 0x43) = 0;
      }
    }
    else {
      if ((*(longlong *)(param_1 + 0x90) == 0) ||
         (lVar9 = *(longlong *)(*(longlong *)(param_1 + 0x90) + 0x18), lVar9 == 0))
      goto LAB_18095022a;
      lVar9 = Torappu_RouteData_Duplicate_0x6007b13(lVar9,0);
    }
    lVar10 = FUN_185337c50(_DAT_1888e0148);
    if (lVar10 == 0) goto LAB_18095022a;
    uVar7 = Torappu_Battle_Map_GenerateRuntimeRoute_0x601119c(lVar10,iVar13,lVar9,0);
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_58 = 0;
    uStack_50 = 0;
    lVar9 = Torappu_Battle_Scheduler__DoSpawnEnemyInternal_0x60119bb
                      (lVar8,*(undefined8 *)(param_1 + 0x28),uVar7,&uStack_78,0);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b638d0(lVar9,0,0);
    if (cVar3 != '\0') {
      return 0;
    }
    if ((lVar9 == 0) || (lVar10 = FUN_180005610(0xe0,lVar9), lVar10 == 0)) goto LAB_18095022a;
    Torappu_Battle_DirectionCursor_AssignHostRouteProgress_0x601127e
              (lVar10,*(undefined4 *)(param_1 + 0x98),0);
    if (*(char *)(param_1 + 0x58) == '\0') {
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      lVar10 = Torappu_Battle_BattleController_get_randomImp_0x600fbd7(0);
      uVar7 = *(undefined8 *)(param_1 + 0x48);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = Torappu_FP_op_UnaryNegation_0x6000308(uVar7,0);
      if (lVar10 == 0) goto LAB_18095022a;
      uVar7 = FUN_1808c8110(lVar10,uVar7,*(undefined8 *)(param_1 + 0x48),0);
      lVar10 = Torappu_Battle_BattleController_get_randomImp_0x600fbd7(0);
      uVar11 = Torappu_FP_op_UnaryNegation_0x6000308(*(undefined8 *)(param_1 + 0x48),0);
      if (lVar10 == 0) goto LAB_18095022a;
      uVar11 = FUN_1808c8110(lVar10,uVar11,*(undefined8 *)(param_1 + 0x48),0);
      uVar12 = func_0x0001866fdad0(*(undefined4 *)(param_1 + 0x3c),0);
      uStackX_8 = func_0x000184624db0(uVar12,uVar7,0);
      uVar5 = Torappu_FP_AsFloat_0x6000323(&uStackX_8,0);
      uVar7 = func_0x0001866fdad0(*(undefined4 *)(param_1 + 0x40),0);
      uStackX_8 = func_0x000184624db0(uVar7,uVar11,0);
      uVar14 = Torappu_FP_AsFloat_0x6000323(&uStackX_8,0);
      lVar10 = FUN_180005610(0xe0,lVar9);
      if ((lVar10 == 0) ||
         (lVar10 = Torappu_Battle_BasicCursor_get_route_0x6011208(lVar10,0), lVar10 == 0))
      goto LAB_18095022a;
      cVar3 = Torappu_Battle_Route_CheckReachable_0x60112e7(lVar10,CONCAT44(uVar14,uVar5),0);
      if (cVar3 != '\0') {
        *(undefined4 *)(param_1 + 0x3c) = uVar5;
        *(undefined4 *)(param_1 + 0x40) = uVar14;
      }
    }
    Torappu_Battle_Enemy_set_hostUid_0x6012a0a(lVar9,*(undefined4 *)(param_1 + 0x9c),0);
    if (*(char *)(param_1 + 0x38) != '\0') {
      if (*(char *)(param_1 + 0x39) == '\0') {
        if (*(longlong *)(lVar8 + 0xc0) == 0) goto LAB_18095022a;
        FUN_1805072d0(*(longlong *)(lVar8 + 0xc0),lVar9,_DAT_188924260);
      }
      if (*(longlong *)(lVar8 + 200) == 0) goto LAB_18095022a;
      FUN_1805072d0(*(longlong *)(lVar8 + 200),lVar9,_DAT_188924260);
    }
    Torappu_Battle_VisualObject_SetPosition_0x6013039(lVar9,*(undefined8 *)(param_1 + 0x3c),0);
    Torappu_Battle_Enemy_InitFaceTo_0x6012aba(lVar9,0);
    if (((*(char *)(param_1 + 0x5b) != '\0') && (*(longlong *)(param_1 + 0x60) != 0)) &&
       (*(longlong *)(param_1 + 0x68) != 0)) {
      Torappu_Battle_Entity_AddBuff_0x60103f2
                (lVar9,*(undefined8 *)(param_1 + 0x68),0,0,*(undefined8 *)(param_1 + 0x60),0,0,0,0);
    }
    if (*(longlong *)(param_1 + 0x78) != 0) {
      lVar8 = *(longlong *)(param_1 + 0x78);
      (**(code **)(lVar8 + 0x18))(*(undefined8 *)(lVar8 + 0x40),lVar9,*(undefined8 *)(lVar8 + 0x28))
      ;
    }
    lVar8 = FUN_185337c50(_DAT_1888d3908);
    if ((lVar8 == 0) ||
       (lVar8 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar8,0), lVar8 == 0))
    goto LAB_18095022a;
    FUN_1808fdfc0(lVar8,*(undefined8 *)(param_1 + 0x30),lVar9,0);
  }
LAB_1809501c9:
  lVar8 = FUN_185337c50(_DAT_1888d3908);
  if ((lVar8 != 0) &&
     (lVar8 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar8,0), lVar8 != 0)) {
    func_0x0001809421d0(lVar8,0);
    return 0;
  }
LAB_18095022a:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar7 = (*pcVar2)();
  return uVar7;
}

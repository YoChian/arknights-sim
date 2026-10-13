/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Enemy_OnTick_0x6012af4(longlong *param_1,undefined8 param_2)
{
  float fVar1;
  longlong lVar2;
  code *pcVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  int iVar12;
  undefined1 uVar13;
  float fVar14;
  undefined8 uStackX_20;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  if (DAT_188c928dc == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_18889bca8);
    FUN_18048bf00(0x188935958);
    FUN_18048bf00(&DAT_188935b98);
    DAT_188c928dc = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x820);
  if (lVar8 != 0) {
    if (cRam0000000188caf41c == '\0') {
      FUN_18048bf00(&DAT_18885a700,param_1,param_2,0);
      cRam0000000188caf41c = '\x01';
    }
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar10 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar12 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar2 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar2 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar2,uVar10,param_1,0);
          auStack_40[0] = param_2;
          uVar11 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
          FUN_183cfbf40(lVar2,uVar10,uVar11,0);
          iVar7 = FUN_183f22380(uVar10,2,0,iVar12,0);
          if (iVar7 == 0) {
code_r0x0001833f996e:
            FUN_183f22fd0(uVar10,iVar12 + -1,0);
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar12 + -1,0);
            goto code_r0x0001833f996e;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  Torappu_Battle_Unit_OnTick_0x6012f84(param_1,param_2,0);
  if (param_1[0x76] == 0) goto LAB_180a72bcd;
  HeightController_OnTick_0x6012c7d(param_1[0x76],param_2,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar6 = (**(code **)(*param_1 + 0x3c0))(param_1,*(undefined8 *)(*param_1 + 0x3c8));
  if (cVar6 == '\0') {
    Torappu_Battle_Enemy_OnTickAfterDead_0x6012af6(param_1,param_2,0);
    return;
  }
  cVar6 = Torappu_Battle_Entity_get_isBlockFree_0x60103d0(param_1,0);
  if (cVar6 != '\0') {
    Torappu_Battle_Enemy_ReleaseFromBlocker_0x6012acd(param_1,0);
  }
  cVar6 = Torappu_Battle_Enemy_get_canBlockEnemies_0x6012b10(param_1,0);
  if ((cVar6 != '\0') &&
     ((((cVar6 = Torappu_Battle_Entity_get_isBlockFree_0x60103d0(param_1,0), cVar6 != '\0' ||
        (cVar6 = Torappu_Battle_Entity_get_isStunned_0x60103b7(param_1,0), cVar6 != '\0')) ||
       (cVar6 = Torappu_Battle_Enemy_get_isUnbalanced_0x6012a31(param_1,0), cVar6 != '\0')) ||
      (cVar6 = Torappu_Battle_Entity_get_isLevitate_0x60103bb(param_1,0), cVar6 != '\0')))) {
    if (param_1[0xaf] == 0) goto LAB_180a72bcd;
    Torappu_Battle_BlockManager_ClearAllBlockees_0x6012d8d(param_1[0xaf],param_1,0);
  }
  cVar6 = Torappu_Battle_Enemy_get_canBlockEnemies_0x6012b10(param_1,0);
  if (cVar6 != '\0') {
    if (param_1[0xaf] == 0) goto LAB_180a72bcd;
    Torappu_Battle_BlockManager_Tick_0x6012d94(param_1[0xaf],param_2,0);
    if (param_1[0xaf] == 0) goto LAB_180a72bcd;
    Torappu_Battle_BlockManager_SearchBlockee_0x6012d87(param_1[0xaf],param_1,0,0);
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  lVar8 = (**(code **)(*param_1 + 0xf50))(param_1,*(undefined8 *)(*param_1 + 0xf58));
  if (DAT_188c928be == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c928be = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x730);
  if (lVar2 == 0) {
    cVar6 = Torappu_Battle_Entity_get_isFeared_0x60103c7(param_1,0);
    if (cVar6 == '\0') {
      cVar6 = Torappu_Battle_Entity_get_isAttracted_0x60103ca(param_1,0);
      uVar13 = cVar6 == '\0';
    }
    else {
      uVar13 = 0;
    }
  }
  else {
    uVar13 = XLua_DelegateBridge___Gen_Delegate_Imp3720_0x60018e8(lVar2,param_1,0,0);
  }
  if (lVar8 == 0) goto LAB_180a72bcd;
  Torappu_Battle_DirectionCursor_OnTick_0x6011290(lVar8,param_2,uVar13,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  plVar9 = (longlong *)(**(code **)(*param_1 + 0xf40))(param_1,*(undefined8 *)(*param_1 + 0xf48));
  if (plVar9 == (longlong *)0x0) goto LAB_180a72bcd;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar9);
  }
  cVar6 = (**(code **)(*plVar9 + 0x1d0))(plVar9,*(undefined8 *)(*plVar9 + 0x1d8));
  if (cVar6 != '\0') {
    if (DAT_188c928ba == '\0') {
      FUN_18048bf00(&DAT_18892ea20);
      FUN_18048bf00(&DAT_18881b6b0);
      FUN_18048bf00(&DAT_188932ce8);
      FUN_18048bf00(&DAT_1888d3908);
      FUN_18048bf00(&DAT_188971a40);
      FUN_18048bf00(&DAT_18880ecb0);
      DAT_188c928ba = '\x01';
    }
    if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18881b6b0);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x710);
    if (lVar8 == 0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      uVar10 = (**(code **)(*param_1 + 0x480))(param_1,*(undefined8 *)(*param_1 + 0x488));
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar6 = FUN_186b638d0(uVar10,0,0);
      if (cVar6 == '\0') {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar6 = (**(code **)(*param_1 + 0xea0))(param_1,*(undefined8 *)(*param_1 + 0xea8));
        if (cVar6 == '\0') {
          lVar8 = FUN_185337c50(_DAT_1888d3908);
          if (lVar8 == 0) goto LAB_180a72bcd;
          cVar6 = Torappu_Battle_BattleController_CheckEnemyCanExit_0x600fd3d(lVar8,param_1,0);
          goto LAB_180a727e1;
        }
      }
      else {
        uVar10 = Torappu_Battle_Entity_get_id_0x6010328(param_1,0);
        uVar10 = System_String_Concat_0x6000309(_DAT_188971a40,uVar10,_DAT_18880ecb0,0);
        if (*(int *)(_DAT_18892ea20 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        UnityEngine_DLog_LogError_0x6000031(uVar10,0);
      }
    }
    else {
      cVar6 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar8,param_1,0);
LAB_180a727e1:
      if (cVar6 != '\0') {
        lVar8 = Torappu_Battle_Enemy_get_stateMachine_0x6012a56(param_1,0);
        if (lVar8 != 0) {
          FUN_18499c9d0(lVar8,7,_DAT_18889bca8);
          FUN_1800053c0(0x75,param_1,1);
          return;
        }
        goto LAB_180a72bcd;
      }
    }
  }
  if (DAT_188c927e2 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c927e2 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x50);
  if (lVar8 == 0) {
    lVar8 = param_1[0x7b];
  }
  else {
    lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3693_0x60018cd(lVar8,param_1,0);
  }
  if (DAT_188c928be == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c928be = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x730);
  if (lVar2 == 0) {
    cVar6 = Torappu_Battle_Entity_get_isFeared_0x60103c7(param_1,0);
    if (cVar6 == '\0') {
      Torappu_Battle_Entity_get_isAttracted_0x60103ca(param_1,0);
      uVar13 = 0;
    }
    else {
      uVar13 = 1;
    }
  }
  else {
    uVar13 = XLua_DelegateBridge___Gen_Delegate_Imp3720_0x60018e8(lVar2,param_1,1,0);
  }
  if (lVar8 != 0) {
    func_0x000180a87060(lVar8,param_2,uVar13,0);
    if (DAT_188c927e3 == '\0') {
      FUN_18048bf00(&DAT_18881b6b0);
      DAT_188c927e3 = '\x01';
    }
    if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x58);
    if (lVar8 == 0) {
      lVar8 = param_1[0x7c];
    }
    else {
      lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3694_0x60018ce(lVar8,param_1,0);
    }
    if (DAT_188c928be == '\0') {
      FUN_18048bf00(&DAT_18881b6b0);
      DAT_188c928be = '\x01';
    }
    if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar2 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x730);
    if (lVar2 == 0) {
      cVar6 = Torappu_Battle_Entity_get_isFeared_0x60103c7(param_1,0);
      if (cVar6 == '\0') {
        cVar6 = Torappu_Battle_Entity_get_isAttracted_0x60103ca(param_1,0);
        uVar13 = cVar6 != '\0';
      }
      else {
        uVar13 = 0;
      }
    }
    else {
      uVar13 = XLua_DelegateBridge___Gen_Delegate_Imp3720_0x60018e8(lVar2,param_1,2,0);
    }
    if (lVar8 != 0) {
      func_0x000180a87060(lVar8,param_2,uVar13,0);
      if (param_1[0x72] != 0) {
        Torappu_Battle_MoveController_OnTick_0x6011598(param_1[0x72],param_2,0);
        Torappu_Battle_Enemy__UpdateCurrentTile_0x6012ad5(param_1,0,0);
        if (param_1[0x75] != 0) {
          cVar6 = func_0x000181e043d0(param_1[0x75],0);
          if (cVar6 != '\0') {
            if (param_1[0x75] == 0) goto LAB_180a72bcd;
            func_0x000181e04370(param_1[0x75],0);
            uVar10 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(param_1,0);
            fVar1 = *(float *)(param_1 + 0x69);
            uStackX_20._0_4_ = (float)uVar10;
            fVar4 = (float)uStackX_20;
            uStackX_20._4_4_ = (float)((ulonglong)uVar10 >> 0x20);
            fVar5 = uStackX_20._4_4_;
            uStackX_20 = CONCAT44(uStackX_20._4_4_ - *(float *)((longlong)param_1 + 0x414),
                                  (float)uStackX_20 - *(float *)(param_1 + 0x82));
            fVar14 = (float)FUN_180535480(&uStackX_20,0);
            *(float *)(param_1 + 0x82) = fVar4;
            *(float *)((longlong)param_1 + 0x414) = fVar5;
            *(float *)(param_1 + 0x69) = fVar14 + fVar1;
          }
          iVar12 = 0;
          if (param_1[0x9c] != 0) {
            iVar7 = *(int *)(param_1[0x9c] + 0x18);
            if (0 < iVar7) {
              do {
                if ((param_1[0x9c] == 0) ||
                   (lVar8 = FUN_184afcf00(param_1[0x9c],iVar12,_DAT_188935b98), lVar8 == 0))
                goto LAB_180a72bcd;
                cVar6 = Torappu_Battle_EnemySkill_get_isEnabled_0x60102df(lVar8,0);
                if (cVar6 != '\0') {
                  Torappu_Battle_EnemySkill_Tick_0x6010309(lVar8,param_2,0);
                }
                iVar12 = iVar12 + 1;
              } while (iVar12 < iVar7);
            }
            if (param_1[0x9d] != 0) {
              cVar6 = Torappu_PeriodicTimer_get_isValid_0x600656e(param_1[0x9d],0);
              if (cVar6 != '\0') {
                plVar9 = (longlong *)param_1[0x9d];
                if (plVar9 == (longlong *)0x0) goto LAB_180a72bcd;
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*plVar9);
                }
                cVar6 = (**(code **)(*plVar9 + 400))
                                  (plVar9,param_2,*(undefined8 *)(*plVar9 + 0x198));
                if (cVar6 != '\0') {
                  Torappu_Battle_Enemy_LogRuntimeSnapshotIfNot_0x6012ab2(param_1,0);
                }
              }
              return;
            }
          }
        }
      }
    }
  }
LAB_180a72bcd:
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

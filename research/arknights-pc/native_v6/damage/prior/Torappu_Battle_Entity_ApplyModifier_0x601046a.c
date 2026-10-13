/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
Torappu_Battle_Entity_ApplyModifier_0x601046a
          (longlong *param_1,undefined8 *param_2,undefined1 param_3)
{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  ushort uVar9;
  undefined8 uStack_138;
  undefined8 uStack_130;
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
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined8 uStack_b8;
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
  if (DAT_188c908f9 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00();
    DAT_188c908f9 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x968);
  if (lVar4 != 0) {
    uVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3066_0x600165a(lVar4,param_1,param_2,param_3,0);
    return uVar8;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar2 = (**(code **)(*param_1 + 0x3c0))(param_1,*(undefined8 *)(*param_1 + 0x3c8));
  if (cVar2 == '\0') {
    return 0;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_2,0);
  if (cVar2 != '\0') {
    return 0;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar4 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
  cVar2 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x80,0);
  if (cVar2 == '\0') {
    if (DAT_188c908fa == '\0') {
      FUN_18048bf00(&DAT_188841368);
      FUN_18048bf00(&DAT_188811960);
      FUN_18048bf00(&DAT_1888ed178);
      FUN_18048bf00(&DAT_1888d3908);
      DAT_188c908fa = '\x01';
    }
    if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188841368);
    }
    lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x970);
    if (lVar5 == 0) {
      lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
      if (lVar5 == 0) {
LAB_1806f074e:
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        uVar8 = (*pcVar1)();
        return uVar8;
      }
      BuffContainer_OnBeforeApplyingModifier_0x600ff62(lVar5,param_2,0);
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
      Torappu_Battle_Entity_EmitEvent_0x601049d(param_1,8,uVar8,0);
      lVar5 = FUN_185337c50(_DAT_1888d3908);
      if (lVar5 == 0) goto LAB_1806f074e;
      lVar5 = Torappu_Battle_BattleController_get_eventPool_0x600fbf9(lVar5,0);
      uStack_138 = *param_2;
      uStack_130 = param_2[1];
      uStack_128 = param_2[2];
      uStack_120 = param_2[3];
      uStack_118 = param_2[4];
      uStack_110 = param_2[5];
      uStack_108 = param_2[6];
      uStack_100 = param_2[7];
      uStack_f8 = param_2[8];
      uStack_f0 = param_2[9];
      uStack_e8 = param_2[10];
      uStack_e0 = param_2[0xb];
      uStack_d8 = param_2[0xc];
      uStack_d0 = param_2[0xd];
      uStack_c8 = *(undefined4 *)(param_2 + 0xe);
      uStack_c4 = *(undefined4 *)((longlong)param_2 + 0x74);
      uStack_c0 = *(undefined4 *)(param_2 + 0xf);
      uStack_bc = *(undefined4 *)((longlong)param_2 + 0x7c);
      uStack_b8 = param_2[0x10];
      uVar8 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_138);
      if (lVar5 == 0) goto LAB_1806f074e;
      FUN_1848dca60(lVar5,0xc,uVar8,_DAT_188811960);
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar5,param_1,param_2,0);
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_2,0);
    if (cVar2 != '\0') {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      iVar3 = Torappu_Battle_Modifier_get_cancelReason_0x601153a(param_2,0);
      if (iVar3 == 5) {
        return 0;
      }
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar4,0,0);
    if (cVar2 == '\0') goto LAB_1806f0457;
    if (lVar4 == 0) goto LAB_1806f0760;
    if (DAT_188c908ff == '\0') {
      FUN_18048bf00(&DAT_188841368);
      FUN_18048bf00(&DAT_1888ed178);
      DAT_188c908ff = '\x01';
    }
    if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188841368);
    }
    lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x998);
    if (lVar5 == 0) {
      lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar4,0);
      if (lVar5 == 0) {
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        uVar8 = (*pcVar1)();
        return uVar8;
      }
      BuffContainer_OnOutputModifier_0x600ff66(lVar5,param_2,0);
      uStack_138 = *param_2;
      uStack_130 = param_2[1];
      uStack_128 = param_2[2];
      uStack_120 = param_2[3];
      uStack_118 = param_2[4];
      uStack_110 = param_2[5];
      uStack_108 = param_2[6];
      uStack_100 = param_2[7];
      uStack_f8 = param_2[8];
      uStack_f0 = param_2[9];
      uStack_e8 = param_2[10];
      uStack_e0 = param_2[0xb];
      uStack_d8 = param_2[0xc];
      uStack_d0 = param_2[0xd];
      uStack_c8 = *(undefined4 *)(param_2 + 0xe);
      uStack_c4 = *(undefined4 *)((longlong)param_2 + 0x74);
      uStack_c0 = *(undefined4 *)(param_2 + 0xf);
      uStack_bc = *(undefined4 *)((longlong)param_2 + 0x7c);
      uStack_b8 = param_2[0x10];
      uVar8 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_138);
      Torappu_Battle_Entity_EmitEvent_0x601049d(lVar4,0xb,uVar8,0);
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = Torappu_Battle_Modifier_get_isDamage_0x6011530(param_2,0);
      if (cVar2 != '\0') {
        if (DAT_188c908fe == '\0') {
          FUN_18048bf00(&DAT_188841368);
          FUN_18048bf00(&DAT_1888ed178);
          DAT_188c908fe = '\x01';
        }
        if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
          func_0x00018048c140(_DAT_188841368);
        }
        lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x990);
        if (lVar5 != 0) goto LAB_1806f0449;
        lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar4,0);
        if (lVar5 == 0) {
          FUN_18048c0b0();
          pcVar1 = (code *)swi(3);
          uVar8 = (*pcVar1)();
          return uVar8;
        }
        BuffContainer_OnOutputDamage_0x600ff73(lVar5,param_2,0);
        uStack_138 = *param_2;
        uStack_130 = param_2[1];
        uStack_128 = param_2[2];
        uStack_120 = param_2[3];
        uStack_118 = param_2[4];
        uStack_110 = param_2[5];
        uStack_108 = param_2[6];
        uStack_100 = param_2[7];
        uStack_f8 = param_2[8];
        uStack_f0 = param_2[9];
        uStack_e8 = param_2[10];
        uStack_e0 = param_2[0xb];
        uStack_d8 = param_2[0xc];
        uStack_d0 = param_2[0xd];
        uStack_c8 = *(undefined4 *)(param_2 + 0xe);
        uStack_c4 = *(undefined4 *)((longlong)param_2 + 0x74);
        uStack_c0 = *(undefined4 *)(param_2 + 0xf);
        uStack_bc = *(undefined4 *)((longlong)param_2 + 0x7c);
        uStack_b8 = param_2[0x10];
        uVar8 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_138);
        Torappu_Battle_Entity_EmitEvent_0x601049d(lVar4,0xe,uVar8,0);
      }
    }
    else {
LAB_1806f0449:
      XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar5,lVar4,param_2,0);
    }
LAB_1806f0457:
    Torappu_Battle_Entity__OnApplyingModifier_0x601046c(param_1,param_2,param_3,0);
  }
  else {
    if (DAT_188c908fc == '\0') {
      FUN_18048bf00(&DAT_188841368);
      FUN_18048bf00(&DAT_1888ed178);
      DAT_188c908fc = '\x01';
    }
    if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188841368);
    }
    lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x980);
    if (lVar5 == 0) {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x8000,0);
      if (cVar2 != '\0') {
        if (*(char *)((longlong)param_1 + 0x26) == '\0') {
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
          cVar2 = Torappu_Battle_Entity_IsUnhurtableWithModifier_0x6010469(param_1,&uStack_a8,0);
          if (cVar2 == '\0') goto LAB_1806effc7;
        }
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        Torappu_Battle_Modifier_Cancel_0x6011549(param_2,0,0);
      }
LAB_1806effc7:
      lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
      if (lVar5 == 0) goto LAB_1806f0760;
      BuffContainer_OnApplyingSkippedModifier_0x600ff65(lVar5,param_2,0);
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar5,param_1,param_2,0);
    }
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_2,0);
  if (cVar2 == '\0') {
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b63a70(lVar4,0,0);
    if (cVar2 != '\0') {
      if (lVar4 == 0) goto LAB_1806f0760;
      if (DAT_188c90900 == '\0') {
        FUN_18048bf00(&DAT_188841368);
        DAT_188c90900 = '\x01';
      }
      if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_188841368);
      }
      lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x9a0);
      if (lVar5 == 0) {
        lVar4 = Torappu_Battle_Entity_get_buffContainer_0x6010363(lVar4,0);
        if (lVar4 == 0) goto LAB_1806f0760;
        BuffContainer_OnBeforeTargetApplyModifier_0x600ff67(lVar4,param_2,0);
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar5,lVar4,param_2,0);
      }
    }
    lVar4 = FUN_185337c50(_DAT_1888d3908);
    if ((lVar4 == 0) ||
       (plVar6 = (longlong *)Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar4,0),
       lVar4 = _DAT_188961dd0, plVar6 == (longlong *)0x0)) {
LAB_1806f0760:
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      uVar8 = (*pcVar1)();
      return uVar8;
    }
    switch(*(undefined4 *)(*plVar6 + 0x11c)) {
    case 0x9b7:
    case 0x9b8:
    case 0x9b9:
    case 0x9ba:
    case 0x9bc:
    case 0x9bf:
    case 0x9c0:
    case 0x9c1:
    case 0x9c2:
    case 0x9c3:
    case 0x9c4:
    case 0x9c5:
    case 0x9c6:
    case 0x9c7:
    case 0x9c8:
    case 0x9c9:
    case 0x9ca:
    case 0x9cb:
    case 0x9cc:
    case 0x9cd:
    case 0x9ce:
    case 0x9cf:
    case 0x9d0:
    case 0x9d1:
      cVar2 = DefaultGameMode_OnEntityApplyModifier_0x6014138(plVar6,param_1,param_2,0);
      break;
    case 0x9bb:
      cVar2 = Act7FunGameMode_OnEntityApplyModifier_0x6013b9f(plVar6,param_1,param_2,0);
      break;
    case 0x9bd:
      cVar2 = ArkDexGameMode_OnEntityApplyModifier_0x6013c1b(plVar6,param_1,param_2,0);
      break;
    case 0x9be:
      cVar2 = AutoChessGameMode_OnEntityApplyModifier_0x6013c70(plVar6,param_1,param_2,0);
      break;
    default:
      lVar5 = *plVar6;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00();
      }
      uVar9 = 0;
      if (*(ushort *)(lVar5 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar9 * 0x10) == lVar4) {
            puVar7 = (undefined8 *)
                     (((longlong)
                       (*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar9 * 0x10) + 0x58)
                      + 0x14) * 0x10 + lVar5);
            goto LAB_1806f0659;
          }
          uVar9 = uVar9 + 1;
        } while (uVar9 < *(ushort *)(lVar5 + 0x12e));
      }
      puVar7 = (undefined8 *)FUN_180445cc0(plVar6,lVar4,0x58);
LAB_1806f0659:
      cVar2 = (*(code *)*puVar7)(plVar6,param_1,param_2,puVar7[1]);
    }
    if (cVar2 != '\0') {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      cVar2 = (**(code **)(*param_1 + 0x900))
                        (param_1,param_2,param_3,*(undefined8 *)(*param_1 + 0x908));
      if (cVar2 != '\0') {
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar2 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x80,0);
        if (cVar2 == '\0') {
          Torappu_Battle_Entity_OnAppliedModifier_0x601046e(param_1,param_2,0);
        }
        return 1;
      }
    }
  }
  return 0;
}

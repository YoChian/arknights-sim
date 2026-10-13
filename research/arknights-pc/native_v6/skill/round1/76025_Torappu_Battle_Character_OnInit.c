
/* WARNING: Removing unreachable block (ram,0x000180a38470) */
/* WARNING: Removing unreachable block (ram,0x0001836501b1) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_OnInit_0x60128fa(longlong param_1,float param_2)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  uint uVar10;
  int iVar11;
  longlong lVar12;
  undefined4 uVar13;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined *puStack_80;
  undefined8 auStack_58 [2];
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  
  if (DAT_188c92633 == '\0') {
    uStack_40 = 0x180a2ddb6;
    FUN_18048bf00(&DAT_18886c268);
    uStack_40 = 0x180a2ddc2;
    FUN_18048bf00(&DAT_18885a700);
    uStack_40 = 0x180a2ddce;
    FUN_18048bf00(&DAT_188932ce8);
    uStack_40 = 0x180a2ddda;
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c92633 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    uStack_40 = 0x180a2ddf9;
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x688);
  if (lVar6 != 0) {
    if (*(longlong *)(lVar6 + 0x18) == 0) {
      puStack_80 = &UNK_18365021c;
      FUN_18048c0b0(lVar6,param_1,param_2,0);
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_80 = &UNK_183650105;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      uVar7 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
      puStack_80 = &UNK_183650128;
      iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
      if (*(longlong *)(lVar6 + 0x18) != 0) {
        lVar12 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
        if (lVar12 == 0) {
          puStack_80 = &UNK_183650200;
          FUN_18048c0b0();
        }
        else {
          puStack_80 = &UNK_183650152;
          FUN_183cf8c20(lVar12,uVar7,param_1,0);
          puStack_80 = &UNK_183650164;
          FUN_183f22700(uVar7,SUB84((double)param_2,0),0);
          auStack_58[0] = 0;
          puStack_80 = &UNK_183650180;
          iVar11 = FUN_183f22380(uVar7,2,0,iVar5);
          if (iVar11 == 0) {
code_r0x000183650198:
            puStack_80 = &UNK_1836501a6;
            FUN_183f22fd0(uVar7,iVar5 + -1,0);
            return;
          }
          if (*(longlong *)(lVar6 + 0x18) != 0) {
            puStack_80 = &UNK_183650198;
            FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar5 + -1,0);
            goto code_r0x000183650198;
          }
        }
        puStack_80 = &UNK_183650206;
        FUN_18048c0b0();
      }
      puStack_80 = &UNK_18365020b;
      FUN_18048c0b0();
    }
    puStack_80 = &UNK_183650210;
    FUN_18048c0b0();
    puStack_80 = &UNK_183650216;
    FUN_180472d50();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  uStack_40 = 0x180a2de25;
  Torappu_Battle_Unit_OnInit_0x6012f62(param_1,param_2,0);
  if (DAT_188c925a4 == '\0') {
    uStack_40 = 0x180a2de3a;
    FUN_18048bf00(&DAT_18886c268);
    DAT_188c925a4 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    uStack_40 = 0x180a2de59;
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x210);
  if (lVar6 == 0) {
    uStack_40 = 0x180a2de8c;
    cVar3 = Torappu_Battle_Character_get_isBuiltPredefined_0x601286a(param_1,0);
    if (cVar3 == '\0') {
      uStack_40 = 0x180a2de9a;
      lVar6 = Torappu_Battle_Character_get_data_0x6012883(param_1,0);
      if (lVar6 != 0) {
        uStack_40 = 0x180a2dea9;
        lVar6 = Torappu_Battle_Character_get_data_0x6012883(param_1,0);
        if (lVar6 == 0) goto LAB_180a2e0d2;
        cVar3 = *(char *)(lVar6 + 0x91) == '\0';
        goto LAB_180a2dec9;
      }
    }
LAB_180a2decd:
    uStack_40 = 0x180a2ded9;
    lVar6 = FUN_185337c50(_DAT_1888d3908);
    uStack_40 = 0x180a2dee6;
    uVar7 = Torappu_Battle_Character_get_characterId_0x6012838(param_1,0);
    if (lVar6 == 0) goto LAB_180a2e0d2;
    uStack_40 = 0x180a2defd;
    cVar3 = Torappu_Battle_BattleController_IsPredefinedAndNeedToTakeSnapshot_0x600fcb1
                      (lVar6,uVar7,0);
    if (cVar3 != '\0') goto LAB_180a2df01;
  }
  else {
    uStack_40 = 0x180a2dec9;
    cVar3 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar6,param_1,0);
LAB_180a2dec9:
    if (cVar3 == '\0') goto LAB_180a2decd;
LAB_180a2df01:
    lVar6 = *(longlong *)(param_1 + 0x3b0);
    if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
      uStack_40 = 0x180a2df1d;
      func_0x00018048c140();
    }
    uStack_40 = 0x180a2df3c;
    uVar13 = func_0x000186732bd0(**(undefined4 **)(_DAT_18886c268 + 0xb8),
                                 (*(undefined4 **)(_DAT_18886c268 + 0xb8))[1],0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      uStack_40 = 0x180a2df54;
      func_0x00018048c140();
    }
    uStack_40 = 0x180a2df5e;
    uVar7 = func_0x0001866fdad0(uVar13,0);
    if (lVar6 == 0) goto LAB_180a2e0d2;
    uStack_40 = 0x180a2df78;
    Torappu_PeriodicTimer_Reset_0x6006576(lVar6,uVar7,1,0);
  }
  uVar7 = *(undefined8 *)(param_1 + 0x3c0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    uStack_40 = 0x180a2df94;
    func_0x00018048c140();
  }
  uStack_40 = 0x180a2dfa1;
  cVar3 = FUN_186b63a70(uVar7,0,0);
  if (cVar3 != '\0') {
    plVar1 = *(longlong **)(param_1 + 0x3c0);
    if (plVar1 == (longlong *)0x0) goto LAB_180a2e0d2;
    if (DAT_188ccc7f0 != '\0') {
      uStack_40 = 0x180a2dfc6;
      func_0x000180446d00(*plVar1);
    }
    uStack_40 = 0x180a2dfdc;
    (**(code **)(*plVar1 + 0x500))(plVar1);
  }
  uVar10 = 0;
  uStack_40 = 0x180a2dfea;
  lVar6 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1);
  if (lVar6 != 0) {
    lVar12 = 0x20;
    do {
      if (*(int *)(lVar6 + 0x18) <= (int)uVar10) {
        if (cRam0000000188c92634 == '\0') {
          FUN_18048bf00(&DAT_18886c268,0,0);
          FUN_18048bf00(0x1888c46e8);
          FUN_18048bf00(0x1888f4550);
          FUN_18048bf00(0x1888f0fa0);
          cRam0000000188c92634 = '\x01';
        }
        uStack_c8 = 0;
        uStack_c0 = 0;
        uStack_b8 = 0;
        uStack_b0 = 0;
        uStack_a8 = 0;
        uStack_a0 = 0;
        if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
          func_0x00018048c140(_DAT_18886c268);
        }
        lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x690);
        if (lVar6 != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp26_0x6000a7a(lVar6,param_1,0,0);
          return;
        }
        if (*(longlong *)(param_1 + 0x448) == 0) {
          return;
        }
        if (*(longlong *)(param_1 + 0x450) == 0) {
          return;
        }
        iVar11 = 0;
        iVar5 = FUN_1844afc00(*(undefined8 *)(param_1 + 0x448),uRam00000001888c46e8);
        if (iVar5 < 1) {
          return;
        }
        goto code_r0x000180a383c0;
      }
      uStack_40 = 0x180a2e013;
      lVar6 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
      if (lVar6 == 0) break;
      if (*(uint *)(lVar6 + 0x18) <= uVar10) {
        uStack_40 = 0x180a2e0dd;
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      lVar6 = *(longlong *)(lVar12 + lVar6);
      uStack_40 = 0x180a2e033;
      Torappu_Battle_Unit_get_currentMode_0x6012ef4(param_1,0);
      if (lVar6 == 0) break;
      uStack_40 = 0x180a2e04a;
      cVar3 = Torappu_Battle_BasicTalent_CheckRootOrValidModeTalent_0x6011e62(lVar6);
      if (cVar3 != '\0') {
        uStack_40 = 0x180a2e058;
        cVar3 = Torappu_Battle_Unit_get_isDummy_0x6012f2b(param_1,0);
        if (cVar3 != '\0') {
          uStack_40 = 0x180a2e069;
          cVar3 = FUN_180005610(7);
          if (cVar3 == '\0') goto LAB_180a2e07b;
        }
        uStack_40 = 0x180a2e07b;
        Torappu_Battle_BasicTalent_Attach_0x6011e59(lVar6);
      }
LAB_180a2e07b:
      uVar10 = uVar10 + 1;
      lVar12 = lVar12 + 8;
      uStack_40 = 0x180a2e08d;
      lVar6 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1);
    } while (lVar6 != 0);
  }
LAB_180a2e0d2:
  uStack_40 = 0x180a2e0d7;
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
code_r0x000180a383c0:
  lVar6 = lRam00000001888f4550;
  plVar1 = *(longlong **)(param_1 + 0x448);
  if (plVar1 == (longlong *)0x0) {
DAT_180a38599:
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  lVar12 = *plVar1;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(lVar12);
  }
  uVar4 = 0;
  if (*(ushort *)(lVar12 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar12 + 0xb0) + (ulonglong)uVar4 * 0x10) == lVar6) {
        puVar8 = (undefined8 *)
                 (((longlong)*(int *)(*(longlong *)(lVar12 + 0xb0) + 8 + (ulonglong)uVar4 * 0x10) +
                  0x14) * 0x10 + lVar12);
        goto code_r0x000180a38436;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(ushort *)(lVar12 + 0x12e));
  }
  puVar8 = (undefined8 *)FUN_180445cc0(plVar1,lVar6,0);
code_r0x000180a38436:
  puVar8 = (undefined8 *)(*(code *)*puVar8)(auStack_58,plVar1,iVar11,puVar8[1]);
  uStack_c8 = *puVar8;
  uStack_c0 = puVar8[1];
  uStack_b8 = puVar8[2];
  uStack_b0 = puVar8[3];
  uStack_a8 = puVar8[4];
  uStack_a0 = puVar8[5];
  if (((*(char *)(puVar8 + 3) == '\0') || ((*(byte *)(param_1 + 0x4e8) & 1) == 0)) &&
     ((cVar3 = Torappu_Battle_Unit_get_isDummy_0x6012f2b(param_1,0), cVar3 == '\0' ||
      (cVar3 = FUN_1806db130(&uStack_c8,0), cVar3 != '\0')))) {
    uStack_98 = (undefined4)uStack_a8;
    uStack_94 = uStack_a8._4_4_;
    uStack_90 = (undefined4)uStack_a0;
    uStack_8c = uStack_a0._4_4_;
    if (*(longlong *)(param_1 + 0x450) == 0) goto DAT_180a38599;
    uVar7 = FUN_180004e80(0,uRam00000001888f0fa0,*(longlong *)(param_1 + 0x450),iVar11);
    uVar9 = FUN_1806db260(&uStack_c8,0);
    FUN_1806ef4a0(param_1,CONCAT44(uStack_94,uStack_98),0,0,uVar7,0,0,uVar9,0);
  }
  iVar11 = iVar11 + 1;
  if (iVar5 <= iVar11) {
    return;
  }
  goto code_r0x000180a383c0;
}


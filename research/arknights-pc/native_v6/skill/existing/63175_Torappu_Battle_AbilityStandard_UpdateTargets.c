
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_Battle_AbilityStandard_UpdateTargets_0x600f6c8(longlong *param_1,byte param_2)

{
  longlong *plVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  byte bVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  longlong *plVar9;
  undefined8 uVar10;
  longlong lVar11;
  int iVar12;
  longlong lStack_108;
  longlong *plStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  longlong lStack_e8;
  longlong *plStack_d0;
  longlong lStack_c8;
  longlong lStack_c0;
  longlong lStack_b8;
  longlong lStack_b0;
  longlong alStack_a8 [2];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  longlong *plStack_80;
  longlong lStack_78;
  longlong lStack_70;
  
  plStack_d0 = param_1;
  if (DAT_188c8fd46 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_1888c4f88);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_18885a150);
    FUN_18048bf00(0x18885a388);
    FUN_18048bf00(0x18885a5b8);
    FUN_18048bf00(&DAT_1888e2bf0);
    FUN_18048bf00(0x1888e3070);
    FUN_18048bf00(&DAT_1888e32b0);
    FUN_18048bf00(&DAT_1888e3bb0);
    FUN_18048bf00(0x188938898);
    FUN_18048bf00(0x1888e4030);
    FUN_18048bf00(&DAT_188938ad8);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_1889357e8);
    FUN_18048bf00(&DAT_18896e2a0);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c8fd46 = '\x01';
  }
  lStack_78 = 0;
  lStack_70 = 0;
  iVar12 = 0;
  lStack_c8 = 0;
  lStack_c0 = 0;
  lStack_b8 = 0;
  alStack_a8[0] = 0;
  uStack_88 = 0;
  lVar11 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 400);
  if (lVar11 != 0) {
    uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp87_0x6000ab7(lVar11,param_1,param_2,0);
    return (bool)uVar7;
  }
  lStack_78 = param_1[0x1d];
  lStack_70 = param_1[0x1e];
  plVar9 = (longlong *)FUN_185159d80(&lStack_78,_DAT_1889355a8);
  plStack_80 = plVar9;
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  bVar5 = FUN_186b63a70(plVar9,0,0);
  if ((param_2 & bVar5) != 0) {
    if (plVar9 != (longlong *)0x0) {
      uVar10 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(plVar9,0);
      uStack_f8 = 0;
      uStack_f0 = 0;
      lStack_e8 = 0;
      lStack_108 = param_1[0x1d];
      plStack_100 = (longlong *)param_1[0x1e];
      func_0x000184a62fb0(&uStack_f8,uVar10,&lStack_108,_DAT_18885a150);
      *(undefined4 *)(param_1 + 0x1c) = (undefined4)uStack_f8;
      *(undefined4 *)((longlong)param_1 + 0xe4) = uStack_f8._4_4_;
      *(undefined4 *)(param_1 + 0x1d) = (undefined4)uStack_f0;
      *(undefined4 *)((longlong)param_1 + 0xec) = uStack_f0._4_4_;
      param_1[0x1e] = lStack_e8;
      func_0x00018048b9e0(param_1 + 0x1d,0);
      goto LAB_1805d35e3;
    }
    FUN_18048c0b0();
LAB_1805d3e03:
    FUN_18048c0b0();
LAB_1805d3e09:
    FUN_18048c0b0();
    FUN_180472d50();
LAB_1805d3e15:
    FUN_18048c0b0();
LAB_1805d3e1a:
    FUN_18048c0b0();
    FUN_180472d50();
LAB_1805d3e26:
    FUN_18048c0b0();
LAB_1805d3e2b:
    FUN_18048c0b0();
    FUN_180472d50();
LAB_1805d3e37:
    FUN_18048c0b0();
LAB_1805d3e3c:
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar2 = (code *)swi(3);
    uVar7 = (*pcVar2)();
    return (bool)uVar7;
  }
LAB_1805d35e3:
  plVar1 = param_1 + 0x1c;
  lStack_b0 = *plVar1;
  lVar4 = *plVar1;
  lVar3 = *plVar1;
  lVar11 = param_1[0x1b];
  if (lVar11 == 0) goto LAB_1805d3e48;
  *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
  iVar8 = *(int *)(lVar11 + 0x18);
  *(undefined4 *)(lVar11 + 0x18) = 0;
  if (0 < iVar8) {
    System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar11 + 0x10),0,iVar8,0);
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  iVar8 = (**(code **)(*param_1 + 0x580))(param_1,*(undefined8 *)(*param_1 + 0x588));
  if (iVar8 == 0) {
    return true;
  }
  if (iVar8 == 1) {
    uVar10 = FUN_180005610(0xf,param_1);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(uVar10,0,0);
    if ((cVar6 != '\0') && (cVar6 = FUN_185159fc0(param_1 + 10,_DAT_1889357e8), cVar6 != '\0')) {
      lVar11 = FUN_180005610(0xf,param_1);
      uVar10 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
      if (lVar11 == 0) goto LAB_1805d3e48;
      lStack_b8 = Torappu_Battle_TargetSelector_FindTargets_DISPOSE_0x6012555(lVar11,uVar10,0);
      lStack_108 = 0;
      plStack_100 = &lStack_b8;
      while (lStack_b8 != 0) {
        if (*(int *)(lStack_b8 + 0x18) <= iVar12) {
          if (lStack_b8 != 0) {
            FUN_180005310(0,_DAT_188954c98,lStack_b8);
          }
          goto LAB_1805d3c2d;
        }
        lVar11 = param_1[0x1b];
        uVar10 = FUN_184afcf00(lStack_b8,iVar12,_DAT_188938ad8);
        FUN_1845638c0(&uStack_f8,uVar10,_DAT_18896e2a0);
        if (lVar11 == 0) goto LAB_1805d3e26;
        uStack_98 = (undefined4)uStack_f8;
        uStack_94 = uStack_f8._4_4_;
        uStack_90 = (undefined4)uStack_f0;
        uStack_8c = uStack_f0._4_4_;
        FUN_180007100(lVar11,&uStack_98,_DAT_1888e2bf0);
        iVar12 = iVar12 + 1;
      }
      goto LAB_1805d3e2b;
    }
  }
  else if (iVar8 == 2) {
    uVar10 = FUN_180005610(0xf,param_1);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(uVar10,0,0);
    if (cVar6 != '\0') {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar6 = FUN_186b63a70(plVar9,0,0);
      if (cVar6 != '\0') {
        lVar11 = FUN_180005610(0xf,param_1);
        if (lVar11 == 0) goto LAB_1805d3e48;
        lStack_c0 = Torappu_Battle_TargetSelector_FindTargets_DISPOSE_0x6012555(lVar11,plVar9,0);
        lStack_108 = 0;
        plStack_100 = &lStack_c0;
        while (lStack_c0 != 0) {
          if (*(int *)(lStack_c0 + 0x18) <= iVar12) {
            if (lStack_c0 != 0) {
              FUN_180005310(0,_DAT_188954c98,lStack_c0);
            }
            goto LAB_1805d3c2d;
          }
          lVar11 = param_1[0x1b];
          uVar10 = FUN_184afcf00(lStack_c0,iVar12,_DAT_188938ad8);
          FUN_1845638c0(&uStack_f8,uVar10,_DAT_18896e2a0);
          if (lVar11 == 0) goto LAB_1805d3e15;
          uStack_98 = (undefined4)uStack_f8;
          uStack_94 = uStack_f8._4_4_;
          uStack_90 = (undefined4)uStack_f0;
          uStack_8c = uStack_f0._4_4_;
          FUN_180007100(lVar11,&uStack_98,_DAT_1888e2bf0);
          iVar12 = iVar12 + 1;
        }
        goto LAB_1805d3e1a;
      }
    }
  }
  else if (iVar8 == 3) {
    uVar10 = FUN_180005610(0xf,param_1);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(uVar10,0,0);
    if (cVar6 != '\0') {
      lVar11 = FUN_180005610(0xf,param_1);
      if (lVar11 == 0) goto LAB_1805d3e48;
      lStack_b0 = lVar3;
      lStack_c8 = Torappu_Battle_TargetSelector_FindTargets_DISPOSE_0x6012556(lVar11,lVar4,0);
      lStack_108 = 0;
      plStack_100 = &lStack_c8;
      while (lStack_c8 != 0) {
        if (*(int *)(lStack_c8 + 0x18) <= iVar12) {
          if (lStack_c8 != 0) {
            FUN_180005310(0,_DAT_188954c98,lStack_c8);
          }
          goto LAB_1805d3c2d;
        }
        lVar11 = param_1[0x1b];
        uVar10 = FUN_184afcf00(lStack_c8,iVar12,_DAT_188938ad8);
        FUN_1845638c0(&uStack_98,uVar10,_DAT_18896e2a0);
        if (lVar11 == 0) goto LAB_1805d3e03;
        uStack_f8 = CONCAT44(uStack_94,uStack_98);
        uStack_f0 = CONCAT44(uStack_8c,uStack_90);
        FUN_180007100(lVar11,&uStack_f8,_DAT_1888e2bf0);
        iVar12 = iVar12 + 1;
      }
      goto LAB_1805d3e09;
    }
  }
  else if (iVar8 == 4) {
    uVar10 = FUN_180005610(0xf,param_1);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(uVar10,0,0);
    if (cVar6 != '\0') {
      lVar11 = FUN_180005610(0xf,param_1);
      if (*(int *)(_DAT_1888c4f88 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uStack_88 = Torappu_GridPosition_FromVectorPosition_0x6006d90(lStack_b0,0);
      uVar10 = func_0x000182104010(&uStack_88,0);
      if (lVar11 == 0) goto LAB_1805d3e48;
      alStack_a8[0] = Torappu_Battle_TargetSelector_FindTargets_DISPOSE_0x6012556(lVar11,uVar10,0);
      lStack_108 = 0;
      plStack_100 = alStack_a8;
      while (alStack_a8[0] != 0) {
        if (*(int *)(alStack_a8[0] + 0x18) <= iVar12) {
          if (alStack_a8[0] != 0) {
            FUN_180005310(0,_DAT_188954c98,alStack_a8[0]);
          }
          goto LAB_1805d3c2d;
        }
        lVar11 = param_1[0x1b];
        uVar10 = FUN_184afcf00(alStack_a8[0],iVar12,_DAT_188938ad8);
        FUN_1845638c0(&uStack_f8,uVar10,_DAT_18896e2a0);
        if (lVar11 == 0) goto LAB_1805d3e37;
        uStack_98 = (undefined4)uStack_f8;
        uStack_94 = uStack_f8._4_4_;
        uStack_90 = (undefined4)uStack_f0;
        uStack_8c = uStack_f0._4_4_;
        FUN_180007100(lVar11,&uStack_98,_DAT_1888e2bf0);
        iVar12 = iVar12 + 1;
      }
      goto LAB_1805d3e3c;
    }
  }
LAB_1805d3c2d:
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar6 = (**(code **)(*param_1 + 0x5a0))(param_1,*(undefined8 *)(*param_1 + 0x5a8));
  if (cVar6 != '\0') {
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(plVar9,0,0);
    if (cVar6 != '\0') {
      if (plVar9 == (longlong *)0x0) goto LAB_1805d3e48;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar9);
      }
      cVar6 = (**(code **)(*plStack_80 + 0x3c0))(plVar9,*(undefined8 *)(*plStack_80 + 0x3c8));
      if (cVar6 != '\0') {
        lVar11 = param_1[0x1b];
        FUN_1845638c0(&uStack_f8,plVar9,_DAT_18896e2a0);
        if (lVar11 == 0) goto LAB_1805d3e48;
        cVar6 = FUN_184bae520(lVar11,&uStack_f8,_DAT_1888e32b0);
        if (cVar6 == '\0') {
          lVar11 = param_1[0x1b];
          if (lVar11 == 0) goto LAB_1805d3e48;
          if (0 < *(int *)(lVar11 + 0x18)) {
            FUN_184acd910(lVar11,*(int *)(lVar11 + 0x18) + -1,_DAT_1888e3bb0);
          }
          lVar11 = param_1[0x1b];
          FUN_1845638c0(&uStack_f8,plVar9,_DAT_18896e2a0);
          if (lVar11 == 0) goto LAB_1805d3e48;
          FUN_180007100(lVar11,&uStack_f8,_DAT_1888e2bf0);
        }
      }
    }
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar6 = (**(code **)(*param_1 + 0x260))(param_1,*(undefined8 *)(*param_1 + 0x268));
  if (cVar6 != '\0') {
    return true;
  }
  if (param_1[0x1b] != 0) {
    return 0 < *(int *)(param_1[0x1b] + 0x18);
  }
LAB_1805d3e48:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar7 = (*pcVar2)();
  return (bool)uVar7;
}


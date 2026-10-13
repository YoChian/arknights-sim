
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BornState_OnTick_0x601297d(longlong param_1,undefined8 param_2)

{
  undefined4 uVar1;
  longlong *plVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong *plVar11;
  undefined8 uStackX_20;
  undefined8 *puStack_20;
  
  if (DAT_188c92774 == '\0') {
    FUN_18048bf00(&DAT_1888771f8);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188956960);
    DAT_188c92774 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_1888771f8 + 0xb8) + 8);
  if (lVar8 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b(lVar8,param_1,param_2,0);
    return;
  }
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar8 == 0) goto LAB_180a66624;
  if (0.0 < *(float *)(lVar8 + 0x50c)) {
    lVar8 = FUN_18536e540(param_1,_DAT_188956960);
    if (lVar8 == 0) goto LAB_180a66624;
    uVar1 = *(undefined4 *)(lVar8 + 0x50c);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar9 = func_0x0001866fdad0(uVar1,0);
    *(undefined8 *)(param_1 + 0x18) = uVar9;
    lVar8 = FUN_18536e540(param_1,_DAT_188956960);
    if (lVar8 == 0) goto LAB_180a66624;
    *(undefined4 *)(lVar8 + 0x50c) = 0xbf800000;
  }
  uVar9 = *(undefined8 *)(param_1 + 0x18);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar9 = func_0x0001866fba10(uVar9,param_2,0);
  *(undefined8 *)(param_1 + 0x18) = uVar9;
  uVar10 = func_0x0001866fdac0(0,0);
  cVar5 = func_0x000185ed91e0(uVar9,uVar10,0);
  if (cVar5 == '\0') {
    return;
  }
  if (DAT_188c92776 == '\0') {
    FUN_18048bf00(&DAT_1888771f8);
    FUN_18048bf00(&DAT_188956720);
    FUN_18048bf00(&DAT_188956960);
    DAT_188c92776 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_1888771f8 + 0xb8) + 0x18);
  if (lVar8 != 0) {
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    puStack_20 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar9 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar7 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar3 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar3 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar3,uVar9,param_1,0);
          iVar6 = FUN_183f22380(uVar9,1,0,iVar7,0);
          if (iVar6 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar9,iVar7 + -1,0);
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar7 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  plVar11 = (longlong *)FUN_18536e540(param_1,_DAT_188956960);
  if (plVar11 == (longlong *)0x0) {
LAB_180a66624:
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar11);
  }
  (**(code **)(*plVar11 + 0x8b0))(plVar11,*(undefined8 *)(*plVar11 + 0x8b8));
  cVar5 = BasicState_ShouldSwitchToAbnormalState_0x601297a(param_1,1,0);
  if (cVar5 != '\0') {
    return;
  }
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar8 == 0) goto LAB_180a66624;
  cVar5 = Torappu_Battle_Entity_get_isDialogTarget_0x60103e3(lVar8,0);
  lVar8 = _DAT_188956720;
  uVar9 = 0xc;
  if (cVar5 == '\0') {
    uVar9 = 1;
  }
  plVar11 = *(longlong **)(param_1 + 0x10);
  if (plVar11 == (longlong *)0x0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(longlong *)
       (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18) + 0x20) ==
      0) {
    (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18))
              ();
  }
  iVar7 = func_0x0001844dc660(uVar9,*(undefined8 *)
                                     (*(longlong *)
                                       (*(longlong *)
                                         (*(longlong *)
                                           (*(longlong *)(*(longlong *)(lVar8 + 0x20) + 0xc0) + 0x18
                                           ) + 0x20) + 0xc0) + 0x18));
  if (plVar11 == (longlong *)0x0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (cRam0000000188ca7590 == '\0') {
    FUN_18048bf00(0x1888fec00,iVar7,0,0);
    FUN_18048bf00(0x188885868);
    FUN_18048bf00(0x188803338);
    cRam0000000188ca7590 = '\x01';
  }
  if (iVar7 == 0) {
    iVar7 = *(int *)((longlong)plVar11 + 0x2c);
  }
  if ((char)plVar11[5] == '\0') {
    *(undefined1 *)(plVar11 + 5) = 1;
    puStack_20 = (undefined8 *)&stack0x00000008;
    if (iVar7 == (int)plVar11[9]) {
code_r0x000182648833:
      FUN_18262d450(&puStack_20);
      return;
    }
    lVar8 = plVar11[9];
    if (cRam0000000188ca7592 == '\0') {
      FUN_18048bf00(0x1888fe780);
      cRam0000000188ca7592 = '\x01';
    }
    if ((int)lVar8 < 1) goto code_r0x000182648833;
    if (plVar11[6] == 0) goto code_r0x000182648914;
    cVar5 = FUN_1857c6f10(plVar11[6],(int)lVar8,uRam00000001888fe780);
    if (cVar5 == '\0') goto code_r0x000182648833;
    if (plVar11[10] != 0) {
      cVar5 = FUN_185c320a0(plVar11[10],iVar7,0);
      if (cVar5 == '\0') {
        FUN_18262d450(&puStack_20);
        return;
      }
      if (plVar11[10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(plVar11[10],iVar7,0);
    }
    uVar1 = (undefined4)plVar11[9];
    cVar5 = FUN_182648440(plVar11,iVar7,0);
    if (cVar5 == '\0') {
      *(undefined4 *)(plVar11 + 9) = 0xffffffff;
      plVar11[10] = 0;
      func_0x00018048b9e0(plVar11 + 10,0);
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(0x188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (plVar11[7] != 0) {
        func_0x0001851b8c60(plVar11[7],uRam0000000188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar11);
        }
        cVar5 = (**(code **)(*plVar11 + 400))(plVar11,*(undefined8 *)(*plVar11 + 0x198));
        if ((cVar5 != '\0') && (plVar11[8] != 0)) {
          plVar2 = (longlong *)plVar11[8];
          switch(*(undefined4 *)(*plVar2 + 0x11c)) {
          case 0x487:
          case 0x488:
          case 0x48a:
            break;
          case 0x489:
            FUN_183cc2f80(plVar2,0);
            break;
          case 0x48b:
            func_0x00018050cf60(plVar2,0);
            break;
          case 0x48c:
            func_0x00018050cf60(plVar2,0);
            break;
          default:
            FUN_180005310(2,uRam0000000188903f38);
          }
        }
        if (plVar11[4] != 0) {
          lVar8 = plVar11[4];
          (**(code **)(lVar8 + 0x18))
                    (*(undefined8 *)(lVar8 + 0x40),uVar1,*(undefined8 *)(lVar8 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&puStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(plVar11 + 9) = iVar7;
    if (plVar11[6] == 0) goto code_r0x000182648929;
    lVar8 = FUN_1857ed6c0(plVar11[6],iVar7,uRam00000001888fec00);
    plVar11[10] = lVar8;
    func_0x00018048b9e0(plVar11 + 10,lVar8);
    if (plVar11[10] != 0) {
      FUN_185c32d70(plVar11[10],uVar1,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar11);
      }
      (**(code **)(*plVar11 + 0x1a0))(plVar11,iVar7,uVar1,*(undefined8 *)(*plVar11 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar8 = plVar11[7];
    uVar9 = FUN_1845596e0(iVar7,0,uRam0000000188885868);
    if (lVar8 != 0) {
      FUN_1851ba9c0(lVar8,uVar9,uRam0000000188803338);
      return;
    }
    FUN_18048c0b0();
code_r0x000182648914:
    FUN_18048c0b0();
code_r0x00018264891a:
    FUN_18048c0b0();
code_r0x00018264891f:
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
code_r0x000182648929:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


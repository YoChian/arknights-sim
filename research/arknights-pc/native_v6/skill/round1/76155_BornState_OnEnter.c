
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BornState_OnEnter_0x601297c(longlong param_1,undefined4 param_2)

{
  undefined4 uVar1;
  longlong *plVar2;
  longlong *plVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  undefined1 *puStack_20;
  
  if (DAT_188c92773 == '\0') {
    uStack_40 = 0x180a66194;
    FUN_18048bf00(&DAT_188802da8);
    uStack_40 = 0x180a661a0;
    FUN_18048bf00(&DAT_188952e58);
    uStack_40 = 0x180a661ac;
    FUN_18048bf00(&DAT_1888771f8);
    uStack_40 = 0x180a661b8;
    FUN_18048bf00(&DAT_1888d3908);
    uStack_40 = 0x180a661c4;
    FUN_18048bf00(&DAT_188956720);
    uStack_40 = 0x180a661d0;
    FUN_18048bf00(&DAT_188956960);
    DAT_188c92773 = '\x01';
  }
  lVar8 = **(longlong **)(_DAT_1888771f8 + 0xb8);
  if (lVar8 != 0) {
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar10 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar7 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar9 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar9 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar9,uVar10,param_1,0);
          FUN_183f25080(uVar10,param_2,0);
          iVar6 = FUN_183f22380(uVar10,2,0,iVar7,0);
          if (iVar6 == 0) {
code_r0x0001834c0f1e:
            FUN_183f22fd0(uVar10,iVar7 + -1,0);
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar7 + -1,0);
            goto code_r0x0001834c0f1e;
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
  uStack_40 = 0x180a66205;
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar8 == 0) goto LAB_180a66315;
  if (*(char *)(lVar8 + 0x36e) != '\0') {
    uStack_40 = 0x180a66223;
    lVar8 = FUN_185337c50(_DAT_1888d3908);
    if (lVar8 == 0) goto LAB_180a66315;
    uStack_40 = 0x180a66236;
    cVar5 = Torappu_Battle_BattleController_get_isPlaying_0x600fc14(lVar8,0);
    if (cVar5 == '\0') {
      uStack_40 = 0x180a66249;
      lVar8 = FUN_18536e540(param_1,_DAT_188956960);
      if (lVar8 == 0) goto LAB_180a66315;
      uStack_40 = 0x180a6625c;
      cVar5 = Torappu_Battle_Entity_get_isDialogTarget_0x60103e3(lVar8,0);
      lVar8 = _DAT_188956720;
      if (param_1 == 0) goto LAB_180a66315;
      uVar10 = 0xc;
      if (cVar5 == '\0') {
        uVar10 = 1;
      }
      plVar3 = *(longlong **)(param_1 + 0x10);
      if (plVar3 == (longlong *)0x0) {
        puStack_30 = &UNK_18536e4c1;
        FUN_18048c0b0();
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
      if (*(longlong *)
           (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18) + 0x20)
          == 0) {
        puStack_30 = &UNK_18536e494;
        (*(code *)**(undefined8 **)
                    (*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18))();
      }
      puStack_30 = &UNK_18499c9f3;
      iVar7 = func_0x0001844dc660(uVar10,*(undefined8 *)
                                          (*(longlong *)
                                            (*(longlong *)
                                              (*(longlong *)
                                                (*(longlong *)(*(longlong *)(lVar8 + 0x20) + 0xc0) +
                                                0x18) + 0x20) + 0xc0) + 0x18));
      if (plVar3 == (longlong *)0x0) {
        puStack_30 = &UNK_18499ca0f;
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
        iVar7 = *(int *)((longlong)plVar3 + 0x2c);
      }
      if ((char)plVar3[5] == '\0') {
        *(undefined1 *)(plVar3 + 5) = 1;
        puStack_28 = (undefined8 *)0x0;
        puStack_20 = &stack0x00000008;
        if (iVar7 == (int)plVar3[9]) {
code_r0x000182648833:
          FUN_18262d450(&puStack_20);
          return;
        }
        lVar8 = plVar3[9];
        if (cRam0000000188ca7592 == '\0') {
          FUN_18048bf00(0x1888fe780);
          cRam0000000188ca7592 = '\x01';
        }
        if ((int)lVar8 < 1) goto code_r0x000182648833;
        if (plVar3[6] == 0) goto code_r0x000182648914;
        cVar5 = FUN_1857c6f10(plVar3[6],(int)lVar8,uRam00000001888fe780);
        if (cVar5 == '\0') goto code_r0x000182648833;
        if (plVar3[10] != 0) {
          cVar5 = FUN_185c320a0(plVar3[10],iVar7,0);
          if (cVar5 == '\0') {
            FUN_18262d450(&puStack_20);
            return;
          }
          if (plVar3[10] == 0) goto code_r0x00018264891a;
          FUN_185c33f30(plVar3[10],iVar7,0);
        }
        uVar1 = (undefined4)plVar3[9];
        cVar5 = FUN_182648440(plVar3,iVar7,0);
        if (cVar5 == '\0') {
          *(undefined4 *)(plVar3 + 9) = 0xffffffff;
          plVar3[10] = 0;
          func_0x00018048b9e0(plVar3 + 10,0);
          if (cRam0000000188ca758f == '\0') {
            FUN_18048bf00(0x188802eb8);
            cRam0000000188ca758f = '\x01';
          }
          if (plVar3[7] != 0) {
            func_0x0001851b8c60(plVar3[7],uRam0000000188802eb8);
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(*plVar3);
            }
            cVar5 = (**(code **)(*plVar3 + 400))(plVar3,*(undefined8 *)(*plVar3 + 0x198));
            if ((cVar5 != '\0') && (plVar3[8] != 0)) {
              plVar2 = (longlong *)plVar3[8];
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
            if (plVar3[4] != 0) {
              lVar8 = plVar3[4];
              (**(code **)(lVar8 + 0x18))
                        (*(undefined8 *)(lVar8 + 0x40),uVar1,*(undefined8 *)(lVar8 + 0x28));
            }
code_r0x000182648824:
            FUN_18262d450(&puStack_20);
            return;
          }
          goto code_r0x00018264891f;
        }
        *(int *)(plVar3 + 9) = iVar7;
        if (plVar3[6] == 0) goto code_r0x000182648929;
        lVar8 = FUN_1857ed6c0(plVar3[6],iVar7,uRam00000001888fec00);
        plVar3[10] = lVar8;
        func_0x00018048b9e0(plVar3 + 10,lVar8);
        if (plVar3[10] != 0) {
          FUN_185c32d70(plVar3[10],uVar1,0);
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar3);
          }
          (**(code **)(*plVar3 + 0x1a0))(plVar3,iVar7,uVar1,*(undefined8 *)(*plVar3 + 0x1a8));
          goto code_r0x000182648824;
        }
      }
      else {
        lVar8 = plVar3[7];
        uVar10 = FUN_1845596e0(iVar7,0,uRam0000000188885868);
        if (lVar8 != 0) {
          FUN_1851ba9c0(lVar8,uVar10,uRam0000000188803338);
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
  }
  uStack_40 = 0x180a662a1;
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  uStack_40 = 0x180a662b0;
  lVar9 = func_0x00018045cfe0(_DAT_188802da8);
  if (lVar9 != 0) {
    uStack_40 = 0x180a662cd;
    EasyTouchIsReadyHandler__ctor_0x6000a20(lVar9,param_1,_DAT_188952e58,0);
    if (lVar8 != 0) {
      uStack_40 = 0x180a662ed;
      Torappu_Battle_Character_PlayBornAnimationAndEffect_0x6012899(lVar8,param_1 + 0x18,lVar9,0);
      return;
    }
  }
LAB_180a66315:
  uStack_40 = 0x180a6631a;
  FUN_18048c0b0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


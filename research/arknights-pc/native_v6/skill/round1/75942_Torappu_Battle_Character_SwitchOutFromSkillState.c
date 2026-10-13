
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_SwitchOutFromSkillState_0x60128a7(longlong param_1)

{
  undefined4 uVar1;
  longlong *plVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  char cVar10;
  longlong *aplStackX_8 [2];
  longlong *plStackX_20;
  longlong **pplStack_20;
  
  if (DAT_188c925e0 == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_18889b5f0);
    DAT_188c925e0 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x3f0);
  if (lVar8 != 0) {
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    plStackX_20 = *(longlong **)(*(longlong *)(lVar8 + 0x18) + 0x30);
    aplStackX_8[0] = (longlong *)((ulonglong)aplStackX_8[0] & 0xffffffffffffff00);
    pplStack_20 = &plStackX_20;
    FUN_185ca7f50(plStackX_20,aplStackX_8,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar9 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar6 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar3 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar3 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar3,uVar9,param_1,0);
          iVar5 = FUN_183f22380(uVar9,1,0,iVar6,0);
          if (iVar5 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar9,iVar6 + -1,0);
            if ((char)aplStackX_8[0] != '\0') {
              func_0x000185ca7ff0(plStackX_20,0);
            }
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar6 + -1,0);
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
  if (DAT_188c925c5 == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    DAT_188c925c5 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x318);
  if (lVar8 == 0) {
    if (*(longlong *)(param_1 + 0x38) == 0) goto LAB_180a32271;
    cVar10 = *(int *)(*(longlong *)(param_1 + 0x38) + 0x48) == 4;
  }
  else {
    cVar10 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar8,param_1,0);
  }
  if (cVar10 == '\0') {
    return;
  }
  plVar7 = (longlong *)Torappu_Battle_Character_get_stateMachine_0x6012882(param_1,0);
  if (plVar7 == (longlong *)0x0) {
LAB_180a32271:
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  iVar6 = func_0x0001844dc660(1,*(undefined8 *)
                                 (*(longlong *)(*(longlong *)(_DAT_18889b5f0 + 0x20) + 0xc0) + 0x18)
                             );
  if (plVar7 == (longlong *)0x0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  aplStackX_8[0] = plVar7;
  if (cRam0000000188ca7590 == '\0') {
    FUN_18048bf00(0x1888fec00,iVar6,0,0);
    FUN_18048bf00(0x188885868);
    FUN_18048bf00(0x188803338);
    cRam0000000188ca7590 = '\x01';
  }
  plVar7 = aplStackX_8[0];
  if (iVar6 == 0) {
    iVar6 = *(int *)((longlong)aplStackX_8[0] + 0x2c);
  }
  if ((char)aplStackX_8[0][5] == '\0') {
    *(undefined1 *)(aplStackX_8[0] + 5) = 1;
    pplStack_20 = aplStackX_8;
    if (iVar6 == (int)aplStackX_8[0][9]) {
code_r0x000182648833:
      FUN_18262d450(&pplStack_20);
      return;
    }
    lVar8 = aplStackX_8[0][9];
    if (cRam0000000188ca7592 == '\0') {
      FUN_18048bf00(0x1888fe780);
      cRam0000000188ca7592 = '\x01';
    }
    if ((int)lVar8 < 1) goto code_r0x000182648833;
    if (plVar7[6] == 0) goto code_r0x000182648914;
    cVar10 = FUN_1857c6f10(plVar7[6],(int)lVar8,uRam00000001888fe780);
    if (cVar10 == '\0') goto code_r0x000182648833;
    if (aplStackX_8[0][10] != 0) {
      cVar10 = FUN_185c320a0(aplStackX_8[0][10],iVar6,0);
      if (cVar10 == '\0') {
        FUN_18262d450(&pplStack_20);
        return;
      }
      if (aplStackX_8[0][10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(aplStackX_8[0][10],iVar6,0);
    }
    uVar1 = (undefined4)aplStackX_8[0][9];
    cVar10 = FUN_182648440(aplStackX_8[0],iVar6,0);
    if (cVar10 == '\0') {
      *(undefined4 *)(aplStackX_8[0] + 9) = 0xffffffff;
      aplStackX_8[0][10] = 0;
      func_0x00018048b9e0(aplStackX_8[0] + 10,0);
      plVar7 = aplStackX_8[0];
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(0x188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (plVar7[7] != 0) {
        func_0x0001851b8c60(plVar7[7],uRam0000000188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar7);
        }
        cVar10 = (**(code **)(*plVar7 + 400))(plVar7,*(undefined8 *)(*plVar7 + 0x198));
        if ((cVar10 != '\0') && (plVar7[8] != 0)) {
          plVar2 = (longlong *)plVar7[8];
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
        if (plVar7[4] != 0) {
          lVar8 = plVar7[4];
          (**(code **)(lVar8 + 0x18))
                    (*(undefined8 *)(lVar8 + 0x40),uVar1,*(undefined8 *)(lVar8 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&pplStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(aplStackX_8[0] + 9) = iVar6;
    if (aplStackX_8[0][6] == 0) goto code_r0x000182648929;
    lVar8 = FUN_1857ed6c0(aplStackX_8[0][6],iVar6,uRam00000001888fec00);
    aplStackX_8[0][10] = lVar8;
    func_0x00018048b9e0(aplStackX_8[0] + 10,lVar8);
    if (aplStackX_8[0][10] != 0) {
      FUN_185c32d70(aplStackX_8[0][10],uVar1,0);
      plVar7 = aplStackX_8[0];
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*aplStackX_8[0]);
      }
      lVar8 = *plVar7;
      (**(code **)(lVar8 + 0x1a0))(plVar7,iVar6,uVar1,*(undefined8 *)(lVar8 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar8 = aplStackX_8[0][7];
    uVar9 = FUN_1845596e0(iVar6,0,uRam0000000188885868);
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


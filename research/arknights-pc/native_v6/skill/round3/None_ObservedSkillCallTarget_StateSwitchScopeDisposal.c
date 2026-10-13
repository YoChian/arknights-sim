
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ObservedSkillCallTarget_StateSwitchScopeDisposal_call_target(undefined8 *param_1)

{
  undefined4 uVar1;
  longlong *plVar2;
  longlong *plVar3;
  code *pcVar4;
  char cVar5;
  char cVar6;
  ulonglong uVar7;
  longlong lVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  longlong *aplStackX_8 [2];
  longlong **pplStack_20;
  
  plVar2 = *(longlong **)*param_1;
  if (DAT_188ca7591 == '\0') {
    FUN_18048bf00(0x1888e8468);
    FUN_18048bf00(0x1888e86a8);
    FUN_18048bf00(&DAT_1888030f8);
    FUN_18048bf00(0x188803578);
    DAT_188ca7591 = '\x01';
  }
  lVar8 = plVar2[7];
  *(undefined1 *)(plVar2 + 5) = 0;
  if (lVar8 == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(int *)(lVar8 + 0x20) < 1) {
    return;
  }
  uVar7 = FUN_1851b9980(lVar8,_DAT_1888030f8);
  cVar6 = (char)(uVar7 >> 0x20);
  uVar10 = uVar7 & 0xffffffff;
  aplStackX_8[0] = plVar2;
  if (DAT_188ca7590 == '\0') {
    FUN_18048bf00(&DAT_1888fec00,uVar7 & 0xffffffff,uVar7 >> 0x20,0);
    FUN_18048bf00(&DAT_188885868);
    FUN_18048bf00(&DAT_188803338);
    DAT_188ca7590 = '\x01';
  }
  plVar2 = aplStackX_8[0];
  if ((int)uVar7 == 0) {
    uVar10 = (ulonglong)*(uint *)((longlong)aplStackX_8[0] + 0x2c);
  }
  if ((char)aplStackX_8[0][5] == '\0') {
    *(undefined1 *)(aplStackX_8[0] + 5) = 1;
    pplStack_20 = aplStackX_8;
    if ((int)uVar10 == (int)aplStackX_8[0][9]) {
LAB_182648833:
      ObservedSkillCallTarget_StateSwitchScopeDisposal_call_target(&pplStack_20);
      return;
    }
    if (cVar6 == '\0') {
      lVar8 = aplStackX_8[0][9];
      if (DAT_188ca7592 == '\0') {
        FUN_18048bf00(&DAT_1888fe780);
        DAT_188ca7592 = '\x01';
      }
      if ((int)lVar8 < 1) goto LAB_182648833;
      if (plVar2[6] == 0) goto LAB_182648914;
      cVar5 = FUN_1857c6f10(plVar2[6],(int)lVar8,_DAT_1888fe780);
      if (cVar5 == '\0') goto LAB_182648833;
    }
    if (aplStackX_8[0][10] != 0) {
      if ((cVar6 == '\0') && (cVar6 = FUN_185c320a0(aplStackX_8[0][10],uVar10,0), cVar6 == '\0')) {
        ObservedSkillCallTarget_StateSwitchScopeDisposal_call_target(&pplStack_20);
        return;
      }
      if (aplStackX_8[0][10] == 0) goto LAB_18264891a;
      FUN_185c33f30(aplStackX_8[0][10],uVar10,0);
    }
    uVar1 = (undefined4)aplStackX_8[0][9];
    cVar6 = Torappu_StateMachine__CheckValidState_0x6008207(aplStackX_8[0],uVar10,0);
    if (cVar6 == '\0') {
      *(undefined4 *)(aplStackX_8[0] + 9) = 0xffffffff;
      aplStackX_8[0][10] = 0;
      func_0x00018048b9e0(aplStackX_8[0] + 10,0);
      plVar2 = aplStackX_8[0];
      if (DAT_188ca758f == '\0') {
        FUN_18048bf00(&DAT_188802eb8);
        DAT_188ca758f = '\x01';
      }
      if (plVar2[7] != 0) {
        func_0x0001851b8c60(plVar2[7],_DAT_188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
        cVar6 = (**(code **)(*plVar2 + 400))(plVar2,*(undefined8 *)(*plVar2 + 0x198));
        if ((cVar6 != '\0') && (plVar2[8] != 0)) {
          plVar3 = (longlong *)plVar2[8];
          switch(*(undefined4 *)(*plVar3 + 0x11c)) {
          case 0x487:
          case 0x488:
          case 0x48a:
            break;
          case 0x489:
            Torappu_Building_BuildingModel_OnStop_0x600b020(plVar3,0);
            break;
          case 0x48b:
            func_0x00018050cf60(plVar3,0);
            break;
          case 0x48c:
            func_0x00018050cf60(plVar3,0);
            break;
          default:
            FUN_180005310(2,_DAT_188903f38);
          }
        }
        if (plVar2[4] != 0) {
          lVar8 = plVar2[4];
          (**(code **)(lVar8 + 0x18))
                    (*(undefined8 *)(lVar8 + 0x40),uVar1,*(undefined8 *)(lVar8 + 0x28));
        }
LAB_182648824:
        ObservedSkillCallTarget_StateSwitchScopeDisposal_call_target(&pplStack_20);
        return;
      }
      goto LAB_18264891f;
    }
    *(int *)(aplStackX_8[0] + 9) = (int)uVar10;
    if (aplStackX_8[0][6] == 0) goto LAB_182648929;
    lVar8 = FUN_1857ed6c0(aplStackX_8[0][6],uVar10,_DAT_1888fec00);
    aplStackX_8[0][10] = lVar8;
    func_0x00018048b9e0(aplStackX_8[0] + 10,lVar8);
    if (aplStackX_8[0][10] != 0) {
      FUN_185c32d70(aplStackX_8[0][10],uVar1,0);
      plVar2 = aplStackX_8[0];
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*aplStackX_8[0]);
      }
      lVar8 = *plVar2;
      (**(code **)(lVar8 + 0x1a0))(plVar2,uVar10,uVar1,*(undefined8 *)(lVar8 + 0x1a8));
      goto LAB_182648824;
    }
  }
  else {
    lVar8 = aplStackX_8[0][7];
    uVar9 = FUN_1845596e0(uVar10,cVar6,_DAT_188885868);
    if (lVar8 != 0) {
      FUN_1851ba9c0(lVar8,uVar9,_DAT_188803338);
      return;
    }
    FUN_18048c0b0();
LAB_182648914:
    FUN_18048c0b0();
LAB_18264891a:
    FUN_18048c0b0();
LAB_18264891f:
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
LAB_182648929:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


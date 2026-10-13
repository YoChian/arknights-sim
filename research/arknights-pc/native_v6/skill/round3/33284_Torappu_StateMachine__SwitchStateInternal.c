
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_StateMachine__SwitchStateInternal_0x6008205(longlong *param_1,int param_2,char param_3)

{
  undefined4 uVar1;
  longlong *plVar2;
  code *pcVar3;
  longlong *plVar4;
  char cVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong *plStackX_8;
  longlong **pplStack_20;
  
  plStackX_8 = param_1;
  if (DAT_188ca7590 == '\0') {
    FUN_18048bf00(&DAT_1888fec00);
    FUN_18048bf00(&DAT_188885868);
    FUN_18048bf00(&DAT_188803338);
    DAT_188ca7590 = '\x01';
  }
  plVar4 = plStackX_8;
  if (param_2 == 0) {
    param_2 = *(int *)((longlong)plStackX_8 + 0x2c);
  }
  if ((char)plStackX_8[5] == '\0') {
    *(undefined1 *)(plStackX_8 + 5) = 1;
    pplStack_20 = &plStackX_8;
    if (param_2 == (int)plStackX_8[9]) {
LAB_182648833:
      FUN_18262d450(&pplStack_20);
      return;
    }
    if (param_3 == '\0') {
      lVar6 = plStackX_8[9];
      if (DAT_188ca7592 == '\0') {
        FUN_18048bf00(&DAT_1888fe780);
        DAT_188ca7592 = '\x01';
      }
      if ((int)lVar6 < 1) goto LAB_182648833;
      if (plVar4[6] == 0) goto LAB_182648914;
      cVar5 = FUN_1857c6f10(plVar4[6],(int)lVar6,_DAT_1888fe780);
      if (cVar5 == '\0') goto LAB_182648833;
    }
    if (plStackX_8[10] != 0) {
      if ((param_3 == '\0') && (cVar5 = FUN_185c320a0(plStackX_8[10],param_2,0), cVar5 == '\0')) {
        FUN_18262d450(&pplStack_20);
        return;
      }
      if (plStackX_8[10] == 0) goto LAB_18264891a;
      FUN_185c33f30(plStackX_8[10],param_2,0);
    }
    uVar1 = (undefined4)plStackX_8[9];
    cVar5 = Torappu_StateMachine__CheckValidState_0x6008207(plStackX_8,param_2,0);
    if (cVar5 == '\0') {
      *(undefined4 *)(plStackX_8 + 9) = 0xffffffff;
      plStackX_8[10] = 0;
      func_0x00018048b9e0(plStackX_8 + 10,0);
      plVar4 = plStackX_8;
      if (DAT_188ca758f == '\0') {
        FUN_18048bf00(&DAT_188802eb8);
        DAT_188ca758f = '\x01';
      }
      if (plVar4[7] != 0) {
        func_0x0001851b8c60(plVar4[7],_DAT_188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar4);
        }
        cVar5 = (**(code **)(*plVar4 + 400))(plVar4,*(undefined8 *)(*plVar4 + 0x198));
        if ((cVar5 != '\0') && (plVar4[8] != 0)) {
          plVar2 = (longlong *)plVar4[8];
          switch(*(undefined4 *)(*plVar2 + 0x11c)) {
          case 0x487:
          case 0x488:
          case 0x48a:
            break;
          case 0x489:
            Torappu_Building_BuildingModel_OnStop_0x600b020(plVar2,0);
            break;
          case 0x48b:
            func_0x00018050cf60(plVar2,0);
            break;
          case 0x48c:
            func_0x00018050cf60(plVar2,0);
            break;
          default:
            FUN_180005310(2,_DAT_188903f38);
          }
        }
        if (plVar4[4] != 0) {
          lVar6 = plVar4[4];
          (**(code **)(lVar6 + 0x18))
                    (*(undefined8 *)(lVar6 + 0x40),uVar1,*(undefined8 *)(lVar6 + 0x28));
        }
LAB_182648824:
        FUN_18262d450(&pplStack_20);
        return;
      }
      goto LAB_18264891f;
    }
    *(int *)(plStackX_8 + 9) = param_2;
    if (plStackX_8[6] == 0) goto LAB_182648929;
    lVar6 = FUN_1857ed6c0(plStackX_8[6],param_2,_DAT_1888fec00);
    plStackX_8[10] = lVar6;
    func_0x00018048b9e0(plStackX_8 + 10,lVar6);
    if (plStackX_8[10] != 0) {
      FUN_185c32d70(plStackX_8[10],uVar1,0);
      plVar4 = plStackX_8;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plStackX_8);
      }
      lVar6 = *plVar4;
      (**(code **)(lVar6 + 0x1a0))(plVar4,param_2,uVar1,*(undefined8 *)(lVar6 + 0x1a8));
      goto LAB_182648824;
    }
  }
  else {
    lVar6 = plStackX_8[7];
    uVar7 = FUN_1845596e0(param_2,param_3,_DAT_188885868);
    if (lVar6 != 0) {
      FUN_1851ba9c0(lVar6,uVar7,_DAT_188803338);
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
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


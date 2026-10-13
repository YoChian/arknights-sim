
/* WARNING: Removing unreachable block (ram,0x0001826485d0) */
/* WARNING: Removing unreachable block (ram,0x0001826485dd) */
/* WARNING: Removing unreachable block (ram,0x0001826485f0) */
/* WARNING: Removing unreachable block (ram,0x0001826485f9) */
/* WARNING: Removing unreachable block (ram,0x000182648606) */
/* WARNING: Removing unreachable block (ram,0x00018264861d) */
/* WARNING: Removing unreachable block (ram,0x00018264862e) */
/* WARNING: Removing unreachable block (ram,0x000182648640) */
/* WARNING: Removing unreachable block (ram,0x00018264864f) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_StateMachine_Start_0x60081f9(longlong *param_1,int param_2)

{
  undefined4 uVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined1 *puStack_20;
  
  if (DAT_188ca758c == '\0') {
    FUN_18048bf00(&DAT_188802eb8);
    DAT_188ca758c = '\x01';
  }
  if (param_1[7] == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  func_0x0001851b8c60(param_1[7],_DAT_188802eb8);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar4 = (**(code **)(*param_1 + 400))(param_1,*(undefined8 *)(*param_1 + 0x198));
  if ((cVar4 != '\0') && (param_1[8] != 0)) {
    plVar2 = (longlong *)param_1[8];
    switch(*(undefined4 *)(*plVar2 + 0x11c)) {
    case 0x487:
      break;
    case 0x488:
      Options_OnReset_0x60094c9(plVar2,0);
      break;
    case 0x489:
      Torappu_Building_BuildingModel_OnReset_0x600b01e(plVar2,0);
      break;
    case 0x48a:
      Options_OnReset_0x600bc82(plVar2,0);
      break;
    case 0x48b:
      func_0x00018050cf60(plVar2,0);
      break;
    case 0x48c:
      Blackboard_OnReset_0x6012b5b(plVar2,0);
      break;
    default:
      FUN_180005310(0,_DAT_188903f38);
    }
  }
  if (param_1[2] != 0) {
    lVar5 = param_1[2];
    (**(code **)(lVar5 + 0x18))
              (*(undefined8 *)(lVar5 + 0x40),(int)param_1[9],*(undefined8 *)(lVar5 + 0x28));
  }
  if (cRam0000000188ca7590 == '\0') {
    FUN_18048bf00(0x1888fec00,param_2,1,0);
    FUN_18048bf00(0x188885868);
    FUN_18048bf00(0x188803338);
    cRam0000000188ca7590 = '\x01';
  }
  if (param_2 == 0) {
    param_2 = *(int *)((longlong)param_1 + 0x2c);
  }
  if ((char)param_1[5] == '\0') {
    *(undefined1 *)(param_1 + 5) = 1;
    puStack_20 = &stack0x00000008;
    if (param_2 == (int)param_1[9]) {
      FUN_18262d450(&puStack_20);
      return;
    }
    if (param_1[10] != 0) {
      if (param_1[10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(param_1[10],param_2,0);
    }
    uVar1 = (undefined4)param_1[9];
    cVar4 = FUN_182648440(param_1,param_2,0);
    if (cVar4 == '\0') {
      *(undefined4 *)(param_1 + 9) = 0xffffffff;
      param_1[10] = 0;
      func_0x00018048b9e0(param_1 + 10,0);
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(&DAT_188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (param_1[7] != 0) {
        func_0x0001851b8c60(param_1[7],_DAT_188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar4 = (**(code **)(*param_1 + 400))(param_1,*(undefined8 *)(*param_1 + 0x198));
        if ((cVar4 != '\0') && (param_1[8] != 0)) {
          plVar2 = (longlong *)param_1[8];
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
            FUN_180005310(2,_DAT_188903f38);
          }
        }
        if (param_1[4] != 0) {
          lVar5 = param_1[4];
          (**(code **)(lVar5 + 0x18))
                    (*(undefined8 *)(lVar5 + 0x40),uVar1,*(undefined8 *)(lVar5 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&puStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(param_1 + 9) = param_2;
    if (param_1[6] == 0) goto code_r0x000182648929;
    lVar5 = FUN_1857ed6c0(param_1[6],param_2,uRam00000001888fec00);
    param_1[10] = lVar5;
    func_0x00018048b9e0(param_1 + 10,lVar5);
    if (param_1[10] != 0) {
      FUN_185c32d70(param_1[10],uVar1,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      (**(code **)(*param_1 + 0x1a0))(param_1,param_2,uVar1,*(undefined8 *)(*param_1 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar5 = param_1[7];
    uVar6 = FUN_1845596e0(param_2,1,uRam0000000188885868);
    if (lVar5 != 0) {
      FUN_1851ba9c0(lVar5,uVar6,uRam0000000188803338);
      return;
    }
    FUN_18048c0b0();
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
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


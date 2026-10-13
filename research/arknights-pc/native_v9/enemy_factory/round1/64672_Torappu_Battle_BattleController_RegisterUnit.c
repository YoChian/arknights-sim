
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BattleController_RegisterUnit_0x600fca1(longlong param_1,undefined8 param_2)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c900cb == '\0') {
    puStack_30 = (undefined1 *)0x18062f135;
    FUN_18048bf00(&DAT_188927d60);
    puStack_30 = (undefined1 *)0x18062f141;
    FUN_18048bf00(0x1889663c0);
    puStack_30 = (undefined1 *)0x18062f14d;
    FUN_18048bf00(&DAT_188966600);
    DAT_188c900cb = '\x01';
  }
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    puStack_30 = (undefined1 *)0x18062f16c;
    func_0x00018048c140(_DAT_188927d60);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0x7a8);
  if (lVar6 == 0) {
    puStack_30 = (undefined1 *)0x18062f194;
    iVar4 = Torappu_Battle_BattleController_get_state_0x600fc2f(param_1,0);
    if (iVar4 == 0) {
      return;
    }
    puStack_30 = (undefined1 *)0x18062f1b0;
    lVar6 = Torappu_Battle_BattleController_get_unitManager_0x600fbf7(param_1,0);
    if (lVar6 != 0) {
      puStack_30 = (undefined1 *)0x18062f1c7;
      Torappu_Battle_UnitManager_Register_0x6012fe5(lVar6,param_2,0);
      puStack_30 = (undefined1 *)0x18062f1d1;
      plVar7 = (longlong *)Torappu_Battle_BattleController_get_gameMode_0x600fc04(param_1,0);
      if (plVar7 != (longlong *)0x0) {
        switch(*(undefined4 *)(*plVar7 + 0x11c)) {
        case 0x9b7:
        case 0x9b8:
        case 0x9b9:
        case 0x9bb:
        case 0x9bc:
        case 0x9bf:
        case 0x9c1:
        case 0x9c4:
        case 0x9c5:
        case 0x9c8:
        case 0x9c9:
        case 0x9ca:
        case 0x9cb:
        case 0x9cc:
        case 0x9cf:
        case 0x9d0:
        case 0x9d1:
          puStack_30 = (undefined1 *)0x18062f2c3;
          DefaultGameMode_OnUnitRegistered_0x601411a(plVar7,param_2,0);
          break;
        case 0x9ba:
          puStack_30 = (undefined1 *)0x18062f217;
          Act6FunGameMode_OnUnitRegistered_0x6013b6a(plVar7,param_2,0);
          break;
        case 0x9bd:
          puStack_30 = (undefined1 *)0x18062f22a;
          ArkDexGameMode_OnUnitRegistered_0x6013c17(plVar7,param_2,0);
          break;
        case 0x9be:
          puStack_30 = (undefined1 *)0x18062f23d;
          AutoChessGameMode_OnUnitRegistered_0x6013c73(plVar7,param_2,0);
          break;
        case 0x9c0:
          puStack_30 = (undefined1 *)0x18062f250;
          CooperateGameMode_OnUnitRegistered_0x6013def(plVar7,param_2,0);
          break;
        case 0x9c2:
          puStack_30 = (undefined1 *)0x18062f263;
          DouququGameMode_OnUnitRegistered_0x6013f7e(plVar7,param_2,0);
          break;
        case 0x9c3:
          puStack_30 = (undefined1 *)0x18062f273;
          EnemyDuelGameMode_OnUnitRegistered_0x6013fad(plVar7,param_2,0);
          break;
        case 0x9c6:
          puStack_30 = (undefined1 *)0x18062f283;
          GameCityGameMode_OnUnitRegistered_0x6014097(plVar7,param_2,0);
          break;
        case 0x9c7:
          puStack_30 = (undefined1 *)0x18062f293;
          HalfIdleGameMode_OnUnitRegistered_0x601417f(plVar7,param_2,0);
          break;
        case 0x9cd:
          puStack_30 = (undefined1 *)0x18062f2a3;
          RoguelikeDuelGameMode_OnUnitRegistered_0x601431d(plVar7,param_2,0);
          break;
        case 0x9ce:
          puStack_30 = (undefined1 *)0x18062f2b3;
          SandboxGameMode_OnUnitRegistered_0x60143c1(plVar7,param_2,0);
          break;
        default:
          puStack_30 = (undefined1 *)0x18062f2dc;
          FUN_180005010(0x39,_DAT_188961dd0,plVar7,param_2);
        }
        iVar4 = 0;
        lVar6 = *(longlong *)(param_1 + 0x68);
        while (lVar6 != 0) {
          if (*(int *)(lVar6 + 0x18) <= iVar4) {
            return;
          }
          if (*(longlong *)(param_1 + 0x68) == 0) break;
          puStack_30 = (undefined1 *)0x18062f310;
          plVar7 = (longlong *)FUN_184afcf00(*(longlong *)(param_1 + 0x68),iVar4,_DAT_188966600);
          if (plVar7 == (longlong *)0x0) break;
          if (DAT_188ccc7f0 != '\0') {
            puStack_30 = (undefined1 *)0x18062f329;
            func_0x000180446d00(*plVar7);
          }
          puStack_30 = (undefined1 *)0x18062f346;
          (**(code **)(*plVar7 + 0x210))(plVar7,param_2,1,*(undefined8 *)(*plVar7 + 0x218));
          iVar4 = iVar4 + 1;
          lVar6 = *(longlong *)(param_1 + 0x68);
        }
      }
    }
    puStack_30 = (undefined1 *)0x18062f387;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        FUN_183cf8c20(lVar2,uVar1,param_2,0);
        iVar5 = FUN_183f22380(uVar1,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001832d231b;
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


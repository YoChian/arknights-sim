
/* WARNING: Removing unreachable block (ram,0x0001836501b1) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_OnInit_0x6012af1(longlong param_1,undefined8 param_2)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong *plVar6;
  uint uVar7;
  int iVar8;
  longlong lVar9;
  undefined4 uVar10;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c928d9 == '\0') {
    uStack_40 = 0x180a71036;
    FUN_18048bf00(&DAT_18881b6b0);
    uStack_40 = 0x180a71042;
    FUN_18048bf00(&DAT_18885a700);
    uStack_40 = 0x180a7104e;
    FUN_18048bf00(0x188935958);
    uStack_40 = 0x180a7105a;
    FUN_18048bf00(&DAT_188935b98);
    uStack_40 = 0x180a71066;
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c928d9 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    uStack_40 = 0x180a71085;
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x808);
  if (lVar4 != 0) {
    if (*(longlong *)(lVar4 + 0x18) == 0) {
      FUN_18048c0b0(lVar4,param_1,(float)param_2,0);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar4 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar4 + 0x18) != 0) {
      uVar5 = *(undefined8 *)(*(longlong *)(lVar4 + 0x18) + 0x10);
      iVar8 = FUN_183f23b70(uVar5,*(undefined4 *)(lVar4 + 0x38),*(undefined4 *)(lVar4 + 0x14),0);
      if (*(longlong *)(lVar4 + 0x18) != 0) {
        lVar9 = *(longlong *)(*(longlong *)(lVar4 + 0x18) + 0x20);
        if (lVar9 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar9,uVar5,param_1,0);
          FUN_183f22700(uVar5,(double)(float)param_2,0);
          iVar3 = FUN_183f22380(uVar5,2,0,iVar8,0);
          if (iVar3 == 0) {
code_r0x000183650198:
            FUN_183f22fd0(uVar5,iVar8 + -1,0);
            return;
          }
          if (*(longlong *)(lVar4 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar4 + 0x18),iVar8 + -1,0);
            goto code_r0x000183650198;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  uStack_40 = 0x180a710c0;
  Torappu_Battle_Unit_OnInit_0x6012f62(param_1,param_2,0);
  if (*(longlong *)(param_1 + 0x3b0) != 0) {
    uStack_40 = 0x180a710db;
    HeightController_OnInit_0x6012c75(*(longlong *)(param_1 + 0x3b0),param_2,0);
    if (*(longlong *)(param_1 + 0x3d8) != 0) {
      uStack_40 = 0x180a710f2;
      FearController_OnInit_0x6012c5c(*(longlong *)(param_1 + 0x3d8),0);
      if (*(longlong *)(param_1 + 0x3e0) != 0) {
        uStack_40 = 0x180a71109;
        AttractController_OnInit_0x6012c67(*(longlong *)(param_1 + 0x3e0),0);
        if (*(longlong *)(param_1 + 1000) != 0) {
          uStack_40 = 0x180a71120;
          Torappu_Battle_GroundBoundController_OnInit_0x6012d58(*(longlong *)(param_1 + 1000),0);
          iVar8 = 0;
          lVar4 = *(longlong *)(param_1 + 0x4e0);
          while (lVar4 != 0) {
            if (*(int *)(lVar4 + 0x18) <= iVar8) {
              uVar7 = 0;
              uStack_40 = 0x180a711fb;
              lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
              if (lVar4 != 0) {
                lVar9 = 0x20;
                goto LAB_180a71210;
              }
              break;
            }
            if (*(longlong *)(param_1 + 0x4e0) == 0) break;
            uStack_40 = 0x180a7115d;
            lVar4 = FUN_184afcf00(*(longlong *)(param_1 + 0x4e0),iVar8,_DAT_188935b98);
            if (lVar4 == 0) break;
            uStack_40 = 0x180a71170;
            Torappu_Battle_EnemySkill_Init_0x60102ff(lVar4,0);
            if (*(longlong *)(param_1 + 0x4e0) == 0) break;
            uStack_40 = 0x180a7118e;
            lVar4 = FUN_184afcf00();
            if (lVar4 == 0) break;
            uStack_40 = 0x180a711a1;
            cVar2 = Torappu_Battle_EnemySkill_get_isRoot_0x60102eb(lVar4);
            if (cVar2 != '\0') {
              if (*(longlong *)(param_1 + 0x4e0) == 0) break;
              uStack_40 = 0x180a711c3;
              lVar4 = FUN_184afcf00();
              if (lVar4 == 0) break;
              uStack_40 = 0x180a711d6;
              Torappu_Battle_EnemySkill_Attach_0x6010300(lVar4);
            }
            iVar8 = iVar8 + 1;
            lVar4 = *(longlong *)(param_1 + 0x4e0);
          }
        }
      }
    }
  }
  goto LAB_180a71406;
LAB_180a71210:
  do {
    if (*(int *)(lVar4 + 0x18) <= (int)uVar7) {
      uStack_40 = 0x180a712e0;
      lVar4 = FUN_185337c50(_DAT_1888d3908);
      if (lVar4 == 0) break;
      uStack_40 = 0x180a712f3;
      plVar6 = (longlong *)Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar4,0);
      if (plVar6 == (longlong *)0x0) break;
      switch(*(undefined4 *)(*plVar6 + 0x11c)) {
      case 0x9b7:
      case 0x9b8:
      case 0x9b9:
      case 0x9ba:
      case 0x9bb:
      case 0x9bc:
      case 0x9be:
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
        uStack_40 = 0x180a7133a;
        cVar2 = DefaultGameMode_get_enableEnemyRuntimeSnapshot_0x60140eb(plVar6,0);
        break;
      case 0x9bd:
        uStack_40 = 0x180a71346;
        cVar2 = ArkDexGameMode_get_enableEnemyRuntimeSnapshot_0x6013c08(plVar6,0);
        break;
      default:
        uStack_40 = 0x180a7135c;
        cVar2 = FUN_180005310(0x10,_DAT_188961dd0,plVar6);
      }
      if (cVar2 != '\0') {
        lVar4 = *(longlong *)(param_1 + 0x4e8);
        if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
          uStack_40 = 0x180a7137c;
          func_0x00018048c140();
        }
        uStack_40 = 0x180a7139c;
        uVar10 = func_0x000186732bd0(*(undefined4 *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 8),
                                     *(undefined4 *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0xc),0);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          uStack_40 = 0x180a713b4;
          func_0x00018048c140();
        }
        uStack_40 = 0x180a713be;
        uVar5 = func_0x0001866fdad0(uVar10,0);
        if (lVar4 == 0) break;
        uStack_40 = 0x180a713d4;
        Torappu_PeriodicTimer_Reset_0x6006576(lVar4,uVar5,1,0);
      }
      return;
    }
    uStack_40 = 0x180a71223;
    lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
    if (lVar4 == 0) break;
    if (*(uint *)(lVar4 + 0x18) <= uVar7) {
LAB_180a7140c:
      uStack_40 = 0x180a71411;
      FUN_18048c0a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    lVar4 = *(longlong *)(lVar9 + lVar4);
    uStack_40 = 0x180a71243;
    uVar5 = Torappu_Battle_Unit_get_currentMode_0x6012ef4(param_1,0);
    if (lVar4 == 0) break;
    uStack_40 = 0x180a7125a;
    cVar2 = Torappu_Battle_BasicTalent_CheckRootOrValidModeTalent_0x6011e62(lVar4,uVar5,0);
    if (cVar2 == '\0') {
      uStack_40 = 0x180a71268;
      lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1);
      if (lVar4 == 0) break;
      if (*(uint *)(lVar4 + 0x18) <= uVar7) goto LAB_180a7140c;
      if (*(longlong *)(lVar9 + lVar4) == 0) break;
      uStack_40 = 0x180a7128e;
      lVar4 = FUN_186b59d80();
      if (lVar4 == 0) break;
      uStack_40 = 0x180a712a4;
      FUN_186b5c530(lVar4);
    }
    else {
      uStack_40 = 0x180a712b4;
      Torappu_Battle_BasicTalent_Attach_0x6011e59(lVar4);
    }
    uVar7 = uVar7 + 1;
    lVar9 = lVar9 + 8;
    uStack_40 = 0x180a712c6;
    lVar4 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1);
  } while (lVar4 != 0);
LAB_180a71406:
  uStack_40 = 0x180a7140b;
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


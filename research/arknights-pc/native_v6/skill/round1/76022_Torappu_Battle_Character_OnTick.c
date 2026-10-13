
/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_OnTick_0x60128f7(longlong *param_1,undefined8 param_2)

{
  float fVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  float fVar12;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c92630 == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c92630 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x670);
  if (lVar2 != 0) {
    if (cRam0000000188caf41c == '\0') {
      FUN_18048bf00(0x18885a700,param_1,param_2,0);
      cRam0000000188caf41c = '\x01';
    }
    if (*(longlong *)(lVar2 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar2 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar2 + 0x18) != 0) {
      uVar10 = *(undefined8 *)(*(longlong *)(lVar2 + 0x18) + 0x10);
      iVar8 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar2 + 0x38),*(undefined4 *)(lVar2 + 0x14),0);
      if (*(longlong *)(lVar2 + 0x18) != 0) {
        lVar4 = *(longlong *)(*(longlong *)(lVar2 + 0x18) + 0x20);
        if (lVar4 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar4,uVar10,param_1,0);
          auStack_40[0] = param_2;
          uVar11 = func_0x00018048b9c0(uRam000000018885a700,auStack_40);
          FUN_183cfbf40(lVar4,uVar10,uVar11,0);
          iVar9 = FUN_183f22380(uVar10,2,0,iVar8,0);
          if (iVar9 == 0) {
code_r0x0001833f996e:
            FUN_183f22fd0(uVar10,iVar8 + -1,0);
            return;
          }
          if (*(longlong *)(lVar2 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar2 + 0x18),iVar8 + -1,0);
            goto code_r0x0001833f996e;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  Torappu_Battle_Unit_OnTick_0x6012f84(param_1,param_2,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar6 = (**(code **)(*param_1 + 0x3c0))(param_1,*(undefined8 *)(*param_1 + 0x3c8));
  if (cVar6 != '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    fVar12 = (float)(**(code **)(*param_1 + 0x1010))(param_1,*(undefined8 *)(*param_1 + 0x1018));
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar10 = (**(code **)(*param_1 + 0x480))(param_1,*(undefined8 *)(*param_1 + 0x488));
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(uVar10,0,0);
    if ((cVar6 != '\0') && (fVar1 = *(float *)((longlong)param_1 + 0x4f4), fVar1 != fVar12)) {
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = func_0x0001866e44d0(fVar1,0xbf800000,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      (**(code **)(*param_1 + 0x200))(param_1,fVar12,uVar7,*(undefined8 *)(*param_1 + 0x208));
      *(float *)((longlong)param_1 + 0x4f4) = fVar12;
    }
    Torappu_Battle_Character_OnBlockModeChanged_0x60128c3(param_1,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar6 = (**(code **)(*param_1 + 4000))(param_1,*(undefined8 *)(*param_1 + 0xfa8));
    if ((cVar6 == '\0') &&
       ((cVar6 = Torappu_Battle_Entity_get_isBlockFree_0x60103d0(param_1,0), cVar6 != '\0' ||
        (cVar6 = Torappu_Battle_Entity_get_isStunned_0x60103b7(param_1,0), cVar6 != '\0')))) {
      if (param_1[0xa2] == 0) goto LAB_180a2efde;
      Torappu_Battle_BlockManager_ClearAllBlockees_0x6012d8d(param_1[0xa2],param_1,0);
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar6 = (**(code **)(*param_1 + 4000))(param_1,*(undefined8 *)(*param_1 + 0xfa8));
    if (cVar6 == '\0') {
      if (param_1[0xa2] == 0) goto LAB_180a2efde;
      Torappu_Battle_BlockManager_Tick_0x6012d94(param_1[0xa2],param_2,0);
      FUN_180005540(0xec,param_1,0);
    }
    if (param_1[0x76] == 0) {
LAB_180a2efde:
      FUN_18048c0b0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    cVar6 = Torappu_PeriodicTimer_get_isValid_0x600656e(param_1[0x76],0);
    if (cVar6 != '\0') {
      plVar3 = (longlong *)param_1[0x76];
      if (plVar3 == (longlong *)0x0) goto LAB_180a2efde;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar3);
      }
      cVar6 = (**(code **)(*plVar3 + 400))(plVar3,param_2,*(undefined8 *)(*plVar3 + 0x198));
      if (cVar6 != '\0') {
        Torappu_Battle_Character_LogSnapshotIfNot_0x60128d5(param_1,0);
      }
    }
    lVar2 = param_1[0x78];
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar6 = FUN_186b63a70(lVar2,0,0);
    if (cVar6 != '\0') {
      if (param_1[0x78] == 0) goto LAB_180a2efde;
      Torappu_Battle_BasicSkill_Tick_0x6011bd9(param_1[0x78],param_2,0);
    }
  }
  return;
}


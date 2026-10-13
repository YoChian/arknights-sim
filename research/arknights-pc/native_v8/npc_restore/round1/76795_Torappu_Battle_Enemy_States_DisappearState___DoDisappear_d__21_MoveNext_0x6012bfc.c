
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_Enemy_States_DisappearState___DoDisappear_d__21_MoveNext_0x6012bfc(longlong param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong lVar12;
  undefined1 auStack_28 [16];
  
  if (DAT_188c9297f == '\0') {
    FUN_18048bf00(&DAT_1889715e8);
    FUN_18048bf00(&DAT_1889730e8);
    FUN_18048bf00(&DAT_18892f320);
    FUN_18048bf00(&DAT_188957b60);
    FUN_18048bf00(&DAT_1888148e0);
    FUN_18048bf00(&DAT_18881f330);
    FUN_18048bf00(&DAT_18881f570);
    FUN_18048bf00(&DAT_18881f7b0);
    FUN_18048bf00(&DAT_18881f9f0);
    FUN_18048bf00(&DAT_1888e7318);
    FUN_18048bf00(&DAT_1888e70d8);
    DAT_188c9297f = '\x01';
  }
  lVar12 = *(longlong *)(param_1 + 0x20);
  if (*(int *)(param_1 + 0x10) == 0) {
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    lVar5 = func_0x00018045cfe0(_DAT_1888e7318);
    if (lVar5 != 0) {
      func_0x00018050cf60(lVar5,0);
      *(undefined8 *)(lVar5 + 0x20) = *(undefined8 *)(param_1 + 0x20);
      func_0x00018048b9e0(lVar5 + 0x20);
      if ((lVar12 != 0) &&
         (plVar6 = (longlong *)FUN_18536e540(lVar12,_DAT_188957b60), plVar6 != (longlong *)0x0)) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar6);
        }
        plVar6 = (longlong *)(**(code **)(*plVar6 + 0xb60))(plVar6,*(undefined8 *)(*plVar6 + 0xb68))
        ;
        if (plVar6 != (longlong *)0x0) {
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar6);
          }
          puVar7 = (undefined4 *)
                   (**(code **)(*plVar6 + 400))(auStack_28,plVar6,*(undefined8 *)(*plVar6 + 0x198));
          uVar2 = puVar7[1];
          uVar3 = puVar7[2];
          uVar4 = puVar7[3];
          *(undefined4 *)(lVar5 + 0x10) = *puVar7;
          *(undefined4 *)(lVar5 + 0x14) = uVar2;
          *(undefined4 *)(lVar5 + 0x18) = uVar3;
          *(undefined4 *)(lVar5 + 0x1c) = uVar4;
          if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar8 = FUN_18424e070(0);
          if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
            func_0x00018048c140(_DAT_1888e70d8);
          }
          lVar9 = *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 8);
          if (lVar9 == 0) {
            if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
              func_0x00018048c140(_DAT_1888e70d8);
            }
            uVar11 = **(undefined8 **)(_DAT_1888e70d8 + 0xb8);
            lVar9 = func_0x00018045cfe0(_DAT_1889715e8);
            if (lVar9 == 0) goto LAB_180a9deab;
            XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar9,uVar11,_DAT_18881f330,0);
            *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 8) = lVar9;
            func_0x00018048b9e0(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 8,lVar9);
          }
          lVar10 = func_0x00018045cfe0(_DAT_1889730e8);
          if (lVar10 != 0) {
            InputLongTapProgress__ctor_0x60054bf(lVar10,lVar5,_DAT_18881f7b0,0);
            if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            uVar11 = FUN_18424f2c0(lVar9,lVar10,0,0x3e19999a,0);
            uVar8 = FUN_184262620(uVar8,uVar11,0);
            if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
              func_0x00018048c140(_DAT_1888e70d8);
            }
            lVar9 = *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x10);
            if (lVar9 == 0) {
              if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
                func_0x00018048c140(_DAT_1888e70d8);
              }
              uVar11 = **(undefined8 **)(_DAT_1888e70d8 + 0xb8);
              lVar9 = func_0x00018045cfe0(_DAT_1889715e8);
              if (lVar9 == 0) goto LAB_180a9deab;
              XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar9,uVar11,_DAT_18881f570,0);
              *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x10) = lVar9;
              func_0x00018048b9e0(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x10,lVar9);
            }
            lVar10 = func_0x00018045cfe0(_DAT_1889730e8);
            if (lVar10 != 0) {
              InputLongTapProgress__ctor_0x60054bf(lVar10,lVar5,_DAT_18881f9f0,0);
              if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uVar11 = FUN_18424f2c0(lVar9,lVar10,0,0x3e19999a,0);
              uVar8 = FUN_184262620(uVar8,uVar11,0);
              uVar8 = FUN_1845f1320(uVar8,lVar12,_DAT_1888148e0);
              uVar8 = Torappu_Battle_BattleUtil_Deprecated_PlayTweenInBattle_0x60131ab(uVar8,0);
              *(undefined8 *)(lVar12 + 0x30) = uVar8;
              func_0x00018048b9e0(lVar12 + 0x30,uVar8);
              uVar8 = Torappu_Battle_AsyncUtil_WaitForFixedSeconds_0x600fa80(0x3e99999a,0);
              *(undefined8 *)(param_1 + 0x18) = uVar8;
              func_0x00018048b9e0(param_1 + 0x18,uVar8);
              *(undefined4 *)(param_1 + 0x10) = 1;
              return 1;
            }
          }
        }
      }
    }
  }
  else {
    if (*(int *)(param_1 + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
    if (lVar12 != 0) {
      FUN_184260440(*(undefined8 *)(lVar12 + 0x30),1,0);
      lVar12 = FUN_18536e540(lVar12,_DAT_188957b60);
      if (lVar12 != 0) {
        uVar8 = FUN_186b59d80(lVar12,0);
        Torappu_GameObjectUtil_SetActiveIfNecessary_0x6000681(uVar8,0,0);
        return 0;
      }
    }
  }
LAB_180a9deab:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  uVar8 = (*pcVar1)();
  return uVar8;
}


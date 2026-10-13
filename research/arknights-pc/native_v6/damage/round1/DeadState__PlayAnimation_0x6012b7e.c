/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void DeadState__PlayAnimation_0x6012b7e(longlong param_1)
{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined4 *puVar13;
  float fVar14;
  undefined8 in_stack_ffffffffffffffa8;
  undefined4 uVar15;
  undefined8 auStack_48 [3];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined1 *puStack_20;
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffffa8 >> 0x20);
  if (DAT_188c9291c == '\0') {
    FUN_18048bf00(&DAT_1889715e8);
    FUN_18048bf00(&DAT_1889730e8);
    FUN_18048bf00(&DAT_18892f320);
    FUN_18048bf00(&DAT_188884ab8);
    FUN_18048bf00(&DAT_1888d3908);
    FUN_18048bf00(&DAT_188957b60);
    FUN_18048bf00(&DAT_1888148e0);
    FUN_18048bf00(&DAT_18881e130);
    FUN_18048bf00(&DAT_18881e370);
    FUN_18048bf00(&DAT_18881e5b0);
    FUN_18048bf00(&DAT_18881e7f0);
    FUN_18048bf00(&DAT_18881ea30);
    FUN_18048bf00(&DAT_18881ec70);
    FUN_18048bf00(&DAT_1888e6e98);
    FUN_18048bf00(&DAT_1888e6c58);
    DAT_188c9291c = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188884ab8 + 0xb8) + 0x18);
  if (lVar6 == 0) {
    lVar6 = func_0x00018045cfe0(_DAT_1888e6e98);
    if (lVar6 != 0) {
      func_0x00018050cf60(lVar6,0);
      *(longlong *)(lVar6 + 0x10) = param_1;
      func_0x00018048b9e0(lVar6 + 0x10,param_1);
      lVar7 = FUN_185337c50(_DAT_1888d3908);
      lVar8 = FUN_18536e540(param_1,_DAT_188957b60);
      if (lVar8 != 0) {
        uVar9 = Torappu_Battle_Enemy_get_deadEffect_0x6012a6a(lVar8,0);
        uVar10 = FUN_18536e540(param_1,_DAT_188957b60);
        uVar11 = FUN_18536e540(param_1,_DAT_188957b60);
        if (lVar7 != 0) {
          Torappu_Battle_BattleController_CreateEffect_0x600fcd9
                    (lVar7,uVar9,uVar10,uVar11,CONCAT44(uVar15,0x3f800000),0);
          lVar7 = FUN_18536e540(param_1,_DAT_188957b60);
          if (lVar7 != 0) {
            if (*(char *)(lVar7 + 0x2fb) != '\0') {
              return;
            }
            plVar12 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
            if (plVar12 != (longlong *)0x0) {
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(*plVar12);
              }
              fVar14 = (float)(**(code **)(*plVar12 + 0x580))
                                        (plVar12,*(undefined8 *)(*plVar12 + 0x588));
              plVar12 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
              if (plVar12 != (longlong *)0x0) {
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*plVar12);
                }
                plVar12 = (longlong *)
                          (**(code **)(*plVar12 + 0xb60))(plVar12,*(undefined8 *)(*plVar12 + 0xb68))
                ;
                if (plVar12 != (longlong *)0x0) {
                  if (DAT_188ccc7f0 != '\0') {
                    func_0x000180446d00(*plVar12);
                  }
                  puVar13 = (undefined4 *)
                            (**(code **)(*plVar12 + 400))
                                      (auStack_48,plVar12,*(undefined8 *)(*plVar12 + 0x198));
                  uVar15 = puVar13[1];
                  uVar2 = puVar13[2];
                  uVar3 = puVar13[3];
                  *(undefined4 *)(lVar6 + 0x18) = *puVar13;
                  *(undefined4 *)(lVar6 + 0x1c) = uVar15;
                  *(undefined4 *)(lVar6 + 0x20) = uVar2;
                  *(undefined4 *)(lVar6 + 0x24) = uVar3;
                  if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                    func_0x00018048c140();
                  }
                  uVar9 = FUN_18424e070(0);
                  if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                    func_0x00018048c140(_DAT_1888e6c58);
                  }
                  lVar7 = *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 8);
                  if (lVar7 == 0) {
                    if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                      func_0x00018048c140(_DAT_1888e6c58);
                    }
                    uVar10 = **(undefined8 **)(_DAT_1888e6c58 + 0xb8);
                    lVar7 = func_0x00018045cfe0(_DAT_1889715e8);
                    if (lVar7 == 0) goto LAB_180a8bdd5;
                    XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar7,uVar10,_DAT_18881e130,0);
                    *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 8) = lVar7;
                    func_0x00018048b9e0(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 8,lVar7);
                  }
                  if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                    func_0x00018048c140(_DAT_1888e6c58);
                  }
                  lVar8 = *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x10);
                  if (lVar8 == 0) {
                    if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                      func_0x00018048c140(_DAT_1888e6c58);
                    }
                    uVar10 = **(undefined8 **)(_DAT_1888e6c58 + 0xb8);
                    lVar8 = func_0x00018045cfe0(_DAT_1889730e8);
                    if (lVar8 == 0) goto LAB_180a8bdd5;
                    InputLongTapProgress__ctor_0x60054bf(lVar8,uVar10,_DAT_18881e370,0);
                    *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x10) = lVar8;
                    func_0x00018048b9e0(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x10,lVar8);
                  }
                  if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                    func_0x00018048c140();
                  }
                  uVar10 = FUN_18424f2c0(lVar7,lVar8,0x3f800000,fVar14 / 3.0,0);
                  uVar9 = FUN_184262620(uVar9,uVar10,0);
                  if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                    func_0x00018048c140(_DAT_1888e6c58);
                  }
                  lVar7 = *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x18);
                  if (lVar7 == 0) {
                    if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                      func_0x00018048c140(_DAT_1888e6c58);
                    }
                    uVar10 = **(undefined8 **)(_DAT_1888e6c58 + 0xb8);
                    lVar7 = func_0x00018045cfe0(_DAT_1889715e8);
                    if (lVar7 == 0) goto LAB_180a8bdd5;
                    XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar7,uVar10,_DAT_18881e5b0,0);
                    *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x18) = lVar7;
                    func_0x00018048b9e0(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x18,lVar7);
                  }
                  lVar8 = func_0x00018045cfe0(_DAT_1889730e8);
                  if (lVar8 != 0) {
                    InputLongTapProgress__ctor_0x60054bf(lVar8,lVar6,_DAT_18881ea30,0);
                    if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                      func_0x00018048c140();
                    }
                    uVar10 = FUN_18424f2c0(lVar7,lVar8,0,fVar14 / 3.0,0);
                    uVar9 = FUN_184262620(uVar9,uVar10,0);
                    if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                      func_0x00018048c140(_DAT_1888e6c58);
                    }
                    lVar7 = *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x20);
                    if (lVar7 == 0) {
                      if (*(int *)(_DAT_1888e6c58 + 0xe0) == 0) {
                        func_0x00018048c140(_DAT_1888e6c58);
                      }
                      uVar10 = **(undefined8 **)(_DAT_1888e6c58 + 0xb8);
                      lVar7 = func_0x00018045cfe0(_DAT_1889715e8);
                      if (lVar7 == 0) goto LAB_180a8bdd5;
                      XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar7,uVar10,_DAT_18881e7f0,0);
                      *(longlong *)(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x20) = lVar7;
                      func_0x00018048b9e0(*(longlong *)(_DAT_1888e6c58 + 0xb8) + 0x20,lVar7);
                    }
                    lVar8 = func_0x00018045cfe0(_DAT_1889730e8);
                    if (lVar8 != 0) {
                      InputLongTapProgress__ctor_0x60054bf(lVar8,lVar6,_DAT_18881ec70,0);
                      if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                        func_0x00018048c140();
                      }
                      uVar10 = FUN_18424f2c0(lVar7,lVar8,0,fVar14 / 3.0,0);
                      uVar9 = FUN_184262620(uVar9,uVar10,0);
                      uVar9 = FUN_1845f1320(uVar9,param_1,_DAT_1888148e0);
                      uVar9 = Torappu_Battle_BattleUtil_Deprecated_PlayTweenInBattle_0x60131ab
                                        (uVar9,0);
                      if (param_1 != 0) {
                        *(undefined8 *)(param_1 + 0x18) = uVar9;
                        func_0x00018048b9e0(param_1 + 0x18,uVar9);
                        return;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
LAB_180a8bdd5:
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &stack0x00000020;
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar9 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar7 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar7 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar7,uVar9,param_1,0);
        auStack_48[0] = 0;
        iVar5 = FUN_183f22380(uVar9,1,0,iVar4);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar9,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001833100e8;
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

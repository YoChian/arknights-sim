
/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_States_DisappearState_OnExit_0x6012beb
               (longlong param_1,undefined4 param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  undefined4 *puVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  
  if (DAT_188c92976 == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_1888e5f78);
    FUN_18048bf00(&DAT_188884f30);
    FUN_18048bf00(&DAT_188957260);
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c92976 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x40);
  if (lVar9 == 0) {
    func_0x00018050cf60(param_1,param_2,_DAT_188957260);
    if (*(int *)(_DAT_1888e5f78 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar5 = Torappu_Battle_CoroutineId_get_isValid_0x600fae2(param_1 + 0x18,0);
    if (cVar5 != '\0') {
      uVar8 = FUN_18536e540(param_1,_DAT_188957b60);
      uStack_28 = *(undefined8 **)(param_1 + 0x18);
      uStack_20 = *(undefined1 **)(param_1 + 0x20);
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      Torappu_Battle_BattleController_StopBattleCoroutine_0x600fce9(uVar8,&uStack_28,0);
      if (*(int *)(_DAT_1888e5f78 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      Torappu_Battle_CoroutineId_MarkInvalid_0x600fae3(param_1 + 0x18,0);
    }
    lVar9 = FUN_18536e540(param_1,_DAT_188957b60);
    if ((lVar9 == 0) ||
       (lVar9 = Torappu_Battle_Entity_get_attributes_0x6010337(lVar9,0), lVar9 == 0)) {
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    Torappu_Battle_Attributes_RemoveModifier_0x600fb13(lVar9,param_1,0);
    if (cRam0000000188c92979 == '\0') {
      FUN_18048bf00(0x1889715e8,0);
      FUN_18048bf00(0x1889730e8);
      FUN_18048bf00(0x18892f320);
      FUN_18048bf00(&DAT_188884f30);
      FUN_18048bf00(&DAT_188957b60);
      FUN_18048bf00(0x1888148e0);
      FUN_18048bf00(0x18881eeb0);
      FUN_18048bf00(0x18881f0f0);
      FUN_18048bf00(0x18881fc30);
      FUN_18048bf00(0x18881fe70);
      FUN_18048bf00(0x1888e7558);
      FUN_18048bf00(0x1888e70d8);
      cRam0000000188c92979 = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x58);
    if (lVar9 == 0) {
      lVar9 = func_0x00018045cfe0(uRam00000001888e7558);
      if (lVar9 != 0) {
        func_0x00018050cf60(lVar9,0);
        *(longlong *)(lVar9 + 0x20) = param_1;
        func_0x00018048b9e0(lVar9 + 0x20,param_1);
        lVar10 = FUN_18536e540(param_1,_DAT_188957b60);
        if (lVar10 != 0) {
          uVar8 = FUN_186b59d80(lVar10,0);
          Torappu_GameObjectUtil_SetActiveIfNecessary_0x6000681(uVar8,1,0);
          lVar10 = FUN_18536e540(param_1,_DAT_188957b60);
          if (lVar10 != 0) {
            puVar11 = (undefined4 *)
                      Torappu_Battle_Entity_GetBodyColor_0x601041d(&uStack_28,lVar10,0);
            uVar2 = puVar11[1];
            uVar3 = puVar11[2];
            uVar4 = puVar11[3];
            *(undefined4 *)(lVar9 + 0x10) = *puVar11;
            *(undefined4 *)(lVar9 + 0x14) = uVar2;
            *(undefined4 *)(lVar9 + 0x18) = uVar3;
            *(undefined4 *)(lVar9 + 0x1c) = uVar4;
            lVar10 = FUN_18536e540(param_1,_DAT_188957b60);
            if (lVar10 != 0) {
              cVar5 = Torappu_Battle_Enemy_get_disableAppearTweenColor_0x60129f7(lVar10,0);
              if (cVar5 == '\0') {
                plVar12 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
                if (plVar12 == (longlong *)0x0) goto DAT_180a8d9fa;
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*plVar12);
                }
                uStack_28 = (undefined8 *)0x0;
                uStack_20 = (undefined1 *)0x3f80000000000000;
                (**(code **)(*plVar12 + 0x560))
                          (plVar12,&uStack_28,*(undefined8 *)(*plVar12 + 0x568));
                if (*(int *)(lRam000000018892f320 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                uVar8 = FUN_18424e070(0);
                if (*(int *)(lRam00000001888e70d8 + 0xe0) == 0) {
                  func_0x00018048c140(lRam00000001888e70d8);
                }
                lVar10 = *(longlong *)(*(longlong *)(lRam00000001888e70d8 + 0xb8) + 0x18);
                if (lVar10 == 0) {
                  if (*(int *)(lRam00000001888e70d8 + 0xe0) == 0) {
                    func_0x00018048c140(lRam00000001888e70d8);
                  }
                  uVar14 = **(undefined8 **)(lRam00000001888e70d8 + 0xb8);
                  lVar10 = func_0x00018045cfe0(uRam00000001889715e8);
                  if (lVar10 == 0) goto DAT_180a8d9fa;
                  XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar10,uVar14,uRam000000018881eeb0,0);
                  *(longlong *)(*(longlong *)(lRam00000001888e70d8 + 0xb8) + 0x18) = lVar10;
                  func_0x00018048b9e0(*(longlong *)(lRam00000001888e70d8 + 0xb8) + 0x18,lVar10);
                }
                lVar13 = func_0x00018045cfe0(uRam00000001889730e8);
                if (lVar13 == 0) goto DAT_180a8d9fa;
                InputLongTapProgress__ctor_0x60054bf(lVar13,lVar9,uRam000000018881fc30,0);
                if (*(int *)(lRam000000018892f320 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                uStack_38 = 0;
                uVar14 = FUN_18424f2c0(lVar10,lVar13,0x3f800000,0x3e19999a);
                uVar8 = FUN_184262620(uVar8,uVar14,0);
                if (*(int *)(lRam00000001888e70d8 + 0xe0) == 0) {
                  func_0x00018048c140(lRam00000001888e70d8);
                }
                lVar10 = *(longlong *)(*(longlong *)(lRam00000001888e70d8 + 0xb8) + 0x20);
                if (lVar10 == 0) {
                  if (*(int *)(lRam00000001888e70d8 + 0xe0) == 0) {
                    func_0x00018048c140(lRam00000001888e70d8);
                  }
                  uVar14 = **(undefined8 **)(lRam00000001888e70d8 + 0xb8);
                  lVar10 = func_0x00018045cfe0(uRam00000001889715e8);
                  if (lVar10 == 0) goto DAT_180a8d9fa;
                  XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar10,uVar14,uRam000000018881f0f0,0);
                  *(longlong *)(*(longlong *)(lRam00000001888e70d8 + 0xb8) + 0x20) = lVar10;
                  func_0x00018048b9e0(*(longlong *)(lRam00000001888e70d8 + 0xb8) + 0x20,lVar10);
                }
                lVar13 = func_0x00018045cfe0(uRam00000001889730e8);
                if (lVar13 == 0) goto DAT_180a8d9fa;
                InputLongTapProgress__ctor_0x60054bf(lVar13,lVar9,uRam000000018881fe70,0);
                if (*(int *)(lRam000000018892f320 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                uStack_38 = 0;
                uVar14 = FUN_18424f2c0(lVar10,lVar13,0x3f800000,0x3e19999a);
                uVar8 = FUN_184262620(uVar8,uVar14,0);
                uVar8 = FUN_1845f1320(uVar8,param_1,uRam00000001888148e0);
                Torappu_Battle_BattleUtil_Deprecated_PlayTweenInBattle_0x60131ab(uVar8,0);
              }
              else {
                if (cRam0000000188c9297a == '\0') {
                  FUN_18048bf00(&DAT_188884f30);
                  FUN_18048bf00(&DAT_188957b60);
                  cRam0000000188c9297a = '\x01';
                }
                lVar9 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x60);
                if (lVar9 == 0) {
                  FUN_184260440(*(undefined8 *)(param_1 + 0x30),1);
                  lVar9 = FUN_18536e540(param_1,_DAT_188957b60);
                  if (lVar9 == 0) goto DAT_180a8d9fa;
                  puVar11 = (undefined4 *)
                            Torappu_Battle_Entity_GetBodyColor_0x601041d(&uStack_28,lVar9,0);
                  uVar2 = *puVar11;
                  uVar3 = puVar11[1];
                  uVar4 = puVar11[2];
                  plVar12 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
                  if (plVar12 == (longlong *)0x0) goto DAT_180a8d9fa;
                  uStack_20._4_4_ = 0x3f800000;
                  uStack_28._0_4_ = uVar2;
                  uStack_28._4_4_ = uVar3;
                  uStack_20._0_4_ = uVar4;
                  if (DAT_188ccc7f0 != '\0') {
                    func_0x000180446d00(*plVar12);
                  }
                  (**(code **)(*plVar12 + 0x560))
                            (plVar12,&uStack_28,*(undefined8 *)(*plVar12 + 0x568));
                }
                else {
                  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar9,param_1,0);
                }
              }
              lVar9 = FUN_18536e540(param_1);
              if (lVar9 != 0) {
                if (cRam0000000188c927e0 == '\0') {
                  puStack_30 = &UNK_180a80fa5;
                  FUN_18048bf00(0x18881b6b0,0,0);
                  cRam0000000188c927e0 = '\x01';
                }
                if (*(int *)(lRam000000018881b6b0 + 0xe0) == 0) {
                  puStack_30 = &UNK_180a80fc4;
                  func_0x00018048c140(lRam000000018881b6b0);
                }
                lVar10 = *(longlong *)(*(longlong *)(lRam000000018881b6b0 + 0xb8) + 0x40);
                if (lVar10 == 0) {
                  *(undefined1 *)(lVar9 + 0x3c8) = 0;
                  return;
                }
                if (*(longlong *)(lVar10 + 0x18) == 0) {
                  FUN_18048c0b0(lVar10,lVar9,0,0);
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
                auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30);
                uStack_38 = 0;
                puStack_30 = &stack0x00000008;
                uStack_28 = auStack_48;
                FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
                if (*(longlong *)(lVar10 + 0x18) != 0) {
                  uVar8 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
                  iVar6 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar10 + 0x38),
                                        *(undefined4 *)(lVar10 + 0x14),0);
                  if (*(longlong *)(lVar10 + 0x18) != 0) {
                    lVar13 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
                    if (lVar13 == 0) {
                      FUN_18048c0b0();
                    }
                    else {
                      FUN_183cf8c20(lVar13,uVar8,lVar9,0);
                      FUN_183f22430(uVar8,0,0);
                      iVar7 = FUN_183f22380(uVar8,2,0,iVar6,0);
                      if (iVar7 == 0) {
code_r0x0001833006e0:
                        FUN_183f22fd0(uVar8,iVar6 + -1,0);
                        return;
                      }
                      if (*(longlong *)(lVar10 + 0x18) != 0) {
                        FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar6 + -1,0);
                        goto code_r0x0001833006e0;
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
            }
          }
        }
      }
DAT_180a8d9fa:
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if (*(longlong *)(lVar9 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    puStack_30 = (undefined *)0x0;
    uStack_28 = (undefined8 *)&stack0x00000008;
    uStack_20 = &stack0x00000020;
    FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30),&stack0x00000008,0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      uVar8 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
      iVar6 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        lVar10 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
        if (lVar10 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar10,uVar8,param_1,0);
          auStack_48[0] = 0;
          iVar7 = FUN_183f22380(uVar8,1,0,iVar6);
          if (iVar7 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar8,iVar6 + -1,0);
            return;
          }
          if (*(longlong *)(lVar9 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar6 + -1,0);
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
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0(lVar9,param_1,param_2,0);
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  uStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar8 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar10 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar10 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar10,uVar8,param_1,0);
        FUN_183f25080(uVar8,param_2,0);
        iVar7 = FUN_183f22380(uVar8,2,0,iVar6,0);
        if (iVar7 == 0) {
code_r0x0001834c0f1e:
          FUN_183f22fd0(uVar8,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar6 + -1,0);
          goto code_r0x0001834c0f1e;
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


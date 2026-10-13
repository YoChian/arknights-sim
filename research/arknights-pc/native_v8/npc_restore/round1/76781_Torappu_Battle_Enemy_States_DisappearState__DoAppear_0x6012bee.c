
/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_States_DisappearState__DoAppear_0x6012bee(longlong param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined4 *puVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  
  if (DAT_188c92979 == '\0') {
    FUN_18048bf00(&DAT_1889715e8);
    FUN_18048bf00(&DAT_1889730e8);
    FUN_18048bf00(&DAT_18892f320);
    FUN_18048bf00(&DAT_188884f30);
    FUN_18048bf00(&DAT_188957b60);
    FUN_18048bf00(&DAT_1888148e0);
    FUN_18048bf00(&DAT_18881eeb0);
    FUN_18048bf00(&DAT_18881f0f0);
    FUN_18048bf00(&DAT_18881fc30);
    FUN_18048bf00(&DAT_18881fe70);
    FUN_18048bf00(&DAT_1888e7558);
    FUN_18048bf00(&DAT_1888e70d8);
    DAT_188c92979 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x58);
  if (lVar8 == 0) {
    lVar8 = func_0x00018045cfe0(_DAT_1888e7558);
    if (lVar8 != 0) {
      func_0x00018050cf60(lVar8,0);
      *(longlong *)(lVar8 + 0x20) = param_1;
      func_0x00018048b9e0(lVar8 + 0x20,param_1);
      lVar9 = FUN_18536e540(param_1,_DAT_188957b60);
      if (lVar9 != 0) {
        uVar10 = FUN_186b59d80(lVar9,0);
        Torappu_GameObjectUtil_SetActiveIfNecessary_0x6000681(uVar10,1,0);
        lVar9 = FUN_18536e540(param_1,_DAT_188957b60);
        if (lVar9 != 0) {
          puVar11 = (undefined4 *)Torappu_Battle_Entity_GetBodyColor_0x601041d(&uStack_28,lVar9,0);
          uVar2 = puVar11[1];
          uVar3 = puVar11[2];
          uVar4 = puVar11[3];
          *(undefined4 *)(lVar8 + 0x10) = *puVar11;
          *(undefined4 *)(lVar8 + 0x14) = uVar2;
          *(undefined4 *)(lVar8 + 0x18) = uVar3;
          *(undefined4 *)(lVar8 + 0x1c) = uVar4;
          lVar9 = FUN_18536e540(param_1,_DAT_188957b60);
          if (lVar9 != 0) {
            cVar5 = Torappu_Battle_Enemy_get_disableAppearTweenColor_0x60129f7(lVar9,0);
            if (cVar5 == '\0') {
              plVar12 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
              if (plVar12 == (longlong *)0x0) goto LAB_180a8d9fa;
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(*plVar12);
              }
              uStack_28 = (undefined8 *)0x0;
              uStack_20 = (undefined1 *)0x3f80000000000000;
              (**(code **)(*plVar12 + 0x560))(plVar12,&uStack_28,*(undefined8 *)(*plVar12 + 0x568));
              if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uVar10 = FUN_18424e070(0);
              if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
                func_0x00018048c140(_DAT_1888e70d8);
              }
              lVar9 = *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x18);
              if (lVar9 == 0) {
                if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
                  func_0x00018048c140(_DAT_1888e70d8);
                }
                uVar14 = **(undefined8 **)(_DAT_1888e70d8 + 0xb8);
                lVar9 = func_0x00018045cfe0(_DAT_1889715e8);
                if (lVar9 == 0) goto LAB_180a8d9fa;
                XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar9,uVar14,_DAT_18881eeb0,0);
                *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x18) = lVar9;
                func_0x00018048b9e0(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x18,lVar9);
              }
              lVar13 = func_0x00018045cfe0(_DAT_1889730e8);
              if (lVar13 == 0) goto LAB_180a8d9fa;
              InputLongTapProgress__ctor_0x60054bf(lVar13,lVar8,_DAT_18881fc30,0);
              if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uStack_38 = 0;
              uVar14 = FUN_18424f2c0(lVar9,lVar13,0x3f800000,0x3e19999a);
              uVar10 = FUN_184262620(uVar10,uVar14,0);
              if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
                func_0x00018048c140(_DAT_1888e70d8);
              }
              lVar9 = *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x20);
              if (lVar9 == 0) {
                if (*(int *)(_DAT_1888e70d8 + 0xe0) == 0) {
                  func_0x00018048c140(_DAT_1888e70d8);
                }
                uVar14 = **(undefined8 **)(_DAT_1888e70d8 + 0xb8);
                lVar9 = func_0x00018045cfe0(_DAT_1889715e8);
                if (lVar9 == 0) goto LAB_180a8d9fa;
                XLua___XLua_Gen_Delegate11__ctor_0x6001100(lVar9,uVar14,_DAT_18881f0f0,0);
                *(longlong *)(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x20) = lVar9;
                func_0x00018048b9e0(*(longlong *)(_DAT_1888e70d8 + 0xb8) + 0x20,lVar9);
              }
              lVar13 = func_0x00018045cfe0(_DAT_1889730e8);
              if (lVar13 == 0) goto LAB_180a8d9fa;
              InputLongTapProgress__ctor_0x60054bf(lVar13,lVar8,_DAT_18881fe70,0);
              if (*(int *)(_DAT_18892f320 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uStack_38 = 0;
              uVar14 = FUN_18424f2c0(lVar9,lVar13,0x3f800000,0x3e19999a);
              uVar10 = FUN_184262620(uVar10,uVar14,0);
              uVar10 = FUN_1845f1320(uVar10,param_1,_DAT_1888148e0);
              Torappu_Battle_BattleUtil_Deprecated_PlayTweenInBattle_0x60131ab(uVar10,0);
            }
            else {
              if (DAT_188c9297a == '\0') {
                FUN_18048bf00(&DAT_188884f30);
                FUN_18048bf00(&DAT_188957b60);
                DAT_188c9297a = '\x01';
              }
              lVar8 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x60);
              if (lVar8 == 0) {
                FUN_184260440(*(undefined8 *)(param_1 + 0x30),1);
                lVar8 = FUN_18536e540(param_1,_DAT_188957b60);
                if (lVar8 == 0) goto LAB_180a8d9fa;
                puVar11 = (undefined4 *)
                          Torappu_Battle_Entity_GetBodyColor_0x601041d(&uStack_28,lVar8,0);
                uVar2 = *puVar11;
                uVar3 = puVar11[1];
                uVar4 = puVar11[2];
                plVar12 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
                if (plVar12 == (longlong *)0x0) goto LAB_180a8d9fa;
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
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar8,param_1,0);
              }
            }
            lVar8 = FUN_18536e540(param_1);
            if (lVar8 != 0) {
              if (cRam0000000188c927e0 == '\0') {
                puStack_30 = &UNK_180a80fa5;
                FUN_18048bf00(0x18881b6b0,0,0);
                cRam0000000188c927e0 = '\x01';
              }
              if (*(int *)(lRam000000018881b6b0 + 0xe0) == 0) {
                puStack_30 = &UNK_180a80fc4;
                func_0x00018048c140(lRam000000018881b6b0);
              }
              lVar9 = *(longlong *)(*(longlong *)(lRam000000018881b6b0 + 0xb8) + 0x40);
              if (lVar9 == 0) {
                *(undefined1 *)(lVar8 + 0x3c8) = 0;
                return;
              }
              if (*(longlong *)(lVar9 + 0x18) == 0) {
                FUN_18048c0b0(lVar9,lVar8,0,0);
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
                uVar10 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
                iVar6 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar9 + 0x38),
                                      *(undefined4 *)(lVar9 + 0x14),0);
                if (*(longlong *)(lVar9 + 0x18) != 0) {
                  lVar13 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
                  if (lVar13 == 0) {
                    FUN_18048c0b0();
                  }
                  else {
                    FUN_183cf8c20(lVar13,uVar10,lVar8,0);
                    FUN_183f22430(uVar10,0,0);
                    iVar7 = FUN_183f22380(uVar10,2,0,iVar6,0);
                    if (iVar7 == 0) {
code_r0x0001833006e0:
                      FUN_183f22fd0(uVar10,iVar6 + -1,0);
                      return;
                    }
                    if (*(longlong *)(lVar9 + 0x18) != 0) {
                      FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar6 + -1,0);
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
LAB_180a8d9fa:
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  puStack_30 = (undefined *)0x0;
  uStack_28 = (undefined8 *)&stack0x00000008;
  uStack_20 = &stack0x00000020;
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar8 + 0x18) != 0) {
    uVar10 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar9 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar9,uVar10,param_1,0);
        auStack_48[0] = 0;
        iVar7 = FUN_183f22380(uVar10,1,0,iVar6);
        if (iVar7 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar10,iVar6 + -1,0);
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
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


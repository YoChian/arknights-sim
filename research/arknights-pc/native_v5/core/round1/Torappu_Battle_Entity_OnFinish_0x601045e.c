
/* WARNING: Removing unreachable block (ram,0x00018333b158) */
/* WARNING: Removing unreachable block (ram,0x000183333d78) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_OnFinish_0x601045e(longlong *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong *plVar10;
  char cVar11;
  bool bVar12;
  int aiStack_48 [2];
  undefined8 auStack_40 [2];
  undefined *puStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c908ed == '\0') {
    puStack_30 = (undefined *)0x1806f8c64;
    FUN_18048bf00(&DAT_18886c268);
    puStack_30 = (undefined *)0x1806f8c70;
    FUN_18048bf00(&DAT_18891de98);
    puStack_30 = (undefined *)0x1806f8c7c;
    FUN_18048bf00(&DAT_188841368);
    puStack_30 = (undefined *)0x1806f8c88;
    FUN_18048bf00(&DAT_188932ce8);
    puStack_30 = (undefined *)0x1806f8c94;
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c908ed = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined *)0x1806f8cb0;
    func_0x00018048c140();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x908);
  if (lVar5 != 0) {
    if (cRam0000000188cafcfd == '\0') {
      FUN_18048bf00(0x1888735a0,param_1,param_2,0);
      cRam0000000188cafcfd = '\x01';
    }
    if (*(longlong *)(lVar5 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
    puStack_30 = (undefined *)0x0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      uVar7 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
      iVar2 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0);
      if (*(longlong *)(lVar5 + 0x18) != 0) {
        lVar9 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
        if (lVar9 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar9,uVar7,param_1,0);
          aiStack_48[0] = param_2;
          uVar8 = func_0x00018048b9c0(uRam00000001888735a0,aiStack_48);
          FUN_183cfbf40(lVar9,uVar7,uVar8,0);
          iVar3 = FUN_183f22380(uVar7,2,0,iVar2,0);
          if (iVar3 == 0) {
code_r0x000183333d5e:
            FUN_183f22fd0(uVar7,iVar2 + -1,0);
            return;
          }
          if (*(longlong *)(lVar5 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar2 + -1,0);
            goto code_r0x000183333d5e;
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
  if (DAT_188c907e3 == '\0') {
    puStack_30 = (undefined *)0x1806f8ce3;
    FUN_18048bf00(&DAT_188841368);
    puStack_30 = (undefined *)0x1806f8cef;
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c907e3 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined *)0x1806f8d0b;
    func_0x00018048c140();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xb0);
  if (lVar5 == 0) {
    puStack_30 = (undefined *)0x1806f8d40;
    lVar5 = FUN_185337c50(_DAT_1888d3908);
    if (lVar5 == 0) goto LAB_1806f90d7;
    puStack_30 = (undefined *)0x1806f8d53;
    lVar5 = Torappu_Battle_BattleController_get_context_0x600fbfa(lVar5,0);
  }
  else {
    puStack_30 = (undefined *)0x1806f8d60;
    lVar5 = XLua_DelegateBridge___Gen_Delegate_Imp2632_0x60014a8(lVar5,param_1,0);
  }
  if ((lVar5 == 0) || (*(longlong *)(lVar5 + 0x10) == 0)) goto LAB_1806f90d7;
  puStack_30 = (undefined *)0x1806f8d82;
  plVar6 = (longlong *)FUN_185733380(*(longlong *)(lVar5 + 0x10),_DAT_18891de98);
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined *)0x1806f8d9a;
    func_0x00018048c140();
  }
  if (DAT_188c90929 == '\0') {
    puStack_30 = (undefined *)0x1806f8daf;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c90929 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined *)0x1806f8dcb;
    func_0x00018048c140();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xae8);
  if (lVar5 == 0) {
    if (((param_2 - 2U & 0xfffffffc) != 0) || (param_2 == 4)) {
      cVar11 = param_2 == 8;
      goto LAB_1806f8e06;
    }
LAB_1806f8e0e:
    puStack_30 = (undefined *)0x1806f8e1a;
    lVar5 = FUN_185337c50(_DAT_1888d3908);
    if (lVar5 == 0) goto LAB_1806f90d7;
    puStack_30 = (undefined *)0x1806f8e2d;
    lVar5 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar5,0);
    if (lVar5 != 0) {
      if (plVar6 == (longlong *)0x0) {
        plVar10 = (longlong *)0x0;
      }
      else {
        lVar5 = *plVar6;
        if (DAT_188ccc7f0 == '\0') {
          if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_18886c268 + 0x130)) ||
             (bVar12 = true,
             *(longlong *)
              (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_18886c268 + 0x130) * 8)
             != _DAT_18886c268)) {
            bVar12 = false;
          }
          bVar12 = !bVar12;
        }
        else {
          puStack_30 = (undefined *)0x1806f8e5a;
          cVar11 = func_0x0001804463e0(lVar5);
          bVar12 = cVar11 == '\0';
        }
        plVar10 = (longlong *)0x0;
        if (!bVar12) {
          plVar10 = plVar6;
        }
      }
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        puStack_30 = (undefined *)0x1806f8ea5;
        func_0x00018048c140();
      }
      puStack_30 = (undefined *)0x1806f8eb2;
      cVar11 = FUN_186b63a70(plVar10,0,0);
      if (cVar11 != '\0') {
        puStack_30 = (undefined *)0x1806f8ec2;
        lVar5 = FUN_185337c50(_DAT_1888d3908);
        if (lVar5 == 0) goto LAB_1806f90d7;
        puStack_30 = (undefined *)0x1806f8ed5;
        lVar5 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar5,0);
        if (plVar10 == (longlong *)0x0) goto LAB_1806f90d7;
        puStack_30 = (undefined *)0x1806f8eeb;
        uVar7 = Torappu_Battle_Entity_get_id_0x6010328(plVar10,0);
        if (lVar5 == 0) goto LAB_1806f90d7;
        puStack_30 = (undefined *)0x1806f8f02;
        Torappu_Battle_BattleLogger_LogExtraBattleInfoCharacterKillCount_0x60105b0(lVar5,uVar7,0);
      }
      if (param_2 == 3) {
        puStack_30 = (undefined *)0x1806f8f13;
        lVar5 = FUN_185337c50(_DAT_1888d3908);
        if (lVar5 == 0) goto LAB_1806f90d7;
        puStack_30 = (undefined *)0x1806f8f26;
        lVar5 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar5,0);
        puStack_30 = (undefined *)0x1806f8f33;
        uVar7 = Torappu_Battle_Entity_get_id_0x6010328(param_1,0);
        if (lVar5 == 0) goto LAB_1806f90d7;
        puStack_30 = (undefined *)0x1806f8f4a;
        Torappu_Battle_BattleLogger_LogExtraBattleInfoEnemyDieBecauseOfFallDown_0x60105b1
                  (lVar5,uVar7,0);
      }
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      puStack_30 = (undefined *)0x1806f8f5f;
      func_0x00018048c140();
    }
    puStack_30 = (undefined *)0x1806f8f6c;
    cVar11 = FUN_186b63a70(plVar6,0,0);
    if (cVar11 != '\0') {
      if (plVar6 == (longlong *)0x0) goto LAB_1806f90d7;
      if (DAT_188c90923 == '\0') {
        puStack_30 = (undefined *)0x1806f8f92;
        FUN_18048bf00(&DAT_188841368);
        DAT_188c90923 = '\x01';
      }
      if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
        puStack_30 = (undefined *)0x1806f8fb1;
        func_0x00018048c140(_DAT_188841368);
      }
      lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xab8);
      if (lVar5 == 0) {
        puStack_30 = (undefined *)0x1806f8fd5;
        lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(plVar6,0);
        if (lVar5 == 0) goto LAB_1806f90d7;
        puStack_30 = (undefined *)0x1806f8fec;
        BuffContainer_OnTargetKilled_0x600ff76(lVar5,param_1,0);
      }
      else {
        puStack_30 = (undefined *)0x1806f8ffc;
        XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar5,plVar6,param_1,0);
      }
    }
    puStack_30 = (undefined *)0x1806f900c;
    Torappu_Battle_Entity_EmitEvent_0x601049c(param_1,1,0);
  }
  else {
    puStack_30 = (undefined *)0x1806f8e06;
    cVar11 = XLua_DelegateBridge___Gen_Delegate_Imp3072_0x6001660(lVar5,param_2,0);
LAB_1806f8e06:
    if (cVar11 != '\0') goto LAB_1806f8e0e;
  }
  puStack_30 = (undefined *)0x1806f9016;
  lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
  if (lVar5 != 0) {
    puStack_30 = (undefined *)0x1806f902f;
    BuffContainer_OnOwnerFinish_0x600ff5e(lVar5,param_2,plVar6,0);
    puStack_30 = (undefined *)0x1806f9039;
    lVar5 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    if (lVar5 != 0) {
      puStack_30 = (undefined *)0x1806f904f;
      BuffContainer_Clear_0x600ff4e(lVar5,1,0);
      if (DAT_188ccc7f0 != '\0') {
        puStack_30 = (undefined *)0x1806f9060;
        func_0x000180446d00(*param_1);
      }
      puStack_30 = (undefined *)0x1806f9076;
      (**(code **)(*param_1 + 0x8a0))(param_1,*(undefined8 *)(*param_1 + 0x8a8));
      puStack_30 = (undefined *)0x1806f9080;
      Torappu_Battle_Entity_ClearHoldEffects_0x6010451(param_1,0);
      if (param_1[0x20] != 0) {
        puStack_30 = (undefined *)0x1806f9093;
        EPController_OnFinish_0x60104c6(param_1[0x20],0);
        if (cRam0000000188c9092b == '\0') {
          puStack_30 = &UNK_1806f2724;
          FUN_18048bf00(&DAT_188841368);
          puStack_30 = &UNK_1806f2730;
          FUN_18048bf00(0x188819760);
          cRam0000000188c9092b = '\x01';
        }
        if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
          puStack_30 = &UNK_1806f274f;
          func_0x00018048c140(_DAT_188841368);
        }
        lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xaf8);
        if (lVar5 == 0) {
          lVar5 = param_1[0x17];
          if (lVar5 == 0) {
            puStack_30 = &UNK_1806f27ad;
            FUN_18048c0b0();
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          puStack_30 = &UNK_1848dca8e;
          uVar4 = func_0x0001844dc660(2,**(undefined8 **)
                                          (*(longlong *)(lRam0000000188819760 + 0x20) + 0xc0));
          if (lVar5 != 0) {
            puStack_30 = &UNK_1848dcaa7;
            lVar9 = FUN_18672ebc0(lVar5,*(undefined8 *)(lVar5 + 0x10),uVar4,0);
            if (lVar9 != 0) {
              puStack_30 = &UNK_1848dcaba;
              FUN_18672d3c0(lVar9,0,0);
              puStack_30 = &UNK_1848dcacc;
              lVar9 = FUN_18672ebc0(lVar5,*(undefined8 *)(lVar5 + 0x18),uVar4,0);
              if (lVar9 != 0) {
                puStack_30 = &UNK_1848dcadf;
                FUN_18672d3c0(lVar9,0,0);
                lVar5 = *(longlong *)(lVar5 + 0x18);
                if (cRam0000000188cc3a06 == '\0') {
                  puStack_30 = &UNK_18672ee05;
                  FUN_18048bf00(0x1888f5540,lVar5,uVar4,0);
                  puStack_30 = &UNK_18672ee11;
                  FUN_18048bf00(0x1888f59c0);
                  puStack_30 = &UNK_18672ee1d;
                  FUN_18048bf00(0x1888f5c00);
                  puStack_30 = &UNK_18672ee29;
                  FUN_18048bf00(0x18884e2e8);
                  puStack_30 = &UNK_18672ee35;
                  FUN_18048bf00(0x1888b5590);
                  cRam0000000188cc3a06 = '\x01';
                }
                if (lVar5 != 0) {
                  puStack_30 = &UNK_18672ee5b;
                  cVar11 = FUN_1857c6f10(lVar5,uVar4,uRam00000001888f5540);
                  if (cVar11 == '\0') {
                    return;
                  }
                  puStack_30 = &UNK_18672ee70;
                  lVar9 = FUN_1857ed6c0(lVar5,uVar4,uRam00000001888f5c00);
                  puStack_30 = &UNK_18672ee84;
                  FUN_1857de990(lVar5,uVar4,uRam00000001888f59c0);
                  if (lVar9 != 0) {
                    puStack_30 = &UNK_18672ee93;
                    FUN_18672d6e0(lVar9,0);
                    if (*(int *)(lRam000000018884e2e8 + 0xe0) == 0) {
                      puStack_30 = &UNK_18672eeab;
                      func_0x00018048c140(lRam000000018884e2e8);
                    }
                    if (**(longlong **)(lRam000000018884e2e8 + 0xb8) != 0) {
                      puStack_30 = &UNK_18672eed0;
                      FUN_1805072d0(**(longlong **)(lRam000000018884e2e8 + 0xb8),lVar9,
                                    uRam00000001888b5590);
                      return;
                    }
                  }
                }
                puStack_30 = &UNK_18672eee5;
                FUN_18048c0b0();
                pcVar1 = (code *)swi(3);
                (*pcVar1)();
                return;
              }
            }
          }
          puStack_30 = &UNK_1848dcb05;
          FUN_18048c0b0();
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        if (cRam0000000188cafd27 == '\0') {
          FUN_18048bf00(0x188873360,param_1,2,0);
          cRam0000000188cafd27 = '\x01';
        }
        if (*(longlong *)(lVar5 + 0x18) == 0) {
          FUN_18048c0b0();
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
        puStack_30 = (undefined *)0x0;
        puStack_28 = &stack0x00000008;
        puStack_20 = auStack_40;
        FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
        if (*(longlong *)(lVar5 + 0x18) != 0) {
          uVar7 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
          iVar2 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0)
          ;
          if (*(longlong *)(lVar5 + 0x18) != 0) {
            lVar9 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
            if (lVar9 == 0) {
              FUN_18048c0b0();
            }
            else {
              FUN_183cf8c20(lVar9,uVar7,param_1,0);
              aiStack_48[0] = 2;
              uVar8 = func_0x00018048b9c0(uRam0000000188873360,aiStack_48);
              FUN_183cfbf40(lVar9,uVar7,uVar8,0);
              iVar3 = FUN_183f22380(uVar7,2,0,iVar2,0);
              if (iVar3 == 0) {
code_r0x00018333b13e:
                FUN_183f22fd0(uVar7,iVar2 + -1,0);
                return;
              }
              if (*(longlong *)(lVar5 + 0x18) != 0) {
                FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar2 + -1,0);
                goto code_r0x00018333b13e;
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
LAB_1806f90d7:
  puStack_30 = (undefined *)0x1806f90dc;
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


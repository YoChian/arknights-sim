
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Removing unreachable block (ram,0x0001836501b1) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Unit_OnInit_0x6012f62(longlong *param_1,undefined8 param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 *puVar6;
  longlong lVar7;
  undefined8 uVar8;
  longlong *plVar9;
  ushort uVar10;
  longlong lVar11;
  uint uVar12;
  undefined8 auStack_48 [2];
  ulonglong uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  longlong lStack_20;
  
  if (DAT_188c92be3 == '\0') {
    FUN_18048bf00(&DAT_18893b8a8);
    FUN_18048bf00(&DAT_188833298);
    FUN_18048bf00(&DAT_188805040);
    DAT_188c92be3 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x348);
  if (lVar7 == 0) {
    Torappu_Battle_Entity_OnInit_0x6010462(param_1,param_2,0);
    lVar7 = param_1[0x34];
    uVar12 = 0;
    if (lVar7 != 0) {
      lVar11 = 0x20;
      do {
        if (*(int *)(lVar7 + 0x18) <= (int)uVar12) {
          Torappu_Battle_Unit_InitCommonAbilities_0x6012f68(param_1,0);
          Torappu_Battle_Unit_InitDynamicAbilities_0x6012f6a(param_1,0);
          Torappu_Battle_Unit__TouchBakeMuzzleData_0x6012fa1(param_1,0);
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*param_1);
          }
          uVar8 = (**(code **)(*param_1 + 0xa50))(param_1,*(undefined8 *)(*param_1 + 0xa58));
          puStack_30 = (undefined *)0x0;
          uStack_38 = uStack_38 & 0xffffffffffffff00;
          Torappu_Battle_Unit_SwitchMode_0x6012f64(param_1,uVar8,1);
          *(int *)(param_1 + 0x44) = (int)param_1[0x39];
          *(undefined4 *)((longlong)param_1 + 0x224) = *(undefined4 *)((longlong)param_1 + 0x1cc);
          *(int *)(param_1 + 0x45) = (int)param_1[0x3a];
          *(undefined4 *)((longlong)param_1 + 0x22c) = *(undefined4 *)((longlong)param_1 + 0x1d4);
          FUN_18515a130(&puStack_28,param_1,_DAT_18893b8a8);
          plVar9 = (longlong *)func_0x00018045cfe0(_DAT_188833298);
          if (plVar9 != (longlong *)0x0) {
            if (DAT_188c92c2c == '\0') {
              FUN_18048bf00(&DAT_188833298);
              DAT_188c92c2c = '\x01';
            }
            func_0x00018050cf60(plVar9,0);
            plVar9[3] = (longlong)puStack_28;
            plVar9[4] = lStack_20;
            func_0x00018048b9e0(plVar9 + 3,0);
            if (**(longlong **)(_DAT_188833298 + 0xb8) != 0) {
              XLua_DelegateBridge___Gen_Delegate_Imp10927_0x600350f
                        (**(longlong **)(_DAT_188833298 + 0xb8),plVar9,&puStack_28,0);
            }
            if (cRam0000000188c90932 == '\0') {
              puStack_30 = &UNK_1806fb4d5;
              FUN_18048bf00(&DAT_188841368,plVar9,0);
              cRam0000000188c90932 = '\x01';
            }
            if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
              puStack_30 = &UNK_1806fb4f4;
              func_0x00018048c140(_DAT_188841368);
            }
            lVar11 = lRam0000000188873c50;
            lVar7 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xb30);
            if (lVar7 != 0) {
              if (*(longlong *)(lVar7 + 0x18) == 0) {
                FUN_18048c0b0(lVar7,param_1,plVar9,0);
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
              uStack_38 = 0;
              puStack_30 = &stack0x00000008;
              puStack_28 = auStack_48;
              FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
              if (*(longlong *)(lVar7 + 0x18) != 0) {
                uVar8 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
                iVar4 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar7 + 0x38),
                                      *(undefined4 *)(lVar7 + 0x14),0);
                if (*(longlong *)(lVar7 + 0x18) != 0) {
                  lVar11 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
                  if (lVar11 == 0) {
                    FUN_18048c0b0();
                  }
                  else {
                    FUN_183cf8c20(lVar11,uVar8,param_1,0);
                    FUN_183cf8c20(lVar11,uVar8,plVar9,0);
                    iVar5 = FUN_183f22380(uVar8,2,0,iVar4,0);
                    if (iVar5 == 0) {
code_r0x0001832d231b:
                      FUN_183f22fd0(uVar8,iVar4 + -1,0);
                      return;
                    }
                    if (*(longlong *)(lVar7 + 0x18) != 0) {
                      FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar4 + -1,0);
                      goto code_r0x0001832d231b;
                    }
                  }
                  FUN_18048c0b0();
                }
                FUN_18048c0b0();
              }
              FUN_18048c0b0();
              FUN_180472d50();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            lVar7 = param_1[0x32];
            if (plVar9 == (longlong *)0x0) goto DAT_1806fb671;
            switch(*(undefined4 *)(*plVar9 + 0x11c)) {
            case 0x906:
              puStack_30 = &UNK_1806fb55b;
              uVar8 = FUN_180758010(plVar9,0);
              goto DAT_1806fb617;
            case 0x907:
              puStack_30 = &UNK_1806fb56a;
              uVar8 = FUN_180aaeab0(plVar9,0);
              goto DAT_1806fb617;
            case 0x908:
              puStack_30 = &UNK_1806fb579;
              uVar8 = FUN_180ac1370(plVar9,0);
              goto DAT_1806fb617;
            case 0x909:
              puStack_30 = &UNK_1806fb588;
              uVar8 = FUN_180f87e80(plVar9,0);
              goto DAT_1806fb617;
            case 0x90a:
              puStack_30 = &UNK_1806fb597;
              uVar8 = FUN_180f916a0(plVar9,0);
              goto DAT_1806fb617;
            case 0x90b:
              puStack_30 = &UNK_1806fb5a6;
              uVar8 = FUN_180f9b160(plVar9,0);
              goto DAT_1806fb617;
            }
            lVar1 = *plVar9;
            if (DAT_188ccc7f0 != '\0') {
              puStack_30 = &UNK_1806fb5c8;
              func_0x000180446d00();
            }
            uVar10 = 0;
            if (*(ushort *)(lVar1 + 0x12e) == 0) goto code_r0x0001806fb5f4;
            goto code_r0x0001806fb5e0;
          }
          break;
        }
        lVar7 = param_1[0x34];
        if (lVar7 == 0) break;
        if (*(uint *)(lVar7 + 0x18) <= uVar12) {
          FUN_18048c0a0();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        if (*(longlong *)(lVar11 + lVar7) == 0) break;
        Torappu_Battle_UnitMode_OnInit_0x601300a();
        lVar7 = param_1[0x34];
        uVar12 = uVar12 + 1;
        lVar11 = lVar11 + 8;
      } while (lVar7 != 0);
    }
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0(lVar7,param_1,(float)param_2,0);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar8 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar11 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar11 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar11,uVar8,param_1,0);
        FUN_183f22700(uVar8,(double)(float)param_2,0);
        iVar5 = FUN_183f22380(uVar8,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x000183650198:
          FUN_183f22fd0(uVar8,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar4 + -1,0);
          goto code_r0x000183650198;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
  while (uVar10 = uVar10 + 1, uVar10 < *(ushort *)(lVar1 + 0x12e)) {
code_r0x0001806fb5e0:
    if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar11) {
      puVar6 = (undefined8 *)
               (((longlong)
                 (*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) + 2) + 0x14)
                * 0x10 + lVar1);
      goto code_r0x0001806fb605;
    }
  }
code_r0x0001806fb5f4:
  puStack_30 = &UNK_1806fb605;
  puVar6 = (undefined8 *)FUN_180445cc0(plVar9,lVar11,2);
code_r0x0001806fb605:
  puStack_30 = &UNK_1806fb612;
  uVar8 = (*(code *)*puVar6)(plVar9,puVar6[1]);
DAT_1806fb617:
  if (lVar7 != 0) {
    if (cRam0000000188c90964 == '\0') {
      FUN_18048bf00(0x18889ead0,uVar8,plVar9,0);
      FUN_18048bf00(0x18889f3c0);
      FUN_18048bf00(0x18889f5f8);
      FUN_18048bf00(0x1888737d8);
      cRam0000000188c90964 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam00000001888737d8 + 0xb8) + 8);
    if (lVar11 == 0) {
      if (*(longlong *)(lVar7 + 0x10) != 0) {
        cVar3 = FUN_1858c8f90(*(longlong *)(lVar7 + 0x10),uVar8,&stack0xffffffffffffffe8,
                              uRam000000018889f3c0);
        if (cVar3 == '\0') {
          if (*(longlong *)(lVar7 + 0x10) != 0) {
            FUN_1858bcbe0(*(longlong *)(lVar7 + 0x10),uVar8,plVar9,uRam000000018889ead0);
            return;
          }
        }
        else if (*(longlong *)(lVar7 + 0x10) != 0) {
          FUN_1858ce5f0(*(longlong *)(lVar7 + 0x10),uVar8,plVar9,uRam000000018889f5f8);
          return;
        }
      }
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    puStack_28 = (undefined8 *)0x0;
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar11,lVar7,uVar8,plVar9);
    return;
  }
DAT_1806fb671:
  puStack_30 = &UNK_1806fb676;
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


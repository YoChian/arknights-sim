
/* WARNING: Removing unreachable block (ram,0x000180a7a681) */
/* WARNING: Removing unreachable block (ram,0x000180a7a698) */
/* WARNING: Removing unreachable block (ram,0x000180a7a69d) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BornState_OnExit_0x6012b65(longlong param_1,undefined4 param_2)

{
  longlong *plVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  longlong *plVar11;
  undefined8 uStack_70;
  undefined8 uStack_68;
  longlong lStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  longlong lStack_48;
  undefined8 uStack_30;
  
  if (DAT_188c92905 == '\0') {
    uStack_30 = 0x180a88644;
    FUN_18048bf00(&DAT_188884640);
    uStack_30 = 0x180a88650;
    FUN_18048bf00(&DAT_188933868);
    uStack_30 = 0x180a8865c;
    FUN_18048bf00(&DAT_188933aa8);
    uStack_30 = 0x180a88668;
    FUN_18048bf00(&DAT_188905bc8);
    uStack_30 = 0x180a88674;
    FUN_18048bf00(&DAT_188957260);
    uStack_30 = 0x180a88680;
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c92905 = '\x01';
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188884640 + 0xb8) + 8);
  if (lVar10 != 0) {
    uStack_30 = 0x180a8878c;
    XLua_DelegateBridge___Gen_Delegate_Imp55_0x6000a97(lVar10,param_1,param_2,0);
    return;
  }
  uStack_30 = 0x180a886b3;
  func_0x00018050cf60(param_1,param_2,_DAT_188957260);
  uStack_30 = 0x180a886c3;
  cVar4 = FUN_185159fc0(param_1 + 0x20,_DAT_188933aa8);
  if (cVar4 != '\0') {
    uStack_30 = 0x180a886d7;
    lVar10 = FUN_185159d80(param_1 + 0x20,_DAT_188933868);
    if (lVar10 == 0) goto LAB_180a88797;
    uStack_30 = 0x180a886ed;
    Torappu_Battle_Effects_Effect_FinishMe_0x60189a7(lVar10,0,0);
  }
  uStack_30 = 0x180a886f9;
  lVar10 = FUN_185339460(_DAT_188905bc8);
  if (lVar10 != 0) {
    uStack_30 = 0x180a8870c;
    cVar4 = Torappu_Config_DynamicConfig_get_enableDelayUpdateTileForEnemy_0x600a8e4(lVar10,0);
    if (cVar4 == '\0') {
      return;
    }
    uStack_30 = 0x180a8871f;
    plVar11 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
    if (plVar11 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        uStack_30 = 0x180a88738;
        func_0x000180446d00(*plVar11);
      }
      uStack_30 = 0x180a8874f;
      cVar4 = (**(code **)(*plVar11 + 0x3c0))(plVar11,*(undefined8 *)(*plVar11 + 0x3c8));
      if (cVar4 == '\0') {
        return;
      }
      uStack_30 = 0x180a88762;
      plVar11 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
      if (plVar11 != (longlong *)0x0) {
        if (cRam0000000188c928bd == '\0') {
          FUN_18048bf00(&DAT_18881b6b0,1,0);
          FUN_18048bf00(&DAT_1888c9870);
          FUN_18048bf00(&DAT_1888c9ab0);
          FUN_18048bf00(0x1888c9cf0);
          FUN_18048bf00(0x1888f4de0);
          FUN_18048bf00(0x1888f5260);
          FUN_18048bf00(&DAT_1888f5920);
          FUN_18048bf00(0x1888f6d60);
          FUN_18048bf00(0x1888f6fa0);
          FUN_18048bf00(&DAT_188932ce8);
          FUN_18048bf00(&DAT_1888e0148);
          cRam0000000188c928bd = '\x01';
        }
        if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
          func_0x00018048c140(_DAT_18881b6b0);
        }
        lVar10 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x728);
        if (lVar10 != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp26_0x6000a7a(lVar10,plVar11,1,0);
          return;
        }
        lVar10 = FUN_185337c50(_DAT_1888e0148);
        uVar8 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(plVar11,0);
        if (lVar10 != 0) {
          lVar9 = FUN_18087dbc0(lVar10,uVar8,0);
          lVar10 = plVar11[0x6b];
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar4 = FUN_186b63a70(lVar10,0,0);
          if (cVar4 != '\0') {
            if (plVar11[0x6b] == 0) goto code_r0x000180a7ab77;
            Torappu_Battle_Tile_RemoveEnemy_0x6011449(plVar11[0x6b],plVar11,0);
          }
          lVar10 = plVar11[0x6b];
          plVar11[0x6b] = lVar9;
          func_0x00018048b9e0(plVar11 + 0x6b,lVar9);
          lVar9 = plVar11[0x6b];
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar4 = FUN_186b63a70(lVar9,0,0);
          if (cVar4 != '\0') {
            if (plVar11[0x6b] == 0) goto code_r0x000180a7ab77;
            FUN_1808bc0b0(plVar11[0x6b],plVar11,0);
            lVar9 = plVar11[0x6b];
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar4 = FUN_186b63a70(lVar9,0,0);
            if (cVar4 != '\0') {
              iVar5 = FUN_180706fc0(plVar11,0);
              if (plVar11[0x6b] == 0) goto code_r0x000180a7ab77;
              uVar6 = FUN_1808c64e0(plVar11[0x6b],0);
              FUN_180709940(plVar11,uVar6,0);
              iVar7 = FUN_180706fc0(plVar11,0);
              if (iVar5 != iVar7) {
                Torappu_Battle_Entity_EmitEvent_0x601049c(plVar11,0x1f,0);
              }
              lVar9 = plVar11[0x6b];
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(*plVar11);
              }
              (**(code **)(*plVar11 + 0x1040))
                        (plVar11,lVar9,lVar10,*(undefined8 *)(*plVar11 + 0x1048));
              lVar10 = plVar11[0x6b];
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar4 = FUN_186b63a70(lVar10,0,0);
              if (cVar4 != '\0') {
                if (plVar11[0x6b] == 0) goto code_r0x000180a7ab77;
                uVar6 = FUN_1808c4c70(plVar11[0x6b],0);
                if (cRam0000000188c92865 == '\0') {
                  FUN_18048bf00(&DAT_18881b6b0);
                  cRam0000000188c92865 = '\x01';
                }
                if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
                  func_0x00018048c140(_DAT_18881b6b0);
                }
                lVar10 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x468);
                if (lVar10 == 0) {
                  *(undefined4 *)((longlong)plVar11 + 0x574) = uVar6;
                }
                else {
                  XLua_DelegateBridge___Gen_Delegate_Imp81_0x6000ab1(lVar10,plVar11,uVar6,0);
                }
              }
            }
          }
          lVar10 = plVar11[0x5a];
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar4 = FUN_186b63a70(lVar10,0,0);
          if (cVar4 == '\0') {
            return;
          }
          if (plVar11[0x9e] != 0) {
            FUN_184aef040(&uStack_70,plVar11[0x9e],_DAT_1888f5920);
            uStack_58 = (undefined4)uStack_70;
            uStack_54 = uStack_70._4_4_;
            uStack_50 = (undefined4)uStack_68;
            uStack_4c = uStack_68._4_4_;
            lStack_48 = lStack_60;
            iVar5 = 0;
            uStack_70 = 0;
            uStack_68 = &uStack_58;
            while (cVar4 = FUN_185a610f0(&uStack_58,_DAT_1888c9ab0), lVar10 = lStack_48,
                  cVar4 != '\0') {
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar4 = FUN_186b63a70(lVar10,0,0);
              if (cVar4 != '\0') {
                if (lVar10 == 0) {
                  FUN_18048c0b0();
                  FUN_180472d50();
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                Torappu_Battle_Tile_RemoveEnemy_0x6011449(lVar10,plVar11);
              }
            }
            func_0x00018050cf60(&uStack_58,_DAT_1888c9870);
            lVar10 = plVar11[0x9e];
            if (lVar10 != 0) {
              *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
              iVar7 = *(int *)(lVar10 + 0x18);
              *(undefined4 *)(lVar10 + 0x18) = 0;
              if (0 < iVar7) {
                System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar10 + 0x10),0,iVar7,0);
              }
              plVar1 = (longlong *)plVar11[0x5a];
              if (DAT_188c8f5b5 == '\0') {
                FUN_18048bf00(&DAT_188828bc0);
                DAT_188c8f5b5 = '\x01';
              }
              uVar8 = **(undefined8 **)(_DAT_188828bc0 + 0xb8);
              if (plVar1 != (longlong *)0x0) {
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*plVar1);
                }
                lVar10 = (**(code **)(*plVar1 + 0x200))
                                   (plVar1,uVar8,0,*(undefined8 *)(*plVar1 + 0x208));
                if (lVar10 == 0) {
                  return;
                }
                do {
                  if (*(int *)(lVar10 + 0x18) <= iVar5) {
                    return;
                  }
                  lVar9 = FUN_184afcf00(lVar10,iVar5,uRam00000001888f6fa0);
                  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                    func_0x00018048c140();
                  }
                  cVar4 = FUN_186b63a70(lVar9,0,0);
                  if (cVar4 != '\0') {
                    lVar2 = plVar11[0x6b];
                    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                      func_0x00018048c140();
                    }
                    cVar4 = FUN_186b63a70(lVar9,lVar2,0);
                    if (cVar4 != '\0') {
                      if (lVar9 == 0) break;
                      FUN_1808bc0b0(lVar9,plVar11,0);
                      if (plVar11[0x9e] == 0) break;
                      FUN_1805072d0(plVar11[0x9e],lVar9,uRam00000001888f4de0);
                    }
                  }
                  iVar5 = iVar5 + 1;
                } while( true );
              }
            }
          }
        }
code_r0x000180a7ab77:
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
  }
LAB_180a88797:
  uStack_30 = 0x180a8879c;
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


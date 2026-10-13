
/* WARNING: Removing unreachable block (ram,0x000180a7a681) */
/* WARNING: Removing unreachable block (ram,0x000180a7a698) */
/* WARNING: Removing unreachable block (ram,0x000180a7a69d) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_Born_0x6012a84(longlong *param_1)

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
  undefined8 uStackX_20;
  undefined8 uStack_70;
  undefined8 uStack_68;
  longlong lStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  longlong lStack_48;
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c9286c == '\0') {
    uStack_30 = 0x180a6b2ae;
    FUN_18048bf00(&DAT_18881b6b0);
    uStack_30 = 0x180a6b2ba;
    FUN_18048bf00(&DAT_1888c4f88);
    uStack_30 = 0x180a6b2c6;
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c9286c = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    uStack_30 = 0x180a6b2e5;
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x4a0);
  if (lVar9 == 0) {
    uStack_30 = 0x180a6b312;
    uVar8 = Torappu_Battle_Entity_get_originTile_0x601034d(param_1,0);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      uStack_30 = 0x180a6b32a;
      func_0x00018048c140();
    }
    uStack_30 = 0x180a6b337;
    cVar4 = FUN_186b63a70(uVar8,0,0);
    if (cVar4 != '\0') {
      uStack_30 = 0x180a6b349;
      lVar9 = Torappu_Battle_Entity_get_originTile_0x601034d(param_1,0);
      if (lVar9 == 0) {
LAB_180a6b3f0:
        uStack_30 = 0x180a6b3f5;
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      uStack_30 = 0x180a6b35c;
      uVar8 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(lVar9,0);
      if (*(int *)(_DAT_1888c4f88 + 0xe0) == 0) {
        uStack_30 = 0x180a6b377;
        func_0x00018048c140(_DAT_1888c4f88);
      }
      uStack_30 = 0x180a6b394;
      cVar4 = Torappu_GridPosition_op_Inequality_0x6006d95
                        (uVar8,*(undefined8 *)(*(longlong *)(_DAT_1888c4f88 + 0xb8) + 0x60),0);
      if (cVar4 != '\0') {
        uStack_30 = 0x180a6b3a2;
        lVar9 = Torappu_Battle_Entity_get_originTile_0x601034d(param_1,0);
        if (lVar9 == 0) goto LAB_180a6b3f0;
        uStack_30 = 0x180a6b3b1;
        cVar4 = Torappu_Battle_Tile_get_isHidden_0x6011411(lVar9,0);
        if (cVar4 != '\0') {
          if (cRam0000000188c928bd == '\0') {
            FUN_18048bf00(&DAT_18881b6b0,1,0);
            FUN_18048bf00(0x1888c9870);
            FUN_18048bf00(0x1888c9ab0);
            FUN_18048bf00(0x1888c9cf0);
            FUN_18048bf00(0x1888f4de0);
            FUN_18048bf00(0x1888f5260);
            FUN_18048bf00(0x1888f5920);
            FUN_18048bf00(0x1888f6d60);
            FUN_18048bf00(0x1888f6fa0);
            FUN_18048bf00(&DAT_188932ce8);
            FUN_18048bf00(&DAT_1888e0148);
            cRam0000000188c928bd = '\x01';
          }
          if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
            func_0x00018048c140(_DAT_18881b6b0);
          }
          lVar9 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x728);
          if (lVar9 != 0) {
            XLua_DelegateBridge___Gen_Delegate_Imp26_0x6000a7a(lVar9,param_1,1,0);
            return;
          }
          lVar9 = FUN_185337c50(_DAT_1888e0148);
          uVar8 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(param_1,0);
          if (lVar9 != 0) {
            lVar10 = Torappu_Battle_Map_GetTile_0x60111be(lVar9,uVar8,0);
            lVar9 = param_1[0x6b];
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar4 = FUN_186b63a70(lVar9,0,0);
            if (cVar4 != '\0') {
              if (param_1[0x6b] == 0) goto code_r0x000180a7ab77;
              FUN_1808c2390(param_1[0x6b],param_1,0);
            }
            lVar9 = param_1[0x6b];
            param_1[0x6b] = lVar10;
            func_0x00018048b9e0(param_1 + 0x6b,lVar10);
            lVar10 = param_1[0x6b];
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar4 = FUN_186b63a70(lVar10,0,0);
            if (cVar4 != '\0') {
              if (param_1[0x6b] == 0) goto code_r0x000180a7ab77;
              FUN_1808bc0b0(param_1[0x6b],param_1,0);
              lVar10 = param_1[0x6b];
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar4 = FUN_186b63a70(lVar10,0,0);
              if (cVar4 != '\0') {
                iVar5 = Torappu_Battle_Entity_get_mapLayer_0x6010365(param_1,0);
                if (param_1[0x6b] == 0) goto code_r0x000180a7ab77;
                uVar6 = FUN_1808c64e0(param_1[0x6b],0);
                FUN_180709940(param_1,uVar6,0);
                iVar7 = Torappu_Battle_Entity_get_mapLayer_0x6010365(param_1,0);
                if (iVar5 != iVar7) {
                  FUN_1806f2700(param_1,0x1f,0);
                }
                lVar10 = param_1[0x6b];
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*param_1);
                }
                (**(code **)(*param_1 + 0x1040))
                          (param_1,lVar10,lVar9,*(undefined8 *)(*param_1 + 0x1048));
                lVar9 = param_1[0x6b];
                if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                cVar4 = FUN_186b63a70(lVar9,0,0);
                if (cVar4 != '\0') {
                  if (param_1[0x6b] == 0) goto code_r0x000180a7ab77;
                  uVar6 = FUN_1808c4c70(param_1[0x6b],0);
                  if (cRam0000000188c92865 == '\0') {
                    FUN_18048bf00(&DAT_18881b6b0);
                    cRam0000000188c92865 = '\x01';
                  }
                  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
                    func_0x00018048c140(_DAT_18881b6b0);
                  }
                  lVar9 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x468);
                  if (lVar9 == 0) {
                    *(undefined4 *)((longlong)param_1 + 0x574) = uVar6;
                  }
                  else {
                    FUN_1836500a0(lVar9,param_1,uVar6,0);
                  }
                }
              }
            }
            lVar9 = param_1[0x5a];
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar4 = FUN_186b63a70(lVar9,0,0);
            if (cVar4 == '\0') {
              return;
            }
            if (param_1[0x9e] != 0) {
              FUN_184aef040(&uStack_70,param_1[0x9e],uRam00000001888f5920);
              uStack_58 = (undefined4)uStack_70;
              uStack_54 = uStack_70._4_4_;
              uStack_50 = (undefined4)uStack_68;
              uStack_4c = uStack_68._4_4_;
              lStack_48 = lStack_60;
              iVar5 = 0;
              uStack_70 = (undefined *)0x0;
              uStack_68 = &uStack_58;
              while (cVar4 = FUN_185a610f0(&uStack_58,uRam00000001888c9ab0), lVar9 = lStack_48,
                    cVar4 != '\0') {
                if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                cVar4 = FUN_186b63a70(lVar9,0,0);
                if (cVar4 != '\0') {
                  if (lVar9 == 0) {
                    FUN_18048c0b0();
                    FUN_180472d50();
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  FUN_1808c2390(lVar9,param_1);
                }
              }
              func_0x00018050cf60(&uStack_58,uRam00000001888c9870);
              lVar9 = param_1[0x9e];
              if (lVar9 != 0) {
                *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
                iVar7 = *(int *)(lVar9 + 0x18);
                *(undefined4 *)(lVar9 + 0x18) = 0;
                if (0 < iVar7) {
                  System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar9 + 0x10),0,iVar7,0);
                }
                plVar1 = (longlong *)param_1[0x5a];
                if (cRam0000000188c8f5b5 == '\0') {
                  FUN_18048bf00(0x188828bc0);
                  cRam0000000188c8f5b5 = '\x01';
                }
                uVar8 = **(undefined8 **)(lRam0000000188828bc0 + 0xb8);
                if (plVar1 != (longlong *)0x0) {
                  if (DAT_188ccc7f0 != '\0') {
                    func_0x000180446d00(*plVar1);
                  }
                  lVar9 = (**(code **)(*plVar1 + 0x200))
                                    (plVar1,uVar8,0,*(undefined8 *)(*plVar1 + 0x208));
                  if (lVar9 == 0) {
                    return;
                  }
                  do {
                    if (*(int *)(lVar9 + 0x18) <= iVar5) {
                      return;
                    }
                    lVar10 = FUN_184afcf00(lVar9,iVar5,uRam00000001888f6fa0);
                    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                      func_0x00018048c140();
                    }
                    cVar4 = FUN_186b63a70(lVar10,0,0);
                    if (cVar4 != '\0') {
                      lVar2 = param_1[0x6b];
                      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                        func_0x00018048c140();
                      }
                      cVar4 = FUN_186b63a70(lVar10,lVar2,0);
                      if (cVar4 != '\0') {
                        if (lVar10 == 0) break;
                        FUN_1808bc0b0(lVar10,param_1,0);
                        if (param_1[0x9e] == 0) break;
                        FUN_1805072d0(param_1[0x9e],lVar10,uRam00000001888f4de0);
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
    if (DAT_188ccc7f0 != '\0') {
      uStack_30 = 0x18066253a;
      func_0x000180446d00(*param_1,0);
    }
    uStack_30 = 0x180662550;
    (**(code **)(*param_1 + 0x340))(param_1,*(undefined8 *)(*param_1 + 0x348));
    *(undefined1 *)((longlong)param_1 + 0x25) = 1;
    return;
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    uStack_70 = &UNK_18331015e;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStackX_20;
  uStack_70 = &UNK_183310067;
  FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar8 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    uStack_70 = &UNK_18331008a;
    iVar5 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar10 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar10 == 0) {
        uStack_70 = &UNK_183310142;
        FUN_18048c0b0();
      }
      else {
        uStack_70 = &UNK_1833100b4;
        FUN_183cf8c20(lVar10,uVar8,param_1,0);
        lStack_48 = 0;
        uStack_70 = &UNK_1833100d0;
        iVar7 = FUN_183f22380(uVar8,1,0,iVar5);
        if (iVar7 == 0) {
code_r0x0001833100e8:
          uStack_70 = &UNK_1833100f6;
          FUN_183f22fd0(uVar8,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          uStack_70 = &UNK_1833100e8;
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      uStack_70 = &UNK_183310148;
      FUN_18048c0b0();
    }
    uStack_70 = &UNK_18331014d;
    FUN_18048c0b0();
  }
  uStack_70 = &UNK_183310152;
  FUN_18048c0b0();
  uStack_70 = &UNK_183310158;
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


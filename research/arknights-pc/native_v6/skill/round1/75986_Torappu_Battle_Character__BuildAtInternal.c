
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character__BuildAtInternal_0x60128d3(longlong param_1,longlong *param_2)

{
  int *piVar1;
  undefined1 auVar2 [16];
  undefined4 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  code *pcVar6;
  char cVar7;
  undefined4 uVar8;
  int iVar9;
  undefined8 uVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  undefined4 uVar13;
  undefined4 auStackX_20 [2];
  longlong alStack_f8 [2];
  longlong lStack_e8;
  longlong lStack_e0;
  longlong lStack_d8;
  longlong lStack_d0;
  longlong lStack_c8;
  longlong lStack_c0;
  undefined1 auStack_b8 [16];
  longlong lStack_a8;
  longlong lStack_a0;
  undefined8 uStack_98;
  longlong *plStack_90;
  undefined4 *puStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  
  if (DAT_188c9260c == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_1888e9420);
    FUN_18048bf00(&DAT_1888e9660);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188937ba8);
    DAT_188c9260c = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x550);
  if (lVar4 != 0) {
    lStack_e8 = *param_2;
    lStack_e0 = param_2[1];
    lStack_d8 = param_2[2];
    lStack_d0 = param_2[3];
    lStack_c8 = param_2[4];
    lStack_c0 = param_2[5];
    auStack_b8 = *(undefined1 (*) [16])(param_2 + 6);
    lStack_a8 = param_2[8];
    lStack_a0 = param_2[9];
    XLua_DelegateBridge___Gen_Delegate_Imp3679_0x60018bf(lVar4,param_1,&lStack_e8,0);
    return;
  }
  auVar2 = *(undefined1 (*) [16])(param_2 + 6);
  lStack_a8 = param_2[8];
  lStack_a0 = param_2[9];
  alStack_f8[0] = *param_2;
  uVar5 = param_2[2];
  auStack_b8 = auVar2;
  if (alStack_f8[0] != 0) {
    Torappu_Battle_Character_set_cardUid_0x6012836(param_1,*(undefined4 *)(alStack_f8[0] + 0x6c),0);
    lStack_a8 = param_2[8];
    lStack_a0 = param_2[9];
    *(longlong *)(param_1 + 0x3a8) = param_2[1];
    auStack_b8 = auVar2;
    func_0x00018048b9e0(param_1 + 0x3a8);
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar10 = Torappu_Battle_BattleController_get_fixedPlayTime_0x600fbd5(0);
    *(undefined8 *)(param_1 + 0x390) = uVar10;
    uVar10 = *(undefined8 *)(param_1 + 0x3a8);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar7 = FUN_186b63a70(uVar10,0,0);
    if (cVar7 != '\0') {
      if (*(longlong *)(param_1 + 0x3a8) == 0) goto LAB_180a3559a;
      uVar8 = Torappu_Battle_Tile_get_mapLayer_0x601140b(*(longlong *)(param_1 + 0x3a8),0);
      Torappu_Battle_Entity_set_mapLayer_0x6010366(param_1,uVar8,0);
    }
    lStack_a8 = param_2[8];
    lStack_a0 = param_2[9];
    *(longlong *)(param_1 + 0x450) = param_2[5];
    auStack_b8 = auVar2;
    func_0x00018048b9e0(param_1 + 0x450);
    lStack_a8 = param_2[8];
    lStack_a0 = param_2[9];
    *(longlong *)(param_1 + 0x448) = param_2[4];
    auStack_b8 = auVar2;
    func_0x00018048b9e0(param_1 + 0x448);
    lStack_a8 = param_2[8];
    lStack_a0 = param_2[9];
    *(char *)(param_1 + 0x372) = auVar2[4];
    auStack_b8._8_8_ = auVar2._8_8_;
    *(undefined8 *)(param_1 + 0x4c0) = auStack_b8._8_8_;
    *(longlong *)(param_1 + 0x4c8) = lStack_a8;
    *(int *)(param_1 + 0x4d0) = (int)param_2[9];
    *(undefined4 *)(param_1 + 0x4e0) = *(undefined4 *)(param_1 + 0x338);
    *(undefined1 *)(param_1 + 0x4e4) = 0;
    *(int *)(param_1 + 0x4ec) = (int)(uVar5 >> 0x20);
    *(undefined4 *)(param_1 + 0x4e8) = *(undefined4 *)((longlong)param_2 + 0x4c);
    auStack_b8 = auVar2;
    if (*(longlong *)(param_1 + 0x4f8) != 0) {
      FUN_185a43000(*(longlong *)(param_1 + 0x4f8),_DAT_1888e9420);
      if (*(longlong *)(param_1 + 0x4f8) != 0) {
        FUN_185a43140(*(longlong *)(param_1 + 0x4f8),1,*(undefined1 *)(param_1 + 0x36c),
                      _DAT_1888e9660);
        if (*(longlong *)(param_1 + 0x500) != 0) {
          Torappu_EnableStateWithKey_Reset_0x6000611(*(longlong *)(param_1 + 0x500),0);
          uVar8 = 0;
          Torappu_Battle_Character__AssignData_0x6012917
                    (param_1,alStack_f8[0],(int)param_2[3],auVar2._0_4_,0);
          Torappu_Battle_Entity_set_direction_0x6010359(param_1,(int)param_2[2],0);
          if ((alStack_f8[0] != 0) && (lVar4 = *(longlong *)(alStack_f8[0] + 0x38), lVar4 != 0)) {
            uVar10 = *(undefined8 *)(lVar4 + 100);
            uVar12 = *(undefined8 *)(lVar4 + 0x6c);
            uVar3 = *(undefined4 *)(lVar4 + 0x74);
            if (*(int *)(_DAT_188937ba8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            uStack_78 = uVar10;
            uStack_70 = uVar12;
            uStack_68 = uVar3;
            auStackX_20[0] =
                 CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3(&uStack_78,0);
            uStack_98 = 0;
            plStack_90 = alStack_f8;
            puStack_88 = auStackX_20;
            if (alStack_f8[0] != 0) {
              lVar4 = *(longlong *)(alStack_f8[0] + 0x38);
              if (*(int *)(_DAT_188937ba8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              puVar11 = (undefined8 *)
                        CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea2
                                  (&uStack_78,uVar5 >> 0x20,0);
              uVar10 = puVar11[1];
              uVar3 = *(undefined4 *)(puVar11 + 2);
              if (lVar4 != 0) {
                *(undefined8 *)(lVar4 + 100) = *puVar11;
                *(undefined8 *)(lVar4 + 0x6c) = uVar10;
                *(undefined4 *)(lVar4 + 0x74) = uVar3;
                if (alStack_f8[0] != 0) {
                  uVar10 = *(undefined8 *)(alStack_f8[0] + 0x38);
                  lVar4 = param_2[3];
                  uVar3 = *(undefined4 *)(param_1 + 0x2c8);
                  if (param_2[1] != 0) {
                    uVar12 = Torappu_Battle_VisualObject_get_mapPosition_0x601302b(param_2[1],0);
                    if (param_2[1] != 0) {
                      uVar13 = Torappu_Battle_Tile_get_locateHeight_0x60113f6(param_2[1],0);
                      if (alStack_f8[0] != 0) {
                        if (*(longlong *)(alStack_f8[0] + 0x108) != 0) {
                          Torappu_Battle_Entity_Init_0x6010441
                                    (param_1,uVar10,(int)lVar4,auVar2._0_4_,CONCAT44(uVar8,uVar3),
                                     uVar12,uVar13,
                                     *(undefined8 *)(*(longlong *)(alStack_f8[0] + 0x108) + 0x48),0)
                          ;
                          FUN_180a23fe0(&plStack_90);
                          if ((alStack_f8[0] != 0) && (*(longlong *)(alStack_f8[0] + 0x158) != 0)) {
                            piVar1 = (int *)(*(longlong *)(alStack_f8[0] + 0x158) + 0x20);
                            *piVar1 = *piVar1 + 1;
                            if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                              func_0x00018048c140();
                            }
                            iVar9 = Torappu_Battle_BattleController_get_fixedFrameCnt_0x600fbd4(0);
                            if (iVar9 != 0) {
                              if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                                func_0x00018048c140(_DAT_188927d60);
                              }
                              *(int *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0x50) =
                                   *(int *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0x50) + 1;
                            }
                            Torappu_Battle_Character_UpdateHatred_0x6012914(param_1,0);
                            Torappu_Battle_Entity_SetBodyDirection_0x60103eb
                                      (param_1,(int)param_2[2],1,0);
                            Torappu_Battle_Character__InitAllModeDirection_0x60128d4(param_1,0);
                            return;
                          }
                          goto LAB_180a3559a;
                        }
                        FUN_18048c0b0();
                      }
                      FUN_18048c0b0();
                    }
                    FUN_18048c0b0();
                  }
                  FUN_18048c0b0();
                }
                FUN_18048c0b0();
              }
              FUN_18048c0b0();
            }
            FUN_18048c0b0();
            FUN_180472d50();
            pcVar6 = (code *)swi(3);
            (*pcVar6)();
            return;
          }
        }
      }
    }
  }
LAB_180a3559a:
  FUN_18048c0b0();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}


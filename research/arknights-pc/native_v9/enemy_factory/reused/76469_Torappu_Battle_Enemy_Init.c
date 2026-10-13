
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_Init_0x6012ab6
               (longlong *param_1,longlong param_2,undefined8 param_3,undefined4 *param_4,
               longlong param_5)

{
  undefined1 uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  undefined8 in_stack_ffffffffffffff38;
  ulonglong uVar13;
  undefined8 in_stack_ffffffffffffff48;
  undefined4 uVar15;
  ulonglong uVar14;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  
  uVar7 = (undefined4)((ulonglong)in_stack_ffffffffffffff38 >> 0x20);
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffff48 >> 0x20);
  if (DAT_188c9289e == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18896d0f8);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_188905bc8);
    DAT_188c9289e = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x630);
  if (lVar8 != 0) {
    uStack_88 = *param_4;
    uStack_84 = param_4[1];
    uStack_80 = param_4[2];
    uStack_7c = param_4[3];
    uStack_78 = *(undefined8 *)(param_4 + 4);
    XLua_DelegateBridge___Gen_Delegate_Imp3717_0x60018e5
              (lVar8,param_1,param_2,param_3,&uStack_88,param_5,0);
    return;
  }
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar8 = Torappu_Battle_BattleController_get_fixedPlayTime_0x600fbd5(0);
  param_1[0x96] = lVar8;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  uVar5 = (**(code **)(*param_1 + 0xf10))(param_1,*(undefined8 *)(*param_1 + 0xf18));
  uVar5 = func_0x000186727980(uVar5,0);
  func_0x000180662a30(param_1,uVar5,0,0);
  Torappu_Battle_Enemy__AssignData_0x6012aea(param_1,param_2,param_3,0);
  if (param_5 != 0) {
    uVar9 = Torappu_Battle_Route_GetSpawnOffset_0x60112e1(param_5,0);
    if (*(longlong *)(param_5 + 0x18) != 0) {
      param_1[0x98] = *(longlong *)(*(longlong *)(param_5 + 0x18) + 0x14);
      if ((*(longlong *)(param_5 + 0x18) != 0) &&
         (param_1[0x97] = *(longlong *)(*(longlong *)(param_5 + 0x18) + 0x1c), param_2 != 0)) {
        uVar12 = *(undefined8 *)(param_2 + 0x28);
        uVar6 = Torappu_Battle_Route_get_motionMode_0x60112d2(param_5,0);
        uVar10 = Torappu_Battle_Route_GetSpawnPosition_0x60112e0(param_5,0);
        fStack_98 = (float)uVar9;
        fStack_94 = (float)(uVar9 >> 0x20);
        fStack_90 = (float)uVar10;
        fStack_8c = (float)((ulonglong)uVar10 >> 0x20);
        lVar8 = param_1[0x60];
        if (DAT_188c928e6 == '\0') {
          FUN_18048bf00(&DAT_18881b6b0);
          FUN_18048bf00(&DAT_18881f8b8);
          DAT_188c928e6 = '\x01';
        }
        if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
          func_0x00018048c140(_DAT_18881b6b0);
        }
        lVar2 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x870);
        if (lVar2 == 0) {
          if (*(longlong *)(param_2 + 0x78) == 0) {
            if (*(int *)(_DAT_18881f8b8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            uVar11 = Torappu_SpData_GetDefault_0x6008051(0);
          }
          else {
            uVar10 = *(undefined8 *)(param_2 + 0x78);
            if (*(int *)(_DAT_18881f8b8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            uVar11 = Torappu_SpData_CreateFrom_0x6008056(uVar10,0,0);
          }
        }
        else {
          uVar11 = XLua_DelegateBridge___Gen_Delegate_Imp958_0x6000e1e(lVar2,param_1,param_2,0);
        }
        uVar14 = CONCAT44(uVar15,(int)lVar8);
        uVar13 = CONCAT44(fStack_94 + fStack_8c,fStack_98 + fStack_90);
        Torappu_Battle_Entity_Init_0x6010441
                  (param_1,uVar12,uVar5,0,CONCAT44(uVar7,uVar6),uVar13,uVar14,uVar11,0);
        uVar1 = *(undefined1 *)((longlong)param_1 + 0x33d);
        lVar8 = func_0x00018045cfe0(_DAT_18896d0f8);
        if (lVar8 != 0) {
          uStack_88 = *param_4;
          uStack_84 = param_4[1];
          uStack_80 = param_4[2];
          uStack_7c = param_4[3];
          uStack_78 = *(undefined8 *)(param_4 + 4);
          Torappu_Battle_DirectionCursor__ctor_0x601127f
                    (lVar8,param_5,&uStack_88,uVar9 ^ 0x8000000080000000,param_1,
                     uVar13 & 0xffffffffffffff00,uVar14 & 0xffffffffffffff00,
                     uVar11 & 0xffffffffffffff00,uVar1,0);
          param_1[0x6d] = lVar8;
          func_0x00018048b9e0(param_1 + 0x6d,lVar8);
          param_1[0x71] = 0;
          func_0x00018048b9e0(param_1 + 0x71,0);
          lVar8 = FUN_185339460(_DAT_188905bc8);
          if (lVar8 != 0) {
            cVar4 = Torappu_Config_DynamicConfig_get_enableDelayUpdateTileForEnemy_0x600a8e4
                              (lVar8,0);
            if (cVar4 == '\0') {
              Torappu_Battle_Enemy__UpdateCurrentTile_0x6012ad5(param_1,0,0);
            }
            else {
              if (DAT_188c928b9 == '\0') {
                FUN_18048bf00(&DAT_18881b6b0);
                FUN_18048bf00(&DAT_188932ce8);
                FUN_18048bf00(&DAT_1888e0148);
                DAT_188c928b9 = '\x01';
              }
              if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
                func_0x00018048c140(_DAT_18881b6b0);
              }
              lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x708);
              if (lVar8 == 0) {
                lVar8 = FUN_185337c50(_DAT_1888e0148);
                uVar12 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(param_1,0);
                if (lVar8 == 0) goto LAB_180a6e9a7;
                Torappu_Battle_Map_TryGetTile_0x60111b8(lVar8,uVar12,param_1 + 0x6b,0);
                lVar8 = param_1[0x6b];
                if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                cVar4 = FUN_186b63a70(lVar8,0,0);
                if (cVar4 != '\0') {
                  if (param_1[0x6b] == 0) goto LAB_180a6e9a7;
                  uVar7 = Torappu_Battle_Tile_get_mapLayer_0x601140b(param_1[0x6b],0);
                  Torappu_Battle_Entity_set_mapLayer_0x6010366(param_1,uVar7,0);
                }
              }
              else {
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar8,param_1,0);
              }
            }
            return;
          }
        }
      }
    }
  }
LAB_180a6e9a7:
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


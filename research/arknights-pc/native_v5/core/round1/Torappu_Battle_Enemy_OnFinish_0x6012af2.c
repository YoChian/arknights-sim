
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_OnFinish_0x6012af2(longlong param_1,int param_2)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined4 *puVar7;
  longlong lVar8;
  int iVar9;
  longlong lStackX_20;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  longlong lStack_b0;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 *puStack_78;
  longlong lStack_70;
  undefined1 auStack_58 [48];
  
  if (DAT_188c928da == '\0') {
    FUN_18048bf00(&DAT_1888cb510);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_1888c9870);
    FUN_18048bf00(&DAT_1888c9ab0);
    FUN_18048bf00(0x1888c9cf0);
    FUN_18048bf00(0x1888f5260);
    FUN_18048bf00(&DAT_1888f5920);
    FUN_18048bf00(&DAT_188935b98);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888a36e8);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c928da = '\x01';
  }
  lStackX_20 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  puStack_78 = (undefined8 *)0x0;
  lStack_70 = 0;
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x810);
  if (lVar6 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp3026_0x6001632(lVar6,param_1,param_2,0);
    return;
  }
  Torappu_Battle_Unit_OnFinish_0x6012f7a(param_1,param_2,0);
  puVar4 = (undefined8 *)
           Torappu_Battle_LevelScript_EventParams_Allocate_0x601476e(&uStack_c0,&lStackX_20,0);
  lVar6 = lStackX_20;
  uStack_90 = *puVar4;
  uStack_88 = puVar4[1];
  uStack_c0 = 0;
  puStack_b8 = &uStack_90;
  uVar5 = Torappu_Battle_Entity_get_id_0x6010328(param_1,0);
  if (lVar6 != 0) {
    Torappu_Battle_LevelScript_EventParams_SetSender_0x6014770(lVar6,uVar5,0);
    lVar6 = lStackX_20;
    uVar5 = Torappu_Battle_Entity_get_id_0x6010328(param_1,0);
    if (lVar6 != 0) {
      Torappu_Battle_LevelScript_EventParams_SetReceiver_0x6014771(lVar6,uVar5,0);
      lVar6 = FUN_185337c50(_DAT_1888d3908);
      if (lVar6 != 0) {
        lVar6 = Torappu_Battle_BattleController_get_levelScriptEventManager_0x600fc11(lVar6,0);
        if (lVar6 != 0) {
          Torappu_Battle_LevelScript_LevelScriptEventManager_RaiseLevelEvent_0x60147ea
                    (lVar6,3,lStackX_20,0);
          FUN_18531eef0(&uStack_90,_DAT_1888a36e8);
          lVar6 = 0;
          uVar5 = *(undefined8 *)(param_1 + 0x358);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar2 = FUN_186b63a70(uVar5,0,0);
          if (cVar2 != '\0') {
            lVar6 = *(longlong *)(param_1 + 0x358);
            if (lVar6 == 0) goto LAB_180a70e7a;
            Torappu_Battle_Tile_RemoveEnemy_0x6011449(lVar6,param_1,0);
          }
          uVar5 = *(undefined8 *)(param_1 + 0x2d0);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar2 = FUN_186b63a70(uVar5,0,0);
          if (cVar2 != '\0') {
            if (*(longlong *)(param_1 + 0x4f0) == 0) goto LAB_180a70e7a;
            FUN_184aef040(&uStack_c0,*(longlong *)(param_1 + 0x4f0),_DAT_1888f5920);
            uStack_80 = uStack_c0;
            puStack_78 = puStack_b8;
            lStack_70 = lStack_b0;
            uStack_c0 = 0;
            puStack_b8 = &uStack_80;
            while( true ) {
              cVar2 = FUN_185a610f0(&uStack_80,_DAT_1888c9ab0);
              lVar8 = lStack_70;
              if (cVar2 == '\0') break;
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar2 = FUN_186b63a70(lVar8,0,0);
              if (cVar2 != '\0') {
                if (lVar8 == 0) goto LAB_180a70e6e;
                Torappu_Battle_Tile_RemoveEnemy_0x6011449(lVar8,param_1);
              }
            }
            func_0x00018050cf60(&uStack_80,_DAT_1888c9870);
            lVar8 = *(longlong *)(param_1 + 0x4f0);
            if (lVar8 == 0) goto LAB_180a70e7a;
            *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
            iVar3 = *(int *)(lVar8 + 0x18);
            *(undefined4 *)(lVar8 + 0x18) = 0;
            if (0 < iVar3) {
              System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar8 + 0x10),0,iVar3,0);
            }
          }
          Torappu_Battle_Enemy_ReleaseBlock_0x6012b03(param_1,0);
          if (param_2 == 1) {
            if (DAT_188c92835 == '\0') {
              FUN_18048bf00(&DAT_18881b6b0);
              DAT_188c92835 = '\x01';
            }
            if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
              func_0x00018048c140(_DAT_18881b6b0);
            }
            lVar8 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x2e8);
            if (lVar8 == 0) {
              cVar2 = (char)*(undefined4 *)(param_1 + 0x528);
            }
            else {
              puVar7 = (undefined4 *)
                       XLua_DelegateBridge___Gen_Delegate_Imp3702_0x60018d6
                                 (auStack_58,lVar8,param_1,0);
              cVar2 = (char)*puVar7;
            }
            if (cVar2 == '\0') {
              lVar8 = FUN_185337c50(_DAT_1888d3908);
              if (lVar8 == 0) {
LAB_180a70e7a:
                FUN_18048c0b0();
                pcVar1 = (code *)swi(3);
                (*pcVar1)();
                return;
              }
              Torappu_Battle_BattleController_OnEnemyReachedExit_0x600fd06(lVar8,param_1,lVar6,0);
            }
          }
          iVar9 = 0;
          iVar3 = FUN_1844afc00(*(undefined8 *)(param_1 + 0x4e0),_DAT_1888cb510);
          if (0 < iVar3) {
            do {
              if (*(longlong *)(param_1 + 0x4e0) == 0) goto LAB_180a70e7a;
              lVar6 = FUN_184afcf00(*(longlong *)(param_1 + 0x4e0),iVar9,_DAT_188935b98);
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar2 = FUN_186b63a70(lVar6,0,0);
              if (cVar2 != '\0') {
                if (lVar6 == 0) goto LAB_180a70e7a;
                Torappu_Battle_EnemySkill_Detach_0x6010301(lVar6,0);
              }
              iVar9 = iVar9 + 1;
            } while (iVar9 < iVar3);
          }
          *(undefined8 *)(param_1 + 0x358) = 0;
          func_0x00018048b9e0(param_1 + 0x358,0);
          return;
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
LAB_180a70e6e:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


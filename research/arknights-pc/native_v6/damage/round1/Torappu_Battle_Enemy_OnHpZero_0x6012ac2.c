/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Enemy_OnHpZero_0x6012ac2(longlong *param_1,undefined1 param_2,char param_3)
{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  if (DAT_188c928aa == '\0') {
    uStack_40 = 0x180a70eae;
    FUN_18048bf00(&DAT_1888a8898);
    uStack_40 = 0x180a70eba;
    FUN_18048bf00(&DAT_18881b6b0);
    uStack_40 = 0x180a70ec6;
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c928aa = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    uStack_40 = 0x180a70ee5;
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x690);
  if (lVar3 != 0) {
    uStack_18 = 0;
    uStack_40 = 0x180a70fef;
    XLua_DelegateBridge___Gen_Delegate_Imp264_0x6000b68(lVar3,param_1,param_2,param_3);
    return;
  }
  uStack_40 = 0x180a70f0d;
  lVar3 = Torappu_Battle_Enemy_get_stateMachine_0x6012a56(param_1,0);
  if (lVar3 != 0) {
    if (*(int *)(lVar3 + 0x48) == 8) {
      uStack_40 = 0x180a70f28;
      lVar3 = FUN_185337c50(_DAT_1888d3908);
      if (lVar3 == 0) goto LAB_180a70fff;
      uStack_40 = 0x180a70f3b;
      cVar2 = Torappu_Battle_BattleController_get_isCooperateMode_0x600fbcd(lVar3,0);
      if (cVar2 == '\0') {
        return;
      }
    }
    uStack_40 = 0x180a70f4d;
    lVar3 = Torappu_Battle_Enemy_get_stateMachine_0x6012a56(param_1,0);
    if (lVar3 != 0) {
      if (*(int *)(lVar3 + 0x48) == 8) {
        uStack_40 = 0x180a70f68;
        lVar3 = FUN_185337c50(_DAT_1888d3908);
        if (lVar3 == 0) goto LAB_180a70fff;
        uStack_40 = 0x180a70f7b;
        cVar2 = Torappu_Battle_BattleController_get_isCooperateMode_0x600fbcd(lVar3,0);
        if (cVar2 != '\0') {
          uStack_40 = 0x180a70f8b;
          lVar3 = FUN_185337c50(_DAT_1888d3908);
          if (lVar3 == 0) goto LAB_180a70fff;
          uStack_40 = 0x180a70f9a;
          uVar4 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar3,0);
          uStack_40 = 0x180a70fa9;
          lVar3 = FUN_1800057a0(uVar4,_DAT_1888a8898);
          if (lVar3 == 0) {
            return;
          }
          if (*(char *)(lVar3 + 0x28) == '\0') {
            return;
          }
        }
      }
      if (cRam0000000188c92c0a == '\0') {
        FUN_18048bf00(&DAT_188805040,param_2);
        cRam0000000188c92c0a = '\x01';
      }
      uStack_a8 = 0;
      uStack_e8 = 0;
      uStack_e0 = 0;
      uStack_d8 = 0;
      uStack_d0 = 0;
      uStack_c8 = 0;
      uStack_c0 = 0;
      uStack_b8 = 0;
      uStack_b0 = 0;
      lVar3 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x480);
      if (lVar3 == 0) {
        if ((param_3 == '\0') &&
           (cVar2 = Torappu_Battle_Unit_CheckReborn_0x6012f74(param_1,&uStack_e8,0),
           uStack_18 = uStack_a8, cVar2 != '\0')) {
          uStack_98 = (undefined4)uStack_e8;
          uStack_94 = uStack_e8._4_4_;
          uStack_90 = (undefined4)uStack_e0;
          uStack_8c = uStack_e0._4_4_;
          uStack_88 = (undefined4)uStack_d8;
          uStack_84 = uStack_d8._4_4_;
          uStack_80 = (undefined4)uStack_d0;
          uStack_7c = uStack_d0._4_4_;
          uStack_78 = (undefined4)uStack_c8;
          uStack_74 = uStack_c8._4_4_;
          uStack_70 = (undefined4)uStack_c0;
          uStack_6c = uStack_c0._4_4_;
          uStack_68 = (undefined4)uStack_b8;
          uStack_64 = uStack_b8._4_4_;
          uStack_60 = (undefined4)uStack_b0;
          uStack_5c = uStack_b0._4_4_;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*param_1);
          }
          uStack_40 = CONCAT44(uStack_7c,uStack_80);
          uStack_58 = uStack_98;
          uStack_54 = uStack_94;
          uStack_50 = uStack_90;
          uStack_4c = uStack_8c;
          uStack_48 = uStack_88;
          uStack_44 = uStack_84;
          uStack_38 = uStack_78;
          uStack_34 = uStack_74;
          uStack_30 = uStack_70;
          uStack_2c = uStack_6c;
          uStack_28 = uStack_68;
          uStack_24 = uStack_64;
          uStack_20 = uStack_60;
          uStack_1c = uStack_5c;
          (**(code **)(*param_1 + 0xd00))(param_1,&uStack_58,*(undefined8 *)(*param_1 + 0xd08));
          return;
        }
        Torappu_Battle_Entity_OnHpZero_0x601045b(param_1,param_2,param_3,0);
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp264_0x6000b68(lVar3,param_1,param_2,param_3,0);
      }
      return;
    }
  }
LAB_180a70fff:
  uStack_40 = 0x180a71004;
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

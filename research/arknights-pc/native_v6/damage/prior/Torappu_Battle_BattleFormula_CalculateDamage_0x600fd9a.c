/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_BattleFormula_CalculateDamage_0x600fd9a
               (undefined8 param_1,longlong param_2,undefined4 param_3,undefined8 param_4,
               undefined8 param_5)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  ulonglong in_stack_ffffffffffffff58;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  if (DAT_188c90248 == '\0') {
    FUN_18048bf00(&DAT_18892fda0);
    DAT_188c90248 = '\x01';
  }
  uStack_84 = 0;
  if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x38);
  if (lVar1 == 0) {
    if (DAT_188c90258 == '\0') {
      FUN_18048bf00(&DAT_18885a700);
      DAT_188c90258 = '\x01';
    }
    uStack_88 = param_3;
    uStack_78 = param_1;
    uStack_70 = param_4;
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18885a700);
    }
    uStack_68 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x38);
    uStack_80 = param_1;
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    if (DAT_188c90245 == '\0') {
      FUN_18048bf00(&DAT_18892fda0);
      FUN_18048bf00(&DAT_188932ce8);
      DAT_188c90245 = '\x01';
    }
    if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_18892fda0 + 0xb8) + 0x20);
    if (lVar1 == 0) {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(param_2,0,0);
      if (cVar3 != '\0') {
        if (param_2 == 0) {
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        Torappu_Battle_Entity_OnBeingCalculateDamage_0x6010467(param_2,&uStack_88,0);
      }
      uStack_58 = uStack_88;
      uStack_54 = uStack_84;
      uStack_50 = (undefined4)uStack_80;
      uStack_4c = uStack_80._4_4_;
      uStack_48 = (undefined4)uStack_78;
      uStack_44 = uStack_78._4_4_;
      uStack_40 = (undefined4)uStack_70;
      uStack_3c = uStack_70._4_4_;
      uStack_60 = uStack_68;
      if (*(int *)(_DAT_18892fda0 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uStack_38 = uStack_58;
      uStack_34 = uStack_54;
      uStack_30 = uStack_50;
      uStack_2c = uStack_4c;
      uStack_28 = uStack_48;
      uStack_24 = uStack_44;
      uStack_20 = uStack_40;
      uStack_1c = uStack_3c;
      uStack_18 = uStack_60;
      Torappu_Battle_BattleFormula_CalculateDamageNoEvent_0x600fd98(param_2,0,&uStack_38,0);
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp12109_0x60039ad
                (lVar1,param_2,0,1,in_stack_ffffffffffffff58 & 0xffffffffffffff00,&uStack_88,0);
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp12112_0x60039b0
              (lVar1,param_1,param_2,param_3,param_4,param_5,0);
  }
  return;
}

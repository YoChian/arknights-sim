/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Modifier__ctor_0x6011559
               (undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8)
{
  longlong lVar1;
  undefined8 uVar2;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  if (DAT_188c9170e == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_18896e2a0);
    DAT_188c9170e = '\x01';
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  Torappu_Battle_Modifier_set_targetType_0x601152b(param_1,param_2,0);
  Torappu_Battle_Modifier_set_deltaType_0x601152d(param_1,param_3,0);
  Torappu_Battle_Modifier_set_value_0x6011546(param_1,param_4,0);
  Torappu_Battle_Modifier_set_playerSide_0x6011548(param_1,param_8,0);
  Torappu_Battle_Modifier_set_originValue_0x6011543(param_1,param_5,0);
  Torappu_Battle_Modifier_set_originAtk_0x6011541(param_1,param_5,0);
  FUN_1845638c0(&uStack_c8,param_6,_DAT_18896e2a0);
  *(undefined4 *)param_1 = uStack_c8;
  *(undefined4 *)((longlong)param_1 + 4) = uStack_c4;
  *(undefined4 *)(param_1 + 1) = uStack_c0;
  *(undefined4 *)((longlong)param_1 + 0xc) = uStack_bc;
  func_0x00018048b9e0(param_1,0);
  FUN_1845638c0(&uStack_c8,param_7,_DAT_18896e2a0);
  *(undefined4 *)(param_1 + 2) = uStack_c8;
  *(undefined4 *)((longlong)param_1 + 0x14) = uStack_c4;
  *(undefined4 *)(param_1 + 3) = uStack_c0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = uStack_bc;
  func_0x00018048b9e0(param_1 + 2,0);
  Torappu_Battle_Modifier_set_damageType_0x6011537(param_1,0,0);
  Torappu_Battle_Modifier_set_applyWay_0x6011539(param_1,0,0);
  Torappu_Battle_Modifier_set_cancelReason_0x601153b(param_1,0,0);
  Torappu_Battle_Modifier_set_attackType_0x601153d(param_1,0,0);
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar2 = func_0x0001866fdac0(0,0);
  param_1[7] = uVar2;
  uVar2 = func_0x0001866fdac0(0,0);
  param_1[8] = uVar2;
  param_1[9] = 0;
  func_0x00018048b9e0(param_1 + 9,0);
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0x200);
  if (lVar1 != 0) {
    uStack_b8 = *param_1;
    uStack_b0 = param_1[1];
    uStack_a8 = param_1[2];
    uStack_a0 = param_1[3];
    uStack_98 = param_1[4];
    uStack_90 = param_1[5];
    uStack_88 = param_1[6];
    uStack_80 = param_1[7];
    uStack_78 = param_1[8];
    uStack_70 = param_1[9];
    uStack_68 = param_1[10];
    uStack_60 = param_1[0xb];
    uStack_58 = param_1[0xc];
    uStack_50 = param_1[0xd];
    uStack_48 = *(undefined4 *)(param_1 + 0xe);
    uStack_44 = *(undefined4 *)((longlong)param_1 + 0x74);
    uStack_40 = *(undefined4 *)(param_1 + 0xf);
    uStack_3c = *(undefined4 *)((longlong)param_1 + 0x7c);
    uStack_38 = param_1[0x10];
    XLua_DelegateBridge___Gen_Delegate_Imp3436_0x60017cc
              (lVar1,&uStack_b8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  }
  return;
}

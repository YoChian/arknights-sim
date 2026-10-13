/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Modifier__ctor_0x601155a
               (undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined4 param_7)
{
  longlong lVar1;
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
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  if (DAT_188c9170f == '\0') {
    FUN_18048bf00(&DAT_1888ed178);
    DAT_188c9170f = '\x01';
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  Torappu_Battle_Modifier__ctor_0x6011559
            (param_1,param_2,param_3,param_4,param_4,param_5,param_6,param_7,0);
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0x208);
  if (lVar1 != 0) {
    uStack_a8 = *param_1;
    uStack_a0 = param_1[1];
    uStack_98 = param_1[2];
    uStack_90 = param_1[3];
    uStack_88 = param_1[4];
    uStack_80 = param_1[5];
    uStack_78 = param_1[6];
    uStack_70 = param_1[7];
    uStack_68 = param_1[8];
    uStack_60 = param_1[9];
    uStack_58 = param_1[10];
    uStack_50 = param_1[0xb];
    uStack_48 = param_1[0xc];
    uStack_40 = param_1[0xd];
    uStack_38 = *(undefined4 *)(param_1 + 0xe);
    uStack_34 = *(undefined4 *)((longlong)param_1 + 0x74);
    uStack_30 = *(undefined4 *)(param_1 + 0xf);
    uStack_2c = *(undefined4 *)((longlong)param_1 + 0x7c);
    uStack_28 = param_1[0x10];
    XLua_DelegateBridge___Gen_Delegate_Imp3437_0x60017cd
              (lVar1,&uStack_a8,param_2,param_3,param_4,param_5,param_6,param_7,0);
  }
  return;
}

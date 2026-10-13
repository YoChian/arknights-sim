/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 Torappu_Battle_Modifier_Cancel_0x6011549(undefined8 *param_1,undefined4 param_2)
{
  longlong lVar1;
  char cVar2;
  undefined8 uVar3;
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
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  if (DAT_188c916fe == '\0') {
    FUN_18048bf00(&DAT_1888ed178);
    DAT_188c916fe = '\x01';
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0x180);
  if (lVar1 == 0) {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_1,0);
    if (cVar2 == '\0') {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = Torappu_Battle_Modifier_CheckIgnoreCancel_0x601154a(param_1,param_2,0);
      if (cVar2 == '\0') {
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        Torappu_Battle_Modifier_set_deltaType_0x601152d(param_1,0,0);
        Torappu_Battle_Modifier_set_cancelReason_0x601153b(param_1,param_2,0);
        return 1;
      }
    }
    return 0;
  }
  uStack_98 = *param_1;
  uStack_90 = param_1[1];
  uStack_88 = param_1[2];
  uStack_80 = param_1[3];
  uStack_78 = param_1[4];
  uStack_70 = param_1[5];
  uStack_68 = param_1[6];
  uStack_60 = param_1[7];
  uStack_58 = param_1[8];
  uStack_50 = param_1[9];
  uStack_48 = param_1[10];
  uStack_40 = param_1[0xb];
  uStack_38 = param_1[0xc];
  uStack_30 = param_1[0xd];
  uStack_28 = *(undefined4 *)(param_1 + 0xe);
  uStack_24 = *(undefined4 *)((longlong)param_1 + 0x74);
  uStack_20 = *(undefined4 *)(param_1 + 0xf);
  uStack_1c = *(undefined4 *)((longlong)param_1 + 0x7c);
  uStack_18 = param_1[0x10];
  uVar3 = XLua_DelegateBridge___Gen_Delegate_Imp3417_0x60017b9(lVar1,&uStack_98,param_2,0);
  return uVar3;
}

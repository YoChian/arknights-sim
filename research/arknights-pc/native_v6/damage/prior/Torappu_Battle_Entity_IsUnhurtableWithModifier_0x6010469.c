/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
byte Torappu_Battle_Entity_IsUnhurtableWithModifier_0x6010469(longlong param_1,undefined8 *param_2)
{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  longlong lVar4;
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
  if (DAT_188c908f8 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_1888ed178);
    DAT_188c908f8 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x960);
  if (lVar4 != 0) {
    uStack_98 = *param_2;
    uStack_90 = param_2[1];
    uStack_88 = param_2[2];
    uStack_80 = param_2[3];
    uStack_78 = param_2[4];
    uStack_70 = param_2[5];
    uStack_68 = param_2[6];
    uStack_60 = param_2[7];
    uStack_58 = param_2[8];
    uStack_50 = param_2[9];
    uStack_48 = param_2[10];
    uStack_40 = param_2[0xb];
    uStack_38 = param_2[0xc];
    uStack_30 = param_2[0xd];
    uStack_28 = *(undefined4 *)(param_2 + 0xe);
    uStack_24 = *(undefined4 *)((longlong)param_2 + 0x74);
    uStack_20 = *(undefined4 *)(param_2 + 0xf);
    uStack_1c = *(undefined4 *)((longlong)param_2 + 0x7c);
    uStack_18 = param_2[0x10];
    bVar3 = XLua_DelegateBridge___Gen_Delegate_Imp3065_0x6001659(lVar4,param_1,&uStack_98,0);
    return bVar3;
  }
  if (DAT_188c9086a == '\0') {
    FUN_18048bf00(&DAT_188841368);
    DAT_188c9086a = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x4e8);
  if (lVar4 == 0) {
    lVar4 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
    if (lVar4 == 0) {
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      bVar3 = (*pcVar1)();
      return bVar3;
    }
    cVar2 = Torappu_Battle_Attributes_GetAbnormalFlag_0x600fb18(lVar4,5,0);
    if (cVar2 != '\0') goto LAB_1806f6166;
    cVar2 = *(char *)(param_1 + 0x26);
  }
  else {
    cVar2 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar4,param_1,0);
  }
  if (cVar2 == '\0') {
    return 0;
  }
LAB_1806f6166:
  if (DAT_188c90863 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    DAT_188c90863 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x4b0);
  if (lVar4 == 0) {
    if (*(char *)(param_1 + 0x88) == '\0') {
      return 1;
    }
    if (*(char *)(param_1 + 0x26) != '\0') {
      return 1;
    }
    cVar2 = Torappu_Battle_Entity_isTargetFreeWithImmuneFlag_0x60103cd(param_1,0x2e,0,0);
  }
  else {
    cVar2 = XLua_DelegateBridge___Gen_Delegate_Imp3037_0x600163d(lVar4,param_1,0x2e,0,0);
  }
  if (cVar2 != '\0') {
    return 1;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  bVar3 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x100,0);
  return bVar3 ^ 1;
}

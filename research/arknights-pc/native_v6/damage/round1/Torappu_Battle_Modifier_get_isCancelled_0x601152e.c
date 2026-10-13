/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
bool Torappu_Battle_Modifier_get_isCancelled_0x601152e(undefined8 *param_1)
{
  longlong lVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
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
  undefined *puStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  if (DAT_188c916e3 == '\0') {
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_1888ed178);
    DAT_188c916e3 = '\x01';
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0xa8);
  if (lVar5 == 0) {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar3 = Torappu_Battle_Modifier_get_deltaType_0x601152c(param_1,0);
    if (iVar3 == 0) {
      return true;
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_value_0x6011545(param_1,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    if (cRam0000000188cc370d == '\0') {
      puStack_30 = &UNK_1866e5442;
      FUN_18048bf00(&DAT_18885a700);
      puStack_30 = &UNK_1866e544e;
      FUN_18048bf00(&DAT_1888c3c38);
      puStack_30 = &UNK_1866e545a;
      FUN_18048bf00(&DAT_1888915d8);
      cRam0000000188cc370d = '\x01';
    }
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      puStack_30 = &UNK_1866e5476;
      func_0x00018048c140();
    }
    puStack_30 = &UNK_1866e5480;
    lVar5 = Torappu_TSMath_Abs_0x600034b(uVar4,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      puStack_30 = &UNK_1866e549b;
      func_0x00018048c140(_DAT_1888c3c38);
    }
    lVar1 = **(longlong **)(_DAT_1888c3c38 + 0xb8);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = &UNK_1866e54c1;
      func_0x00018048c140();
    }
    return lVar5 < lVar1;
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
  puStack_30 = (undefined *)param_1[0xd];
  uStack_28 = *(undefined4 *)(param_1 + 0xe);
  uStack_24 = *(undefined4 *)((longlong)param_1 + 0x74);
  uStack_20 = *(undefined4 *)(param_1 + 0xf);
  uStack_1c = *(undefined4 *)((longlong)param_1 + 0x7c);
  uStack_18 = param_1[0x10];
  uVar2 = XLua_DelegateBridge___Gen_Delegate_Imp3401_0x60017a9(lVar5,&uStack_98,0);
  return (bool)uVar2;
}

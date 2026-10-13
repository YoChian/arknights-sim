/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
longlong Torappu_Battle_Scheduler_SpawnSummonedEnemyTrackedInGameMode_0x60119b0
                   (undefined8 param_1,undefined8 *param_2)
{
  undefined8 uVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong lVar10;
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
  if (DAT_188c91a4c == '\0') {
    FUN_18048bf00(&DAT_18891b6c0);
    FUN_18048bf00(&DAT_188899458);
    DAT_188c91a4c = '\x01';
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_18891b6c0 + 0xb8) + 0x220);
  if (lVar10 == 0) {
    lVar10 = func_0x00018045cfe0(_DAT_188899458);
    if (lVar10 != 0) {
      _UpdateVirtualControl_d__78__ctor_0x60000f6(lVar10,0,0);
      *(undefined8 *)(lVar10 + 0x20) = param_1;
      func_0x00018048b9e0(lVar10 + 0x20,param_1);
      uVar1 = param_2[1];
      uVar7 = param_2[2];
      uVar8 = param_2[3];
      *(undefined8 *)(lVar10 + 0x28) = *param_2;
      *(undefined8 *)(lVar10 + 0x30) = uVar1;
      uVar1 = param_2[4];
      uVar9 = param_2[5];
      *(undefined8 *)(lVar10 + 0x38) = uVar7;
      *(undefined8 *)(lVar10 + 0x40) = uVar8;
      uVar7 = param_2[6];
      uVar8 = param_2[7];
      *(undefined8 *)(lVar10 + 0x48) = uVar1;
      *(undefined8 *)(lVar10 + 0x50) = uVar9;
      uVar1 = param_2[8];
      uVar9 = param_2[9];
      *(undefined8 *)(lVar10 + 0x58) = uVar7;
      *(undefined8 *)(lVar10 + 0x60) = uVar8;
      uVar3 = *(undefined4 *)(param_2 + 10);
      uVar4 = *(undefined4 *)((longlong)param_2 + 0x54);
      uVar5 = *(undefined4 *)(param_2 + 0xb);
      uVar6 = *(undefined4 *)((longlong)param_2 + 0x5c);
      *(undefined8 *)(lVar10 + 0x68) = uVar1;
      *(undefined8 *)(lVar10 + 0x70) = uVar9;
      uVar1 = param_2[0xc];
      *(undefined4 *)(lVar10 + 0x78) = uVar3;
      *(undefined4 *)(lVar10 + 0x7c) = uVar4;
      *(undefined4 *)(lVar10 + 0x80) = uVar5;
      *(undefined4 *)(lVar10 + 0x84) = uVar6;
      *(undefined8 *)(lVar10 + 0x88) = uVar1;
      func_0x00018048b9e0(lVar10 + 0x28,0);
      return lVar10;
    }
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    lVar10 = (*pcVar2)();
    return lVar10;
  }
  uStack_78 = *param_2;
  uStack_70 = param_2[1];
  uStack_68 = param_2[2];
  uStack_60 = param_2[3];
  uStack_58 = param_2[4];
  uStack_50 = param_2[5];
  uStack_48 = param_2[6];
  uStack_40 = param_2[7];
  uStack_38 = param_2[8];
  uStack_30 = param_2[9];
  uStack_28 = *(undefined4 *)(param_2 + 10);
  uStack_24 = *(undefined4 *)((longlong)param_2 + 0x54);
  uStack_20 = *(undefined4 *)(param_2 + 0xb);
  uStack_1c = *(undefined4 *)((longlong)param_2 + 0x5c);
  uStack_18 = param_2[0xc];
  lVar10 = XLua_DelegateBridge___Gen_Delegate_Imp3525_0x6001825(lVar10,param_1,&uStack_78,0);
  return lVar10;
}

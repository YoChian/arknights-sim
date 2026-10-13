
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_BuildAsPredefined_0x601289e
               (longlong *param_1,undefined8 param_2,longlong param_3,uint param_4)

{
  longlong lVar1;
  code *pcVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined8 uStack_a8;
  longlong lStack_a0;
  ulonglong uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  longlong lStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c925d7 == '\0') {
    FUN_18048bf00(&DAT_188821ca8);
    FUN_18048bf00(&DAT_18886c268);
    DAT_188c925d7 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lStack_a0 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x3a8);
  if (lStack_a0 == 0) {
    uStack_98 = 0;
    uStack_90 = 0;
    uStack_88 = 0;
    uStack_80 = 0;
    uStack_78 = 0;
    uStack_70 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_a8 = param_2;
    func_0x00018048b9e0(&uStack_a8,param_2);
    lStack_a0 = param_3;
    func_0x00018048b9e0(&lStack_a0,param_3);
    uStack_98 = (ulonglong)param_4;
    uStack_88 = 0;
    func_0x00018048b9e0(&uStack_88,0);
    if (param_3 == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar3 = Torappu_Battle_Tile_get_playerSideMask_0x601140a(param_3,0);
    uVar4 = func_0x0001866e8c00(uVar3,0);
    uStack_78._0_5_ = (uint5)uVar4;
    if (*(int *)(_DAT_188821ca8 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188821ca8);
    }
    lVar1 = *(longlong *)(_DAT_188821ca8 + 0xb8);
    uStack_70._0_4_ = *(undefined4 *)(lVar1 + 0x28);
    uStack_70._4_4_ = *(undefined4 *)(lVar1 + 0x2c);
    uStack_68._0_4_ = *(undefined4 *)(lVar1 + 0x30);
    uStack_68._4_4_ = *(undefined4 *)(lVar1 + 0x34);
    uStack_60._0_4_ = *(undefined4 *)(lVar1 + 0x38);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar5 = (**(code **)(*param_1 + 0xe80))(param_1,*(undefined8 *)(*param_1 + 0xe88));
    uStack_58 = uStack_a8;
    lStack_50 = lStack_a0;
    uStack_90 = CONCAT44(uStack_90._4_4_,uVar5);
    uStack_38 = uStack_88;
    uStack_30 = uStack_80;
    uStack_48 = uStack_98;
    uStack_40 = uStack_90;
    uStack_18 = (undefined4)uStack_68;
    uStack_14 = uStack_68._4_4_;
    uStack_10 = (undefined4)uStack_60;
    uStack_c = uStack_60._4_4_;
    *(undefined1 *)((longlong)param_1 + 0x36e) = 1;
    uStack_28 = (undefined4)uStack_78;
    uStack_24 = uStack_78._4_4_;
    uStack_20 = (undefined4)uStack_70;
    uStack_1c = uStack_70._4_4_;
    Torappu_Battle_Character__BuildAtInternal_0x60128d3(param_1,&uStack_58,0);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp1374_0x6000fbe
              (lStack_a0,param_1,param_2,param_3,param_4,0);
  }
  return;
}


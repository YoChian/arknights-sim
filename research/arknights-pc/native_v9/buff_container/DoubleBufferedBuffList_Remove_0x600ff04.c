
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 DoubleBufferedBuffList_Remove_0x600ff04(longlong param_1,longlong param_2)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
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
  
  if (DAT_188c90388 == '\0') {
    FUN_18048bf00(&DAT_1888d5490);
    FUN_18048bf00(&DAT_1888dd438);
    FUN_18048bf00(0x1888dd8b8);
    FUN_18048bf00(&DAT_1888ddaf8);
    FUN_18048bf00(&DAT_1889316a8);
    FUN_18048bf00(&DAT_188931b28);
    DAT_188c90388 = '\x01';
  }
  uStack_38 = 0;
  uStack_30 = 0;
  if (**(longlong **)(_DAT_1888d5490 + 0xb8) != 0) {
    uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp29_0x6000a7d
                      (**(longlong **)(_DAT_1888d5490 + 0xb8),param_1,param_2,0);
    return uVar7;
  }
  if (param_2 == 0) {
    return 0;
  }
  if (*(longlong *)(param_1 + 0x10) != 0) {
    iVar1 = *(int *)(*(longlong *)(param_1 + 0x10) + 0x18);
    do {
      do {
        iVar1 = iVar1 + -1;
        if (iVar1 < 0) {
          return 0;
        }
        if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_180690bfe;
        FUN_184ad2ef0(&uStack_28,*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888ddaf8);
        uStack_38 = CONCAT44(uStack_24,uStack_28);
        uStack_30 = CONCAT44(uStack_1c,uStack_20);
        cVar3 = FUN_185159fc0(&uStack_38,_DAT_188931b28);
      } while (cVar3 == '\0');
      if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_180690bfe;
      FUN_184ad2ef0(&uStack_18,*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888ddaf8);
      uStack_38 = CONCAT44(uStack_14,uStack_18);
      uStack_30 = CONCAT44(uStack_c,uStack_10);
      lVar6 = FUN_185159d80(&uStack_38,_DAT_1889316a8);
      if (lVar6 == 0) goto LAB_180690bfe;
      iVar4 = Torappu_Battle_Buff_get_instanceUid_0x600fe22(lVar6,0);
      iVar5 = Torappu_Battle_Buff_get_instanceUid_0x600fe22(param_2,0);
    } while (iVar4 != iVar5);
    if (*(longlong *)(param_1 + 0x10) != 0) {
      FUN_184acd910(*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888dd438);
      return 1;
    }
  }
LAB_180690bfe:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar7 = (*pcVar2)();
  return uVar7;
}


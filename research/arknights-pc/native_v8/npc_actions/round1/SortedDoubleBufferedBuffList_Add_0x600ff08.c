
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SortedDoubleBufferedBuffList_Add_0x600ff08(longlong param_1,undefined4 *param_2)

{
  code *pcVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  int iVar8;
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
  
  if (DAT_188c9038c == '\0') {
    FUN_18048bf00(&DAT_18882b2a8);
    FUN_18048bf00(&DAT_1888dcfb8);
    FUN_18048bf00(0x1888dd8b8);
    FUN_18048bf00(&DAT_1888ddaf8);
    FUN_18048bf00(&DAT_1889316a8);
    FUN_18048bf00(&DAT_188931b28);
    FUN_18048bf00(&DAT_1888d5b50);
    DAT_188c9038c = '\x01';
  }
  uStack_38 = 0;
  uStack_30 = 0;
  if (**(longlong **)(_DAT_1888d5b50 + 0xb8) != 0) {
    uStack_18 = *param_2;
    uStack_14 = param_2[1];
    uStack_10 = param_2[2];
    uStack_c = param_2[3];
    XLua_DelegateBridge___Gen_Delegate_Imp2871_0x6001597
              (**(longlong **)(_DAT_1888d5b50 + 0xb8),param_1,&uStack_18,0);
    return;
  }
  cVar3 = FUN_185159fc0(param_2,_DAT_188931b28);
  if (cVar3 == '\0') {
    uStack_28 = *param_2;
    uStack_24 = param_2[1];
    uStack_20 = param_2[2];
    uStack_1c = param_2[3];
    FUN_185a16f20(param_1,&uStack_28,_DAT_18882b2a8);
    return;
  }
  lVar6 = FUN_185159d80(param_2,_DAT_1889316a8);
  if (*(longlong *)(param_1 + 0x10) != 0) {
    iVar2 = *(int *)(*(longlong *)(param_1 + 0x10) + 0x18);
    do {
      do {
        iVar8 = iVar2;
        iVar2 = iVar8 + -1;
        if (iVar2 < 0) {
          lVar6 = *(longlong *)(param_1 + 0x10);
          if (lVar6 == 0) goto LAB_1806925bb;
          uStack_18 = *param_2;
          uStack_14 = param_2[1];
          uStack_10 = param_2[2];
          uStack_c = param_2[3];
          iVar8 = 0;
          goto LAB_180692553;
        }
        if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_1806925bb;
        FUN_184ad2ef0(&uStack_28,*(longlong *)(param_1 + 0x10),iVar2,_DAT_1888ddaf8);
        uStack_38 = CONCAT44(uStack_24,uStack_28);
        uStack_30 = CONCAT44(uStack_1c,uStack_20);
        cVar3 = FUN_185159fc0(&uStack_38,_DAT_188931b28);
      } while (cVar3 == '\0');
      if (lVar6 == 0) goto LAB_1806925bb;
      iVar4 = Torappu_Battle_Buff_get_onEventPriority_0x600fe43(lVar6,0);
      if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_1806925bb;
      FUN_184ad2ef0(&uStack_18,*(longlong *)(param_1 + 0x10),iVar2,_DAT_1888ddaf8);
      uStack_38 = CONCAT44(uStack_14,uStack_18);
      uStack_30 = CONCAT44(uStack_c,uStack_10);
      lVar7 = FUN_185159d80(&uStack_38,_DAT_1889316a8);
      if (lVar7 == 0) goto LAB_1806925bb;
      iVar5 = Torappu_Battle_Buff_get_onEventPriority_0x600fe43(lVar7,0);
    } while (iVar5 < iVar4);
    lVar6 = *(longlong *)(param_1 + 0x10);
    if (lVar6 != 0) {
      uStack_18 = *param_2;
      uStack_14 = param_2[1];
      uStack_10 = param_2[2];
      uStack_c = param_2[3];
LAB_180692553:
      FUN_184acc090(lVar6,iVar8,&uStack_18,_DAT_1888dcfb8);
      return;
    }
  }
LAB_1806925bb:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void DoubleBufferedBuffList_ClearInvalidElementsIfNotLoop_0x600ff05(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c90389 == '\0') {
    FUN_18048bf00(&DAT_1888d5490);
    FUN_18048bf00(&DAT_18882bdc0);
    FUN_18048bf00(&DAT_1888dd438);
    FUN_18048bf00(0x1888dd8b8);
    FUN_18048bf00(&DAT_1888ddaf8);
    FUN_18048bf00(&DAT_188931b28);
    DAT_188c90389 = '\x01';
  }
  uStack_28 = 0;
  uStack_20 = 0;
  lVar2 = *(longlong *)(*(longlong *)(_DAT_1888d5490 + 0xb8) + 8);
  if (lVar2 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar2,param_1,0);
    return;
  }
  cVar4 = FUN_185a19b40(param_1,_DAT_18882bdc0);
  if (cVar4 == '\0') {
    if (*(longlong *)(param_1 + 0x10) == 0) {
LAB_1806908a6:
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    iVar1 = *(int *)(*(longlong *)(param_1 + 0x10) + 0x18);
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_1806908a6;
      FUN_184ad2ef0(&uStack_18,*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888ddaf8);
      uStack_28 = CONCAT44(uStack_14,uStack_18);
      uStack_20 = CONCAT44(uStack_c,uStack_10);
      cVar4 = FUN_185159fc0(&uStack_28,_DAT_188931b28);
      if (cVar4 == '\0') {
        if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_1806908a6;
        FUN_184acd910(*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888dd438);
      }
    }
  }
  return;
}


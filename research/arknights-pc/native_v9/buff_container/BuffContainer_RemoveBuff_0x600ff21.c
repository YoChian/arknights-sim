
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 BuffContainer_RemoveBuff_0x600ff21(longlong param_1,undefined4 param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined1 uVar4;
  longlong lStackX_20;
  
  if (DAT_188c903a3 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_188944048);
    DAT_188c903a3 = '\x01';
  }
  lStackX_20 = 0;
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x50);
  if (lVar1 != 0) {
    uVar4 = XLua_DelegateBridge___Gen_Delegate_Imp299_0x6000b8b(lVar1,param_1,param_2,0);
    return uVar4;
  }
  if (*(longlong *)(param_1 + 0x28) != 0) {
    cVar3 = FUN_1859851e0(*(longlong *)(param_1 + 0x28),param_2,&lStackX_20,_DAT_188944048);
    if (cVar3 == '\0') {
      return 0;
    }
    if (lStackX_20 != 0) {
      Torappu_Battle_Buff_MarkFinish_0x600fe62(lStackX_20,1,0);
      return 1;
    }
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar4 = (*pcVar2)();
  return uVar4;
}


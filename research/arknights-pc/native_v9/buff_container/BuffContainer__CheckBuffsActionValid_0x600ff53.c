
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 BuffContainer__CheckBuffsActionValid_0x600ff53(longlong param_1,undefined4 param_2)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined1 auStack_20 [24];
  
  if (DAT_188c903d5 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c903d5 = '\x01';
  }
  uStack_30 = 0;
  uStack_28 = 0;
  lVar3 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x1e0);
  if (lVar3 != 0) {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp2923_0x60015cb(lVar3,param_1,param_2,0);
    return uVar6;
  }
  if (*(longlong *)(param_1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    uVar6 = (*pcVar1)();
    return uVar6;
  }
  lVar3 = FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
  do {
    if (lVar3 == 0) {
LAB_18067e59d:
      FUN_18048c0b0();
      FUN_180472d50();
      pcVar1 = (code *)swi(3);
      uVar6 = (*pcVar1)();
      return uVar6;
    }
    cVar2 = FUN_180005310(0,_DAT_188959b58);
    if (cVar2 == '\0') {
      if (lVar3 != 0) {
        FUN_180005310(0,_DAT_188954c98,lVar3);
      }
      return 0;
    }
    if (lVar3 == 0) {
      FUN_18048c0b0();
      goto LAB_18067e59d;
    }
    puVar4 = (undefined8 *)FUN_18000f5e0(auStack_20,0,_DAT_1888cfcb0);
    uStack_30 = *puVar4;
    uStack_28 = puVar4[1];
    lVar5 = FUN_185159d80(&uStack_30,_DAT_1889316a8);
    if (lVar5 != 0) {
      cVar2 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar5,0);
      if (cVar2 == '\0') {
        cVar2 = Torappu_Battle_Buff__IsActionValid_0x600fe58(lVar5,param_2,0);
        if (cVar2 != '\0') {
          if (lVar3 != 0) {
            FUN_180005310(0,_DAT_188954c98,lVar3);
          }
          return 1;
        }
      }
    }
  } while( true );
}


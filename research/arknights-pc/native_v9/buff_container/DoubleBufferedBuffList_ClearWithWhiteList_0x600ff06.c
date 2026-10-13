
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void DoubleBufferedBuffList_ClearWithWhiteList_0x600ff06(longlong param_1,longlong param_2)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c9038a == '\0') {
    FUN_18048bf00(&DAT_1888d5490);
    FUN_18048bf00(&DAT_1888c9940);
    FUN_18048bf00(&DAT_1888dd438);
    FUN_18048bf00(0x1888dd8b8);
    FUN_18048bf00(&DAT_1888ddaf8);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c9038a = '\x01';
  }
  uStack_28 = 0;
  uStack_20 = 0;
  lVar4 = *(longlong *)(*(longlong *)(_DAT_1888d5490 + 0xb8) + 0x10);
  if (lVar4 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar4,param_1,param_2,0);
    return;
  }
  if (*(longlong *)(param_1 + 0x10) != 0) {
    iVar1 = *(int *)(*(longlong *)(param_1 + 0x10) + 0x18);
    while( true ) {
      while( true ) {
        do {
          do {
            iVar1 = iVar1 + -1;
            if (iVar1 < 1) {
              return;
            }
            if (*(longlong *)(param_1 + 0x10) == 0) goto LAB_180690a3a;
            FUN_184ad2ef0(&uStack_18,*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888ddaf8);
            uStack_28 = CONCAT44(uStack_14,uStack_18);
            uStack_20 = CONCAT44(uStack_c,uStack_10);
            lVar4 = FUN_185159d80(&uStack_28,_DAT_1889316a8);
          } while (lVar4 == 0);
          uVar5 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar4,0);
          if (param_2 == 0) goto LAB_180690a3a;
          cVar3 = FUN_184d0ba50(param_2,uVar5,_DAT_1888c9940);
        } while (cVar3 != '\0');
        cVar3 = Torappu_Battle_Buff_get_isFinished_0x600fe4d(lVar4,0);
        if (cVar3 != '\0') break;
        Torappu_Battle_Buff_set_needRemove_0x600fe4f(lVar4,1,0);
      }
      if (*(longlong *)(param_1 + 0x10) == 0) break;
      FUN_184acd910(*(longlong *)(param_1 + 0x10),iVar1,_DAT_1888dd438);
    }
  }
LAB_180690a3a:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


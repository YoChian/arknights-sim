
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BuffContainer_OnOtherBuffStart_0x600ff86(longlong param_1,longlong param_2)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar5;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 auStack_30 [24];
  
  if (DAT_188c90408 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18891d598);
    FUN_18048bf00(&DAT_18891d7d8);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c90408 = '\x01';
  }
  uStack_40 = 0;
  uStack_38 = 0;
  lVar3 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x378);
  if (lVar3 == 0) {
    cVar2 = BuffContainer__CheckBuffsActionValid_0x600ff53(param_1,0x24,0);
    if (cVar2 != '\0') {
      lVar3 = BuffContainer_get_context_0x600ff1a(param_1,0);
      if ((lVar3 != 0) && (*(longlong *)(lVar3 + 0x58) != 0)) {
        FUN_185733520(*(longlong *)(lVar3 + 0x58),param_2,_DAT_18891d7d8);
        if (*(longlong *)(param_1 + 0x18) != 0) {
          lVar3 = FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
LAB_180673d80:
          if (lVar3 != 0) {
            cVar2 = FUN_180005310(0,_DAT_188959b58);
            if (cVar2 == '\0') {
              if (lVar3 != 0) {
                FUN_180005310(0,_DAT_188954c98,lVar3);
              }
              goto LAB_180673e7b;
            }
            if (lVar3 != 0) goto code_r0x000180673db8;
            FUN_18048c0b0();
          }
          FUN_18048c0b0();
          FUN_180472d50();
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
LAB_180673eeb:
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar3,param_1,param_2,0);
  }
  return;
code_r0x000180673db8:
  puVar4 = (undefined8 *)FUN_18000f5e0(auStack_30,0,_DAT_1888cfcb0);
  uStack_40 = *puVar4;
  uStack_38 = puVar4[1];
  lVar5 = FUN_185159d80(&uStack_40,_DAT_1889316a8);
  if (((lVar5 != 0) &&
      (cVar2 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar5,0), cVar2 == '\0')) &&
     (lVar5 != param_2)) {
    if ((param_2 != 0) && (*(char *)(param_2 + 0x1fa) != '\0')) {
      if (lVar3 != 0) {
        FUN_180005310(0,_DAT_188954c98,lVar3);
      }
LAB_180673e7b:
      lVar3 = BuffContainer_get_context_0x600ff1a(param_1,0);
      if ((lVar3 != 0) && (*(longlong *)(lVar3 + 0x58) != 0)) {
        FUN_185733450(*(longlong *)(lVar3 + 0x58),_DAT_18891d598);
        BuffContainer__CheckFinishedBuffs_0x600ff52(param_1,0);
        return;
      }
      goto LAB_180673eeb;
    }
    Torappu_Battle_Buff_OnOtherBuffStart_0x600fe9d(lVar5,0);
  }
  goto LAB_180673d80;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void BuffContainer_OnOwnerFinish_0x600ff5e(longlong param_1,undefined4 param_2,undefined8 param_3)
{
  longlong lVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  undefined8 *puVar5;
  longlong lVar6;
  ushort uVar7;
  longlong *aplStack_68 [2];
  undefined8 uStack_58;
  longlong **pplStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined1 auStack_38 [16];
  if (DAT_188c903e0 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c903e0 = '\x01';
  }
  uStack_48 = 0;
  uStack_40 = 0;
  lVar6 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x238);
  if (lVar6 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp2937_0x60015d9(lVar6,param_1,param_2,param_3,0);
    return;
  }
  if (*(longlong *)(param_1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  aplStack_68[0] = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
  uStack_58 = 0;
  pplStack_50 = aplStack_68;
  do {
    if (aplStack_68[0] == (longlong *)0x0) {
LAB_180675ff3:
      FUN_18048c0b0();
      FUN_180472d50();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    cVar4 = FUN_180005310(0,_DAT_188959b58);
    plVar3 = aplStack_68[0];
    lVar6 = _DAT_1888cfcb0;
    if (cVar4 == '\0') {
      if (aplStack_68[0] != (longlong *)0x0) {
        FUN_180005310(0,_DAT_188954c98,aplStack_68[0]);
      }
      BuffContainer__CheckFinishedBuffs_0x600ff52(param_1,0);
      return;
    }
    if (aplStack_68[0] == (longlong *)0x0) {
      FUN_18048c0b0();
      goto LAB_180675ff3;
    }
    lVar1 = *aplStack_68[0];
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar1);
    }
    uVar7 = 0;
    if (*(ushort *)(lVar1 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar7 * 0x10) == lVar6) {
          puVar5 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) +
                    0x14) * 0x10 + lVar1);
          goto LAB_180675f05;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(ushort *)(lVar1 + 0x12e));
    }
    puVar5 = (undefined8 *)FUN_180445cc0(plVar3,lVar6,0);
LAB_180675f05:
    puVar5 = (undefined8 *)(*(code *)*puVar5)(auStack_38,plVar3,puVar5[1]);
    uStack_48 = *puVar5;
    uStack_40 = puVar5[1];
    lVar6 = FUN_185159d80(&uStack_48,_DAT_1889316a8);
    if (lVar6 != 0) {
      Torappu_Battle_Buff_OnOwnerFinish_0x600fe83(lVar6,param_2,param_3,0);
    }
  } while( true );
}

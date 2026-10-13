
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BuffContainer_RemoveBuffs_0x600ff23(longlong param_1,undefined8 param_2,longlong param_3)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong lVar6;
  ushort uVar7;
  longlong *aplStack_58 [2];
  undefined8 uStack_48;
  longlong **pplStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined1 auStack_28 [16];
  
  if (DAT_188c903a5 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c903a5 = '\x01';
  }
  uStack_38 = 0;
  uStack_30 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x60);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar5,param_1,param_2,param_3,0);
    return;
  }
  if (*(longlong *)(param_1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  aplStack_58[0] = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
  uStack_48 = 0;
  pplStack_40 = aplStack_58;
LAB_18067b232:
  if (aplStack_58[0] != (longlong *)0x0) {
    cVar3 = FUN_180005310(0,_DAT_188959b58);
    plVar2 = aplStack_58[0];
    lVar5 = _DAT_1888cfcb0;
    if (cVar3 == '\0') {
      if (aplStack_58[0] == (longlong *)0x0) {
        return;
      }
      FUN_180005310(0,_DAT_188954c98,aplStack_58[0]);
      return;
    }
    if (aplStack_58[0] != (longlong *)0x0) goto code_r0x00018067b264;
    goto LAB_18067b3da;
  }
LAB_18067b3df:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
code_r0x00018067b264:
  lVar6 = *aplStack_58[0];
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(lVar6);
  }
  uVar7 = 0;
  if (*(ushort *)(lVar6 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar7 * 0x10) == lVar5) {
        puVar4 = (undefined8 *)
                 (((longlong)*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) +
                  0x14) * 0x10 + lVar6);
        goto LAB_18067b2c9;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(ushort *)(lVar6 + 0x12e));
  }
  puVar4 = (undefined8 *)FUN_180445cc0(plVar2,lVar5,0);
LAB_18067b2c9:
  puVar4 = (undefined8 *)(*(code *)*puVar4)(auStack_28,plVar2,puVar4[1]);
  uStack_38 = *puVar4;
  uStack_30 = puVar4[1];
  lVar5 = FUN_185159d80(&uStack_38,_DAT_1889316a8);
  if ((lVar5 != 0) && (lVar5 != param_3)) {
    lVar6 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar5,0);
    if (lVar6 == 0) {
      FUN_18048c0b0();
LAB_18067b3da:
      FUN_18048c0b0();
      goto LAB_18067b3df;
    }
    cVar3 = func_0x000185db7700(lVar6,param_2,0);
    if (cVar3 != '\0') {
      Torappu_Battle_Buff_MarkFinish_0x600fe62(lVar5,1,0);
    }
  }
  goto LAB_18067b232;
}


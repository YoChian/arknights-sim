/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void BuffContainer_OnOwnerHpFull_0x600ffad(longlong param_1)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong *plVar4;
  undefined8 *puVar5;
  longlong lVar6;
  ushort uVar7;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 auStack_40 [24];
  if (DAT_188c9042f == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c9042f = '\x01';
  }
  uStack_50 = 0;
  uStack_48 = 0;
  lVar6 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x4b0);
  if (lVar6 == 0) {
    cVar3 = BuffContainer__CheckBuffsActionValid_0x600ff53(param_1,0x62);
    if (cVar3 != '\0') {
      if (*(longlong *)(param_1 + 0x18) == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      plVar4 = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
      do {
        if (plVar4 == (longlong *)0x0) {
LAB_18067626b:
          FUN_18048c0b0();
          FUN_180472d50();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        cVar3 = FUN_180005310(0,_DAT_188959b58);
        lVar6 = _DAT_1888cfcb0;
        if (cVar3 == '\0') {
          if (plVar4 != (longlong *)0x0) {
            FUN_180005310(0,_DAT_188954c98,plVar4);
          }
          BuffContainer__CheckFinishedBuffs_0x600ff52(param_1,0);
          return;
        }
        if (plVar4 == (longlong *)0x0) {
          FUN_18048c0b0();
          goto LAB_18067626b;
        }
        lVar1 = *plVar4;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(lVar1);
        }
        uVar7 = 0;
        if (*(ushort *)(lVar1 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar7 * 0x10) == lVar6) {
              puVar5 = (undefined8 *)
                       (((longlong)
                         *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) + 0x14)
                        * 0x10 + lVar1);
              goto LAB_180676186;
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < *(ushort *)(lVar1 + 0x12e));
        }
        puVar5 = (undefined8 *)FUN_180445cc0(plVar4,lVar6,0);
LAB_180676186:
        puVar5 = (undefined8 *)(*(code *)*puVar5)(auStack_40,plVar4,puVar5[1]);
        uStack_50 = *puVar5;
        uStack_48 = puVar5[1];
        lVar6 = FUN_185159d80(&uStack_50,_DAT_1889316a8);
        if ((lVar6 != 0) &&
           (cVar3 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar6,0), cVar3 == '\0'))
        {
          Torappu_Battle_Buff_OnOwnerHpFull_0x600fed2(lVar6,0);
        }
      } while( true );
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar6,param_1,0);
  }
  return;
}

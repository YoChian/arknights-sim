/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void BuffContainer_OnBeingCalculateDamage_0x600ff7a(longlong param_1,undefined8 *param_2)
{
  longlong lVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  longlong lVar5;
  undefined8 *puVar6;
  ushort uVar7;
  longlong *plStackX_20;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  longlong **pplStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  undefined1 auStack_38 [16];
  if (DAT_188c903fc == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c903fc = '\x01';
  }
  plStackX_20 = (longlong *)0x0;
  uStack_90 = 0;
  uStack_88 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x318);
  if (lVar5 == 0) {
    cVar4 = BuffContainer__CheckBuffsActionValid_0x600ff53(param_1,0x49,0);
    if (cVar4 != '\0') {
      lVar5 = BuffContainer_get_context_0x600ff1a(param_1,0);
      if (lVar5 != 0) {
        uStack_b8 = Torappu_Battle_Context_BeginChangeGard_0x6010096(lVar5,0);
        uStack_a0 = 0;
        puStack_98 = &uStack_b8;
        if (*(longlong *)(param_1 + 0x18) != 0) {
          plStackX_20 = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
          uStack_b0 = 0;
          pplStack_a8 = &plStackX_20;
          while (plStackX_20 != (longlong *)0x0) {
            cVar4 = FUN_180005310(0,_DAT_188959b58);
            plVar3 = plStackX_20;
            lVar5 = _DAT_1888cfcb0;
            if (cVar4 == '\0') {
              if (plStackX_20 != (longlong *)0x0) {
                FUN_180005310(0,_DAT_188954c98,plStackX_20);
              }
              ChangeGuard_Dispose_0x60100ba(&uStack_b8,0);
              BuffContainer__CheckFinishedBuffs_0x600ff52(param_1,0);
              return;
            }
            if (plStackX_20 == (longlong *)0x0) {
              FUN_18048c0b0();
              break;
            }
            lVar1 = *plStackX_20;
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(lVar1);
            }
            uVar7 = 0;
            if (*(ushort *)(lVar1 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar7 * 0x10) == lVar5) {
                  puVar6 = (undefined8 *)
                           (((longlong)
                             *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) +
                            0x14) * 0x10 + lVar1);
                  goto LAB_18066f0e9;
                }
                uVar7 = uVar7 + 1;
              } while (uVar7 < *(ushort *)(lVar1 + 0x12e));
            }
            puVar6 = (undefined8 *)FUN_180445cc0(plVar3,lVar5,0);
LAB_18066f0e9:
            puVar6 = (undefined8 *)(*(code *)*puVar6)(auStack_38,plVar3,puVar6[1]);
            uStack_90 = *puVar6;
            uStack_88 = puVar6[1];
            lVar5 = FUN_185159d80(&uStack_90,_DAT_1889316a8);
            if ((lVar5 != 0) &&
               (cVar4 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar5,0),
               cVar4 == '\0')) {
              uStack_68 = *param_2;
              uStack_60 = param_2[1];
              uStack_58 = *(undefined4 *)(param_2 + 2);
              uStack_54 = *(undefined4 *)((longlong)param_2 + 0x14);
              uStack_50 = *(undefined4 *)(param_2 + 3);
              uStack_4c = *(undefined4 *)((longlong)param_2 + 0x1c);
              uStack_48 = param_2[4];
              ChangeGuard_set_atkInfo_0x60100b5(&uStack_b8,&uStack_68,0);
              Torappu_Battle_Buff_OnBeingCalculateDamage_0x600fe93(lVar5,param_2,0);
            }
          }
          FUN_18048c0b0();
          FUN_180472d50();
          FUN_180472d50();
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp2938_0x60015da(lVar5,param_1,param_2,0);
  }
  return;
}

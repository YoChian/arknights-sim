/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void BuffContainer_OnBeforeTrySetHpZero_0x600ff95
               (longlong param_1,undefined8 *param_2,longlong *param_3)
{
  longlong lVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  longlong lVar5;
  undefined8 *puVar6;
  ushort uVar7;
  longlong *plStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  longlong **pplStack_100;
  undefined8 uStack_f8;
  undefined8 *puStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  undefined1 auStack_38 [16];
  if (DAT_188c90417 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c90417 = '\x01';
  }
  plStack_118 = (longlong *)0x0;
  uStack_e8 = 0;
  uStack_e0 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x3f0);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp10823_0x60034a7(lVar5,param_1,param_2,param_3,0);
    return;
  }
  *param_3 = 0;
  func_0x00018048b9e0(param_3,0);
  lVar5 = BuffContainer_get_context_0x600ff1a(param_1,0);
  if (lVar5 != 0) {
    uStack_110 = Torappu_Battle_Context_BeginChangeGard_0x6010096(lVar5,0);
    uStack_f8 = 0;
    puStack_f0 = &uStack_110;
    if (*(longlong *)(param_1 + 0x18) != 0) {
      plStack_118 = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
      uStack_108 = 0;
      pplStack_100 = &plStack_118;
      while (plStack_118 != (longlong *)0x0) {
        cVar4 = FUN_180005310(0,_DAT_188959b58);
        plVar3 = plStack_118;
        lVar5 = _DAT_1888cfcb0;
        if (cVar4 == '\0') {
          if (plStack_118 != (longlong *)0x0) {
            FUN_180005310(0,_DAT_188954c98,plStack_118);
          }
          ChangeGuard_Dispose_0x60100ba(&uStack_110,0);
          BuffContainer__CheckFinishedBuffs_0x600ff52(param_1,0);
          return;
        }
        if (plStack_118 == (longlong *)0x0) {
          FUN_18048c0b0();
          break;
        }
        lVar1 = *plStack_118;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(lVar1);
        }
        uVar7 = 0;
        if (*(ushort *)(lVar1 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar7 * 0x10) == lVar5) {
              puVar6 = (undefined8 *)
                       (((longlong)
                         *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) + 0x14)
                        * 0x10 + lVar1);
              goto LAB_18066ed09;
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < *(ushort *)(lVar1 + 0x12e));
        }
        puVar6 = (undefined8 *)FUN_180445cc0(plVar3,lVar5,0);
LAB_18066ed09:
        puVar6 = (undefined8 *)(*(code *)*puVar6)(auStack_38,plVar3,puVar6[1]);
        uStack_e8 = *puVar6;
        uStack_e0 = puVar6[1];
        lVar5 = FUN_185159d80(&uStack_e8,_DAT_1889316a8);
        if ((lVar5 != 0) &&
           (cVar4 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar5,0), cVar4 == '\0'))
        {
          uStack_c8 = *param_2;
          uStack_c0 = param_2[1];
          uStack_b8 = param_2[2];
          uStack_b0 = param_2[3];
          uStack_a8 = param_2[4];
          uStack_a0 = param_2[5];
          uStack_98 = param_2[6];
          uStack_90 = param_2[7];
          uStack_88 = param_2[8];
          uStack_80 = param_2[9];
          uStack_78 = param_2[10];
          uStack_70 = param_2[0xb];
          uStack_68 = param_2[0xc];
          uStack_60 = param_2[0xd];
          uStack_58 = *(undefined4 *)(param_2 + 0xe);
          uStack_54 = *(undefined4 *)((longlong)param_2 + 0x74);
          uStack_50 = *(undefined4 *)(param_2 + 0xf);
          uStack_4c = *(undefined4 *)((longlong)param_2 + 0x7c);
          uStack_48 = param_2[0x10];
          ChangeGuard_set_modifier_0x60100af(&uStack_110,&uStack_c8,0);
          Torappu_Battle_Buff_OnBeforeTrySetHpZero_0x600feaa(lVar5,param_2,0);
          if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar4 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_2,0);
          if ((cVar4 != '\0') && (*param_3 == 0)) {
            *param_3 = lVar5;
            func_0x00018048b9e0(param_3,lVar5);
          }
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

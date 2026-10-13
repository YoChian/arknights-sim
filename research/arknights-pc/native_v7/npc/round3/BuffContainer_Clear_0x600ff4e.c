/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void BuffContainer_Clear_0x600ff4e(longlong param_1,undefined1 param_2)
{
  code *pcVar1;
  char cVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong lVar6;
  ushort uVar7;
  ushort uVar8;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined1 auStack_38 [16];
  if (DAT_188c903d0 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_188943988);
    FUN_18048bf00(&DAT_18888ee78);
    FUN_18048bf00(&DAT_18882b4e0);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_1889237f0);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c903d0 = '\x01';
  }
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x1b8);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp26_0x6000a7a(lVar5,param_1,param_2,0);
    return;
  }
  if (*(longlong *)(param_1 + 0x18) == 0) {
LAB_180664ff2:
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  plVar3 = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
  while (plVar3 != (longlong *)0x0) {
    cVar2 = FUN_180005310(0,_DAT_188959b58);
    lVar5 = _DAT_1888cfcb0;
    uVar7 = 0;
    if (cVar2 == '\0') {
      if (plVar3 != (longlong *)0x0) {
        FUN_180005310(0,_DAT_188954c98,plVar3);
      }
      if (*(longlong *)(param_1 + 0x18) == 0) goto LAB_180664ff2;
      plVar3 = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
      goto LAB_180664d21;
    }
    if (plVar3 == (longlong *)0x0) {
      FUN_18048c0b0();
      break;
    }
    lVar6 = *plVar3;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar6);
    }
    if (*(ushort *)(lVar6 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar7 * 0x10) == lVar5) {
          puVar4 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) +
                    0x14) * 0x10 + lVar6);
          goto LAB_180664c35;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(ushort *)(lVar6 + 0x12e));
    }
    puVar4 = (undefined8 *)FUN_180445cc0(plVar3,lVar5,0);
LAB_180664c35:
    puVar4 = (undefined8 *)(*(code *)*puVar4)(auStack_38,plVar3,puVar4[1]);
    uStack_58 = *puVar4;
    uStack_50 = puVar4[1];
    lVar5 = FUN_185159d80(&uStack_58,_DAT_1889316a8);
    if (lVar5 != 0) {
      BuffContainer__FinishBuff_0x600ff5a(param_1,lVar5,0,1,param_2,0);
    }
  }
  FUN_18048c0b0();
  FUN_180472d50();
LAB_180664fd2:
  FUN_18048c0b0();
LAB_180664fd7:
  FUN_18048c0b0();
LAB_180664fdc:
  FUN_18048c0b0();
LAB_180664fe1:
  FUN_18048c0b0();
  goto LAB_180664fe6;
LAB_180664d21:
  lVar5 = _DAT_188959b58;
  if (plVar3 != (longlong *)0x0) {
    lVar6 = *plVar3;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar6);
    }
    if (*(ushort *)(lVar6 + 0x12e) != 0) {
      uVar8 = uVar7;
      do {
        if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar8 * 0x10) == lVar5) {
          puVar4 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar8 * 0x10) +
                    0x14) * 0x10 + lVar6);
          goto LAB_180664d99;
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(ushort *)(lVar6 + 0x12e));
    }
    puVar4 = (undefined8 *)FUN_180445cc0(plVar3,lVar5,0);
LAB_180664d99:
    cVar2 = (*(code *)*puVar4)(plVar3,puVar4[1]);
    lVar5 = _DAT_1888cfcb0;
    if (cVar2 == '\0') {
      if (plVar3 != (longlong *)0x0) {
        FUN_180005310(0,_DAT_188954c98,plVar3);
      }
      if (*(longlong *)(param_1 + 0x18) != 0) {
        FUN_185a17130(*(longlong *)(param_1 + 0x18),_DAT_18882b4e0);
        if (*(longlong *)(param_1 + 0x20) != 0) {
          FUN_1857610f0(*(longlong *)(param_1 + 0x20),_DAT_18888ee78);
          if (*(longlong *)(param_1 + 0x28) != 0) {
            FUN_1857610f0(*(longlong *)(param_1 + 0x28),_DAT_188943988);
            return;
          }
        }
      }
      goto LAB_180664ff2;
    }
    if (plVar3 == (longlong *)0x0) goto LAB_180664fe1;
    lVar6 = *plVar3;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar6);
    }
    if (*(ushort *)(lVar6 + 0x12e) != 0) {
      uVar8 = uVar7;
      do {
        if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar8 * 0x10) == lVar5) {
          puVar4 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar8 * 0x10) +
                    0x14) * 0x10 + lVar6);
          goto LAB_180664e29;
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(ushort *)(lVar6 + 0x12e));
    }
    puVar4 = (undefined8 *)FUN_180445cc0(plVar3,lVar5,0);
LAB_180664e29:
    puVar4 = (undefined8 *)(*(code *)*puVar4)(auStack_38,plVar3);
    uStack_48 = *puVar4;
    uStack_40 = puVar4[1];
    lVar5 = FUN_185159d80(&uStack_48,_DAT_1889316a8);
    if ((lVar5 != 0) && (*(char *)(lVar5 + 0x1fb) == '\0')) {
      lVar6 = BuffContainer_get_owner_0x600ff17(param_1,0);
      if (lVar6 == 0) goto LAB_180664fdc;
      lVar6 = Torappu_Battle_Entity_get_attributes_0x6010337(lVar6,0);
      if (lVar6 == 0) goto LAB_180664fd7;
      Torappu_Battle_Attributes_RemoveModifier_0x600fb13(lVar6,lVar5,0);
      lVar6 = BuffContainer_get_pool_0x600ff1c(param_1,0);
      if (lVar6 == 0) goto LAB_180664fd2;
      FUN_185158320(lVar6,lVar5);
    }
    goto LAB_180664d21;
  }
LAB_180664fe6:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

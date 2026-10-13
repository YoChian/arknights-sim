
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_OnOtherBuffStart_0x6010480(undefined8 param_1,longlong param_2)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 *puVar7;
  longlong lVar8;
  longlong lStackX_20;
  longlong *plStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 **ppuStack_28;
  
  if (DAT_188c9090f == '\0') {
    puStack_30 = (undefined1 *)0x1806f9645;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c9090f = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined1 *)0x1806f9664;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xa18);
  if (lVar8 == 0) {
    if (param_2 != 0) {
      puStack_30 = (undefined1 *)0x1806f968d;
      cVar3 = Torappu_Battle_Buff_get_isStatusResistable_0x600fe55(param_2,0);
      if (cVar3 == '\0') {
        puStack_30 = (undefined1 *)0x1806f969b;
        lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
        if (lVar8 != 0) {
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
          lVar6 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x378);
          if (lVar6 == 0) {
            cVar3 = BuffContainer__CheckBuffsActionValid_0x600ff53(lVar8,0x24,0);
            if (cVar3 != '\0') {
              lVar6 = BuffContainer_get_context_0x600ff1a(lVar8,0);
              if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x58) != 0)) {
                FUN_185733520(*(longlong *)(lVar6 + 0x58),param_2,_DAT_18891d7d8);
                if (*(longlong *)(lVar8 + 0x18) != 0) {
                  lStackX_20 = FUN_185a17960(*(longlong *)(lVar8 + 0x18),_DAT_18882b720);
                  plStack_48 = &lStackX_20;
LAB_180673d80:
                  if (lStackX_20 != 0) {
                    cVar3 = FUN_180005310(0,_DAT_188959b58);
                    if (cVar3 == '\0') {
                      if (lStackX_20 != 0) {
                        FUN_180005310(0,_DAT_188954c98,lStackX_20);
                      }
                      goto LAB_180673e7b;
                    }
                    if (lStackX_20 != 0) goto code_r0x000180673db8;
                    FUN_18048c0b0();
                  }
                  FUN_18048c0b0();
                  FUN_180472d50();
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
              }
LAB_180673eeb:
              FUN_18048c0b0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
          }
          else {
            XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar6,lVar8,param_2,0);
          }
          return;
        }
      }
      else {
        puStack_30 = (undefined1 *)0x1806f96bd;
        lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
        if (lVar8 != 0) {
          if (cRam0000000188c90409 == '\0') {
            FUN_18048bf00(&DAT_1888d5250);
            FUN_18048bf00(&DAT_18891d598);
            FUN_18048bf00(&DAT_18891d7d8);
            FUN_18048bf00(&DAT_18882b720);
            FUN_18048bf00(&DAT_188954c98);
            FUN_18048bf00(&DAT_1888cfcb0);
            FUN_18048bf00(&DAT_188959b58);
            FUN_18048bf00(&DAT_1889316a8);
            cRam0000000188c90409 = '\x01';
          }
          uStack_40 = 0;
          uStack_38 = 0;
          lVar6 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x380);
          if (lVar6 == 0) {
            cVar3 = BuffContainer__CheckBuffsActionValid_0x600ff53(lVar8,0x24,0);
            if ((cVar3 != '\0') ||
               (cVar3 = BuffContainer__CheckBuffsActionValid_0x600ff53(lVar8,0x2d,0), cVar3 != '\0')
               ) {
              lVar6 = BuffContainer_get_context_0x600ff1a(lVar8,0);
              if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x58) != 0)) {
                FUN_185733520(*(longlong *)(lVar6 + 0x58),param_2,_DAT_18891d7d8);
                if (*(longlong *)(lVar8 + 0x18) != 0) {
                  lStackX_20 = FUN_185a17960(*(longlong *)(lVar8 + 0x18),_DAT_18882b720);
                  plStack_48 = &lStackX_20;
code_r0x000180674040:
                  if (lStackX_20 != 0) {
                    cVar3 = FUN_180005310(0,_DAT_188959b58);
                    if (cVar3 == '\0') {
                      if (lStackX_20 != 0) {
                        FUN_180005310(0,_DAT_188954c98,lStackX_20);
                      }
                      goto code_r0x00018067416f;
                    }
                    if (lStackX_20 != 0) goto code_r0x000180674078;
                    FUN_18048c0b0();
                  }
                  FUN_18048c0b0();
                  FUN_180472d50();
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
              }
code_r0x0001806741df:
              FUN_18048c0b0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
          }
          else {
            XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar6,lVar8,param_2,0);
          }
          return;
        }
      }
    }
    puStack_30 = (undefined1 *)0x1806f96f7;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  plStack_48 = *(longlong **)(*(longlong *)(lVar8 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  ppuStack_28 = &plStack_48;
  FUN_185ca7f50(plStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar8 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar6 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar6 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar6,uVar1,param_1,0);
        FUN_183cf8c20(lVar6,uVar1,param_2,0);
        iVar5 = FUN_183f22380(uVar1,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar8 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar4 + -1,0);
          goto code_r0x0001832d231b;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
code_r0x000180674078:
  puVar7 = (undefined8 *)FUN_18000f5e0(&puStack_30,0,_DAT_1888cfcb0);
  uStack_40 = *puVar7;
  uStack_38 = puVar7[1];
  lVar6 = FUN_185159d80(&uStack_40,_DAT_1889316a8);
  if (((lVar6 != 0) &&
      (cVar3 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar6,0), cVar3 == '\0')) &&
     (lVar6 != param_2)) {
    if ((param_2 == 0) || (*(char *)(param_2 + 0x1fa) == '\0')) {
      Torappu_Battle_Buff_OnOtherBuffStart_0x600fe9d(lVar6,0);
      if ((param_2 == 0) || (*(char *)(param_2 + 0x1fa) == '\0')) {
        FUN_180685830(lVar6,0);
        goto code_r0x000180674040;
      }
      if (lStackX_20 != 0) {
        FUN_180005310(0,_DAT_188954c98,lStackX_20);
      }
    }
    else if (lStackX_20 != 0) {
      FUN_180005310(0,_DAT_188954c98,lStackX_20);
    }
code_r0x00018067416f:
    lVar6 = BuffContainer_get_context_0x600ff1a(lVar8,0);
    if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x58) != 0)) {
      FUN_185733450(*(longlong *)(lVar6 + 0x58),_DAT_18891d598);
      BuffContainer__CheckFinishedBuffs_0x600ff52(lVar8,0);
      return;
    }
    goto code_r0x0001806741df;
  }
  goto code_r0x000180674040;
code_r0x000180673db8:
  puVar7 = (undefined8 *)FUN_18000f5e0(&puStack_30,0,_DAT_1888cfcb0);
  uStack_40 = *puVar7;
  uStack_38 = puVar7[1];
  lVar6 = FUN_185159d80(&uStack_40,_DAT_1889316a8);
  if (((lVar6 != 0) &&
      (cVar3 = Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(lVar6,0), cVar3 == '\0')) &&
     (lVar6 != param_2)) {
    if ((param_2 != 0) && (*(char *)(param_2 + 0x1fa) != '\0')) {
      if (lStackX_20 != 0) {
        FUN_180005310(0,_DAT_188954c98,lStackX_20);
      }
LAB_180673e7b:
      lVar6 = BuffContainer_get_context_0x600ff1a(lVar8,0);
      if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x58) != 0)) {
        FUN_185733450(*(longlong *)(lVar6 + 0x58),_DAT_18891d598);
        BuffContainer__CheckFinishedBuffs_0x600ff52(lVar8,0);
        return;
      }
      goto LAB_180673eeb;
    }
    Torappu_Battle_Buff_OnOtherBuffStart_0x600fe9d(lVar6,0);
  }
  goto LAB_180673d80;
}


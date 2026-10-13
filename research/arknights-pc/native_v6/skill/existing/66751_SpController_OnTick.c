
/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SpController_OnTick_0x60104c0(longlong param_1,undefined8 param_2)

{
  longlong lVar1;
  longlong *plVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined *puVar10;
  undefined8 uStack_48;
  undefined *apuStack_40 [2];
  undefined *puStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c90947 == '\0') {
    puStack_30 = (undefined *)0x18070a1e5;
    FUN_18048bf00(&DAT_18885a700);
    puStack_30 = (undefined *)0x18070a1f1;
    FUN_18048bf00(&DAT_188874308);
    DAT_188c90947 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x80);
  if (lVar1 == 0) {
    if ((*(byte *)(param_1 + 0x10) & 1) != 0) {
      if (*(longlong *)(param_1 + 0x40) != 0) {
        puStack_30 = (undefined *)0x18070a234;
        cVar5 = Torappu_PeriodicTimer_get_isValid_0x600656e(*(longlong *)(param_1 + 0x40),0);
        if (cVar5 == '\0') {
          return;
        }
        if (*(longlong *)(param_1 + 0x18) != 0) {
          puStack_30 = (undefined *)0x18070a250;
          cVar5 = Torappu_Battle_Entity_get_spRecoverStopped_0x60103c2
                            (*(longlong *)(param_1 + 0x18),0);
          if (cVar5 != '\0') {
            return;
          }
          puStack_30 = (undefined *)0x18070a262;
          cVar5 = SpController_get_isFull_0x60104b0(param_1,0);
          if (cVar5 != '\0') {
            return;
          }
          if (*(longlong *)(param_1 + 0x40) != 0) {
            puStack_30 = (undefined *)0x18070a27a;
            iVar6 = Torappu_PrecisePeriodicTimer_UpdateMultiple_0x6006584
                              (*(longlong *)(param_1 + 0x40),param_2);
            if (iVar6 < 1) {
              return;
            }
            if (*(longlong *)(param_1 + 0x40) != 0) {
              puStack_30 = (undefined *)0x18070a293;
              Torappu_PrecisePeriodicTimer_NextMultiple_0x6006585
                        (*(longlong *)(param_1 + 0x40),iVar6);
              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                puStack_30 = (undefined *)0x18070a2a8;
                func_0x00018048c140();
              }
              puStack_30 = (undefined *)0x18070a2b1;
              uVar8 = func_0x0001866fdac0(iVar6,0);
              if (cRam0000000188c90948 == '\0') {
                apuStack_40[0] = &UNK_18070a85e;
                FUN_18048bf00(&DAT_18885a700,uVar8,0,0);
                apuStack_40[0] = &UNK_18070a86a;
                FUN_18048bf00(&DAT_188874308);
                cRam0000000188c90948 = '\x01';
              }
              lVar1 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x88);
              if (lVar1 != 0) {
                apuStack_40[0] = &UNK_18070a916;
                XLua_DelegateBridge___Gen_Delegate_Imp3340_0x600176c(lVar1,param_1,uVar8,0);
                return;
              }
              if (*(longlong *)(param_1 + 0x18) != 0) {
                apuStack_40[0] = &UNK_18070a8a4;
                cVar5 = Torappu_Battle_Entity_get_spRecoverStopped_0x60103c2
                                  (*(longlong *)(param_1 + 0x18),0);
                if (cVar5 != '\0') {
                  return;
                }
                plVar2 = *(longlong **)(param_1 + 0x18);
                if (plVar2 != (longlong *)0x0) {
                  apuStack_40[0] = &UNK_18070a8bb;
                  uVar9 = Torappu_Battle_Entity_get_sp_0x6010388(plVar2,0);
                  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                    apuStack_40[0] = &UNK_18070a8d3;
                    func_0x00018048c140();
                  }
                  apuStack_40[0] = &UNK_18070a8e1;
                  puVar10 = (undefined *)func_0x000184624db0(uVar9,uVar8,0);
                  if (cRam0000000188c90820 == '\0') {
                    puStack_30 = &UNK_180709df5;
                    FUN_18048bf00(&DAT_188841368);
                    cRam0000000188c90820 = '\x01';
                  }
                  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
                    puStack_30 = &UNK_180709e14;
                    func_0x00018048c140(_DAT_188841368);
                  }
                  lVar1 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x298);
                  if (lVar1 == 0) {
                    if (DAT_188ccc7f0 != '\0') {
                      puStack_30 = &UNK_180709e3e;
                      func_0x000180446d00(*plVar2);
                    }
                    /* WARNING: Could not recover jumptable at 0x000180709e62. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                    (**(code **)(*plVar2 + 0x850))
                              (plVar2,puVar10,0,*(undefined8 *)(*plVar2 + 0x858));
                    return;
                  }
                  if (cRam0000000188caf41c == '\0') {
                    FUN_18048bf00(&DAT_18885a700,plVar2,puVar10,0);
                    cRam0000000188caf41c = '\x01';
                  }
                  if (*(longlong *)(lVar1 + 0x18) == 0) {
                    FUN_18048c0b0();
                    pcVar4 = (code *)swi(3);
                    (*pcVar4)();
                    return;
                  }
                  uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
                  puStack_30 = (undefined *)0x0;
                  puStack_28 = &stack0x00000008;
                  puStack_20 = &uStack_48;
                  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
                  if (*(longlong *)(lVar1 + 0x18) != 0) {
                    uVar8 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
                    iVar6 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar1 + 0x38),
                                          *(undefined4 *)(lVar1 + 0x14),0);
                    if (*(longlong *)(lVar1 + 0x18) != 0) {
                      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
                      if (lVar3 == 0) {
                        FUN_18048c0b0();
                      }
                      else {
                        FUN_183cf8c20(lVar3,uVar8,plVar2,0);
                        apuStack_40[0] = puVar10;
                        uVar9 = func_0x00018048b9c0(_DAT_18885a700,apuStack_40);
                        FUN_183cfbf40(lVar3,uVar8,uVar9,0);
                        iVar7 = FUN_183f22380(uVar8,2,0,iVar6,0);
                        if (iVar7 == 0) {
code_r0x0001833f996e:
                          FUN_183f22fd0(uVar8,iVar6 + -1,0);
                          return;
                        }
                        if (*(longlong *)(lVar1 + 0x18) != 0) {
                          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
                          goto code_r0x0001833f996e;
                        }
                      }
                      FUN_18048c0b0();
                    }
                    FUN_18048c0b0();
                  }
                  FUN_18048c0b0();
                  FUN_180472d50();
                  pcVar4 = (code *)swi(3);
                  (*pcVar4)();
                  return;
                }
              }
              apuStack_40[0] = &UNK_18070a92b;
              FUN_18048c0b0();
              pcVar4 = (code *)swi(3);
              (*pcVar4)();
              return;
            }
          }
        }
      }
      puStack_30 = (undefined *)0x18070a2ea;
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
  }
  else {
    puStack_30 = (undefined *)0x18070a2da;
    XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b(lVar1,param_1,param_2,0);
  }
  return;
}



/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SpController__RecoverMp_0x60104c1(longlong param_1,undefined8 param_2,char param_3)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined *puStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c90948 == '\0') {
    auStack_40[0] = 0x18070a85e;
    FUN_18048bf00(&DAT_18885a700);
    auStack_40[0] = 0x18070a86a;
    FUN_18048bf00(&DAT_188874308);
    DAT_188c90948 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x88);
  if (lVar1 != 0) {
    auStack_40[0] = 0x18070a916;
    XLua_DelegateBridge___Gen_Delegate_Imp3340_0x600176c(lVar1,param_1,param_2,param_3);
    return;
  }
  if (param_3 == '\0') {
    if (*(longlong *)(param_1 + 0x18) == 0) goto LAB_18070a926;
    auStack_40[0] = 0x18070a8a4;
    cVar6 = Torappu_Battle_Entity_get_spRecoverStopped_0x60103c2(*(longlong *)(param_1 + 0x18),0);
    if (cVar6 != '\0') {
      return;
    }
  }
  plVar2 = *(longlong **)(param_1 + 0x18);
  if (plVar2 == (longlong *)0x0) {
LAB_18070a926:
    auStack_40[0] = 0x18070a92b;
    FUN_18048c0b0();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  auStack_40[0] = 0x18070a8bb;
  uVar9 = Torappu_Battle_Entity_get_sp_0x6010388(plVar2,0);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    auStack_40[0] = 0x18070a8d3;
    func_0x00018048c140();
  }
  auStack_40[0] = 0x18070a8e1;
  uVar9 = func_0x000184624db0(uVar9,param_2,0);
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
    (**(code **)(*plVar2 + 0x850))(plVar2,uVar9,0,*(undefined8 *)(*plVar2 + 0x858));
    return;
  }
  if (cRam0000000188caf41c == '\0') {
    FUN_18048bf00(&DAT_18885a700,plVar2,uVar9,0);
    cRam0000000188caf41c = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  puStack_30 = (undefined *)0x0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar4 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar4 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar4,uVar3,plVar2,0);
        auStack_40[0] = uVar9;
        uVar9 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
        FUN_183cfbf40(lVar4,uVar3,uVar9,0);
        iVar8 = FUN_183f22380(uVar3,2,0,iVar7,0);
        if (iVar8 == 0) {
code_r0x0001833f996e:
          FUN_183f22fd0(uVar3,iVar7 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
          goto code_r0x0001833f996e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}


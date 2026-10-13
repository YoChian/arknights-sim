
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BornState_OnEnter_0x6012b64(longlong param_1,undefined4 param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c92904 == '\0') {
    uStack_40 = 0x180a884e4;
    FUN_18048bf00(&DAT_188884640);
    uStack_40 = 0x180a884f0;
    FUN_18048bf00(&DAT_18885a700);
    uStack_40 = 0x180a884fc;
    FUN_18048bf00(&DAT_1888c3c38);
    uStack_40 = 0x180a88508;
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c92904 = '\x01';
  }
  lVar6 = **(longlong **)(_DAT_188884640 + 0xb8);
  if (lVar6 == 0) {
    uStack_40 = 0x180a88538;
    BornState__PlayAnimation_0x6012b67(param_1,0);
    uStack_40 = 0x180a88547;
    lVar6 = FUN_18536e540(param_1,_DAT_188957b60);
    if (lVar6 == 0) {
LAB_180a88610:
      uStack_40 = 0x180a88615;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_40 = 0x180a8855a;
    uVar8 = Torappu_Battle_Enemy_get_delayToBorn_0x6012a5b(lVar6,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      uStack_40 = 0x180a88572;
      func_0x00018048c140();
    }
    uStack_40 = 0x180a88580;
    cVar3 = func_0x0001866e4c50(uVar8,0,0);
    if (cVar3 == '\0') {
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        uStack_40 = 0x180a88599;
        func_0x00018048c140();
      }
      uStack_40 = 0x180a885a2;
      uVar7 = func_0x0001866fdac0(0,0);
    }
    else {
      uStack_40 = 0x180a885c5;
      lVar6 = FUN_18536e540(param_1,_DAT_188957b60);
      if (lVar6 == 0) goto LAB_180a88610;
      uStack_40 = 0x180a885d4;
      uVar8 = Torappu_Battle_Enemy_get_delayToBorn_0x6012a5b(lVar6,0);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        uStack_40 = 0x180a885ec;
        func_0x00018048c140();
      }
      uStack_40 = 0x180a885f6;
      uVar7 = func_0x0001866fdad0(uVar8,0);
    }
    *(undefined8 *)(param_1 + 0x18) = uVar7;
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0(lVar6,param_1,param_2,0);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar7 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar7,param_1,0);
        FUN_183f25080(uVar7,param_2,0);
        iVar5 = FUN_183f22380(uVar7,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001834c0f1e:
          FUN_183f22fd0(uVar7,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001834c0f1e;
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
}


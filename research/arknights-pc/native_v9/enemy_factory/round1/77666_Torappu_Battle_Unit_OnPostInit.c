
/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Unit_OnPostInit_0x6012f63(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  longlong *plVar8;
  undefined8 uStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c92be4 == '\0') {
    puStack_30 = (undefined *)0x180acae3e;
    FUN_18048bf00(&DAT_188932ce8);
    puStack_30 = (undefined *)0x180acae4a;
    FUN_18048bf00(&DAT_188805040);
    DAT_188c92be4 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x350);
  if (lVar1 != 0) {
    if (*(longlong *)(lVar1 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    puStack_30 = (undefined *)0x0;
    puStack_28 = (undefined8 *)&stack0x00000008;
    puStack_20 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      uVar7 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
      iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
        if (lVar2 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar2,uVar7,param_1,0);
          auStack_48[0] = 0;
          iVar6 = FUN_183f22380(uVar7,1,0,iVar5);
          if (iVar6 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar7,iVar5 + -1,0);
            return;
          }
          if (*(longlong *)(lVar1 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  puStack_30 = (undefined *)0x180acae7e;
  func_0x00018050cf60(param_1,0);
  if (DAT_188ccc7f0 != '\0') {
    puStack_30 = (undefined *)0x180acae8f;
    func_0x000180446d00(*param_1);
  }
  puStack_30 = (undefined *)0x180acaea5;
  uVar7 = (**(code **)(*param_1 + 0xb60))(param_1,*(undefined8 *)(*param_1 + 0xb68));
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    puStack_30 = (undefined *)0x180acaebd;
    func_0x00018048c140();
  }
  puStack_30 = (undefined *)0x180acaeca;
  cVar4 = FUN_186b63a70(uVar7,0,0);
  if (cVar4 != '\0') {
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined *)0x180acaedf;
      func_0x000180446d00(*param_1);
    }
    puStack_30 = (undefined *)0x180acaef5;
    plVar8 = (longlong *)(**(code **)(*param_1 + 0xb60))(param_1,*(undefined8 *)(*param_1 + 0xb68));
    if (plVar8 == (longlong *)0x0) {
      puStack_30 = (undefined *)0x180acaf51;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined *)0x180acaf0e;
      func_0x000180446d00(*plVar8);
    }
    puStack_30 = (undefined *)0x180acaf25;
    (**(code **)(*plVar8 + 0x330))(plVar8,*(undefined8 *)(*plVar8 + 0x338));
  }
  if (cRam0000000188c90812 == '\0') {
    puStack_30 = &UNK_180709d65;
    FUN_18048bf00(&DAT_188841368,1,0);
    cRam0000000188c90812 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = &UNK_180709d84;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x228);
  if (lVar1 == 0) {
    *(undefined1 *)((longlong)param_1 + 0x174) = 1;
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar7 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar7,param_1,0);
        FUN_183f22430(uVar7,1,0);
        iVar6 = FUN_183f22380(uVar7,2,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833006e0:
          FUN_183f22fd0(uVar7,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833006e0;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


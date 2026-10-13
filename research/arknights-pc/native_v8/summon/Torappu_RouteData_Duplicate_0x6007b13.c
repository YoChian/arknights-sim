
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_RouteData_Duplicate_0x6007b13(longlong param_1)

{
  undefined4 uVar1;
  longlong *plVar2;
  code *pcVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong lVar7;
  uint uVar8;
  longlong lVar9;
  undefined8 uStackX_18;
  undefined8 uStackX_20;
  undefined8 auStack_48 [2];
  
  if (DAT_188ca5be5 == '\0') {
    FUN_18048bf00(&DAT_188952c50);
    FUN_18048bf00(&DAT_18881ea78);
    DAT_188ca5be5 = '\x01';
  }
  lVar4 = func_0x00018045cfe0(_DAT_18881ea78);
  if (lVar4 == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    lVar4 = (*pcVar3)();
    return lVar4;
  }
  *(undefined1 *)(lVar4 + 0x40) = 1;
  func_0x00018050cf60(lVar4,0);
  uVar8 = 0;
  *(undefined4 *)(lVar4 + 0x10) = *(undefined4 *)(param_1 + 0x10);
  uStackX_18 = 0;
  func_0x000180518de0(&uStackX_18,*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),0)
  ;
  *(undefined8 *)(lVar4 + 0x14) = uStackX_18;
  uStackX_20 = 0;
  func_0x000180518de0(&uStackX_20,*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20),0)
  ;
  *(undefined8 *)(lVar4 + 0x1c) = uStackX_20;
  uVar1 = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(lVar4 + 0x28) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(lVar4 + 0x24) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(lVar4 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(lVar4 + 0x2c) = uVar1;
  *(undefined1 *)(lVar4 + 0x40) = *(undefined1 *)(param_1 + 0x40);
  *(undefined1 *)(lVar4 + 0x41) = *(undefined1 *)(param_1 + 0x41);
  *(undefined1 *)(lVar4 + 0x42) = *(undefined1 *)(param_1 + 0x42);
  *(undefined1 *)(lVar4 + 0x43) = *(undefined1 *)(param_1 + 0x43);
  if (*(longlong *)(param_1 + 0x38) == 0) {
    return lVar4;
  }
  uVar5 = func_0x00018048ba50(_DAT_188952c50,*(undefined4 *)(*(longlong *)(param_1 + 0x38) + 0x18));
  *(undefined8 *)(lVar4 + 0x38) = uVar5;
  func_0x00018048b9e0(lVar4 + 0x38,uVar5);
  lVar7 = *(longlong *)(param_1 + 0x38);
  if (lVar7 != 0) {
    lVar9 = 0x20;
    do {
      if (*(int *)(lVar7 + 0x18) <= (int)uVar8) {
        return lVar4;
      }
      lVar7 = *(longlong *)(param_1 + 0x38);
      plVar2 = *(longlong **)(lVar4 + 0x38);
      if (lVar7 == 0) break;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) {
LAB_18242dbf0:
        FUN_18048c0a0();
        pcVar3 = (code *)swi(3);
        lVar4 = (*pcVar3)();
        return lVar4;
      }
      lVar7 = *(longlong *)(lVar9 + lVar7);
      if (lVar7 == 0) break;
      if (DAT_188ca5be6 == '\0') {
        FUN_18048bf00(&DAT_188824b48);
        DAT_188ca5be6 = '\x01';
      }
      lVar6 = func_0x00018045cfe0(_DAT_188824b48);
      if (lVar6 == 0) {
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        lVar4 = (*pcVar3)();
        return lVar4;
      }
      func_0x00018050cf60(lVar6,0);
      *(undefined4 *)(lVar6 + 0x10) = *(undefined4 *)(lVar7 + 0x10);
      *(undefined4 *)(lVar6 + 0x14) = *(undefined4 *)(lVar7 + 0x14);
      auStack_48[0] = 0;
      func_0x000180518de0(auStack_48,*(undefined4 *)(lVar7 + 0x18),*(undefined4 *)(lVar7 + 0x1c),0);
      *(undefined8 *)(lVar6 + 0x18) = auStack_48[0];
      uVar1 = *(undefined4 *)(lVar7 + 0x20);
      *(undefined4 *)(lVar6 + 0x24) = *(undefined4 *)(lVar7 + 0x24);
      *(undefined4 *)(lVar6 + 0x20) = uVar1;
      *(undefined1 *)(lVar6 + 0x28) = *(undefined1 *)(lVar7 + 0x28);
      *(undefined4 *)(lVar6 + 0x2c) = *(undefined4 *)(lVar7 + 0x2c);
      if (plVar2 == (longlong *)0x0) break;
      lVar7 = func_0x00018048b9f0(lVar6,*(undefined8 *)(*plVar2 + 0x40));
      if (lVar7 == 0) {
        uVar5 = func_0x00018048bc50();
        FUN_18048c070(uVar5,0);
        pcVar3 = (code *)swi(3);
        lVar4 = (*pcVar3)();
        return lVar4;
      }
      if (*(uint *)(plVar2 + 3) <= uVar8) goto LAB_18242dbf0;
      *(longlong *)(lVar9 + (longlong)plVar2) = lVar6;
      func_0x00018048b9e0(plVar2 + (longlong)(int)uVar8 + 4);
      lVar7 = *(longlong *)(param_1 + 0x38);
      uVar8 = uVar8 + 1;
      lVar9 = lVar9 + 8;
    } while (lVar7 != 0);
  }
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  lVar4 = (*pcVar3)();
  return lVar4;
}



/* WARNING: Removing unreachable block (ram,0x0001832f923c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_AbilityStandard_GeneratePurposeMask_0x600f6ce(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  uint auStackX_20 [2];
  undefined8 auStack_50 [2];
  undefined8 uStack_40;
  undefined1 *puStack_38;
  undefined8 *puStack_30;
  
  if (DAT_188c8fd4c == '\0') {
    puStack_30 = (undefined8 *)0x1805d064e;
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd4c = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x1c0);
  if (lVar1 == 0) {
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined8 *)0x1805d0688;
      func_0x000180446d00(*param_1);
    }
    puStack_30 = (undefined8 *)0x1805d06a3;
    uVar8 = (**(code **)(*param_1 + 0x5f0))(param_1,4,*(undefined8 *)(*param_1 + 0x5f8));
    puStack_30 = (undefined8 *)0x1805d06ad;
    uVar4 = Torappu_Battle_Action_ActionUtil_GeneratePurposeMask_0x6018907(uVar8,0);
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined8 *)0x1805d06c0;
      func_0x000180446d00(*param_1);
    }
    puStack_30 = (undefined8 *)0x1805d06dc;
    uVar8 = (**(code **)(*param_1 + 0x420))(param_1,0,0,*(undefined8 *)(*param_1 + 0x428));
    puStack_30 = (undefined8 *)0x1805d06e6;
    uVar5 = Torappu_Battle_Action_ActionUtil_GeneratePurposeMask_0x6018907(uVar8,0);
    return (ulonglong)(uVar5 | uVar4);
  }
  if (cRam0000000188cafbb4 == '\0') {
    FUN_18048bf00(0x188821b98);
    cRam0000000188cafbb4 = '\x01';
  }
  auStackX_20[0] = 0;
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832f928b:
    FUN_18048c0b0();
code_r0x0001832f9291:
    FUN_18048c0b0();
  }
  else {
    auStack_50[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    uStack_40 = 0;
    puStack_38 = &stack0x00000008;
    puStack_30 = auStack_50;
    FUN_185ca7f50(auStack_50[0],&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832f929b;
    uVar8 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) goto code_r0x0001832f928b;
      FUN_183cf8c20(lVar2,uVar8,param_1,0);
      iVar7 = FUN_183f22380(uVar8,1,1,iVar6,0);
      if (iVar7 == 0) {
code_r0x0001832f91f6:
        FUN_184566d40(lVar2,uVar8,iVar6 + 1,auStackX_20,uRam0000000188821b98);
        FUN_183f22fd0(uVar8,iVar6 + -1,0);
        return (ulonglong)auStackX_20[0];
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
        goto code_r0x0001832f91f6;
      }
      goto code_r0x0001832f9291;
    }
  }
  FUN_18048c0b0();
code_r0x0001832f929b:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  uVar9 = (*pcVar3)();
  return uVar9;
}


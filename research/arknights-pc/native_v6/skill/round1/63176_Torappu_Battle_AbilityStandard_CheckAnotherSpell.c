
/* WARNING: Removing unreachable block (ram,0x000183250277) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_AbilityStandard_CheckAnotherSpell_0x600f6c9
                    (undefined8 param_1,undefined4 param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  ulonglong uVar8;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c8fd47 == '\0') {
    uStack_30 = 0x1805cf014;
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd47 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x198);
  if (lVar1 == 0) {
    return _DAT_188974cb0 & 0xffffffffffffff00;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832502c9:
    FUN_18048c0b0();
code_r0x0001832502cf:
    FUN_18048c0b0();
  }
  else {
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832502d9;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x0001832502c9;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      FUN_183f25080(uVar2,param_2,0);
      iVar7 = FUN_183f22380(uVar2,2,1,iVar6,0);
      if (iVar7 == 0) {
code_r0x00018325024a:
        bVar5 = FUN_183f23100(uVar2,iVar6 + 1,0);
        FUN_183f22fd0(uVar2,iVar6 + -1,0);
        return (ulonglong)bVar5;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
        goto code_r0x00018325024a;
      }
      goto code_r0x0001832502cf;
    }
  }
  FUN_18048c0b0();
code_r0x0001832502d9:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  uVar8 = (*pcVar4)();
  return uVar8;
}


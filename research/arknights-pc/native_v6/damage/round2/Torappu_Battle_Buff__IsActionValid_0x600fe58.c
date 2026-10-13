/* WARNING: Removing unreachable block (ram,0x000183324785) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong Torappu_Battle_Buff__IsActionValid_0x600fe58(longlong param_1,undefined4 param_2)
{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  undefined4 uStack_44;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  if (DAT_188c902dd == '\0') {
    uStack_30 = 0x18068c084;
    FUN_18048bf00(&DAT_18895c250);
    uStack_30 = 0x18068c090;
    FUN_18048bf00(&DAT_188966e58);
    uStack_30 = 0x18068c09c;
    FUN_18048bf00(&DAT_188871398);
    DAT_188c902dd = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    uStack_30 = 0x18068c0bb;
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x1f8);
  if (lVar1 == 0) {
    lVar1 = *(longlong *)(param_1 + 0xb0);
    uStack_30 = 0x18068c0ea;
    uVar6 = func_0x0001844dc660(param_2,_DAT_188871398);
    if (lVar1 == 0) {
      uStack_30 = 0x18068c138;
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      uVar9 = (*pcVar4)();
      return uVar9;
    }
    if (*(uint *)(lVar1 + 0x18) <= uVar6) {
      uStack_30 = 0x18068c132;
      FUN_18048c0a0();
      pcVar4 = (code *)swi(3);
      uVar9 = (*pcVar4)();
      return uVar9;
    }
    uStack_30 = 0x18068c108;
    uVar9 = FUN_1844acab0(*(undefined8 *)(lVar1 + 0x20 + (longlong)(int)uVar6 * 8),_DAT_188966e58);
    return uVar9 ^ 1;
  }
  if (cRam0000000188cafca7 == '\0') {
    FUN_18048bf00(0x1888d56d0,param_1,param_2,0);
    cRam0000000188cafca7 = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001833247dc:
    FUN_18048c0b0();
code_r0x0001833247e2:
    FUN_18048c0b0();
  }
  else {
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001833247ec;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x0001833247dc;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      uStack_44 = param_2;
      uVar10 = func_0x00018048b9c0(uRam00000001888d56d0,&uStack_44);
      FUN_183cfbf40(lVar3,uVar2,uVar10,0);
      iVar8 = FUN_183f22380(uVar2,2,1,iVar7,0);
      if (iVar8 == 0) {
code_r0x000183324758:
        bVar5 = FUN_183f23100(uVar2,iVar7 + 1,0);
        FUN_183f22fd0(uVar2,iVar7 + -1,0);
        return (ulonglong)bVar5;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
        goto code_r0x000183324758;
      }
      goto code_r0x0001833247e2;
    }
  }
  FUN_18048c0b0();
code_r0x0001833247ec:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  uVar9 = (*pcVar4)();
  return uVar9;
}

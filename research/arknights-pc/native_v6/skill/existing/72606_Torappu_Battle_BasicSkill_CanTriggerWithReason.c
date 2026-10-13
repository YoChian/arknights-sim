
/* WARNING: Removing unreachable block (ram,0x000183385615) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1
Torappu_Battle_BasicSkill_CanTriggerWithReason_0x6011b9f(undefined8 param_1,undefined4 param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  undefined4 uStack_44;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c91c13 == '\0') {
    uStack_30 = 0x180959244;
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c13 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0xf8);
  if (lVar1 == 0) {
    return 1;
  }
  if (cRam0000000188cafed1 == '\0') {
    FUN_18048bf00(0x188809538,param_1,param_2,0);
    cRam0000000188cafed1 = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x00018338566c:
    FUN_18048c0b0();
code_r0x000183385672:
    FUN_18048c0b0();
  }
  else {
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x00018338567c;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x00018338566c;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      uStack_44 = param_2;
      uVar8 = func_0x00018048b9c0(uRam0000000188809538,&uStack_44);
      FUN_183cfbf40(lVar3,uVar2,uVar8,0);
      iVar7 = FUN_183f22380(uVar2,2,1,iVar6,0);
      if (iVar7 == 0) {
code_r0x0001833855e8:
        uVar5 = FUN_183f23100(uVar2,iVar6 + 1,0);
        FUN_183f22fd0(uVar2,iVar6 + -1,0);
        return uVar5;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
        goto code_r0x0001833855e8;
      }
      goto code_r0x000183385672;
    }
  }
  FUN_18048c0b0();
code_r0x00018338567c:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  uVar5 = (*pcVar4)();
  return uVar5;
}


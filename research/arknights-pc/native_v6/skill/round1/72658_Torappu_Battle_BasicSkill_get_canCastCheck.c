
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_BasicSkill_get_canCastCheck_0x6011bd3(undefined8 param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  ulonglong uVar8;
  char acStackX_8 [24];
  byte bStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  char *pcStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c91c47 == '\0') {
    pcStack_30 = (char *)0x18095f33e;
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c47 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x298);
  if (lVar1 == 0) {
    pcStack_30 = (char *)0x18095f369;
    uVar8 = Torappu_Battle_BasicSkill_get_isInChant_0x6011bd0(param_1,0);
    return uVar8 ^ 1;
  }
  bStackX_20 = 0;
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    uStack_38 = 0;
    pcStack_30 = acStackX_8;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],acStackX_8,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      iVar7 = FUN_183f22380(uVar2,1,1,iVar6,0);
      if (iVar7 == 0) {
code_r0x0001832b39f4:
        bVar5 = FUN_183f23100(uVar2,iVar6 + 1,0);
        FUN_183f22fd0(uVar2,iVar6 + -1,0);
        if (acStackX_8[0] != '\0') {
          bStackX_20 = bVar5;
          func_0x000185ca7ff0(auStack_48[0],0);
        }
        return (ulonglong)bVar5;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  uVar8 = (*pcVar4)();
  return uVar8;
}


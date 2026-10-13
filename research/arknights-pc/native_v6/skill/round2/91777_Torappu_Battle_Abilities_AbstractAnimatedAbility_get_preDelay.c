
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 Torappu_Battle_Abilities_AbstractAnimatedAbility_get_preDelay_0x6016682(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_40;
  char *pcStack_38;
  undefined8 *puStack_30;
  
  if (DAT_188c956c7 == '\0') {
    puStack_30 = (undefined8 *)0x180f014fe;
    FUN_18048bf00(&DAT_1887f76b0);
    DAT_188c956c7 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0x70);
  if (lVar1 == 0) {
    return *(undefined8 *)(param_1 + 0x1a8);
  }
  if (cRam0000000188cafb95 == '\0') {
    FUN_18048bf00(0x18883f608);
    cRam0000000188cafb95 = '\x01';
  }
  uStack_58 = 0;
  uStack_50 = 0;
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832f4dd5:
    FUN_18048c0b0();
code_r0x0001832f4ddb:
    FUN_18048c0b0();
  }
  else {
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    uStack_40 = 0;
    pcStack_38 = acStackX_8;
    puStack_30 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,acStackX_8,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832f4de5;
    uVar6 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) goto code_r0x0001832f4dd5;
      FUN_183cf8c20(lVar2,uVar6,param_1,0);
      iVar5 = FUN_183f22380(uVar6,1,1,iVar4,0);
      if (iVar5 == 0) {
code_r0x0001832f4d3c:
        FUN_184565cb0(lVar2,uVar6,iVar4 + 1,&uStack_58,uRam000000018883f608);
        FUN_183f22fd0(uVar6,iVar4 + -1,0);
        uVar6 = uStack_58;
        uStack_50 = uStack_58;
        if (acStackX_8[0] != '\0') {
          func_0x000185ca7ff0(uStackX_20,0);
        }
        return uVar6;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar4 + -1,0);
        goto code_r0x0001832f4d3c;
      }
      goto code_r0x0001832f4ddb;
    }
  }
  FUN_18048c0b0();
code_r0x0001832f4de5:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  uVar6 = (*pcVar3)();
  return uVar6;
}


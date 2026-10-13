
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 Torappu_Battle_AbilityStandard_CheckFinished_0x600f6ca(longlong param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  char acStackX_8 [24];
  undefined1 uStackX_20;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  char *pcStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c8fd48 == '\0') {
    uStack_40 = 0x1805cf12e;
    FUN_18048bf00(&DAT_188974cb0);
    uStack_40 = 0x1805cf13a;
    FUN_18048bf00(&DAT_18896b108);
    DAT_188c8fd48 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x1a0);
  if (lVar1 == 0) {
    if (DAT_188c8fcd3 == '\0') {
      uStack_40 = 0x1805cf173;
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcd3 = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xc0);
    if (lVar1 == 0) {
      cVar5 = *(char *)(param_1 + 0x60);
    }
    else {
      uStack_40 = 0x1805cf1a5;
      cVar5 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
    }
    if (cVar5 != '\0') {
      uStack_40 = 0x1805cf1ca;
      cVar5 = FUN_18449ae30(&stack0xffffffffffffffe8,*(undefined1 *)(param_1 + 0xd0),_DAT_18896b108)
      ;
      if (cVar5 != '\0') {
        return 0;
      }
      uStack_40 = 0x1805cf1ec;
      FUN_18000d950(0x3f,param_1,2,0);
    }
    return 1;
  }
  uStackX_20 = 0;
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    uStack_38 = 0;
    pcStack_30 = acStackX_8;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,acStackX_8,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      iVar8 = FUN_183f22380(uVar2,1,1,iVar7,0);
      if (iVar8 == 0) {
code_r0x0001832b39f4:
        uVar6 = FUN_183f23100(uVar2,iVar7 + 1,0);
        FUN_183f22fd0(uVar2,iVar7 + -1,0);
        if (acStackX_8[0] != '\0') {
          uStackX_20 = uVar6;
          func_0x000185ca7ff0(uStack_48,0);
        }
        return uVar6;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
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
  uVar6 = (*pcVar4)();
  return uVar6;
}


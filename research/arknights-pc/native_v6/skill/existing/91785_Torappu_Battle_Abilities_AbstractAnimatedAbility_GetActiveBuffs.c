
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_Abilities_AbstractAnimatedAbility_GetActiveBuffs_0x601668a(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 unaff_RSI;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c956cf == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    DAT_188c956cf = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0xb0);
  if (lVar7 == 0) {
    return *(longlong *)(param_1 + 0x198);
  }
  if (cRam0000000188cafb9a == '\0') {
    FUN_18048bf00(0x18890e628);
    FUN_18048bf00(0x1888f11e0);
    FUN_18048bf00(0x188906850);
    cRam0000000188cafb9a = '\x01';
  }
  lVar8 = 0;
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832f5864:
    FUN_18048ba10(lVar7,unaff_RSI);
code_r0x0001832f586f:
    FUN_18048c0b0();
code_r0x0001832f5874:
    FUN_18048c0b0();
  }
  else {
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    FUN_185ca7f50(uStackX_20,acStackX_8,0);
    if (*(longlong *)(lVar7 + 0x18) == 0) goto code_r0x0001832f587e;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar2 != 0) {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        iVar5 = FUN_183f22380(uVar1,1,1,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001832f5790:
          uVar6 = uRam000000018890e628;
          if (*(int *)(lRam0000000188906850 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar6 = FUN_185eded20(uVar6,0);
          lVar7 = FUN_183cf3ce0(lVar2,uVar1,iVar4 + 1,uVar6,0);
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          unaff_RSI = uRam00000001888f11e0;
          if (lVar7 == 0) {
code_r0x0001832f57fe:
            if (acStackX_8[0] != '\0') {
              func_0x000185ca7ff0(uStackX_20,0);
            }
            return lVar8;
          }
          lVar8 = func_0x00018048b9f0(lVar7,uRam00000001888f11e0);
          if (lVar8 != 0) goto code_r0x0001832f57fe;
          goto code_r0x0001832f5864;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar4 + -1,0);
          goto code_r0x0001832f5790;
        }
        goto code_r0x0001832f586f;
      }
      goto code_r0x0001832f5874;
    }
  }
  FUN_18048c0b0();
code_r0x0001832f587e:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  lVar7 = (*pcVar3)();
  return lVar7;
}


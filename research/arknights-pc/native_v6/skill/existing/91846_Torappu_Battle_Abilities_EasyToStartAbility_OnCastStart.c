
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_EasyToStartAbility_OnCastStart_0x60166c7(longlong *param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c956f7 == '\0') {
    FUN_18048bf00(&DAT_18880dc70);
    DAT_188c956f7 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18880dc70 + 0xb8) + 0x10);
  if (lVar6 == 0) {
    Torappu_Battle_AbilityStandard_OnCastStart_0x600f6bb(param_1,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    lVar6 = (**(code **)(*param_1 + 0x7a0))(param_1,*(undefined8 *)(*param_1 + 0x7a8));
    param_1[0x24] = lVar6;
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
  acStackX_8[0] = '\0';
  FUN_185ca7f50(uStackX_20,acStackX_8,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        iVar5 = FUN_183f22380(uVar1,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          if (acStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
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


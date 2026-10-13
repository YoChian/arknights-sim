
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_EasyToStartAbility__ctor_0x60166d1(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c95700 == '\0') {
    FUN_18048bf00(&DAT_18880dc70);
    FUN_18048bf00(&DAT_18885a700);
    DAT_188c95700 = '\x01';
  }
  *(undefined1 *)(param_1 + 0x118) = 1;
  *(undefined4 *)(param_1 + 0x11c) = 1;
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar6 = func_0x0001866fdac0(0,0);
  *(undefined8 *)(param_1 + 0x120) = uVar6;
  Torappu_Battle_AbilityStandard__ctor_0x600f6d6(param_1,0);
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18880dc70 + 0xb8) + 0x58);
  if (lVar1 == 0) {
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  acStackX_8[0] = '\0';
  FUN_185ca7f50(uStackX_20,acStackX_8,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar6 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar6,param_1,0);
        iVar5 = FUN_183f22380(uVar6,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar6,iVar4 + -1,0);
          if (acStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar4 + -1,0);
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


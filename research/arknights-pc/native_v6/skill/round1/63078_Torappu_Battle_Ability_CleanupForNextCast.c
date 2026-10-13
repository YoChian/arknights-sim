
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_CleanupForNextCast_0x600f667(longlong param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c8fcf8 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    FUN_18048bf00(&DAT_188927d60);
    DAT_188c8fcf8 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x1e8);
  if (lVar1 == 0) {
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_BattleController_StopAllBattleCoroutines_0x600fcea(param_1,1,0);
    *(undefined8 *)(param_1 + 0x68) = 0;
    func_0x00018048b9e0(param_1 + 0x68,0);
    *(undefined1 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = 0;
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  acStackX_8[0] = '\0';
  FUN_185ca7f50(uStackX_20,acStackX_8,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar3,uVar2,param_1,0);
        iVar6 = FUN_183f22380(uVar2,1,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar5 + -1,0);
          if (acStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


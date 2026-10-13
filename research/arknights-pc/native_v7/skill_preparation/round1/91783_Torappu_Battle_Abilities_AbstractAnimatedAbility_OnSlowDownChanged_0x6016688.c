
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_AbstractAnimatedAbility_OnSlowDownChanged_0x6016688(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (DAT_188c956cd == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    DAT_188c956cd = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0xa0);
  if (lVar1 == 0) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar4 = (**(code **)(*param_1 + 0x210))(param_1,*(undefined8 *)(*param_1 + 0x218));
    if ((cVar4 != '\0') &&
       (Torappu_Battle_AbilityStandard_DoUpdatePlaybackSpeed_0x600f6cb(param_1,0,0),
       (int)param_1[0x28] == 1)) {
      lVar1 = param_1[0xe];
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      uVar7 = (**(code **)(*param_1 + 0x250))(param_1,*(undefined8 *)(*param_1 + 600));
      if (lVar1 == 0) {
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      Torappu_PeriodicTimer_ResetButKeepProgress_0x6006578(lVar1,uVar7,0);
    }
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar7 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar7,param_1,0);
        iVar6 = FUN_183f22380(uVar7,1,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar7,iVar5 + -1,0);
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
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


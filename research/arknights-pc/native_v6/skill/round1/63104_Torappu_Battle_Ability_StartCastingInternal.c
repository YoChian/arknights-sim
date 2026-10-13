
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_StartCastingInternal_0x600f681(longlong *param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c8fd0b == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    FUN_18048bf00(&DAT_188927d60);
    DAT_188c8fd0b = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x280);
  if (lVar1 == 0) {
    *(undefined1 *)(param_1 + 0xc) = 1;
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = Torappu_Battle_BattleController_get_fixedFrameCnt_0x600fbd4(0);
    *(undefined4 *)((longlong)param_1 + 100) = uVar5;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
                    /* WARNING: Could not recover jumptable at 0x0001805d6db8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x480))(param_1,*(undefined8 *)(*param_1 + 0x488));
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
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar3,uVar2,param_1,0);
        iVar7 = FUN_183f22380(uVar2,1,0,iVar6,0);
        if (iVar7 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar6 + -1,0);
          if (acStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
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



/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_OnTick_0x600f674(longlong param_1,undefined8 param_2)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c8fcfe == '\0') {
    uStack_30 = 0x1805d6595;
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fcfe = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x218);
  if (lVar1 == 0) {
    plVar2 = *(longlong **)(param_1 + 0x70);
    if (plVar2 == (longlong *)0x0) {
      uStack_30 = 0x1805d6610;
      FUN_18048c0b0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    if (DAT_188ccc7f0 != '\0') {
      uStack_30 = 0x1805d65cf;
      func_0x000180446d00(*plVar2);
    }
                    /* WARNING: Could not recover jumptable at 0x0001805d65f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 400))(plVar2,param_2,*(undefined8 *)(*plVar2 + 0x198));
    return;
  }
  if (cRam0000000188caf41c == '\0') {
    FUN_18048bf00(&DAT_18885a700,param_1,param_2,0);
    cRam0000000188caf41c = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar4 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar4 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar4,uVar3,param_1,0);
        auStack_40[0] = param_2;
        uVar8 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
        FUN_183cfbf40(lVar4,uVar3,uVar8,0);
        iVar7 = FUN_183f22380(uVar3,2,0,iVar6,0);
        if (iVar7 == 0) {
code_r0x0001833f996e:
          FUN_183f22fd0(uVar3,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
          goto code_r0x0001833f996e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}



/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_Awake_0x600f6d5(longlong param_1)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  uint uVar7;
  longlong lVar8;
  
  if (DAT_188c8fd53 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_188902e38);
    DAT_188c8fd53 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x1f8);
  if (lVar6 == 0) {
    uVar5 = FUN_1844ba1c0(param_1,_DAT_188902e38);
    *(undefined8 *)(param_1 + 0x100) = uVar5;
    func_0x00018048b9e0(param_1 + 0x100,uVar5);
    lVar6 = *(longlong *)(param_1 + 0x100);
    uVar7 = 0;
    if (lVar6 != 0) {
      lVar8 = 0x20;
      do {
        if (*(int *)(lVar6 + 0x18) <= (int)uVar7) {
          return;
        }
        lVar6 = *(longlong *)(param_1 + 0x100);
        if (lVar6 == 0) break;
        if (*(uint *)(lVar6 + 0x18) <= uVar7) {
          FUN_18048c0a0();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        plVar1 = *(longlong **)(lVar8 + lVar6);
        if (plVar1 == (longlong *)0x0) break;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar1);
        }
        (**(code **)(*plVar1 + 400))(plVar1,param_1,*(undefined8 *)(*plVar1 + 0x198));
        lVar6 = *(longlong *)(param_1 + 0x100);
        uVar7 = uVar7 + 1;
        lVar8 = lVar8 + 8;
      } while (lVar6 != 0);
    }
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar5 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar5,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar8 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar8 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar8,uVar5,param_1,0);
        iVar4 = FUN_183f22380(uVar5,1,0,iVar3,0);
        if (iVar4 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar5,iVar3 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar3 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


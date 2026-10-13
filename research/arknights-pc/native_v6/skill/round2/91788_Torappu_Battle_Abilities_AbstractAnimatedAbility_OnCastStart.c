
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_AbstractAnimatedAbility_OnCastStart_0x601668d(longlong *param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 in_stack_ffffffffffffffe8;
  undefined4 uVar8;
  ulonglong in_stack_fffffffffffffff0;
  
  uVar8 = (undefined4)((ulonglong)in_stack_ffffffffffffffe8 >> 0x20);
  if (DAT_188c956d2 == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    DAT_188c956d2 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 200);
  if (lVar6 == 0) {
    Torappu_Battle_Abilities_EasyToStartAbility_OnCastStart_0x60166c7(param_1,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 2000))(param_1,*(undefined8 *)(*param_1 + 0x7d8));
    lVar6 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar7 = (**(code **)(*param_1 + 0x810))(param_1,*(undefined8 *)(*param_1 + 0x818));
    cVar3 = func_0x000185db9d60(uVar7,0);
    if (cVar3 == '\0') {
      if (lVar6 == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      FUN_180023a80(0x67,lVar6,uVar7,1,
                    CONCAT44(uVar8,(1.0 / *(float *)(param_1 + 0x37)) *
                                   *(float *)((longlong)param_1 + 0x1bc)),
                    in_stack_fffffffffffffff0 & 0xffffffffffffff00);
    }
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
    uVar7 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar7,param_1,0);
        iVar5 = FUN_183f22380(uVar7,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar7,iVar4 + -1,0);
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
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


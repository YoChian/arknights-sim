
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_DoAttach_0x600f656(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong *plVar8;
  longlong *plVar9;
  bool bVar10;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  undefined8 in_stack_ffffffffffffffe8;
  undefined8 in_stack_fffffffffffffff0;
  
  if (DAT_188c8fcea == '\0') {
    uStack_40 = 0x1805d4f25;
    FUN_18048bf00(&DAT_1889733f0);
    uStack_40 = 0x1805d4f31;
    FUN_18048bf00(&DAT_188935c68);
    uStack_40 = 0x1805d4f3d;
    FUN_18048bf00(&DAT_188805040);
    DAT_188c8fcea = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x178);
  if (lVar1 != 0) {
    if (*(longlong *)(lVar1 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
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
          FUN_183cf8c20(lVar3,uVar2,param_2,0);
          iVar7 = FUN_183f22380(uVar2,2,0,iVar6,0);
          if (iVar7 == 0) {
code_r0x0001832d231b:
            FUN_183f22fd0(uVar2,iVar6 + -1,0);
            return;
          }
          if (*(longlong *)(lVar1 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
            goto code_r0x0001832d231b;
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
  uStack_40 = 0x1805d4f73;
  FriendComponent_AttachAbilityToEntity_0x60104dd(param_1,param_2,param_1);
  uStack_40 = 0x1805d4f87;
  FUN_18515a130(&stack0xffffffffffffffe8,param_2,_DAT_188935c68);
  *(int *)(param_1 + 10) = (int)in_stack_ffffffffffffffe8;
  *(int *)((longlong)param_1 + 0x54) = (int)((ulonglong)in_stack_ffffffffffffffe8 >> 0x20);
  *(int *)(param_1 + 0xb) = (int)in_stack_fffffffffffffff0;
  *(int *)((longlong)param_1 + 0x5c) = (int)((ulonglong)in_stack_fffffffffffffff0 >> 0x20);
  uStack_40 = 0x1805d4f9b;
  func_0x00018048b9e0(param_1 + 10,0);
  if (DAT_188ccc7f0 != '\0') {
    uStack_40 = 0x1805d4fac;
    func_0x000180446d00(*param_1);
  }
  uStack_40 = 0x1805d4fcc;
  (**(code **)(*param_1 + 0x3e0))(param_1,*(undefined8 *)(*param_1 + 1000));
  if (param_2 != (longlong *)0x0) {
    lVar1 = *param_2;
    if (DAT_188ccc7f0 == '\0') {
      if ((*(byte *)(lVar1 + 0x130) < *(byte *)(_DAT_188805040 + 0x130)) ||
         (bVar10 = true,
         *(longlong *)
          (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_188805040 + 0x130) * 8) !=
         _DAT_188805040)) {
        bVar10 = false;
      }
      bVar10 = !bVar10;
    }
    else {
      uStack_40 = 0x1805d4ff5;
      cVar5 = func_0x0001804463e0(lVar1);
      bVar10 = cVar5 == '\0';
    }
    plVar9 = (longlong *)0x0;
    plVar8 = plVar9;
    if (!bVar10) {
      plVar8 = param_2;
    }
    if (plVar8 != (longlong *)0x0) {
      lVar1 = *param_2;
      if (DAT_188ccc7f0 == '\0') {
        if ((*(byte *)(lVar1 + 0x130) < *(byte *)(_DAT_188805040 + 0x130)) ||
           (bVar10 = true,
           *(longlong *)
            (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_188805040 + 0x130) * 8) !=
           _DAT_188805040)) {
          bVar10 = false;
        }
        bVar10 = !bVar10;
      }
      else {
        uStack_40 = 0x1805d504f;
        cVar5 = func_0x0001804463e0(lVar1);
        bVar10 = cVar5 == '\0';
      }
      plVar8 = plVar9;
      if (!bVar10) {
        plVar8 = param_2;
      }
      if (plVar8 == (longlong *)0x0) {
        uStack_40 = 0x1805d5170;
        FUN_18048c0b0();
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
      lVar1 = *param_2;
      if (DAT_188ccc7f0 == '\0') {
        if ((*(byte *)(lVar1 + 0x130) < *(byte *)(_DAT_188805040 + 0x130)) ||
           (bVar10 = true,
           *(longlong *)
            (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_188805040 + 0x130) * 8) !=
           _DAT_188805040)) {
          bVar10 = false;
        }
        bVar10 = !bVar10;
      }
      else {
        uStack_40 = 0x1805d50a5;
        cVar5 = func_0x0001804463e0(lVar1);
        bVar10 = cVar5 == '\0';
      }
      if (!bVar10) {
        plVar9 = param_2;
      }
      uStack_40 = 0x1805d50dc;
      cVar5 = Torappu_Battle_Unit_get_isDummy_0x6012f2b(plVar9,0);
      if ((cVar5 != '\0') && (*(char *)((longlong)param_1 + 0x49) == '\0')) goto LAB_1805d510d;
    }
  }
  if (DAT_188ccc7f0 != '\0') {
    uStack_40 = 0x1805d50f7;
    func_0x000180446d00(*param_1);
  }
  uStack_40 = 0x1805d510d;
  (**(code **)(*param_1 + 0x540))(param_1,*(undefined8 *)(*param_1 + 0x548));
LAB_1805d510d:
  uStack_40 = 0x1805d511a;
  Torappu_Battle_Ability_set_isAttached_0x600f641(param_1,1,0);
  if (DAT_188ccc7f0 != '\0') {
    uStack_40 = 0x1805d512b;
    func_0x000180446d00(*param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x0001805d5153. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x4a0))(param_1,*(undefined8 *)(*param_1 + 0x4a8));
  return;
}


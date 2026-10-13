
/* WARNING: Removing unreachable block (ram,0x0001832f7a98) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_AbstractAnimatedAbility_OnCastEnd_0x601668f
               (longlong param_1,undefined4 param_2)

{
  undefined4 uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined4 auStack_48 [2];
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c956d4 == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c956d4 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0xd8);
  if (lVar8 != 0) {
    if (cRam0000000188cafba9 == '\0') {
      FUN_18048bf00(0x1888a0e78,param_1,param_2,0);
      cRam0000000188cafba9 = '\x01';
    }
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar7 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar2 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar2 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar2,uVar7,param_1,0);
          auStack_48[0] = param_2;
          uVar9 = func_0x00018048b9c0(uRam00000001888a0e78,auStack_48);
          FUN_183cfbf40(lVar2,uVar7,uVar9,0);
          iVar6 = FUN_183f22380(uVar7,2,0,iVar5,0);
          if (iVar6 == 0) {
code_r0x0001832f7a7e:
            FUN_183f22fd0(uVar7,iVar5 + -1,0);
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar5 + -1,0);
            goto code_r0x0001832f7a7e;
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
  Torappu_Battle_Abilities_EasyToStartAbility_OnCastEnd_0x60166c8(param_1,param_2,0);
  uVar7 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar4 = FUN_186b638d0(uVar7,0,0);
  if (cVar4 == '\0') {
    if (*(char *)(param_1 + 0x1a4) != '\0') {
      uVar7 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
      lVar8 = FUN_1800057a0(uVar7,_DAT_18881b6b0);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar4 = FUN_186b63a70(lVar8,0,0);
      if (cVar4 != '\0') {
        if (lVar8 == 0) goto LAB_180f00576;
        uVar7 = Torappu_Battle_Enemy_get_lastAttackOrCombatAbility_0x6012a67(lVar8,0);
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar4 = FUN_186b63a70(uVar7,param_1,0);
        if (cVar4 != '\0') {
          return;
        }
      }
    }
    cVar4 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x150),0);
    if (cVar4 == '\0') {
      lVar8 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
      if (lVar8 == 0) goto LAB_180f00576;
      cVar4 = Torappu_Battle_Entity_get_canUseAbility_0x601036c(lVar8,0);
      if (cVar4 != '\0') {
        if (*(int *)(param_1 + 0x140) == 0) {
          if (*(longlong *)(param_1 + 0x70) == 0) goto LAB_180f00576;
          uVar7 = Torappu_PeriodicTimer_get_progress_0x6006572(*(longlong *)(param_1 + 0x70),0);
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar9 = func_0x0001866fdac0(1,0);
          if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar4 = Torappu_MathUtil_LT_0x6000276(uVar7,uVar9,0);
          if (cVar4 == '\0') {
            uVar7 = *(undefined8 *)(param_1 + 0x1b0);
            uVar9 = FUN_180005610(0x11,param_1);
            if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar4 = Torappu_MathUtil_LT_0x6000276(uVar7,uVar9,0);
            if (cVar4 == '\0') {
              uVar1 = *(undefined4 *)(param_1 + 0x18c);
              if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar4 = func_0x0001866e4c50(uVar1,0,0);
              if (cVar4 == '\0') {
                return;
              }
            }
          }
        }
        cVar4 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x160),0);
        if ((cVar4 == '\0') && (cVar4 = FUN_180005610(0x6e,param_1), cVar4 != '\0')) {
          lVar8 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
          if (lVar8 == 0) goto LAB_180f00576;
          uVar7 = *(undefined8 *)(param_1 + 0x160);
          puStack_20 = (undefined8 *)((ulonglong)puStack_20 & 0xffffffffffffff00);
          puStack_28 = (undefined1 *)CONCAT44(puStack_28._4_4_,0x3f800000);
        }
        else {
          cVar4 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x170),0);
          if ((cVar4 == '\0') && (cVar4 = FUN_180005610(0x6f,param_1), cVar4 != '\0')) {
            lVar8 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
            if (lVar8 == 0) {
LAB_180f00576:
              FUN_18048c0b0();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            uVar7 = *(undefined8 *)(param_1 + 0x170);
            puStack_20 = (undefined8 *)((ulonglong)puStack_20 & 0xffffffffffffff00);
            puStack_28 = (undefined1 *)CONCAT44(puStack_28._4_4_,0x3f800000);
          }
          else {
            lVar8 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
            if (lVar8 == 0) goto LAB_180f00576;
            uVar7 = *(undefined8 *)(param_1 + 0x150);
            puStack_20 = (undefined8 *)((ulonglong)puStack_20 & 0xffffffffffffff00);
            puStack_28 = (undefined1 *)CONCAT44(puStack_28._4_4_,0x3f800000);
          }
        }
        FUN_180023a80(0x67,lVar8,uVar7,1);
      }
    }
  }
  return;
}


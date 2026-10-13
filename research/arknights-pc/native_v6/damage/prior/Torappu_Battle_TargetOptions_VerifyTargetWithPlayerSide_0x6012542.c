/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
bool Torappu_Battle_TargetOptions_VerifyTargetWithPlayerSide_0x6012542
               (longlong param_1,longlong *param_2,char param_3)
{
  undefined4 uVar1;
  code *pcVar2;
  char cVar3;
  undefined1 uVar4;
  longlong lVar5;
  longlong *plVar6;
  bool bVar7;
  ulonglong auStack_18 [2];
  if (param_2 == (longlong *)0x0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    uVar4 = (*pcVar2)();
    return (bool)uVar4;
  }
  if ((*(uint *)(param_1 + 0x44) & *(uint *)((longlong)param_2 + 0x1c)) !=
      *(uint *)((longlong)param_2 + 0x1c)) {
    return false;
  }
  auStack_18[0] = 0;
  cVar3 = Torappu_Battle_BattleUtil_VerifyTargetWithPlayerSide_0x601319b
                    (param_2,*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8),
                     *(undefined1 *)(param_1 + 0x58));
  if (cVar3 == '\0') {
    return false;
  }
  if (cRam0000000188c9233f == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_188932ce8);
    cRam0000000188c9233f = '\x01';
  }
  auStack_18[0] = auStack_18[0] & 0xffffffff00000000;
  if (*(char *)(param_1 + 0xc) == '\0') {
    return true;
  }
  if ((*(char *)(param_1 + 0x24) != '\0') &&
     (cVar3 = Torappu_Battle_BattleUtil_CheckEntityUnitType_0x601318f
                        (*(undefined4 *)(param_1 + 0x28),param_2,0), cVar3 == '\0')) {
    return false;
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    if (*(char *)(param_1 + 0xd) == '\0') {
      if (param_2 == (longlong *)0x0) goto code_r0x0001809fad08;
      if (*(int *)((longlong)param_2 + 0x1c) != *(int *)(param_1 + 0x38)) {
        cVar3 = Torappu_Battle_Entity_get_isTargetFree_0x60103c6(param_2,0);
        if (cVar3 != '\0') {
          return false;
        }
        Torappu_Battle_TargetOptions__TryGetSourceMotionMode_0x6012544(param_1,&stack0x00000008,0);
        if ((*(char *)(param_1 + 0x10) == '\0') &&
           (cVar3 = FUN_180024b00(0x57,param_2,0x2e,3,0), cVar3 != '\0')) {
          return false;
        }
      }
      if (*(char *)(param_1 + 0xd) != '\0') goto code_r0x0001809faaed;
    }
    else {
code_r0x0001809faaed:
      if (*(char *)(param_1 + 0x2c) != '\0') {
        if (param_2 == (longlong *)0x0) goto code_r0x0001809fad08;
        cVar3 = Torappu_Battle_Entity_IsStillTargetFreeWithImmuneFlag_0x60103cc
                          (param_2,*(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34),0
                          );
        if (cVar3 != '\0') {
          return false;
        }
        Torappu_Battle_TargetOptions__TryGetSourceMotionMode_0x6012544(param_1,auStack_18,0);
        if (*(char *)(param_1 + 0x10) == '\0') {
          cVar3 = FUN_180024b00(0x57,param_2,*(undefined4 *)(param_1 + 0x30),
                                *(undefined4 *)(param_1 + 0x34),(undefined4)auStack_18[0]);
          if (cVar3 != '\0') {
            return false;
          }
        }
      }
    }
    if (*(char *)(param_1 + 0xe) == '\0') {
      if (param_2 == (longlong *)0x0) goto code_r0x0001809fad08;
      cVar3 = Torappu_Battle_Entity_get_isAllyTargetFree_0x60103d6(param_2,0);
      if ((cVar3 != '\0') && (*(int *)((longlong)param_2 + 0x1c) == *(int *)(param_1 + 0x38))) {
        return false;
      }
    }
    if (*(char *)(param_1 + 0x12) != '\0') {
      if ((param_2 == (longlong *)0x0) ||
         (lVar5 = Torappu_Battle_Entity_get_attributes_0x6010337(param_2,0), lVar5 == 0))
      goto code_r0x0001809fad08;
      cVar3 = Torappu_Battle_Attributes_GetAbnormalFlag_0x600fb18
                        (lVar5,*(undefined4 *)(param_1 + 0x14),0);
      if (cVar3 != '\0') {
        return false;
      }
    }
    if (*(char *)(param_1 + 0x13) != '\0') {
      if ((param_2 == (longlong *)0x0) ||
         (lVar5 = Torappu_Battle_Entity_get_attributes_0x6010337(param_2,0), lVar5 == 0))
      goto code_r0x0001809fad08;
      cVar3 = Torappu_Battle_Attributes_GetAbnormalFlag_0x600fb18
                        (lVar5,*(undefined4 *)(param_1 + 0x18),0);
      if (cVar3 == '\0') {
        return false;
      }
    }
  }
  if ((*(int *)(param_1 + 0x1c) != 0) && (*(char *)(param_1 + 0xf) == '\0')) {
    if (param_2 == (longlong *)0x0) goto code_r0x0001809fad08;
    cVar3 = Torappu_Battle_Entity_get_isHealFree_0x60103d5(param_2,0);
    if ((cVar3 != '\0') && ((*(byte *)(param_1 + 0x1c) & 2) != 0)) {
      return false;
    }
  }
  plVar6 = (longlong *)0x0;
  if (param_2 != (longlong *)0x0) {
    lVar5 = *param_2;
    if (DAT_188ccc7f0 == '\0') {
      if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_18886c268 + 0x130)) ||
         (bVar7 = true,
         *(longlong *)
          (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_18886c268 + 0x130) * 8) !=
         _DAT_18886c268)) {
        bVar7 = false;
      }
      bVar7 = !bVar7;
    }
    else {
      cVar3 = func_0x0001804463e0(lVar5);
      bVar7 = cVar3 == '\0';
    }
    if (!bVar7) {
      plVar6 = param_2;
    }
  }
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(plVar6,0,0);
  if (cVar3 == '\0') {
    if (param_2 == (longlong *)0x0) {
code_r0x0001809fad08:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar4 = (*pcVar2)();
      return (bool)uVar4;
    }
    if ((*(int *)((longlong)param_2 + 0x1c) == 1) && (*(int *)(param_1 + 0x20) != 0)) {
      return false;
    }
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x20);
    if ((plVar6 == (longlong *)0x0) ||
       (lVar5 = Torappu_Battle_Character_get_data_0x6012883(plVar6,0), lVar5 == 0))
    goto code_r0x0001809fad08;
    cVar3 = Torappu_Battle_BattleUtil_CheckProfessionMask_0x6013192
                      (uVar1,*(undefined4 *)(lVar5 + 0x70),1,0);
    if (cVar3 == '\0') {
      if (param_3 != '\0') {
        lVar5 = Torappu_Battle_Character_get_sharedData_0x6012885(plVar6,0);
        if (lVar5 == 0) goto code_r0x0001809fad08;
        if (*(uint *)(lVar5 + 0x34) != 0) {
          return 0 < (int)(*(uint *)(param_1 + 0x20) & *(uint *)(lVar5 + 0x34));
        }
      }
      return false;
    }
  }
  return true;
}

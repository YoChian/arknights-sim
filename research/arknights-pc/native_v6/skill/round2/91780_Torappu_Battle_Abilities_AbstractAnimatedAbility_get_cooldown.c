
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Abilities_AbstractAnimatedAbility_get_cooldown_0x6016685(longlong param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  code *pcVar4;
  char cVar5;
  undefined8 uVar6;
  longlong lVar7;
  float fVar8;
  undefined8 auStackX_18 [2];
  
  if (DAT_188c956ca == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c956ca = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0x88);
  if (lVar7 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp2620_0x600149c(lVar7,param_1,0);
    return;
  }
  iVar3 = *(int *)(param_1 + 0x140);
  if (iVar3 != 0) {
    if (iVar3 == 1) {
      cVar5 = FUN_180005610(0xd,param_1);
      if (cVar5 != '\0') {
        uVar6 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar5 = FUN_186b63a70(uVar6,0,0);
        if (cVar5 != '\0') {
          lVar7 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
          if (lVar7 != 0) {
            uVar6 = Torappu_Battle_Entity_get_slowDown_0x60103b5(lVar7,0);
            if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
              func_0x00018048c140(_DAT_18885a700);
            }
            cVar5 = func_0x000185ed91d0(uVar6,*(undefined8 *)
                                               (*(longlong *)(_DAT_18885a700 + 0xb8) + 0x20),0);
            if (cVar5 == '\0') goto LAB_180f01216;
            fVar1 = *(float *)(param_1 + 0x178);
            lVar7 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
            if (lVar7 != 0) {
              auStackX_18[0] = Torappu_Battle_Entity_get_animSlowDown_0x60103b6(lVar7,0);
              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              fVar8 = (float)Torappu_FP_AsFloat_0x6000323(auStackX_18,0);
              func_0x0001866fdad0(fVar1 / fVar8,0);
              return;
            }
          }
LAB_180f012be:
          FUN_18048c0b0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
      }
    }
    else if ((iVar3 != 2) && (iVar3 != 3)) goto LAB_180f010da;
LAB_180f01216:
    uVar2 = *(undefined4 *)(param_1 + 0x178);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    func_0x0001866fdad0(uVar2,0);
    return;
  }
  uVar6 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar5 = FUN_186b63a70(uVar6,0,0);
  if (cVar5 != '\0') {
    lVar7 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
    if (lVar7 != 0) {
      Torappu_Battle_Entity_get_attackTime_0x6010396(lVar7,0);
      return;
    }
    goto LAB_180f012be;
  }
LAB_180f010da:
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  func_0x0001866fdac0(0,0);
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_Abilities_AbstractAnimatedAbility_UpdatePlaybackSpeed_0x6016697
          (longlong *param_1,int param_2,float *param_3)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined8 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fStack_48;
  float fStack_44;
  undefined8 auStack_40 [7];
  
  if (DAT_188c956dc == '\0') {
    FUN_18048bf00(&DAT_1887f76b0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888915d8);
    DAT_188c956dc = '\x01';
  }
  fStack_48 = 0.0;
  fStack_44 = 0.0;
  auStack_40[0] = 0;
  lVar3 = *(longlong *)(*(longlong *)(_DAT_1887f76b0 + 0xb8) + 0x118);
  if (lVar3 == 0) {
    if ((param_2 == 1) || (param_2 == 2)) {
      *param_3 = 1.0;
      return 0;
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    lVar3 = (**(code **)(*param_1 + 0x250))(param_1,*(undefined8 *)(*param_1 + 600));
    param_1[0x36] = lVar3;
    *(undefined4 *)(param_1 + 0x37) = 0x3f800000;
    *(undefined4 *)((longlong)param_1 + 0x1bc) = 0x3f800000;
    plVar4 = (longlong *)Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
    lVar3 = param_1[0x29];
    if (plVar4 == (longlong *)0x0) goto LAB_180f00c66;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar4);
    }
    cVar2 = (**(code **)(*plVar4 + 0x7e0))
                      (plVar4,lVar3,&fStack_48,&fStack_44,*(undefined8 *)(*plVar4 + 0x7e8));
    if (cVar2 != '\0') {
      cVar2 = FUN_180005610(0xd,param_1);
      if (cVar2 == '\0') {
        cVar2 = '\0';
      }
      else {
        lVar3 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
        if (lVar3 == 0) goto LAB_180f00c66;
        uVar5 = Torappu_Battle_Entity_get_slowDown_0x60103b5(lVar3,0);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140(_DAT_18885a700);
        }
        cVar2 = func_0x000185ed91d0(uVar5,*(undefined8 *)
                                           (*(longlong *)(_DAT_18885a700 + 0xb8) + 0x20),0);
        fVar6 = fStack_44;
        if ((cVar2 != '\0') && ((int)param_1[0x28] == 1)) {
          lVar3 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
          if (lVar3 == 0) goto LAB_180f00c66;
          auStack_40[0] = Torappu_Battle_Entity_get_animSlowDown_0x60103b6(lVar3,0);
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          fStack_44 = (float)Torappu_FP_AsFloat_0x6000323(auStack_40,0);
          fVar8 = fStack_48;
          fStack_44 = fStack_44 * fVar6;
          lVar3 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
          if (lVar3 == 0) goto LAB_180f00c66;
          auStack_40[0] = Torappu_Battle_Entity_get_animSlowDown_0x60103b6(lVar3,0);
          fStack_48 = (float)Torappu_FP_AsFloat_0x6000323(auStack_40,0);
          fStack_48 = fVar8 / fStack_48;
        }
      }
      *(float *)((longlong)param_1 + 0x1bc) = fStack_44;
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      fVar6 = (float)Torappu_FP_AsFloat_0x6000323(param_1 + 0x36,0);
      fVar6 = fVar6 / fStack_48;
      if (fVar6 <= 0.1) {
        fVar6 = 0.1;
      }
      *(float *)(param_1 + 0x37) = fVar6;
      fVar6 = *(float *)(param_1 + 0x34);
      if (0.0 <= fVar6) {
        fVar8 = fVar6;
        if (cVar2 != '\0') {
          lVar3 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
          if (lVar3 == 0) {
LAB_180f00c66:
            FUN_18048c0b0();
            pcVar1 = (code *)swi(3);
            uVar5 = (*pcVar1)();
            return uVar5;
          }
          auStack_40[0] = Torappu_Battle_Entity_get_animSlowDown_0x60103b6(lVar3,0);
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          fVar7 = (float)Torappu_FP_AsFloat_0x6000323(auStack_40,0);
          fVar8 = 2.5;
          if (fVar6 / fVar7 <= 2.5) {
            fVar8 = fVar6 / fVar7;
          }
        }
        fVar6 = *(float *)(param_1 + 0x37);
        if (fVar8 <= *(float *)(param_1 + 0x37)) {
          fVar6 = fVar8;
        }
        *(float *)(param_1 + 0x37) = fVar6;
      }
      fVar8 = fStack_48;
      fVar6 = *(float *)(param_1 + 0x37);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      lVar3 = func_0x0001866fdad0(fVar6 * fVar8,0);
      param_1[0x36] = lVar3;
    }
    cVar2 = Torappu_Battle_Abilities_EasyToStartAbility_get_waitForAttackEvent_0x60166c4(param_1,0);
    lVar3 = param_1[0x36];
    if (cVar2 == '\0') {
      fVar6 = *(float *)(param_1 + 0x31);
      fVar8 = *(float *)(param_1 + 0x37);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar5 = func_0x0001866fdad0(fVar8 * fVar6,0);
      if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      lVar3 = Torappu_TSMath_Min_0x600033c(lVar3,uVar5,0);
    }
    param_1[0x35] = lVar3;
    uVar5 = 1;
    *param_3 = (1.0 / *(float *)(param_1 + 0x37)) * fStack_44;
  }
  else {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp2655_0x60014bf(lVar3,param_1,param_2,param_3,0);
  }
  return uVar5;
}


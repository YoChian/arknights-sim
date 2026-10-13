/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
Torappu_Battle_Entity_DoApplyModifier_0x601047c(undefined8 param_1,longlong param_2,char param_3)
{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong lVar11;
  int iVar12;
  if (DAT_188c9090b == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_1888703f8);
    FUN_18048bf00(&DAT_18887fe38);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_1888915d8);
    DAT_188c9090b = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar11 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x9f8);
  if (lVar11 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp3066_0x600165a(lVar11,param_1,param_2,param_3,0);
    return uVar5;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  iVar3 = Torappu_Battle_Modifier_get_targetType_0x601152a(param_2,0);
  if (iVar3 == 0) {
    uVar5 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
    uVar6 = Torappu_Battle_Entity_get_es_0x6010385(param_1,0);
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar7 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = func_0x0001866fdac0(0,0);
    cVar2 = func_0x000185ed91b0(uVar7,uVar8,0);
    if (cVar2 != '\0') {
      if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,0x400,0);
      if (cVar2 != '\0') {
        uVar8 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar8 = func_0x000184624db0(uVar8,uVar7,0);
        uVar9 = Torappu_Battle_Entity_get_maxHp_0x6010397(param_1,0);
        cVar2 = func_0x000185ed91c0(uVar8,uVar9,0);
        if (cVar2 != '\0') {
          uVar8 = Torappu_Battle_Entity_get_es_0x6010385(param_1,0);
          uVar9 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
          if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uVar9 = func_0x000184624db0(uVar9,uVar7,0);
          uVar10 = Torappu_Battle_Entity_get_maxHp_0x6010397(param_1,0);
          uVar9 = func_0x0001866fba10(uVar9,uVar10,0);
          uVar8 = func_0x000184624db0(uVar8,uVar9,0);
          Torappu_Battle_Entity_set_es_0x6010386(param_1,uVar8,0);
        }
      }
    }
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = func_0x0001866fdac0(0,0);
    cVar2 = func_0x000185ed91f0(uVar7,uVar8,0);
    if (cVar2 != '\0') {
      uVar8 = Torappu_Battle_Entity_get_es_0x6010385(param_1,0);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar9 = func_0x0001866fdac0(0,0);
      cVar2 = func_0x000185ed91c0(uVar8,uVar9,0);
      if (cVar2 != '\0') {
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar7 = func_0x0001866fdac0(0,0);
        uVar8 = Torappu_Battle_Entity_get_es_0x6010385(param_1,0);
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar9 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
        uVar8 = func_0x000184624db0(uVar8,uVar9,0);
        if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar7 = Torappu_TSMath_Min_0x600033c(uVar7,uVar8,0);
        uVar8 = Torappu_Battle_Entity_get_es_0x6010385(param_1,0);
        uVar9 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
        uVar8 = func_0x000184624db0(uVar8,uVar9,0);
        Torappu_Battle_Entity_set_es_0x6010386(param_1,uVar8,0);
      }
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = Torappu_Battle_Modifier_CheckSharedFlag_0x6011554(param_2,8,0);
    if (cVar2 == '\0') {
      uVar8 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = func_0x000184624db0(uVar8,uVar7,0);
    }
    else {
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar8 = func_0x0001866fdac0(1,0);
      uVar9 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
      uVar7 = func_0x000184624db0(uVar9,uVar7,0);
      if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = Torappu_TSMath_Max_0x600033b(uVar8,uVar7,0);
    }
    Torappu_Battle_Entity_set_hp_0x6010384(param_1,uVar7,0);
    uVar7 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar5 = func_0x0001866fba10(uVar7,uVar5,0);
    uVar7 = Torappu_Battle_Entity_get_es_0x6010385(param_1,0);
    uVar5 = func_0x000184624db0(uVar5,uVar7,0);
    uVar5 = func_0x0001866fba10(uVar5,uVar6,0);
    *(undefined8 *)(param_2 + 0x38) = uVar5;
    return 1;
  }
  if (iVar3 != 1) {
    if ((iVar3 != 5) ||
       (cVar2 = Torappu_Battle_Entity_get_isEPFreeAll_0x60103d7(param_1,0), cVar2 != '\0')) {
      return 0;
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar3 = Torappu_Battle_Modifier_get_deltaType_0x601152c(param_2,0);
    if (iVar3 == 1) {
      iVar3 = func_0x0001844dc660(6,_DAT_1888703f8);
      iVar12 = 1;
      if (iVar3 < 2) {
        return 1;
      }
      do {
        uVar4 = func_0x0001844dc660(iVar12,_DAT_18887fe38);
        Torappu_Battle_Entity__DoApplyEPModifierInternal_0x601047d(param_1,param_2,uVar4,param_3,0);
        iVar12 = iVar12 + 1;
      } while (iVar12 < iVar3);
      return 1;
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar3 = Torappu_Battle_Modifier_get_elementType_0x601153e(param_2,0);
    if (iVar3 < 1) {
      return 0;
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar3 = Torappu_Battle_Modifier_get_elementType_0x601153e(param_2,0);
    if (5 < iVar3) {
      return 0;
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar4 = Torappu_Battle_Modifier_get_elementType_0x601153e(param_2,0);
    Torappu_Battle_Entity__DoApplyEPModifierInternal_0x601047d(param_1,param_2,uVar4,param_3,0);
    return 1;
  }
  if (param_3 == '\0') {
    if (DAT_188c9085a == '\0') {
      FUN_18048bf00(&DAT_188841368);
      DAT_188c9085a = '\x01';
    }
    if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188841368);
    }
    lVar11 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x468);
    if (lVar11 == 0) {
      lVar11 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
      if (lVar11 == 0) {
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        uVar5 = (*pcVar1)();
        return uVar5;
      }
      cVar2 = Torappu_Battle_Attributes_GetAbnormalFlag_0x600fb18(lVar11,0x1d,0);
    }
    else {
      cVar2 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar11,param_1,0);
    }
    if (cVar2 != '\0') {
      return 0;
    }
  }
  uVar5 = Torappu_Battle_Entity_get_sp_0x6010388(param_1,0);
  if ((param_3 == '\0') &&
     (cVar2 = Torappu_Battle_Entity_get_spRecoverStopped_0x60103c2(param_1,0), cVar2 != '\0')) {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar7 = func_0x0001866fdac0(0,0);
    cVar2 = func_0x000185ed91f0(uVar6,uVar7,0);
    if (cVar2 == '\0') goto LAB_1806f221b;
  }
  uVar6 = Torappu_Battle_Entity_get_sp_0x6010388(param_1,0);
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar7 = Torappu_Battle_Modifier_get_finalDelta_0x6011544(param_2,0);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar6 = func_0x000184624db0(uVar6,uVar7,0);
  Torappu_Battle_Entity_set_sp_0x6010389(param_1,uVar6,0);
LAB_1806f221b:
  uVar6 = Torappu_Battle_Entity_get_sp_0x6010388(param_1,0);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar5 = func_0x0001866fba10(uVar6,uVar5,0);
  *(undefined8 *)(param_2 + 0x38) = uVar5;
  return 1;
}

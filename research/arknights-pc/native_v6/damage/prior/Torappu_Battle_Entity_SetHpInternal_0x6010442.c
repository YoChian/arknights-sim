/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined1
Torappu_Battle_Entity_SetHpInternal_0x6010442
          (longlong *param_1,undefined8 param_2,char param_3,undefined1 param_4,undefined1 param_5)
{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  bool bVar13;
  longlong lStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined1 auStack_b8 [144];
  if (DAT_188c908d2 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_1888915d8);
    DAT_188c908d2 = '\x01';
  }
  uStack_c8 = 0;
  uStack_148 = 0;
  uStack_140 = 0;
  uStack_138 = 0;
  uStack_130 = 0;
  uStack_128 = 0;
  uStack_120 = 0;
  uStack_118 = 0;
  uStack_110 = 0;
  uStack_108 = 0;
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_e8 = 0;
  uStack_e0 = 0;
  uStack_d8 = 0;
  uStack_d0 = 0;
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x830);
  if (lVar8 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp3060_0x6001654
                      (lVar8,param_1,param_2,param_3,param_4,param_5,0);
    return uVar5;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar2 = (**(code **)(*param_1 + 0x3c0))(param_1,*(undefined8 *)(*param_1 + 0x3c8));
  if ((cVar2 == '\0') && (param_3 == '\0')) {
    return 0;
  }
  uVar12 = 0;
  lStack_150 = 0;
  uVar6 = Torappu_Battle_Entity_get_maxMinusHp_0x6010391(param_1,0);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar7 = func_0x0001866fdac0(0,0);
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  bVar3 = Torappu_MathUtil_Equals_0x6000284(uVar6,uVar7,0);
  bVar3 = bVar3 ^ 1;
  uVar6 = func_0x0001866fdac0(0,0);
  cVar2 = Torappu_MathUtil_LE_0x6000277(param_2,uVar6,0);
  if ((cVar2 == '\0') ||
     (lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0), lVar8 == 0)) {
    if (bVar3 != 0) goto LAB_1806fd6a2;
LAB_1806fd85d:
    cVar2 = '\0';
LAB_1806fd860:
    if (param_3 == '\0') {
LAB_1806fd865:
      cVar4 = Torappu_Battle_Entity_get_isUndeadable_0x60103d4(param_1,0);
      if ((cVar4 != '\0' || bVar3 != 0) || cVar2 != '\0') {
        uVar12 = 1;
      }
    }
  }
  else {
    lVar8 = param_1[8];
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = func_0x0001866fba10(param_2,lVar8,0);
    lVar8 = param_1[4];
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    puVar9 = (undefined8 *)
             Torappu_Battle_Modifier_NewTrySetHpZero_0x6011567
                       (auStack_b8,uVar6,param_1,(int)lVar8,0);
    uStack_148 = *puVar9;
    uStack_140 = puVar9[1];
    uStack_138 = puVar9[2];
    uStack_130 = puVar9[3];
    uStack_128 = puVar9[4];
    uStack_120 = puVar9[5];
    uStack_118 = puVar9[6];
    uStack_110 = puVar9[7];
    uStack_108 = puVar9[8];
    uStack_100 = puVar9[9];
    uStack_f8 = puVar9[10];
    uStack_f0 = puVar9[0xb];
    uStack_e8 = puVar9[0xc];
    uStack_e0 = puVar9[0xd];
    uStack_d8 = puVar9[0xe];
    uStack_d0 = puVar9[0xf];
    uStack_c8 = puVar9[0x10];
    if (bVar3 != 0) {
      lVar8 = param_1[8];
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar6 = func_0x0001866fdac0(1,0);
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = Torappu_MathUtil_GT_0x6000273(lVar8,uVar6,0);
      if (cVar2 == '\0') {
        uVar6 = Torappu_Battle_Entity_get_minusHp_0x601038d(param_1,0);
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar7 = Torappu_Battle_Modifier_get_value_0x6011545(&uStack_148,0);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar6 = func_0x000184624db0(uVar6,uVar7,0);
      }
      else {
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar6 = Torappu_Battle_Modifier_get_value_0x6011545(&uStack_148,0);
        lVar8 = param_1[8];
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar6 = func_0x0001866fba10(uVar6,lVar8,0);
      }
      Torappu_Battle_Entity_set_minusHp_0x601038e(param_1,uVar6,0);
      uVar6 = Torappu_Battle_Entity_get_minusHp_0x601038d(param_1,0);
      uVar7 = Torappu_Battle_Entity_get_maxMinusHp_0x6010391(param_1,0);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = func_0x000185ed91b0(uVar6,uVar7,0);
      if (cVar2 != '\0') {
        lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
        if (lVar8 == 0) goto LAB_1806fdbcd;
        BuffContainer_OnBeforeTrySetHpZero_0x600ff95(lVar8,&uStack_148,&lStack_150,0);
      }
LAB_1806fd6a2:
      lVar8 = param_1[8];
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = Torappu_MathUtil_GT_0x6000273(param_2,lVar8,0);
      if (cVar2 != '\0') {
        lVar8 = param_1[8];
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar6 = func_0x0001866fba10(param_2,lVar8,0);
        uVar7 = func_0x0001866fdac0(0,0);
        uVar10 = Torappu_Battle_Entity_get_minusHp_0x601038d(param_1,0);
        uVar10 = func_0x0001866fba10(uVar6,uVar10,0);
        if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar7 = Torappu_TSMath_Max_0x600033b(uVar7,uVar10,0);
        param_2 = func_0x000184624db0(uVar7,param_1[8],0);
        uVar7 = func_0x0001866fdac0(0,0);
        uVar10 = Torappu_Battle_Entity_get_minusHp_0x601038d(param_1,0);
        uVar6 = func_0x0001866fba10(uVar10,uVar6,0);
        uVar6 = Torappu_TSMath_Max_0x600033b(uVar7,uVar6,0);
        Torappu_Battle_Entity_set_minusHp_0x601038e(param_1,uVar6,0);
      }
      uVar6 = Torappu_Battle_Entity_get_minusHp_0x601038d(param_1,0);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar7 = func_0x0001866fdac0(0,0);
      if ((param_3 == '\0') &&
         (cVar2 = Torappu_Battle_Entity_get_isUndeadable_0x60103d4(param_1,0), cVar2 != '\0')) {
        uVar10 = Torappu_Battle_Entity_get_maxMinusHp_0x6010391(param_1,0);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar11 = func_0x0001866fdac0(1,0);
        uVar10 = func_0x0001866fba10(uVar10,uVar11,0);
      }
      else {
        uVar10 = Torappu_Battle_Entity_get_maxMinusHp_0x6010391(param_1,0);
      }
      if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar6 = Torappu_TSMath_Clamp_0x600033e(uVar6,uVar7,uVar10,0);
      Torappu_Battle_Entity_set_minusHp_0x601038e(param_1,uVar6,0);
      goto LAB_1806fd85d;
    }
    lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    if (lVar8 == 0) goto LAB_1806fdbcd;
    BuffContainer_OnBeforeTrySetHpZero_0x600ff95(lVar8,&uStack_148,&lStack_150,0);
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(&uStack_148,0);
    uVar6 = uStack_110;
    if (cVar2 == '\0') goto LAB_1806fd860;
    if (param_3 == '\0') {
      lVar8 = param_1[8];
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      param_2 = func_0x000184624db0(lVar8,uVar6,0);
      goto LAB_1806fd865;
    }
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar6 = func_0x0001866fdac0(uVar12,0);
  uVar12 = Torappu_Battle_Entity_get_maxHp_0x6010397(param_1,0);
  if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar8 = Torappu_TSMath_Clamp_0x600033e(param_2,uVar6,uVar12,0);
  bVar13 = DAT_188c9081e == '\0';
  param_1[8] = lVar8;
  if (bVar13) {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    DAT_188c9081e = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x288);
  if (lVar8 == 0) {
    uVar6 = Torappu_Battle_Entity_get_hp_0x6010383(param_1,0);
    uVar12 = Torappu_Battle_Entity_get_maxHp_0x6010397(param_1,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = Torappu_FP_op_Division_0x6000305(uVar6,uVar12,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = Torappu_MathUtil_Clamp01_0x600028a(uVar6,0);
  }
  else {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp2620_0x600149c(lVar8,param_1,0);
  }
  uVar12 = func_0x0001866fdac0(1,0);
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_MathUtil_Equals_0x6000284(uVar6,uVar12,0);
  if (cVar2 != '\0') {
    if (DAT_188c908eb == '\0') {
      FUN_18048bf00(&DAT_188841368);
      DAT_188c908eb = '\x01';
    }
    if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_188841368);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x8f8);
    if (lVar8 == 0) {
      lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
      if (lVar8 == 0) goto LAB_1806fdbcd;
      BuffContainer_OnOwnerHpFull_0x600ffad(lVar8,0);
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar8,param_1,0);
    }
  }
  lVar8 = param_1[8];
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar6 = func_0x0001866fdac0(0,0);
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_MathUtil_LE_0x6000277(lVar8,uVar6,0);
  if (cVar2 == '\0') {
    if (bVar3 != 0) {
      uVar6 = Torappu_Battle_Entity_get_minusHp_0x601038d(param_1,0);
      uVar12 = Torappu_Battle_Entity_get_maxMinusHp_0x6010391(param_1,0);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = func_0x000185ed91b0(uVar6,uVar12,0);
      if (cVar2 != '\0') goto LAB_1806fdaef;
    }
  }
  else {
LAB_1806fdaef:
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar8 = func_0x0001866fdac0(0,0);
    param_1[8] = lVar8;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 0x8d0))(param_1,param_4,param_5,*(undefined8 *)(*param_1 + 0x8d8));
  }
  cVar2 = Torappu_Battle_Entity_get_unfinished_0x6010353(param_1,0);
  if ((cVar2 != '\0') && (lStack_150 != 0)) {
    lVar8 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    if (lVar8 == 0) {
LAB_1806fdbcd:
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      uVar5 = (*pcVar1)();
      return uVar5;
    }
    BuffContainer_OnPostTrySetHpZero_0x600ff96(lVar8,lStack_150,0);
  }
  return 1;
}

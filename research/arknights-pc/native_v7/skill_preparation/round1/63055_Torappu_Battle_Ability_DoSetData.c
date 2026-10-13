
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_DoSetData_0x600f650
               (longlong param_1,undefined8 param_2,longlong *param_3)

{
  longlong *plVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  char cVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  longlong lStack_18;
  longlong lStack_10;
  
  if (DAT_188c8fce4 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_1888db540);
    FUN_18048bf00(&DAT_188935c68);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1887fd218);
    DAT_188c8fce4 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x148);
  if (lVar6 == 0) {
    FUN_18515a130(&uStack_38,param_2,_DAT_188935c68);
    *(undefined4 *)(param_1 + 0x50) = (undefined4)uStack_38;
    *(undefined4 *)(param_1 + 0x54) = uStack_38._4_4_;
    *(undefined4 *)(param_1 + 0x58) = (undefined4)uStack_30;
    *(undefined4 *)(param_1 + 0x5c) = uStack_30._4_4_;
    func_0x00018048b9e0(param_1 + 0x50,0);
    lStack_18 = param_3[2];
    lStack_10 = param_3[3];
    if (*param_3 == 0) {
      lVar6 = func_0x00018045cfe0(_DAT_188941920);
      if (lVar6 == 0) goto LAB_1805d5903;
      Torappu_Blackboard__ctor_0x6007854(lVar6,0);
    }
    else {
      cVar5 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x38),0);
      if (cVar5 == '\0') {
        lStack_18 = param_3[2];
        lStack_10 = param_3[3];
        if (*param_3 == 0) goto LAB_1805d5903;
        lVar6 = Torappu_Blackboard_GenerateBlackboardWithPrefix_0x600787b
                          (*param_3,*(undefined8 *)(param_1 + 0x38),0);
      }
      else {
        uStack_38 = *param_3;
        uStack_30 = param_3[1];
        lStack_18 = param_3[2];
        lStack_10 = param_3[3];
        lVar6 = func_0x00018045cfe0(_DAT_188941920);
        if (lVar6 == 0) goto LAB_1805d5903;
        Torappu_Blackboard__ctor_0x6007855(lVar6,uStack_38,0);
      }
    }
    Torappu_Battle_Ability_set_blackboard_0x600f62b(param_1,lVar6,0);
    if (DAT_188c8fcc1 == '\0') {
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcc1 = '\x01';
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x30);
    if (lVar6 == 0) {
      lVar6 = *(longlong *)(param_1 + 0x88);
    }
    else {
      lVar6 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar6,param_1,0);
    }
    *param_3 = lVar6;
    func_0x00018048b9e0(param_3,lVar6);
    cVar5 = func_0x000185db9d60(*(undefined8 *)(param_1 + 0x40),0);
    if (cVar5 == '\0') {
      lStack_18 = param_3[2];
      lStack_10 = param_3[3];
      cVar5 = func_0x000185db9d60(param_3[1],0);
      lVar6 = *(longlong *)(param_1 + 0x40);
      if (cVar5 == '\0') {
        uStack_38 = *param_3;
        uStack_30 = param_3[1];
        lStack_18 = param_3[2];
        lStack_10 = param_3[3];
        if (*(int *)(_DAT_1888db540 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        lVar6 = Torappu_HGString_Format_0x6000518(_DAT_1887fd218,uStack_30,lVar6,0);
        param_3[1] = lVar6;
      }
      else {
        param_3[1] = lVar6;
      }
      func_0x00018048b9e0(param_3 + 1,lVar6);
    }
    uStack_38 = *param_3;
    uStack_30 = param_3[1];
    uStack_28 = param_3[2];
    uStack_20 = param_3[3];
    uVar8 = (int)*param_3;
    uVar9 = *(undefined4 *)((longlong)param_3 + 4);
    uVar10 = (int)param_3[1];
    uVar11 = *(undefined4 *)((longlong)param_3 + 0xc);
    if (DAT_188c8fcdc == '\0') {
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcdc = '\x01';
      uVar8 = (undefined4)uStack_38;
      uVar9 = uStack_38._4_4_;
      uVar10 = (undefined4)uStack_30;
      uVar11 = uStack_30._4_4_;
    }
    lVar4 = uStack_20;
    lVar3 = uStack_28;
    lVar6 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x108);
    if (lVar6 == 0) {
      *(undefined4 *)(param_1 + 0x98) = uVar8;
      *(undefined4 *)(param_1 + 0x9c) = uVar9;
      *(undefined4 *)(param_1 + 0xa0) = uVar10;
      *(undefined4 *)(param_1 + 0xa4) = uVar11;
      *(longlong *)(param_1 + 0xa8) = uStack_28;
      *(longlong *)(param_1 + 0xb0) = uStack_20;
      func_0x00018048b9e0(param_1 + 0x98,0);
    }
    else {
      uStack_28 = CONCAT44(uVar9,uVar8);
      uStack_20 = CONCAT44(uVar11,uVar10);
      lStack_18 = lVar3;
      lStack_10 = lVar4;
      XLua_DelegateBridge___Gen_Delegate_Imp2638_0x60014ae(lVar6,param_1,&uStack_28,0);
    }
    uVar7 = *(undefined8 *)(param_1 + 0x28);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar5 = FUN_186b63a70(uVar7,0,0);
    if (cVar5 != '\0') {
      plVar1 = *(longlong **)(param_1 + 0x28);
      if (DAT_188c8fcc1 == '\0') {
        FUN_18048bf00(&DAT_1889733f0);
        DAT_188c8fcc1 = '\x01';
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x30);
      if (lVar6 == 0) {
        uVar7 = *(undefined8 *)(param_1 + 0x88);
      }
      else {
        uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar6,param_1,0);
      }
      if (plVar1 != (longlong *)0x0) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar1);
        }
        (**(code **)(*plVar1 + 0x2a0))(plVar1,uVar7,*(undefined8 *)(*plVar1 + 0x2a8));
        return;
      }
LAB_1805d5903:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  else {
    uStack_28 = *param_3;
    uStack_20 = param_3[1];
    lStack_18 = param_3[2];
    lStack_10 = param_3[3];
    XLua_DelegateBridge___Gen_Delegate_Imp2626_0x60014a2(lVar6,param_1,param_2,&uStack_28,0);
  }
  return;
}


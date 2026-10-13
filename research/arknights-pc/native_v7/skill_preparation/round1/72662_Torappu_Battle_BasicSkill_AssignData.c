
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_AssignData_0x6011bd7
               (longlong *param_1,longlong param_2,longlong *param_3,longlong param_4,
               longlong *param_5)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong lVar12;
  uint uVar13;
  ulonglong uVar14;
  ulonglong uVar15;
  ulonglong uVar16;
  bool bVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  longlong lStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  longlong alStack_a8 [2];
  undefined8 uStack_98;
  undefined8 uStack_90;
  uint auStack_88 [2];
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  longlong lStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  
  if (DAT_188c91c4b == '\0') {
    FUN_18048bf00(&DAT_188802da8);
    FUN_18048bf00(&DAT_18895c4e0);
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_1888746f8);
    FUN_18048bf00(&DAT_18896a750);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888a0c38);
    FUN_18048bf00(&DAT_188848cb0);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188878840);
    FUN_18048bf00(&DAT_188836150);
    FUN_18048bf00(&DAT_188817fd0);
    FUN_18048bf00(&DAT_1887fc6d8);
    FUN_18048bf00(&DAT_1889281b8);
    FUN_18048bf00(&DAT_188926a78);
    FUN_18048bf00(&DAT_1887fc850);
    FUN_18048bf00(&DAT_188835620);
    DAT_188c91c4b = '\x01';
  }
  uVar14 = 0;
  uStack_b0 = 0;
  uStack_c0 = 0;
  uStack_b8 = 0;
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x2b8);
  if (lVar8 != 0) {
    uStack_98 = *param_5;
    uStack_90 = param_5[1];
    XLua_DelegateBridge___Gen_Delegate_Imp3539_0x6001833
              (lVar8,param_1,param_2,param_3,param_4,&uStack_98,0);
    return;
  }
  param_1[0x16] = param_2;
  func_0x00018048b9e0(param_1 + 0x16,param_2);
  param_1[0x15] = (longlong)param_3;
  func_0x00018048b9e0(param_1 + 0x15,param_3);
  if (param_4 == 0) {
    if (param_2 == 0) goto LAB_180958f88;
    Torappu_Battle_BasicSkill_set_blackboard_0x6011bb1(param_1,*(undefined8 *)(param_2 + 0x60),0);
  }
  else {
    if (param_1[0x16] == 0) goto LAB_180958f88;
    uVar7 = Torappu_Blackboard_Union_0x6007863(*(undefined8 *)(param_1[0x16] + 0x60),param_4,0);
    Torappu_Battle_BasicSkill_set_blackboard_0x6011bb1(param_1,uVar7,0);
    if (param_2 == 0) goto LAB_180958f88;
  }
  if (*(longlong *)(param_2 + 0x20) == 0) {
    if (param_3 == (longlong *)0x0) goto LAB_180958f88;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_3);
    }
    alStack_a8[0] = (**(code **)(*param_3 + 0xb50))(param_3,*(undefined8 *)(*param_3 + 0xb58));
  }
  else {
    alStack_a8[0] = *(longlong *)(param_2 + 0x20);
  }
  if (DAT_188c91c24 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c24 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
  if (lVar8 == 0) {
    lVar8 = param_1[0x23];
  }
  else {
    lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar8,param_1,0);
  }
  if (lVar8 == 0) {
    uVar21 = 0xbf800000;
  }
  else {
    lVar8 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
    if (lVar8 == 0) goto LAB_180958f88;
    uVar21 = Torappu_Blackboard_GetFloatOrDefault_0x6007871(lVar8,_DAT_188926a78,0xbf800000,0,0);
  }
  uStack_98 = *param_5;
  uStack_90 = param_5[1];
  uVar5 = (int)*param_5;
  uVar18 = *(undefined4 *)((longlong)param_5 + 4);
  uVar19 = (int)param_5[1];
  uVar20 = *(undefined4 *)((longlong)param_5 + 0xc);
  if (DAT_188c91c76 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_188833b88);
    DAT_188c91c76 = '\x01';
    uVar5 = (undefined4)uStack_98;
    uVar18 = uStack_98._4_4_;
    uVar19 = (undefined4)uStack_90;
    uVar20 = uStack_90._4_4_;
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x418);
  if (lVar8 == 0) {
    if (*(int *)(_DAT_188833b88 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar4 = Delta_IsNull_0x6013020(&uStack_98,0);
    if (cVar4 == '\0') {
      if (uStack_98 != 0) {
        uVar7 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
        uVar7 = Torappu_Blackboard_Union_0x6007863(uVar7,uStack_98,0);
        Torappu_Battle_BasicSkill_set_blackboard_0x6011bb1(param_1,uVar7,0);
      }
      cVar4 = func_0x000185db9d60(uStack_90,0);
      if (cVar4 == '\0') {
        alStack_a8[0] = uStack_90;
        func_0x00018048b9e0(alStack_a8);
      }
    }
  }
  else {
    uStack_78 = CONCAT44(uVar18,uVar5);
    uStack_70 = CONCAT44(uVar20,uVar19);
    XLua_DelegateBridge___Gen_Delegate_Imp3545_0x6001839(lVar8,param_1,&uStack_78,alStack_a8,0);
  }
  if (DAT_188c91c74 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c74 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x408);
  if (lVar8 == 0) {
    if ((*(char *)(param_2 + 0x68) == '\0') ||
       (cVar4 = func_0x000185db9d60(*(undefined8 *)(param_2 + 0x50),0), cVar4 != '\0')) {
      uVar7 = *(undefined8 *)(param_2 + 0x18);
    }
    else {
      uVar7 = *(undefined8 *)(param_2 + 0x50);
    }
  }
  else {
    uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp67_0x6000aa3(lVar8,param_1,param_2,0);
  }
  uStack_80 = uVar7;
  if ((*(char *)((longlong)param_1 + 0x49) != '\0') &&
     (lVar8 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0), lVar8 != 0)) {
    lVar8 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar9 = func_0x0001866fdac0(0xffffffff,0);
    if (lVar8 == 0) goto LAB_180958f88;
    uVar9 = Torappu_Blackboard_GetFpOrDefault_0x6007872(lVar8,_DAT_1889281b8,uVar9,0,0);
    uVar10 = System_String_Format_0x600030d(_DAT_188817fd0,_DAT_1887fc850,_DAT_1889281b8,0);
    lVar8 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
    if (lVar8 == 0) goto LAB_180958f88;
    cVar4 = Torappu_Blackboard_ContainsKey_0x600785e(lVar8,uVar10,0);
    if (cVar4 == '\0') {
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar11 = func_0x0001866fdac0(0,0);
      cVar4 = func_0x000185ed91c0(uVar9,uVar11,0);
      if (cVar4 != '\0') {
        lVar8 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
        if (lVar8 == 0) goto LAB_180958f88;
        Torappu_Blackboard_Assign_0x600785c(lVar8,uVar10,uVar9,0);
      }
    }
  }
  if (DAT_188c91c26 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c26 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 400);
  if (lVar8 == 0) {
    lVar8 = param_1[0x18];
  }
  else {
    lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp2921_0x60015c9(lVar8,param_1,0);
  }
  uStack_c0 = 0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  if (DAT_188c91c24 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c24 = '\x01';
  }
  lVar12 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
  if (lVar12 == 0) {
    lStack_c8 = param_1[0x23];
  }
  else {
    lStack_c8 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar12,param_1,0);
  }
  func_0x00018048b9e0(&lStack_c8,lStack_c8);
  uStack_c0 = uVar7;
  func_0x00018048b9e0(&uStack_c0,uVar7);
  uStack_b8 = alStack_a8[0];
  func_0x00018048b9e0(&uStack_b8);
  uStack_b0 = CONCAT44(uStack_b0._4_4_,uVar21);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  uVar5 = (**(code **)(*param_1 + 0x390))(param_1,*(undefined8 *)(*param_1 + 0x398));
  uStack_b0 = CONCAT44(uVar5,(undefined4)uStack_b0);
  if (lVar8 != 0) {
    uStack_78 = lStack_c8;
    uStack_70 = uStack_c0;
    uStack_68 = (undefined4)uStack_b8;
    uStack_64 = uStack_b8._4_4_;
    uStack_60 = (undefined4)uStack_b0;
    uStack_5c = uVar5;
    Torappu_Battle_Ability_SetData_0x600f64f(lVar8,param_3,&uStack_78,0);
    if (DAT_188c91c26 == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c26 = '\x01';
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 400);
    if (lVar8 == 0) {
      lVar8 = param_1[0x18];
    }
    else {
      lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp2921_0x60015c9(lVar8,param_1,0);
    }
    lVar12 = func_0x00018045cfe0(_DAT_188802da8);
    if ((lVar12 != 0) &&
       (EasyTouchIsReadyHandler__ctor_0x6000a20(lVar12,param_1,_DAT_18895c4e0,0), lVar8 != 0)) {
      *(longlong *)(lVar8 + 0x18) = lVar12;
      func_0x00018048b9e0(lVar8 + 0x18,lVar12);
      if (DAT_188c91c26 == '\0') {
        FUN_18048bf00(&DAT_188925ba0);
        DAT_188c91c26 = '\x01';
      }
      lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 400);
      if (lVar8 == 0) {
        lVar8 = param_1[0x18];
      }
      else {
        lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp2921_0x60015c9(lVar8,param_1,0);
      }
      lVar12 = func_0x00018045cfe0(_DAT_1888a0c38);
      if (lVar12 != 0) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        FinishCallbackDelegate__ctor_0x600f688(lVar12,param_1,*(undefined8 *)(*param_1 + 0x638),0);
        if (lVar8 != 0) {
          *(longlong *)(lVar8 + 0x20) = lVar12;
          func_0x00018048b9e0(lVar8 + 0x20,lVar12);
          iVar6 = FUN_1844afc00(param_1[10],_DAT_1888746f8);
          lVar8 = 0x20;
          if (0 < iVar6) {
            uStack_78 = (longlong)iVar6;
            lVar12 = 0x20;
            uVar16 = uVar14;
            uVar15 = uVar14;
            do {
              lVar1 = param_1[10];
              if (lVar1 == 0) goto LAB_180958f88;
              uVar13 = (uint)uVar16;
              if (*(uint *)(lVar1 + 0x18) <= uVar13) goto LAB_180958f82;
              lVar1 = *(longlong *)(lVar12 + lVar1);
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar4 = FUN_186b63a70(lVar1,0,0);
              if (cVar4 != '\0') {
                lStack_c8 = 0;
                uStack_c0 = 0;
                uStack_b8 = 0;
                uStack_b0 = 0;
                lStack_c8 = Torappu_Battle_BasicSkill_get_blackboard_0x6011bb0(param_1,0);
                func_0x00018048b9e0(&lStack_c8,lStack_c8);
                if (*(char *)((longlong)param_1 + 0x4a) == '\0') {
                  uStack_c0 = **(undefined8 **)(_DAT_188878840 + 0xb8);
                }
                else {
                  auStack_88[0] = uVar13;
                  uVar7 = func_0x00018048b9c0(_DAT_188848cb0,auStack_88);
                  uStack_c0 = System_String_Format_0x600030d(_DAT_1887fc6d8,uStack_80,uVar7,0);
                }
                func_0x00018048b9e0(&uStack_c0,uStack_c0);
                uStack_b8 = alStack_a8[0];
                func_0x00018048b9e0(&uStack_b8);
                uStack_b0 = CONCAT44(uStack_b0._4_4_,uVar21);
                uVar5 = FUN_180005610(0x25,param_1);
                uStack_b0 = CONCAT44(uVar5,(undefined4)uStack_b0);
                if (lVar1 == 0) goto LAB_180958f88;
                lStack_58 = lStack_c8;
                uStack_50 = uStack_c0;
                uStack_48 = (undefined4)uStack_b8;
                uStack_44 = uStack_b8._4_4_;
                uStack_40 = (undefined4)uStack_b0;
                uStack_3c = uVar5;
                Torappu_Battle_Ability_SetData_0x600f64f(lVar1);
              }
              uVar16 = (ulonglong)(uVar13 + 1);
              uVar15 = uVar15 + 1;
              lVar12 = lVar12 + 8;
            } while ((longlong)uVar15 < uStack_78);
          }
          bVar17 = DAT_188c91c24 == '\0';
          *(undefined1 *)((longlong)param_1 + 0x9b) = *(undefined1 *)((longlong)param_1 + 0x23);
          *(undefined1 *)(param_1 + 0x13) = 0;
          if (bVar17) {
            FUN_18048bf00(&DAT_188925ba0);
            DAT_188c91c24 = '\x01';
          }
          lVar12 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
          if (lVar12 == 0) {
            lVar12 = param_1[0x23];
          }
          else {
            lVar12 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar12,param_1,0);
          }
          if (lVar12 != 0) {
            uVar21 = Torappu_Blackboard_GetIntOrDefault_0x6007874
                               (lVar12,_DAT_188836150,(int)param_1[3],0,0);
            bVar17 = DAT_188c91c24 == '\0';
            *(undefined4 *)((longlong)param_1 + 0xcc) = uVar21;
            if (bVar17) {
              FUN_18048bf00(&DAT_188925ba0);
              DAT_188c91c24 = '\x01';
            }
            lVar12 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
            if (lVar12 == 0) {
              lVar12 = param_1[0x23];
            }
            else {
              lVar12 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar12,param_1,0);
            }
            if (lVar12 != 0) {
              uVar21 = Torappu_Blackboard_GetIntOrDefault_0x6007874
                                 (lVar12,_DAT_188835620,0xffffffff,0,0);
              bVar17 = DAT_188c91c24 == '\0';
              *(undefined4 *)((longlong)param_1 + 0x9c) = uVar21;
              if (bVar17) {
                FUN_18048bf00(&DAT_188925ba0);
                DAT_188c91c24 = '\x01';
              }
              lVar12 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
              if (lVar12 == 0) {
                lVar12 = param_1[0x23];
              }
              else {
                lVar12 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar12,param_1,0);
              }
              if (lVar12 != 0) {
                Torappu_Blackboard_GenerateBlackboardWithPrefix_0x600787a
                          (lVar12,param_1 + 0x17,_DAT_1887fc850,0);
                lVar12 = param_1[0x10];
                if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                cVar4 = FUN_186b63a70(lVar12,0,0);
                if (cVar4 != '\0') {
                  plVar2 = (longlong *)param_1[0x10];
                  if (DAT_188c91c24 == '\0') {
                    FUN_18048bf00(&DAT_188925ba0);
                    DAT_188c91c24 = '\x01';
                  }
                  lVar12 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
                  if (lVar12 == 0) {
                    lVar12 = param_1[0x23];
                  }
                  else {
                    lVar12 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar12,param_1,0);
                  }
                  if (plVar2 == (longlong *)0x0) goto LAB_180958f88;
                  if (DAT_188ccc7f0 != '\0') {
                    func_0x000180446d00(*plVar2);
                  }
                  (**(code **)(*plVar2 + 0x180))
                            (plVar2,param_3,lVar12,0,*(undefined8 *)(*plVar2 + 0x188));
                }
                iVar6 = FUN_1844afc00(param_1[0x1b],_DAT_18896a750);
                uVar16 = uVar14;
                if (0 < iVar6) {
                  do {
                    lVar12 = param_1[0x1b];
                    if (lVar12 == 0) goto LAB_180958f88;
                    if (*(uint *)(lVar12 + 0x18) <= (uint)uVar14) {
LAB_180958f82:
                      FUN_18048c0a0();
                      pcVar3 = (code *)swi(3);
                      (*pcVar3)();
                      return;
                    }
                    plVar2 = *(longlong **)(lVar12 + lVar8);
                    if (DAT_188c91c24 == '\0') {
                      FUN_18048bf00(&DAT_188925ba0);
                      DAT_188c91c24 = '\x01';
                    }
                    lVar12 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
                    if (lVar12 == 0) {
                      lVar12 = param_1[0x23];
                    }
                    else {
                      lVar12 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar12,param_1,0)
                      ;
                    }
                    if (plVar2 == (longlong *)0x0) goto LAB_180958f88;
                    if (DAT_188ccc7f0 != '\0') {
                      func_0x000180446d00(*plVar2);
                    }
                    (**(code **)(*plVar2 + 400))(plVar2,lVar12);
                    uVar14 = (ulonglong)((uint)uVar14 + 1);
                    uVar16 = uVar16 + 1;
                    lVar8 = lVar8 + 8;
                  } while ((longlong)uVar16 < (longlong)iVar6);
                }
                plVar2 = (longlong *)param_1[0x11];
                if (plVar2 == (longlong *)0x0) {
                  return;
                }
                if (DAT_188c91c24 == '\0') {
                  FUN_18048bf00(&DAT_188925ba0);
                  DAT_188c91c24 = '\x01';
                }
                lVar8 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x180);
                if (lVar8 == 0) {
                  lVar8 = param_1[0x23];
                }
                else {
                  lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar8,param_1,0);
                }
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*plVar2);
                }
                (**(code **)(*plVar2 + 0x180))
                          (plVar2,param_3,lVar8,0,*(undefined8 *)(*plVar2 + 0x188));
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_180958f88:
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


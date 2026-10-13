
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_Init_0x6010441
               (longlong *param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined8 param_6,undefined4 param_7,longlong param_8)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  longlong lVar5;
  char cVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong lVar12;
  longlong lVar13;
  ulonglong uVar14;
  undefined8 *puVar15;
  longlong *plVar16;
  undefined8 uVar17;
  ulonglong uVar18;
  bool bVar19;
  float fVar20;
  undefined4 uVar21;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined4 uStack_78;
  undefined1 auStack_68 [64];
  
  if (DAT_188c908d1 == '\0') {
    FUN_18048bf00(&DAT_188868850);
    FUN_18048bf00(&DAT_188868618);
    FUN_18048bf00(&DAT_1888eb668);
    FUN_18048bf00(&DAT_188849538);
    FUN_18048bf00(&DAT_188849770);
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_1888703f8);
    FUN_18048bf00(&DAT_188870aa8);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_188937ba8);
    FUN_18048bf00(&DAT_1888e0148);
    DAT_188c908d1 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  uVar18 = 0;
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x828);
  if (lVar10 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp3059_0x6001653
              (lVar10,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
    return;
  }
  bVar19 = DAT_188c908e1 == '\0';
  *(undefined1 *)((longlong)param_1 + 0x89) = 1;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  if (bVar19) {
    FUN_18048bf00(&DAT_1888ccc00);
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_18884c880);
    DAT_188c908e1 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x8a8);
  if (lVar10 == 0) {
    if (*(int *)(_DAT_1888ccc00 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar10 = Torappu_AttributesData_get_fieldMetas_0x6007843(0);
    if (((lVar10 == 0) || (lVar10 = FUN_184afcf00(lVar10,0,_DAT_18884c880), lVar10 == 0)) ||
       (plVar16 = *(longlong **)(lVar10 + 0x10), plVar16 == (longlong *)0x0)) goto LAB_1806f5d01;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar16);
    }
    uVar11 = (**(code **)(*plVar16 + 0x310))(plVar16,param_2,*(undefined8 *)(*plVar16 + 0x318));
    fVar20 = (float)Torappu_AttributesData_ReadAttributesField_0x6007847(uVar11,0);
    if (fVar20 <= 0.0) {
      if (*(int *)(_DAT_1888ccc00 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      Torappu_AttributesData_WriteAttributesField_0x6007848(plVar16,param_2,0x3f800000,0);
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar10,param_1,param_2,0);
  }
  lVar10 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
  if (lVar10 != 0) {
    Torappu_Battle_Attributes_Reset_0x600fb0d(lVar10,param_2,0);
    lVar10 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
    if (param_8 != 0) {
      lVar12 = Torappu_SpData_get_incrementsForAllSpTypes_0x6008054(param_8,0);
      uVar7 = func_0x0001844dc660(0,_DAT_188870aa8);
      if (lVar12 != 0) {
        if (*(uint *)(lVar12 + 0x18) <= uVar7) {
LAB_1806f5cfb:
          FUN_18048c0a0();
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        uVar21 = *(undefined4 *)(lVar12 + 0x20 + (longlong)(int)uVar7 * 4);
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar11 = func_0x0001866fdad0(uVar21,0);
        if (lVar10 != 0) {
          uVar21 = 0;
          Torappu_Battle_Attributes_OverwriteRawData_0x600fb0e(lVar10,0xe,uVar11,1,0);
          lVar10 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
          if (lVar10 != 0) {
            uVar11 = *(undefined8 *)(lVar10 + 0x80);
            lVar12 = func_0x00018045cfe0(_DAT_1888eb668);
            if (lVar12 != 0) {
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(*param_1);
              }
              FUN_185880ed0(lVar12,param_1,*(undefined8 *)(*param_1 + 0x928),0);
              lVar12 = System_Delegate_Combine_0x6001132(uVar11,lVar12,0);
              uVar11 = _DAT_1888eb668;
              if (lVar12 == 0) {
                *(undefined8 *)(lVar10 + 0x80) = 0;
                uVar14 = uVar18;
              }
              else {
                lVar13 = func_0x00018048b9f0(lVar12,_DAT_1888eb668);
                if (lVar13 == 0) {
                  FUN_18048ba10(lVar12,uVar11);
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
                *(longlong *)(lVar10 + 0x80) = lVar13;
                uVar11 = _DAT_1888eb668;
                uVar14 = func_0x00018048b9f0(lVar12,_DAT_1888eb668);
                if (uVar14 == 0) {
                  FUN_18048ba10(lVar12,uVar11);
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
              }
              func_0x00018048b9e0(lVar10 + 0x80,uVar14);
              lVar10 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
              if (lVar10 != 0) {
                uVar11 = *(undefined8 *)(lVar10 + 0x88);
                lVar12 = func_0x00018045cfe0(_DAT_188868850);
                if (lVar12 != 0) {
                  Torappu_SocketNetwork_Msg_ProcRespFail__ctor_0x6008985
                            (lVar12,param_1,_DAT_188849770,0);
                  lVar12 = System_Delegate_Combine_0x6001132(uVar11,lVar12,0);
                  uVar11 = _DAT_188868850;
                  if (lVar12 == 0) {
                    *(undefined8 *)(lVar10 + 0x88) = 0;
                    uVar14 = uVar18;
                  }
                  else {
                    lVar13 = func_0x00018048b9f0(lVar12,_DAT_188868850);
                    if (lVar13 == 0) {
                      FUN_18048ba10(lVar12,uVar11);
                      pcVar1 = (code *)swi(3);
                      (*pcVar1)();
                      return;
                    }
                    *(longlong *)(lVar10 + 0x88) = lVar13;
                    uVar11 = _DAT_188868850;
                    uVar14 = func_0x00018048b9f0(lVar12,_DAT_188868850);
                    if (uVar14 == 0) {
                      FUN_18048ba10(lVar12,uVar11);
                      pcVar1 = (code *)swi(3);
                      (*pcVar1)();
                      return;
                    }
                  }
                  func_0x00018048b9e0(lVar10 + 0x88,uVar14);
                  lVar10 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
                  if (lVar10 != 0) {
                    uVar11 = *(undefined8 *)(lVar10 + 0x90);
                    lVar12 = func_0x00018045cfe0(_DAT_188868618);
                    if (lVar12 != 0) {
                      Torappu_SocketNetwork_Msg_ProcRespFail__ctor_0x6008985
                                (lVar12,param_1,_DAT_188849538,0);
                      lVar12 = System_Delegate_Combine_0x6001132(uVar11,lVar12,0);
                      uVar11 = _DAT_188868618;
                      if (lVar12 == 0) {
                        *(undefined8 *)(lVar10 + 0x90) = 0;
                        uVar14 = uVar18;
                      }
                      else {
                        lVar13 = func_0x00018048b9f0(lVar12,_DAT_188868618);
                        if (lVar13 == 0) {
                          FUN_18048ba10(lVar12,uVar11);
                          pcVar1 = (code *)swi(3);
                          (*pcVar1)();
                          return;
                        }
                        *(longlong *)(lVar10 + 0x90) = lVar13;
                        uVar11 = _DAT_188868618;
                        uVar14 = func_0x00018048b9f0(lVar12,_DAT_188868618);
                        if (uVar14 == 0) {
                          FUN_18048ba10(lVar12,uVar11);
                          pcVar1 = (code *)swi(3);
                          (*pcVar1)();
                          return;
                        }
                      }
                      func_0x00018048b9e0(lVar10 + 0x90,uVar14);
                      puVar15 = (undefined8 *)
                                Torappu_SpData_get_maxSp_0x6008052(&uStack_88,param_8,0);
                      uStack_88 = *puVar15;
                      uStack_80 = puVar15[1];
                      uStack_78 = *(undefined4 *)(puVar15 + 2);
                      if (*(int *)(_DAT_188937ba8 + 0xe0) == 0) {
                        func_0x00018048c140();
                      }
                      CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3
                                (&uStack_88,0);
                      uStack_78 = *(undefined4 *)(param_8 + 0x58);
                      uStack_88 = *(undefined8 *)(param_8 + 0x48);
                      uStack_80 = *(undefined8 *)(param_8 + 0x50);
                      CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3
                                (&uStack_88,0);
                      plVar16 = (longlong *)Torappu_ObscuredFP_op_Implicit_0x60002e5(auStack_68);
                      lVar12 = plVar16[1];
                      lVar13 = plVar16[2];
                      uVar8 = *(undefined4 *)((longlong)plVar16 + 0x14);
                      lVar5 = plVar16[3];
                      uVar2 = *(undefined4 *)((longlong)plVar16 + 0x1c);
                      lVar10 = plVar16[4];
                      param_1[10] = *plVar16;
                      param_1[0xb] = lVar12;
                      *(int *)(param_1 + 0xc) = (int)lVar13;
                      *(undefined4 *)((longlong)param_1 + 100) = uVar8;
                      *(int *)(param_1 + 0xd) = (int)lVar5;
                      *(undefined4 *)((longlong)param_1 + 0x6c) = uVar2;
                      param_1[0xe] = lVar10;
                      puVar15 = (undefined8 *)
                                Torappu_SpData_get_maxSp_0x6008052(auStack_68,param_8,0);
                      uStack_88 = *puVar15;
                      uStack_80 = puVar15[1];
                      uStack_78 = *(undefined4 *)(puVar15 + 2);
                      uVar8 = CodeStage_AntiCheat_ObscuredTypes_ObscuredInt_op_Implicit_0x6002ea3
                                        (&uStack_88,0);
                      Torappu_Battle_Entity_set_maxSp_0x601038b(param_1,uVar8,0);
                      lVar10 = param_1[0x1f];
                      if (lVar10 != 0) {
                        if (DAT_188c90941 == '\0') {
                          FUN_18048bf00(&DAT_18885a700);
                          FUN_18048bf00(&DAT_188874308);
                          DAT_188c90941 = '\x01';
                        }
                        lVar12 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x50);
                        if (lVar12 == 0) {
                          *(longlong **)(lVar10 + 0x18) = param_1;
                          func_0x00018048b9e0(lVar10 + 0x18,param_1);
                          *(undefined4 *)(lVar10 + 0x10) = *(undefined4 *)(param_8 + 0x10);
                          uVar2 = *(undefined4 *)(param_8 + 0x38);
                          uVar3 = *(undefined4 *)(param_8 + 0x3c);
                          uVar4 = *(undefined4 *)(param_8 + 0x40);
                          uVar8 = *(undefined4 *)(param_8 + 0x44);
                          *(undefined4 *)(lVar10 + 0x20) = *(undefined4 *)(param_8 + 0x34);
                          *(undefined4 *)(lVar10 + 0x24) = uVar2;
                          *(undefined4 *)(lVar10 + 0x28) = uVar3;
                          *(undefined4 *)(lVar10 + 0x2c) = uVar4;
                          *(undefined4 *)(lVar10 + 0x30) = uVar8;
                          uVar11 = Torappu_SpData_get_incrementsForAllSpTypes_0x6008054(param_8,0);
                          if (*(longlong *)(lVar10 + 0x38) == 0) goto LAB_1806f5d01;
                          System_Array_Copy_0x6000ea3
                                    (uVar11,*(undefined8 *)(lVar10 + 0x38),
                                     *(undefined4 *)(*(longlong *)(lVar10 + 0x38) + 0x18),0);
                          if (*(longlong *)(lVar10 + 0x18) == 0) goto LAB_1806f5d01;
                          cVar6 = Torappu_Battle_Entity_get_canRecoverSp_0x601036a
                                            (*(longlong *)(lVar10 + 0x18),0);
                          if (cVar6 == '\0') {
                            SpController_MarkInvalid_0x60104b9(lVar10,0);
                          }
                          else {
                            lVar12 = *(longlong *)(lVar10 + 0x40);
                            if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                              func_0x00018048c140(_DAT_18885a700);
                            }
                            uVar11 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x20);
                            if (*(longlong *)(lVar10 + 0x18) == 0) goto LAB_1806f5d01;
                            uVar17 = Torappu_Battle_Entity_get_spRecoveryPerSec_0x60103ae
                                               (*(longlong *)(lVar10 + 0x18),0);
                            uVar11 = Torappu_FP_op_Division_0x6000305(uVar11,uVar17,0);
                            if (lVar12 == 0) goto LAB_1806f5d01;
                            Torappu_PeriodicTimer_Reset_0x6006576(lVar12,uVar11,1,0);
                          }
                        }
                        else {
                          uVar21 = 0;
                          XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84
                                    (lVar12,lVar10,param_1,param_8,0);
                        }
                        if (param_1[0x20] != 0) {
                          EPController_Reset_0x60104c5(param_1[0x20],param_1,0);
                          if (param_1[0x21] != 0) {
                            ShieldUIController_Reset_0x60104d7(param_1[0x21],param_1,0);
                            Torappu_Battle_Entity_set_pathMotionMode_0x6010345(param_1,param_5,0);
                            uVar8 = Torappu_Battle_Entity_get_pathMotionMode_0x6010344(param_1,0);
                            Torappu_Battle_Entity_set_changeableMotionMode_0x6010346
                                      (param_1,uVar8,0);
                            cVar6 = Torappu_Battle_Entity_get_canRecoverHp_0x6010369(param_1,0);
                            lVar10 = param_1[0x18];
                            if (cVar6 == '\0') {
                              if (lVar10 == 0) goto LAB_1806f5d01;
                              Torappu_PeriodicTimer_MarkInvalid_0x6006579(lVar10,0);
                            }
                            else {
                              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                                func_0x00018048c140(_DAT_18885a700);
                              }
                              uVar11 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x20);
                              uVar17 = Torappu_Battle_Entity_get_sumUpHpRecoveryPerSec_0x60103ad
                                                 (param_1,0);
                              uVar11 = Torappu_FP_op_Division_0x6000305(uVar11,uVar17,0);
                              if (lVar10 == 0) goto LAB_1806f5d01;
                              Torappu_PeriodicTimer_Reset_0x6006576(lVar10,uVar11,1,0);
                            }
                            cVar6 = Torappu_Battle_Entity_get_canRecoverEp_0x601036b(param_1,0);
                            lVar10 = param_1[0x1b];
                            if (cVar6 == '\0') {
                              if (lVar10 == 0) goto LAB_1806f5d01;
                              Torappu_PeriodicTimer_MarkInvalid_0x6006579(lVar10,0);
                            }
                            else {
                              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                                func_0x00018048c140(_DAT_18885a700);
                              }
                              uVar11 = *(undefined8 *)(*(longlong *)(_DAT_18885a700 + 0xb8) + 0x20);
                              if (DAT_188c90846 == '\0') {
                                FUN_18048bf00(&DAT_188841368);
                                DAT_188c90846 = '\x01';
                              }
                              if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
                                func_0x00018048c140(_DAT_188841368);
                              }
                              lVar12 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x3c8);
                              if (lVar12 == 0) {
                                lVar12 = Torappu_Battle_Entity_get_attributes_0x6010337(param_1,0);
                                if (lVar12 == 0) goto LAB_1806f5d01;
                                uVar17 = Torappu_Battle_Attributes_GetValue_0x600fb15(lVar12,0x1d,0)
                                ;
                              }
                              else {
                                uVar17 = XLua_DelegateBridge___Gen_Delegate_Imp2620_0x600149c
                                                   (lVar12,param_1,0);
                              }
                              uVar11 = Torappu_FP_op_Division_0x6000305(uVar11,uVar17,0);
                              if (lVar10 == 0) goto LAB_1806f5d01;
                              Torappu_PeriodicTimer_Reset_0x6006576(lVar10,uVar11,1,0);
                            }
                            Torappu_Battle_BObject_Init_0x600fe06
                                      (param_1,param_3,param_4,param_6,CONCAT44(uVar21,param_7),0);
                            if (DAT_188ccc7f0 != '\0') {
                              func_0x000180446d00(*param_1);
                            }
                            lVar10 = (**(code **)(*param_1 + 0x6a0))
                                               (param_1,*(undefined8 *)(*param_1 + 0x6a8));
                            param_1[8] = lVar10;
                            if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                              func_0x00018048c140();
                            }
                            lVar10 = func_0x0001866fdac0(0,0);
                            param_1[9] = lVar10;
                            uVar11 = func_0x0001866fdac0(0,0);
                            Torappu_Battle_Entity_set_minusHp_0x601038e(param_1,uVar11,0);
                            lVar10 = func_0x0001866fdac0(0,0);
                            if (DAT_188c90827 == '\0') {
                              FUN_18048bf00(&DAT_188841368);
                              DAT_188c90827 = '\x01';
                            }
                            if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
                              func_0x00018048c140(_DAT_188841368);
                            }
                            lVar12 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x2d0);
                            if (lVar12 == 0) {
                              param_1[0x31] = lVar10;
                            }
                            else {
                              XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b
                                        (lVar12,param_1,lVar10,0);
                            }
                            *(undefined1 *)((longlong)param_1 + 0x8a) = 0;
                            iVar9 = func_0x0001844dc660(6,_DAT_1888703f8);
                            if (0 < iVar9) {
                              lVar10 = 0x20;
                              do {
                                lVar12 = param_1[0x10];
                                if (DAT_188ccc7f0 != '\0') {
                                  func_0x000180446d00(*param_1);
                                }
                                uVar11 = (**(code **)(*param_1 + 0x640))
                                                   (param_1,*(undefined8 *)(*param_1 + 0x648));
                                if (lVar12 == 0) goto LAB_1806f5d01;
                                if (*(uint *)(lVar12 + 0x18) <= (uint)uVar18) goto LAB_1806f5cfb;
                                *(undefined8 *)(lVar10 + lVar12) = uVar11;
                                uVar7 = (uint)uVar18 + 1;
                                uVar18 = (ulonglong)uVar7;
                                lVar10 = lVar10 + 8;
                                iVar9 = func_0x0001844dc660(6,_DAT_1888703f8);
                              } while ((int)uVar7 < iVar9);
                            }
                            lVar10 = FUN_185337c50(_DAT_1888e0148);
                            uVar11 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030
                                               (param_1,0);
                            if (lVar10 != 0) {
                              lVar10 = Torappu_Battle_Map_GetTile_0x60111be(lVar10,uVar11,0);
                              if (DAT_188c907f0 == '\0') {
                                FUN_18048bf00(&DAT_188841368);
                                DAT_188c907f0 = '\x01';
                              }
                              if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
                                func_0x00018048c140(_DAT_188841368);
                              }
                              lVar12 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x118);
                              if (lVar12 == 0) {
                                param_1[0x2c] = lVar10;
                                func_0x00018048b9e0(param_1 + 0x2c,lVar10);
                                return;
                              }
                              XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77
                                        (lVar12,param_1,lVar10,0);
                              return;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_1806f5d01:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BuffContainer_ClearWithWhiteList_0x600ff4f(longlong param_1,longlong param_2,char param_3)

{
  int iVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  undefined4 uVar5;
  longlong lVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  ushort uVar12;
  ulonglong uVar13;
  ushort uVar14;
  ulonglong in_stack_fffffffffffffef8;
  longlong *aplStack_f8 [2];
  longlong lStack_e8;
  undefined8 uStack_e0;
  longlong lStack_d8;
  longlong lStack_d0;
  longlong lStack_c8;
  longlong lStack_c0;
  longlong lStack_b8;
  longlong lStack_b0;
  longlong lStack_a8;
  longlong lStack_a0;
  longlong lStack_98;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined1 auStack_58 [48];
  
  lStack_d8 = param_1;
  if (DAT_188c903d1 == '\0') {
    FUN_18048bf00(&DAT_1888d5250);
    FUN_18048bf00(&DAT_18882b720);
    FUN_18048bf00(&DAT_188954c98);
    FUN_18048bf00(&DAT_1888cfcb0);
    FUN_18048bf00(&DAT_188959b58);
    FUN_18048bf00(&DAT_18892dce0);
    FUN_18048bf00(&DAT_1888c9280);
    FUN_18048bf00(0x18892e160);
    FUN_18048bf00(0x1888c9700);
    FUN_18048bf00(&DAT_1888c9940);
    FUN_18048bf00(&DAT_18892e3a0);
    FUN_18048bf00(&DAT_1888c8e00);
    FUN_18048bf00(&DAT_18892d860);
    FUN_18048bf00(&DAT_1888c8bc0);
    FUN_18048bf00(&DAT_188908578);
    FUN_18048bf00(&DAT_1888f6598);
    FUN_18048bf00(&DAT_1889237f0);
    FUN_18048bf00(&DAT_1889316a8);
    DAT_188c903d1 = '\x01';
  }
  aplStack_f8[0] = (longlong *)0x0;
  uStack_88 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  lVar6 = *(longlong *)(*(longlong *)(_DAT_1888d5250 + 0xb8) + 0x1c0);
  if (lVar6 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp265_0x6000b69(lVar6,param_1,param_2,param_3,0);
    return;
  }
  lVar6 = func_0x00018045cfe0(_DAT_1888f6598);
  lStack_b8 = lVar6;
  if (lVar6 != 0) {
    FUN_184d1bb80(lVar6,param_2,_DAT_1888c8e00);
    lStack_b0 = lVar6;
    lVar6 = func_0x00018045cfe0(_DAT_1888f6598);
    lStack_c8 = lVar6;
    if (lVar6 != 0) {
      FUN_1848f2320(lVar6,_DAT_1888c8bc0);
      lStack_d0 = lVar6;
      lStack_a8 = lVar6;
      lVar6 = func_0x00018045cfe0(_DAT_188908578);
      lStack_c0 = lVar6;
      if (lVar6 != 0) {
        FUN_1848f2320(lVar6,_DAT_18892d860);
        uVar14 = 0;
        lStack_a0 = lVar6;
        lStack_98 = lVar6;
        if (param_3 == '\0') {
          if (*(longlong *)(param_1 + 0x18) == 0) goto LAB_180664a7b;
          aplStack_f8[0] = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
          lStack_e8 = 0;
          uStack_e0 = aplStack_f8;
LAB_1806640b0:
          if (aplStack_f8[0] != (longlong *)0x0) {
            cVar4 = FUN_180005310(0,_DAT_188959b58);
            plVar3 = aplStack_f8[0];
            lVar6 = _DAT_1888cfcb0;
            if (cVar4 != '\0') {
              if (aplStack_f8[0] != (longlong *)0x0) goto code_r0x0001806640e2;
              goto LAB_180664a33;
            }
            if (aplStack_f8[0] != (longlong *)0x0) {
              FUN_180005310(0,_DAT_188954c98,aplStack_f8[0]);
            }
            goto LAB_180664278;
          }
LAB_180664a38:
          FUN_18048c0b0();
          FUN_180472d50();
LAB_180664a44:
          FUN_18048c0b0();
        }
        else {
LAB_180664278:
          lVar6 = lStack_b8;
          if (*(longlong *)(param_1 + 0x18) == 0) goto LAB_180664a7b;
          aplStack_f8[0] = (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
          lStack_e8 = 0;
          uStack_e0 = aplStack_f8;
          while (plVar3 = aplStack_f8[0], lVar9 = _DAT_188959b58, aplStack_f8[0] != (longlong *)0x0)
          {
            lVar10 = *aplStack_f8[0];
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(lVar10);
            }
            if (*(ushort *)(lVar10 + 0x12e) != 0) {
              uVar12 = uVar14;
              do {
                if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + (ulonglong)uVar12 * 0x10) == lVar9)
                {
                  puVar7 = (undefined8 *)
                           (((longlong)
                             *(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10) +
                            0x14) * 0x10 + lVar10);
                  goto LAB_180664329;
                }
                uVar12 = uVar12 + 1;
              } while (uVar12 < *(ushort *)(lVar10 + 0x12e));
            }
            puVar7 = (undefined8 *)FUN_180445cc0(plVar3,lVar9,0);
LAB_180664329:
            cVar4 = (*(code *)*puVar7)(plVar3,puVar7[1]);
            plVar3 = aplStack_f8[0];
            lVar9 = _DAT_1888cfcb0;
            if (cVar4 == '\0') {
              if (aplStack_f8[0] != (longlong *)0x0) {
                FUN_180005310(0,_DAT_188954c98,aplStack_f8[0]);
              }
              if (*(longlong *)(param_1 + 0x18) == 0) goto LAB_180664a7b;
              aplStack_f8[0] =
                   (longlong *)FUN_185a17960(*(longlong *)(param_1 + 0x18),_DAT_18882b720);
              lStack_e8 = 0;
              uStack_e0 = aplStack_f8;
              goto LAB_180664540;
            }
            if (aplStack_f8[0] == (longlong *)0x0) goto LAB_180664a44;
            lVar10 = *aplStack_f8[0];
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(lVar10);
            }
            uVar13 = 0;
            if (*(ushort *)(lVar10 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + uVar13 * 0x10) == lVar9) {
                  puVar7 = (undefined8 *)
                           (((longlong)*(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + uVar13 * 0x10) +
                            0x14) * 0x10 + lVar10);
                  goto LAB_1806643a9;
                }
                uVar12 = (short)uVar13 + 1;
                uVar13 = (ulonglong)uVar12;
              } while (uVar12 < *(ushort *)(lVar10 + 0x12e));
            }
            puVar7 = (undefined8 *)FUN_180445cc0(plVar3,lVar9,0);
LAB_1806643a9:
            puVar7 = (undefined8 *)(*(code *)*puVar7)(auStack_58,plVar3);
            uStack_78 = *puVar7;
            uStack_70 = puVar7[1];
            lVar9 = FUN_185159d80(&uStack_78,_DAT_1889316a8);
            if (lVar9 != 0) {
              uVar8 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar9,0);
              cVar4 = FUN_184d0ba50(lVar6,uVar8);
              if (cVar4 == '\0') {
                in_stack_fffffffffffffef8 = in_stack_fffffffffffffef8 & 0xffffffffffffff00;
                BuffContainer__FinishBuff_0x600ff5a(param_1,lVar9,0,1,in_stack_fffffffffffffef8,0);
              }
              else {
                uVar8 = Torappu_Battle_Buff_get_overrideKey_0x600fe20(lVar9,0);
                FUN_1805072d0(lStack_c8,uVar8,_DAT_1888c9280);
                uVar5 = Torappu_Battle_Buff_get_instanceUid_0x600fe22(lVar9,0);
                FUN_180007630(lStack_c0,uVar5);
              }
            }
          }
        }
        FUN_18048c0b0();
        FUN_180472d50();
LAB_180664a55:
        FUN_18048c0b0();
LAB_180664a5a:
        FUN_18048c0b0();
LAB_180664a5f:
        FUN_18048c0b0();
LAB_180664a64:
        FUN_18048c0b0();
        goto LAB_180664a69;
      }
    }
  }
LAB_180664a7b:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
code_r0x0001806640e2:
  lVar9 = *aplStack_f8[0];
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(lVar9);
  }
  if (*(ushort *)(lVar9 + 0x12e) != 0) {
    uVar12 = uVar14;
    do {
      if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar12 * 0x10) == lVar6) {
        puVar7 = (undefined8 *)
                 (((longlong)*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10) +
                  0x14) * 0x10 + lVar9);
        goto LAB_180664149;
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < *(ushort *)(lVar9 + 0x12e));
  }
  puVar7 = (undefined8 *)FUN_180445cc0(plVar3,lVar6,0);
LAB_180664149:
  puVar7 = (undefined8 *)(*(code *)*puVar7)(auStack_58,plVar3,puVar7[1]);
  uStack_88 = *puVar7;
  uStack_80 = puVar7[1];
  lVar6 = FUN_185159d80(&uStack_88,_DAT_1889316a8);
  if (lVar6 != 0) {
    uVar8 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar6,0);
    if (param_2 == 0) {
      FUN_18048c0b0();
LAB_180664a33:
      FUN_18048c0b0();
      goto LAB_180664a38;
    }
    cVar4 = FUN_184d0ba50(param_2,uVar8,_DAT_1888c9940);
    if ((cVar4 == '\0') && (*(char *)(lVar6 + 0x1f0) != '\0')) {
      uVar8 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar6,0);
      FUN_1805072d0(lStack_b8,uVar8,_DAT_1888c9280);
    }
  }
  goto LAB_1806640b0;
joined_r0x0001806648a6:
  do {
    do {
      iVar1 = iVar1 + -1;
      if (iVar1 < 1) {
LAB_18066496d:
        lVar11 = lStack_a0;
        lVar9 = lStack_d8;
        BuffContainer__ClearBuffOverrideMapWithWhiteList_0x600ff50(lStack_d8,lStack_d0,0);
        BuffContainer__ClearBuffUidMapWithWhiteList_0x600ff51(lVar9,lVar11,0);
        *(int *)(lStack_c8 + 0x1c) = *(int *)(lStack_c8 + 0x1c) + 1;
        iVar1 = *(int *)(lStack_c8 + 0x18);
        *(undefined4 *)(lStack_c8 + 0x18) = 0;
        if (iVar1 < 1) {
          *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
        }
        else {
          System_Array_Clear_0x6000ea1(*(undefined8 *)(lStack_c8 + 0x10),0,iVar1,0);
          *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
          lVar10 = lVar11;
        }
        *(undefined4 *)(lVar10 + 0x18) = 0;
        *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
        iVar1 = *(int *)(lVar6 + 0x18);
        *(undefined4 *)(lVar6 + 0x18) = 0;
        if (0 < iVar1) {
          System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar6 + 0x10),0,iVar1,0);
        }
        return;
      }
      if (*(longlong *)(lVar9 + 0x10) == 0) goto LAB_180664a75;
      FUN_184ad2ef0(&lStack_98,*(longlong *)(lVar9 + 0x10),iVar1,_DAT_1888ddaf8);
      lStack_e8 = lStack_98;
      uStack_e0 = (longlong **)CONCAT44(uStack_8c,uStack_90);
      lVar11 = FUN_185159d80(&lStack_e8,_DAT_1889316a8);
    } while (lVar11 == 0);
    uVar8 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar11,0);
    cVar4 = FUN_184d0ba50(lVar6,uVar8,_DAT_1888c9940);
  } while (cVar4 != '\0');
  cVar4 = Torappu_Battle_Buff_get_isFinished_0x600fe4d(lVar11,0);
  if (cVar4 != '\0') {
    if (*(longlong *)(lVar9 + 0x10) == 0) {
LAB_180664a75:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_184acd910(*(longlong *)(lVar9 + 0x10),iVar1,_DAT_1888dd438);
    goto joined_r0x0001806648a6;
  }
  Torappu_Battle_Buff_set_needRemove_0x600fe4f(lVar11,1,0);
  goto joined_r0x0001806648a6;
LAB_180664540:
  plVar3 = aplStack_f8[0];
  lVar9 = _DAT_188959b58;
  if (aplStack_f8[0] != (longlong *)0x0) {
    lVar10 = *aplStack_f8[0];
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar10);
    }
    if (*(ushort *)(lVar10 + 0x12e) != 0) {
      uVar12 = uVar14;
      do {
        if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + (ulonglong)uVar12 * 0x10) == lVar9) {
          puVar7 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10)
                    + 0x14) * 0x10 + lVar10);
          goto LAB_1806645b9;
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 < *(ushort *)(lVar10 + 0x12e));
    }
    puVar7 = (undefined8 *)FUN_180445cc0(plVar3,lVar9,0);
LAB_1806645b9:
    cVar4 = (*(code *)*puVar7)(plVar3,puVar7[1]);
    plVar3 = aplStack_f8[0];
    lVar9 = _DAT_1888cfcb0;
    if (cVar4 == '\0') {
      if (aplStack_f8[0] != (longlong *)0x0) {
        FUN_180005310(0,_DAT_188954c98,aplStack_f8[0]);
      }
      lVar10 = lStack_c0;
      lVar9 = *(longlong *)(param_1 + 0x18);
      if (lVar9 == 0) goto LAB_180664a7b;
      if (DAT_188c9038a == '\0') {
        FUN_18048bf00(&DAT_1888d5490);
        FUN_18048bf00(&DAT_1888c9940);
        FUN_18048bf00(&DAT_1888dd438);
        FUN_18048bf00(0x1888dd8b8);
        FUN_18048bf00(&DAT_1888ddaf8);
        FUN_18048bf00(&DAT_1889316a8);
        DAT_188c9038a = '\x01';
      }
      lStack_e8 = 0;
      uStack_e0 = (longlong **)0x0;
      lVar11 = *(longlong *)(*(longlong *)(_DAT_1888d5490 + 0xb8) + 0x10);
      if (lVar11 != 0) {
        XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar11,lVar9,lVar6,0);
        goto LAB_18066496d;
      }
      if (*(longlong *)(lVar9 + 0x10) == 0) goto LAB_180664a75;
      iVar1 = *(int *)(*(longlong *)(lVar9 + 0x10) + 0x18);
      goto joined_r0x0001806648a6;
    }
    if (aplStack_f8[0] == (longlong *)0x0) goto LAB_180664a64;
    lVar10 = *aplStack_f8[0];
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar10);
    }
    uVar13 = 0;
    if (*(ushort *)(lVar10 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + uVar13 * 0x10) == lVar9) {
          puVar7 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + uVar13 * 0x10) + 0x14) *
                    0x10 + lVar10);
          goto LAB_180664639;
        }
        uVar12 = (short)uVar13 + 1;
        uVar13 = (ulonglong)uVar12;
      } while (uVar12 < *(ushort *)(lVar10 + 0x12e));
    }
    puVar7 = (undefined8 *)FUN_180445cc0(plVar3,lVar9,0);
LAB_180664639:
    puVar7 = (undefined8 *)(*(code *)*puVar7)(auStack_58,plVar3);
    uStack_68 = *puVar7;
    uStack_60 = puVar7[1];
    lVar9 = FUN_185159d80(&uStack_68,_DAT_1889316a8);
    if ((lVar9 != 0) && (*(char *)(lVar9 + 0x1fb) == '\0')) {
      uVar5 = Torappu_Battle_Buff_get_instanceUid_0x600fe22(lVar9,0);
      lVar10 = lStack_c0;
      cVar4 = FUN_184dbb210(lStack_c0,uVar5);
      if (cVar4 == '\0') {
        uVar8 = Torappu_Battle_Buff_get_key_0x600fe1d(lVar9,0);
        cVar4 = FUN_184d0ba50(lVar6,uVar8,_DAT_1888c9940);
        if (cVar4 == '\0') {
          lVar10 = BuffContainer_get_owner_0x600ff17(param_1,0);
          if (lVar10 == 0) goto LAB_180664a5f;
          lVar10 = Torappu_Battle_Entity_get_attributes_0x6010337(lVar10,0);
          if (lVar10 == 0) goto LAB_180664a5a;
          Torappu_Battle_Attributes_RemoveModifier_0x600fb13(lVar10,lVar9,0);
          lVar10 = BuffContainer_get_pool_0x600ff1c(param_1,0);
          if (lVar10 == 0) goto LAB_180664a55;
          FUN_185158320(lVar10,lVar9);
        }
        else {
          uVar8 = Torappu_Battle_Buff_get_overrideKey_0x600fe20(lVar9);
          FUN_1805072d0(lStack_c8,uVar8,_DAT_1888c9280);
          uVar5 = Torappu_Battle_Buff_get_instanceUid_0x600fe22(lVar9,0);
          FUN_180007630(lVar10,uVar5);
        }
      }
    }
    goto LAB_180664540;
  }
LAB_180664a69:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


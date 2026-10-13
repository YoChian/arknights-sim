
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Unit_OnTick_0x6012f84(longlong param_1,undefined8 param_2)

{
  float fVar1;
  undefined4 uVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong lVar10;
  undefined8 *puVar11;
  float *pfVar12;
  float fVar13;
  undefined8 uStackX_20;
  undefined8 uStack_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c92c05 == '\0') {
    uStack_30 = 0x180acbdd5;
    FUN_18048bf00(&DAT_188932ce8);
    uStack_30 = 0x180acbde1;
    FUN_18048bf00(&DAT_188805040);
    DAT_188c92c05 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x458);
  if (lVar7 != 0) {
    uStack_30 = 0x180acbe8e;
    XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b(lVar7,param_1,param_2,0);
    return;
  }
  uStack_30 = 0x180acbe10;
  Torappu_Battle_Entity_OnTick_0x601048a(param_1,param_2,0);
  uVar9 = *(undefined8 *)(param_1 + 0x1c0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    uStack_30 = 0x180acbe2c;
    func_0x00018048c140();
  }
  uStack_30 = 0x180acbe39;
  cVar4 = FUN_186b63a70(uVar9,0,0);
  if (cVar4 == '\0') {
    return;
  }
  if (*(longlong *)(param_1 + 0x1c0) == 0) {
LAB_180acbe99:
    uStack_30 = 0x180acbe9e;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStack_30 = 0x180acbe50;
  lVar7 = FUN_186b59d80(*(longlong *)(param_1 + 0x1c0),0);
  if (lVar7 == 0) goto LAB_180acbe99;
  uStack_30 = 0x180acbe5f;
  cVar4 = FUN_186b5c980(lVar7,0);
  if (cVar4 == '\0') {
    return;
  }
  lVar7 = *(longlong *)(param_1 + 0x1c0);
  if (lVar7 == 0) goto LAB_180acbe99;
  if (cRam0000000188c92de7 == '\0') {
    FUN_18048bf00(0x188858948);
    FUN_18048bf00(0x1888c3c38);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(0x18894de60);
    FUN_18048bf00(0x1888d3908);
    cRam0000000188c92de7 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(lRam000000018894de60 + 0xb8) + 0x18);
  if (lVar8 != 0) {
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar9 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar5 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar10 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar10 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar10,uVar9,lVar7,0);
          uStack_48 = 0;
          iVar6 = FUN_183f22380(uVar9,1,0,iVar5);
          if (iVar6 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar9,iVar5 + -1,0);
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar5 + -1,0);
            goto code_r0x0001833100e8;
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
  uVar9 = *(undefined8 *)(lVar7 + 0x58);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar4 = FUN_186b638d0(uVar9,0,0);
  if (cVar4 == '\0') {
    lVar8 = FUN_185337c50(uRam00000001888d3908);
    if ((lVar8 == 0) ||
       (lVar8 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar8,0), lVar8 == 0))
    goto DAT_180b06048;
    cVar4 = FUN_1805ff0e0(lVar8,*(undefined8 *)(lVar7 + 0x58),0x10,0);
    if (cVar4 == '\0') {
      return;
    }
  }
  if (*(char *)(lVar7 + 0x21) != '\0') {
    if (*(char *)(lVar7 + 0x48) != '\0') {
      FUN_180b06660(lVar7,0);
    }
    if (*(char *)(lVar7 + 0x49) != '\0') {
      uVar9 = *(undefined8 *)(lVar7 + 0x70);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar4 = FUN_186b63a70(uVar9,0,0);
      if (cVar4 != '\0') {
        if (*(longlong *)(lVar7 + 0x70) == 0) goto DAT_180b06048;
        uVar9 = FUN_180005610(0x14);
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar4 = FUN_186b63a70(uVar9,0,0);
        if (cVar4 != '\0') {
          lVar8 = FUN_186b59e30(lVar7,0);
          if ((((*(longlong *)(lVar7 + 0x70) != 0) && (lVar10 = FUN_180005610(0x14), lVar10 != 0))
              && (lVar10 = FUN_186b59e30(lVar10,0), lVar10 != 0)) &&
             (puVar11 = (undefined8 *)FUN_186b752e0(&uStack_38,lVar10,0), lVar8 != 0)) {
            uStack_48 = *puVar11;
            uStack_40 = *(undefined4 *)(puVar11 + 1);
            FUN_186b75b30(lVar8,&uStack_48,0);
            goto code_r0x000180b05e1b;
          }
          goto DAT_180b06048;
        }
      }
    }
    uVar9 = *(undefined8 *)(lVar7 + 0x28);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar4 = FUN_186b63a70(uVar9,0,0);
    if (cVar4 != '\0') {
      uVar9 = *(undefined8 *)(lVar7 + 0x40);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar4 = FUN_186b63a70(uVar9,0,0);
      if (cVar4 != '\0') {
        lVar8 = FUN_186b59e30(lVar7,0);
        if (lVar8 != 0) {
          puVar11 = (undefined8 *)FUN_186b74fb0(&uStack_38,lVar8,0);
          uStack_48 = *puVar11;
          uVar2 = *(undefined4 *)(puVar11 + 1);
          if (*(longlong *)(lVar7 + 0x38) != 0) {
            iVar5 = func_0x0001805f22b0(*(longlong *)(lVar7 + 0x38),0);
            if (((*(longlong *)(lVar7 + 0x40) != 0) &&
                (lVar10 = *(longlong *)(*(longlong *)(lVar7 + 0x40) + 0x40), lVar10 != 0)) &&
               (*(longlong *)(lVar7 + 0x30) != 0)) {
              fVar1 = *(float *)(lVar10 + 0x74);
              pfVar12 = (float *)FUN_186b750f0(&uStack_38,*(longlong *)(lVar7 + 0x30),0);
              uStack_48 = CONCAT44((int)((ulonglong)uStack_48 >> 0x20),
                                   (float)iVar5 * fVar1 * *pfVar12);
              uStack_40 = uVar2;
              FUN_186b75890(lVar8,&uStack_48,0);
              if (*(longlong *)(lVar7 + 0x28) != 0) {
                puVar11 = (undefined8 *)FUN_186b6cef0(&uStack_38,*(longlong *)(lVar7 + 0x28),0);
                fVar1 = *(float *)(lVar7 + 0x60);
                uStack_48 = *puVar11;
                uStack_40 = *(undefined4 *)(puVar11 + 1);
                uStack_3c = *(undefined4 *)((longlong)puVar11 + 0xc);
                if ((*(longlong *)(lVar7 + 0x40) != 0) &&
                   (lVar8 = *(longlong *)(*(longlong *)(lVar7 + 0x40) + 0x40), lVar8 != 0)) {
                  fVar13 = (float)FUN_1860de5e0(lVar8,0);
                  if (*(int *)(lRam00000001888c3c38 + 0xe0) == 0) {
                    func_0x00018048c140();
                  }
                  fVar13 = (float)FUN_1845546e0(1.0 - ABS(fVar13) / 180.0);
                  fVar13 = fVar13 * fVar1;
                  uStack_38 = (undefined4)uStack_48;
                  uStack_30 = CONCAT44(fVar13,uStack_40);
                  uStack_34 = uStack_48._4_4_;
                  if (*(longlong *)(lVar7 + 0x28) != 0) {
                    uStack_30 = CONCAT44(fVar13,uStack_40);
                    FUN_186b6cf90(*(longlong *)(lVar7 + 0x28),&uStack_38,0);
                    goto code_r0x000180b05e1b;
                  }
                }
              }
            }
          }
        }
DAT_180b06048:
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
  }
code_r0x000180b05e1b:
  FUN_180b061c0(lVar7,0);
  return;
}


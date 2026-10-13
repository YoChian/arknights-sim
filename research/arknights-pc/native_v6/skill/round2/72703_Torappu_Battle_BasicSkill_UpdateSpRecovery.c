
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_UpdateSpRecovery_0x6011c00(longlong *param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong lVar10;
  longlong lVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  ulonglong uVar15;
  uint uVar16;
  ulonglong uVar17;
  undefined8 unaff_R14;
  longlong lVar18;
  ulonglong uStackX_8;
  
  if (DAT_188c91c71 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c71 = '\x01';
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x3f0);
  if (lVar10 == 0) {
    if (DAT_188c91bfd == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91bfd = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x48);
    if (lVar10 == 0) {
      cVar3 = *(char *)((longlong)param_1 + 0x1c);
    }
    else {
      cVar3 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar10,param_1,0);
    }
    if ((cVar3 != '\0') ||
       (cVar3 = Torappu_Battle_BasicSkill_get_isUsedUp_0x6011bbd(param_1,0), cVar3 != '\0')) {
      return;
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar3 = (**(code **)(*param_1 + 0x2e0))(param_1,*(undefined8 *)(*param_1 + 0x2e8));
    if (cRam0000000188c91c33 == '\0') {
      FUN_18048bf00(&DAT_188925ba0,cVar3,0);
      cRam0000000188c91c33 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x1f8);
    if (lVar10 == 0) {
      if ((char)param_1[0x19] != cVar3) {
        *(char *)(param_1 + 0x19) = cVar3;
        if (param_1[0x15] != 0) {
          lVar10 = FUN_180701e20(param_1[0x15],0);
          if (cVar3 == '\0') {
            if (lVar10 != 0) {
              if (cRam0000000188c9019e == '\0') {
                FUN_18048bf00(0x18888e410,param_1,0);
                cRam0000000188c9019e = '\x01';
              }
              if ((*(longlong *)(lVar10 + 0x10) == 0) ||
                 (cVar3 = FUN_1849738a0(*(longlong *)(lVar10 + 0x10),param_1,uRam000000018888e410),
                 param_1 == (longlong *)0x0)) {
code_r0x00018064a46a:
                FUN_18048c0b0();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              uVar13 = 0;
              uVar15 = 1;
              lVar18 = 0x20;
              if (cVar3 != '\0') {
                uVar5 = func_0x0001806465c0(param_1,0);
                uVar6 = func_0x000180645d00(param_1,0);
                uVar7 = func_0x000180646390(param_1,0);
                lVar11 = 0x20;
                uVar16 = uVar13;
                do {
                  uVar17 = 1L << ((byte)uVar16 & 0x3f);
                  if (0 < (longlong)(uVar7 & uVar17)) {
                    lVar1 = *(longlong *)(lVar10 + 0x20);
                    if (lVar1 == 0) goto code_r0x00018064a46a;
                    if (*(uint *)(lVar1 + 0x18) <= uVar16) goto code_r0x00018064a470;
                    *(short *)(lVar11 + lVar1) = *(short *)(lVar11 + lVar1) + -1;
                  }
                  if (0 < (longlong)(uVar5 & uVar17)) {
                    lVar1 = *(longlong *)(lVar10 + 0x28);
                    if (lVar1 == 0) goto code_r0x00018064a46a;
                    if (*(uint *)(lVar1 + 0x18) <= uVar16) goto code_r0x00018064a470;
                    *(short *)(lVar11 + lVar1) = *(short *)(lVar11 + lVar1) + -1;
                  }
                  if (0 < (longlong)(uVar17 & uVar6)) {
                    lVar1 = *(longlong *)(lVar10 + 0x30);
                    if (lVar1 == 0) goto code_r0x00018064a46a;
                    if (*(uint *)(lVar1 + 0x18) <= uVar16) goto code_r0x00018064a470;
                    *(short *)(lVar11 + lVar1) = *(short *)(lVar11 + lVar1) + -1;
                  }
                  uVar16 = uVar16 + 1;
                  lVar11 = lVar11 + 2;
                } while ((int)uVar16 < 0x2e);
                lVar11 = *(longlong *)(lVar10 + 0x50);
                uVar8 = func_0x000180646160(param_1,0);
                uVar9 = func_0x000180645f30(param_1,0);
                if (lVar11 == 0) goto code_r0x00018064a46a;
                FUN_180647100(lVar11,uVar8,uVar9,0);
              }
              uVar5 = func_0x0001806467f0(param_1,0);
              uVar16 = uVar13;
              do {
                if (0 < (longlong)(uVar5 & 1L << ((byte)uVar16 & 0x3f))) {
                  lVar11 = *(longlong *)(lVar10 + 0x18);
                  if (lVar11 == 0) goto code_r0x00018064a46a;
                  if (*(uint *)(lVar11 + 0x18) <= uVar16) {
code_r0x00018064a470:
                    FUN_18048c0a0();
                    pcVar2 = (code *)swi(3);
                    (*pcVar2)();
                    return;
                  }
                  if (*(longlong *)(lVar18 + lVar11) == 0) goto code_r0x00018064a46a;
                  FUN_1849738a0(*(longlong *)(lVar18 + lVar11),param_1,uRam000000018888e410);
                }
                uVar16 = uVar16 + 1;
                lVar18 = lVar18 + 8;
              } while ((int)uVar16 < 0x26);
              do {
                if (0 < (longlong)(uVar5 & uVar15)) {
                  FUN_180649a90(lVar10,uVar13,0);
                }
                uVar13 = uVar13 + 1;
                uVar15 = uVar15 << 1 | (ulonglong)((longlong)uVar15 < 0);
              } while ((int)uVar13 < 0x26);
FUN_18064ab90:
              if (cRam0000000188c901b0 == '\0') {
                FUN_18048bf00(0x1888727b8,param_1,0);
                FUN_18048bf00(0x1888729f0);
                cRam0000000188c901b0 = '\x01';
              }
              if (param_1 == (longlong *)0x0) {
                FUN_18048c0b0();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              uVar15 = func_0x000180646390(param_1,0);
              iVar14 = 0;
              iVar12 = iVar14;
              do {
                if ((0 < (longlong)(uVar15 & 1L << ((byte)iVar12 & 0x3f))) &&
                   (uVar4 = func_0x0001844dc660(iVar12,uRam00000001888729f0),
                   *(longlong *)(lVar10 + 0x88) != 0)) {
                  lVar18 = *(longlong *)(lVar10 + 0x88);
                  (**(code **)(lVar18 + 0x18))
                            (*(undefined8 *)(lVar18 + 0x40),uVar4,*(undefined8 *)(lVar18 + 0x28),
                             *(code **)(lVar18 + 0x18),unaff_R14);
                }
                iVar12 = iVar12 + 1;
              } while (iVar12 < 0x2e);
              uVar15 = func_0x000180646160(param_1,0);
              iVar12 = iVar14;
              do {
                if ((0 < (longlong)(uVar15 & 1L << ((byte)iVar12 & 0x3f))) &&
                   (uVar4 = func_0x0001844dc660(iVar12,uRam00000001888727b8),
                   *(longlong *)(lVar10 + 0x90) != 0)) {
                  lVar18 = *(longlong *)(lVar10 + 0x90);
                  (**(code **)(lVar18 + 0x18))
                            (*(undefined8 *)(lVar18 + 0x40),uVar4,*(undefined8 *)(lVar18 + 0x28));
                }
                iVar12 = iVar12 + 1;
              } while (iVar12 < 3);
              uVar15 = func_0x0001806465c0(param_1,0);
              iVar12 = iVar14;
              do {
                if ((0 < (longlong)(uVar15 & 1L << ((byte)iVar12 & 0x3f))) &&
                   (uVar4 = func_0x0001844dc660(iVar12,uRam00000001888729f0),
                   *(longlong *)(lVar10 + 0x88) != 0)) {
                  lVar18 = *(longlong *)(lVar10 + 0x88);
                  (**(code **)(lVar18 + 0x18))
                            (*(undefined8 *)(lVar18 + 0x40),uVar4,*(undefined8 *)(lVar18 + 0x28));
                }
                iVar12 = iVar12 + 1;
              } while (iVar12 < 0x2e);
              uVar15 = func_0x000180645f30(param_1,0);
              do {
                if ((0 < (longlong)(uVar15 & 1L << ((byte)iVar14 & 0x3f))) &&
                   (uVar4 = func_0x0001844dc660(iVar14,uRam00000001888727b8),
                   *(longlong *)(lVar10 + 0x90) != 0)) {
                  lVar18 = *(longlong *)(lVar10 + 0x90);
                  (**(code **)(lVar18 + 0x18))
                            (*(undefined8 *)(lVar18 + 0x40),uVar4,*(undefined8 *)(lVar18 + 0x28));
                }
                iVar14 = iVar14 + 1;
              } while (iVar14 < 3);
              return;
            }
          }
          else if (lVar10 != 0) {
            if (cRam0000000188c9019d == '\0') {
              FUN_18048bf00(0x18888dd60,param_1,0);
              cRam0000000188c9019d = '\x01';
            }
            if ((*(longlong *)(lVar10 + 0x10) == 0) ||
               (cVar3 = FUN_184964190(*(longlong *)(lVar10 + 0x10),param_1,uRam000000018888dd60),
               param_1 == (longlong *)0x0)) {
code_r0x00018064884a:
              FUN_18048c0b0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            uVar13 = 0;
            uVar15 = 1;
            lVar18 = 0x20;
            if (cVar3 != '\0') {
              uVar5 = func_0x0001806465c0(param_1,0);
              uVar6 = func_0x000180645d00(param_1,0);
              uVar7 = func_0x000180646390(param_1,0);
              lVar11 = 0x20;
              uVar16 = uVar13;
              do {
                uVar17 = 1L << ((byte)uVar16 & 0x3f);
                if (0 < (longlong)(uVar7 & uVar17)) {
                  lVar1 = *(longlong *)(lVar10 + 0x20);
                  if (lVar1 == 0) goto code_r0x00018064884a;
                  if (*(uint *)(lVar1 + 0x18) <= uVar16) goto code_r0x000180648850;
                  *(short *)(lVar11 + lVar1) = *(short *)(lVar11 + lVar1) + 1;
                }
                if (0 < (longlong)(uVar5 & uVar17)) {
                  lVar1 = *(longlong *)(lVar10 + 0x28);
                  if (lVar1 == 0) goto code_r0x00018064884a;
                  if (*(uint *)(lVar1 + 0x18) <= uVar16) goto code_r0x000180648850;
                  *(short *)(lVar11 + lVar1) = *(short *)(lVar11 + lVar1) + 1;
                }
                if (0 < (longlong)(uVar17 & uVar6)) {
                  lVar1 = *(longlong *)(lVar10 + 0x30);
                  if (lVar1 == 0) goto code_r0x00018064884a;
                  if (*(uint *)(lVar1 + 0x18) <= uVar16) goto code_r0x000180648850;
                  *(short *)(lVar11 + lVar1) = *(short *)(lVar11 + lVar1) + 1;
                }
                uVar16 = uVar16 + 1;
                lVar11 = lVar11 + 2;
              } while ((int)uVar16 < 0x2e);
              lVar11 = *(longlong *)(lVar10 + 0x50);
              uVar8 = func_0x000180646160(param_1,0);
              uVar9 = func_0x000180645f30(param_1,0);
              if (lVar11 == 0) goto code_r0x00018064884a;
              FUN_180647260(lVar11,uVar8,uVar9,0);
            }
            uVar5 = func_0x0001806467f0(param_1,0);
            uVar16 = uVar13;
            do {
              if (0 < (longlong)(uVar5 & 1L << ((byte)uVar16 & 0x3f))) {
                lVar11 = *(longlong *)(lVar10 + 0x18);
                if (lVar11 == 0) goto code_r0x00018064884a;
                if (*(uint *)(lVar11 + 0x18) <= uVar16) {
code_r0x000180648850:
                  FUN_18048c0a0();
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                if (*(longlong *)(lVar18 + lVar11) == 0) goto code_r0x00018064884a;
                FUN_184964190(*(longlong *)(lVar18 + lVar11),param_1,uRam000000018888dd60);
              }
              uVar16 = uVar16 + 1;
              lVar18 = lVar18 + 8;
            } while ((int)uVar16 < 0x26);
            do {
              if (0 < (longlong)(uVar5 & uVar15)) {
                FUN_180649a90(lVar10,uVar13,0);
              }
              uVar13 = uVar13 + 1;
              uVar15 = uVar15 << 1 | (ulonglong)((longlong)uVar15 < 0);
            } while ((int)uVar13 < 0x26);
            goto FUN_18064ab90;
          }
        }
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
    }
    else {
      FUN_1833005f0(lVar10,param_1,cVar3,0);
    }
    return;
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  uVar8 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30);
  uStackX_8 = uStackX_8 & 0xffffffffffffff00;
  FUN_185ca7f50(uVar8,&uStackX_8,0);
  if (*(longlong *)(lVar10 + 0x18) != 0) {
    uVar9 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    iVar12 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar18 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar18 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar18,uVar9,param_1,0);
        iVar14 = FUN_183f22380(uVar9,1,0,iVar12,0);
        if (iVar14 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar9,iVar12 + -1,0);
          if ((char)uStackX_8 != '\0') {
            func_0x000185ca7ff0(uVar8,0);
          }
          return;
        }
        if (*(longlong *)(lVar10 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar12 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


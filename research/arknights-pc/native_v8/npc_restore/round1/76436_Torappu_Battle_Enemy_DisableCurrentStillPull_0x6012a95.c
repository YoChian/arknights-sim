
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_DisableCurrentStillPull_0x6012a95(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  longlong lVar6;
  code *pcVar7;
  int iVar8;
  longlong lVar9;
  undefined8 *puVar10;
  ushort uVar11;
  int iVar12;
  ulonglong uStackX_8;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 auStack_48 [3];
  undefined8 uStack_30;
  
  if (DAT_188c9287d == '\0') {
    uStack_30 = 0x180a6c49e;
    FUN_18048bf00(&DAT_18881b6b0);
    uStack_30 = 0x180a6c4aa;
    FUN_18048bf00(&DAT_188819d68);
    uStack_30 = 0x180a6c4b6;
    FUN_18048bf00(&DAT_188819fa8);
    uStack_30 = 0x180a6c4c2;
    FUN_18048bf00(0x18881a428);
    DAT_188c9287d = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    uStack_30 = 0x180a6c4e1;
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x528);
  if (lVar1 == 0) {
    if (*(longlong *)(param_1 + 0x440) != 0) {
      uStack_30 = 0x180a6c513;
      FUN_184ac4b30(*(longlong *)(param_1 + 0x440),_DAT_188819fa8);
      lVar1 = _DAT_188819d68;
      if ((*(longlong *)(param_1 + 0x438) != 0) &&
         (lVar2 = *(longlong *)(param_1 + 0x440), lVar2 != 0)) {
        plVar3 = *(longlong **)(*(longlong *)(param_1 + 0x438) + 0x10);
        iVar8 = FUN_1844afc00(plVar3,*(undefined8 *)
                                      (*(longlong *)(*(longlong *)(_DAT_188819d68 + 0x20) + 0xc0) +
                                      0x58));
        if (0 < iVar8) {
          iVar12 = 0;
          if (plVar3 == (longlong *)0x0) {
            FUN_18048c0b0();
            pcVar7 = (code *)swi(3);
            (*pcVar7)();
            return;
          }
          do {
            lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x60);
            if ((*(byte *)(lVar9 + 0x136) & 1) == 0) {
              lVar9 = FUN_1804463f0(lVar9);
            }
            lVar6 = *plVar3;
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(lVar6);
            }
            uVar11 = 0;
            if (*(ushort *)(lVar6 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar11 * 0x10) == lVar9)
                {
                  puVar10 = (undefined8 *)
                            (((longlong)
                              *(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10) +
                             0x14) * 0x10 + lVar6);
                  goto code_r0x000184ac3e36;
                }
                uVar11 = uVar11 + 1;
              } while (uVar11 < *(ushort *)(lVar6 + 0x12e));
            }
            puVar10 = (undefined8 *)FUN_180445cc0(plVar3,lVar9,0);
code_r0x000184ac3e36:
            puVar10 = (undefined8 *)(*(code *)*puVar10)(auStack_48,plVar3,iVar12,puVar10[1]);
            uVar4 = *puVar10;
            uVar5 = puVar10[1];
            if (*(longlong *)
                 (*(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x70) + 0x20) ==
                0) {
              (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x70))
                        ();
            }
            uStack_58 = uVar4;
            uStack_50 = uVar5;
            FUN_184ac4890(lVar2,&uStack_58);
            iVar12 = iVar12 + 1;
          } while (iVar12 < iVar8);
        }
        return;
      }
    }
    uStack_30 = 0x180a6c555;
    FUN_18048c0b0();
    pcVar7 = (code *)swi(3);
    (*pcVar7)();
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar7 = (code *)swi(3);
    (*pcVar7)();
    return;
  }
  uVar4 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  uStackX_8 = uStackX_8 & 0xffffffffffffff00;
  uStack_30 = 0;
  FUN_185ca7f50(uVar4,&uStackX_8,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar5 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar8 = FUN_183f23b70(uVar5,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar5,param_1,0);
        auStack_48[0] = 0;
        iVar12 = FUN_183f22380(uVar5,1,0,iVar8);
        if (iVar12 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar5,iVar8 + -1,0);
          if ((char)uStackX_8 != '\0') {
            func_0x000185ca7ff0(uVar4,0);
          }
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar8 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}


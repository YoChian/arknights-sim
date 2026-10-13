/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void SummonEnemiesFollowMyRouteWithBuff_GatherBuffs_0x6018169(longlong param_1,longlong param_2)
{
  longlong lVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  ushort uVar11;
  uint uVar12;
  longlong *aplStack_58 [2];
  undefined8 uStack_48;
  longlong **pplStack_40;
  if (DAT_188c96dd5 == '\0') {
    FUN_18048bf00(&DAT_188879750);
    FUN_18048bf00(&DAT_188879510);
    FUN_18048bf00(&DAT_1888cb898);
    DAT_188c96dd5 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_1888cb898 + 0xb8) + 0x18);
  if (lVar8 == 0) {
    if (param_2 == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    if (*(char *)(param_1 + 0x6e) != '\0') {
      FUN_1805072d0(param_2,*(undefined8 *)(param_1 + 0x70),_DAT_188879510);
    }
    lVar1 = _DAT_188879750;
    lVar8 = *(longlong *)(param_1 + 0x80);
    uVar12 = *(uint *)(param_2 + 0x18);
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_188879750 + 0x20) + 0xc0) + 0x78) + 0x20)
        == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(_DAT_188879750 + 0x20) + 0xc0) + 0x78)
      )();
    }
    lVar1 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x78);
    if (cRam0000000188cbad21 == '\0') {
      FUN_18048bf00(0x188954c98);
      FUN_18048bf00(0x188959b58);
      cRam0000000188cbad21 = '\x01';
    }
    aplStack_58[0] = (longlong *)0x0;
    if (lVar8 == 0) {
      FUN_185ed6160(6,0);
    }
    if (*(uint *)(param_2 + 0x18) < uVar12) {
      FUN_185ed63b0(0);
    }
    lVar7 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x10);
    if ((*(byte *)(lVar7 + 0x136) & 1) == 0) {
      lVar7 = FUN_1804463f0(lVar7);
    }
    lVar7 = func_0x00018048b9f0(lVar8,lVar7);
    if (lVar7 == 0) {
      if ((int)uVar12 < *(int *)(param_2 + 0x18)) {
        if (lVar8 == 0) {
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        lVar7 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x138);
        if ((*(byte *)(lVar7 + 0x136) & 1) == 0) {
          lVar7 = FUN_1804463f0(lVar7);
        }
        aplStack_58[0] = (longlong *)FUN_180005310(0,lVar7,lVar8);
        uStack_48 = 0;
        pplStack_40 = aplStack_58;
        do {
          if (aplStack_58[0] == (longlong *)0x0) {
code_r0x000184d0f1ea:
            FUN_18048c0b0();
            FUN_180472d50();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          cVar4 = FUN_180005310(0,uRam0000000188959b58);
          plVar3 = aplStack_58[0];
          if (cVar4 == '\0') {
            if (aplStack_58[0] != (longlong *)0x0) {
              FUN_180005310(0,uRam0000000188954c98,aplStack_58[0]);
            }
            goto code_r0x000184d0f1d0;
          }
          if (aplStack_58[0] == (longlong *)0x0) {
            FUN_18048c0b0();
            goto code_r0x000184d0f1ea;
          }
          lVar8 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x148);
          if ((*(byte *)(lVar8 + 0x136) & 1) == 0) {
            lVar8 = FUN_1804463f0(lVar8);
          }
          lVar7 = *plVar3;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(lVar7);
          }
          uVar11 = 0;
          if (*(ushort *)(lVar7 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar7 + 0xb0) + (ulonglong)uVar11 * 0x10) == lVar8) {
                puVar9 = (undefined8 *)
                         (((longlong)
                           *(int *)(*(longlong *)(lVar7 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10) +
                          0x14) * 0x10 + lVar7);
                goto code_r0x000184d0ef85;
              }
              uVar11 = uVar11 + 1;
            } while (uVar11 < *(ushort *)(lVar7 + 0x12e));
          }
          puVar9 = (undefined8 *)FUN_180445cc0(plVar3,lVar8,0);
code_r0x000184d0ef85:
          uVar10 = (*(code *)*puVar9)(plVar3,puVar9[1]);
          if (*(longlong *)
               (*(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x130) + 0x20) ==
              0) {
            (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x130))
                      ();
          }
          func_0x0001800c9e60(param_2,uVar12,uVar10,
                              *(undefined8 *)
                               (*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x130));
          uVar12 = uVar12 + 1;
        } while( true );
      }
      if (*(longlong *)
           (*(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x28) + 0x20) == 0) {
        (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x28))();
      }
      FUN_184d08380(param_2,lVar8,
                    *(undefined8 *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x28));
    }
    else {
      lVar8 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x10);
      if ((*(byte *)(lVar8 + 0x136) & 1) == 0) {
        lVar8 = FUN_1804463f0(lVar8);
      }
      iVar6 = FUN_180005310(0,lVar8,lVar7);
      if (0 < iVar6) {
        iVar5 = *(int *)(param_2 + 0x18);
        if (*(longlong *)
             (*(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x60) + 0x20) == 0)
        {
          (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x60))();
        }
        FUN_180124580(param_2,iVar5 + iVar6,
                      *(undefined8 *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x60));
        if ((int)uVar12 < *(int *)(param_2 + 0x18)) {
          FUN_185eea240(*(undefined8 *)(param_2 + 0x10),uVar12,*(undefined8 *)(param_2 + 0x10),
                        iVar6 + uVar12,*(int *)(param_2 + 0x18) - uVar12,0);
        }
        uVar10 = *(undefined8 *)(param_2 + 0x10);
        if (param_2 == lVar7) {
          FUN_185eea240(uVar10,0,uVar10,uVar12,uVar12,0);
          FUN_185eea240(*(undefined8 *)(param_2 + 0x10),iVar6 + uVar12,
                        *(undefined8 *)(param_2 + 0x10),uVar12 * 2,*(int *)(param_2 + 0x18) - uVar12
                        ,0);
        }
        else {
          lVar8 = *(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x10);
          if ((*(byte *)(lVar8 + 0x136) & 1) == 0) {
            lVar8 = FUN_1804463f0(lVar8);
          }
          FUN_18000f460(5,lVar8,lVar7,uVar10,uVar12);
        }
        *(int *)(param_2 + 0x18) = *(int *)(param_2 + 0x18) + iVar6;
      }
    }
code_r0x000184d0f1d0:
    *(int *)(param_2 + 0x1c) = *(int *)(param_2 + 0x1c) + 1;
    return;
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar8 + 0x18) != 0) {
    uVar10 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar10,param_1,0);
        FUN_183cf8c20(lVar1,uVar10,param_2,0);
        aplStack_58[0] = (longlong *)0x0;
        iVar5 = FUN_183f22380(uVar10,2,0,iVar6);
        if (iVar5 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar10,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar8 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar6 + -1,0);
          goto code_r0x0001832d231b;
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

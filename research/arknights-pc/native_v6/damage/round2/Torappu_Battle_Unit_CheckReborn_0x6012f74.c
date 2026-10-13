/* WARNING: Removing unreachable block (ram,0x00018338847c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined1 Torappu_Battle_Unit_CheckReborn_0x6012f74(longlong param_1,undefined8 *param_2)
{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  uint uVar10;
  longlong lVar11;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  if (DAT_188c92bf5 == '\0') {
    auStack_40[0] = 0x180ac68d3;
    FUN_18048bf00(&DAT_1888a8a50);
    auStack_40[0] = 0x180ac68df;
    FUN_18048bf00(&DAT_188805040);
    DAT_188c92bf5 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x3d8);
  if (lVar9 == 0) {
    if (DAT_188c92baf == '\0') {
      auStack_40[0] = 0x180ac691e;
      FUN_18048bf00(&DAT_188805040);
      DAT_188c92baf = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x1a8);
    if (lVar9 == 0) {
      uVar7 = *(undefined8 *)(param_1 + 0x270);
    }
    else {
      auStack_40[0] = 0x180ac6953;
      uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp3742_0x60018fe(lVar9,param_1,0);
    }
    auStack_40[0] = 0x180ac6976;
    iVar5 = FUN_1844afc00(uVar7,_DAT_1888a8a50);
    uVar10 = 0;
    if (0 < iVar5) {
      lVar11 = 0;
      lVar9 = 0x20;
      do {
        if (DAT_188c92baf == '\0') {
          auStack_40[0] = 0x180ac69a5;
          FUN_18048bf00(&DAT_188805040);
          DAT_188c92baf = '\x01';
        }
        lVar8 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x1a8);
        if (lVar8 == 0) {
          lVar8 = *(longlong *)(param_1 + 0x270);
        }
        else {
          auStack_40[0] = 0x180ac69da;
          lVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3742_0x60018fe(lVar8,param_1,0);
        }
        if (lVar8 == 0) {
LAB_180ac6acf:
          auStack_40[0] = 0x180ac6ad4;
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          uVar4 = (*pcVar2)();
          return uVar4;
        }
        if (*(uint *)(lVar8 + 0x18) <= uVar10) {
LAB_180ac6ac9:
          auStack_40[0] = 0x180ac6ace;
          FUN_18048c0a0();
          pcVar2 = (code *)swi(3);
          uVar4 = (*pcVar2)();
          return uVar4;
        }
        plVar1 = *(longlong **)(lVar9 + lVar8);
        if (plVar1 == (longlong *)0x0) goto LAB_180ac6acf;
        if (DAT_188ccc7f0 != '\0') {
          auStack_40[0] = 0x180ac6a0a;
          func_0x000180446d00(*plVar1);
        }
        auStack_40[0] = 0x180ac6a20;
        cVar3 = (**(code **)(*plVar1 + 0x1a0))(plVar1,*(undefined8 *)(*plVar1 + 0x1a8));
        if (cVar3 != '\0') {
          auStack_40[0] = 0x180ac6a2e;
          lVar8 = Torappu_Battle_Unit_get_talents_0x6012f2d(param_1,0);
          if (lVar8 == 0) goto LAB_180ac6acf;
          if (*(uint *)(lVar8 + 0x18) <= uVar10) goto LAB_180ac6ac9;
          if (*(longlong *)(lVar9 + lVar8) == 0) goto LAB_180ac6acf;
          auStack_40[0] = 0x180ac6a5a;
          cVar3 = FUN_180005480(0x1a);
          if (cVar3 != '\0') {
            return 1;
          }
        }
        uVar10 = uVar10 + 1;
        lVar11 = lVar11 + 1;
        lVar9 = lVar9 + 8;
      } while (lVar11 < iVar5);
    }
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    param_2[8] = 0;
    return 0;
  }
  if (cRam0000000188cafee1 == '\0') {
    FUN_18048bf00(0x1888c8768,param_1,param_2,0);
    cRam0000000188cafee1 = '\x01';
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001833884d3:
    FUN_18048c0b0();
code_r0x0001833884d9:
    FUN_18048c0b0();
  }
  else {
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar9 + 0x18) == 0) goto code_r0x0001833884e3;
    uVar7 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar11 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar11 == 0) goto code_r0x0001833884d3;
      FUN_183cf8c20(lVar11,uVar7,param_1,0);
      iVar6 = FUN_183f22380(uVar7,1,2,iVar5,0);
      if (iVar6 == 0) {
code_r0x000183388431:
        FUN_184571340(lVar11,uVar7,iVar5 + 2,param_2,uRam00000001888c8768);
        uVar4 = FUN_183f23100(uVar7,iVar5 + 1,0);
        FUN_183f22fd0(uVar7,iVar5 + -1,0);
        return uVar4;
      }
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar5 + -1,0);
        goto code_r0x000183388431;
      }
      goto code_r0x0001833884d9;
    }
  }
  FUN_18048c0b0();
code_r0x0001833884e3:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  uVar4 = (*pcVar2)();
  return uVar4;
}

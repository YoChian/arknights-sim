
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_AbilityStandard_DoUpdatePlaybackSpeed_0x600f6cb(longlong *param_1,undefined4 param_2)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  uint uVar6;
  longlong lVar7;
  longlong lVar8;
  bool bVar9;
  float fVar10;
  float fVar11;
  float afStackX_20 [2];
  
  if (DAT_188c8fd49 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd49 = '\x01';
  }
  afStackX_20[0] = 0.0;
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x1a8);
  if (lVar7 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp2654_0x60014be(lVar7,param_1,param_2,0);
    return uVar5;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar4 = (**(code **)(*param_1 + 0x6f0))
                    (param_1,param_2,afStackX_20,*(undefined8 *)(*param_1 + 0x6f8));
  fVar11 = 0.0;
  if (cVar4 != '\0') {
    fVar11 = afStackX_20[0];
  }
  bVar9 = cVar4 != '\0';
  if (param_1[0x20] != 0) {
    uVar6 = *(int *)(param_1[0x20] + 0x18) - 1;
    lVar7 = (longlong)(int)uVar6;
    if (-1 < (int)uVar6) {
      lVar8 = lVar7 * 8 + 0x20;
      do {
        lVar1 = param_1[0x20];
        if (lVar1 == 0) goto LAB_1805d0173;
        if (*(uint *)(lVar1 + 0x18) <= uVar6) {
          FUN_18048c0a0();
          pcVar3 = (code *)swi(3);
          uVar5 = (*pcVar3)();
          return uVar5;
        }
        plVar2 = *(longlong **)(lVar8 + lVar1);
        if (plVar2 == (longlong *)0x0) goto LAB_1805d0173;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
        cVar4 = (**(code **)(*plVar2 + 0x220))
                          (plVar2,param_2,afStackX_20,*(undefined8 *)(*plVar2 + 0x228));
        if (cVar4 != '\0') {
          bVar9 = true;
          fVar11 = afStackX_20[0];
        }
        uVar6 = uVar6 - 1;
        lVar8 = lVar8 + -8;
        lVar7 = lVar7 + -1;
      } while (-1 < lVar7);
    }
    if (bVar9) {
      fVar10 = 0.01;
      if ((fVar11 < 0.01) || (fVar10 = 100.0, 100.0 < fVar11)) {
        fVar11 = fVar10;
      }
      if (DAT_188c8fd19 == '\0') {
        FUN_18048bf00(&DAT_188974cb0);
        DAT_188c8fd19 = '\x01';
      }
      lVar7 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x20);
      if (lVar7 == 0) {
        *(float *)(param_1 + 0x1f) = fVar11;
        uVar5 = 1;
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp81_0x6000ab1(lVar7,param_1,fVar11,0);
        uVar5 = 1;
      }
    }
    else {
      uVar5 = 0;
    }
    return uVar5;
  }
LAB_1805d0173:
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  uVar5 = (*pcVar3)();
  return uVar5;
}


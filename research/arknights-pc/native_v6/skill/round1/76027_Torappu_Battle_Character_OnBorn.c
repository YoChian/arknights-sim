
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_OnBorn_0x60128fc(longlong *param_1)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  double dVar11;
  undefined1 auVar12 [16];
  uint auStackX_18 [4];
  
  if (DAT_188c92635 == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_18894ebe0);
    FUN_18048bf00(&DAT_1888e0148);
    DAT_188c92635 = '\x01';
  }
  auStackX_18[0] = 0;
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x698);
  if (lVar6 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar6,param_1,0);
    return;
  }
  if (*(int *)(_DAT_18894ebe0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18894ebe0);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18894ebe0 + 0xb8) + 0x50);
  uVar4 = Torappu_Battle_Entity_get_direction_0x6010358(param_1,0);
  if (lVar6 == 0) goto LAB_180a2d5ec;
  if (*(uint *)(lVar6 + 0x18) <= uVar4) goto LAB_180a2d5e6;
  fVar8 = *(float *)(lVar6 + 0x20 + (longlong)(int)uVar4 * 8);
  fVar9 = *(float *)(lVar6 + 0x24 + (longlong)(int)uVar4 * 8);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar3 = (**(code **)(*param_1 + 0x590))(param_1,*(undefined8 *)(*param_1 + 0x598));
  if (cVar3 == '\0') {
    iVar5 = Torappu_Battle_Entity_get_direction_0x6010358(param_1,0);
    if (iVar5 != 0) {
      iVar5 = Torappu_Battle_Entity_get_direction_0x6010358(param_1,0);
      if (iVar5 != 2) goto LAB_180a2d4e8;
    }
    lVar6 = FUN_185337c50(_DAT_1888e0148);
    uVar7 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(param_1,0);
    if (lVar6 == 0) goto LAB_180a2d5ec;
    cVar3 = Torappu_Battle_Map_TryGetInitialLOrR_0x6011180(lVar6,uVar7,auStackX_18,0);
    if (cVar3 != '\0') {
      if (*(int *)(_DAT_18894ebe0 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_18894ebe0);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_18894ebe0 + 0xb8) + 0x50);
      if (lVar6 == 0) goto LAB_180a2d5ec;
      if (*(uint *)(lVar6 + 0x18) <= auStackX_18[0]) {
LAB_180a2d5e6:
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      fVar8 = *(float *)(lVar6 + 0x20 + (longlong)(int)auStackX_18[0] * 8) * 0.5 + fVar8;
      fVar9 = *(float *)(lVar6 + 0x24 + (longlong)(int)auStackX_18[0] * 8) * 0.5 + fVar9;
      if (DAT_188c8f78f == '\0') {
        FUN_18048bf00(&DAT_1888c37c0);
        DAT_188c8f78f = '\x01';
      }
      if (*(int *)(_DAT_1888c37c0 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      dVar11 = (double)(fVar8 * fVar8 + fVar9 * fVar9);
      if (dVar11 < 0.0) {
        dVar11 = (double)FUN_1804d2720();
      }
      else {
        auVar12._8_8_ = 0;
        auVar12._0_8_ = dVar11;
        auVar12 = sqrtpd(ZEXT816(0),auVar12);
        dVar11 = auVar12._0_8_;
      }
      fVar10 = (float)dVar11;
      if (1e-05 < fVar10) {
        fVar8 = fVar8 / fVar10;
        fVar9 = fVar9 / fVar10;
      }
      else {
        if (DAT_188c8f5b5 == '\0') {
          FUN_18048bf00(&DAT_188828bc0);
          DAT_188c8f5b5 = '\x01';
        }
        fVar8 = **(float **)(_DAT_188828bc0 + 0xb8);
        fVar9 = (*(float **)(_DAT_188828bc0 + 0xb8))[1];
      }
    }
  }
LAB_180a2d4e8:
  Torappu_Battle_Entity_FaceTo_0x60103e8(param_1,CONCAT44(fVar9,fVar8),1,0,0);
  Torappu_Battle_Unit_OnBorn_0x6012f81(param_1,0);
  lVar6 = param_1[0x9b];
  *(undefined1 *)((longlong)param_1 + 0x372) = 0;
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(lVar6,0,0);
  if (cVar3 != '\0') {
    if (param_1[0x9b] == 0) goto LAB_180a2d5ec;
    Torappu_Battle_Ability_Attach_0x600f653(param_1[0x9b],param_1,0);
  }
  lVar6 = param_1[0x78];
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(lVar6,0,0);
  if (cVar3 != '\0') {
    plVar1 = (longlong *)param_1[0x78];
    if (plVar1 == (longlong *)0x0) {
LAB_180a2d5ec:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar1);
    }
    (**(code **)(*plVar1 + 0x510))(plVar1,*(undefined8 *)(*plVar1 + 0x518));
  }
  return;
}


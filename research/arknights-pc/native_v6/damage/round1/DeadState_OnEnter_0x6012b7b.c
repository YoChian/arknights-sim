/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void DeadState_OnEnter_0x6012b7b(undefined8 param_1,undefined4 param_2)
{
  code *pcVar1;
  undefined8 uVar2;
  char cVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  float fVar7;
  float fVar8;
  float afStackX_20 [2];
  if (DAT_188c92919 == '\0') {
    FUN_18048bf00(&DAT_188884ab8);
    FUN_18048bf00(&DAT_188957b60);
    FUN_18048bf00(&DAT_188913648);
    DAT_188c92919 = '\x01';
  }
  if (**(longlong **)(_DAT_188884ab8 + 0xb8) != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp55_0x6000a97
              (**(longlong **)(_DAT_188884ab8 + 0xb8),param_1,param_2,0);
    return;
  }
  lVar4 = FUN_18536e540(param_1,_DAT_188957b60);
  if (lVar4 != 0) {
    Torappu_Battle_Enemy_ReleaseBlock_0x6012b03(lVar4,0);
    afStackX_20[0] = 0.0;
    plVar5 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
    uVar2 = _DAT_188913648;
    if (plVar5 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar5);
      }
      cVar3 = (**(code **)(*plVar5 + 2000))
                        (plVar5,uVar2,afStackX_20,*(undefined8 *)(*plVar5 + 0x7d8));
      if (cVar3 == '\0') goto LAB_180a8b577;
      lVar4 = FUN_18536e540(param_1,_DAT_188957b60);
      lVar6 = FUN_18536e540(param_1,_DAT_188957b60);
      fVar8 = afStackX_20[0];
      uVar2 = _DAT_188913648;
      if (lVar6 != 0) {
        if (*(char *)(lVar6 + 0x2fb) == '\0') {
          plVar5 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
          if (plVar5 == (longlong *)0x0) goto LAB_180a8b5b4;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar5);
          }
          fVar7 = (float)(**(code **)(*plVar5 + 0x580))(plVar5,*(undefined8 *)(*plVar5 + 0x588));
          fVar8 = fVar8 / fVar7;
        }
        else {
          fVar8 = 1.0;
        }
        if (lVar4 != 0) {
          FUN_180023a80(0x67,lVar4,uVar2,1,fVar8,0);
          lVar4 = FUN_18536e540(param_1,_DAT_188957b60);
          if (lVar4 != 0) {
            if (*(char *)(lVar4 + 0x2fb) != '\0') {
              lVar4 = FUN_18536e540(param_1,_DAT_188957b60);
              if (lVar4 == 0) goto LAB_180a8b5b4;
              *(float *)(lVar4 + 0x4c8) = afStackX_20[0];
            }
LAB_180a8b577:
            DeadState__PlayAnimation_0x6012b7e(param_1,0);
            return;
          }
        }
      }
    }
  }
LAB_180a8b5b4:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

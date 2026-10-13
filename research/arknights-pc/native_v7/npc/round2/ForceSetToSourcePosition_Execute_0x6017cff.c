/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
ForceSetToSourcePosition_Execute_0x6017cff
          (longlong param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4)
{
  code *pcVar1;
  char cVar2;
  undefined4 uVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong *plVar8;
  bool bVar9;
  if (DAT_188c96979 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_18887c560);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c96979 = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_18887c560 + 0xb8) + 8);
  if (lVar5 != 0) {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar5,param_1,param_2,param_3,param_4,0);
    return uVar6;
  }
  plVar4 = (longlong *)
           Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                     (param_4,*(undefined4 *)(param_1 + 0x10),0);
  if (plVar4 == (longlong *)0x0) {
    plVar8 = (longlong *)0x0;
  }
  else {
    lVar5 = *plVar4;
    if (DAT_188ccc7f0 == '\0') {
      if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_18881b6b0 + 0x130)) ||
         (bVar9 = true,
         *(longlong *)
          (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_18881b6b0 + 0x130) * 8) !=
         _DAT_18881b6b0)) {
        bVar9 = false;
      }
      bVar9 = !bVar9;
    }
    else {
      cVar2 = func_0x0001804463e0(lVar5);
      bVar9 = cVar2 == '\0';
    }
    plVar8 = (longlong *)0x0;
    if (!bVar9) {
      plVar8 = plVar4;
    }
  }
  lVar5 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x14),0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = FUN_186b638d0(plVar8,0,0);
  if (cVar2 == '\0') {
    if (plVar8 == (longlong *)0x0) goto LAB_18107c766;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar8);
    }
    cVar2 = (**(code **)(*plVar8 + 0xef0))(plVar8,*(undefined8 *)(*plVar8 + 0xef8));
    if (cVar2 == '\0') {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b638d0(lVar5,0,0);
      if (cVar2 == '\0') {
        if (*(char *)(param_1 + 0x19) != '\0') {
          Torappu_Battle_Enemy_ReleaseFromBlocker_0x6012acd(plVar8,0);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar2 = FUN_186b638d0(plVar8,0,0);
          if (cVar2 != '\0') {
            return 0;
          }
        }
        if (lVar5 != 0) {
          uVar6 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(lVar5,0);
          Torappu_Battle_VisualObject_SetPosition_0x6013038(plVar8,uVar6,0);
          if (*(char *)(param_1 + 0x18) != '\0') {
            Torappu_Battle_Enemy_DisableCurrentStillPull_0x6012a95(plVar8,0);
          }
          lVar5 = FUN_1800057a0(lVar5,_DAT_18881b6b0);
          if (*(char *)(param_1 + 0x1a) != '\0') {
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar2 = FUN_186b63a70(lVar5,0,0);
            if (cVar2 != '\0') {
              if ((lVar5 != 0) && (lVar7 = FUN_180005610(0xe0,lVar5), lVar7 != 0)) {
                uVar6 = Torappu_Battle_BasicCursor_get_route_0x6011208(lVar7,0);
                lVar5 = FUN_180005610(0xe0,lVar5);
                if (lVar5 != 0) {
                  uVar3 = Torappu_Battle_DirectionCursor_get_cursorIndex_0x601127a(lVar5,0);
                  Torappu_Battle_Enemy_ReassignRoute_0x6012aab(plVar8,uVar6,uVar3,0);
                  return 1;
                }
              }
              goto LAB_18107c766;
            }
          }
          return 1;
        }
LAB_18107c766:
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        uVar6 = (*pcVar1)();
        return uVar6;
      }
    }
  }
  return 0;
}

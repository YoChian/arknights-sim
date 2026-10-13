/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void ModifyLifePoint_Execute_0x601792a
               (longlong param_1,longlong param_2,undefined4 param_3,undefined8 param_4)
{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  undefined8 uVar8;
  bool bVar9;
  undefined1 uVar10;
  if (DAT_188c965b9 == '\0') {
    FUN_18048bf00(&DAT_1888a8898);
    FUN_18048bf00(&DAT_1888a53c0);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c965b9 = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_1888a53c0 + 0xb8) + 8);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f(lVar5,param_1,param_2,param_3,param_4,0);
    return;
  }
  uVar4 = Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                    (param_4,*(undefined4 *)(param_1 + 0x10),0);
  if (param_2 != 0) {
    iVar3 = Torappu_Blackboard_GetIntOrDefault_0x6007874
                      (param_2,*(undefined8 *)(param_1 + 0x18),0,1,0);
    lVar5 = FUN_185337c50(_DAT_1888d3908);
    if (lVar5 == 0) goto LAB_18104120d;
    plVar6 = (longlong *)Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar5,0);
    if (plVar6 != (longlong *)0x0) {
      lVar5 = *plVar6;
      if (DAT_188ccc7f0 == '\0') {
        if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_1888a8898 + 0x130)) ||
           (bVar9 = true,
           *(longlong *)
            (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_1888a8898 + 0x130) * 8) !=
           _DAT_1888a8898)) {
          bVar9 = false;
        }
        bVar9 = !bVar9;
      }
      else {
        cVar2 = func_0x0001804463e0(lVar5);
        bVar9 = cVar2 == '\0';
      }
      plVar7 = (longlong *)0x0;
      if (!bVar9) {
        plVar7 = plVar6;
      }
      if (plVar7 != (longlong *)0x0) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar7);
        }
        cVar2 = (**(code **)(*plVar7 + 0xf30))(plVar7,*(undefined8 *)(*plVar7 + 0xf38));
        if (cVar2 == '\0') {
          lVar5 = FUN_185337c50(_DAT_1888d3908);
          if (lVar5 == 0) goto LAB_18104120d;
          cVar2 = Torappu_Battle_BattleController_ModifyLifePoint_0x600fc75
                            (lVar5,iVar3,uVar4,1,*(undefined1 *)(param_1 + 0x20),0);
          if (cVar2 == '\0') {
            return;
          }
          lVar5 = FUN_185337c50(_DAT_1888d3908);
          uVar10 = *(undefined1 *)(param_1 + 0x20);
          if (lVar5 == 0) goto LAB_18104120d;
          uVar8 = 2;
          goto LAB_1810411a1;
        }
      }
    }
    lVar5 = FUN_185337c50(_DAT_1888d3908);
    if (*(char *)(param_1 + 0x14) != '\0') {
      iVar3 = -iVar3;
    }
    uVar10 = *(undefined1 *)(param_1 + 0x20);
    if (lVar5 != 0) {
      uVar8 = 0;
LAB_1810411a1:
      Torappu_Battle_BattleController_ModifyLifePoint_0x600fc75(lVar5,iVar3,uVar4,uVar8,uVar10,0);
      return;
    }
  }
LAB_18104120d:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

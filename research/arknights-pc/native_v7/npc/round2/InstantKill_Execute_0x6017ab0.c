/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong InstantKill_Execute_0x6017ab0
                    (longlong param_1,undefined8 param_2,undefined4 param_3,undefined8 *param_4)
{
  undefined1 uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  longlong *plVar5;
  ulonglong uVar6;
  longlong *plVar7;
  bool bVar8;
  ulonglong in_stack_ffffffffffffffe8;
  if (DAT_188c96735 == '\0') {
    FUN_18048bf00(&DAT_18888bb20);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888af6c8);
    DAT_188c96735 = '\x01';
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18888bb20 + 0xb8) + 8);
  if (lVar2 == 0) {
    if (*(char *)(param_1 + 0x14) == '\0') {
      plVar5 = (longlong *)
               Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                         (param_4,*(undefined4 *)(param_1 + 0x10),0);
    }
    else {
      plVar5 = (longlong *)*param_4;
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = FUN_186b638d0(plVar5,0,0);
    if ((char)uVar6 != '\0') {
      return uVar6 & 0xffffffffffffff00;
    }
    if (plVar5 == (longlong *)0x0) {
      plVar7 = (longlong *)0x0;
    }
    else {
      lVar2 = *plVar5;
      if (DAT_188ccc7f0 == '\0') {
        if ((*(byte *)(lVar2 + 0x130) < *(byte *)(_DAT_1888af6c8 + 0x130)) ||
           (bVar8 = true,
           *(longlong *)
            (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_1888af6c8 + 0x130) * 8) !=
           _DAT_1888af6c8)) {
          bVar8 = false;
        }
        bVar8 = !bVar8;
      }
      else {
        cVar4 = func_0x0001804463e0(lVar2);
        bVar8 = cVar4 == '\0';
      }
      plVar7 = (longlong *)0x0;
      if (!bVar8) {
        plVar7 = plVar5;
      }
    }
    if (*(char *)(param_1 + 0x16) != '\0') {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar4 = FUN_186b63a70(plVar7,0,0);
      if (cVar4 != '\0') {
        if (plVar7 != (longlong *)0x0) {
          cVar4 = Torappu_Battle_RallyPoint_get_inRallyPointMode_0x6012e00(plVar7,0);
          if (cVar4 == '\0') {
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(*plVar7);
            }
            uVar6 = (**(code **)(*plVar7 + 0xfd0))
                              (plVar7,0,0,1,in_stack_ffffffffffffffe8 & 0xffffffffffffff00,
                               *(undefined8 *)(*plVar7 + 0xfd8));
            return uVar6;
          }
          return (ulonglong)*(byte *)(param_1 + 0x17);
        }
        goto LAB_181058e08;
      }
    }
    if (*(char *)(param_1 + 0x19) == '\0') {
      if (*(char *)(param_1 + 0x1a) == '\0') {
        if (plVar5 == (longlong *)0x0) {
LAB_181058e08:
          FUN_18048c0b0();
          pcVar3 = (code *)swi(3);
          uVar6 = (*pcVar3)();
          return uVar6;
        }
        Torappu_Battle_Entity_Suicide_0x6010414
                  (plVar5,*(undefined1 *)(param_1 + 0x15),*(undefined1 *)(param_1 + 0x18),0);
      }
      else {
        uVar1 = *(undefined1 *)(param_1 + 0x1b);
        if (plVar5 == (longlong *)0x0) goto LAB_181058e08;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar5);
        }
        (**(code **)(*plVar5 + 0x730))(plVar5,uVar1,*(undefined8 *)(*plVar5 + 0x738));
      }
    }
    else {
      if (plVar5 == (longlong *)0x0) goto LAB_181058e08;
      Torappu_Battle_Entity_FinishWithNoReason_0x6010415(plVar5,0);
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar5);
    }
    uVar6 = (**(code **)(*plVar5 + 0x3c0))(plVar5,*(undefined8 *)(*plVar5 + 0x3c8));
  }
  else {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar2,param_1,param_2,param_3,param_4,0);
  }
  return uVar6;
}

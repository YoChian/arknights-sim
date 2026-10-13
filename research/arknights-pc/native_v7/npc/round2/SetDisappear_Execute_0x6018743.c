/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
SetDisappear_Execute_0x6018743
          (longlong param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong *plVar6;
  bool bVar7;
  if (DAT_188c975c5 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1888c26b0);
    DAT_188c975c5 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888c26b0 + 0xb8) + 8);
  if (lVar1 == 0) {
    plVar4 = (longlong *)
             Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                       (param_4,*(undefined4 *)(param_1 + 0x10),0);
    if (plVar4 == (longlong *)0x0) {
      plVar6 = (longlong *)0x0;
    }
    else {
      lVar1 = *plVar4;
      if (DAT_188ccc7f0 == '\0') {
        if ((*(byte *)(lVar1 + 0x130) < *(byte *)(_DAT_18881b6b0 + 0x130)) ||
           (bVar7 = true,
           *(longlong *)
            (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_18881b6b0 + 0x130) * 8) !=
           _DAT_18881b6b0)) {
          bVar7 = false;
        }
        bVar7 = !bVar7;
      }
      else {
        cVar3 = func_0x0001804463e0(lVar1);
        bVar7 = cVar3 == '\0';
      }
      plVar6 = (longlong *)0x0;
      if (!bVar7) {
        plVar6 = plVar4;
      }
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b638d0(plVar6,0,0);
    if (cVar3 == '\0') {
      if (plVar6 == (longlong *)0x0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar5 = (*pcVar2)();
        return uVar5;
      }
      Torappu_Battle_BObject_SetDisappeared_0x600fe04(plVar6,*(undefined1 *)(param_1 + 0x14),0);
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
  }
  else {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar1,param_1,param_2,param_3,param_4,0);
  }
  return uVar5;
}

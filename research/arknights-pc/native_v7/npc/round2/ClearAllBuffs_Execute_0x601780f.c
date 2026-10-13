/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8
ClearAllBuffs_Execute_0x601780f
          (longlong param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4)
{
  code *pcVar1;
  char cVar2;
  longlong *plVar3;
  longlong lVar4;
  undefined8 uVar5;
  if (DAT_188c964c7 == '\0') {
    FUN_18048bf00(&DAT_188851b90);
    FUN_18048bf00(&DAT_18881b4c0);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c964c7 = '\x01';
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188851b90 + 0xb8) + 8);
  if (lVar4 != 0) {
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp11071_0x600359f
                      (lVar4,param_1,param_2,param_3,param_4,0);
    return uVar5;
  }
  plVar3 = (longlong *)
           Torappu_Battle_Action_Nodes_GetActionTarget_0x6017391
                     (param_4,*(undefined4 *)(param_1 + 0x10),0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = FUN_186b638d0(plVar3,0,0);
  if (cVar2 == '\0') {
    if (plVar3 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar3);
      }
      cVar2 = (**(code **)(*plVar3 + 0x3c0))(plVar3,*(undefined8 *)(*plVar3 + 0x3c8));
      if (cVar2 == '\0') {
        return 0;
      }
      cVar2 = FUN_1844acab0(*(undefined8 *)(param_1 + 0x18),_DAT_18881b4c0);
      if (cVar2 == '\0') {
        lVar4 = Torappu_Battle_Entity_get_buffContainer_0x6010363(plVar3);
        if (lVar4 != 0) {
          BuffContainer_ClearWithWhiteList_0x600ff4f
                    (lVar4,*(undefined8 *)(param_1 + 0x18),*(undefined1 *)(param_1 + 0x20),0);
          return 1;
        }
      }
      else {
        lVar4 = Torappu_Battle_Entity_get_buffContainer_0x6010363(plVar3,0);
        if (lVar4 != 0) {
          BuffContainer_Clear_0x600ff4e(lVar4,0,0);
          return 1;
        }
      }
    }
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    uVar5 = (*pcVar1)();
    return uVar5;
  }
  return 0;
}

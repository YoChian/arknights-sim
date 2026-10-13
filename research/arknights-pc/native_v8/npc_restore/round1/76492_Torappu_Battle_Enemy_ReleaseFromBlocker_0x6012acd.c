
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_ReleaseFromBlocker_0x6012acd(longlong param_1)

{
  code *pcVar1;
  char cVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong alStackX_18 [2];
  
  if (DAT_188c928b5 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_1889357e8);
    DAT_188c928b5 = '\x01';
  }
  alStackX_18[0] = 0;
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x6e8);
  if (lVar4 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar4,param_1,0);
    return;
  }
  cVar2 = FUN_185159fc0(param_1 + 0x398,_DAT_1889357e8);
  if (cVar2 != '\0') {
    plVar3 = (longlong *)FUN_185159d80(param_1 + 0x398,_DAT_1889355a8);
    if (plVar3 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar3);
      }
      cVar2 = (**(code **)(*plVar3 + 0x5d0))(plVar3,alStackX_18,*(undefined8 *)(*plVar3 + 0x5d8));
      if (cVar2 == '\0') goto LAB_180a742d1;
      if (alStackX_18[0] != 0) {
        lVar4 = FUN_180a64a50(alStackX_18[0],0);
        if (lVar4 != 0) {
          Torappu_Battle_BlockManager_RemoveBlockee_0x6012d8a(lVar4,alStackX_18[0],param_1,0);
          goto LAB_180a742d1;
        }
      }
    }
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
LAB_180a742d1:
  if (*(longlong *)(param_1 + 0x3f0) != 0) {
    FUN_1805e75e0(*(undefined8 *)(param_1 + 0x3f0),0,0);
  }
  return;
}


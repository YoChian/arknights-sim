
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_ObjectManager_Register_0x60115a3(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong *plVar4;
  bool bVar5;
  
  if (DAT_188c91749 == '\0') {
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_188970200);
    FUN_18048bf00(&DAT_1888233f8);
    FUN_18048bf00(&DAT_1888c4d98);
    DAT_188c91749 = '\x01';
  }
  if (*(longlong *)(param_1 + 0x10) != 0) {
    FUN_1851afc50(*(longlong *)(param_1 + 0x10),param_2,_DAT_188970200);
    if (param_2 == (longlong *)0x0) {
      plVar4 = (longlong *)0x0;
    }
    else {
      lVar1 = *param_2;
      if (DAT_188ccc7f0 == '\0') {
        if ((*(byte *)(lVar1 + 0x130) < *(byte *)(_DAT_1888233f8 + 0x130)) ||
           (bVar5 = true,
           *(longlong *)
            (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_1888233f8 + 0x130) * 8) !=
           _DAT_1888233f8)) {
          bVar5 = false;
        }
        bVar5 = !bVar5;
      }
      else {
        cVar3 = func_0x0001804463e0(lVar1);
        bVar5 = cVar3 == '\0';
      }
      plVar4 = (longlong *)0x0;
      if (!bVar5) {
        plVar4 = param_2;
      }
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b63a70(plVar4,0,0);
    if (cVar3 != '\0') {
      if (*(longlong *)(param_1 + 0x20) == 0) goto LAB_1808d57b9;
      FUN_18545acb0(*(longlong *)(param_1 + 0x20),plVar4,_DAT_1888c4d98);
    }
    return;
  }
LAB_1808d57b9:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


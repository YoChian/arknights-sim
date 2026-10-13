/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_Suicide_0x6010414
               (longlong *param_1,undefined1 param_2,undefined1 param_3)
{
  longlong lVar1;
  char cVar2;
  undefined8 uVar3;
  if (DAT_188c908aa == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_18885a700);
    DAT_188c908aa = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x6e8);
  if (lVar1 == 0) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar2 = (**(code **)(*param_1 + 0x3c0))(param_1,*(undefined8 *)(*param_1 + 0x3c8));
    if (cVar2 != '\0') {
      *(undefined1 *)((longlong)param_1 + 0xe9) = 1;
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uVar3 = func_0x0001866fdac0(0,0);
      FUN_1800134f0(0x6f,param_1,uVar3,1,param_2,param_3);
      return;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp264_0x6000b68(lVar1,param_1,param_2,param_3,0);
  }
  return;
}

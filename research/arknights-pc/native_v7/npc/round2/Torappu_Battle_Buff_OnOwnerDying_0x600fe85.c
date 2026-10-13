/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Buff_OnOwnerDying_0x600fe85(undefined8 param_1)
{
  longlong lVar1;
  char cVar2;
  undefined1 auStack_f8 [240];
  if (DAT_188c9030a == '\0') {
    FUN_18048bf00(&DAT_18895c250);
    DAT_188c9030a = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x360);
  if (lVar1 == 0) {
    cVar2 = Torappu_Battle_Buff__IsActionValid_0x600fe58(param_1,0x32);
    if (cVar2 != '\0') {
      Torappu_Battle_Buff__RunActions_0x600fee4(auStack_f8,param_1,0x32,1,0);
      return;
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,param_1,0);
  }
  return;
}

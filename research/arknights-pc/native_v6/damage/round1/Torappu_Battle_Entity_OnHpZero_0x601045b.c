/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnHpZero_0x601045b(longlong *param_1,char param_2,undefined1 param_3)
{
  code *pcVar1;
  longlong lVar2;
  if (DAT_188c908ea == '\0') {
    FUN_18048bf00(&DAT_188841368);
    DAT_188c908ea = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x8f0);
  if (lVar2 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp264_0x6000b68(lVar2,param_1,param_2,param_3,0);
    return;
  }
  lVar2 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
  if (lVar2 == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  BuffContainer_OnOwnerBeforeDead_0x600ffac(lVar2,0);
  if (param_2 == '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
                    /* WARNING: Could not recover jumptable at 0x0001806f9236. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x890))(param_1,2,*(undefined8 *)(*param_1 + 0x898));
    return;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x0001806f9272. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x890))(param_1,8,*(undefined8 *)(*param_1 + 0x898));
  return;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard__ctor_0x600f6d6(longlong param_1)

{
  code *pcVar1;
  longlong lVar2;
  bool bVar3;
  
  if (DAT_188c8fd54 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_1888e29b0);
    FUN_18048bf00(&DAT_1888048a0);
    DAT_188c8fd54 = '\x01';
  }
  lVar2 = func_0x00018045cfe0(_DAT_1888048a0);
  if (lVar2 != 0) {
    FUN_1848f2320(lVar2,_DAT_1888e29b0);
    *(longlong *)(param_1 + 0xd8) = lVar2;
    func_0x00018048b9e0(param_1 + 0xd8,lVar2);
    bVar3 = DAT_188c8fd11 == '\0';
    *(undefined4 *)(param_1 + 0xf8) = 0x3f800000;
    if (bVar3) {
      FUN_18048bf00(&DAT_1889733f0);
      FUN_18048bf00(&DAT_18892d860);
      FUN_18048bf00(&DAT_188908578);
      FUN_18048bf00(&DAT_18895fa98);
      DAT_188c8fd11 = '\x01';
    }
    *(undefined1 *)(param_1 + 0x49) = 1;
    lVar2 = func_0x00018045cfe0(_DAT_18895fa98);
    if (lVar2 != 0) {
      Torappu_PeriodicTimer__ctor_0x6006573(lVar2,0);
      *(longlong *)(param_1 + 0x70) = lVar2;
      func_0x00018048b9e0(param_1 + 0x70,lVar2);
      lVar2 = func_0x00018045cfe0(_DAT_188908578);
      if (lVar2 != 0) {
        FUN_1848f2320(lVar2,_DAT_18892d860);
        *(longlong *)(param_1 + 0x78) = lVar2;
        func_0x00018048b9e0(param_1 + 0x78,lVar2);
        func_0x0001805111c0(param_1,0);
        lVar2 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x2b0);
        if (lVar2 != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar2,param_1,0);
        }
        lVar2 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x200);
        if (lVar2 != 0) {
          XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar2,param_1,0);
        }
        return;
      }
    }
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_Map_GenerateRuntimeRoute_0x601119e
                   (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  code *pcVar1;
  longlong lVar2;
  
  if (DAT_188c9145e == '\0') {
    FUN_18048bf00(&DAT_1888bca40);
    FUN_18048bf00(&DAT_18881e838);
    DAT_188c9145e = '\x01';
  }
  if (*(int *)(_DAT_1888bca40 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_1888bca40);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_1888bca40 + 0xb8) + 0x2b0);
  if (lVar2 == 0) {
    lVar2 = func_0x00018045cfe0(_DAT_18881e838);
    if (lVar2 != 0) {
      Torappu_Battle_Route__ctor_0x60112d5(lVar2,param_2,param_1,param_3,0);
      Torappu_Battle_Route_ReconstructNextMap_0x60112db(lVar2,0);
      return lVar2;
    }
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    lVar2 = (*pcVar1)();
    return lVar2;
  }
  lVar2 = XLua_DelegateBridge___Gen_Delegate_Imp3307_0x600174b(lVar2,param_1,param_2,param_3,0);
  return lVar2;
}


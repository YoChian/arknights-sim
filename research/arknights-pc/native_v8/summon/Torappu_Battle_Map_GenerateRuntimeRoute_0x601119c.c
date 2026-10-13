
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_Map_GenerateRuntimeRoute_0x601119c
                   (longlong param_1,undefined4 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  
  if (DAT_188c9145c == '\0') {
    FUN_18048bf00(&DAT_188803328);
    FUN_18048bf00(&DAT_188803568);
    FUN_18048bf00(&DAT_1888039e8);
    FUN_18048bf00(&DAT_1888bca40);
    FUN_18048bf00(&DAT_18881e838);
    DAT_188c9145c = '\x01';
  }
  if (*(int *)(_DAT_1888bca40 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_1888bca40);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_1888bca40 + 0xb8) + 0x2a0);
  if (lVar4 == 0) {
    if (*(longlong *)(param_1 + 0x80) != 0) {
      cVar3 = FUN_184a84370(*(longlong *)(param_1 + 0x80),param_2,_DAT_188803568);
      if (cVar3 == '\0') {
        uVar1 = *(undefined8 *)(param_1 + 0xb0);
        lVar4 = func_0x00018045cfe0(_DAT_18881e838);
        if (lVar4 != 0) {
          Torappu_Battle_Route__ctor_0x60112d5(lVar4,param_3,param_1,uVar1,0);
          Torappu_Battle_Route_ReconstructNextMap_0x60112db(lVar4,0);
          if (*(longlong *)(param_1 + 0x80) != 0) {
            FUN_184a81fb0(*(longlong *)(param_1 + 0x80),param_2,lVar4,_DAT_188803328);
            return lVar4;
          }
        }
      }
      else if ((*(longlong *)(param_1 + 0x80) != 0) &&
              (lVar4 = FUN_184a8da30(*(longlong *)(param_1 + 0x80),param_2,_DAT_1888039e8),
              lVar4 != 0)) {
        Torappu_Battle_Route_ReconstructRoute_0x60112d6(lVar4,param_3,0);
        if (*(longlong *)(param_1 + 0x80) != 0) {
          lVar4 = FUN_184a8da30(*(longlong *)(param_1 + 0x80),param_2,_DAT_1888039e8);
          return lVar4;
        }
      }
    }
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    lVar4 = (*pcVar2)();
    return lVar4;
  }
  lVar4 = XLua_DelegateBridge___Gen_Delegate_Imp3305_0x6001749(lVar4,param_1,param_2,param_3,0);
  return lVar4;
}


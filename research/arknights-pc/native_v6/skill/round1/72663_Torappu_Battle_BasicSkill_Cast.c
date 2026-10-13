
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_BasicSkill_Cast_0x6011bd8(longlong *param_1,undefined8 param_2,undefined4 param_3)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  longlong lVar9;
  
  if (DAT_188c91c4c == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_18896a750);
    DAT_188c91c4c = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x2c0);
  if (lVar9 != 0) {
    uVar6 = XLua_DelegateBridge___Gen_Delegate_Imp2812_0x600155c(lVar9,param_1,param_2,param_3,0);
    return uVar6;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar4 = (**(code **)(*param_1 + 0x270))(param_1,param_3,*(undefined8 *)(*param_1 + 0x278));
  if (cVar4 == '\0') {
    return 0;
  }
  cVar4 = FUN_18000f7a0(0x34,param_1,param_2,param_3);
  if (cVar4 != '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 0x550))(param_1,*(undefined8 *)(*param_1 + 0x558));
    return 1;
  }
  uVar7 = 0;
  iVar5 = FUN_1844afc00(param_1[0x1b],_DAT_18896a750);
  if (0 < iVar5) {
    lVar9 = 0x20;
    uVar8 = uVar7;
    do {
      lVar1 = param_1[0x1b];
      if (lVar1 == 0) {
LAB_180959451:
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        uVar6 = (*pcVar3)();
        return uVar6;
      }
      if (*(uint *)(lVar1 + 0x18) <= (uint)uVar8) {
        FUN_18048c0a0();
        pcVar3 = (code *)swi(3);
        uVar6 = (*pcVar3)();
        return uVar6;
      }
      plVar2 = *(longlong **)(lVar9 + lVar1);
      if (plVar2 == (longlong *)0x0) goto LAB_180959451;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar2);
      }
      (**(code **)(*plVar2 + 0x1b0))(plVar2,*(undefined8 *)(*plVar2 + 0x1b8));
      uVar8 = (ulonglong)((uint)uVar8 + 1);
      uVar7 = uVar7 + 1;
      lVar9 = lVar9 + 8;
    } while ((longlong)uVar7 < (longlong)iVar5);
  }
  return 0;
}


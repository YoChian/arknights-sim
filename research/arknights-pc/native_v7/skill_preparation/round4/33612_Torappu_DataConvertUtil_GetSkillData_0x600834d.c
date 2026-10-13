
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_DataConvertUtil_GetSkillData_0x600834d(undefined8 param_1,int param_2,int param_3)

{
  code *pcVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iStack_18;
  int iStack_14;
  longlong lStack_10;
  
  if (DAT_188ca8181 == '\0') {
    FUN_18048bf00(&DAT_18892ea20);
    FUN_18048bf00(&DAT_188932da0);
    FUN_18048bf00(&DAT_188848cb0);
    FUN_18048bf00(&DAT_1888c94c8);
    FUN_18048bf00(&DAT_1888eff00);
    DAT_188ca8181 = '\x01';
  }
  lStack_10 = 0;
  lVar2 = *(longlong *)(*(longlong *)(_DAT_188932da0 + 0xb8) + 0x50);
  if (lVar2 == 0) {
    lVar2 = FUN_1853364a0(_DAT_1888c94c8);
    if (lVar2 == 0) {
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      lVar2 = (*pcVar1)();
      return lVar2;
    }
    Torappu_SkillDB_TryGetSkill_0x6006cc1(lVar2,param_1,param_2 + param_3,&lStack_10,0);
    if (lStack_10 == 0) {
      iStack_18 = param_2;
      uVar3 = func_0x00018048b9c0(_DAT_188848cb0,&iStack_18);
      iStack_14 = param_3;
      uVar4 = func_0x00018048b9c0(_DAT_188848cb0,&iStack_14);
      uVar3 = System_String_Format_0x600030e(_DAT_1888eff00,param_1,uVar3,uVar4,0);
      if (*(int *)(_DAT_18892ea20 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      UnityEngine_DLog_LogError_0x6000031(uVar3,0);
    }
  }
  else {
    lStack_10 = XLua_DelegateBridge___Gen_Delegate_Imp11769_0x6003859
                          (lVar2,param_1,param_2,param_3,0);
  }
  return lStack_10;
}


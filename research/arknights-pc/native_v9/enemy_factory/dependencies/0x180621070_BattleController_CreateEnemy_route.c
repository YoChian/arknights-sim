
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong *
Torappu_Battle_BattleController_CreateEnemy_0x600fcbf
          (longlong param_1,longlong param_2,undefined8 param_3,undefined4 *param_4,
          undefined8 param_5,undefined8 *param_6)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong *plVar4;
  undefined8 uVar5;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  if (DAT_188c900e9 == '\0') {
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18892ea20);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_18894d6b0);
    DAT_188c900e9 = '\x01';
  }
  if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188927d60);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188927d60 + 0xb8) + 0x898);
  if (lVar1 == 0) {
    if ((param_2 == 0) || (*(longlong *)(param_1 + 0x38) == 0)) {
LAB_1806212b1:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      plVar4 = (longlong *)(*pcVar2)();
      return plVar4;
    }
    plVar4 = (longlong *)
             Torappu_Battle_BattleFactory_CreateEnemy_0x60117c0
                       (*(longlong *)(param_1 + 0x38),*(undefined8 *)(param_2 + 0x20),0);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b638d0(plVar4,0,0);
    if (cVar3 == '\0') {
      if (plVar4 == (longlong *)0x0) goto LAB_1806212b1;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar4);
      }
      uStack_38 = *param_6;
      uStack_30 = param_6[1];
      uStack_28 = param_6[2];
      uStack_20 = param_6[3];
      uStack_18 = param_6[4];
      uStack_10 = param_6[5];
      uStack_58 = *param_4;
      uStack_54 = param_4[1];
      uStack_50 = param_4[2];
      uStack_4c = param_4[3];
      uStack_48 = *(undefined8 *)(param_4 + 4);
      (**(code **)(*plVar4 + 0xfb0))
                (plVar4,param_2,param_3,&uStack_58,param_5,&uStack_38,
                 *(undefined8 *)(*plVar4 + 0xfb8));
    }
    else {
      uVar5 = System_String_Concat_0x6000308(_DAT_18894d6b0,*(undefined8 *)(param_2 + 0x20),0);
      if (*(int *)(_DAT_18892ea20 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      UnityEngine_DLog_LogError_0x6000031(uVar5,0);
      plVar4 = (longlong *)0x0;
    }
  }
  else {
    uStack_38 = *param_6;
    uStack_30 = param_6[1];
    uStack_28 = param_6[2];
    uStack_20 = param_6[3];
    uStack_18 = param_6[4];
    uStack_10 = param_6[5];
    uStack_58 = *param_4;
    uStack_54 = param_4[1];
    uStack_50 = param_4[2];
    uStack_4c = param_4[3];
    uStack_48 = *(undefined8 *)(param_4 + 4);
    plVar4 = (longlong *)
             XLua_DelegateBridge___Gen_Delegate_Imp2840_0x6001578
                       (lVar1,param_1,param_2,param_3,&uStack_58,param_5,&uStack_38,0);
  }
  return plVar4;
}


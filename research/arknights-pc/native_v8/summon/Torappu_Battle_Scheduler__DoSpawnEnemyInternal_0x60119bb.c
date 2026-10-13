
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
Torappu_Battle_Scheduler__DoSpawnEnemyInternal_0x60119bb
          (longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined1 auStack_38 [32];
  
  if (DAT_188c91a57 == '\0') {
    FUN_18048bf00(&DAT_1888cb668);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_18891b6c0);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c91a57 = '\x01';
  }
  uStack_a8 = 0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  lVar3 = *(longlong *)(*(longlong *)(_DAT_18891b6c0 + 0xb8) + 0x278);
  if (lVar3 == 0) {
    if (*(char *)(param_1 + 0x110) == '\0') {
      uStack_68 = param_4[2];
      uStack_60 = param_4[3];
      uStack_58 = param_4[4];
      uStack_50 = param_4[5];
      if (*(char *)(param_4 + 1) != '\0') {
        return 0;
      }
    }
    uVar5 = 0;
    if (*(longlong *)(param_1 + 0xa8) == 0) {
LAB_18091b567:
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      uVar5 = (*pcVar1)();
      return uVar5;
    }
    cVar2 = FUN_185879190(*(longlong *)(param_1 + 0xa8),param_2,&uStack_b8,_DAT_1888cb668);
    if (cVar2 != '\0') {
      lVar3 = FUN_185337c50(_DAT_1888d3908);
      uStack_48 = uStack_b8;
      uStack_40 = uStack_b0;
      uStack_88 = uStack_a8;
      puVar4 = (undefined8 *)Torappu_Battle_Scheduler_TakeSnapshot_0x601199c(auStack_38,param_1,0);
      if (lVar3 == 0) goto LAB_18091b567;
      uStack_68 = param_4[2];
      uStack_60 = param_4[3];
      uStack_78 = *param_4;
      uStack_70 = param_4[1];
      uStack_98 = *puVar4;
      uStack_90 = puVar4[1];
      uStack_58 = param_4[4];
      uStack_50 = param_4[5];
      uStack_88 = puVar4[2];
      uVar5 = Torappu_Battle_BattleController_CreateEnemy_0x600fcbf
                        (lVar3,uStack_48,uStack_40,&uStack_98,param_3,&uStack_78,0);
    }
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar2 = FUN_186b638d0(uVar5,0,0);
    if (cVar2 != '\0') {
      Torappu_Battle_Scheduler__AlertSpawnError_0x60119bc(param_1,param_2,0);
    }
  }
  else {
    uStack_78 = *param_4;
    uStack_70 = param_4[1];
    uStack_68 = param_4[2];
    uStack_60 = param_4[3];
    uStack_58 = param_4[4];
    uStack_50 = param_4[5];
    uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp3534_0x600182e
                      (lVar3,param_1,param_2,param_3,&uStack_78,0);
  }
  return uVar5;
}


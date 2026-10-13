
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_Spawn_0x6012a83
               (longlong *param_1,longlong param_2,undefined8 param_3,undefined8 *param_4,
               longlong param_5,undefined8 *param_6)

{
  undefined4 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  if (DAT_188c9286b == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c9286b = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x498);
  uStack_38 = *param_6;
  uStack_30 = param_6[1];
  uStack_28 = *(undefined4 *)(param_6 + 2);
  uStack_24 = *(undefined4 *)((longlong)param_6 + 0x14);
  uStack_58 = param_6[2];
  uStack_50 = *(undefined4 *)(param_6 + 3);
  uStack_4c = *(undefined4 *)((longlong)param_6 + 0x1c);
  if (lVar2 != 0) {
    uStack_18 = param_6[4];
    uStack_10 = param_6[5];
    uStack_68 = *param_4;
    uStack_60 = param_4[1];
    uStack_58 = param_4[2];
    uStack_20 = uStack_50;
    uStack_1c = uStack_4c;
    XLua_DelegateBridge___Gen_Delegate_Imp3463_0x60017e7
              (lVar2,param_1,param_2,param_3,&uStack_68,param_5,&uStack_38,0);
    return;
  }
  uStack_48 = *(undefined4 *)(param_6 + 4);
  uStack_44 = *(undefined4 *)((longlong)param_6 + 0x24);
  uStack_40 = *(undefined4 *)(param_6 + 5);
  uStack_3c = *(undefined4 *)((longlong)param_6 + 0x2c);
  uStack_68 = uStack_38;
  uStack_60 = uStack_30;
  Torappu_Battle_Enemy_set_options_0x6012a4e(param_1,&uStack_68,0);
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  uStack_68 = *param_4;
  uStack_60 = param_4[1];
  uStack_58 = param_4[2];
  (**(code **)(*param_1 + 0x1000))
            (param_1,param_2,param_3,&uStack_68,param_5,*(undefined8 *)(*param_1 + 0x1008));
  if ((param_5 != 0) &&
     (iVar4 = Torappu_Battle_Route_get_motionMode_0x60112d2(param_5,0), param_2 != 0)) {
    if (iVar4 != *(int *)(param_2 + 0x34)) {
      uVar1 = *(undefined4 *)(param_2 + 0x34);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      (**(code **)(*param_1 + 0x750))(param_1,uVar1,*(undefined8 *)(*param_1 + 0x758));
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 0x2c0))(param_1,*(undefined8 *)(*param_1 + 0x2c8));
    return;
  }
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


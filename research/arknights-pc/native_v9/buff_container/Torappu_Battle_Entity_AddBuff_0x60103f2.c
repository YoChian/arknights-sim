
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_AddBuff_0x60103f2
               (undefined8 param_1,longlong param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_188c90888 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    DAT_188c90888 = '\x01';
  }
  uStack_28 = 0;
  uStack_20 = 0;
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x5d8);
  if (lVar1 == 0) {
    cVar3 = Torappu_Battle_BuffDBUtil_TryGetBuff_0x60131c1(param_2,&uStack_28,0);
    if (cVar3 == '\0') {
      uVar4 = func_0x00018048bf20(0x188932918);
      uVar5 = func_0x00018048ba50(uVar4,5);
      FUN_180005cb0(uVar5);
      uVar4 = func_0x00018048bf20(0x1887f7b10);
      FUN_180005fe0(uVar5,0,uVar4);
      FUN_180005cb0(param_2);
      uVar4 = *(undefined8 *)(param_2 + 0x18);
      FUN_180005cb0(uVar5);
      FUN_180005fe0(uVar5,1,uVar4);
      FUN_180005cb0(uVar5);
      uVar4 = func_0x00018048bf20(0x18890e300);
      FUN_180005fe0(uVar5,2,uVar4);
      FUN_180005cb0(param_2);
      uVar4 = *(undefined8 *)(param_2 + 0x30);
      FUN_180005cb0(uVar5);
      FUN_180005fe0(uVar5,3,uVar4);
      FUN_180005cb0(uVar5);
      uVar4 = func_0x00018048bf20(0x18890e540);
      FUN_180005fe0(uVar5,4,uVar4);
      uVar4 = System_String_Concat_0x600030b(uVar5,0);
      uVar5 = func_0x00018048bf20(0x1888ac650);
      uVar5 = func_0x00018045cfe0(uVar5);
      FUN_180005cb0(uVar5);
      Torappu_GameDataException__ctor_0x6005758(uVar5,uVar4,0);
      uVar4 = func_0x00018048bf20(0x188848c48);
      FUN_18048c070(uVar5,uVar4);
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStack_18 = (undefined4)uStack_28;
    uStack_14 = uStack_28._4_4_;
    uStack_10 = (undefined4)uStack_20;
    uStack_c = uStack_20._4_4_;
    Torappu_Battle_Entity_AddBuff_0x60103f1
              (param_1,&uStack_18,param_3,param_4,param_5,param_6,param_7,param_8,0);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp3043_0x6001643
              (lVar1,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  }
  return;
}


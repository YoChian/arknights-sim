/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 *
Torappu_Battle_Modifier_NewLifePointDelta_0x6011566
          (undefined8 *param_1,int param_2,undefined8 param_3,undefined4 param_4)
{
  longlong lVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  int iVar4;
  undefined8 in_stack_ffffffffffffff38;
  undefined4 uVar5;
  undefined1 auStack_a8 [144];
  uVar5 = (undefined4)((ulonglong)in_stack_ffffffffffffff38 >> 0x20);
  if (DAT_188c9171b == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00();
    DAT_188c9171b = '\x01';
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0x268);
  if (lVar1 == 0) {
    if (DAT_188c90f80 == '\0') {
      FUN_18048bf00(&DAT_1888c37c0);
      DAT_188c90f80 = '\x01';
    }
    if (*(int *)(_DAT_1888c37c0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    iVar4 = -param_2;
    if (-param_2 < 0) {
      iVar4 = param_2;
    }
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar2 = func_0x0001866fdac0(iVar4,0);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0x10] = 0;
    Torappu_Battle_Modifier__ctor_0x601155a
              (param_1,4,(param_2 >> 0x1f & 1U) + 1,uVar2,param_3,0,param_4,0);
  }
  else {
    puVar3 = (undefined8 *)
             XLua_DelegateBridge___Gen_Delegate_Imp3435_0x60017cb
                       (auStack_a8,lVar1,param_2,param_3,CONCAT44(uVar5,param_4),0);
    uVar2 = puVar3[1];
    *param_1 = *puVar3;
    param_1[1] = uVar2;
    uVar2 = puVar3[3];
    param_1[2] = puVar3[2];
    param_1[3] = uVar2;
    uVar2 = puVar3[5];
    param_1[4] = puVar3[4];
    param_1[5] = uVar2;
    uVar2 = puVar3[7];
    param_1[6] = puVar3[6];
    param_1[7] = uVar2;
    uVar2 = puVar3[9];
    param_1[8] = puVar3[8];
    param_1[9] = uVar2;
    uVar2 = puVar3[0xb];
    param_1[10] = puVar3[10];
    param_1[0xb] = uVar2;
    uVar2 = puVar3[0xd];
    param_1[0xc] = puVar3[0xc];
    param_1[0xd] = uVar2;
    uVar2 = puVar3[0xf];
    param_1[0xe] = puVar3[0xe];
    param_1[0xf] = uVar2;
    param_1[0x10] = puVar3[0x10];
  }
  return param_1;
}

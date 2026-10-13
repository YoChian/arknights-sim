/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 *
Torappu_Battle_Modifier_NewTrySetHpZero_0x6011567
          (undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)
{
  longlong lVar1;
  byte bVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  undefined8 in_stack_ffffffffffffff48;
  undefined4 uVar5;
  undefined1 auStack_98 [144];
  uVar5 = (undefined4)((ulonglong)in_stack_ffffffffffffff48 >> 0x20);
  if (DAT_188c9171c == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00();
    DAT_188c9171c = '\x01';
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0x270);
  if (lVar1 == 0) {
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar3 = func_0x0001866fdac0(0,0);
    bVar2 = func_0x000185ed91b0(param_2,uVar3,0);
    if (*(int *)(_DAT_1888915d8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar3 = Torappu_TSMath_Abs_0x600034b(param_2,0);
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
    Torappu_Battle_Modifier__ctor_0x601155a(param_1,8,(bVar2 ^ 1) + 1,uVar3,param_3,0,param_4,0);
  }
  else {
    puVar4 = (undefined8 *)
             XLua_DelegateBridge___Gen_Delegate_Imp3434_0x60017ca
                       (auStack_98,lVar1,param_2,param_3,CONCAT44(uVar5,param_4),0);
    uVar3 = puVar4[1];
    *param_1 = *puVar4;
    param_1[1] = uVar3;
    uVar3 = puVar4[3];
    param_1[2] = puVar4[2];
    param_1[3] = uVar3;
    uVar3 = puVar4[5];
    param_1[4] = puVar4[4];
    param_1[5] = uVar3;
    uVar3 = puVar4[7];
    param_1[6] = puVar4[6];
    param_1[7] = uVar3;
    uVar3 = puVar4[9];
    param_1[8] = puVar4[8];
    param_1[9] = uVar3;
    uVar3 = puVar4[0xb];
    param_1[10] = puVar4[10];
    param_1[0xb] = uVar3;
    uVar3 = puVar4[0xd];
    param_1[0xc] = puVar4[0xc];
    param_1[0xd] = uVar3;
    uVar3 = puVar4[0xf];
    param_1[0xe] = puVar4[0xe];
    param_1[0xf] = uVar3;
    param_1[0x10] = puVar4[0x10];
  }
  return param_1;
}

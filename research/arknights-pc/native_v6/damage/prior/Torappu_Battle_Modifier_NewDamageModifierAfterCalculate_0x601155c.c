/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined8 *
Torappu_Battle_Modifier_NewDamageModifierAfterCalculate_0x601155c
          (undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
          undefined4 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8,
          undefined8 param_9)
{
  longlong lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 in_stack_fffffffffffffe98;
  undefined8 in_stack_fffffffffffffea0;
  undefined8 in_stack_fffffffffffffeb0;
  uint uVar9;
  undefined8 in_stack_fffffffffffffeb8;
  undefined4 uVar10;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined1 auStack_98 [144];
  uVar9 = (uint)((ulonglong)in_stack_fffffffffffffeb0 >> 0x20);
  uVar7 = (undefined4)((ulonglong)in_stack_fffffffffffffe98 >> 0x20);
  uVar8 = (undefined4)((ulonglong)in_stack_fffffffffffffea0 >> 0x20);
  uVar10 = (undefined4)((ulonglong)in_stack_fffffffffffffeb8 >> 0x20);
  if (DAT_188c91711 == '\0') {
    FUN_18048bf00(&DAT_1888ed178);
    DAT_188c91711 = '\x01';
  }
  uStack_128 = 0;
  uStack_120 = 0;
  uStack_a8 = 0;
  uStack_118 = 0;
  uStack_110 = 0;
  uStack_108 = 0;
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_e8 = 0;
  uStack_e0 = 0;
  uStack_d8 = 0;
  uStack_d0 = 0;
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888ed178 + 0xb8) + 0x218);
  if (lVar1 == 0) {
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_Modifier__ctor_0x6011559
              (&uStack_128,0,2,param_2,param_3,param_6,param_7,(ulonglong)uVar9 << 0x20,0);
    Torappu_Battle_Modifier_set_damageType_0x6011537(&uStack_128,param_4,0);
    Torappu_Battle_Modifier_set_applyWay_0x6011539(&uStack_128,param_5,0);
    Torappu_Battle_Modifier_set_attackType_0x601153d(&uStack_128,param_8,0);
    Torappu_Battle_Modifier_set_originAtk_0x6011541(&uStack_128,param_9,0);
    *param_1 = uStack_128;
    param_1[1] = uStack_120;
    param_1[2] = uStack_118;
    param_1[3] = uStack_110;
    param_1[4] = uStack_108;
    param_1[5] = uStack_100;
    param_1[6] = uStack_f8;
    param_1[7] = uStack_f0;
    param_1[8] = uStack_e8;
    param_1[9] = uStack_e0;
    param_1[10] = uStack_d8;
    param_1[0xb] = uStack_d0;
    param_1[0xc] = uStack_c8;
    param_1[0xd] = uStack_c0;
    uVar7 = (undefined4)uStack_a8;
    uVar8 = (undefined4)((ulonglong)uStack_a8 >> 0x20);
  }
  else {
    puVar6 = (undefined8 *)
             XLua_DelegateBridge___Gen_Delegate_Imp3430_0x60017c6
                       (auStack_98,lVar1,param_2,param_3,CONCAT44(uVar7,param_4),
                        CONCAT44(uVar8,param_5),param_6,param_7,CONCAT44(uVar10,param_8),param_9,0);
    uVar2 = puVar6[1];
    uVar3 = puVar6[2];
    uVar4 = puVar6[3];
    *param_1 = *puVar6;
    param_1[1] = uVar2;
    uVar2 = puVar6[4];
    uVar5 = puVar6[5];
    param_1[2] = uVar3;
    param_1[3] = uVar4;
    uVar3 = puVar6[6];
    uVar4 = puVar6[7];
    param_1[4] = uVar2;
    param_1[5] = uVar5;
    uVar2 = puVar6[8];
    uVar5 = puVar6[9];
    param_1[6] = uVar3;
    param_1[7] = uVar4;
    uVar3 = puVar6[10];
    uVar4 = puVar6[0xb];
    param_1[8] = uVar2;
    param_1[9] = uVar5;
    uVar2 = puVar6[0xc];
    uVar5 = puVar6[0xd];
    param_1[10] = uVar3;
    param_1[0xb] = uVar4;
    uStack_b8._0_4_ = *(undefined4 *)(puVar6 + 0xe);
    uStack_b8._4_4_ = *(undefined4 *)((longlong)puVar6 + 0x74);
    uStack_b0._0_4_ = *(undefined4 *)(puVar6 + 0xf);
    uStack_b0._4_4_ = *(undefined4 *)((longlong)puVar6 + 0x7c);
    param_1[0xc] = uVar2;
    param_1[0xd] = uVar5;
    uVar7 = (undefined4)puVar6[0x10];
    uVar8 = (undefined4)((ulonglong)puVar6[0x10] >> 0x20);
  }
  *(undefined4 *)(param_1 + 0xe) = (undefined4)uStack_b8;
  *(undefined4 *)((longlong)param_1 + 0x74) = uStack_b8._4_4_;
  *(undefined4 *)(param_1 + 0xf) = (undefined4)uStack_b0;
  *(undefined4 *)((longlong)param_1 + 0x7c) = uStack_b0._4_4_;
  param_1[0x10] = CONCAT44(uVar8,uVar7);
  return param_1;
}

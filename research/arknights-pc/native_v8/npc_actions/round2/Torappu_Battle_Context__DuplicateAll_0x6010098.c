
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * Torappu_Battle_Context__DuplicateAll_0x6010098(undefined8 *param_1,longlong param_2)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined8 uStack_108;
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
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  
  if (DAT_188c905b1 == '\0') {
    FUN_18048bf00(&DAT_18891f750);
    FUN_18048bf00(&DAT_18891ee50);
    FUN_18048bf00(&DAT_18891d7d8);
    FUN_18048bf00(&DAT_18891e318);
    FUN_18048bf00(&DAT_1889312e8);
    FUN_18048bf00(&DAT_18892ea68);
    FUN_18048bf00(&DAT_188944068);
    FUN_18048bf00(&DAT_188938128);
    DAT_188c905b1 = '\x01';
  }
  FUN_180501c30(param_1,0,0xf0);
  puVar7 = (undefined8 *)Torappu_Battle_Context_TakeSnapshot_0x6010095(&uStack_f8,param_2,0);
  uVar3 = puVar7[1];
  uVar4 = puVar7[2];
  uVar5 = puVar7[3];
  *param_1 = *puVar7;
  param_1[1] = uVar3;
  uVar3 = puVar7[4];
  uVar6 = puVar7[5];
  param_1[2] = uVar4;
  param_1[3] = uVar5;
  uVar4 = puVar7[6];
  uVar5 = puVar7[7];
  param_1[4] = uVar3;
  param_1[5] = uVar6;
  uVar3 = puVar7[8];
  uVar6 = puVar7[9];
  param_1[6] = uVar4;
  param_1[7] = uVar5;
  uVar4 = puVar7[10];
  uVar5 = puVar7[0xb];
  param_1[8] = uVar3;
  param_1[9] = uVar6;
  uVar3 = puVar7[0xc];
  uVar6 = puVar7[0xd];
  param_1[10] = uVar4;
  param_1[0xb] = uVar5;
  uVar4 = puVar7[0x10];
  uVar5 = puVar7[0x11];
  param_1[0xc] = uVar3;
  param_1[0xd] = uVar6;
  uVar3 = puVar7[0xf];
  param_1[0xe] = puVar7[0xe];
  param_1[0xf] = uVar3;
  uVar3 = puVar7[0x12];
  uVar6 = puVar7[0x13];
  param_1[0x10] = uVar4;
  param_1[0x11] = uVar5;
  uVar4 = puVar7[0x14];
  uVar5 = puVar7[0x15];
  param_1[0x12] = uVar3;
  param_1[0x13] = uVar6;
  uVar3 = puVar7[0x16];
  uVar6 = puVar7[0x17];
  param_1[0x14] = uVar4;
  param_1[0x15] = uVar5;
  uVar4 = puVar7[0x18];
  uVar5 = puVar7[0x19];
  param_1[0x16] = uVar3;
  param_1[0x17] = uVar6;
  uVar3 = puVar7[0x1a];
  uVar6 = puVar7[0x1b];
  param_1[0x18] = uVar4;
  param_1[0x19] = uVar5;
  uVar4 = puVar7[0x1c];
  uVar5 = puVar7[0x1d];
  lVar1 = *(longlong *)(param_2 + 0x10);
  param_1[0x1a] = uVar3;
  param_1[0x1b] = uVar6;
  uVar3 = *puVar7;
  param_1[0x1c] = uVar4;
  param_1[0x1d] = uVar5;
  if (lVar1 != 0) {
    FUN_185733520(lVar1,uVar3,_DAT_18891e318);
    if (*(longlong *)(param_2 + 0x18) != 0) {
      FUN_185733520(*(longlong *)(param_2 + 0x18),param_1[1],_DAT_18891e318);
      if (*(longlong *)(param_2 + 0x20) != 0) {
        FUN_185733520(*(longlong *)(param_2 + 0x20),param_1[2],_DAT_18891d7d8);
        if (*(longlong *)(param_2 + 0x28) != 0) {
          FUN_185367f40(*(longlong *)(param_2 + 0x28),param_1[3],_DAT_18892ea68);
          lVar1 = *(longlong *)(param_2 + 0x30);
          if (lVar1 != 0) {
            uStack_188 = (undefined4)param_1[0x12];
            uStack_184 = (undefined4)((ulonglong)param_1[0x12] >> 0x20);
            uStack_180 = (undefined4)param_1[0x13];
            uStack_17c = (undefined4)((ulonglong)param_1[0x13] >> 0x20);
            uStack_88 = uStack_188;
            uStack_84 = uStack_184;
            uStack_80 = uStack_180;
            uStack_7c = uStack_17c;
            uStack_f8 = param_1[4];
            uStack_f0 = param_1[5];
            uStack_e8 = param_1[6];
            uStack_e0 = param_1[7];
            uStack_d8 = param_1[8];
            uStack_d0 = param_1[9];
            uStack_c8 = param_1[10];
            uStack_c0 = param_1[0xb];
            uStack_b8 = param_1[0xc];
            uStack_b0 = param_1[0xd];
            uStack_a8 = param_1[0xe];
            uStack_a0 = param_1[0xf];
            uStack_98 = param_1[0x10];
            uStack_90 = param_1[0x11];
            uStack_78 = param_1[0x14];
            FUN_185368160(lVar1,&uStack_f8,_DAT_188938128,lVar1,*param_1,param_1[1],param_1[2],
                          param_1[3]);
            if (*(longlong *)(param_2 + 0x38) != 0) {
              FUN_185733520(*(longlong *)(param_2 + 0x38),param_1[0x15],_DAT_18891ee50);
              if (*(longlong *)(param_2 + 0x40) != 0) {
                FUN_185733520(*(longlong *)(param_2 + 0x40),param_1[0x16],_DAT_18891f750);
                if (*(longlong *)(param_2 + 0x50) != 0) {
                  FUN_185367f40(*(longlong *)(param_2 + 0x50),param_1[0x17],_DAT_1889312e8);
                  if (*(longlong *)(param_2 + 0x48) != 0) {
                    uStack_128 = param_1[0x18];
                    uStack_120 = param_1[0x19];
                    uStack_118 = *(undefined4 *)(param_1 + 0x1a);
                    uStack_114 = *(undefined4 *)((longlong)param_1 + 0xd4);
                    uStack_110 = *(undefined4 *)(param_1 + 0x1b);
                    uStack_10c = *(undefined4 *)((longlong)param_1 + 0xdc);
                    uStack_108 = param_1[0x1c];
                    FUN_18536b170(*(longlong *)(param_2 + 0x48),&uStack_128,_DAT_188944068);
                    if (*(longlong *)(param_2 + 0x58) != 0) {
                      FUN_185733520(*(longlong *)(param_2 + 0x58),param_1[0x1d],_DAT_18891d7d8);
                      return param_1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  puVar7 = (undefined8 *)(*pcVar2)();
  return puVar7;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * Torappu_Battle_Context_TakeSnapshot_0x6010095(undefined8 *param_1,longlong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined8 uStack_10;
  
  if (DAT_188c905af == '\0') {
    FUN_18048bf00(&DAT_18891f990);
    FUN_18048bf00(&DAT_18891da18);
    FUN_18048bf00(&DAT_18891e558);
    FUN_18048bf00(&DAT_18891f090);
    FUN_18048bf00(&DAT_1889216d0);
    FUN_18048bf00(&DAT_188920290);
    FUN_18048bf00(&DAT_188921010);
    FUN_18048bf00(&DAT_188920950);
    DAT_188c905af = '\x01';
  }
  FUN_180501c30(param_1,0,0xf0);
  if (*(longlong *)(param_2 + 0x10) != 0) {
    uVar2 = FUN_185733610(*(longlong *)(param_2 + 0x10),_DAT_18891e558);
    *param_1 = uVar2;
    func_0x00018048b9e0(param_1,uVar2);
    if (*(longlong *)(param_2 + 0x18) != 0) {
      uVar2 = FUN_185733610(*(longlong *)(param_2 + 0x18),_DAT_18891e558);
      param_1[1] = uVar2;
      func_0x00018048b9e0(param_1 + 1,uVar2);
      if (*(longlong *)(param_2 + 0x20) != 0) {
        uVar2 = FUN_185733610(*(longlong *)(param_2 + 0x20),_DAT_18891da18);
        param_1[2] = uVar2;
        func_0x00018048b9e0(param_1 + 2,uVar2);
        if (*(longlong *)(param_2 + 0x28) != 0) {
          uVar2 = FUN_185733df0(*(longlong *)(param_2 + 0x28),_DAT_188920290);
          param_1[3] = uVar2;
          func_0x00018048b9e0(param_1 + 3,uVar2);
          if (*(longlong *)(param_2 + 0x30) != 0) {
            FUN_185733ed0(&uStack_90,*(longlong *)(param_2 + 0x30),_DAT_188921010);
            param_1[4] = uStack_90;
            param_1[5] = uStack_88;
            param_1[6] = uStack_80;
            param_1[7] = uStack_78;
            param_1[8] = uStack_70;
            param_1[9] = uStack_68;
            param_1[10] = uStack_60;
            param_1[0xb] = uStack_58;
            param_1[0xc] = uStack_50;
            param_1[0xd] = uStack_48;
            param_1[0xe] = uStack_40;
            param_1[0xf] = uStack_38;
            param_1[0x10] = uStack_30;
            param_1[0x11] = uStack_28;
            *(undefined4 *)(param_1 + 0x12) = uStack_20;
            *(undefined4 *)((longlong)param_1 + 0x94) = uStack_1c;
            *(undefined4 *)(param_1 + 0x13) = uStack_18;
            *(undefined4 *)((longlong)param_1 + 0x9c) = uStack_14;
            param_1[0x14] = uStack_10;
            func_0x00018048b9e0(param_1 + 4,0);
            if (*(longlong *)(param_2 + 0x38) != 0) {
              uVar2 = FUN_185733610(*(longlong *)(param_2 + 0x38),_DAT_18891f090);
              param_1[0x15] = uVar2;
              func_0x00018048b9e0(param_1 + 0x15,uVar2);
              if (*(longlong *)(param_2 + 0x40) != 0) {
                uVar2 = FUN_185733610(*(longlong *)(param_2 + 0x40),_DAT_18891f990);
                param_1[0x16] = uVar2;
                func_0x00018048b9e0(param_1 + 0x16,uVar2);
                if (*(longlong *)(param_2 + 0x48) != 0) {
                  FUN_185733ce0(&uStack_b8,*(longlong *)(param_2 + 0x48),_DAT_1889216d0);
                  param_1[0x18] = uStack_b8;
                  param_1[0x19] = uStack_b0;
                  *(undefined4 *)(param_1 + 0x1a) = uStack_a8;
                  *(undefined4 *)((longlong)param_1 + 0xd4) = uStack_a4;
                  *(undefined4 *)(param_1 + 0x1b) = uStack_a0;
                  *(undefined4 *)((longlong)param_1 + 0xdc) = uStack_9c;
                  param_1[0x1c] = uStack_98;
                  if (*(longlong *)(param_2 + 0x50) != 0) {
                    uVar2 = FUN_185733df0(*(longlong *)(param_2 + 0x50),_DAT_188920950);
                    param_1[0x17] = uVar2;
                    func_0x00018048b9e0(param_1 + 0x17,uVar2);
                    if (*(longlong *)(param_2 + 0x58) != 0) {
                      uVar2 = FUN_185733610(*(longlong *)(param_2 + 0x58),_DAT_18891da18);
                      param_1[0x1d] = uVar2;
                      func_0x00018048b9e0(param_1 + 0x1d,uVar2);
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
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined8 *)(*pcVar1)();
  return puVar3;
}


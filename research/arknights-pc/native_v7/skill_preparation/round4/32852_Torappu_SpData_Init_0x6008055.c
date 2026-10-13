
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_SpData_Init_0x6008055(longlong param_1,longlong param_2)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  char cVar5;
  undefined8 uVar6;
  longlong lVar7;
  uint uVar8;
  undefined4 auStackX_20 [2];
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  if (DAT_188ca6952 == '\0') {
    FUN_18048bf00(&DAT_188937728);
    FUN_18048bf00(&DAT_188930998);
    FUN_18048bf00(&DAT_18881f8b8);
    FUN_18048bf00(&DAT_188820878);
    DAT_188ca6952 = '\x01';
  }
  auStackX_20[0] = 0;
  if (*(int *)(_DAT_18881f8b8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_18881f8b8 + 0xb8) + 0x28);
  if (lVar7 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar7,param_1,param_2,0);
    return;
  }
  if (DAT_188ca6950 == '\0') {
    FUN_18048bf00(&DAT_18881f8b8);
    DAT_188ca6950 = '\x01';
  }
  if (*(int *)(_DAT_18881f8b8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_18881f8b8 + 0xb8) + 0x18);
  if (lVar7 == 0) {
    cVar5 = *(longlong *)(param_1 + 0x78) != 0;
  }
  else {
    cVar5 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar7,param_1,0);
  }
  if (cVar5 == '\0') {
    uVar6 = func_0x00018048ba50(_DAT_188930998,4);
    *(undefined8 *)(param_1 + 0x78) = uVar6;
    func_0x00018048b9e0(param_1 + 0x78,uVar6);
    uVar8 = 0;
    lVar7 = 0x20;
    do {
      if (param_2 == 0) {
LAB_18252b49d:
        if ((int)(*(uint *)(param_1 + 0x10) & 1 << ((byte)uVar8 & 0x1f)) < 1) {
          auStackX_20[0] = 0x3f800000;
        }
        else {
          uVar3 = *(undefined8 *)(param_1 + 0x5c);
          uVar4 = *(undefined8 *)(param_1 + 100);
          uVar6 = *(undefined8 *)(param_1 + 0x6c);
          if (*(int *)(_DAT_188937728 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          uStack_58 = uVar3;
          uStack_50 = uVar4;
          uStack_48 = uVar6;
          auStackX_20[0] =
               CodeStage_AntiCheat_ObscuredTypes_ObscuredFloat_op_Implicit_0x6002e88(&uStack_58);
        }
      }
      else {
        uStack_58 = _DAT_188820878;
        uStack_50 = 0xffffffffffffffff;
        uStack_48 = CONCAT44(uStack_48._4_4_,uVar8);
        uVar6 = System_Enum_ToString_0x6000f6e(&uStack_58,0);
        cVar5 = Torappu_Blackboard_TryGetFloat_0x6007869(param_2,uVar6,auStackX_20,0);
        if (cVar5 == '\0') goto LAB_18252b49d;
        *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1 << (uVar8 & 0x1f);
      }
      lVar1 = *(longlong *)(param_1 + 0x78);
      if (lVar1 == 0) {
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      if (*(uint *)(lVar1 + 0x18) <= uVar8) {
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      *(undefined4 *)(lVar7 + lVar1) = auStackX_20[0];
      uVar8 = uVar8 + 1;
      lVar7 = lVar7 + 4;
    } while ((int)uVar8 < 4);
  }
  return;
}


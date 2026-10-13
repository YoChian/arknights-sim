
void Torappu_DoubleBufferedList_1_Add_call_target
               (longlong param_1,undefined4 *param_2,longlong param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  longlong lVar9;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  lVar9 = **(longlong **)(*(longlong *)(param_3 + 0x20) + 0xc0);
  if ((*(byte *)(lVar9 + 0x136) & 1) == 0) {
    lVar9 = FUN_1804463f0(lVar9);
  }
  lVar9 = *(longlong *)(*(longlong *)(lVar9 + 0xb8) + 0x28);
  if (lVar9 != 0) {
    XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar9,0);
    if (*(longlong *)(*(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 8) + 0x20)
        == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 8))();
    }
    FUN_1844c6730(lVar9,param_1,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 8));
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x50) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x50))();
    }
    uStack_18 = *param_2;
    uStack_14 = param_2[1];
    uStack_10 = param_2[2];
    uStack_c = param_2[3];
    FUN_1844c5100(lVar9,&uStack_18,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x50));
    XLua_DelegateBridge_Invoke_0x6003c9e(lVar9,0,0);
    XLua_DelegateBridge_InvokeSessionEnd_0x6003c9f(lVar9,0);
    return;
  }
  lVar9 = *(longlong *)(param_1 + 0x10);
  if (lVar9 != 0) {
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x58) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x58))();
    }
    lVar3 = *(longlong *)(lVar9 + 0x10);
    lVar4 = *(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x58);
    *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
    if (lVar3 != 0) {
      uVar2 = *(uint *)(lVar9 + 0x18);
      if (*(uint *)(lVar3 + 0x18) <= uVar2) {
        if (*(longlong *)
             (*(longlong *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x58) + 0x20) == 0)
        {
          (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x58))();
        }
        uStack_18 = *param_2;
        uStack_14 = param_2[1];
        uStack_10 = param_2[2];
        uStack_c = param_2[3];
        FUN_184ac7730(lVar9,&uStack_18,
                      *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x58));
        return;
      }
      *(uint *)(lVar9 + 0x18) = uVar2 + 1;
      if (uVar2 < *(uint *)(lVar3 + 0x18)) {
        uVar6 = param_2[1];
        uVar7 = param_2[2];
        uVar8 = param_2[3];
        puVar1 = (undefined4 *)(lVar3 + ((longlong)(int)uVar2 + 2) * 0x10);
        *puVar1 = *param_2;
        puVar1[1] = uVar6;
        puVar1[2] = uVar7;
        puVar1[3] = uVar8;
        func_0x00018048b9e0(((longlong)(int)uVar2 + 2) * 0x10 + lVar3,0);
        return;
      }
      FUN_18048c0a0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
  FUN_18048c0b0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}


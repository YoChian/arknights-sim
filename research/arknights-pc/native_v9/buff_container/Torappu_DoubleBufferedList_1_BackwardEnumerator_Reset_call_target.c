
void Torappu_DoubleBufferedList_1_BackwardEnumerator_Reset_call_target
               (longlong param_1,undefined8 param_2,longlong param_3)

{
  longlong lVar1;
  code *pcVar2;
  undefined4 uVar3;
  longlong lVar4;
  
  lVar1 = *(longlong *)(param_1 + 0x10);
  if (lVar1 != 0) {
    lVar4 = *(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x18);
    if ((*(byte *)(lVar4 + 0x136) & 1) == 0) {
      lVar4 = FUN_1804463f0(lVar4);
    }
    uVar3 = FUN_180005310(0,lVar4,lVar1);
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    *(undefined8 *)(param_1 + 0x10) = param_2;
    func_0x00018048b9e0(param_1 + 0x10,param_2);
    *(undefined1 *)(param_1 + 0x1c) = 0;
    return;
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


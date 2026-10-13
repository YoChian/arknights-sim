
void Torappu_DoubleBufferedList_1_ForwardEnumerator_Reset_call_target
               (longlong param_1,undefined8 param_2)

{
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(undefined8 *)(param_1 + 0x10) = param_2;
  func_0x00018048b9e0(param_1 + 0x10);
  *(undefined1 *)(param_1 + 0x1c) = 0;
  return;
}


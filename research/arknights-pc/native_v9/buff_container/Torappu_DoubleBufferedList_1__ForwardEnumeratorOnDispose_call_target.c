
void Torappu_DoubleBufferedList_1__ForwardEnumeratorOnDispose_call_target
               (longlong param_1,undefined8 param_2,longlong param_3)

{
  code *pcVar1;
  longlong lVar2;
  
  lVar2 = **(longlong **)(*(longlong *)(param_3 + 0x20) + 0xc0);
  if ((*(byte *)(lVar2 + 0x136) & 1) == 0) {
    lVar2 = FUN_1804463f0(lVar2);
  }
  lVar2 = *(longlong *)(*(longlong *)(lVar2 + 0xb8) + 0x60);
  if (lVar2 == 0) {
    *(short *)(param_1 + 0x20) = *(short *)(param_1 + 0x20) + -1;
    lVar2 = *(longlong *)(param_1 + 0x28);
    if (lVar2 == 0) {
      FUN_18048c0b0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x118) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x118))();
    }
    FUN_185367f40(lVar2,param_2,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x118));
  }
  else {
    XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar2,0);
    if (*(longlong *)(*(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 8) + 0x20)
        == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 8))();
    }
    FUN_1844c6730(lVar2,param_1,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 8));
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x110) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x110))();
    }
    FUN_1844c6730(lVar2,param_2,
                  *(undefined8 *)(*(longlong *)(*(longlong *)(param_3 + 0x20) + 0xc0) + 0x110));
    XLua_DelegateBridge_Invoke_0x6003c9e(lVar2,0,0);
    XLua_DelegateBridge_InvokeSessionEnd_0x6003c9f(lVar2,0);
  }
  return;
}


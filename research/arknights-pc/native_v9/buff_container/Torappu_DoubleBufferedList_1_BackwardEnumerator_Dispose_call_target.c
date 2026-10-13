
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_DoubleBufferedList_1_BackwardEnumerator_Dispose_call_target
               (longlong param_1,longlong param_2)

{
  longlong lVar1;
  code *pcVar2;
  
  if (DAT_188cbc9b1 == '\0') {
    FUN_18048bf00(&DAT_18892ea20);
    FUN_18048bf00(&DAT_188919880);
    DAT_188cbc9b1 = '\x01';
  }
  if (*(char *)(param_1 + 0x1c) != '\0') {
    if (*(int *)(_DAT_18892ea20 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    UnityEngine_DLog_LogError_0x6000031(_DAT_188919880,0);
  }
  if ((*(longlong *)(param_1 + 0x20) != 0) && (*(char *)(param_1 + 0x1c) == '\0')) {
    lVar1 = *(longlong *)(param_1 + 0x20);
    *(undefined1 *)(param_1 + 0x1c) = 1;
    if (lVar1 == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    if (*(longlong *)
         (*(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x30) + 0x20) == 0) {
      (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x30))();
    }
    (**(code **)(lVar1 + 0x18))(*(undefined8 *)(lVar1 + 0x40),param_1,*(undefined8 *)(lVar1 + 0x28))
    ;
  }
  return;
}


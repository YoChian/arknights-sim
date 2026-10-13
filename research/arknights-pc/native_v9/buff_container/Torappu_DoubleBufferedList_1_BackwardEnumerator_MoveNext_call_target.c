
uint Torappu_DoubleBufferedList_1_BackwardEnumerator_MoveNext_call_target(longlong param_1)

{
  uint uVar1;
  
  uVar1 = *(int *)(param_1 + 0x18) - 1;
  *(uint *)(param_1 + 0x18) = uVar1;
  return uVar1 >> 0x1f ^ 1;
}


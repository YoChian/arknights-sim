
bool Torappu_DoubleBufferedList_1_ForwardEnumerator_MoveNext_call_target
               (longlong param_1,longlong param_2)

{
  longlong lVar1;
  code *pcVar2;
  undefined1 uVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  
  lVar1 = *(longlong *)(param_1 + 0x10);
  iVar6 = *(int *)(param_1 + 0x18) + 1;
  *(int *)(param_1 + 0x18) = iVar6;
  if (lVar1 != 0) {
    lVar5 = *(longlong *)(*(longlong *)(*(longlong *)(param_2 + 0x20) + 0xc0) + 0x18);
    if ((*(byte *)(lVar5 + 0x136) & 1) == 0) {
      lVar5 = FUN_1804463f0(lVar5);
    }
    iVar4 = FUN_180005310(0,lVar5,lVar1);
    return iVar6 < iVar4;
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  uVar3 = (*pcVar2)();
  return (bool)uVar3;
}


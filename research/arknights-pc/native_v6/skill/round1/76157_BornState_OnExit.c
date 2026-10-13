
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BornState_OnExit_0x601297e(undefined8 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c92775 == '\0') {
    puStack_30 = (undefined1 *)0x180a66344;
    FUN_18048bf00(&DAT_1888771f8);
    puStack_30 = (undefined1 *)0x180a66350;
    FUN_18048bf00(&DAT_188956960);
    DAT_188c92775 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_1888771f8 + 0xb8) + 0x10);
  if (lVar6 == 0) {
    puStack_30 = (undefined1 *)0x180a6637d;
    lVar6 = FUN_18536e540(param_1,_DAT_188956960);
    if (lVar6 == 0) {
      puStack_30 = (undefined1 *)0x180a663b1;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    *(undefined1 *)(lVar6 + 0x88) = 1;
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        FUN_183f25080(uVar1,param_2,0);
        iVar5 = FUN_183f22380(uVar1,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001834c0f1e:
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001834c0f1e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


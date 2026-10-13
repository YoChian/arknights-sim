/* WARNING: Removing unreachable block (ram,0x0001833006f9) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnDisappearChanged_0x6010461(undefined8 param_1,undefined1 param_2)
{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined1 auStackX_20 [8];
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  if (DAT_188c908f0 == '\0') {
    puStack_30 = (undefined1 *)0x1806f87c5;
    FUN_18048bf00(&DAT_188949060);
    puStack_30 = (undefined1 *)0x1806f87d1;
    FUN_18048bf00(&DAT_188841368);
    puStack_30 = (undefined1 *)0x1806f87dd;
    FUN_18048bf00(&DAT_188819760);
    DAT_188c908f0 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (undefined1 *)0x1806f87fc;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x920);
  if (lVar5 == 0) {
    puStack_30 = (undefined1 *)0x1806f8824;
    Torappu_Battle_BObject_OnDisappearChanged_0x600fe14(param_1,param_2,0);
    puStack_30 = (undefined1 *)0x1806f882e;
    lVar5 = Torappu_Battle_Entity_get_eventPool_0x6010338(param_1,0);
    puStack_30 = (undefined1 *)0x1806f8846;
    auStackX_20[0] = param_2;
    uVar6 = func_0x00018048b9c0(_DAT_188949060,auStackX_20);
    if (lVar5 == 0) {
      puStack_30 = (undefined1 *)0x1806f888b;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    puStack_30 = (undefined1 *)0x1806f8862;
    FUN_1848dca60(lVar5,0x17,uVar6,_DAT_188819760);
    return;
  }
  if (*(longlong *)(lVar5 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar5 + 0x18) != 0) {
    uVar6 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0);
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar6,param_1,0);
        FUN_183f22430(uVar6,param_2,0);
        iVar4 = FUN_183f22380(uVar6,2,0,iVar3,0);
        if (iVar4 == 0) {
code_r0x0001833006e0:
          FUN_183f22fd0(uVar6,iVar3 + -1,0);
          return;
        }
        if (*(longlong *)(lVar5 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar3 + -1,0);
          goto code_r0x0001833006e0;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_set_hp_0x6010384(longlong *param_1,undefined8 param_2)
{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  if (DAT_188c9081b == '\0') {
    auStack_40[0] = 0x180709775;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c9081b = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    auStack_40[0] = 0x180709794;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x270);
  if (lVar1 == 0) {
    if (DAT_188ccc7f0 != '\0') {
      auStack_40[0] = 0x1807097be;
      func_0x000180446d00(*param_1);
    }
    auStack_40[0] = 0x1807097e8;
    (**(code **)(*param_1 + 0x830))(param_1,param_2,0,0);
    return;
  }
  if (cRam0000000188caf41c == '\0') {
    FUN_18048bf00(&DAT_18885a700,param_1,param_2,0);
    cRam0000000188caf41c = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar3,uVar2,param_1,0);
        auStack_40[0] = param_2;
        uVar7 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
        FUN_183cfbf40(lVar3,uVar2,uVar7,0);
        iVar6 = FUN_183f22380(uVar2,2,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833f996e:
          FUN_183f22fd0(uVar2,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833f996e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

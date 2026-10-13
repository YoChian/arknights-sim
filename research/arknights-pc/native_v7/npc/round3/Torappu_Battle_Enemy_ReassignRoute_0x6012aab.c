/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Enemy_ReassignRoute_0x6012aab
               (longlong param_1,undefined8 param_2,undefined4 param_3)
{
  longlong lVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  int iVar6;
  int iVar7;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  if (DAT_188c92893 == '\0') {
    uStack_40 = 0x180a738cd;
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c92893 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    uStack_40 = 0x180a738ec;
    func_0x00018048c140(_DAT_18881b6b0);
  }
  lVar2 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x5d8);
  if (lVar2 != 0) {
    uStack_40 = 0x180a73959;
    XLua_DelegateBridge___Gen_Delegate_Imp192_0x6000b20(lVar2,param_1,param_2,param_3);
    return;
  }
  if (*(longlong *)(param_1 + 0x368) != 0) {
    uStack_40 = 0x180a7391d;
    Torappu_Battle_BasicCursor_OnRouteChanged_0x6011210(*(longlong *)(param_1 + 0x368),param_2,0);
    lVar2 = *(longlong *)(param_1 + 0x368);
    if (lVar2 != 0) {
      if (cRam0000000188c914dc == '\0') {
        puStack_30 = &UNK_180894bd4;
        FUN_18048bf00(0x18896d0f8,param_3,0);
        cRam0000000188c914dc = '\x01';
      }
      lVar1 = *(longlong *)(*(longlong *)(lRam000000018896d0f8 + 0xb8) + 0x40);
      if (lVar1 == 0) {
        *(undefined4 *)(lVar2 + 0x18) = param_3;
        return;
      }
      if (*(longlong *)(lVar1 + 0x18) == 0) {
        FUN_18048c0b0();
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
      uStack_38 = 0;
      puStack_30 = &stack0x00000008;
      puStack_28 = &uStack_48;
      FUN_185ca7f50(uStack_48,&stack0x00000008,0);
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
        iVar6 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          lVar4 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
          if (lVar4 == 0) {
            FUN_18048c0b0();
          }
          else {
            FUN_183cf8c20(lVar4,uVar3,lVar2,0);
            FUN_183f25080(uVar3,param_3,0);
            iVar7 = FUN_183f22380(uVar3,2,0,iVar6,0);
            if (iVar7 == 0) {
code_r0x0001834c0f1e:
              FUN_183f22fd0(uVar3,iVar6 + -1,0);
              return;
            }
            if (*(longlong *)(lVar1 + 0x18) != 0) {
              FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
              goto code_r0x0001834c0f1e;
            }
          }
          FUN_18048c0b0();
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
      FUN_180472d50();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
  uStack_40 = 0x180a7396e;
  FUN_18048c0b0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

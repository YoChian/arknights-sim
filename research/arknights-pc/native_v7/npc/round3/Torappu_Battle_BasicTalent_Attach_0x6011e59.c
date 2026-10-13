/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_BasicTalent_Attach_0x6011e59(longlong *param_1,longlong param_2)
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
  if (DAT_188c91e22 == '\0') {
    puStack_30 = (undefined1 *)0x1809724f5;
    FUN_18048bf00(&DAT_188925de0);
    DAT_188c91e22 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0xf0);
  if (lVar6 == 0) {
    puStack_30 = (undefined1 *)0x180972520;
    lVar6 = FUN_186b59d80(param_1,0);
    if (lVar6 == 0) {
      puStack_30 = (undefined1 *)0x180972591;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    puStack_30 = (undefined1 *)0x180972532;
    FUN_186b5c530(lVar6,1,0);
    param_1[6] = param_2;
    puStack_30 = (undefined1 *)0x180972542;
    func_0x00018048b9e0(param_1 + 6,param_2);
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (undefined1 *)0x180972553;
      func_0x000180446d00(*param_1);
    }
                    /* WARNING: Could not recover jumptable at 0x000180972571. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x310))(param_1,*(undefined8 *)(*param_1 + 0x318));
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
        FUN_183cf8c20(lVar2,uVar1,param_2,0);
        iVar5 = FUN_183f22380(uVar1,2,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
          goto code_r0x0001832d231b;
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

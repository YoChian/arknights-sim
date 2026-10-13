
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_Character_get_initState_0x601287e(undefined8 param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  ulonglong uVar8;
  char acStackX_8 [24];
  uint uStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  char *pcStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c925b7 == '\0') {
    pcStack_30 = (char *)0x180a3acde;
    FUN_18048bf00(&DAT_18886c268);
    DAT_188c925b7 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    pcStack_30 = (char *)0x180a3acfd;
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x2a8);
  if (lVar1 == 0) {
    return 7;
  }
  uStackX_20 = 0;
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001834b22c4:
    FUN_18048c0b0();
code_r0x0001834b22ca:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    uStack_38 = 0;
    pcStack_30 = acStackX_8;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],acStackX_8,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001834b22d4;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x0001834b22c4;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      iVar6 = FUN_183f22380(uVar2,1,1,iVar5,0);
      if (iVar6 == 0) {
code_r0x0001834b2247:
        uVar7 = FUN_183f25660(uVar2,iVar5 + 1,0);
        FUN_183f22fd0(uVar2,iVar5 + -1,0);
        if (acStackX_8[0] != '\0') {
          uStackX_20 = uVar7;
          func_0x000185ca7ff0(auStack_48[0],0);
        }
        return (ulonglong)uVar7;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
        goto code_r0x0001834b2247;
      }
      goto code_r0x0001834b22ca;
    }
  }
  FUN_18048c0b0();
code_r0x0001834b22d4:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  uVar8 = (*pcVar4)();
  return uVar8;
}


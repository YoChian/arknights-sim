
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte Torappu_Battle_Buff_get_isFinishedOrDisabled_0x600fe50(undefined8 param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  char acStackX_8 [24];
  byte bStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  char *pcStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c902d5 == '\0') {
    pcStack_30 = (char *)0x18068edce;
    FUN_18048bf00(&DAT_18895c250);
    DAT_188c902d5 = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    pcStack_30 = (char *)0x18068eded;
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x1b8);
  if (lVar1 == 0) {
    pcStack_30 = (char *)0x18068ee11;
    cVar5 = Torappu_Battle_Buff_get_isFinished_0x600fe4d(param_1,0);
    if (cVar5 != '\0') {
      return 1;
    }
    pcStack_30 = (char *)0x18068ee27;
    bVar6 = Torappu_Battle_Buff_get_isEnabled_0x600fe4b(param_1,0);
    return bVar6 ^ 1;
  }
  bStackX_20 = 0;
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    uStack_38 = 0;
    pcStack_30 = acStackX_8;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],acStackX_8,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar3,uVar2,param_1,0);
      iVar8 = FUN_183f22380(uVar2,1,1,iVar7,0);
      if (iVar8 == 0) {
code_r0x0001832b39f4:
        bVar6 = FUN_183f23100(uVar2,iVar7 + 1,0);
        FUN_183f22fd0(uVar2,iVar7 + -1,0);
        if (acStackX_8[0] != '\0') {
          bStackX_20 = bVar6;
          func_0x000185ca7ff0(auStack_48[0],0);
        }
        return bVar6;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  bVar6 = (*pcVar4)();
  return bVar6;
}


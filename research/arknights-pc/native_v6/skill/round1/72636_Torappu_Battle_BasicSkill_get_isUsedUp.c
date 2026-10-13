
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_Battle_BasicSkill_get_isUsedUp_0x6011bbd(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  char acStackX_8 [24];
  undefined1 uStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  char *pcStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c91c31 == '\0') {
    pcStack_30 = (char *)0x1809600fe;
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c31 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x1e8);
  if (lVar7 == 0) {
    if (*(int *)(param_1 + 0xcc) < 0) {
      return false;
    }
    if (*(char *)(param_1 + 0x1d) == '\0') {
      return *(int *)(param_1 + 0xcc) <= *(int *)(param_1 + 0x90);
    }
    pcStack_30 = (char *)0x18096014b;
    lVar7 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
    if (lVar7 != 0) {
      pcStack_30 = (char *)0x18096015a;
      lVar7 = Torappu_Battle_Character_get_sharedData_0x6012885(lVar7,0);
      if (lVar7 != 0) {
        return *(int *)(param_1 + 0xcc) <= *(int *)(lVar7 + 0x10);
      }
    }
    pcStack_30 = (char *)0x18096018e;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    uVar4 = (*pcVar3)();
    return (bool)uVar4;
  }
  uStackX_20 = 0;
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
    acStackX_8[0] = '\0';
    uStack_38 = 0;
    pcStack_30 = acStackX_8;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],acStackX_8,0);
    if (*(longlong *)(lVar7 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar2 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar2,uVar1,param_1,0);
      iVar6 = FUN_183f22380(uVar1,1,1,iVar5,0);
      if (iVar6 == 0) {
code_r0x0001832b39f4:
        uVar4 = FUN_183f23100(uVar1,iVar5 + 1,0);
        FUN_183f22fd0(uVar1,iVar5 + -1,0);
        if (acStackX_8[0] != '\0') {
          uStackX_20 = uVar4;
          func_0x000185ca7ff0(auStack_48[0],0);
        }
        return (bool)uVar4;
      }
      if (*(longlong *)(lVar7 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  uVar4 = (*pcVar3)();
  return (bool)uVar4;
}


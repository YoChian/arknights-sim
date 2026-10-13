
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_BasicSkill_get_ownerSkillActivatable_0x6011b93(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  ulonglong uVar8;
  char acStackX_8 [24];
  byte bStackX_20;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  char *pcStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c91c07 == '\0') {
    pcStack_30 = (char *)0x1809607be;
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c07 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x98);
  if (lVar7 == 0) {
    if (DAT_188c91c3d == '\0') {
      pcStack_30 = (char *)0x1809607f3;
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar7 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar7 == 0) {
      param_1 = *(longlong *)(param_1 + 0xa8);
    }
    else {
      pcStack_30 = (char *)0x180960828;
      param_1 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar7,param_1,0);
    }
    if (param_1 == 0) {
      pcStack_30 = (char *)0x180960851;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      uVar8 = (*pcVar3)();
      return uVar8;
    }
    if (cRam0000000188c90872 == '\0') {
      pcStack_30 = &UNK_18070686e;
      FUN_18048bf00(0x188841368);
      cRam0000000188c90872 = '\x01';
    }
    if (*(int *)(lRam0000000188841368 + 0xe0) == 0) {
      pcStack_30 = &UNK_18070688d;
      func_0x00018048c140(lRam0000000188841368);
    }
    lVar7 = *(longlong *)(*(longlong *)(lRam0000000188841368 + 0xb8) + 0x528);
    if (lVar7 == 0) {
      pcStack_30 = &UNK_1807068b1;
      lVar7 = FUN_180701e20(param_1,0);
      if (lVar7 == 0) {
        pcStack_30 = &UNK_1807068e3;
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        uVar8 = (*pcVar3)();
        return uVar8;
      }
      pcStack_30 = &UNK_1807068c6;
      uVar8 = FUN_180649280(lVar7,0x18,0);
      return uVar8 ^ 1;
    }
  }
  bStackX_20 = 0;
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
        bVar4 = FUN_183f23100(uVar1,iVar5 + 1,0);
        FUN_183f22fd0(uVar1,iVar5 + -1,0);
        if (acStackX_8[0] != '\0') {
          bStackX_20 = bVar4;
          func_0x000185ca7ff0(auStack_48[0],0);
        }
        return (ulonglong)bVar4;
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
  uVar8 = (*pcVar3)();
  return uVar8;
}


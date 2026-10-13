/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
ulonglong Torappu_Battle_Entity__VerifyAbilityDamageMiss_0x6010495
                    (undefined8 param_1,undefined8 param_2,char param_3)
{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  if (DAT_188c90924 == '\0') {
    uStack_40 = 0x180700d3e;
    FUN_18048bf00(&DAT_18891f090);
    uStack_40 = 0x180700d4a;
    FUN_18048bf00(&DAT_188920290);
    uStack_40 = 0x180700d56;
    FUN_18048bf00(&DAT_188841368);
    uStack_40 = 0x180700d62;
    FUN_18048bf00(&DAT_1888ed178);
    uStack_40 = 0x180700d6e;
    FUN_18048bf00(&DAT_188932ce8);
    uStack_40 = 0x180700d7a;
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c90924 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    uStack_40 = 0x180700d99;
    func_0x00018048c140(_DAT_188841368);
  }
  uVar7 = *(ulonglong *)(_DAT_188841368 + 0xb8);
  if (*(longlong *)(uVar7 + 0xac0) != 0) {
    uStack_40 = 0x180700f72;
    uVar7 = XLua_DelegateBridge___Gen_Delegate_Imp3066_0x600165a
                      (*(longlong *)(uVar7 + 0xac0),param_1,param_2,param_3);
    return uVar7;
  }
  if (param_3 != '\0') {
LAB_180700f48:
    return uVar7 & 0xffffffffffffff00;
  }
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    uStack_40 = 0x180700dd5;
    func_0x00018048c140();
  }
  uStack_40 = 0x180700ddf;
  uVar7 = Torappu_Battle_Modifier_get_attackType_0x601153c(param_2,0);
  if ((int)uVar7 == 4) goto LAB_180700f48;
  if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
    uStack_40 = 0x180700dfd;
    func_0x00018048c140();
  }
  uStack_40 = 0x180700e07;
  uVar8 = Torappu_Battle_Modifier_get_source_0x6011534(param_2,0);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    uStack_40 = 0x180700e1f;
    func_0x00018048c140();
  }
  uStack_40 = 0x180700e2c;
  uVar7 = FUN_186b638d0(uVar8,0,0);
  if ((char)uVar7 != '\0') goto LAB_180700f48;
  uStack_40 = 0x180700e40;
  lVar9 = FUN_185337c50(_DAT_1888d3908);
  if (lVar9 == 0) {
LAB_180700f82:
    uStack_40 = 0x180700f87;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    uVar7 = (*pcVar2)();
    return uVar7;
  }
  uStack_40 = 0x180700e53;
  lVar9 = Torappu_Battle_BattleController_get_context_0x600fbfa(lVar9,0);
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x38) == 0)) goto LAB_180700f82;
  uStack_40 = 0x180700e75;
  lVar9 = FUN_185733610(*(longlong *)(lVar9 + 0x38),_DAT_18891f090);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    uStack_40 = 0x180700e8d;
    func_0x00018048c140();
  }
  uStack_40 = 0x180700e9a;
  cVar3 = FUN_186b63a70(lVar9,0,0);
  if (cVar3 == '\0') {
    uStack_40 = 0x180700eae;
    lVar9 = FUN_185337c50(_DAT_1888d3908);
    if (lVar9 == 0) goto LAB_180700f82;
    uStack_40 = 0x180700ec1;
    lVar9 = Torappu_Battle_BattleController_get_context_0x600fbfa(lVar9,0);
    if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x28) == 0)) goto LAB_180700f82;
    uStack_40 = 0x180700ee3;
    lVar9 = FUN_185733df0(*(longlong *)(lVar9 + 0x28),_DAT_188920290);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      uStack_40 = 0x180700efb;
      func_0x00018048c140();
    }
    uStack_40 = 0x180700f08;
    uVar7 = FUN_186b63a70(lVar9,0,0);
    if ((char)uVar7 == '\0') goto LAB_180700f48;
    if (lVar9 == 0) goto LAB_180700f82;
    if (cRam0000000188c8fcde == '\0') {
      puStack_30 = &UNK_1805d7a0e;
      FUN_18048bf00(&DAT_1889733f0,0);
      cRam0000000188c8fcde = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x118);
    if (lVar10 == 0) {
      return (ulonglong)*(byte *)(lVar9 + 0xb8);
    }
  }
  else {
    if (lVar9 == 0) goto LAB_180700f82;
    if (cRam0000000188c917f2 == '\0') {
      puStack_30 = &UNK_1808dcf9e;
      FUN_18048bf00(&DAT_1888233f8,0);
      cRam0000000188c917f2 = '\x01';
    }
    lVar10 = *(longlong *)(*(longlong *)(_DAT_1888233f8 + 0xb8) + 0x120);
    if (lVar10 == 0) {
      return (ulonglong)*(byte *)(lVar9 + 0x188);
    }
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar10 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar8 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar1 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar1,uVar8,lVar9,0);
      iVar6 = FUN_183f22380(uVar8,1,1,iVar5,0);
      if (iVar6 == 0) {
code_r0x0001832b39f4:
        bVar4 = FUN_183f23100(uVar8,iVar5 + 1,0);
        FUN_183f22fd0(uVar8,iVar5 + -1,0);
        return (ulonglong)bVar4;
      }
      if (*(longlong *)(lVar10 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar5 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  uVar7 = (*pcVar2)();
  return uVar7;
}

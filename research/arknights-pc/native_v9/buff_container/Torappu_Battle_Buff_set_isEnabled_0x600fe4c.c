
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Buff_set_isEnabled_0x600fe4c
               (longlong param_1,byte param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  char cVar7;
  undefined8 uVar8;
  undefined7 uVar9;
  bool bVar10;
  undefined8 uStackX_20;
  undefined1 auStack_f8 [136];
  undefined *puStack_70;
  undefined8 uStack_48;
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c902d1 == '\0') {
    uStack_30 = 0x180690385;
    FUN_18048bf00(&DAT_18895c250);
    DAT_188c902d1 = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    uStack_30 = 0x1806903a4;
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x198);
  if (lVar6 != 0) {
    uStack_30 = 0x1806903f1;
    XLua_DelegateBridge___Gen_Delegate_Imp26_0x6000a7a(lVar6,param_1,param_2,0);
    return;
  }
  if ((*(byte *)(param_1 + 0x1fa) & param_2) != 0) {
    return;
  }
  *(byte *)(param_1 + 0x1ff) = param_2;
  if (cRam0000000188c90379 == '\0') {
    FUN_18048bf00(&DAT_18895c250);
    FUN_18048bf00(0x188932ce8);
    cRam0000000188c90379 = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x6d8);
  if (lVar6 != 0) {
    if (*(longlong *)(lVar6 + 0x18) == 0) {
      puStack_70 = &UNK_18331015e;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = &uStackX_20;
    puStack_70 = &UNK_183310067;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      uVar8 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
      puStack_70 = &UNK_18331008a;
      iVar4 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
      if (*(longlong *)(lVar6 + 0x18) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
        if (lVar1 == 0) {
          puStack_70 = &UNK_183310142;
          FUN_18048c0b0();
        }
        else {
          puStack_70 = &UNK_1833100b4;
          FUN_183cf8c20(lVar1,uVar8,param_1,0);
          uStack_48 = 0;
          puStack_70 = &UNK_1833100d0;
          iVar5 = FUN_183f22380(uVar8,1,0,iVar4);
          if (iVar5 == 0) {
code_r0x0001833100e8:
            puStack_70 = &UNK_1833100f6;
            FUN_183f22fd0(uVar8,iVar4 + -1,0);
            return;
          }
          if (*(longlong *)(lVar6 + 0x18) != 0) {
            puStack_70 = &UNK_1833100e8;
            FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        puStack_70 = &UNK_183310148;
        FUN_18048c0b0();
      }
      puStack_70 = &UNK_18331014d;
      FUN_18048c0b0();
    }
    puStack_70 = &UNK_183310152;
    FUN_18048c0b0();
    puStack_70 = &UNK_183310158;
    FUN_180472d50();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  cVar7 = *(char *)(param_1 + 0x1ff);
  lVar6 = FUN_18068f400(param_1,0);
  if (*(char *)(param_1 + 0x1f2) == '\0') {
code_r0x00018068dd28:
    if (*(char *)(param_1 + 499) != '\0') {
      if (*(int *)(lRam0000000188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(lVar6,0,0);
      if (cVar3 != '\0') {
        if (lVar6 == 0) goto DAT_18068e055;
        cVar3 = FUN_180706a00(lVar6,0);
        if (cVar3 != '\0') goto code_r0x00018068de48;
      }
    }
    if (*(char *)(param_1 + 500) != '\0') {
      if (*(int *)(lRam0000000188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(lVar6,0,0);
      if (cVar3 != '\0') {
        if (lVar6 == 0) goto DAT_18068e055;
        cVar3 = FUN_180705b50(lVar6,0);
        if (cVar3 != '\0') goto code_r0x00018068de48;
      }
    }
    if (*(char *)(param_1 + 0x1f7) != '\0') {
      if (*(int *)(lRam0000000188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(lVar6,0,0);
      if (cVar3 != '\0') {
        if (lVar6 == 0) goto DAT_18068e055;
        cVar3 = FUN_180705320(lVar6,0);
        if (cVar3 != '\0') goto code_r0x00018068de48;
      }
    }
    if (*(char *)(param_1 + 0x1f8) != '\0') {
      if (*(int *)(lRam0000000188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(lVar6,0,0);
      if (cVar3 != '\0') {
        if (lVar6 == 0) goto DAT_18068e055;
        cVar3 = FUN_180705270(lVar6,0);
        if (cVar3 != '\0') goto code_r0x00018068de48;
      }
    }
  }
  else {
    if (*(int *)(lRam0000000188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b63a70(lVar6,0,0);
    if (cVar3 == '\0') goto code_r0x00018068dd28;
    if (lVar6 == 0) goto DAT_18068e055;
    cVar3 = FUN_180706710(lVar6,0);
    if (cVar3 == '\0') goto code_r0x00018068dd28;
code_r0x00018068de48:
    cVar7 = '\0';
  }
  if (*(char *)(param_1 + 0x1fd) == cVar7) {
    return;
  }
  if (cVar7 == '\0') {
    bVar10 = cRam0000000188c902fc == '\0';
    *(undefined1 *)(param_1 + 0x1fd) = 0;
    if (bVar10) {
      FUN_18048bf00(&DAT_18895c250);
      cRam0000000188c902fc = '\x01';
    }
    if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18895c250);
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x2f0);
    if (lVar6 != 0) {
code_r0x00018068e032:
      FUN_183310010(lVar6,param_1,0);
      return;
    }
    lVar6 = FUN_18068f400(param_1,0);
    if ((lVar6 == 0) || (lVar6 = FUN_180701e20(lVar6,0), lVar6 == 0)) {
DAT_18068e055:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_18064a270(lVar6,param_1,0);
    if (*(longlong *)(param_1 + 0x70) != 0) {
      lVar6 = FUN_18068f400(param_1,0);
      if ((lVar6 == 0) || (lVar6 = FUN_180701e20(lVar6,0), lVar6 == 0)) goto DAT_18068e055;
      FUN_18064a1d0(lVar6,param_1,0);
    }
    uVar9 = (undefined7)((ulonglong)param_4 >> 8);
    uVar8 = 0x19;
  }
  else {
    bVar10 = cRam0000000188c902fb == '\0';
    *(undefined2 *)(param_1 + 0x1fd) = 0x101;
    if (bVar10) {
      FUN_18048bf00(&DAT_18895c250);
      cRam0000000188c902fb = '\x01';
    }
    if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
      func_0x00018048c140(_DAT_18895c250);
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x2e8);
    if (lVar6 != 0) goto code_r0x00018068e032;
    lVar6 = FUN_18068f400(param_1,0);
    if ((lVar6 == 0) || (lVar6 = FUN_180701e20(lVar6,0), lVar6 == 0)) goto DAT_18068e055;
    FUN_180648650(lVar6,param_1,0);
    if (*(longlong *)(param_1 + 0x70) != 0) {
      lVar6 = FUN_18068f400(param_1,0);
      if ((lVar6 == 0) || (lVar6 = FUN_180701e20(lVar6,0), lVar6 == 0)) goto DAT_18068e055;
      FUN_1806484d0(lVar6,param_1,0);
    }
    uVar9 = (undefined7)((ulonglong)param_4 >> 8);
    uVar8 = 0x18;
  }
  FUN_18068d4b0(auStack_f8,param_1,uVar8,CONCAT71(uVar9,1),0);
  return;
}


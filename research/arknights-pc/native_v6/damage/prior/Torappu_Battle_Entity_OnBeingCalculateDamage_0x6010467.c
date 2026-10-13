/* WARNING: Removing unreachable block (ram,0x000183326946) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnBeingCalculateDamage_0x6010467(undefined8 param_1,undefined8 *param_2)
{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  longlong *plVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  ushort uVar12;
  longlong *plStackX_20;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  longlong **pplStack_a8;
  undefined *puStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined1 *puStack_50;
  undefined8 *puStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  if (DAT_188c908f6 == '\0') {
    uStack_30 = 0x1806f7cb5;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c908f6 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    uStack_30 = 0x1806f7cd4;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x950);
  if (lVar10 == 0) {
    uStack_30 = 0x1806f7cf8;
    lVar10 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    if (lVar10 == 0) {
      uStack_30 = 0x1806f7d32;
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    if (cRam0000000188c903fc == '\0') {
      FUN_18048bf00(0x1888d5250);
      FUN_18048bf00(0x18882b720);
      FUN_18048bf00(&DAT_188954c98);
      FUN_18048bf00(0x1888cfcb0);
      FUN_18048bf00(0x188959b58);
      FUN_18048bf00(0x1889316a8);
      cRam0000000188c903fc = '\x01';
    }
    plStackX_20 = (longlong *)0x0;
    uStack_90 = 0;
    uStack_88 = 0;
    lVar8 = *(longlong *)(*(longlong *)(lRam00000001888d5250 + 0xb8) + 0x318);
    if (lVar8 == 0) {
      cVar5 = FUN_18067e3a0(lVar10,0x49,0);
      if (cVar5 != '\0') {
        lVar8 = FUN_18067ffe0(lVar10,0);
        if (lVar8 != 0) {
          uStack_b8 = FUN_1806c5c20(lVar8,0);
          puStack_a0 = (undefined *)0x0;
          puStack_98 = &uStack_b8;
          if (*(longlong *)(lVar10 + 0x18) != 0) {
            plStackX_20 = (longlong *)
                          FUN_185a17960(*(longlong *)(lVar10 + 0x18),uRam000000018882b720);
            uStack_b0 = 0;
            pplStack_a8 = &plStackX_20;
            while (plStackX_20 != (longlong *)0x0) {
              cVar5 = FUN_180005310(0,uRam0000000188959b58);
              plVar4 = plStackX_20;
              lVar8 = lRam00000001888cfcb0;
              if (cVar5 == '\0') {
                if (plStackX_20 != (longlong *)0x0) {
                  FUN_180005310(0,_DAT_188954c98,plStackX_20);
                }
                FUN_1806c2ce0(&uStack_b8,0);
                FUN_18067e5b0(lVar10,0);
                return;
              }
              if (plStackX_20 == (longlong *)0x0) {
                FUN_18048c0b0();
                break;
              }
              lVar1 = *plStackX_20;
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(lVar1);
              }
              uVar12 = 0;
              if (*(ushort *)(lVar1 + 0x12e) != 0) {
                do {
                  if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar12 * 0x10) == lVar8
                     ) {
                    puVar9 = (undefined8 *)
                             (((longlong)
                               *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10)
                              + 0x14) * 0x10 + lVar1);
                    goto code_r0x00018066f0e9;
                  }
                  uVar12 = uVar12 + 1;
                } while (uVar12 < *(ushort *)(lVar1 + 0x12e));
              }
              puVar9 = (undefined8 *)FUN_180445cc0(plVar4,lVar8,0);
code_r0x00018066f0e9:
              puVar9 = (undefined8 *)(*(code *)*puVar9)(&uStack_38,plVar4,puVar9[1]);
              uStack_90 = *puVar9;
              uStack_88 = puVar9[1];
              lVar8 = FUN_185159d80(&uStack_90,uRam00000001889316a8);
              if ((lVar8 != 0) && (cVar5 = FUN_18068edb0(lVar8,0), cVar5 == '\0')) {
                uStack_68 = *param_2;
                uStack_60 = param_2[1];
                uStack_58 = param_2[2];
                puStack_50 = (undefined1 *)param_2[3];
                puStack_48 = (undefined8 *)param_2[4];
                FUN_1806c3320(&uStack_b8,&uStack_68,0);
                FUN_180683a50(lVar8,param_2,0);
              }
            }
            FUN_18048c0b0();
            FUN_180472d50();
            FUN_180472d50();
          }
          FUN_18048c0b0();
        }
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp2938_0x60015da(lVar8,lVar10,param_2,0);
    }
    return;
  }
  if (cRam0000000188cafcb5 == '\0') {
    puStack_a0 = &UNK_1833267da;
    FUN_18048bf00(0x1888c1e70,param_1,param_2,0);
    puStack_a0 = &UNK_1833267e6;
    FUN_18048bf00(0x18888e150);
    cRam0000000188cafcb5 = '\x01';
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    puStack_a0 = &UNK_1833269b3;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStack_68 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30);
  uStack_58 = 0;
  puStack_50 = &stack0x00000008;
  puStack_48 = &uStack_68;
  puStack_a0 = &UNK_183326840;
  FUN_185ca7f50(uStack_68,&stack0x00000008,0);
  if (*(longlong *)(lVar10 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    puStack_a0 = &UNK_183326863;
    iVar6 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar8 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar8 == 0) {
        puStack_a0 = &UNK_183326997;
        FUN_18048c0b0();
      }
      else {
        puStack_a0 = &UNK_183326891;
        FUN_183cf8c20(lVar8,uVar2,param_1,0);
        uStack_40 = *param_2;
        uStack_38 = param_2[1];
        uStack_30 = param_2[2];
        puStack_a0 = &UNK_1833268c1;
        uVar11 = func_0x00018048b9c0(uRam00000001888c1e70,&uStack_40);
        puStack_a0 = &UNK_1833268d2;
        FUN_183cfbf40(lVar8,uVar2,uVar11,0);
        uStack_78 = 0;
        puStack_a0 = &UNK_1833268f1;
        iVar7 = FUN_183f22380(uVar2,2,1,iVar6);
        if (iVar7 == 0) {
code_r0x00018332690e:
          uStack_78 = uRam000000018888e150;
          puStack_a0 = &UNK_18332692c;
          FUN_184566b70(lVar8,uVar2,iVar6 + 1,param_2);
          puStack_a0 = &UNK_18332693b;
          FUN_183f22fd0(uVar2,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar10 + 0x18) != 0) {
          puStack_a0 = &UNK_18332690e;
          FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar6 + -1,0);
          goto code_r0x00018332690e;
        }
      }
      puStack_a0 = &UNK_18332699d;
      FUN_18048c0b0();
    }
    puStack_a0 = &UNK_1833269a2;
    FUN_18048c0b0();
  }
  puStack_a0 = &UNK_1833269a7;
  FUN_18048c0b0();
  puStack_a0 = &UNK_1833269ad;
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
undefined1 Torappu_Battle_Entity_CheckCanSwitchToDisappearState_0x601045f(longlong param_1)
{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined8 *puVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  ulonglong unaff_RBX;
  ulonglong uStackX_8;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  ulonglong *puStack_30;
  ulonglong *puStack_28;
  undefined8 *puStack_20;
  if (DAT_188c908ee == '\0') {
    puStack_30 = (ulonglong *)0x1806f0aee;
    FUN_18048bf00(&DAT_188841368);
    puStack_30 = (ulonglong *)0x1806f0afa;
    FUN_18048bf00(&DAT_188872340);
    DAT_188c908ee = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    puStack_30 = (ulonglong *)0x1806f0b19;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar11 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x910);
  if (lVar11 != 0) {
code_r0x0001832b3910:
    if (*(longlong *)(lVar11 + 0x18) == 0) {
      FUN_18048c0b0();
code_r0x0001832b3a74:
      FUN_18048c0b0();
code_r0x0001832b3a7a:
      FUN_18048c0b0();
    }
    else {
      uStack_48 = *(ulonglong *)(*(longlong *)(lVar11 + 0x18) + 0x30);
      uStackX_8 = uStackX_8 & 0xffffffffffffff00;
      uStack_38 = 0;
      puStack_30 = &uStackX_8;
      puStack_28 = &uStack_48;
      FUN_185ca7f50(uStack_48,&uStackX_8,0);
      if (*(longlong *)(lVar11 + 0x18) == 0) goto code_r0x0001832b3a84;
      uVar12 = *(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x10);
      iVar8 = FUN_183f23b70(uVar12,*(undefined4 *)(lVar11 + 0x38),*(undefined4 *)(lVar11 + 0x14),0);
      if (*(longlong *)(lVar11 + 0x18) != 0) {
        lVar13 = *(longlong *)(*(longlong *)(lVar11 + 0x18) + 0x20);
        if (lVar13 == 0) goto code_r0x0001832b3a74;
        FUN_183cf8c20(lVar13,uVar12,param_1,0);
        iVar9 = FUN_183f22380(uVar12,1,1,iVar8,0);
        if (iVar9 == 0) {
code_r0x0001832b39f4:
          uVar5 = FUN_183f23100(uVar12,iVar8 + 1,0);
          FUN_183f22fd0(uVar12,iVar8 + -1,0);
          if ((char)uStackX_8 != '\0') {
            func_0x000185ca7ff0(uStack_48,0);
          }
          return uVar5;
        }
        if (*(longlong *)(lVar11 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar11 + 0x18),iVar8 + -1,0);
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
    uVar5 = (*pcVar2)();
    return uVar5;
  }
  if (*(longlong *)(param_1 + 0x38) == 0) {
LAB_1806f0b78:
    puStack_30 = (ulonglong *)0x1806f0b7d;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    uVar5 = (*pcVar2)();
    return uVar5;
  }
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x38) + 0x50);
  puStack_30 = (ulonglong *)0x1806f0b51;
  uVar7 = func_0x0001844dc660(0xb,_DAT_188872340);
  lVar11 = lRam0000000188904178;
  if (plVar1 == (longlong *)0x0) goto LAB_1806f0b78;
  iVar8 = *(int *)(*plVar1 + 0x11c);
  uStackX_8 = unaff_RBX;
  if (iVar8 < 0x948) {
    if (iVar8 == 0x947) {
FUN_181297950:
      if (cRam0000000188c9821b == '\0') {
        puStack_30 = (ulonglong *)&UNK_181297974;
        FUN_18048bf00(0x1889654a0,uVar7,0);
        cRam0000000188c9821b = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001889654a0 + 0xb8) + 0x60);
      if (lVar11 == 0) {
        return true;
      }
    }
    else if (iVar8 < 0x8c8) {
      if (iVar8 != 0x8c7) {
        if (iVar8 == 0x692) {
          if (DAT_188ccc7f0 != '\0') {
            puStack_30 = (ulonglong *)&UNK_185c320f1;
            func_0x000180446d00(*plVar1);
          }
          lVar11 = *(longlong *)(*plVar1 + 0x268);
          goto FUN_1855c9270;
        }
        goto FUN_180004e80;
      }
      if (cRam0000000188c927af == '\0') {
        puStack_30 = (ulonglong *)&UNK_180a68ec4;
        FUN_18048bf00(0x188877d28,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_180a68ed0;
        FUN_18048bf00(0x188956960);
        cRam0000000188c927af = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188877d28 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        puStack_30 = (ulonglong *)&UNK_180a68efd;
        lVar11 = FUN_18536e540(plVar1,uRam0000000188956960);
        if (lVar11 == 0) {
          puStack_30 = (ulonglong *)&UNK_180a68f55;
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          uVar5 = (*pcVar2)();
          return uVar5;
        }
        puStack_30 = (ulonglong *)&UNK_180a68f0c;
        cVar3 = FUN_180705950(lVar11,0);
        if ((cVar3 != '\0') && ((uVar7 - 6 & 0xfffffffb) != 0)) {
          return uVar7 == 0xb;
        }
        return true;
      }
    }
    else {
      switch(iVar8) {
      case 0x8c8:
        if (cRam0000000188c927bb == '\0') {
          puStack_30 = (ulonglong *)&UNK_180a81704;
          FUN_18048bf00(0x1888781a0,uVar7,0);
          puStack_30 = (ulonglong *)&UNK_180a81710;
          FUN_18048bf00(0x188956960);
          cRam0000000188c927bb = '\x01';
        }
        lVar11 = *(longlong *)(*(longlong *)(lRam00000001888781a0 + 0xb8) + 0x48);
        if (lVar11 == 0) {
          puStack_30 = (ulonglong *)&UNK_180a8173d;
          lVar11 = FUN_18536e540(plVar1,uRam0000000188956960);
          if (lVar11 == 0) {
            puStack_30 = (ulonglong *)&UNK_180a8179a;
            FUN_18048c0b0();
            pcVar2 = (code *)swi(3);
            uVar5 = (*pcVar2)();
            return uVar5;
          }
          puStack_30 = (ulonglong *)&UNK_180a8174c;
          cVar3 = FUN_180705b50(lVar11,0);
          if ((cVar3 != '\0') && ((0xd < uVar7 || ((0x2460U >> (uVar7 & 0x1f) & 1) == 0)))) {
            return uVar7 == 0xb;
          }
          return true;
        }
        break;
      case 0x8c9:
        if (cRam0000000188c927c8 == '\0') {
          puStack_30 = (ulonglong *)&UNK_180a82384;
          FUN_18048bf00(&DAT_1888a8898,uVar7,0);
          puStack_30 = (ulonglong *)&UNK_180a82390;
          FUN_18048bf00(0x188878618);
          puStack_30 = (ulonglong *)&UNK_180a8239c;
          FUN_18048bf00(&DAT_1888d3908);
          cRam0000000188c927c8 = '\x01';
        }
        lVar11 = *(longlong *)(*(longlong *)(lRam0000000188878618 + 0xb8) + 0x50);
        if (lVar11 == 0) {
          puStack_30 = (ulonglong *)&UNK_180a823c6;
          lVar11 = FUN_185337c50(_DAT_1888d3908);
          if (lVar11 != 0) {
            puStack_30 = (ulonglong *)&UNK_180a823d5;
            cVar3 = FUN_180641f50(lVar11,0);
            if ((cVar3 != '\0') && (uVar7 == 6)) {
              puStack_30 = (ulonglong *)&UNK_180a823ea;
              lVar11 = FUN_185337c50(_DAT_1888d3908);
              if (lVar11 == 0) goto code_r0x000180a82441;
              puStack_30 = (ulonglong *)&UNK_180a823f9;
              uVar12 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar11,0);
              puStack_30 = (ulonglong *)&UNK_180a82408;
              lVar11 = FUN_1800057a0(uVar12,_DAT_1888a8898);
              if (lVar11 != 0) {
                return *(undefined1 *)(lVar11 + 0x28);
              }
            }
            return false;
          }
code_r0x000180a82441:
          puStack_30 = (ulonglong *)&UNK_180a82446;
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          uVar5 = (*pcVar2)();
          return uVar5;
        }
        break;
      case 0x8ca:
        if (DAT_188ccc7f0 == '\0') {
          return true;
        }
        puStack_30 = (ulonglong *)&UNK_185c32188;
        func_0x000180446d00(*plVar1);
        return true;
      case 0x8cb:
        if (cRam0000000188c92944 == '\0') {
          puStack_30 = (ulonglong *)&UNK_180a94dc4;
          FUN_18048bf00(0x1888855e0,uVar7,0);
          puStack_30 = (ulonglong *)&UNK_180a94dd0;
          FUN_18048bf00(0x188957b60);
          cRam0000000188c92944 = '\x01';
        }
        lVar11 = *(longlong *)(*(longlong *)(lRam00000001888855e0 + 0xb8) + 0x50);
        if (lVar11 == 0) {
          puStack_30 = (ulonglong *)&UNK_180a94dfd;
          lVar11 = FUN_18536e540(plVar1,uRam0000000188957b60);
          if (lVar11 == 0) {
            puStack_30 = (ulonglong *)&UNK_180a94e5a;
            FUN_18048c0b0();
            pcVar2 = (code *)swi(3);
            uVar5 = (*pcVar2)();
            return uVar5;
          }
          puStack_30 = (ulonglong *)&UNK_180a94e0c;
          cVar3 = FUN_180705b50(lVar11,0);
          if ((cVar3 != '\0') && ((0xe < uVar7 || ((0x4330U >> (uVar7 & 0x1f) & 1) == 0)))) {
            return uVar7 == 10;
          }
          return true;
        }
        break;
      case 0x8cc:
        if (cRam0000000188c92950 == '\0') {
          puStack_30 = (ulonglong *)&UNK_180a96774;
          FUN_18048bf00(0x188885820,uVar7,0);
          puStack_30 = (ulonglong *)&UNK_180a96780;
          FUN_18048bf00(0x188957b60);
          cRam0000000188c92950 = '\x01';
        }
        if (*(int *)(lRam0000000188885820 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_180a9679f;
          func_0x00018048c140(lRam0000000188885820);
        }
        lVar11 = *(longlong *)(*(longlong *)(lRam0000000188885820 + 0xb8) + 0x68);
        if (lVar11 == 0) {
          puStack_30 = (ulonglong *)&UNK_180a967c5;
          lVar11 = FUN_18536e540(plVar1,uRam0000000188957b60);
          if (lVar11 == 0) {
            puStack_30 = (ulonglong *)&UNK_180a96818;
            FUN_18048c0b0();
            pcVar2 = (code *)swi(3);
            uVar5 = (*pcVar2)();
            return uVar5;
          }
          puStack_30 = (ulonglong *)&UNK_180a967d4;
          cVar3 = FUN_180705320(lVar11,0);
          if ((cVar3 != '\0') && (uVar7 != 5)) {
            return uVar7 == 8;
          }
          return true;
        }
        break;
      case 0x8cd:
      case 0x8ce:
        if (DAT_188ccc7f0 == '\0') {
          return true;
        }
        puStack_30 = (ulonglong *)&UNK_185c321e5;
        func_0x000180446d00(*plVar1);
        return true;
      case 0x8cf:
        if (cRam0000000188c9298b == '\0') {
          puStack_30 = (ulonglong *)&UNK_180a87c74;
          FUN_18048bf00(0x188884400,uVar7,0);
          cRam0000000188c9298b = '\x01';
        }
        lVar11 = *(longlong *)(*(longlong *)(lRam0000000188884400 + 0xb8) + 0x48);
        if (lVar11 == 0) {
          if (uVar7 - 3 < 2) {
            return false;
          }
          return uVar7 != 2;
        }
        break;
      case 0x8d0:
        if (cRam0000000188c92999 == '\0') {
          puStack_30 = (ulonglong *)&UNK_180a99894;
          FUN_18048bf00(&DAT_1888a8898,uVar7,0);
          puStack_30 = (ulonglong *)&UNK_180a998a0;
          FUN_18048bf00(0x188886110);
          puStack_30 = (ulonglong *)&UNK_180a998ac;
          FUN_18048bf00(&DAT_1888d3908);
          cRam0000000188c92999 = '\x01';
        }
        lVar11 = *(longlong *)(*(longlong *)(lRam0000000188886110 + 0xb8) + 0x50);
        if (lVar11 == 0) {
          puStack_30 = (ulonglong *)&UNK_180a998d6;
          lVar11 = FUN_185337c50(_DAT_1888d3908);
          if (lVar11 != 0) {
            puStack_30 = (ulonglong *)&UNK_180a998e5;
            cVar3 = FUN_180641f50(lVar11,0);
            if ((cVar3 != '\0') && (uVar7 == 5)) {
              puStack_30 = (ulonglong *)&UNK_180a998fa;
              lVar11 = FUN_185337c50(_DAT_1888d3908);
              if (lVar11 == 0) goto code_r0x000180a99951;
              puStack_30 = (ulonglong *)&UNK_180a99909;
              uVar12 = Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar11,0);
              puStack_30 = (ulonglong *)&UNK_180a99918;
              lVar11 = FUN_1800057a0(uVar12,_DAT_1888a8898);
              if (lVar11 != 0) {
                return *(undefined1 *)(lVar11 + 0x28);
              }
            }
            return false;
          }
code_r0x000180a99951:
          puStack_30 = (ulonglong *)&UNK_180a99956;
          FUN_18048c0b0();
          pcVar2 = (code *)swi(3);
          uVar5 = (*pcVar2)();
          return uVar5;
        }
        break;
      case 0x8d1:
        if (DAT_188ccc7f0 == '\0') {
          return true;
        }
        puStack_30 = (ulonglong *)&UNK_185c32242;
        func_0x000180446d00(*plVar1);
        return true;
      default:
FUN_180004e80:
        lVar13 = *plVar1;
        if (DAT_188ccc7f0 != '\0') {
          puStack_30 = (ulonglong *)&UNK_180004eba;
          func_0x000180446d00(lVar13);
        }
        uVar6 = 0;
        if (*(ushort *)(lVar13 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar13 + 0xb0) + (ulonglong)uVar6 * 0x10) == lVar11) {
              puVar10 = (undefined8 *)
                        (((longlong)
                          (*(int *)(*(longlong *)(lVar13 + 0xb0) + 8 + (ulonglong)uVar6 * 0x10) + 4)
                         + 0x14) * 0x10 + lVar13);
              goto code_r0x000180004ef3;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < *(ushort *)(lVar13 + 0x12e));
        }
        puStack_30 = (ulonglong *)&UNK_180004ef3;
        puVar10 = (undefined8 *)FUN_180445cc0(plVar1,lVar11,4);
code_r0x000180004ef3:
                    /* WARNING: Could not recover jumptable at 0x000180004f1a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar5 = (*(code *)*puVar10)(plVar1,uVar7,puVar10[1],(code *)*puVar10);
        return uVar5;
      }
    }
    goto FUN_183250150;
  }
  if (iVar8 < 0x1a38) {
    if (iVar8 == 0x1a37) {
code_r0x000185c32679:
      if (DAT_188ccc7f0 != '\0') {
        puStack_30 = (ulonglong *)&UNK_185c3268a;
        func_0x000180446d00(*plVar1);
      }
      lVar11 = *(longlong *)(*plVar1 + 0x208);
      goto FUN_185444db0;
    }
    switch(iVar8) {
    case 0x948:
    case 0x94a:
    case 0x94b:
    case 0x94c:
    case 0x955:
    case 0x956:
    case 0x957:
    case 0x958:
    case 0x959:
    case 0x95a:
    case 0x960:
    case 0x961:
    case 0x962:
    case 0x964:
    case 0x965:
    case 0x966:
    case 0x969:
    case 0x96a:
    case 0x96b:
    case 0x96c:
    case 0x96d:
    case 0x96e:
    case 0x96f:
    case 0x970:
    case 0x976:
    case 0x97c:
    case 0x980:
    case 0x983:
    case 0x986:
    case 0x988:
    case 0x98c:
    case 0x98d:
    case 0x98e:
      goto FUN_181297950;
    case 0x949:
      if (cRam0000000188c92e73 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180af6f94;
        FUN_18048bf00(0x1888984b8,uVar7,0);
        cRam0000000188c92e73 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888984b8 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x94d:
      if (cRam0000000188c943ca == '\0') {
        puStack_30 = (ulonglong *)&UNK_180d1e554;
        FUN_18048bf00(0x188923cf0,uVar7,0);
        cRam0000000188c943ca = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188923cf0 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x94e:
      if (cRam0000000188c943d4 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180d1a194;
        FUN_18048bf00(0x18891de80,uVar7,0);
        cRam0000000188c943d4 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018891de80 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x94f:
      if (cRam0000000188c94fc8 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e499f4;
        FUN_18048bf00(0x188885808,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_180e49a00;
        FUN_18048bf00(0x188886c20);
        cRam0000000188c94fc8 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188885808 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          if (*(int *)(lRam0000000188886c20 + 0xe0) == 0) {
            puStack_30 = (ulonglong *)&UNK_180e49a3f;
            func_0x00018048c140(lRam0000000188886c20);
          }
          return uVar7 == *(uint *)(*(longlong *)(lRam0000000188886c20 + 0xb8) + 4);
        }
        return true;
      }
      break;
    case 0x950:
      if (cRam0000000188c94fd7 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e4a194;
        FUN_18048bf00(0x188885c80,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_180e4a1a0;
        FUN_18048bf00(0x188886c20);
        cRam0000000188c94fd7 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188885c80 + 0xb8) + 0x68);
      if (lVar11 == 0) {
        if (((uVar7 - 2 & 0xfffffffa) == 0) && (uVar7 != 3)) {
          return true;
        }
        if (*(int *)(lRam0000000188886c20 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_180e4a1f2;
          func_0x00018048c140(lRam0000000188886c20);
        }
        return uVar7 == *(uint *)(*(longlong *)(lRam0000000188886c20 + 0xb8) + 0xc);
      }
      break;
    case 0x951:
      if (cRam0000000188c94fe3 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e4b234;
        FUN_18048bf00(0x188885eb8,uVar7,0);
        cRam0000000188c94fe3 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188885eb8 + 0xb8) + 0x50);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          return uVar7 == 8;
        }
        return true;
      }
      break;
    case 0x952:
      if (cRam0000000188c94ff0 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e4c064;
        FUN_18048bf00(0x1888860f8,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_180e4c070;
        FUN_18048bf00(0x188886c20);
        cRam0000000188c94ff0 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888860f8 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (1 < uVar7 - 7)) {
          if (*(int *)(lRam0000000188886c20 + 0xe0) == 0) {
            puStack_30 = (ulonglong *)&UNK_180e4c0b2;
            func_0x00018048c140(lRam0000000188886c20);
          }
          return uVar7 == *(uint *)(*(longlong *)(lRam0000000188886c20 + 0xb8) + 4);
        }
        return true;
      }
      break;
    case 0x953:
      if (cRam0000000188c950e1 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e64684;
        FUN_18048bf00(0x188973ab8,uVar7,0);
        cRam0000000188c950e1 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188973ab8 + 0xb8) + 0x50);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x954:
      if (cRam0000000188c950ee == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e66974;
        FUN_18048bf00(0x188973f38,uVar7,0);
        cRam0000000188c950ee = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188973f38 + 0xb8) + 0x58);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x95b:
      if (cRam0000000188c97f8c == '\0') {
        puStack_30 = (ulonglong *)&UNK_18125c894;
        FUN_18048bf00(0x188915490,uVar7,0);
        cRam0000000188c97f8c = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188915490 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x95c:
      if (cRam0000000188c97f99 == '\0') {
        puStack_30 = (ulonglong *)&UNK_18125d664;
        FUN_18048bf00(0x188915908,uVar7,0);
        cRam0000000188c97f99 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188915908 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return false;
      }
      break;
    case 0x95d:
      if (cRam0000000188c97fa6 == '\0') {
        puStack_30 = (ulonglong *)&UNK_18125e524;
        FUN_18048bf00(0x188916688,uVar7,0);
        cRam0000000188c97fa6 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188916688 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x95e:
      if (cRam0000000188c97fb2 == '\0') {
        puStack_30 = (ulonglong *)&UNK_18125ee94;
        FUN_18048bf00(0x1889168c8,uVar7,0);
        cRam0000000188c97fb2 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001889168c8 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 9;
      }
      break;
    case 0x95f:
      if (cRam0000000188c97fc7 == '\0') {
        puStack_30 = (ulonglong *)&UNK_181260614;
        FUN_18048bf00(0x18891d948,uVar7,0);
        cRam0000000188c97fc7 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018891d948 + 0xb8) + 0x30);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          return uVar7 == 0x13;
        }
        return true;
      }
      break;
    case 0x963:
      if (cRam0000000188c9802a == '\0') {
        puStack_30 = (ulonglong *)&UNK_181266fd4;
        FUN_18048bf00(0x18895fce0,uVar7,0);
        cRam0000000188c9802a = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018895fce0 + 0xb8) + 0x30);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          return uVar7 == 0x13;
        }
        return true;
      }
      break;
    case 0x967:
      if (cRam0000000188c9822b == '\0') {
        puStack_30 = (ulonglong *)&UNK_1812995d4;
        FUN_18048bf00(0x188822200,uVar7,0);
        cRam0000000188c9822b = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188822200 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x968:
      if (cRam0000000188c9846c == '\0') {
        puStack_30 = (ulonglong *)&UNK_1812c0354;
        FUN_18048bf00(0x18893d5b0,uVar7,0);
        cRam0000000188c9846c = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018893d5b0 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        if (uVar7 == 2) {
          return true;
        }
        return uVar7 == 7;
      }
      break;
    case 0x971:
      if (cRam0000000188c986bf == '\0') {
        puStack_30 = (ulonglong *)&UNK_1812f4e14;
        FUN_18048bf00(0x18893fbf0,uVar7,0);
        cRam0000000188c986bf = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018893fbf0 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x972:
      if (cRam0000000188c986cb == '\0') {
        puStack_30 = (ulonglong *)&UNK_1812f7824;
        FUN_18048bf00(0x188889eb8,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_1812f7830;
        FUN_18048bf00(0x1889404f0);
        cRam0000000188c986cb = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001889404f0 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        if ((uVar7 < 0xb) && ((0x504U >> (uVar7 & 0x1f) & 1) != 0)) {
          return true;
        }
        if (*(int *)(lRam0000000188889eb8 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_1812f7882;
          func_0x00018048c140(lRam0000000188889eb8);
        }
        return uVar7 == *(uint *)(*(longlong *)(lRam0000000188889eb8 + 0xb8) + 8);
      }
      break;
    case 0x973:
      if (cRam0000000188c986d7 == '\0') {
        puStack_30 = (ulonglong *)&UNK_1812f8cf4;
        FUN_18048bf00(0x188889eb8,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_1812f8d00;
        FUN_18048bf00(0x188940970);
        cRam0000000188c986d7 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188940970 + 0xb8) + 0x50);
      if (lVar11 == 0) {
        if ((uVar7 - 2 & 0xfffffff7) == 0) {
          return true;
        }
        if (*(int *)(lRam0000000188889eb8 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_1812f8d4d;
          func_0x00018048c140(lRam0000000188889eb8);
        }
        return uVar7 == *(uint *)(*(longlong *)(lRam0000000188889eb8 + 0xb8) + 8);
      }
      break;
    case 0x974:
      if (cRam0000000188c98899 == '\0') {
        puStack_30 = (ulonglong *)&UNK_181337094;
        FUN_18048bf00(0x188933170,uVar7,0);
        cRam0000000188c98899 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188933170 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x975:
      if (cRam0000000188c988a6 == '\0') {
        puStack_30 = (ulonglong *)&UNK_181339c54;
        FUN_18048bf00(0x1888e4fb8,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_181339c60;
        FUN_18048bf00(0x188933cb0);
        cRam0000000188c988a6 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188933cb0 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          if (*(int *)(lRam00000001888e4fb8 + 0xe0) == 0) {
            puStack_30 = (ulonglong *)&UNK_181339c9d;
            func_0x00018048c140();
          }
          if (uVar7 != *(uint *)(*(longlong *)(lRam00000001888e4fb8 + 0xb8) + 0x18)) {
            if (*(int *)(lRam00000001888e4fb8 + 0xe0) == 0) {
              puStack_30 = (ulonglong *)&UNK_181339cbe;
              func_0x00018048c140();
            }
            return uVar7 == *(uint *)(*(longlong *)(lRam00000001888e4fb8 + 0xb8) + 0x1c);
          }
        }
        return true;
      }
      break;
    case 0x977:
      if (cRam0000000188c988cc == '\0') {
        puStack_30 = (ulonglong *)&UNK_181346394;
        FUN_18048bf00(0x1889360b0,uVar7,0);
        cRam0000000188c988cc = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001889360b0 + 0xb8) + 0x50);
      if (lVar11 == 0) {
        if ((uVar7 - 2 & 0xfffffff7) == 0) {
          return true;
        }
        return uVar7 == 8;
      }
      break;
    case 0x978:
      if (cRam0000000188c988d8 == '\0') {
        puStack_30 = (ulonglong *)&UNK_181346d04;
        FUN_18048bf00(0x1888e4fb8,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_181346d10;
        FUN_18048bf00(0x188936770);
        cRam0000000188c988d8 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188936770 + 0xb8) + 0x50);
      if (lVar11 == 0) {
        if ((uVar7 - 2 & 0xfffffff7) == 0) {
          return true;
        }
        if (*(int *)(lRam00000001888e4fb8 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_181346d5d;
          func_0x00018048c140(lRam00000001888e4fb8);
        }
        return uVar7 == *(uint *)(*(longlong *)(lRam00000001888e4fb8 + 0xb8) + 0x18);
      }
      break;
    case 0x979:
      if (cRam0000000188c988e8 == '\0') {
        puStack_30 = (ulonglong *)&UNK_181348314;
        FUN_18048bf00(0x1889369b0,uVar7,0);
        cRam0000000188c988e8 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001889369b0 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        if (uVar7 == 2) {
          return true;
        }
        return uVar7 == 10;
      }
      break;
    case 0x97a:
      if (cRam0000000188c989f7 == '\0') {
        puStack_30 = (ulonglong *)&UNK_18135bac4;
        FUN_18048bf00(0x1888ad308,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_18135bad0;
        FUN_18048bf00(0x1888aeb98);
        cRam0000000188c989f7 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888ad308 + 0xb8) + 0x20);
      if (lVar11 == 0) {
        if (uVar7 == 10) {
          return true;
        }
        if (*(int *)(lRam00000001888aeb98 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_18135bb18;
          func_0x00018048c140(lRam00000001888aeb98);
        }
        return uVar7 == *(uint *)(*(longlong *)(lRam00000001888aeb98 + 0xb8) + 8);
      }
      break;
    case 0x97b:
      if (cRam0000000188c989ff == '\0') {
        puStack_30 = (ulonglong *)&UNK_18135c304;
        FUN_18048bf00(0x1888ae4e8,uVar7,0);
        cRam0000000188c989ff = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888ae4e8 + 0xb8) + 0x30);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x97d:
      if (cRam0000000188c98a3b == '\0') {
        puStack_30 = (ulonglong *)&UNK_1813489e4;
        FUN_18048bf00(0x1888d5d78,uVar7,0);
        cRam0000000188c98a3b = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888d5d78 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          return uVar7 == 0x13;
        }
        return true;
      }
      break;
    case 0x97e:
      if (cRam0000000188caa68e == '\0') {
        puStack_30 = (ulonglong *)&UNK_182a29e54;
        FUN_18048bf00(0x188913510,uVar7,0);
        cRam0000000188caa68e = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188913510 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        if ((uVar7 != 2) && (uVar7 != 7)) {
          return uVar7 == 10;
        }
        return true;
      }
      break;
    case 0x97f:
      if (cRam0000000188cad8f7 == '\0') {
        puStack_30 = (ulonglong *)&UNK_182e3e574;
        FUN_18048bf00(0x18894d618,uVar7,0);
        puStack_30 = (ulonglong *)&UNK_182e3e580;
        FUN_18048bf00(0x18894da98);
        cRam0000000188cad8f7 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018894d618 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        if (*(int *)(lRam000000018894da98 + 0xe0) == 0) {
          puStack_30 = (ulonglong *)&UNK_182e3e5b5;
          func_0x00018048c140(lRam000000018894da98);
        }
        return uVar7 == *(uint *)(*(longlong *)(lRam000000018894da98 + 0xb8) + 0x10);
      }
      break;
    case 0x981:
      if (cRam0000000188cad910 == '\0') {
        puStack_30 = (ulonglong *)&UNK_182e40a24;
        FUN_18048bf00(0x188955f58,uVar7,0);
        cRam0000000188cad910 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188955f58 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x982:
      if (cRam0000000188cada8a == '\0') {
        puStack_30 = (ulonglong *)&UNK_182e538c4;
        FUN_18048bf00(0x1888aadb8,uVar7,0);
        cRam0000000188cada8a = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888aadb8 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x984:
      if (cRam0000000188cadaa5 == '\0') {
        puStack_30 = (ulonglong *)&UNK_182e579e4;
        FUN_18048bf00(0x1888abb28,uVar7,0);
        cRam0000000188cadaa5 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888abb28 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x985:
      if (cRam0000000188cae090 == '\0') {
        puStack_30 = (ulonglong *)&UNK_182ec5cb4;
        FUN_18048bf00(0x1888db0b8,uVar7,0);
        cRam0000000188cae090 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888db0b8 + 0xb8) + 0x40);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x987:
      if (cRam0000000188cae0a8 == '\0') {
        puStack_30 = (ulonglong *)&UNK_182eca374;
        FUN_18048bf00(0x1888dcdf8,uVar7,0);
        cRam0000000188cae0a8 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888dcdf8 + 0xb8) + 0x48);
      if (lVar11 == 0) {
        return uVar7 == 2;
      }
      break;
    case 0x989:
      if (cRam0000000188cb2461 == '\0') {
        puStack_30 = (ulonglong *)&UNK_1837c54d4;
        FUN_18048bf00(0x188856b78,uVar7,0);
        cRam0000000188cb2461 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam0000000188856b78 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x98a:
      if (cRam0000000188cb2483 == '\0') {
        puStack_30 = (ulonglong *)&UNK_1837c7b04;
        FUN_18048bf00(0x18887f720,uVar7,0);
        cRam0000000188cb2483 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018887f720 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    case 0x98b:
      if (cRam0000000188cb248c == '\0') {
        puStack_30 = (ulonglong *)&UNK_1837c7f44;
        FUN_18048bf00(0x18887f960,uVar7,0);
        cRam0000000188cb248c = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam000000018887f960 + 0xb8) + 0x38);
      if (lVar11 == 0) {
        return uVar7 == 10;
      }
      break;
    default:
      goto FUN_180004e80;
    case 0xa1c:
    case 0xa1d:
    case 0xa1e:
    case 0xa1f:
    case 0xa20:
      if (cRam0000000188c94ea5 == '\0') {
        puStack_30 = (ulonglong *)&UNK_180e37eb4;
        FUN_18048bf00(0x1888e91c0,uVar7,0);
        cRam0000000188c94ea5 = '\x01';
      }
      lVar11 = *(longlong *)(*(longlong *)(lRam00000001888e91c0 + 0xb8) + 0x28);
      if (lVar11 == 0) {
        return true;
      }
    }
    goto FUN_183250150;
  }
  if (0x4f26 < iVar8) goto FUN_180004e80;
  if (iVar8 == 0x4f26) {
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32abb;
      func_0x000180446d00(*plVar1);
    }
    lVar11 = *(longlong *)(*plVar1 + 0x268);
FUN_1855c9270:
    if (cRam0000000188cbca9b == '\0') {
      puStack_30 = (ulonglong *)&UNK_1855c92a1;
      FUN_18048bf00(0x1888b9ea0);
      puStack_30 = (ulonglong *)&UNK_1855c92ad;
      FUN_18048bf00(0x18892adb8);
      cRam0000000188cbca9b = '\x01';
    }
    lVar13 = **(longlong **)(*(longlong *)(lVar11 + 0x20) + 0xc0);
    if ((*(byte *)(lVar13 + 0x136) & 1) == 0) {
      puStack_30 = (ulonglong *)&UNK_1855c92d3;
      lVar13 = FUN_1804463f0(lVar13);
    }
    lVar13 = *(longlong *)(*(longlong *)(lVar13 + 0xb8) + 0x48);
    if (lVar13 == 0) {
      uVar5 = 1;
    }
    else {
      puStack_30 = (ulonglong *)&UNK_1855c92f1;
      XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar13,0);
      if (*(longlong *)
           (*(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x10) + 0x20) == 0) {
        puStack_30 = (ulonglong *)&UNK_1855c9318;
        (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x10))();
      }
      puStack_30 = (ulonglong *)&UNK_1855c9332;
      FUN_1844c6730(lVar13,plVar1,
                    *(undefined8 *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 0x10));
      puStack_30 = (ulonglong *)&UNK_1855c9343;
      FUN_1844c6210(lVar13,uVar7,uRam00000001888b9ea0);
      puStack_30 = (ulonglong *)&UNK_1855c9353;
      XLua_DelegateBridge_Invoke_0x6003c9e(lVar13,1,0);
      puStack_30 = (ulonglong *)&UNK_1855c9362;
      uVar5 = FUN_1844c7bb0(lVar13,uRam000000018892adb8);
    }
    return uVar5;
  }
  switch(iVar8) {
  case 0x1a38:
  case 0x1a39:
  case 0x1a3a:
  case 0x1a3b:
  case 0x1a3c:
    goto code_r0x000185c32679;
  case 0x1a3d:
  case 0x1a3e:
  case 0x1a3f:
  case 0x1a40:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c326b9;
      func_0x000180446d00(*plVar1);
    }
    lVar11 = *(longlong *)(*plVar1 + 0x208);
    goto FUN_185444db0;
  case 0x1a41:
  case 0x1a42:
  case 0x1a43:
  case 0x1a44:
  case 0x1a45:
  case 0x1a46:
  case 0x1a47:
  case 0x1a48:
  case 0x1a49:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c326e8;
      func_0x000180446d00(*plVar1);
    }
    lVar11 = *(longlong *)(*plVar1 + 0x208);
FUN_185444db0:
    if (cRam0000000188cbc551 == '\0') {
      puStack_30 = (ulonglong *)&UNK_185444de1;
      FUN_18048bf00(0x1888b9ea0);
      puStack_30 = (ulonglong *)&UNK_185444ded;
      FUN_18048bf00(0x18892adb8);
      cRam0000000188cbc551 = '\x01';
    }
    lVar13 = **(longlong **)(*(longlong *)(lVar11 + 0x20) + 0xc0);
    if ((*(byte *)(lVar13 + 0x136) & 1) == 0) {
      puStack_30 = (ulonglong *)&UNK_185444e13;
      lVar13 = FUN_1804463f0(lVar13);
    }
    lVar13 = *(longlong *)(*(longlong *)(lVar13 + 0xb8) + 0x58);
    if (lVar13 == 0) {
      uVar5 = 1;
    }
    else {
      puStack_30 = (ulonglong *)&UNK_185444e31;
      XLua_DelegateBridge_InvokeSessionStart_0x6003c9d(lVar13,0);
      if (*(longlong *)
           (*(longlong *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 8) + 0x20) == 0) {
        puStack_30 = (ulonglong *)&UNK_185444e58;
        (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 8))();
      }
      puStack_30 = (ulonglong *)&UNK_185444e72;
      FUN_1844c6730(lVar13,plVar1,
                    *(undefined8 *)(*(longlong *)(*(longlong *)(lVar11 + 0x20) + 0xc0) + 8));
      puStack_30 = (ulonglong *)&UNK_185444e83;
      FUN_1844c6210(lVar13,uVar7,uRam00000001888b9ea0);
      puStack_30 = (ulonglong *)&UNK_185444e93;
      XLua_DelegateBridge_Invoke_0x6003c9e(lVar13,1,0);
      puStack_30 = (ulonglong *)&UNK_185444ea2;
      uVar5 = FUN_1844c7bb0(lVar13,uRam000000018892adb8);
    }
    return uVar5;
  case 0x1a4a:
  case 0x1a4b:
  case 0x1a4c:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32717;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a4d:
    if (cRam0000000188cb57ca == '\0') {
      puStack_30 = (ulonglong *)&UNK_183d9bef4;
      FUN_18048bf00(0x18895aa98,uVar7,0);
      cRam0000000188cb57ca = '\x01';
    }
    if (((uVar7 - 7 & 0xfffffffc) == 0) && (uVar7 != 8)) {
      return true;
    }
    puStack_30 = (ulonglong *)&UNK_183d9bf26;
    lVar11 = FUN_18536e540(plVar1,uRam000000018895aa98);
    if (lVar11 != 0) {
      puStack_30 = (ulonglong *)&UNK_183d9bf35;
      bVar4 = FUN_183da9a00(lVar11,0);
      return bVar4 ^ 1;
    }
    puStack_30 = (ulonglong *)&UNK_183d9bf47;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    uVar5 = (*pcVar2)();
    return uVar5;
  case 0x1a4e:
    if (cRam0000000188cb57cd == '\0') {
      puStack_30 = (ulonglong *)&UNK_183d9c164;
      FUN_18048bf00(0x18895aa98,uVar7,0);
      cRam0000000188cb57cd = '\x01';
    }
    if (uVar7 - 8 < 3) {
      return true;
    }
    puStack_30 = (ulonglong *)&UNK_183d9c18f;
    lVar11 = FUN_18536e540(plVar1,uRam000000018895aa98);
    if (lVar11 != 0) {
      puStack_30 = (ulonglong *)&UNK_183d9c19e;
      bVar4 = FUN_183da9a00(lVar11,0);
      return bVar4 ^ 1;
    }
    puStack_30 = (ulonglong *)&UNK_183d9c1b0;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    uVar5 = (*pcVar2)();
    return uVar5;
  case 0x1a4f:
    if (cRam0000000188cb57d3 == '\0') {
      puStack_30 = (ulonglong *)&UNK_183d9ba54;
      FUN_18048bf00(0x18895aa98,uVar7,0);
      cRam0000000188cb57d3 = '\x01';
    }
    if (uVar7 - 7 < 2) {
      return true;
    }
    puStack_30 = (ulonglong *)&UNK_183d9ba7f;
    lVar11 = FUN_18536e540(plVar1,uRam000000018895aa98);
    if (lVar11 == 0) {
      puStack_30 = (ulonglong *)&UNK_183d9baf1;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar5 = (*pcVar2)();
      return uVar5;
    }
    if (cRam0000000188cb577f == '\0') {
      puStack_30 = (ulonglong *)&UNK_183d9ba9c;
      FUN_18048bf00(0x18881b840);
      cRam0000000188cb577f = '\x01';
    }
    lVar13 = *(longlong *)(*(longlong *)(lRam000000018881b840 + 0xb8) + 0x18);
    if (lVar13 == 0) {
      return *(char *)(lVar11 + 0xe8) == '\0';
    }
    puStack_30 = (ulonglong *)&UNK_183d9badc;
    cVar3 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar13,lVar11,0);
    return cVar3 == '\0';
  case 0x1a50:
  case 0x1a51:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c3278b;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a52:
  case 0x1a53:
  case 0x1a54:
  case 0x1a55:
  case 0x1a56:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c327ba;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a57:
    if (cRam0000000188cb57ff == '\0') {
      puStack_30 = (ulonglong *)&UNK_183da18f2;
      FUN_18048bf00(0x18895aa98,uVar7,0);
      cRam0000000188cb57ff = '\x01';
    }
    puStack_30 = (ulonglong *)&UNK_183da1908;
    lVar11 = FUN_18536e540(plVar1,uRam000000018895aa98);
    if (lVar11 == 0) {
code_r0x000183da19e0:
      puStack_30 = (ulonglong *)&UNK_183da19e5;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar5 = (*pcVar2)();
      return uVar5;
    }
    if (cRam0000000188cb5794 == '\0') {
      puStack_30 = (ulonglong *)&UNK_183da1929;
      FUN_18048bf00(0x18881b840);
      cRam0000000188cb5794 = '\x01';
    }
    lVar13 = *(longlong *)(*(longlong *)(lRam000000018881b840 + 0xb8) + 0xc0);
    if (lVar13 == 0) {
      cVar3 = *(char *)(lVar11 + 0xc4);
    }
    else {
      puStack_30 = (ulonglong *)&UNK_183da195e;
      cVar3 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar13,lVar11,0);
    }
    if (cVar3 == '\0') {
      return true;
    }
    puStack_30 = (ulonglong *)&UNK_183da197e;
    param_1 = FUN_18536e540(plVar1,uRam000000018895aa98);
    if (param_1 == 0) goto code_r0x000183da19e0;
    if (cRam0000000188cb577f == '\0') {
      puStack_30 = (ulonglong *)&UNK_183da199b;
      FUN_18048bf00(0x18881b840);
      cRam0000000188cb577f = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam000000018881b840 + 0xb8) + 0x18);
    if (lVar11 == 0) {
      return *(undefined1 *)(param_1 + 0xe8);
    }
    goto code_r0x0001832b3910;
  case 0x1a58:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32800;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a59:
  case 0x1a5a:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c3282f;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a5b:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c3285e;
      func_0x000180446d00(*plVar1);
    }
    lVar11 = *(longlong *)(*plVar1 + 0x268);
    goto FUN_1855c9270;
  case 0x1a5c:
  case 0x1a5d:
  case 0x1a5e:
  case 0x1a5f:
  case 0x1a60:
  case 0x1a61:
    break;
  case 0x1a62:
  case 0x1a63:
  case 0x1a64:
  case 0x1a65:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c328a4;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a66:
    if (cRam0000000188c92785 == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a67444;
      FUN_18048bf00(0x188877670,uVar7,0);
      cRam0000000188c92785 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188877670 + 0xb8) + 0x10);
    if (lVar11 == 0) {
      return false;
    }
    goto FUN_183250150;
  case 0x1a67:
    if (cRam0000000188c9278c == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a696d4;
      FUN_18048bf00(0x188877f60,uVar7,0);
      cRam0000000188c9278c = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188877f60 + 0xb8) + 8);
    if (lVar11 == 0) {
      return uVar7 == 6;
    }
    goto FUN_183250150;
  case 0x1a68:
  case 0x1a69:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32901;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a6a:
    if (cRam0000000188c927a2 == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a84ce4;
      FUN_18048bf00(0x188956960,uVar7,0);
      puStack_30 = (ulonglong *)&UNK_180a84cf0;
      FUN_18048bf00(0x188878cc8);
      cRam0000000188c927a2 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188878cc8 + 0xb8) + 0x18);
    if (lVar11 == 0) {
      puStack_30 = (ulonglong *)&UNK_180a84d1d;
      lVar11 = FUN_18536e540(plVar1,uRam0000000188956960);
      if (lVar11 == 0) {
        puStack_30 = (ulonglong *)&UNK_180a84d7a;
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar5 = (*pcVar2)();
        return uVar5;
      }
      puStack_30 = (ulonglong *)&UNK_180a84d2c;
      cVar3 = FUN_180706a00(lVar11,0);
      if ((cVar3 != '\0') && ((0xd < uVar7 || ((0x2840U >> (uVar7 & 0x1f) & 1) == 0)))) {
        return uVar7 == 10;
      }
      return true;
    }
    goto FUN_183250150;
  case 0x1a6b:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32947;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a6c:
  case 0x1a6d:
  case 0x1a6e:
  case 0x1a6f:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32976;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a70:
    if (cRam0000000188c9291b == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a8b344;
      FUN_18048bf00(0x188884ab8,uVar7,0);
      cRam0000000188c9291b = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188884ab8 + 0xb8) + 0x10);
    if (lVar11 == 0) {
      return false;
    }
    goto FUN_183250150;
  case 0x1a71:
    if (cRam0000000188c92923 == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a98a04;
      FUN_18048bf00(0x188885ed0,uVar7,0);
      cRam0000000188c92923 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188885ed0 + 0xb8) + 0x10);
    if (lVar11 == 0) {
      return false;
    }
    goto FUN_183250150;
  case 0x1a72:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c329d3;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a73:
    if (cRam0000000188c92931 == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a9c364;
      FUN_18048bf00(0x188957b60,uVar7,0);
      puStack_30 = (ulonglong *)&UNK_180a9c370;
      FUN_18048bf00(0x188886348);
      cRam0000000188c92931 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188886348 + 0xb8) + 0x10);
    if (lVar11 == 0) {
      puStack_30 = (ulonglong *)&UNK_180a9c39d;
      lVar11 = FUN_18536e540(plVar1,uRam0000000188957b60);
      if (lVar11 == 0) {
        puStack_30 = (ulonglong *)&UNK_180a9c3fa;
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar5 = (*pcVar2)();
        return uVar5;
      }
      puStack_30 = (ulonglong *)&UNK_180a9c3ac;
      cVar3 = FUN_180706a00(lVar11,0);
      if ((cVar3 != '\0') && ((0xe < uVar7 || ((0x4320U >> (uVar7 & 0x1f) & 1) == 0)))) {
        return uVar7 == 10;
      }
      return true;
    }
    goto FUN_183250150;
  case 0x1a74:
    if (cRam0000000188c92936 == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a98194;
      FUN_18048bf00(0x188885c98,uVar7,0);
      puStack_30 = (ulonglong *)&UNK_180a981a0;
      FUN_18048bf00(0x188957b60);
      cRam0000000188c92936 = '\x01';
    }
    if (*(int *)(lRam0000000188885c98 + 0xe0) == 0) {
      puStack_30 = (ulonglong *)&UNK_180a981bf;
      func_0x00018048c140(lRam0000000188885c98);
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam0000000188885c98 + 0xb8) + 0x28);
    if (lVar11 == 0) {
      puStack_30 = (ulonglong *)&UNK_180a981e5;
      lVar11 = FUN_18536e540(plVar1,uRam0000000188957b60);
      if (lVar11 == 0) {
        puStack_30 = (ulonglong *)&UNK_180a98242;
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        uVar5 = (*pcVar2)();
        return uVar5;
      }
      puStack_30 = (ulonglong *)&UNK_180a981f4;
      cVar3 = FUN_180706560(lVar11,0);
      if ((cVar3 != '\0') && ((0xe < uVar7 || ((0x6330U >> (uVar7 & 0x1f) & 1) == 0)))) {
        return uVar7 == 10;
      }
      return true;
    }
    goto FUN_183250150;
  case 0x1a75:
    if (cRam0000000188c92967 == '\0') {
      puStack_30 = (ulonglong *)&UNK_180a90a54;
      FUN_18048bf00(0x1888853a8,uVar7,0);
      cRam0000000188c92967 = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam00000001888853a8 + 0xb8) + 0x10);
    if (lVar11 == 0) {
      return false;
    }
    goto FUN_183250150;
  case 0x1a76:
    if (cRam0000000188c931bf == '\0') {
      puStack_30 = (ulonglong *)&UNK_180b49ac4;
      FUN_18048bf00(0x18889ce68,uVar7,0);
      cRam0000000188c931bf = '\x01';
    }
    lVar11 = *(longlong *)(*(longlong *)(lRam000000018889ce68 + 0xb8) + 0x60);
    if (lVar11 == 0) {
      return true;
    }
FUN_183250150:
    uStack_48 = uStack_48 & 0xffffffffffffff00;
    if (*(longlong *)(lVar11 + 0x18) == 0) {
      FUN_18048c0b0();
code_r0x0001832502c9:
      FUN_18048c0b0();
code_r0x0001832502cf:
      FUN_18048c0b0();
    }
    else {
      uStack_40 = *(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x30);
      uStackX_8 = uStackX_8 & 0xffffffffffffff00;
      puStack_30 = (ulonglong *)0x0;
      puStack_28 = &uStackX_8;
      puStack_20 = &uStack_40;
      FUN_185ca7f50(uStack_40,&uStackX_8,0);
      if (*(longlong *)(lVar11 + 0x18) == 0) goto code_r0x0001832502d9;
      uVar12 = *(undefined8 *)(*(longlong *)(lVar11 + 0x18) + 0x10);
      iVar8 = FUN_183f23b70(uVar12,*(undefined4 *)(lVar11 + 0x38),*(undefined4 *)(lVar11 + 0x14),0);
      if (*(longlong *)(lVar11 + 0x18) != 0) {
        lVar13 = *(longlong *)(*(longlong *)(lVar11 + 0x18) + 0x20);
        if (lVar13 == 0) goto code_r0x0001832502c9;
        FUN_183cf8c20(lVar13,uVar12,plVar1,0);
        FUN_183f25080(uVar12,uVar7,0);
        iVar9 = FUN_183f22380(uVar12,2,1,iVar8,0);
        if (iVar9 == 0) {
code_r0x00018325024a:
          uVar5 = FUN_183f23100(uVar12,iVar8 + 1,0);
          FUN_183f22fd0(uVar12,iVar8 + -1,0);
          uStack_48 = CONCAT71(uStack_48._1_7_,uVar5);
          if ((char)uStackX_8 != '\0') {
            func_0x000185ca7ff0(uStack_40,0);
          }
          return uVar5;
        }
        if (*(longlong *)(lVar11 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar11 + 0x18),iVar8 + -1,0);
          goto code_r0x00018325024a;
        }
        goto code_r0x0001832502cf;
      }
    }
    FUN_18048c0b0();
code_r0x0001832502d9:
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar2 = (code *)swi(3);
    uVar5 = (*pcVar2)();
    return uVar5;
  case 0x1a77:
    goto code_r0x0001824713a0;
  case 0x1a78:
    if (DAT_188ccc7f0 != '\0') {
      puStack_30 = (ulonglong *)&UNK_185c32a75;
      func_0x000180446d00(*plVar1);
    }
    break;
  case 0x1a79:
code_r0x0001824713a0:
    return uVar7 == 2;
  default:
    goto FUN_180004e80;
  }
  return true;
}

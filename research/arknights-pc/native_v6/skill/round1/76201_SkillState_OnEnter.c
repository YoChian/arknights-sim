
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SkillState_OnEnter_0x60129aa(longlong param_1,undefined4 param_2)

{
  longlong lVar1;
  longlong *plVar2;
  longlong lVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong *plVar14;
  uint uVar15;
  longlong *plVar16;
  undefined8 uStack_48;
  undefined *puStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  undefined1 *puStack_20;
  
  if (DAT_188c92798 == '\0') {
    puStack_30 = (undefined1 *)0x180a83784;
    FUN_18048bf00(&DAT_188802da8);
    puStack_30 = (undefined1 *)0x180a83790;
    FUN_18048bf00(&DAT_18885a700);
    puStack_30 = (undefined1 *)0x180a8379c;
    FUN_18048bf00(&DAT_188953998);
    puStack_30 = (undefined1 *)0x180a837a8;
    FUN_18048bf00(&DAT_188878850);
    puStack_30 = (undefined1 *)0x180a837b4;
    FUN_18048bf00(&DAT_188956720);
    puStack_30 = (undefined1 *)0x180a837c0;
    FUN_18048bf00(&DAT_188956960);
    DAT_188c92798 = '\x01';
  }
  lVar13 = **(longlong **)(_DAT_188878850 + 0xb8);
  if (lVar13 != 0) {
    if (*(longlong *)(lVar13 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar13 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar13 + 0x18) != 0) {
      uVar12 = *(undefined8 *)(*(longlong *)(lVar13 + 0x18) + 0x10);
      iVar9 = FUN_183f23b70(uVar12,*(undefined4 *)(lVar13 + 0x38),*(undefined4 *)(lVar13 + 0x14),0);
      if (*(longlong *)(lVar13 + 0x18) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar13 + 0x18) + 0x20);
        if (lVar1 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar1,uVar12,param_1,0);
          FUN_183f25080(uVar12,param_2,0);
          iVar10 = FUN_183f22380(uVar12,2,0,iVar9,0);
          if (iVar10 == 0) {
code_r0x0001834c0f1e:
            FUN_183f22fd0(uVar12,iVar9 + -1,0);
            return;
          }
          if (*(longlong *)(lVar13 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar13 + 0x18),iVar9 + -1,0);
            goto code_r0x0001834c0f1e;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    puStack_30 = (undefined1 *)0x180a837f6;
    func_0x00018048c140();
  }
  puStack_30 = (undefined1 *)0x180a83807;
  uVar12 = func_0x0001866fdac0(0xffffffff,0);
  *(undefined8 *)(param_1 + 0x18) = uVar12;
  puStack_30 = (undefined1 *)0x180a8381a;
  lVar13 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar13 == 0) goto LAB_180a838d9;
  puStack_30 = (undefined1 *)0x180a8382d;
  cVar8 = Torappu_Battle_Character_get_hasSkill_0x6012850(lVar13,0);
  lVar13 = _DAT_188956720;
  if (cVar8 != '\0') {
    puStack_30 = (undefined1 *)0x180a83840;
    lVar13 = FUN_18536e540(param_1,_DAT_188956960);
    if (lVar13 == 0) {
LAB_180a838d9:
      puStack_30 = (undefined1 *)0x180a838de;
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    puStack_30 = (undefined1 *)0x180a83853;
    plVar14 = (longlong *)Torappu_Battle_Character_get_skill_0x601284d(lVar13,0);
    puStack_30 = (undefined1 *)0x180a83862;
    lVar13 = func_0x00018045cfe0(_DAT_188802da8);
    if (lVar13 == 0) goto LAB_180a838d9;
    puStack_30 = (undefined1 *)0x180a8387f;
    EasyTouchIsReadyHandler__ctor_0x6000a20(lVar13,param_1,_DAT_188953998,0);
    if (plVar14 == (longlong *)0x0) goto LAB_180a838d9;
    if (cRam0000000188c91c66 == '\0') {
      puStack_40 = &UNK_18095b285;
      FUN_18048bf00(0x188925ba0,lVar13,0);
      puStack_40 = &UNK_18095b291;
      FUN_18048bf00(&DAT_188927d60);
      puStack_40 = &UNK_18095b29d;
      FUN_18048bf00(0x188811960);
      puStack_40 = &UNK_18095b2a9;
      FUN_18048bf00(0x1888d36c8);
      puStack_40 = &UNK_18095b2b5;
      FUN_18048bf00(&DAT_1888d3908);
      cRam0000000188c91c66 = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(lRam0000000188925ba0 + 0xb8) + 0x398);
    if (lVar1 != 0) {
      if (*(longlong *)(lVar1 + 0x18) == 0) {
        FUN_18048c0b0();
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
      uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
      uStack_38 = 0;
      puStack_30 = &stack0x00000008;
      puStack_28 = &uStack_48;
      FUN_185ca7f50(uStack_48,&stack0x00000008,0);
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        uVar12 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
        iVar9 = FUN_183f23b70(uVar12,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
          if (lVar3 == 0) {
            FUN_18048c0b0();
          }
          else {
            FUN_183cf8c20(lVar3,uVar12,plVar14,0);
            FUN_183cf8c20(lVar3,uVar12,lVar13,0);
            iVar10 = FUN_183f22380(uVar12,2,0,iVar9,0);
            if (iVar10 == 0) {
code_r0x0001832d231b:
              FUN_183f22fd0(uVar12,iVar9 + -1,0);
              return;
            }
            if (*(longlong *)(lVar1 + 0x18) != 0) {
              FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar9 + -1,0);
              goto code_r0x0001832d231b;
            }
          }
          FUN_18048c0b0();
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
      FUN_180472d50();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    plVar14[0x1d] = lVar13;
    puStack_40 = &UNK_18095b2f0;
    func_0x00018048b9e0(plVar14 + 0x1d,lVar13);
    if (DAT_188ccc7f0 != '\0') {
      puStack_40 = &UNK_18095b301;
      func_0x000180446d00(*plVar14);
    }
    puStack_40 = &UNK_18095b317;
    cVar8 = (**(code **)(*plVar14 + 0x420))(plVar14,*(undefined8 *)(*plVar14 + 0x428));
    if (cVar8 == '\0') {
      if (DAT_188ccc7f0 != '\0') {
        puStack_40 = &UNK_18095b32f;
        func_0x000180446d00(*plVar14);
      }
      puStack_40 = &UNK_18095b354;
      (**(code **)(*plVar14 + 0x5c0))(plVar14,*(undefined8 *)(*plVar14 + 0x5c8));
      puStack_40 = &UNK_18095b35e;
      cVar8 = Torappu_Battle_BasicSkill_get_hasSkillBeginAnim_0x6011bcc(plVar14,0);
      if (cVar8 != '\0') {
        puStack_40 = &UNK_18095b376;
        cVar8 = FUN_1800053c0(0x13,plVar14,0);
        if (cVar8 != '\0') {
          puStack_40 = &UNK_18095b38b;
          cVar8 = FUN_180005610(0x3b,plVar14);
          if (cVar8 != '\0') {
            if (cRam0000000188c91c67 == '\0') {
              puStack_40 = &UNK_18095b3a8;
              FUN_18048bf00(0x188925ba0);
              cRam0000000188c91c67 = '\x01';
            }
            lVar13 = *(longlong *)(*(longlong *)(lRam0000000188925ba0 + 0xb8) + 0x3a0);
            if (lVar13 == 0) {
              lVar13 = plVar14[0x1b];
              uVar15 = 0;
              if (lVar13 == 0) goto code_r0x00018095b612;
              plVar16 = (longlong *)(lVar13 + 0x20);
              for (; (int)uVar15 < *(int *)(lVar13 + 0x18); uVar15 = uVar15 + 1) {
                if (*(uint *)(lVar13 + 0x18) <= uVar15) {
                  puStack_40 = &UNK_18095b611;
                  FUN_18048c0a0();
                  pcVar4 = (code *)swi(3);
                  (*pcVar4)();
                  return;
                }
                plVar2 = (longlong *)*plVar16;
                if (plVar2 == (longlong *)0x0) goto code_r0x00018095b612;
                if (DAT_188ccc7f0 != '\0') {
                  puStack_40 = &UNK_18095b40c;
                  func_0x000180446d00(*plVar2);
                }
                puStack_40 = &UNK_18095b422;
                (**(code **)(*plVar2 + 0x240))(plVar2);
                plVar16 = plVar16 + 1;
              }
            }
            else {
              puStack_40 = &UNK_18095b437;
              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar13,plVar14,0);
            }
            if (*(char *)((longlong)plVar14 + 0x24) != '\0') {
              puStack_40 = &UNK_18095b449;
              cVar8 = FUN_185337b70(uRam00000001888d36c8);
              if (cVar8 != '\0') {
                puStack_40 = &UNK_18095b459;
                lVar13 = FUN_185337c50(_DAT_1888d3908);
                if (lVar13 == 0) goto code_r0x00018095b612;
                puStack_40 = &UNK_18095b46c;
                lVar13 = Torappu_Battle_BattleController_get_eventPool_0x600fbf9(lVar13,0);
                if (lVar13 == 0) goto code_r0x00018095b612;
                puStack_40 = &UNK_18095b48c;
                FUN_1848dca60(lVar13,0x3f,plVar14,uRam0000000188811960);
              }
            }
            puStack_40 = &UNK_18095b499;
            FUN_180005610(0x45,plVar14);
            puStack_40 = &UNK_18095b4a3;
            cVar8 = FUN_18095f910(plVar14,0);
            if (cVar8 == '\0') {
              puStack_40 = &UNK_18095b4b5;
              uVar12 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(plVar14,0);
              if (cRam0000000188c91c63 == '\0') {
                puStack_40 = &UNK_18095b4cd;
                FUN_18048bf00(0x188925ba0);
                puStack_40 = &UNK_18095b4d9;
                FUN_18048bf00(0x1888ba390);
                cRam0000000188c91c63 = '\x01';
              }
              lVar13 = *(longlong *)(*(longlong *)(lRam0000000188925ba0 + 0xb8) + 0x380);
              if (lVar13 == 0) {
                puStack_40 = &UNK_18095b506;
                lVar13 = func_0x00018045cfe0(uRam00000001888ba390);
                if (lVar13 == 0) goto code_r0x00018095b612;
                puStack_40 = &UNK_18095b51c;
                func_0x00018050cf60(lVar13,0);
                *(undefined4 *)(lVar13 + 0x10) = 0;
                *(longlong **)(lVar13 + 0x20) = plVar14;
                puStack_40 = &UNK_18095b533;
                func_0x00018048b9e0(lVar13 + 0x20,plVar14);
              }
              else {
                puStack_40 = &UNK_18095b540;
                lVar13 = XLua_DelegateBridge___Gen_Delegate_Imp73_0x6000aa9(lVar13,plVar14,0);
              }
              if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                puStack_40 = &UNK_18095b558;
                func_0x00018048c140();
              }
code_r0x00018095b5a0:
              puStack_40 = &UNK_18095b5ad;
              puVar11 = (undefined4 *)FUN_180633110(&stack0xffffffffffffffe8,uVar12,lVar13,0);
              uVar5 = puVar11[1];
              uVar6 = puVar11[2];
              uVar7 = puVar11[3];
              *(undefined4 *)(plVar14 + 0x1e) = *puVar11;
              *(undefined4 *)((longlong)plVar14 + 0xf4) = uVar5;
              *(undefined4 *)(plVar14 + 0x1f) = uVar6;
              *(undefined4 *)((longlong)plVar14 + 0xfc) = uVar7;
              puStack_40 = &UNK_18095b5c5;
              func_0x00018048b9e0(plVar14 + 0x1e,0);
              return;
            }
            puStack_40 = &UNK_18095b565;
            uVar12 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(plVar14,0);
            if (plVar14[0x1c] != 0) {
              puStack_40 = &UNK_18095b582;
              lVar13 = FUN_180005610(0x15);
              if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
                puStack_40 = &UNK_18095b59a;
                func_0x00018048c140();
              }
              goto code_r0x00018095b5a0;
            }
            goto code_r0x00018095b612;
          }
        }
      }
      if (lVar13 == 0) {
code_r0x00018095b612:
        puStack_40 = &UNK_18095b617;
        FUN_18048c0b0();
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
      puStack_40 = &UNK_18095b5f2;
      (**(code **)(lVar13 + 0x18))(*(undefined8 *)(lVar13 + 0x40),*(undefined8 *)(lVar13 + 0x28));
    }
    return;
  }
  plVar14 = *(longlong **)(param_1 + 0x10);
  if (plVar14 == (longlong *)0x0) {
    puStack_30 = &UNK_18536e4c1;
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(longlong *)
       (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18) + 0x20) ==
      0) {
    puStack_30 = &UNK_18536e494;
    (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18))
              ();
  }
  puStack_30 = &UNK_18499c9f3;
  iVar9 = func_0x0001844dc660(1,*(undefined8 *)
                                 (*(longlong *)
                                   (*(longlong *)
                                     (*(longlong *)
                                       (*(longlong *)(*(longlong *)(lVar13 + 0x20) + 0xc0) + 0x18) +
                                     0x20) + 0xc0) + 0x18));
  if (plVar14 == (longlong *)0x0) {
    puStack_30 = &UNK_18499ca0f;
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (cRam0000000188ca7590 == '\0') {
    FUN_18048bf00(0x1888fec00,iVar9,0,0);
    FUN_18048bf00(0x188885868);
    FUN_18048bf00(0x188803338);
    cRam0000000188ca7590 = '\x01';
  }
  if (iVar9 == 0) {
    iVar9 = *(int *)((longlong)plVar14 + 0x2c);
  }
  if ((char)plVar14[5] == '\0') {
    *(undefined1 *)(plVar14 + 5) = 1;
    puStack_28 = (undefined8 *)0x0;
    puStack_20 = &stack0x00000008;
    if (iVar9 == (int)plVar14[9]) {
code_r0x000182648833:
      FUN_18262d450(&puStack_20);
      return;
    }
    lVar13 = plVar14[9];
    if (cRam0000000188ca7592 == '\0') {
      FUN_18048bf00(0x1888fe780);
      cRam0000000188ca7592 = '\x01';
    }
    if ((int)lVar13 < 1) goto code_r0x000182648833;
    if (plVar14[6] == 0) goto code_r0x000182648914;
    cVar8 = FUN_1857c6f10(plVar14[6],(int)lVar13,uRam00000001888fe780);
    if (cVar8 == '\0') goto code_r0x000182648833;
    if (plVar14[10] != 0) {
      cVar8 = FUN_185c320a0(plVar14[10],iVar9,0);
      if (cVar8 == '\0') {
        FUN_18262d450(&puStack_20);
        return;
      }
      if (plVar14[10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(plVar14[10],iVar9,0);
    }
    uVar5 = (undefined4)plVar14[9];
    cVar8 = FUN_182648440(plVar14,iVar9,0);
    if (cVar8 == '\0') {
      *(undefined4 *)(plVar14 + 9) = 0xffffffff;
      plVar14[10] = 0;
      func_0x00018048b9e0(plVar14 + 10,0);
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(0x188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (plVar14[7] != 0) {
        func_0x0001851b8c60(plVar14[7],uRam0000000188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar14);
        }
        cVar8 = (**(code **)(*plVar14 + 400))(plVar14,*(undefined8 *)(*plVar14 + 0x198));
        if ((cVar8 != '\0') && (plVar14[8] != 0)) {
          plVar16 = (longlong *)plVar14[8];
          switch(*(undefined4 *)(*plVar16 + 0x11c)) {
          case 0x487:
          case 0x488:
          case 0x48a:
            break;
          case 0x489:
            FUN_183cc2f80(plVar16,0);
            break;
          case 0x48b:
            func_0x00018050cf60(plVar16,0);
            break;
          case 0x48c:
            func_0x00018050cf60(plVar16,0);
            break;
          default:
            FUN_180005310(2,uRam0000000188903f38);
          }
        }
        if (plVar14[4] != 0) {
          lVar13 = plVar14[4];
          (**(code **)(lVar13 + 0x18))
                    (*(undefined8 *)(lVar13 + 0x40),uVar5,*(undefined8 *)(lVar13 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&puStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(plVar14 + 9) = iVar9;
    if (plVar14[6] == 0) goto code_r0x000182648929;
    lVar13 = FUN_1857ed6c0(plVar14[6],iVar9,uRam00000001888fec00);
    plVar14[10] = lVar13;
    func_0x00018048b9e0(plVar14 + 10,lVar13);
    if (plVar14[10] != 0) {
      FUN_185c32d70(plVar14[10],uVar5,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar14);
      }
      (**(code **)(*plVar14 + 0x1a0))(plVar14,iVar9,uVar5,*(undefined8 *)(*plVar14 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar13 = plVar14[7];
    uVar12 = FUN_1845596e0(iVar9,0,uRam0000000188885868);
    if (lVar13 != 0) {
      FUN_1851ba9c0(lVar13,uVar12,uRam0000000188803338);
      return;
    }
    FUN_18048c0b0();
code_r0x000182648914:
    FUN_18048c0b0();
code_r0x00018264891a:
    FUN_18048c0b0();
code_r0x00018264891f:
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
code_r0x000182648929:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


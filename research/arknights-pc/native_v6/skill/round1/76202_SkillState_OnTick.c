
/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SkillState_OnTick_0x60129ab(longlong param_1,undefined8 param_2)

{
  undefined4 uVar1;
  longlong *plVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined *puStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c92799 == '\0') {
    puStack_30 = (undefined *)0x180a83a05;
    FUN_18048bf00(&DAT_18885a700);
    puStack_30 = (undefined *)0x180a83a11;
    FUN_18048bf00(&DAT_1888c3c38);
    puStack_30 = (undefined *)0x180a83a1d;
    FUN_18048bf00(&DAT_188878850);
    puStack_30 = (undefined *)0x180a83a29;
    FUN_18048bf00(&DAT_188956720);
    puStack_30 = (undefined *)0x180a83a35;
    FUN_18048bf00(&DAT_188956960);
    DAT_188c92799 = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188878850 + 0xb8) + 8);
  if (lVar8 != 0) {
    if (cRam0000000188caf41c == '\0') {
      FUN_18048bf00(&DAT_18885a700,param_1,param_2,0);
      cRam0000000188caf41c = '\x01';
    }
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    puStack_30 = (undefined *)0x0;
    puStack_28 = &stack0x00000008;
    puStack_20 = &uStack_48;
    FUN_185ca7f50(uStack_48,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      uVar11 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar7 = FUN_183f23b70(uVar11,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar3 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar3 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar3,uVar11,param_1,0);
          auStack_40[0] = param_2;
          uVar10 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
          FUN_183cfbf40(lVar3,uVar11,uVar10,0);
          iVar6 = FUN_183f22380(uVar11,2,0,iVar7,0);
          if (iVar6 == 0) {
code_r0x0001833f996e:
            FUN_183f22fd0(uVar11,iVar7 + -1,0);
            return;
          }
          if (*(longlong *)(lVar8 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar7 + -1,0);
            goto code_r0x0001833f996e;
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
  puStack_30 = (undefined *)0x180a83a6b;
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar8 == 0) goto LAB_180a83c2b;
  puStack_30 = (undefined *)0x180a83a7e;
  cVar5 = Torappu_Battle_Entity_get_canUseAbility_0x601036c(lVar8,0);
  if (cVar5 != '\0') {
LAB_180a83b38:
    uVar11 = *(undefined8 *)(param_1 + 0x18);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      puStack_30 = (undefined *)0x180a83b56;
      func_0x00018048c140();
    }
    puStack_30 = (undefined *)0x180a83b5f;
    uVar10 = func_0x0001866fdac0(0,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      puStack_30 = (undefined *)0x180a83b77;
      func_0x00018048c140();
    }
    puStack_30 = (undefined *)0x180a83b85;
    cVar5 = Torappu_MathUtil_GT_0x6000273(uVar11,uVar10,0);
    if (cVar5 != '\0') {
      uVar11 = *(undefined8 *)(param_1 + 0x18);
      if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
        puStack_30 = (undefined *)0x180a83ba2;
        func_0x00018048c140();
      }
      puStack_30 = (undefined *)0x180a83bb0;
      uVar11 = func_0x0001866fba10(uVar11,param_2,0);
      *(undefined8 *)(param_1 + 0x18) = uVar11;
      puStack_30 = (undefined *)0x180a83bc0;
      uVar10 = func_0x0001866fdac0(0,0);
      if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
        puStack_30 = (undefined *)0x180a83bd8;
        func_0x00018048c140();
      }
      puStack_30 = (undefined *)0x180a83be6;
      cVar5 = Torappu_MathUtil_LE_0x6000277(uVar11,uVar10,0);
      if (cVar5 != '\0') {
        puStack_30 = (undefined *)0x180a83bfe;
        FUN_18536e450(param_1,1,_DAT_188956720);
      }
    }
    return;
  }
  puStack_30 = (undefined *)0x180a83a95;
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar8 == 0) {
LAB_180a83c2b:
    puStack_30 = (undefined *)0x180a83c30;
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  puStack_30 = (undefined *)0x180a83aa8;
  plVar9 = (longlong *)Torappu_Battle_Character_get_skill_0x601284d(lVar8,0);
  if (plVar9 == (longlong *)0x0) goto LAB_180a83c2b;
  if (DAT_188ccc7f0 != '\0') {
    puStack_30 = (undefined *)0x180a83ac5;
    func_0x000180446d00(*plVar9);
  }
  puStack_30 = (undefined *)0x180a83adc;
  cVar5 = (**(code **)(*plVar9 + 0x250))(plVar9,*(undefined8 *)(*plVar9 + 600));
  if (cVar5 != '\0') goto LAB_180a83b38;
  puStack_30 = (undefined *)0x180a83aef;
  lVar8 = FUN_18536e540(param_1,_DAT_188956960);
  if (lVar8 == 0) goto LAB_180a83c2b;
  puStack_30 = (undefined *)0x180a83b02;
  lVar8 = Torappu_Battle_Character_get_skill_0x601284d(lVar8,0);
  if (lVar8 == 0) goto LAB_180a83c2b;
  puStack_30 = (undefined *)0x180a83b15;
  Torappu_Battle_BasicSkill_OnCastFailedInSkillState_0x6011bea(lVar8,0);
  lVar8 = _DAT_188956720;
  plVar9 = *(longlong **)(param_1 + 0x10);
  if (plVar9 == (longlong *)0x0) {
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
  iVar7 = func_0x0001844dc660(1,*(undefined8 *)
                                 (*(longlong *)
                                   (*(longlong *)
                                     (*(longlong *)
                                       (*(longlong *)(*(longlong *)(lVar8 + 0x20) + 0xc0) + 0x18) +
                                     0x20) + 0xc0) + 0x18));
  if (plVar9 == (longlong *)0x0) {
    puStack_30 = &UNK_18499ca0f;
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (cRam0000000188ca7590 == '\0') {
    FUN_18048bf00(0x1888fec00,iVar7,0,0);
    FUN_18048bf00(0x188885868);
    FUN_18048bf00(0x188803338);
    cRam0000000188ca7590 = '\x01';
  }
  if (iVar7 == 0) {
    iVar7 = *(int *)((longlong)plVar9 + 0x2c);
  }
  if ((char)plVar9[5] == '\0') {
    *(undefined1 *)(plVar9 + 5) = 1;
    puStack_28 = (undefined1 *)0x0;
    puStack_20 = (undefined8 *)&stack0x00000008;
    if (iVar7 == (int)plVar9[9]) {
code_r0x000182648833:
      FUN_18262d450(&puStack_20);
      return;
    }
    lVar8 = plVar9[9];
    if (cRam0000000188ca7592 == '\0') {
      FUN_18048bf00(0x1888fe780);
      cRam0000000188ca7592 = '\x01';
    }
    if ((int)lVar8 < 1) goto code_r0x000182648833;
    if (plVar9[6] == 0) goto code_r0x000182648914;
    cVar5 = FUN_1857c6f10(plVar9[6],(int)lVar8,uRam00000001888fe780);
    if (cVar5 == '\0') goto code_r0x000182648833;
    if (plVar9[10] != 0) {
      cVar5 = FUN_185c320a0(plVar9[10],iVar7,0);
      if (cVar5 == '\0') {
        FUN_18262d450(&puStack_20);
        return;
      }
      if (plVar9[10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(plVar9[10],iVar7,0);
    }
    uVar1 = (undefined4)plVar9[9];
    cVar5 = FUN_182648440(plVar9,iVar7,0);
    if (cVar5 == '\0') {
      *(undefined4 *)(plVar9 + 9) = 0xffffffff;
      plVar9[10] = 0;
      func_0x00018048b9e0(plVar9 + 10,0);
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(0x188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (plVar9[7] != 0) {
        func_0x0001851b8c60(plVar9[7],uRam0000000188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar9);
        }
        cVar5 = (**(code **)(*plVar9 + 400))(plVar9,*(undefined8 *)(*plVar9 + 0x198));
        if ((cVar5 != '\0') && (plVar9[8] != 0)) {
          plVar2 = (longlong *)plVar9[8];
          switch(*(undefined4 *)(*plVar2 + 0x11c)) {
          case 0x487:
          case 0x488:
          case 0x48a:
            break;
          case 0x489:
            FUN_183cc2f80(plVar2,0);
            break;
          case 0x48b:
            func_0x00018050cf60(plVar2,0);
            break;
          case 0x48c:
            func_0x00018050cf60(plVar2,0);
            break;
          default:
            FUN_180005310(2,uRam0000000188903f38);
          }
        }
        if (plVar9[4] != 0) {
          lVar8 = plVar9[4];
          (**(code **)(lVar8 + 0x18))
                    (*(undefined8 *)(lVar8 + 0x40),uVar1,*(undefined8 *)(lVar8 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&puStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(plVar9 + 9) = iVar7;
    if (plVar9[6] == 0) goto code_r0x000182648929;
    lVar8 = FUN_1857ed6c0(plVar9[6],iVar7,uRam00000001888fec00);
    plVar9[10] = lVar8;
    func_0x00018048b9e0(plVar9 + 10,lVar8);
    if (plVar9[10] != 0) {
      FUN_185c32d70(plVar9[10],uVar1,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar9);
      }
      (**(code **)(*plVar9 + 0x1a0))(plVar9,iVar7,uVar1,*(undefined8 *)(*plVar9 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar8 = plVar9[7];
    uVar11 = FUN_1845596e0(iVar7,0,uRam0000000188885868);
    if (lVar8 != 0) {
      FUN_1851ba9c0(lVar8,uVar11,uRam0000000188803338);
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


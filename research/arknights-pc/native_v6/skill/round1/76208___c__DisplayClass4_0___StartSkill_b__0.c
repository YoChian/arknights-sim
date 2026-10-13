
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __c__DisplayClass4_0___StartSkill_b__0_0x60129b1
               (longlong param_1,undefined8 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  longlong *plVar2;
  longlong *plVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined1 *puStack_20;
  
  if (DAT_188c9279e == '\0') {
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_188956720);
    FUN_18048bf00(&DAT_188956960);
    DAT_188c9279e = '\x01';
  }
  if ((*(longlong *)(param_1 + 0x10) == 0) ||
     (lVar8 = FUN_18536e540(*(longlong *)(param_1 + 0x10),_DAT_188956960), lVar8 == 0)) {
LAB_180a854e1:
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  Torappu_Battle_Character_OnAfterSkill_0x601290a(lVar8,*(undefined8 *)(param_1 + 0x18),param_3,0);
  uVar10 = *(undefined8 *)(param_1 + 0x20);
  if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  uVar9 = func_0x0001866fdac0(0,0);
  if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar6 = Torappu_MathUtil_GT_0x6000273(uVar10,uVar9,0);
  lVar5 = _DAT_188956720;
  lVar8 = *(longlong *)(param_1 + 0x10);
  if (lVar8 == 0) goto LAB_180a854e1;
  if (cVar6 != '\0') {
    *(undefined8 *)(lVar8 + 0x18) = *(undefined8 *)(param_1 + 0x20);
    return;
  }
  plVar3 = *(longlong **)(lVar8 + 0x10);
  if (plVar3 == (longlong *)0x0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(longlong *)
       (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18) + 0x20) ==
      0) {
    (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18))
              ();
  }
  iVar7 = func_0x0001844dc660(1,*(undefined8 *)
                                 (*(longlong *)
                                   (*(longlong *)
                                     (*(longlong *)
                                       (*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x18) +
                                     0x20) + 0xc0) + 0x18));
  if (plVar3 == (longlong *)0x0) {
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
    iVar7 = *(int *)((longlong)plVar3 + 0x2c);
  }
  if ((char)plVar3[5] == '\0') {
    *(undefined1 *)(plVar3 + 5) = 1;
    puStack_20 = &stack0x00000008;
    if (iVar7 == (int)plVar3[9]) {
code_r0x000182648833:
      FUN_18262d450(&puStack_20);
      return;
    }
    lVar8 = plVar3[9];
    if (cRam0000000188ca7592 == '\0') {
      FUN_18048bf00(0x1888fe780);
      cRam0000000188ca7592 = '\x01';
    }
    if ((int)lVar8 < 1) goto code_r0x000182648833;
    if (plVar3[6] == 0) goto code_r0x000182648914;
    cVar6 = FUN_1857c6f10(plVar3[6],(int)lVar8,uRam00000001888fe780);
    if (cVar6 == '\0') goto code_r0x000182648833;
    if (plVar3[10] != 0) {
      cVar6 = FUN_185c320a0(plVar3[10],iVar7,0);
      if (cVar6 == '\0') {
        FUN_18262d450(&puStack_20);
        return;
      }
      if (plVar3[10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(plVar3[10],iVar7,0);
    }
    uVar1 = (undefined4)plVar3[9];
    cVar6 = FUN_182648440(plVar3,iVar7,0);
    if (cVar6 == '\0') {
      *(undefined4 *)(plVar3 + 9) = 0xffffffff;
      plVar3[10] = 0;
      func_0x00018048b9e0(plVar3 + 10,0);
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(0x188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (plVar3[7] != 0) {
        func_0x0001851b8c60(plVar3[7],uRam0000000188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar3);
        }
        cVar6 = (**(code **)(*plVar3 + 400))(plVar3,*(undefined8 *)(*plVar3 + 0x198));
        if ((cVar6 != '\0') && (plVar3[8] != 0)) {
          plVar2 = (longlong *)plVar3[8];
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
        if (plVar3[4] != 0) {
          lVar8 = plVar3[4];
          (**(code **)(lVar8 + 0x18))
                    (*(undefined8 *)(lVar8 + 0x40),uVar1,*(undefined8 *)(lVar8 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&puStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(plVar3 + 9) = iVar7;
    if (plVar3[6] == 0) goto code_r0x000182648929;
    lVar8 = FUN_1857ed6c0(plVar3[6],iVar7,uRam00000001888fec00);
    plVar3[10] = lVar8;
    func_0x00018048b9e0(plVar3 + 10,lVar8);
    if (plVar3[10] != 0) {
      FUN_185c32d70(plVar3[10],uVar1,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar3);
      }
      (**(code **)(*plVar3 + 0x1a0))(plVar3,iVar7,uVar1,*(undefined8 *)(*plVar3 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar8 = plVar3[7];
    uVar10 = FUN_1845596e0(iVar7,0,uRam0000000188885868);
    if (lVar8 != 0) {
      FUN_1851ba9c0(lVar8,uVar10,uRam0000000188803338);
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



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SkillState__DoStartSkill_0x60129ae(longlong param_1)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  longlong *plVar2;
  longlong lVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined8 uVar9;
  longlong *plStackX_8;
  longlong *plStackX_20;
  longlong **pplStack_20;
  
  if (DAT_188c9279c == '\0') {
    FUN_18048bf00(&DAT_188878850);
    FUN_18048bf00(&DAT_188956720);
    FUN_18048bf00(&DAT_188956960);
    DAT_188c9279c = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188878850 + 0xb8) + 0x20);
  if (lVar7 != 0) {
    if (*(longlong *)(lVar7 + 0x18) == 0) {
      FUN_18048c0b0();
      UNRECOVERED_JUMPTABLE = (code *)swi(3);
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    plStackX_20 = *(longlong **)(*(longlong *)(lVar7 + 0x18) + 0x30);
    plStackX_8 = (longlong *)((ulonglong)plStackX_8 & 0xffffffffffffff00);
    pplStack_20 = &plStackX_20;
    FUN_185ca7f50(plStackX_20,&plStackX_8,0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      uVar9 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
      iVar6 = FUN_183f23b70(uVar9,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
      if (*(longlong *)(lVar7 + 0x18) != 0) {
        lVar3 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
        if (lVar3 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar3,uVar9,param_1,0);
          iVar5 = FUN_183f22380(uVar9,1,0,iVar6,0);
          if (iVar5 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar9,iVar6 + -1,0);
            if ((char)plStackX_8 != '\0') {
              func_0x000185ca7ff0(plStackX_20,0);
            }
            return;
          }
          if (*(longlong *)(lVar7 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar6 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    UNRECOVERED_JUMPTABLE = (code *)swi(3);
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  cVar4 = SkillState__StartSkill_0x60129ad(param_1,0);
  lVar7 = _DAT_188956720;
  if (cVar4 != '\0') {
    lVar7 = FUN_18536e540(param_1,_DAT_188956960);
    if ((lVar7 != 0) &&
       (plVar8 = (longlong *)Torappu_Battle_Character_get_skill_0x601284d(lVar7,0),
       plVar8 != (longlong *)0x0)) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar8);
      }
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar8 + 0x4d0);
                    /* WARNING: Could not recover jumptable at 0x000180a83cf2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)(plVar8,*(undefined8 *)(*plVar8 + 0x4d8),UNRECOVERED_JUMPTABLE);
      return;
    }
    FUN_18048c0b0();
    UNRECOVERED_JUMPTABLE = (code *)swi(3);
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  plVar8 = *(longlong **)(param_1 + 0x10);
  if (plVar8 == (longlong *)0x0) {
    FUN_18048c0b0();
    UNRECOVERED_JUMPTABLE = (code *)swi(3);
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (*(longlong *)
       (*(longlong *)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18) + 0x20) ==
      0) {
    (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(_DAT_188956720 + 0x20) + 0xc0) + 0x18))
              ();
  }
  iVar6 = func_0x0001844dc660(1,*(undefined8 *)
                                 (*(longlong *)
                                   (*(longlong *)
                                     (*(longlong *)
                                       (*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x18) +
                                     0x20) + 0xc0) + 0x18));
  if (plVar8 == (longlong *)0x0) {
    FUN_18048c0b0();
    UNRECOVERED_JUMPTABLE = (code *)swi(3);
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  plStackX_8 = plVar8;
  if (cRam0000000188ca7590 == '\0') {
    FUN_18048bf00(0x1888fec00,iVar6,0,0);
    FUN_18048bf00(0x188885868);
    FUN_18048bf00(0x188803338);
    cRam0000000188ca7590 = '\x01';
  }
  plVar8 = plStackX_8;
  if (iVar6 == 0) {
    iVar6 = *(int *)((longlong)plStackX_8 + 0x2c);
  }
  if ((char)plStackX_8[5] == '\0') {
    *(undefined1 *)(plStackX_8 + 5) = 1;
    pplStack_20 = &plStackX_8;
    if (iVar6 == (int)plStackX_8[9]) {
code_r0x000182648833:
      FUN_18262d450(&pplStack_20);
      return;
    }
    lVar7 = plStackX_8[9];
    if (cRam0000000188ca7592 == '\0') {
      FUN_18048bf00(0x1888fe780);
      cRam0000000188ca7592 = '\x01';
    }
    if ((int)lVar7 < 1) goto code_r0x000182648833;
    if (plVar8[6] == 0) goto code_r0x000182648914;
    cVar4 = FUN_1857c6f10(plVar8[6],(int)lVar7,uRam00000001888fe780);
    if (cVar4 == '\0') goto code_r0x000182648833;
    if (plStackX_8[10] != 0) {
      cVar4 = FUN_185c320a0(plStackX_8[10],iVar6,0);
      if (cVar4 == '\0') {
        FUN_18262d450(&pplStack_20);
        return;
      }
      if (plStackX_8[10] == 0) goto code_r0x00018264891a;
      FUN_185c33f30(plStackX_8[10],iVar6,0);
    }
    uVar1 = (undefined4)plStackX_8[9];
    cVar4 = FUN_182648440(plStackX_8,iVar6,0);
    if (cVar4 == '\0') {
      *(undefined4 *)(plStackX_8 + 9) = 0xffffffff;
      plStackX_8[10] = 0;
      func_0x00018048b9e0(plStackX_8 + 10,0);
      plVar8 = plStackX_8;
      if (cRam0000000188ca758f == '\0') {
        FUN_18048bf00(0x188802eb8);
        cRam0000000188ca758f = '\x01';
      }
      if (plVar8[7] != 0) {
        func_0x0001851b8c60(plVar8[7],uRam0000000188802eb8);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar8);
        }
        cVar4 = (**(code **)(*plVar8 + 400))(plVar8,*(undefined8 *)(*plVar8 + 0x198));
        if ((cVar4 != '\0') && (plVar8[8] != 0)) {
          plVar2 = (longlong *)plVar8[8];
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
        if (plVar8[4] != 0) {
          lVar7 = plVar8[4];
          (**(code **)(lVar7 + 0x18))
                    (*(undefined8 *)(lVar7 + 0x40),uVar1,*(undefined8 *)(lVar7 + 0x28));
        }
code_r0x000182648824:
        FUN_18262d450(&pplStack_20);
        return;
      }
      goto code_r0x00018264891f;
    }
    *(int *)(plStackX_8 + 9) = iVar6;
    if (plStackX_8[6] == 0) goto code_r0x000182648929;
    lVar7 = FUN_1857ed6c0(plStackX_8[6],iVar6,uRam00000001888fec00);
    plStackX_8[10] = lVar7;
    func_0x00018048b9e0(plStackX_8 + 10,lVar7);
    if (plStackX_8[10] != 0) {
      FUN_185c32d70(plStackX_8[10],uVar1,0);
      plVar8 = plStackX_8;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plStackX_8);
      }
      lVar7 = *plVar8;
      (**(code **)(lVar7 + 0x1a0))(plVar8,iVar6,uVar1,*(undefined8 *)(lVar7 + 0x1a8));
      goto code_r0x000182648824;
    }
  }
  else {
    lVar7 = plStackX_8[7];
    uVar9 = FUN_1845596e0(iVar6,0,uRam0000000188885868);
    if (lVar7 != 0) {
      FUN_1851ba9c0(lVar7,uVar9,uRam0000000188803338);
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
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  (*UNRECOVERED_JUMPTABLE)();
  return;
}


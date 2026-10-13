
/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Removing unreachable block (ram,0x00018330f795) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_Battle_CastSkill_IsAvailable_0x6011cb3(longlong param_1,undefined4 param_2)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c91cfe == '\0') {
    uStack_40 = 0x180968904;
    FUN_18048bf00(&DAT_188855d90);
    DAT_188c91cfe = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    uStack_40 = 0x180968923;
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0x38);
  if (lVar8 == 0) {
    uStack_40 = 0x18096894d;
    cVar3 = Torappu_Battle_BasicSkill_get_isUsedUp_0x6011bbd(param_1,0);
    if (cVar3 != '\0') {
      return false;
    }
    uStack_40 = 0x18096895f;
    plVar7 = (longlong *)Torappu_Battle_BasicSkill_get_ability_0x6011bb2(param_1,0);
    if (plVar7 == (longlong *)0x0) {
LAB_180968b2b:
      uStack_40 = 0x180968b30;
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      uVar4 = (*pcVar2)();
      return (bool)uVar4;
    }
    if (DAT_188ccc7f0 != '\0') {
      uStack_40 = 0x18096897c;
      func_0x000180446d00(*plVar7);
    }
    uStack_40 = 0x180968993;
    cVar3 = (**(code **)(*plVar7 + 0x270))(plVar7,*(undefined8 *)(*plVar7 + 0x278));
    if (cVar3 == '\0') {
      return false;
    }
    uStack_40 = 0x1809689a8;
    cVar3 = Torappu_Battle_BasicSkill_IsAvailable_0x6011b8f(param_1,param_2,0);
    if (cVar3 == '\0') {
      return false;
    }
    if (*(char *)(param_1 + 0x142) == '\0') {
      return true;
    }
    if (DAT_188c91cff == '\0') {
      uStack_40 = 0x1809689e0;
      FUN_18048bf00(&DAT_188855d90);
      uStack_40 = 0x1809689ec;
      FUN_18048bf00(&DAT_188936918);
      uStack_40 = 0x1809689f8;
      FUN_18048bf00(0x188938898);
      uStack_40 = 0x180968a04;
      FUN_18048bf00(&DAT_18886bf68);
      DAT_188c91cff = '\x01';
    }
    if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
      uStack_40 = 0x180968a23;
      func_0x00018048c140(_DAT_188855d90);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0x40);
    if (lVar8 == 0) {
      uStack_40 = 0x180968a4a;
      lVar8 = func_0x00018045cfe0(_DAT_18886bf68);
      if (lVar8 != 0) {
        uStack_40 = 0x180968a65;
        FUN_1848f2320(lVar8,_DAT_188936918);
        if (DAT_188c91c3d == '\0') {
          uStack_40 = 0x180968a7a;
          FUN_18048bf00(&DAT_188925ba0);
          DAT_188c91c3d = '\x01';
        }
        lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
        if (lVar9 == 0) {
          lVar9 = *(longlong *)(param_1 + 0xa8);
        }
        else {
          uStack_40 = 0x180968aaf;
          lVar9 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar9,param_1,0);
        }
        if (lVar9 != 0) {
          uStack_40 = 0x180968ad0;
          Torappu_Battle_Character_FetchTokenOrHost_0x60128b5(lVar9,0x80,lVar8,0);
          return 0 < *(int *)(lVar8 + 0x18);
        }
      }
      goto LAB_180968b2b;
    }
    if (*(longlong *)(lVar8 + 0x18) == 0) {
      FUN_18048c0b0();
code_r0x0001832b3a74:
      FUN_18048c0b0();
code_r0x0001832b3a7a:
      FUN_18048c0b0();
    }
    else {
      uStack_48 = *(ulonglong *)(*(longlong *)(lVar8 + 0x18) + 0x30);
      uStack_38 = 0;
      puStack_30 = &stack0x00000008;
      puStack_28 = &uStack_48;
      FUN_185ca7f50(uStack_48,&stack0x00000008,0);
      if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x0001832b3a84;
      uVar1 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
      iVar5 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        lVar9 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
        if (lVar9 == 0) goto code_r0x0001832b3a74;
        FUN_183cf8c20(lVar9,uVar1,param_1,0);
        iVar6 = FUN_183f22380(uVar1,1,1,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001832b39f4:
          uVar4 = FUN_183f23100(uVar1,iVar5 + 1,0);
          FUN_183f22fd0(uVar1,iVar5 + -1,0);
          return (bool)uVar4;
        }
        if (*(longlong *)(lVar8 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar5 + -1,0);
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
    uVar4 = (*pcVar2)();
    return (bool)uVar4;
  }
  if (cRam0000000188cafc31 == '\0') {
    FUN_18048bf00(0x18880c778,param_1,param_2,0);
    cRam0000000188cafc31 = '\x01';
  }
  uStack_48 = uStack_48 & 0xffffffffffffff00;
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x00018330f7ec:
    FUN_18048c0b0();
code_r0x00018330f7f2:
    FUN_18048c0b0();
  }
  else {
    uStack_40 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    puStack_30 = (undefined1 *)0x0;
    puStack_28 = (undefined8 *)&stack0x00000008;
    puStack_20 = &uStack_40;
    FUN_185ca7f50(uStack_40,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x00018330f7fc;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar9 == 0) goto code_r0x00018330f7ec;
      FUN_183cf8c20(lVar9,uVar1,param_1,0);
      uStack_48 = CONCAT44(param_2,(undefined4)uStack_48);
      uVar10 = func_0x00018048b9c0(uRam000000018880c778,(longlong)&uStack_48 + 4);
      FUN_183cfbf40(lVar9,uVar1,uVar10,0);
      iVar6 = FUN_183f22380(uVar1,2,1,iVar5,0);
      if (iVar6 == 0) {
code_r0x00018330f768:
        uVar4 = FUN_183f23100(uVar1,iVar5 + 1,0);
        FUN_183f22fd0(uVar1,iVar5 + -1,0);
        return (bool)uVar4;
      }
      if (*(longlong *)(lVar8 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar5 + -1,0);
        goto code_r0x00018330f768;
      }
      goto code_r0x00018330f7f2;
    }
  }
  FUN_18048c0b0();
code_r0x00018330f7fc:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  uVar4 = (*pcVar2)();
  return (bool)uVar4;
}


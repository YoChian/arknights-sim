
/* WARNING: Removing unreachable block (ram,0x0001837013bc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong *
Torappu_Battle_BasicSkill_GetAttackBlackboard_0x6011bee(longlong param_1,longlong param_2)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong *unaff_RSI;
  bool bVar10;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_40;
  undefined1 *puStack_38;
  undefined8 *puStack_30;
  
  if (DAT_188c91c5f == '\0') {
    puStack_30 = (undefined8 *)0x180959d95;
    FUN_18048bf00(&DAT_188925ba0);
    puStack_30 = (undefined8 *)0x180959da1;
    FUN_18048bf00(&DAT_1888c6e90);
    DAT_188c91c5f = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x360);
  if (lVar9 == 0) {
    if (-1 < *(int *)(param_1 + 0x2c)) {
      if (param_2 == 0) {
        puStack_30 = (undefined8 *)0x180959e33;
        FUN_18048c0b0();
        pcVar3 = (code *)swi(3);
        plVar7 = (longlong *)(*pcVar3)();
        return plVar7;
      }
      if (*(int *)(param_2 + 0xb0) != *(int *)(param_1 + 0x2c)) {
        if (*(longlong *)(param_1 + 0x30) != 0) {
          puStack_30 = (undefined8 *)0x180959df3;
          cVar4 = FUN_1844a8890(*(undefined8 *)(param_1 + 0x30),*(undefined4 *)(param_2 + 0xb0),
                                _DAT_1888c6e90);
          if (cVar4 != '\0') goto LAB_180959e04;
        }
        return (longlong *)0x0;
      }
    }
LAB_180959e04:
    return *(longlong **)(param_1 + 0xb8);
  }
  if (cRam0000000188caf5c5 == '\0') {
    FUN_18048bf00(0x1888cbaa8,param_1,param_2,0);
    FUN_18048bf00(0x188941920);
    FUN_18048bf00(0x188906850);
    cRam0000000188caf5c5 = '\x01';
  }
  uStack_50 = 0;
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x000183701412:
    FUN_18048c0b0();
code_r0x000183701418:
    FUN_18048ba10(unaff_RSI,lVar9);
code_r0x000183701423:
    FUN_18048c0b0();
  }
  else {
    uStack_58 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
    uStack_40 = 0;
    puStack_38 = &stack0x00000008;
    puStack_30 = &uStack_58;
    FUN_185ca7f50(uStack_58,&stack0x00000008,0);
    if (*(longlong *)(lVar9 + 0x18) == 0) goto code_r0x00018370142d;
    uVar1 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      unaff_RSI = *(longlong **)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (unaff_RSI != (longlong *)0x0) {
        FUN_183cf8c20(unaff_RSI,uVar1,param_1,0);
        FUN_183cf8c20(unaff_RSI,uVar1,param_2,0);
        bVar10 = true;
        iVar6 = FUN_183f22380(uVar1,2,1,iVar5,0);
        if (iVar6 != 0) {
          if (*(longlong *)(lVar9 + 0x18) == 0) goto code_r0x000183701412;
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar5 + -1,0);
        }
        uVar8 = uRam00000001888cbaa8;
        if (*(int *)(lRam0000000188906850 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar8 = FUN_185eded20(uVar8,0);
        unaff_RSI = (longlong *)FUN_183cf3ce0(unaff_RSI,uVar1,iVar5 + 1,uVar8,0);
        FUN_183f22fd0(uVar1,iVar5 + -1,0);
        lVar9 = lRam0000000188941920;
        if (unaff_RSI == (longlong *)0x0) {
          return (longlong *)0x0;
        }
        lVar2 = *unaff_RSI;
        if (DAT_188ccc7f0 == '\0') {
          if ((*(byte *)(lVar2 + 0x130) < *(byte *)(lRam0000000188941920 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(lVar2 + 200) + -8 +
               (ulonglong)*(byte *)(lRam0000000188941920 + 0x130) * 8) != lRam0000000188941920)) {
            bVar10 = false;
          }
          bVar10 = !bVar10;
        }
        else {
          cVar4 = func_0x0001804463e0(lVar2,lRam0000000188941920);
          bVar10 = cVar4 == '\0';
        }
        plVar7 = (longlong *)0x0;
        if (!bVar10) {
          plVar7 = unaff_RSI;
        }
        if (plVar7 != (longlong *)0x0) {
          return plVar7;
        }
        goto code_r0x000183701418;
      }
      goto code_r0x000183701423;
    }
  }
  FUN_18048c0b0();
code_r0x00018370142d:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  plVar7 = (longlong *)(*pcVar3)();
  return plVar7;
}



/* WARNING: Removing unreachable block (ram,0x0001833561ec) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong * Torappu_Battle_BattleFactory_CreateEnemy_0x60117c0(longlong param_1,undefined8 param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong *unaff_RSI;
  bool bVar10;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_40;
  undefined1 *puStack_38;
  undefined8 *puStack_30;
  
  if (DAT_188c918dd == '\0') {
    uStack_40 = 0x1808e9195;
    FUN_18048bf00(&DAT_18892a3a0);
    uStack_40 = 0x1808e91a1;
    FUN_18048bf00(&DAT_188932ce8);
    uStack_40 = 0x1808e91ad;
    FUN_18048bf00(&DAT_188937848);
    uStack_40 = 0x1808e91b9;
    FUN_18048bf00(&DAT_188815538);
    DAT_188c918dd = '\x01';
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18892a3a0 + 0xb8) + 0x40);
  if (lVar8 == 0) {
    if (DAT_188c91938 == '\0') {
      uStack_40 = 0x1808e91ef;
      FUN_18048bf00(&DAT_188871340);
      uStack_40 = 0x1808e91fb;
      FUN_18048bf00(&DAT_188816f48);
      DAT_188c91938 = '\x01';
    }
    if (*(int *)(_DAT_188871340 + 0xe0) == 0) {
      uStack_40 = 0x1808e9217;
      func_0x00018048c140();
    }
    uStack_40 = 0x1808e9229;
    uVar6 = Torappu_FileUtil_Combine_0x600062a(_DAT_188816f48,param_2,0);
    if (*(int *)(_DAT_188815538 + 0xe0) == 0) {
      uStack_40 = 0x1808e9241;
      func_0x00018048c140();
    }
    uStack_40 = 0x1808e9250;
    plVar7 = (longlong *)FUN_184589b30(uVar6,_DAT_188937848);
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      uStack_40 = 0x1808e9268;
      func_0x00018048c140();
    }
    uStack_40 = 0x1808e9275;
    cVar3 = FUN_186b638d0(plVar7,0,0);
    if (cVar3 != '\0') {
      return (longlong *)0x0;
    }
    if (plVar7 != (longlong *)0x0) {
      uStack_40 = 0x1808e9290;
      lVar8 = FUN_186b59e30(plVar7,0);
      if (lVar8 != 0) {
        uStack_40 = 0x1808e92a8;
        FUN_186b73fb0(lVar8,*(undefined8 *)(param_1 + 0x28),0);
        uStack_40 = 0x1808e92b2;
        lVar8 = FUN_186b59e30(plVar7,0);
        if (DAT_188c8fd8f == '\0') {
          uStack_40 = 0x1808e92ca;
          FUN_18048bf00(&DAT_188829ff0);
          DAT_188c8fd8f = '\x01';
        }
        if (lVar8 != 0) {
          uStack_40 = 0x1808e9306;
          FUN_186b759d0(lVar8,&stack0xffffffffffffffe8,0);
          return plVar7;
        }
      }
    }
    uStack_40 = 0x1808e933e;
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    plVar7 = (longlong *)(*pcVar2)();
    return plVar7;
  }
  if (cRam0000000188cafdc2 == '\0') {
    FUN_18048bf00(0x188923610,param_1,param_2,0);
    FUN_18048bf00(0x18881b6b0);
    FUN_18048bf00(0x188906850);
    cRam0000000188cafdc2 = '\x01';
  }
  uStack_50 = 0;
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x000183356242:
    FUN_18048c0b0();
code_r0x000183356248:
    FUN_18048ba10(unaff_RSI,lVar8);
code_r0x000183356253:
    FUN_18048c0b0();
  }
  else {
    uStack_58 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
    uStack_40 = 0;
    puStack_38 = &stack0x00000008;
    puStack_30 = &uStack_58;
    FUN_185ca7f50(uStack_58,&stack0x00000008,0);
    if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x00018335625d;
    uVar6 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      unaff_RSI = *(longlong **)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (unaff_RSI != (longlong *)0x0) {
        FUN_183cf8c20(unaff_RSI,uVar6,param_1,0);
        FUN_183cf8c20(unaff_RSI,uVar6,param_2,0);
        bVar10 = true;
        iVar5 = FUN_183f22380(uVar6,2,1,iVar4,0);
        if (iVar5 != 0) {
          if (*(longlong *)(lVar8 + 0x18) == 0) goto code_r0x000183356242;
          FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar4 + -1,0);
        }
        uVar9 = uRam0000000188923610;
        if (*(int *)(lRam0000000188906850 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar9 = FUN_185eded20(uVar9,0);
        unaff_RSI = (longlong *)FUN_183cf3ce0(unaff_RSI,uVar6,iVar4 + 1,uVar9,0);
        FUN_183f22fd0(uVar6,iVar4 + -1,0);
        lVar8 = lRam000000018881b6b0;
        if (unaff_RSI == (longlong *)0x0) {
          return (longlong *)0x0;
        }
        lVar1 = *unaff_RSI;
        if (DAT_188ccc7f0 == '\0') {
          if ((*(byte *)(lVar1 + 0x130) < *(byte *)(lRam000000018881b6b0 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(lVar1 + 200) + -8 +
               (ulonglong)*(byte *)(lRam000000018881b6b0 + 0x130) * 8) != lRam000000018881b6b0)) {
            bVar10 = false;
          }
          bVar10 = !bVar10;
        }
        else {
          cVar3 = func_0x0001804463e0(lVar1,lRam000000018881b6b0);
          bVar10 = cVar3 == '\0';
        }
        plVar7 = (longlong *)0x0;
        if (!bVar10) {
          plVar7 = unaff_RSI;
        }
        if (plVar7 != (longlong *)0x0) {
          return plVar7;
        }
        goto code_r0x000183356248;
      }
      goto code_r0x000183356253;
    }
  }
  FUN_18048c0b0();
code_r0x00018335625d:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  plVar7 = (longlong *)(*pcVar2)();
  return plVar7;
}


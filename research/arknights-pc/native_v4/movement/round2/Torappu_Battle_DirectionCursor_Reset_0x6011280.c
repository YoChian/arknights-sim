
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_DirectionCursor_Reset_0x6011280(longlong param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  longlong lVar11;
  
  if (DAT_188c914de == '\0') {
    FUN_18048bf00(&DAT_18895f6c8);
    FUN_18048bf00(&DAT_18896d0f8);
    DAT_188c914de = '\x01';
  }
  lVar10 = *(longlong *)(*(longlong *)(_DAT_18896d0f8 + 0xb8) + 0x50);
  if (lVar10 == 0) {
    Torappu_Battle_BasicCursor_Reset_0x6011211(param_1,0);
    cVar3 = Torappu_Battle_BasicCursor_get_visitEveryTileCenter_0x6011203(param_1,0);
    if ((cVar3 == '\0') &&
       (cVar3 = Torappu_Battle_BasicCursor_get_visitEveryNodeCenter_0x6011205(param_1,0),
       cVar3 == '\0')) {
      return;
    }
    if (*(longlong *)(param_1 + 0x60) != 0) {
LAB_180896814:
      lVar10 = *(longlong *)(param_1 + 0x10);
      uVar9 = 0;
      if (lVar10 != 0) {
        lVar11 = 0;
        while (*(longlong *)(lVar10 + 0x10) != 0) {
          iVar4 = Torappu_Battle_Map_get_height_0x6011154(*(longlong *)(lVar10 + 0x10),0);
          if (iVar4 <= (int)uVar9) {
            return;
          }
          uVar8 = 0;
          lVar10 = 0;
          while( true ) {
            if ((*(longlong *)(param_1 + 0x10) == 0) ||
               (*(longlong *)(*(longlong *)(param_1 + 0x10) + 0x10) == 0)) goto LAB_1808968f6;
            iVar4 = Torappu_Battle_Map_get_width_0x6011153();
            if (iVar4 <= (int)uVar8) break;
            lVar1 = *(longlong *)(param_1 + 0x60);
            if (lVar1 == 0) goto LAB_1808968f6;
            if ((**(uint **)(lVar1 + 0x10) <= uVar9) ||
               (lVar7 = *(longlong *)(*(uint **)(lVar1 + 0x10) + 4), (uint)lVar7 <= uVar8)) {
              FUN_18048c0a0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            uVar8 = uVar8 + 1;
            lVar7 = lVar7 * lVar11 + lVar10;
            lVar10 = lVar10 + 1;
            *(undefined1 *)(lVar7 + 0x20 + lVar1) = 0;
          }
          lVar10 = *(longlong *)(param_1 + 0x10);
          uVar9 = uVar9 + 1;
          lVar11 = lVar11 + 1;
          if (lVar10 == 0) break;
        }
      }
LAB_1808968f6:
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    if ((*(longlong *)(param_1 + 0x10) != 0) &&
       (lVar10 = *(longlong *)(*(longlong *)(param_1 + 0x10) + 0x10), lVar10 != 0)) {
      Torappu_Battle_Map_get_height_0x6011154(lVar10,0);
      if ((*(longlong *)(param_1 + 0x10) != 0) &&
         (lVar10 = *(longlong *)(*(longlong *)(param_1 + 0x10) + 0x10), lVar10 != 0)) {
        Torappu_Battle_Map_get_width_0x6011153(lVar10,0);
        uVar6 = func_0x00018048b9d0(_DAT_18895f6c8,&stack0xffffffffffffffe8);
        *(undefined8 *)(param_1 + 0x60) = uVar6;
        func_0x00018048b9e0(param_1 + 0x60,uVar6);
        goto LAB_180896814;
      }
    }
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar10 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar10 + 0x18) != 0) {
    uVar6 = *(undefined8 *)(*(longlong *)(lVar10 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar10 + 0x38),*(undefined4 *)(lVar10 + 0x14),0);
    if (*(longlong *)(lVar10 + 0x18) != 0) {
      lVar11 = *(longlong *)(*(longlong *)(lVar10 + 0x18) + 0x20);
      if (lVar11 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar11,uVar6,param_1,0);
        iVar5 = FUN_183f22380(uVar6,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar6,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar10 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar10 + 0x18),iVar4 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


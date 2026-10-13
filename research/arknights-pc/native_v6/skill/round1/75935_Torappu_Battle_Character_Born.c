
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_Born_0x60128a0(longlong param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  
  if (DAT_188c925d9 == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_1888c4f88);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c925d9 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x3b8);
  if (lVar6 == 0) {
    lVar6 = Torappu_Battle_Entity_get_originTile_0x601034d(param_1,0);
    if (lVar6 != 0) {
      uVar7 = Torappu_Battle_VisualObject_get_gridPosition_0x6013030(lVar6,0);
      if (*(int *)(_DAT_1888c4f88 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_1888c4f88);
      }
      cVar3 = Torappu_GridPosition_op_Inequality_0x6006d95
                        (uVar7,*(undefined8 *)(*(longlong *)(_DAT_1888c4f88 + 0xb8) + 0x60),0);
      if (cVar3 != '\0') {
        lVar6 = Torappu_Battle_Entity_get_originTile_0x601034d(param_1,0);
        if (lVar6 == 0) goto LAB_180a27719;
        cVar3 = Torappu_Battle_Tile_get_isHidden_0x6011411(lVar6,0);
        if (cVar3 != '\0') {
          return;
        }
      }
      Torappu_Battle_BObject_Born_0x600fe03(param_1,0);
      uVar7 = *(undefined8 *)(param_1 + 0x348);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(uVar7,0,0);
      if (cVar3 == '\0') {
        return;
      }
      if (*(longlong *)(param_1 + 0x348) != 0) {
        lVar6 = FUN_186b59d80(*(longlong *)(param_1 + 0x348),0);
        if (lVar6 != 0) {
          FUN_186b5c530(lVar6,1,0);
          return;
        }
      }
    }
LAB_180a27719:
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar7 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar7,param_1,0);
        iVar5 = FUN_183f22380(uVar7,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar7,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
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


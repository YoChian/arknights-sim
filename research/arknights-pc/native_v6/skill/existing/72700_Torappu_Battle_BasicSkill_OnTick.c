
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnTick_0x6011bfd(longlong *param_1,undefined8 param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong *plVar8;
  longlong lVar9;
  bool bVar10;
  
  if (DAT_188c91c6e == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c6e = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x3d8);
  if (lVar9 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b(lVar9,param_1,param_2,0);
    return;
  }
  plVar8 = (longlong *)param_1[0x15];
  if (plVar8 == (longlong *)0x0) goto LAB_18095d089;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar8);
  }
  cVar3 = (**(code **)(*plVar8 + 0x3c0))(plVar8,*(undefined8 *)(*plVar8 + 0x3c8));
  if (cVar3 == '\0') {
    return;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 0x620))(param_1,*(undefined8 *)(*param_1 + 0x628));
  if ((char)param_1[0x13] != '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar3 = (**(code **)(*param_1 + 0x2e0))(param_1,*(undefined8 *)(*param_1 + 0x2e8));
    if (cVar3 == '\0') {
      FUN_180005610(0x35,param_1);
    }
  }
  if (*(char *)((longlong)param_1 + 0x26) != '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar3 = (**(code **)(*param_1 + 0x2e0))(param_1,*(undefined8 *)(*param_1 + 0x2e8));
    if (cVar3 != '\0') {
      if (param_1[0x15] == 0) {
LAB_18095d089:
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      cVar3 = func_0x000180663060(param_1[0x15],0);
      if (cVar3 != '\0') {
        if (param_1[0x15] == 0) goto LAB_18095d089;
        cVar3 = Torappu_Battle_Entity_get_isSilenced_0x60103da(param_1[0x15],0);
        if (cVar3 != '\0') {
          FUN_180005610(0x38,param_1);
        }
      }
    }
  }
  if (cRam0000000188c91c6f == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888c3c38);
    cRam0000000188c91c6f = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x3e0);
  if (lVar9 == 0) {
    uVar6 = FUN_180961100(param_1,0);
    if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar7 = func_0x0001866fdac0(0,0);
    if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_1866e4c60(uVar6,uVar7,0);
    if (cVar3 == '\0') {
      return;
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    cVar3 = (**(code **)(*param_1 + 0x2e0))(param_1,*(undefined8 *)(*param_1 + 0x2e8));
    if (cVar3 == '\0') {
      return;
    }
    if (*(char *)((longlong)param_1 + 0x9a) != '\0') {
      return;
    }
    bVar10 = cRam0000000188c91c58 == '\0';
    *(undefined1 *)((longlong)param_1 + 0x9a) = 1;
    if (bVar10) {
      FUN_18048bf00(&DAT_188925ba0);
      cRam0000000188c91c58 = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x328);
    if (lVar9 == 0) {
      if (cRam0000000188c91c26 == '\0') {
        FUN_18048bf00(&DAT_188925ba0);
        cRam0000000188c91c26 = '\x01';
      }
      lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 400);
      if (lVar9 == 0) {
        plVar8 = (longlong *)param_1[0x18];
      }
      else {
        plVar8 = (longlong *)FUN_183324130(lVar9,param_1,0);
      }
      if (plVar8 != (longlong *)0x0) {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar8);
        }
        (**(code **)(*plVar8 + 0x4d0))(plVar8,*(undefined8 *)(*plVar8 + 0x4d8));
        return;
      }
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar6 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar1 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar1 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar1,uVar6,param_1,0);
        iVar5 = FUN_183f22380(uVar6,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar6,iVar4 + -1,0);
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar4 + -1,0);
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


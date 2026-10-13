
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicCursor_Reset_0x6011211(longlong param_1)

{
  longlong *plVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  longlong lVar9;
  
  if (DAT_188c914b9 == '\0') {
    FUN_18048bf00(&DAT_188923568);
    DAT_188c914b9 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188923568 + 0xb8) + 0x80);
  if (lVar9 == 0) {
    *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
    if (DAT_188c8f5b5 == '\0') {
      FUN_18048bf00(&DAT_188828bc0);
      DAT_188c8f5b5 = '\x01';
    }
    uVar7 = (*(undefined4 **)(_DAT_188828bc0 + 0xb8))[1];
    *(undefined4 *)(param_1 + 0x1c) = **(undefined4 **)(_DAT_188828bc0 + 0xb8);
    *(undefined4 *)(param_1 + 0x20) = uVar7;
    if (cRam0000000188c914bc == '\0') {
      FUN_18048bf00(&DAT_188923568);
      cRam0000000188c914bc = '\x01';
    }
    lVar9 = *(longlong *)(*(longlong *)(_DAT_188923568 + 0xb8) + 0x98);
    if (lVar9 == 0) {
      iVar8 = *(int *)(param_1 + 0x18);
      if (*(longlong *)(param_1 + 0x10) == 0) goto DAT_180876c66;
      iVar6 = Torappu_Battle_Route_get_checkpointCnt_0x60112d3(*(longlong *)(param_1 + 0x10),0);
      if (iVar6 <= iVar8) {
        return;
      }
      if (*(int *)(param_1 + 0x18) < 0) {
        *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
      }
      else {
        lVar9 = *(longlong *)(param_1 + 0x28);
        if (lVar9 == 0) goto DAT_180876c66;
        if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
        lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
        if (lVar9 == 0) goto DAT_180876c66;
        func_0x00018050cf60(lVar9,0);
        lVar9 = *(longlong *)(param_1 + 0x28);
        if (lVar9 == 0) goto DAT_180876c66;
        if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
        lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
        if (lVar9 == 0) goto DAT_180876c66;
        uVar7 = FUN_1800053c0(0xc,lVar9,*(undefined4 *)(param_1 + 0x18));
        *(undefined4 *)(param_1 + 0x18) = uVar7;
      }
      if (cRam0000000188c914a9 == '\0') {
        FUN_18048bf00(&DAT_188923568);
        cRam0000000188c914a9 = '\x01';
      }
      if (**(longlong **)(_DAT_188923568 + 0xb8) == 0) {
        cVar5 = *(char *)(param_1 + 0x38);
      }
      else {
        cVar5 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75
                          (**(longlong **)(_DAT_188923568 + 0xb8),param_1,0);
      }
      if (cVar5 == '\0') {
code_r0x000180876bec:
        iVar8 = *(int *)(param_1 + 0x18);
        if (*(longlong *)(param_1 + 0x10) != 0) {
          iVar6 = Torappu_Battle_Route_get_checkpointCnt_0x60112d3(*(longlong *)(param_1 + 0x10),0);
          if (iVar6 <= iVar8) {
            return;
          }
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 != 0) {
            if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) {
code_r0x000180876c6c:
              FUN_18048c0a0();
              pcVar4 = (code *)swi(3);
              (*pcVar4)();
              return;
            }
            plVar1 = *(longlong **)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
            if (plVar1 != (longlong *)0x0) {
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(*plVar1);
              }
              (**(code **)(*plVar1 + 0x1e0))(plVar1,*(undefined8 *)(*plVar1 + 0x1e8));
              return;
            }
          }
        }
      }
      else {
        iVar8 = *(int *)(param_1 + 0x18);
        lVar9 = *(longlong *)(param_1 + 0x10);
        while (lVar9 != 0) {
          iVar6 = Torappu_Battle_Route_get_checkpointCnt_0x60112d3(lVar9,0);
          if (iVar6 <= iVar8) goto code_r0x000180876bec;
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 == 0) break;
          if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
          lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
          if (lVar9 == 0) break;
          iVar8 = FilterSetting_get_filterType_0x600b7f9(lVar9,0);
          if (iVar8 == 0) goto code_r0x000180876bec;
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 == 0) break;
          if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
          lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
          if (lVar9 == 0) break;
          iVar8 = FilterSetting_get_filterType_0x600b7f9(lVar9,0);
          if (iVar8 == 8) goto code_r0x000180876bec;
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 == 0) break;
          if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
          lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
          if (lVar9 == 0) break;
          iVar8 = FilterSetting_get_filterType_0x600b7f9(lVar9,0);
          if (iVar8 == 5) goto code_r0x000180876bec;
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 == 0) break;
          if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
          lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
          if (lVar9 == 0) break;
          iVar8 = FilterSetting_get_filterType_0x600b7f9(lVar9,0);
          if (iVar8 == 6) goto code_r0x000180876bec;
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 == 0) break;
          if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
          lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
          if (lVar9 == 0) break;
          iVar8 = FilterSetting_get_filterType_0x600b7f9(lVar9,0);
          if (iVar8 == 10) goto code_r0x000180876bec;
          lVar9 = *(longlong *)(param_1 + 0x28);
          if (lVar9 == 0) break;
          if (*(uint *)(lVar9 + 0x18) <= *(uint *)(param_1 + 0x18)) goto code_r0x000180876c6c;
          plVar1 = *(longlong **)(lVar9 + 0x20 + (longlong)(int)*(uint *)(param_1 + 0x18) * 8);
          uVar7 = *(undefined4 *)(param_1 + 0x18);
          if (plVar1 == (longlong *)0x0) break;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar1);
          }
          iVar8 = (**(code **)(*plVar1 + 0x200))(plVar1,uVar7,*(undefined8 *)(*plVar1 + 0x208));
          *(int *)(param_1 + 0x18) = iVar8;
          lVar9 = *(longlong *)(param_1 + 0x10);
        }
      }
DAT_180876c66:
      FUN_18048c0b0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar8 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar3 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar3,uVar2,param_1,0);
        iVar6 = FUN_183f22380(uVar2,1,0,iVar8,0);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar8 + -1,0);
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar8 + -1,0);
          goto code_r0x0001833100e8;
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


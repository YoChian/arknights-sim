
/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool Torappu_Battle_Ability_get_isReady_0x600f63a(longlong *param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  char cVar9;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c8fccf == '\0') {
    puStack_30 = (undefined1 *)0x1805d805e;
    FUN_18048bf00(&DAT_1889733f0);
    DAT_188c8fccf = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xa0);
  if (lVar1 == 0) {
    if (DAT_188c8fcce == '\0') {
      puStack_30 = (undefined1 *)0x1805d8098;
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fcce = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x98);
    if (lVar1 == 0) {
      if (DAT_188c8fcd5 == '\0') {
        puStack_30 = (undefined1 *)0x1805d80d7;
        FUN_18048bf00(&DAT_1889733f0);
        DAT_188c8fcd5 = '\x01';
      }
      lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xd0);
      if (lVar1 == 0) {
        cVar9 = (char)param_1[0x12];
      }
      else {
        puStack_30 = (undefined1 *)0x1805d810c;
        cVar9 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
      }
      if (cVar9 == '\0') {
        return false;
      }
      if (DAT_188ccc7f0 != '\0') {
        puStack_30 = (undefined1 *)0x1805d8125;
        func_0x000180446d00(*param_1);
      }
      puStack_30 = (undefined1 *)0x1805d813b;
      iVar7 = (**(code **)(*param_1 + 0x220))(param_1,*(undefined8 *)(*param_1 + 0x228));
      cVar9 = iVar7 == 4;
    }
    else {
      puStack_30 = (undefined1 *)0x1805d8151;
      cVar9 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
    }
    if (cVar9 != '\0') {
      if (DAT_188c8fcd1 == '\0') {
        puStack_30 = (undefined1 *)0x1805d816e;
        FUN_18048bf00(&DAT_1889733f0);
        DAT_188c8fcd1 = '\x01';
      }
      lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xb0);
      if (lVar1 == 0) {
        plVar2 = (longlong *)param_1[0xe];
        if (plVar2 == (longlong *)0x0) {
          puStack_30 = (undefined1 *)0x1805d822f;
          FUN_18048c0b0();
          pcVar5 = (code *)swi(3);
          uVar6 = (*pcVar5)();
          return (bool)uVar6;
        }
        if (DAT_188ccc7f0 != '\0') {
          puStack_30 = (undefined1 *)0x1805d81ac;
          func_0x000180446d00(*plVar2);
        }
        puStack_30 = (undefined1 *)0x1805d81c2;
        cVar9 = (**(code **)(*plVar2 + 0x180))(plVar2,*(undefined8 *)(*plVar2 + 0x188));
      }
      else {
        puStack_30 = (undefined1 *)0x1805d81cf;
        cVar9 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
      }
      if (cVar9 != '\0') {
        if (DAT_188ccc7f0 != '\0') {
          puStack_30 = (undefined1 *)0x1805d81e4;
          func_0x000180446d00(*param_1);
        }
        puStack_30 = (undefined1 *)0x1805d81fa;
        cVar9 = (**(code **)(*param_1 + 0x280))(param_1,*(undefined8 *)(*param_1 + 0x288));
        return cVar9 == '\0';
      }
    }
    return false;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar4 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar4 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar4,uVar3,param_1,0);
      iVar8 = FUN_183f22380(uVar3,1,1,iVar7,0);
      if (iVar8 == 0) {
code_r0x0001832b39f4:
        uVar6 = FUN_183f23100(uVar3,iVar7 + 1,0);
        FUN_183f22fd0(uVar3,iVar7 + -1,0);
        return (bool)uVar6;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar5 = (code *)swi(3);
  uVar6 = (*pcVar5)();
  return (bool)uVar6;
}


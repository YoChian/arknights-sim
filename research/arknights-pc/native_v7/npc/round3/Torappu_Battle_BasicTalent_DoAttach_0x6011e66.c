/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_BasicTalent_DoAttach_0x6011e66(longlong param_1)
{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  ulonglong auStackX_8 [3];
  undefined8 uStackX_20;
  if (DAT_188c91e2f == '\0') {
    FUN_18048bf00(&DAT_188925de0);
    DAT_188c91e2f = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925de0 + 0xb8) + 0x158);
  if (lVar1 == 0) {
    plVar2 = *(longlong **)(param_1 + 0x38);
    if (plVar2 == (longlong *)0x0) {
      FUN_18048c0b0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    uVar3 = *(undefined8 *)(param_1 + 0x30);
    if (cRam0000000188c8fce7 == '\0') {
      FUN_18048bf00(&DAT_1889733f0,uVar3,0);
      cRam0000000188c8fce7 = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x160);
    if (lVar1 == 0) {
      if (cRam0000000188c8fcd5 == '\0') {
        FUN_18048bf00(&DAT_1889733f0);
        cRam0000000188c8fcd5 = '\x01';
      }
      lVar1 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0xd0);
      if (lVar1 == 0) {
        cVar6 = (char)plVar2[0x12];
      }
      else {
        cVar6 = FUN_1832b3910(lVar1,plVar2,0);
      }
      if (cVar6 == '\0') {
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar2);
        }
                    /* WARNING: Could not recover jumptable at 0x0001805d4ba8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(*plVar2 + 800))(plVar2,uVar3,*(undefined8 *)(*plVar2 + 0x328));
        return;
      }
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar1,plVar2,uVar3,0);
    }
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  auStackX_8[0] = auStackX_8[0] & 0xffffffffffffff00;
  FUN_185ca7f50(uStackX_20,auStackX_8,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar4 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar4 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar4,uVar3,param_1,0);
        iVar8 = FUN_183f22380(uVar3,1,0,iVar7,0);
        if (iVar8 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar3,iVar7 + -1,0);
          if ((char)auStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

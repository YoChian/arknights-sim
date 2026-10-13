
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_OnCastStart_0x600f6bb(longlong *param_1)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  
  if (DAT_188c8fd39 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_1888797f0);
    FUN_18048bf00(&DAT_1888199a0);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c8fd39 = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x128);
  if (lVar6 == 0) {
    if (DAT_188c8fd23 == '\0') {
      FUN_18048bf00(&DAT_188974cb0);
      DAT_188c8fd23 = '\x01';
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x70);
    if (lVar6 == 0) {
      *(undefined1 *)((longlong)param_1 + 0x115) = 0;
    }
    else {
      XLua_DelegateBridge___Gen_Delegate_Imp26_0x6000a7a(lVar6,param_1,0,0);
    }
    Torappu_Battle_AbilityStandard_DoUpdatePlaybackSpeed_0x600f6cb(param_1,1,0);
    lVar6 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    (**(code **)(*param_1 + 0x730))(param_1,*(undefined8 *)(*param_1 + 0x738));
    if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    cVar3 = FUN_186b63a70(lVar6,0,0);
    if (cVar3 != '\0') {
      if (lVar6 == 0) {
LAB_1805d19d6:
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      lVar7 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar6,0);
      lVar8 = func_0x00018045cfe0(_DAT_1888797f0);
      if (lVar8 == 0) goto LAB_1805d19d6;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      LuaMsgHandlerCallback__ctor_0x601b9cb(lVar8,param_1,*(undefined8 *)(*param_1 + 0x678),0);
      if (lVar7 == 0) goto LAB_1805d19d6;
      FUN_1848dcb10(lVar7,0x14,lVar8,_DAT_1888199a0);
      lVar7 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar6,0);
      lVar8 = func_0x00018045cfe0(_DAT_1888797f0);
      if (lVar8 == 0) goto LAB_1805d19d6;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      LuaMsgHandlerCallback__ctor_0x601b9cb(lVar8,param_1,*(undefined8 *)(*param_1 + 0x688),0);
      if (lVar7 == 0) goto LAB_1805d19d6;
      FUN_1848dcb10(lVar7,0x19,lVar8,_DAT_1888199a0);
      lVar7 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar6,0);
      lVar8 = func_0x00018045cfe0(_DAT_1888797f0);
      if (lVar8 == 0) goto LAB_1805d19d6;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      LuaMsgHandlerCallback__ctor_0x601b9cb(lVar8,param_1,*(undefined8 *)(*param_1 + 0x698),0);
      if (lVar7 == 0) goto LAB_1805d19d6;
      FUN_1848dcb10(lVar7,0x1a,lVar8,_DAT_1888199a0);
      lVar7 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar6,0);
      lVar8 = func_0x00018045cfe0(_DAT_1888797f0);
      if (lVar8 == 0) goto LAB_1805d19d6;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      LuaMsgHandlerCallback__ctor_0x601b9cb(lVar8,param_1,*(undefined8 *)(*param_1 + 0x6a8),0);
      if (lVar7 == 0) goto LAB_1805d19d6;
      FUN_1848dcb10(lVar7,0x21,lVar8,_DAT_1888199a0);
      Torappu_Battle_Entity_OnAbilityStart_0x6010485(lVar6,param_1,0);
    }
    if (cRam0000000188c8fcfd == '\0') {
      FUN_18048bf00(&DAT_1889733f0,0);
      cRam0000000188c8fcfd = '\x01';
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x210);
    if (lVar6 == 0) {
      if (param_1[3] != 0) {
        lVar6 = param_1[3];
                    /* WARNING: Could not recover jumptable at 0x0001805d648a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(lVar6 + 0x18))(*(undefined8 *)(lVar6 + 0x40),*(undefined8 *)(lVar6 + 0x28));
        return;
      }
      return;
    }
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar7 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar7 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar7,uVar1,param_1,0);
        iVar5 = FUN_183f22380(uVar1,1,0,iVar4,0);
        if (iVar5 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar1,iVar4 + -1,0);
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


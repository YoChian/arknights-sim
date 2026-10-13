
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SkillState_OnExit_0x60129ac(undefined8 param_1,undefined4 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined8 uVar1;
  longlong lVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c9279a == '\0') {
    puStack_30 = (undefined1 *)0x180a83904;
    FUN_18048bf00(&DAT_188878850);
    puStack_30 = (undefined1 *)0x180a83910;
    FUN_18048bf00(&DAT_188956960);
    DAT_188c9279a = '\x01';
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188878850 + 0xb8) + 0x10);
  if (lVar5 == 0) {
    puStack_30 = (undefined1 *)0x180a83941;
    lVar5 = FUN_18536e540(param_1,_DAT_188956960);
    if (lVar5 != 0) {
      puStack_30 = (undefined1 *)0x180a83954;
      lVar5 = Torappu_Battle_Character_get_skill_0x601284d(lVar5,0);
      if (lVar5 != 0) {
        puStack_30 = (undefined1 *)0x180a83963;
        Torappu_Battle_BasicSkill_InterruptStartIfNot_0x6011bf0(lVar5,0);
        puStack_30 = (undefined1 *)0x180a83972;
        lVar5 = FUN_18536e540(param_1,_DAT_188956960);
        if (lVar5 != 0) {
          puStack_30 = (undefined1 *)0x180a83981;
          plVar6 = (longlong *)Torappu_Battle_Character_get_skill_0x601284d(lVar5,0);
          if (plVar6 != (longlong *)0x0) {
            if (DAT_188ccc7f0 != '\0') {
              puStack_30 = (undefined1 *)0x180a8399a;
              func_0x000180446d00(*plVar6);
            }
            UNRECOVERED_JUMPTABLE = *(code **)(*plVar6 + 0x4c0);
                    /* WARNING: Could not recover jumptable at 0x000180a839b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            (*UNRECOVERED_JUMPTABLE)(plVar6,*(undefined8 *)(*plVar6 + 0x4c8),UNRECOVERED_JUMPTABLE);
            return;
          }
        }
      }
    }
    puStack_30 = (undefined1 *)0x180a839d8;
    FUN_18048c0b0();
    UNRECOVERED_JUMPTABLE = (code *)swi(3);
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (*(longlong *)(lVar5 + 0x18) == 0) {
    FUN_18048c0b0();
    UNRECOVERED_JUMPTABLE = (code *)swi(3);
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = auStack_48;
  FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
  if (*(longlong *)(lVar5 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar5 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar5 + 0x38),*(undefined4 *)(lVar5 + 0x14),0);
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        FUN_183f25080(uVar1,param_2,0);
        iVar4 = FUN_183f22380(uVar1,2,0,iVar3,0);
        if (iVar4 == 0) {
code_r0x0001834c0f1e:
          FUN_183f22fd0(uVar1,iVar3 + -1,0);
          return;
        }
        if (*(longlong *)(lVar5 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar5 + 0x18),iVar3 + -1,0);
          goto code_r0x0001834c0f1e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  (*UNRECOVERED_JUMPTABLE)();
  return;
}


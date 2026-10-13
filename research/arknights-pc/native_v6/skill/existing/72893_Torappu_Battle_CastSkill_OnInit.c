
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_CastSkill_OnInit_0x6011cbe(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  
  if (DAT_188c91d09 == '\0') {
    FUN_18048bf00(&DAT_188855d90);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91d09 = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0x90);
  if (lVar9 != 0) {
    if (*(longlong *)(lVar9 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30),&stack0x00000008,0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      uVar7 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
      iVar5 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        lVar2 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
        if (lVar2 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar2,uVar7,param_1,0);
          iVar6 = FUN_183f22380(uVar7,1,0,iVar5,0);
          if (iVar6 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar7,iVar5 + -1,0);
            return;
          }
          if (*(longlong *)(lVar9 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar5 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  Torappu_Battle_BasicSkill_OnInit_0x6011be4(param_1,0);
  uVar7 = *(undefined8 *)(param_1 + 0x120);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar4 = FUN_186b63a70(uVar7,0,0);
  if (cVar4 != '\0') {
    plVar1 = *(longlong **)(param_1 + 0x120);
    uVar7 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
    uVar8 = Torappu_Battle_BasicSkill_get_ability_0x6011bb2(param_1,0);
    if (plVar1 == (longlong *)0x0) goto LAB_1809690c1;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar1);
    }
    (**(code **)(*plVar1 + 0x200))(plVar1,uVar7,uVar8,*(undefined8 *)(*plVar1 + 0x208));
  }
  uVar7 = *(undefined8 *)(param_1 + 0x138);
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar4 = FUN_186b63a70(uVar7,0,0);
  if (cVar4 != '\0') {
    lVar9 = *(longlong *)(param_1 + 0x138);
    uVar7 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
    uVar8 = Torappu_Battle_BasicSkill_get_ability_0x6011bb2(param_1,0);
    if (lVar9 == 0) goto LAB_1809690c1;
    FUN_18000d9c0(0xc,lVar9,uVar7,uVar8,0);
  }
  if (DAT_188c91c26 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c26 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 400);
  if (lVar9 == 0) {
    lVar9 = *(longlong *)(param_1 + 0xc0);
  }
  else {
    lVar9 = XLua_DelegateBridge___Gen_Delegate_Imp2921_0x60015c9(lVar9,param_1,0);
  }
  if (lVar9 == 0) {
LAB_1809690c1:
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  cVar4 = Torappu_Battle_Ability_get_isAttached_0x600f640(lVar9,0);
  if (cVar4 == '\0') {
    lVar9 = Torappu_Battle_BasicSkill_get_ability_0x6011bb2(param_1,0);
    uVar7 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
    if (lVar9 == 0) goto LAB_1809690c1;
    Torappu_Battle_Ability_Attach_0x600f653(lVar9,uVar7,0);
  }
  return;
}


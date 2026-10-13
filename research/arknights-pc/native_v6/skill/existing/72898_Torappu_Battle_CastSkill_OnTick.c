
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_CastSkill_OnTick_0x6011cc3(longlong *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  char cVar2;
  longlong *plVar3;
  longlong lVar4;
  
  if (DAT_188c91d0e == '\0') {
    FUN_18048bf00(&DAT_188855d90);
    DAT_188c91d0e = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0xb8);
  if (lVar4 == 0) {
    Torappu_Battle_BasicSkill_OnTick_0x6011bfd(param_1,param_2,0);
    if (DAT_188c91c3d == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar4 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar4 == 0) {
      plVar3 = (longlong *)param_1[0x15];
    }
    else {
      plVar3 = (longlong *)XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar4,param_1,0);
    }
    if (plVar3 == (longlong *)0x0) {
LAB_18096923e:
      FUN_18048c0b0();
      UNRECOVERED_JUMPTABLE = (code *)swi(3);
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar3);
    }
    cVar2 = (**(code **)(*plVar3 + 0x3c0))(plVar3,*(undefined8 *)(*plVar3 + 0x3c8));
    if (cVar2 != '\0') {
      lVar4 = Torappu_Battle_BasicSkill_get_data_0x6011bc1(param_1,0);
      if (lVar4 == 0) goto LAB_18096923e;
      if (*(int *)(lVar4 + 0x40) == 2) {
        cVar2 = FUN_1800053c0(0x13,param_1,0);
        if (cVar2 != '\0') {
          cVar2 = FUN_180005610(0x30,param_1);
          if (cVar2 != '\0') {
            lVar4 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
            if (lVar4 != 0) {
              uVar1 = *(undefined4 *)(lVar4 + 0x20);
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00(*param_1);
              }
              UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x4a0);
                    /* WARNING: Could not recover jumptable at 0x000180005410. Too many branches */
                    /* WARNING: Treating indirect jump as call */
              (*UNRECOVERED_JUMPTABLE)
                        (param_1,uVar1,*(undefined8 *)(*param_1 + 0x4a8),UNRECOVERED_JUMPTABLE);
              return;
            }
            goto LAB_18096923e;
          }
        }
      }
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp427_0x6000c0b(lVar4,param_1,param_2,0);
  }
  return;
}


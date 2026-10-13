/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Buff_OnOwnerFinish_0x600fe83(undefined8 param_1,int param_2,undefined8 param_3)
{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined1 auStack_f8 [240];
  if (DAT_188c90308 == '\0') {
    FUN_18048bf00(&DAT_18895c250);
    FUN_18048bf00(&DAT_188920710);
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1889312e8);
    DAT_188c90308 = '\x01';
  }
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x350);
  if (lVar3 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp2937_0x60015d9(lVar3,param_1,param_2,param_3,0);
    return;
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar2 = Torappu_Battle_Entity_IfReasonIsDeath_0x601049a(param_2,0);
  if (cVar2 == '\0') {
    if (param_2 == 1) {
      lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
      if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x50) == 0)) goto LAB_18068651f;
      FUN_185367f40(*(longlong *)(lVar3 + 0x50),param_3,_DAT_1889312e8);
      cVar2 = Torappu_Battle_Buff__IsActionValid_0x600fe58(param_1,0x22,0);
      if (cVar2 != '\0') {
        uVar4 = 0x22;
LAB_180686428:
        Torappu_Battle_Buff__RunActions_0x600fee4(auStack_f8,param_1,uVar4,1,0);
      }
LAB_18068643d:
      lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
      if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x50) == 0)) goto LAB_18068651f;
      FUN_185733a00(*(longlong *)(lVar3 + 0x50),_DAT_188920710);
    }
  }
  else {
    cVar2 = Torappu_Battle_Buff__IsActionValid_0x600fe58(param_1,3,0);
    if (cVar2 != '\0') {
      lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
      if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x50) == 0)) goto LAB_18068651f;
      FUN_185367f40(*(longlong *)(lVar3 + 0x50),param_3,_DAT_1889312e8);
      Torappu_Battle_Buff__RunActions_0x600fee4(auStack_f8,param_1,3,1,0);
      lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
      if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x50) == 0)) goto LAB_18068651f;
      FUN_185733a00(*(longlong *)(lVar3 + 0x50),_DAT_188920710);
    }
    if (param_2 != 8) {
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b63a70(param_3,0,0);
      if (cVar2 != '\0') {
        lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
        if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x50) == 0)) goto LAB_18068651f;
        FUN_185367f40(*(longlong *)(lVar3 + 0x50),param_3,_DAT_1889312e8);
        cVar2 = Torappu_Battle_Buff__IsActionValid_0x600fe58(param_1,0x1d,0);
        if (cVar2 != '\0') {
          uVar4 = 0x1d;
          goto LAB_180686428;
        }
        goto LAB_18068643d;
      }
    }
  }
  lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
  if ((lVar3 != 0) && (*(longlong *)(lVar3 + 0x50) != 0)) {
    FUN_185367f40(*(longlong *)(lVar3 + 0x50),param_3,_DAT_1889312e8);
    cVar2 = Torappu_Battle_Buff__IsActionValid_0x600fe58(param_1,4,0);
    if (cVar2 != '\0') {
      Torappu_Battle_Buff__RunActions_0x600fee4(auStack_f8,param_1,4,1,0);
    }
    lVar3 = Torappu_Battle_Buff_get_context_0x600fe2a(param_1,0);
    if ((lVar3 != 0) && (*(longlong *)(lVar3 + 0x50) != 0)) {
      FUN_185733a00(*(longlong *)(lVar3 + 0x50),_DAT_188920710);
      return;
    }
  }
LAB_18068651f:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

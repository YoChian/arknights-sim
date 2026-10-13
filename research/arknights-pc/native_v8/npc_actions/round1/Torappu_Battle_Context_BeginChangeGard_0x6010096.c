
longlong Torappu_Battle_Context_BeginChangeGard_0x6010096(longlong param_1)

{
  code *pcVar1;
  longlong lVar2;
  undefined1 auStack_f8 [240];
  
  if (param_1 != 0) {
    Torappu_Battle_Context__DuplicateAll_0x6010098(auStack_f8,param_1,0);
    return param_1;
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  lVar2 = (*pcVar1)();
  return lVar2;
}


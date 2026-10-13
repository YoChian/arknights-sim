
void ChangeGuard__ctor_0x60100a5(longlong *param_1,longlong param_2)

{
  code *pcVar1;
  undefined1 auStack_f8 [248];
  
  *param_1 = param_2;
  if (param_2 != 0) {
    Torappu_Battle_Context__DuplicateAll_0x6010098(auStack_f8,param_2,0);
    return;
  }
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ChangeGuard_set_target_0x60100a9(longlong *param_1,undefined8 param_2)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  undefined1 auStack_18 [16];
  
  if (DAT_188c905b7 == '\0') {
    FUN_18048bf00(&DAT_18891e0d8);
    FUN_18048bf00(&DAT_18891e318);
    DAT_188c905b7 = '\x01';
  }
  if ((*param_1 != 0) && (lVar1 = *(longlong *)(*param_1 + 0x18), lVar1 != 0)) {
    FUN_185733450(lVar1,_DAT_18891e0d8);
    lVar1 = _DAT_18891e318;
    if ((*param_1 != 0) && (lVar2 = *(longlong *)(*param_1 + 0x18), lVar2 != 0)) {
      FUN_1845638c0(auStack_18,param_2,
                    *(undefined8 *)
                     (*(longlong *)(*(longlong *)(_DAT_18891e318 + 0x20) + 0xc0) + 0x18));
      if (lVar2 != 0) {
        if (*(longlong *)
             (*(longlong *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x20) + 0x20) == 0)
        {
          (*(code *)**(undefined8 **)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x20))();
        }
        FUN_185367ff0(lVar2,auStack_18,
                      *(undefined8 *)(*(longlong *)(*(longlong *)(lVar1 + 0x20) + 0xc0) + 0x20));
        return;
      }
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
  }
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


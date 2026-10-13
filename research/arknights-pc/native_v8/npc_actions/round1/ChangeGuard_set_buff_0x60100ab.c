
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ChangeGuard_set_buff_0x60100ab(longlong *param_1,undefined8 param_2)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  undefined1 auStack_18 [16];
  
  if (DAT_188c905b9 == '\0') {
    FUN_18048bf00(&DAT_18891d598);
    FUN_18048bf00(&DAT_18891d7d8);
    DAT_188c905b9 = '\x01';
  }
  if ((*param_1 != 0) && (lVar1 = *(longlong *)(*param_1 + 0x20), lVar1 != 0)) {
    FUN_185733450(lVar1,_DAT_18891d598);
    lVar1 = _DAT_18891d7d8;
    if ((*param_1 != 0) && (lVar2 = *(longlong *)(*param_1 + 0x20), lVar2 != 0)) {
      FUN_1845638c0(auStack_18,param_2,
                    *(undefined8 *)
                     (*(longlong *)(*(longlong *)(_DAT_18891d7d8 + 0x20) + 0xc0) + 0x18));
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


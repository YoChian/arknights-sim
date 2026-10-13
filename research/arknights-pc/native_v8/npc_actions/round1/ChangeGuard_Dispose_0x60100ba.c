
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ChangeGuard_Dispose_0x60100ba(longlong *param_1)

{
  longlong lVar1;
  code *pcVar2;
  undefined1 auStack_b8 [40];
  undefined1 auStack_90 [136];
  
  lVar1 = *param_1;
  if (lVar1 == 0) {
    return;
  }
  if (DAT_188c905b2 == '\0') {
    FUN_18048bf00(&DAT_18891d598);
    FUN_18048bf00(&DAT_18891e0d8);
    FUN_18048bf00(&DAT_18891f510);
    FUN_18048bf00(&DAT_18891ec18);
    FUN_18048bf00(&DAT_188920050);
    FUN_18048bf00(&DAT_188920dd0);
    FUN_18048bf00(&DAT_188921490);
    FUN_18048bf00(&DAT_188920710);
    DAT_188c905b2 = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x10) != 0) {
    FUN_185733450(*(longlong *)(lVar1 + 0x10),_DAT_18891e0d8);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      FUN_185733450(*(longlong *)(lVar1 + 0x18),_DAT_18891e0d8);
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        FUN_185733450(*(longlong *)(lVar1 + 0x20),_DAT_18891d598);
        if (*(longlong *)(lVar1 + 0x28) != 0) {
          FUN_185733a00(*(longlong *)(lVar1 + 0x28),_DAT_188920050);
          if (*(longlong *)(lVar1 + 0x30) != 0) {
            FUN_185733ab0(auStack_90,*(longlong *)(lVar1 + 0x30),_DAT_188920dd0);
            if (*(longlong *)(lVar1 + 0x38) != 0) {
              FUN_185733450(*(longlong *)(lVar1 + 0x38),_DAT_18891ec18);
              if (*(longlong *)(lVar1 + 0x40) != 0) {
                FUN_185733450(*(longlong *)(lVar1 + 0x40),_DAT_18891f510);
                if (*(longlong *)(lVar1 + 0x50) != 0) {
                  FUN_185733a00(*(longlong *)(lVar1 + 0x50),_DAT_188920710);
                  if (*(longlong *)(lVar1 + 0x48) != 0) {
                    FUN_185733c00(auStack_b8,*(longlong *)(lVar1 + 0x48),_DAT_188921490);
                    if (*(longlong *)(lVar1 + 0x58) != 0) {
                      FUN_185733450(*(longlong *)(lVar1 + 0x58),_DAT_18891d598);
                      return;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void SortedDoubleBufferedBuffList__ctor_0x600ff09(undefined8 param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  
  if (DAT_188c9038d == '\0') {
    FUN_18048bf00(&DAT_1888d5b50);
    DAT_188c9038d = '\x01';
  }
  if (DAT_188c9038b == '\0') {
    FUN_18048bf00(&DAT_1888d5490);
    FUN_18048bf00(&DAT_18882b068);
    DAT_188c9038b = '\x01';
  }
  FUN_185a18d90(param_1,_DAT_18882b068);
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888d5490 + 0xb8) + 0x18);
  if (lVar1 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar1,param_1,0);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_1888d5b50 + 0xb8) + 8);
  if (lVar1 == 0) {
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
  acStackX_8[0] = '\0';
  FUN_185ca7f50(uStackX_20,acStackX_8,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar3 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar3,uVar2,param_1,0);
        iVar6 = FUN_183f22380(uVar2,1,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar5 + -1,0);
          if (acStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}


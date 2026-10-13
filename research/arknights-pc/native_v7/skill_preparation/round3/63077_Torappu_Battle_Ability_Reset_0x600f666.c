
/* WARNING: Removing unreachable block (ram,0x000181e047ff) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Ability_Reset_0x600f666(longlong *param_1)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 unaff_RDI;
  bool bVar9;
  
  if (DAT_188c8fcf7 == '\0') {
    FUN_18048bf00(&DAT_1889733f0);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c8fcf7 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x1e0);
  if (lVar7 != 0) {
    if (*(longlong *)(lVar7 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30),&stack0x00000008,0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      uVar6 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
      iVar4 = FUN_183f23b70(uVar6,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
      if (*(longlong *)(lVar7 + 0x18) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
        if (lVar1 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar1,uVar6,param_1,0);
          iVar5 = FUN_183f22380(uVar6,1,0,iVar4,0);
          if (iVar5 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar6,iVar4 + -1,0);
            return;
          }
          if (*(longlong *)(lVar7 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar4 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  uVar6 = (**(code **)(*param_1 + 0x230))(param_1,*(undefined8 *)(*param_1 + 0x238));
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(uVar6,0);
  if (cVar3 != '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    lVar7 = (**(code **)(*param_1 + 0x230))(param_1,*(undefined8 *)(*param_1 + 0x238));
    uVar6 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
    if (lVar7 == 0) goto LAB_1805d6bb5;
    FUN_18000d9c0(0xc,lVar7,uVar6,param_1,0);
  }
  lVar7 = param_1[0xe];
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  uVar6 = (**(code **)(*param_1 + 0x250))(param_1,*(undefined8 *)(*param_1 + 600));
  if (lVar7 != 0) {
    if (cRam0000000188ca0cfe == '\0') {
      FUN_18048bf00(0x18885a700,uVar6,0,0,unaff_RDI);
      FUN_18048bf00(0x1888915d8);
      cRam0000000188ca0cfe = '\x01';
    }
    if (*(int *)(lRam000000018885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar8 = func_0x0001866fdac0(0,0);
    if (*(int *)(lRam00000001888915d8 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = FUN_1866ff750(uVar8,uVar6,0);
    bVar9 = cRam0000000188ca0cfd == '\0';
    *(undefined8 *)(lVar7 + 0x10) = uVar6;
    if (bVar9) {
      FUN_18048bf00(0x18885a700);
      cRam0000000188ca0cfd = '\x01';
    }
    if (*(int *)(lRam000000018885a700 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    uVar6 = func_0x0001866fdac0(0,0);
    *(undefined8 *)(lVar7 + 0x18) = uVar6;
    return;
  }
LAB_1805d6bb5:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


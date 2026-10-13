
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy_States_DisappearState__InterruptDisappearTweenIfNot_0x6012bef
               (longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined4 *puVar10;
  longlong *plVar11;
  char acStackX_8 [24];
  undefined8 uStackX_20;
  undefined8 uStack_28;
  undefined8 uStack_20;
  
  if (DAT_188c9297a == '\0') {
    FUN_18048bf00(&DAT_188884f30);
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c9297a = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x60);
  if (lVar9 == 0) {
    FUN_184260440(*(undefined8 *)(param_1 + 0x30),
                  CONCAT71((int7)((ulonglong)*(longlong *)(_DAT_188884f30 + 0xb8) >> 8),1));
    lVar9 = FUN_18536e540(param_1,_DAT_188957b60);
    if (lVar9 != 0) {
      puVar10 = (undefined4 *)Torappu_Battle_Entity_GetBodyColor_0x601041d(&uStack_28,lVar9,0);
      uVar4 = *puVar10;
      uVar5 = puVar10[1];
      uVar6 = puVar10[2];
      plVar11 = (longlong *)FUN_18536e540(param_1,_DAT_188957b60);
      if (plVar11 != (longlong *)0x0) {
        uStack_20._4_4_ = 0x3f800000;
        uStack_28._0_4_ = uVar4;
        uStack_28._4_4_ = uVar5;
        uStack_20._0_4_ = uVar6;
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*plVar11);
        }
        (**(code **)(*plVar11 + 0x560))(plVar11,&uStack_28,*(undefined8 *)(*plVar11 + 0x568));
        return;
      }
    }
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (*(longlong *)(lVar9 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStackX_20 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
  acStackX_8[0] = '\0';
  uStack_28 = acStackX_8;
  uStack_20 = &uStackX_20;
  FUN_185ca7f50(uStackX_20,acStackX_8,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        iVar8 = FUN_183f22380(uVar1,1,0,iVar7,0);
        if (iVar8 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar1,iVar7 + -1,0);
          if (acStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uStackX_20,0);
          }
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar7 + -1,0);
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



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_SwitchToSkillState_0x60128a6(undefined8 param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 unaff_RSI;
  ulonglong uStackX_8;
  
  if (DAT_188c925df == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_188819760);
    FUN_18048bf00(&DAT_18889b5f0);
    DAT_188c925df = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 1000);
  if (lVar8 == 0) {
    cVar4 = Torappu_Battle_Entity_get_isSkillActivatableInAbnormal_0x60103dc(param_1,0);
    if ((cVar4 != '\0') &&
       (cVar4 = Torappu_Battle_Entity_ContainsIrresistibleAbnormalFlagsBuff_0x6010408(param_1,0),
       cVar4 == '\0')) {
      Torappu_Battle_Entity_RemoveAllStatusResistableBuffs_0x60103fc(param_1,0);
    }
    lVar8 = Torappu_Battle_Character_get_stateMachine_0x6012882(param_1,0);
    if (lVar8 != 0) {
      FUN_18499c9d0(lVar8,4,_DAT_18889b5f0);
      lVar8 = Torappu_Battle_Entity_get_eventPool_0x6010338(param_1,0);
      if (lVar8 != 0) {
        uVar7 = func_0x0001844dc660(5,**(undefined8 **)(*(longlong *)(_DAT_188819760 + 0x20) + 0xc0)
                                   );
        if ((lVar8 != 0) &&
           (lVar9 = FUN_18672ebc0(lVar8,*(undefined8 *)(lVar8 + 0x10),uVar7,0), lVar9 != 0)) {
          FUN_18672d3c0(lVar9,0,0);
          lVar9 = FUN_18672ebc0(lVar8,*(undefined8 *)(lVar8 + 0x18),uVar7,0);
          if (lVar9 != 0) {
            FUN_18672d3c0(lVar9,0,0);
            lVar8 = *(longlong *)(lVar8 + 0x18);
            if (cRam0000000188cc3a06 == '\0') {
              FUN_18048bf00(0x1888f5540,lVar8,uVar7,0,unaff_RSI);
              FUN_18048bf00(0x1888f59c0);
              FUN_18048bf00(0x1888f5c00);
              FUN_18048bf00(0x18884e2e8);
              FUN_18048bf00(0x1888b5590);
              cRam0000000188cc3a06 = '\x01';
            }
            if (lVar8 != 0) {
              cVar4 = FUN_1857c6f10(lVar8,uVar7,uRam00000001888f5540);
              if (cVar4 == '\0') {
                return;
              }
              lVar9 = FUN_1857ed6c0(lVar8,uVar7,uRam00000001888f5c00);
              FUN_1857de990(lVar8,uVar7,uRam00000001888f59c0);
              if (lVar9 != 0) {
                FUN_18672d6e0(lVar9,0);
                if (*(int *)(lRam000000018884e2e8 + 0xe0) == 0) {
                  func_0x00018048c140(lRam000000018884e2e8);
                }
                if (**(longlong **)(lRam000000018884e2e8 + 0xb8) != 0) {
                  FUN_1805072d0(**(longlong **)(lRam000000018884e2e8 + 0xb8),lVar9,
                                uRam00000001888b5590);
                  return;
                }
              }
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
    }
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (*(longlong *)(lVar8 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uVar1 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x30);
  uStackX_8 = uStackX_8 & 0xffffffffffffff00;
  FUN_185ca7f50(uVar1,&uStackX_8,0);
  if (*(longlong *)(lVar8 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar8 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar8 + 0x38),*(undefined4 *)(lVar8 + 0x14),0);
    if (*(longlong *)(lVar8 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar8 + 0x18) + 0x20);
      if (lVar9 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar9,uVar2,param_1,0);
        iVar6 = FUN_183f22380(uVar2,1,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar5 + -1,0);
          if ((char)uStackX_8 != '\0') {
            func_0x000185ca7ff0(uVar1,0);
          }
          return;
        }
        if (*(longlong *)(lVar8 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar8 + 0x18),iVar5 + -1,0);
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


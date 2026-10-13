
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Character_OnSkillFinish_0x601290f(undefined8 param_1)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 unaff_RSI;
  undefined8 unaff_RDI;
  
  if (DAT_188c92648 == '\0') {
    FUN_18048bf00(&DAT_18886c268);
    FUN_18048bf00(&DAT_188819760);
    DAT_188c92648 = '\x01';
  }
  if (*(int *)(_DAT_18886c268 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18886c268);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_18886c268 + 0xb8) + 0x730);
  if (lVar6 == 0) {
    lVar6 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
    uVar7 = Torappu_Battle_Character_get_skill_0x601284d(param_1,0);
    if (lVar6 != 0) {
      BuffContainer_OnSkillFinish_0x600ff92(lVar6,uVar7,0);
      lVar6 = Torappu_Battle_Entity_get_eventPool_0x6010338(param_1,0);
      uVar7 = Torappu_Battle_Character_get_skill_0x601284d(param_1,0);
      if (lVar6 != 0) {
        uVar5 = func_0x0001844dc660(7,**(undefined8 **)(*(longlong *)(_DAT_188819760 + 0x20) + 0xc0)
                                    ,uVar7,_DAT_188819760,unaff_RDI);
        if ((lVar6 != 0) &&
           (lVar8 = FUN_18672ebc0(lVar6,*(undefined8 *)(lVar6 + 0x10),uVar5,0), lVar8 != 0)) {
          FUN_18672d3c0(lVar8,uVar7,0);
          lVar8 = FUN_18672ebc0(lVar6,*(undefined8 *)(lVar6 + 0x18),uVar5,0);
          if (lVar8 != 0) {
            FUN_18672d3c0(lVar8,uVar7,0);
            lVar6 = *(longlong *)(lVar6 + 0x18);
            if (cRam0000000188cc3a06 == '\0') {
              FUN_18048bf00(0x1888f5540,lVar6,uVar5,0,unaff_RSI);
              FUN_18048bf00(0x1888f59c0);
              FUN_18048bf00(0x1888f5c00);
              FUN_18048bf00(0x18884e2e8);
              FUN_18048bf00(0x1888b5590);
              cRam0000000188cc3a06 = '\x01';
            }
            if (lVar6 != 0) {
              cVar2 = FUN_1857c6f10(lVar6,uVar5,uRam00000001888f5540);
              if (cVar2 == '\0') {
                return;
              }
              lVar8 = FUN_1857ed6c0(lVar6,uVar5,uRam00000001888f5c00);
              FUN_1857de990(lVar6,uVar5,uRam00000001888f59c0);
              if (lVar8 != 0) {
                FUN_18672d6e0(lVar8,0);
                if (*(int *)(lRam000000018884e2e8 + 0xe0) == 0) {
                  func_0x00018048c140(lRam000000018884e2e8);
                }
                if (**(longlong **)(lRam000000018884e2e8 + 0xb8) != 0) {
                  FUN_1805072d0(**(longlong **)(lRam000000018884e2e8 + 0xb8),lVar8,
                                uRam00000001888b5590);
                  return;
                }
              }
            }
            FUN_18048c0b0();
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar6 + 0x18) != 0) {
    uVar7 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar3 = FUN_183f23b70(uVar7,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar8 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar8 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar8,uVar7,param_1,0);
        iVar4 = FUN_183f22380(uVar7,1,0,iVar3,0);
        if (iVar4 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar7,iVar3 + -1,0);
          return;
        }
        if (*(longlong *)(lVar6 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar3 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


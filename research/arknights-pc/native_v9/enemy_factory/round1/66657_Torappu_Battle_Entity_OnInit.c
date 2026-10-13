
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_OnInit_0x6010462(longlong param_1,float param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  ulonglong auStackX_8 [2];
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  ulonglong *puStack_30;
  ulonglong *puStack_28;
  undefined1 *puStack_20;
  
  if (DAT_188c908f1 == '\0') {
    uStack_40 = 0x1806f92d6;
    FUN_18048bf00(&DAT_188841368);
    DAT_188c908f1 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    uStack_40 = 0x1806f92f5;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x928);
  if (lVar1 != 0) {
    if (*(longlong *)(lVar1 + 0x18) == 0) {
      FUN_18048c0b0(lVar1,param_1,param_2,0);
      pcVar6 = (code *)swi(3);
      (*pcVar6)();
      return;
    }
    uStack_48 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    auStackX_8[0] = auStackX_8[0] & 0xffffffffffffff00;
    uStack_38 = 0;
    puStack_30 = auStackX_8;
    puStack_28 = &uStack_48;
    FUN_185ca7f50(uStack_48,auStackX_8,0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
      iVar7 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        lVar2 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
        if (lVar2 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar2,uVar3,param_1,0);
          FUN_183f22700(uVar3,(double)param_2,0);
          iVar8 = FUN_183f22380(uVar3,2,0,iVar7,0);
          if (iVar8 == 0) {
code_r0x000183650198:
            FUN_183f22fd0(uVar3,iVar7 + -1,0);
            if ((char)auStackX_8[0] != '\0') {
              func_0x000185ca7ff0(uStack_48,0);
            }
            return;
          }
          if (*(longlong *)(lVar1 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
            goto code_r0x000183650198;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar6 = (code *)swi(3);
    (*pcVar6)();
    return;
  }
  lVar1 = *(longlong *)(param_1 + 400);
  if (lVar1 == 0) {
    uStack_40 = 0x1806f9349;
    FUN_18048c0b0();
    pcVar6 = (code *)swi(3);
    (*pcVar6)();
    return;
  }
  if (cRam0000000188c90963 == '\0') {
    puStack_30 = (ulonglong *)&UNK_18071f03e;
    FUN_18048bf00(0x18889ed08,0);
    puStack_30 = (ulonglong *)&UNK_18071f04a;
    FUN_18048bf00(0x1888737d8);
    cRam0000000188c90963 = '\x01';
  }
  lVar2 = **(longlong **)(lRam00000001888737d8 + 0xb8);
  if (lVar2 == 0) {
    lVar1 = *(longlong *)(lVar1 + 0x10);
    if (lVar1 == 0) {
      puStack_30 = (ulonglong *)&UNK_18071f096;
      FUN_18048c0b0();
      pcVar6 = (code *)swi(3);
      (*pcVar6)();
      return;
    }
    iVar7 = *(int *)(lVar1 + 0x20);
    if (0 < iVar7) {
      if (*(longlong *)(lVar1 + 0x10) == 0) {
        puStack_30 = (ulonglong *)&UNK_185761152;
        FUN_18048c0b0();
        pcVar6 = (code *)swi(3);
        (*pcVar6)();
        return;
      }
      puStack_30 = (ulonglong *)&UNK_18576111f;
      System_Array_Clear_0x6000ea1
                (*(undefined8 *)(lVar1 + 0x10),0,*(undefined4 *)(*(longlong *)(lVar1 + 0x10) + 0x18)
                 ,0);
      *(undefined4 *)(lVar1 + 0x20) = 0;
      *(undefined4 *)(lVar1 + 0x28) = 0;
      *(undefined4 *)(lVar1 + 0x24) = 0xffffffff;
      puStack_30 = (ulonglong *)&UNK_18576113f;
      System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar1 + 0x18),0,iVar7,0);
    }
    *(int *)(lVar1 + 0x2c) = *(int *)(lVar1 + 0x2c) + 1;
    return;
  }
  if (*(longlong *)(lVar2 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar6 = (code *)swi(3);
    (*pcVar6)();
    return;
  }
  uVar3 = *(undefined8 *)(*(longlong *)(lVar2 + 0x18) + 0x30);
  auStackX_8[0] = auStackX_8[0] & 0xffffffffffffff00;
  puStack_30 = (ulonglong *)0x0;
  puStack_28 = auStackX_8;
  puStack_20 = &stack0x00000020;
  FUN_185ca7f50(uVar3,auStackX_8,0);
  if (*(longlong *)(lVar2 + 0x18) != 0) {
    uVar4 = *(undefined8 *)(*(longlong *)(lVar2 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar4,*(undefined4 *)(lVar2 + 0x38),*(undefined4 *)(lVar2 + 0x14),0);
    if (*(longlong *)(lVar2 + 0x18) != 0) {
      lVar5 = *(longlong *)(*(longlong *)(lVar2 + 0x18) + 0x20);
      if (lVar5 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar5,uVar4,lVar1,0);
        uStack_48 = 0;
        iVar8 = FUN_183f22380(uVar4,1,0,iVar7);
        if (iVar8 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar4,iVar7 + -1,0);
          if ((char)auStackX_8[0] != '\0') {
            func_0x000185ca7ff0(uVar3,0);
          }
          return;
        }
        if (*(longlong *)(lVar2 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar2 + 0x18),iVar7 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}


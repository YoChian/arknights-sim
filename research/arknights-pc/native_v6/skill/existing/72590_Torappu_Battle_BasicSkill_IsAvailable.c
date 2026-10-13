
/* WARNING: Removing unreachable block (ram,0x00018330f795) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 Torappu_Battle_BasicSkill_IsAvailable_0x6011b8f(longlong *param_1,undefined4 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined1 uVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  undefined4 uStack_44;
  undefined8 auStack_40 [2];
  undefined *puStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c91c03 == '\0') {
    puStack_30 = (undefined *)0x18095a4e4;
    FUN_18048bf00(&DAT_188925ba0);
    puStack_30 = (undefined *)0x18095a4f0;
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91c03 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x78);
  if (lVar1 == 0) {
    if (param_1[0x16] == 0) {
LAB_18095a5e9:
      puStack_30 = (undefined *)0x18095a5ee;
      FUN_18048c0b0();
      UNRECOVERED_JUMPTABLE = (code *)swi(3);
      uVar5 = (*UNRECOVERED_JUMPTABLE)();
      return uVar5;
    }
    if (*(int *)(param_1[0x16] + 0x40) != 0) {
      if (DAT_188ccc7f0 != '\0') {
        puStack_30 = (undefined *)0x18095a53b;
        func_0x000180446d00(*param_1);
      }
      puStack_30 = (undefined *)0x18095a551;
      cVar6 = (**(code **)(*param_1 + 0x3b0))(param_1,*(undefined8 *)(*param_1 + 0x3b8));
      if (cVar6 != '\0') {
        puStack_30 = (undefined *)0x18095a55f;
        cVar6 = Torappu_Battle_BasicSkill_get_ownerCanUseSkill_0x6011b90(param_1,0);
        if (cVar6 != '\0') {
          lVar1 = param_1[0x11];
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            puStack_30 = (undefined *)0x18095a57f;
            func_0x00018048c140();
          }
          puStack_30 = (undefined *)0x18095a58c;
          cVar6 = FUN_186b638d0(lVar1,0,0);
          if (cVar6 != '\0') {
            return 1;
          }
          plVar2 = (longlong *)param_1[0x11];
          if (plVar2 != (longlong *)0x0) {
            lVar1 = param_1[0x15];
            if (DAT_188ccc7f0 != '\0') {
              puStack_30 = &UNK_1800054a9;
              func_0x000180446d00(*plVar2);
            }
            UNRECOVERED_JUMPTABLE = *(code **)(*plVar2 + 400);
                    /* WARNING: Could not recover jumptable at 0x0001800054d1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            uVar5 = (*UNRECOVERED_JUMPTABLE)
                              (plVar2,lVar1,*(undefined8 *)(*plVar2 + 0x198),UNRECOVERED_JUMPTABLE);
            return uVar5;
          }
          goto LAB_18095a5e9;
        }
      }
    }
    return 0;
  }
  if (cRam0000000188cafc31 == '\0') {
    FUN_18048bf00(0x18880c778,param_1,param_2,0);
    cRam0000000188cafc31 = '\x01';
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x00018330f7ec:
    FUN_18048c0b0();
code_r0x00018330f7f2:
    FUN_18048c0b0();
  }
  else {
    auStack_40[0] = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30);
    puStack_30 = (undefined *)0x0;
    puStack_28 = &stack0x00000008;
    puStack_20 = auStack_40;
    FUN_185ca7f50(auStack_40[0],&stack0x00000008,0);
    if (*(longlong *)(lVar1 + 0x18) == 0) goto code_r0x00018330f7fc;
    uVar3 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar7 = FUN_183f23b70(uVar3,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar4 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar4 == 0) goto code_r0x00018330f7ec;
      FUN_183cf8c20(lVar4,uVar3,param_1,0);
      uStack_44 = param_2;
      uVar9 = func_0x00018048b9c0(uRam000000018880c778,&uStack_44);
      FUN_183cfbf40(lVar4,uVar3,uVar9,0);
      iVar8 = FUN_183f22380(uVar3,2,1,iVar7,0);
      if (iVar8 == 0) {
code_r0x00018330f768:
        uVar5 = FUN_183f23100(uVar3,iVar7 + 1,0);
        FUN_183f22fd0(uVar3,iVar7 + -1,0);
        return uVar5;
      }
      if (*(longlong *)(lVar1 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar7 + -1,0);
        goto code_r0x00018330f768;
      }
      goto code_r0x00018330f7f2;
    }
  }
  FUN_18048c0b0();
code_r0x00018330f7fc:
  FUN_18048c0b0();
  FUN_180472d50();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  uVar5 = (*UNRECOVERED_JUMPTABLE)();
  return uVar5;
}


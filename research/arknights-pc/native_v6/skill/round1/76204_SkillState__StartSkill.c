
/* WARNING: Removing unreachable block (ram,0x0001832b3a24) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong SkillState__StartSkill_0x60129ad(undefined8 param_1)

{
  code *pcVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  longlong lVar10;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c9279b == '\0') {
    puStack_30 = (undefined1 *)0x180a83d4e;
    FUN_18048bf00(&DAT_1888a0c38);
    puStack_30 = (undefined1 *)0x180a83d5a;
    FUN_18048bf00(&DAT_188878850);
    puStack_30 = (undefined1 *)0x180a83d66;
    FUN_18048bf00(&DAT_188956960);
    puStack_30 = (undefined1 *)0x180a83d72;
    FUN_18048bf00(&DAT_18881da70);
    puStack_30 = (undefined1 *)0x180a83d7e;
    FUN_18048bf00(&DAT_1888e6118);
    DAT_188c9279b = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188878850 + 0xb8) + 0x18);
  if (lVar6 == 0) {
    puStack_30 = (undefined1 *)0x180a83dbb;
    lVar6 = func_0x00018045cfe0(_DAT_1888e6118);
    if (lVar6 != 0) {
      puStack_30 = (undefined1 *)0x180a83dd1;
      func_0x00018050cf60(lVar6,0);
      *(undefined8 *)(lVar6 + 0x10) = param_1;
      puStack_30 = (undefined1 *)0x180a83de1;
      func_0x00018048b9e0(lVar6 + 0x10,param_1);
      puStack_30 = (undefined1 *)0x180a83df0;
      lVar7 = FUN_18536e540(param_1,_DAT_188956960);
      if (lVar7 != 0) {
        puStack_30 = (undefined1 *)0x180a83e03;
        uVar8 = Torappu_Battle_Character_get_skill_0x601284d(lVar7,0);
        *(undefined8 *)(lVar6 + 0x18) = uVar8;
        puStack_30 = (undefined1 *)0x180a83e13;
        func_0x00018048b9e0(lVar6 + 0x18,uVar8);
        puStack_30 = (undefined1 *)0x180a83e22;
        lVar7 = FUN_18536e540(param_1,_DAT_188956960);
        if (lVar7 != 0) {
          puStack_30 = (undefined1 *)0x180a83e3a;
          uVar9 = Torappu_Battle_Character_OnBeforeSkill_0x6012909
                            (lVar7,*(undefined8 *)(lVar6 + 0x18),0);
          if ((char)uVar9 == '\0') {
LAB_180a83ede:
            return uVar9 & 0xffffffffffffff00;
          }
          if (*(longlong *)(lVar6 + 0x18) != 0) {
            puStack_30 = (undefined1 *)0x180a83e56;
            uVar8 = Torappu_Battle_BasicSkill_get_escapeTime_0x6011bca
                              (*(longlong *)(lVar6 + 0x18),0);
            lVar7 = *(longlong *)(lVar6 + 0x18);
            *(undefined8 *)(lVar6 + 0x20) = uVar8;
            puStack_30 = (undefined1 *)0x180a83e6a;
            lVar10 = func_0x00018045cfe0(_DAT_1888a0c38);
            if (lVar10 != 0) {
              puStack_30 = (undefined1 *)0x180a83e8b;
              FinishCallbackDelegate__ctor_0x600f688(lVar10,lVar6,_DAT_18881da70,0);
              if (*(longlong *)(lVar6 + 0x18) != 0) {
                puStack_30 = (undefined1 *)0x180a83e9b;
                uVar3 = Torappu_Battle_BasicSkill_get_cachedOperationSide_0x6011ba2
                                  (*(longlong *)(lVar6 + 0x18),0);
                if (lVar7 != 0) {
                  puStack_30 = (undefined1 *)0x180a83eb1;
                  uVar9 = Torappu_Battle_BasicSkill_Cast_0x6011bd8(lVar7,lVar10,uVar3,0);
                  if ((char)uVar9 != '\0') {
                    return uVar9;
                  }
                  puStack_30 = (undefined1 *)0x180a83ec4;
                  lVar7 = FUN_18536e540(param_1,_DAT_188956960);
                  if (lVar7 != 0) {
                    puStack_30 = (undefined1 *)0x180a83ede;
                    uVar9 = Torappu_Battle_Character_OnAfterSkill_0x601290a
                                      (lVar7,*(undefined8 *)(lVar6 + 0x18),1,0);
                    goto LAB_180a83ede;
                  }
                }
              }
            }
          }
        }
      }
    }
    puStack_30 = (undefined1 *)0x180a83f0a;
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    uVar9 = (*pcVar1)();
    return uVar9;
  }
  if (*(longlong *)(lVar6 + 0x18) == 0) {
    FUN_18048c0b0();
code_r0x0001832b3a74:
    FUN_18048c0b0();
code_r0x0001832b3a7a:
    FUN_18048c0b0();
  }
  else {
    auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
    uStack_38 = 0;
    puStack_30 = &stack0x00000008;
    puStack_28 = auStack_48;
    FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
    if (*(longlong *)(lVar6 + 0x18) == 0) goto code_r0x0001832b3a84;
    uVar8 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
    iVar4 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      lVar7 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
      if (lVar7 == 0) goto code_r0x0001832b3a74;
      FUN_183cf8c20(lVar7,uVar8,param_1,0);
      iVar5 = FUN_183f22380(uVar8,1,1,iVar4,0);
      if (iVar5 == 0) {
code_r0x0001832b39f4:
        bVar2 = FUN_183f23100(uVar8,iVar4 + 1,0);
        FUN_183f22fd0(uVar8,iVar4 + -1,0);
        return (ulonglong)bVar2;
      }
      if (*(longlong *)(lVar6 + 0x18) != 0) {
        FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
        goto code_r0x0001832b39f4;
      }
      goto code_r0x0001832b3a7a;
    }
  }
  FUN_18048c0b0();
code_r0x0001832b3a84:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar1 = (code *)swi(3);
  uVar9 = (*pcVar1)();
  return uVar9;
}


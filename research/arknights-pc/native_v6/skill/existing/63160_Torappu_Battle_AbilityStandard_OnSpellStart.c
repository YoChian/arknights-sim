
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong Torappu_Battle_AbilityStandard_OnSpellStart_0x600f6b9(longlong *param_1)

{
  code *pcVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  undefined4 auStackX_18 [2];
  longlong lStack_68;
  longlong lStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 auStack_38 [32];
  
  if (DAT_188c8fd37 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_18896b108);
    FUN_18048bf00(&DAT_18891e0d8);
    FUN_18048bf00(&DAT_18891e318);
    FUN_18048bf00(&DAT_188920050);
    FUN_18048bf00(&DAT_188920710);
    FUN_18048bf00(0x18885a5b8);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1889312e8);
    FUN_18048bf00(&DAT_18892ea68);
    DAT_188c8fd37 = '\x01';
  }
  uVar12 = 0;
  auStackX_18[0] = 0;
  lStack_68 = 0;
  lStack_60 = 0;
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x118);
  if (lVar8 != 0) {
    uVar14 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar8,param_1,0);
    return uVar14;
  }
  uStack_58 = (undefined4)param_1[10];
  uStack_54 = *(undefined4 *)((longlong)param_1 + 0x54);
  uStack_50 = (undefined4)param_1[0xb];
  uStack_4c = *(undefined4 *)((longlong)param_1 + 0x5c);
  cVar2 = FUN_18449ae30(&uStack_58,(char)param_1[0x1a],_DAT_18896b108);
  if (cVar2 == '\0') {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*param_1);
    }
    uVar14 = (**(code **)(*param_1 + 0x530))(param_1,2,0,*(undefined8 *)(*param_1 + 0x538));
    return uVar14 & 0xffffffffffffff00;
  }
  plVar7 = (longlong *)FUN_185159d80(param_1 + 10,_DAT_1889355a8);
  if (plVar7 != (longlong *)0x0) {
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar7);
    }
    cVar2 = (**(code **)(*plVar7 + 0x9c0))
                      (plVar7,param_1,auStackX_18,*(undefined8 *)(*plVar7 + 0x9c8));
    if (cVar2 == '\0') {
      uVar14 = FUN_18000d950(0x3f,param_1,auStackX_18[0],0);
      return uVar14 & 0xffffffffffffff00;
    }
    lVar8 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
    if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x28) != 0)) {
      FUN_185367f40(*(longlong *)(lVar8 + 0x28),param_1,_DAT_18892ea68);
      lVar8 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
      if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x10) != 0)) {
        FUN_185733520(*(longlong *)(lVar8 + 0x10),plVar7,_DAT_18891e318);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        uVar9 = (**(code **)(*param_1 + 0x410))(param_1,*(undefined8 *)(*param_1 + 0x418));
        if (DAT_188c8fcf9 == '\0') {
          FUN_18048bf00(&DAT_1889733f0);
          FUN_18048bf00(&DAT_188932ce8);
          DAT_188c8fcf9 = '\x01';
        }
        lVar8 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x1f0);
        if (lVar8 == 0) {
          uVar10 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          cVar2 = FUN_186b638d0(uVar10,0,0);
          if (cVar2 == '\0') {
            lVar8 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
            if (DAT_188c8fcc0 == '\0') {
              FUN_18048bf00(&DAT_1889733f0);
              DAT_188c8fcc0 = '\x01';
            }
            lVar11 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x28);
            if (lVar11 == 0) {
              if (DAT_188c8fcdb == '\0') {
                FUN_18048bf00(&DAT_1889733f0);
                DAT_188c8fcdb = '\x01';
              }
              lVar11 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x100);
              if (lVar11 == 0) {
                uVar5 = *(undefined4 *)((longlong)param_1 + 0xb4);
              }
              else {
                lVar11 = XLua_DelegateBridge___Gen_Delegate_Imp2637_0x60014ad
                                   (auStack_38,lVar11,param_1,0);
                uVar5 = *(undefined4 *)(lVar11 + 0x1c);
              }
            }
            else {
              uVar5 = XLua_DelegateBridge___Gen_Delegate_Imp2627_0x60014a3(lVar11,param_1,0);
            }
            if (lVar8 == 0) goto LAB_1805d2a13;
            uVar12 = Torappu_Battle_Entity_GetAbilityAttachments_0x6010431(lVar8,uVar5,0);
          }
        }
        else {
          uVar12 = XLua_DelegateBridge___Gen_Delegate_Imp2645_0x60014b5(lVar8,param_1,0);
        }
        uVar10 = FUN_1800053c0(0x4b,param_1,4);
        Torappu_Battle_AbilityStandard_OnEvent_0x600f6ad(param_1,4,0,0);
        if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        cVar2 = FUN_186b63a70(plVar7,0,0);
        if (cVar2 != '\0') {
          lVar8 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
          if (lVar8 == 0) goto LAB_1805d2a13;
          lStack_68 = param_1[0x1d];
          lStack_60 = param_1[0x1e];
          lVar8 = *(longlong *)(lVar8 + 0x50);
          uVar13 = FUN_185159d80(&lStack_68,_DAT_1889355a8);
          if (lVar8 == 0) goto LAB_1805d2a13;
          FUN_185367f40(lVar8,uVar13,_DAT_1889312e8);
          Torappu_Battle_Entity_OnAbilitySpellOn_0x6010488(plVar7,param_1,0);
          lVar8 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
          if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x50) == 0)) goto LAB_1805d2a13;
          FUN_185733a00(*(longlong *)(lVar8 + 0x50),_DAT_188920710);
        }
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        cVar2 = (**(code **)(*param_1 + 0x5b0))(param_1,*(undefined8 *)(*param_1 + 0x5b8));
        if ((cVar2 == '\0') ||
           (iVar6 = Torappu_Battle_AbilityStandard_get_spellCnt_0x600f69b(param_1,0), iVar6 == 0)) {
          FUN_180005610(0x5e,param_1);
        }
        cVar2 = FUN_18000d9c0(0x58,param_1,uVar10,uVar9,uVar12);
        if ((char)param_1[0x21] != '\0') {
          if (((cVar2 != '\0') || (cVar3 = FUN_180005610(0x12,param_1), cVar3 != '\0')) &&
             (iVar6 = Torappu_Battle_AbilityStandard_get_spellCnt_0x600f69b(param_1,0), iVar6 == 0))
          {
            FUN_180005610(0x61,param_1);
          }
          if (((char)param_1[0x21] != '\0') &&
             ((cVar2 != '\0' || (cVar3 = FUN_180005610(0x12,param_1), cVar3 != '\0')))) {
            if (DAT_188c8fd52 == '\0') {
              FUN_18048bf00(&DAT_188974cb0);
              FUN_18048bf00(&DAT_188932ce8);
              DAT_188c8fd52 = '\x01';
            }
            lVar8 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x1f0);
            if (lVar8 == 0) {
              uVar13 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
              if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              cVar3 = FUN_186b63a70(uVar13,0,0);
              if (cVar3 != '\0') {
                lVar8 = Torappu_Battle_Ability_get_owner_0x600f630(param_1,0);
                if (lVar8 == 0) goto LAB_1805d2a13;
                Torappu_Battle_Entity_OnOutputAttackOrHealEachSpell_0x601047b(lVar8,param_1,0);
              }
            }
            else {
              XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar8,param_1,0);
            }
          }
        }
        bVar4 = 1;
        if (cVar2 == '\0') {
          bVar4 = FUN_18000d9c0(0x52,param_1,uVar10,uVar9,uVar12);
        }
        lVar8 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
        if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x10) != 0)) {
          FUN_185733450(*(longlong *)(lVar8 + 0x10),_DAT_18891e0d8);
          lVar8 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
          if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x28) != 0)) {
            FUN_185733a00(*(longlong *)(lVar8 + 0x28),_DAT_188920050);
            return (ulonglong)bVar4;
          }
        }
      }
    }
  }
LAB_1805d2a13:
  FUN_18048c0b0();
  pcVar1 = (code *)swi(3);
  uVar14 = (*pcVar1)();
  return uVar14;
}


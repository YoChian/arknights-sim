
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_OnCastOnTarget_0x600f6b4
               (longlong *param_1,longlong param_2,undefined8 param_3,longlong param_4,
               undefined8 param_5)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  uint uVar9;
  longlong lVar10;
  uint uVar11;
  undefined8 uStack_68;
  longlong lStack_60;
  longlong lStack_58;
  longlong lStack_50;
  undefined8 uStack_48;
  longlong lStack_40;
  
  if (DAT_188c8fd34 == '\0') {
    FUN_18048bf00(&DAT_188974cb0);
    FUN_18048bf00(&DAT_18891e0d8);
    FUN_18048bf00(&DAT_18891e318);
    FUN_18048bf00(&DAT_188920710);
    FUN_18048bf00(&DAT_188899430);
    FUN_18048bf00(&DAT_1888f11e0);
    FUN_18048bf00(0x18885a5b8);
    FUN_18048bf00(&DAT_1889355a8);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1889312e8);
    DAT_188c8fd34 = '\x01';
  }
  lStack_58 = 0;
  lStack_50 = 0;
  uStack_68 = 0;
  lStack_60 = 0;
  lVar5 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x100);
  if (lVar5 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp442_0x6000c1a
              (lVar5,param_1,param_2,param_3,param_4,param_5,0);
    return;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  cVar3 = (**(code **)(*param_1 + 0x5c0))(param_1,*(undefined8 *)(*param_1 + 0x5c8));
  if (cVar3 != '\0') {
    if (DAT_188c8fd1d == '\0') {
      FUN_18048bf00(&DAT_188974cb0);
      DAT_188c8fd1d = '\x01';
    }
    lVar5 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x40);
    if (lVar5 == 0) {
      iVar4 = (int)param_1[0x22];
    }
    else {
      iVar4 = XLua_DelegateBridge___Gen_Delegate_Imp54_0x6000a96(lVar5,param_1,0);
    }
    if (iVar4 != 0) goto LAB_1805d1146;
  }
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*param_1);
  }
  (**(code **)(*param_1 + 0x740))(param_1,param_2,*(undefined8 *)(*param_1 + 0x748));
LAB_1805d1146:
  lVar5 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
  if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x18) != 0)) {
    FUN_185733520(*(longlong *)(lVar5 + 0x18),param_2,_DAT_18891e318);
    lVar5 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
    if (lVar5 != 0) {
      lStack_58 = param_1[0x1d];
      lStack_50 = param_1[0x1e];
      lVar5 = *(longlong *)(lVar5 + 0x50);
      uVar6 = FUN_185159d80(&lStack_58,_DAT_1889355a8);
      if (lVar5 != 0) {
        FUN_185367f40(lVar5,uVar6,_DAT_1889312e8);
        uVar6 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
        if (DAT_188c8fcc1 == '\0') {
          FUN_18048bf00(&DAT_1889733f0);
          DAT_188c8fcc1 = '\x01';
        }
        lVar5 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x30);
        if (lVar5 == 0) {
          lVar5 = param_1[0x11];
        }
        else {
          lVar5 = XLua_DelegateBridge___Gen_Delegate_Imp931_0x6000e03(lVar5,param_1,0);
        }
        uVar9 = 0;
        Torappu_Battle_AbilityAttachment_Apply_0x600f68f(param_5,param_2,uVar6,param_1,lVar5,0);
        if (param_4 != 0) {
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*param_1);
          }
          cVar3 = (**(code **)(*param_1 + 0x6b0))
                            (param_1,param_2,param_4,*(undefined8 *)(*param_1 + 0x6b8));
          uVar11 = uVar9;
          if (cVar3 != '\0') {
            for (; iVar4 = FUN_180005310(0,_DAT_188899430,param_4), (int)uVar11 < iVar4;
                uVar11 = uVar11 + 1) {
              uVar6 = FUN_180004e80(0,_DAT_1888f11e0,param_4,uVar11);
              cVar3 = Torappu_Battle_BuffDBUtil_TryGetBuff_0x60131c1(uVar6,&uStack_68,0);
              if (cVar3 == '\0') {
                uVar6 = func_0x00018048bf20(0x188932918);
                uVar7 = func_0x00018048ba50(uVar6,5);
                FUN_180005cb0(uVar7);
                uVar6 = func_0x00018048bf20(0x1887f7b10);
                FUN_180005fe0(uVar7,0,uVar6);
                FUN_180005cb0(param_4);
                uVar6 = func_0x00018048bf20(&DAT_1888f11e0);
                lVar5 = FUN_180004e80(0,uVar6,param_4,uVar11);
                FUN_180005cb0(lVar5);
                uVar6 = *(undefined8 *)(lVar5 + 0x18);
                FUN_180005cb0(uVar7);
                FUN_180005fe0(uVar7,1,uVar6);
                FUN_180005cb0(uVar7);
                uVar6 = func_0x00018048bf20(0x18890e300);
                FUN_180005fe0(uVar7,2,uVar6);
                FUN_180005cb0(param_4);
                uVar6 = func_0x00018048bf20(&DAT_1888f11e0);
                lVar5 = FUN_180004e80(0,uVar6,param_4,uVar11);
                FUN_180005cb0(lVar5);
                uVar6 = *(undefined8 *)(lVar5 + 0x30);
                FUN_180005cb0(uVar7);
                FUN_180005fe0(uVar7,3,uVar6);
                FUN_180005cb0(uVar7);
                uVar6 = func_0x00018048bf20(0x18890e540);
                FUN_180005fe0(uVar7,4,uVar6);
                uVar6 = System_String_Concat_0x600030b(uVar7,0);
                uVar7 = func_0x00018048bf20(0x1888ac650);
                uVar7 = func_0x00018045cfe0(uVar7);
                FUN_180005cb0(uVar7);
                Torappu_GameDataException__ctor_0x6005758(uVar7,uVar6,0);
                uVar6 = func_0x00018048bf20(0x18893aa68);
                FUN_18048c070(uVar7,uVar6);
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              cVar3 = Torappu_Battle_Ability_get_damageMissFlag_0x600f64a(param_1,0);
              lVar5 = lStack_60;
              uVar6 = uStack_68;
              if (cVar3 == '\0') {
LAB_1805d130b:
                uVar7 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
                uVar8 = Torappu_Battle_Ability_get_blackboard_0x600f62a(param_1,0);
                if (param_2 == 0) goto LAB_1805d169e;
                uStack_48 = uVar6;
                lStack_40 = lVar5;
                Torappu_Battle_Entity_AddBuff_0x60103f1
                          (param_2,&uStack_48,uVar7,param_1,uVar8,0,0,0,0);
              }
              else {
                if (lStack_60 == 0) goto LAB_1805d169e;
                if (*(char *)(lStack_60 + 0x22) == '\0') goto LAB_1805d130b;
              }
            }
          }
        }
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        (**(code **)(*param_1 + 0x610))(param_1,param_2,param_3,*(undefined8 *)(*param_1 + 0x618));
        lVar5 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
        if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x50) != 0)) {
          FUN_185733a00(*(longlong *)(lVar5 + 0x50),_DAT_188920710);
          lVar5 = Torappu_Battle_Ability_get_context_0x600f631(param_1,0);
          if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x18) != 0)) {
            FUN_185733450(*(longlong *)(lVar5 + 0x18),_DAT_18891e0d8);
            lVar5 = param_1[0x20];
            if (lVar5 != 0) {
              lVar10 = 0x20;
              do {
                if (*(int *)(lVar5 + 0x18) <= (int)uVar9) {
                  lVar5 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
                  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
                    func_0x00018048c140();
                  }
                  cVar3 = FUN_186b63a70(lVar5,0,0);
                  if (cVar3 == '\0') {
                    return;
                  }
                  if (lVar5 != 0) {
                    Torappu_Battle_Entity_OnAbilityCastOnTarget_0x6010489(lVar5,param_1,param_2,0);
                    return;
                  }
                  break;
                }
                lVar5 = param_1[0x20];
                if (lVar5 == 0) break;
                if (*(uint *)(lVar5 + 0x18) <= uVar9) {
                  FUN_18048c0a0();
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                plVar1 = *(longlong **)(lVar5 + lVar10);
                if (plVar1 == (longlong *)0x0) break;
                if (DAT_188ccc7f0 != '\0') {
                  func_0x000180446d00(*plVar1);
                }
                (**(code **)(*plVar1 + 0x1f0))(plVar1,param_2);
                lVar5 = param_1[0x20];
                uVar9 = uVar9 + 1;
                lVar10 = lVar10 + 8;
              } while (lVar5 != 0);
            }
          }
        }
      }
    }
  }
LAB_1805d169e:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


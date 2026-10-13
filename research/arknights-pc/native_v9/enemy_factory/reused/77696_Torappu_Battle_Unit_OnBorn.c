
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Unit_OnBorn_0x6012f81(longlong param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  undefined1 *puVar4;
  char cVar5;
  int iVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  longlong lVar9;
  ushort uVar10;
  int iVar11;
  uint uVar12;
  longlong lVar13;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 auStack_40 [16];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined1 *puStack_20;
  
  if (DAT_188c92c02 == '\0') {
    uStack_50 = 0x180aca0ae;
    FUN_18048bf00(&DAT_1888d3908);
    uStack_50 = 0x180aca0ba;
    FUN_18048bf00(&DAT_188805040);
    DAT_188c92c02 = '\x01';
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x440);
  if (lVar9 == 0) {
    uStack_50 = 0x180aca107;
    Torappu_Battle_Entity_OnBorn_0x6010458(param_1,0);
    uStack_50 = 0x180aca113;
    lVar9 = FUN_185337c50(_DAT_1888d3908);
    if (lVar9 != 0) {
      uStack_50 = 0x180aca12a;
      Torappu_Battle_BattleController_RegisterUnit_0x600fca1(lVar9,param_1,0);
      if (DAT_188c92be8 == '\0') {
        uStack_50 = 0x180aca13f;
        FUN_18048bf00(&DAT_1888746f8);
        uStack_50 = 0x180aca14b;
        FUN_18048bf00(&DAT_188932ce8);
        uStack_50 = 0x180aca157;
        FUN_18048bf00(&DAT_188805040);
        DAT_188c92be8 = '\x01';
      }
      iVar11 = 0;
      lVar9 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x370);
      if (lVar9 == 0) {
        uVar12 = 0;
        uStack_50 = 0x180aca194;
        iVar6 = FUN_1844afc00(*(undefined8 *)(param_1 + 0x1a8),_DAT_1888746f8);
        if (0 < iVar6) {
          lVar9 = 0;
          lVar13 = 0x20;
          do {
            lVar1 = *(longlong *)(param_1 + 0x1a8);
            if (lVar1 == 0) goto LAB_180aca3ad;
            if (*(uint *)(lVar1 + 0x18) <= uVar12) {
              uStack_50 = 0x180aca3ac;
              FUN_18048c0a0();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            lVar1 = *(longlong *)(lVar13 + lVar1);
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              uStack_50 = 0x180aca1e2;
              func_0x00018048c140();
            }
            uStack_50 = 0x180aca1ef;
            cVar5 = FUN_186b63a70(lVar1,0,0);
            if (cVar5 != '\0') {
              if (lVar1 == 0) goto LAB_180aca3ad;
              uStack_50 = 0x180aca20a;
              Torappu_Battle_Ability_Attach_0x600f653(lVar1);
            }
            uVar12 = uVar12 + 1;
            lVar9 = lVar9 + 1;
            lVar13 = lVar13 + 8;
          } while (lVar9 < iVar6);
        }
      }
      else {
        uStack_50 = 0x180aca226;
        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar9,param_1,0);
      }
      if (DAT_188c92bea == '\0') {
        uStack_50 = 0x180aca23b;
        FUN_18048bf00(&DAT_18884e338);
        uStack_50 = 0x180aca247;
        FUN_18048bf00(0x1888ccb70);
        uStack_50 = 0x180aca253;
        FUN_18048bf00(&DAT_1888407b8);
        uStack_50 = 0x180aca25f;
        FUN_18048bf00(&DAT_188932ce8);
        uStack_50 = 0x180aca26b;
        FUN_18048bf00(&DAT_188805040);
        DAT_188c92bea = '\x01';
      }
      lVar9 = *(longlong *)(*(longlong *)(_DAT_188805040 + 0xb8) + 0x380);
      if (lVar9 == 0) {
        uStack_50 = 0x180aca2a3;
        iVar6 = FUN_1844afc00(*(undefined8 *)(param_1 + 0x278),_DAT_18884e338);
        if (0 < iVar6) {
          do {
            if (*(longlong *)(param_1 + 0x278) == 0) goto LAB_180aca3ad;
            uStack_50 = 0x180aca2d4;
            FUN_184ad2ef0(&puStack_28,*(longlong *)(param_1 + 0x278),iVar11,_DAT_1888407b8);
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              uStack_50 = 0x180aca2e9;
              func_0x00018048c140();
            }
            puVar4 = puStack_28;
            uStack_50 = 0x180aca2fb;
            cVar5 = FUN_186b63a70(puStack_28,0,0);
            if (cVar5 != '\0') {
              if (puVar4 == (undefined1 *)0x0) goto LAB_180aca3ad;
              uStack_50 = 0x180aca316;
              Torappu_Battle_Ability_Attach_0x600f653(puVar4,param_1,0);
            }
            iVar11 = iVar11 + 1;
            uStack_50 = 0x180aca32b;
            iVar6 = FUN_1844afc00(*(undefined8 *)(param_1 + 0x278),_DAT_18884e338);
          } while (iVar11 < iVar6);
        }
      }
      else {
        uStack_50 = 0x180aca33c;
        XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar9,param_1,0);
      }
      uStack_50 = 0x180aca348;
      lVar9 = FUN_185337c50(_DAT_1888d3908);
      if (lVar9 != 0) {
        uStack_50 = 0x180aca35b;
        Torappu_Battle_BattleController_OnUnitBorn_0x600fcfc(lVar9,param_1,0);
        uStack_50 = 0x180aca365;
        lVar9 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
        if (lVar9 != 0) {
          if (cRam0000000188c903de == '\0') {
            FUN_18048bf00(0x1888d5250,0);
            FUN_18048bf00(0x18882b720);
            FUN_18048bf00(0x188954c98);
            FUN_18048bf00(0x1888cfcb0);
            FUN_18048bf00(0x188959b58);
            FUN_18048bf00(0x1889316a8);
            cRam0000000188c903de = '\x01';
          }
          uStack_50 = 0;
          uStack_48 = 0;
          lVar13 = *(longlong *)(*(longlong *)(lRam00000001888d5250 + 0xb8) + 0x228);
          if (lVar13 != 0) {
            XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar13,lVar9,0);
            return;
          }
          if (*(longlong *)(lVar9 + 0x18) == 0) {
            FUN_18048c0b0();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          plVar7 = (longlong *)FUN_185a17960(*(longlong *)(lVar9 + 0x18),uRam000000018882b720);
          do {
            if (plVar7 == (longlong *)0x0) {
code_r0x000180676a08:
              FUN_18048c0b0();
              FUN_180472d50();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            cVar5 = FUN_180005310(0,uRam0000000188959b58);
            lVar13 = lRam00000001888cfcb0;
            if (cVar5 == '\0') {
              if (plVar7 != (longlong *)0x0) {
                FUN_180005310(0,uRam0000000188954c98,plVar7);
              }
              FUN_18067e5b0(lVar9,0);
              return;
            }
            if (plVar7 == (longlong *)0x0) {
              FUN_18048c0b0();
              goto code_r0x000180676a08;
            }
            lVar1 = *plVar7;
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(lVar1);
            }
            uVar10 = 0;
            if (*(ushort *)(lVar1 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar13)
                {
                  puVar8 = (undefined8 *)
                           (((longlong)
                             *(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) +
                            0x14) * 0x10 + lVar1);
                  goto code_r0x000180676935;
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 < *(ushort *)(lVar1 + 0x12e));
            }
            puVar8 = (undefined8 *)FUN_180445cc0(plVar7,lVar13,0);
code_r0x000180676935:
            puVar8 = (undefined8 *)(*(code *)*puVar8)(auStack_40,plVar7,puVar8[1]);
            uStack_50 = *puVar8;
            uStack_48 = puVar8[1];
            lVar13 = FUN_185159d80(&uStack_50,uRam00000001889316a8);
            if (lVar13 != 0) {
              FUN_180686740(lVar13,0);
            }
          } while( true );
        }
      }
    }
LAB_180aca3ad:
    uStack_50 = 0x180aca3b2;
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
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &stack0x00000020;
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar9 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
    iVar11 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
    if (*(longlong *)(lVar9 + 0x18) != 0) {
      lVar13 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
      if (lVar13 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar13,uVar2,param_1,0);
        uStack_48 = 0;
        iVar6 = FUN_183f22380(uVar2,1,0,iVar11);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          FUN_183f22fd0(uVar2,iVar11 + -1,0);
          return;
        }
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar11 + -1,0);
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


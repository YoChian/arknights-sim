
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnSkillEnd_0x6011bdc(longlong param_1)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  undefined4 uVar12;
  ulonglong uVar13;
  ulonglong uVar14;
  bool bVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined8 uStackX_20;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c91c4f == '\0') {
    FUN_18048bf00(&DAT_18895c720);
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18896a750);
    FUN_18048bf00(&DAT_1888797f0);
    FUN_18048bf00(&DAT_188819e20);
    FUN_18048bf00(&DAT_188932ce8);
    FUN_18048bf00(&DAT_1887f8f48);
    DAT_188c91c4f = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x2d8);
  if (lVar6 != 0) {
    if (*(longlong *)(lVar6 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uStackX_20 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x30);
    uStack_30 = 0;
    puStack_28 = &stack0x00000008;
    puStack_20 = &uStackX_20;
    FUN_185ca7f50(uStackX_20,&stack0x00000008,0);
    if (*(longlong *)(lVar6 + 0x18) != 0) {
      uVar8 = *(undefined8 *)(*(longlong *)(lVar6 + 0x18) + 0x10);
      iVar4 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar6 + 0x38),*(undefined4 *)(lVar6 + 0x14),0);
      if (*(longlong *)(lVar6 + 0x18) != 0) {
        lVar7 = *(longlong *)(*(longlong *)(lVar6 + 0x18) + 0x20);
        if (lVar7 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar7,uVar8,param_1,0);
          uStack_48 = 0;
          iVar5 = FUN_183f22380(uVar8,1,0,iVar4);
          if (iVar5 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar8,iVar4 + -1,0);
            return;
          }
          if (*(longlong *)(lVar6 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar6 + 0x18),iVar4 + -1,0);
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
  bVar15 = DAT_188c91c3d == '\0';
  *(undefined1 *)(param_1 + 0x98) = 0;
  *(undefined1 *)(param_1 + 0x9a) = 0;
  if (bVar15) {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c3d = '\x01';
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
  if (lVar6 == 0) {
    uVar8 = *(undefined8 *)(param_1 + 0xa8);
  }
  else {
    uVar8 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar6,param_1,0);
  }
  if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  cVar3 = FUN_186b63a70(uVar8,0,0);
  uVar13 = 0;
  if (cVar3 != '\0') {
    if (*(char *)(param_1 + 0x59) != '\0') {
      lVar6 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (lVar6 == 0) goto LAB_18095c9fa;
      lVar6 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar6,0);
      lVar7 = func_0x00018045cfe0(_DAT_1888797f0);
      if ((lVar7 == 0) ||
         (LuaMsgHandlerCallback__ctor_0x601b9cb(lVar7,param_1,_DAT_18895c720,0), lVar6 == 0))
      goto LAB_18095c9fa;
      FUN_1848dcbf0(lVar6,0x14,lVar7,_DAT_188819e20);
    }
    if (*(char *)(param_1 + 0x99) == '\0') {
      lVar6 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (lVar6 == 0) {
LAB_18095c9fa:
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      Torappu_Battle_Character_OnSkillFinish_0x601290f(lVar6,0);
      uVar8 = Torappu_Battle_BasicSkill_get_data_0x6011bc1(param_1,0);
      uVar8 = Torappu_Battle_BasicSkill__GenerateSignalId_0x6011c03(param_1,uVar8,0);
      uVar9 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar3 = FUN_186b63a70(uVar9,0,0);
      uVar9 = _DAT_1887f8f48;
      if (cVar3 == '\0') {
        if (DAT_188c8f5b6 == '\0') {
          FUN_18048bf00(&DAT_188829ff0);
          DAT_188c8f5b6 = '\x01';
        }
        uVar11 = **(undefined8 **)(_DAT_188829ff0 + 0xb8);
        uVar16 = (undefined4)uVar11;
        uVar17 = (undefined4)((ulonglong)uVar11 >> 0x20);
        uVar12 = *(undefined4 *)(*(undefined8 **)(_DAT_188829ff0 + 0xb8) + 1);
      }
      else {
        if (DAT_188c91c3d == '\0') {
          FUN_18048bf00(&DAT_188925ba0);
          DAT_188c91c3d = '\x01';
        }
        lVar6 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
        if (lVar6 == 0) {
          lVar6 = *(longlong *)(param_1 + 0xa8);
        }
        else {
          lVar6 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar6,param_1,0);
        }
        if (lVar6 == 0) goto LAB_18095c9fa;
        puVar10 = (undefined8 *)
                  Torappu_Battle_VisualObject_get_worldPosition_0x601302d(&uStack_58,lVar6,0);
        uVar16 = (undefined4)*puVar10;
        uVar17 = (undefined4)((ulonglong)*puVar10 >> 0x20);
        uVar12 = *(undefined4 *)(puVar10 + 1);
      }
      uVar11 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      uStack_58 = CONCAT44(uVar17,uVar16);
      uStack_50 = CONCAT44(uStack_50._4_4_,uVar12);
      Torappu_Battle_BattleController_PlayAudioAtPos_0x600fce5(uVar9,uVar8,&uStack_58,uVar11,0);
    }
  }
  if (DAT_188c91c68 == '\0') {
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(0x1888e0138);
    FUN_18048bf00(0x1888e0a38);
    FUN_18048bf00(&DAT_1888e0c78);
    FUN_18048bf00(&DAT_188933868);
    FUN_18048bf00(&DAT_188933aa8);
    DAT_188c91c68 = '\x01';
  }
  uStack_58 = 0;
  uStack_50 = 0;
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x3a8);
  if (lVar6 == 0) {
    lVar6 = *(longlong *)(param_1 + 0xd0);
    uVar14 = uVar13;
    do {
      if (lVar6 == 0) {
LAB_18095c9ee:
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      lVar7 = *(longlong *)(param_1 + 0xd0);
      if (*(int *)(lVar6 + 0x18) <= (int)uVar14) {
        if (lVar7 != 0) {
          iVar4 = *(int *)(lVar7 + 0x18);
          *(int *)(lVar7 + 0x1c) = *(int *)(lVar7 + 0x1c) + 1;
          *(undefined4 *)(lVar7 + 0x18) = 0;
          if (0 < iVar4) {
            System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar7 + 0x10),0,iVar4,0);
          }
          goto LAB_18095c922;
        }
        goto LAB_18095c9ee;
      }
      if (lVar7 == 0) goto LAB_18095c9ee;
      FUN_184ad2ef0(&uStack_48,lVar7,uVar14);
      uStack_58 = uStack_48;
      uStack_50 = CONCAT44(uStack_3c,uStack_40);
      cVar3 = FUN_185159fc0(&uStack_58,_DAT_188933aa8);
      if (cVar3 != '\0') {
        if (*(longlong *)(param_1 + 0xd0) == 0) goto LAB_18095c9ee;
        FUN_184ad2ef0(&uStack_38,*(longlong *)(param_1 + 0xd0),uVar14);
        uStack_58 = CONCAT44(uStack_34,uStack_38);
        uStack_50 = uStack_30;
        lVar6 = FUN_185159d80(&uStack_58,_DAT_188933868);
        if (lVar6 == 0) goto LAB_18095c9ee;
        Torappu_Battle_Effects_Effect_FinishMe_0x60189a7(lVar6,0,0);
      }
      lVar6 = *(longlong *)(param_1 + 0xd0);
      uVar14 = (ulonglong)((int)uVar14 + 1);
    } while( true );
  }
  XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar6,param_1,0);
LAB_18095c922:
  iVar4 = FUN_1844afc00(*(undefined8 *)(param_1 + 0xd8),_DAT_18896a750);
  if (0 < iVar4) {
    lVar6 = 0x20;
    uVar14 = uVar13;
    do {
      lVar7 = *(longlong *)(param_1 + 0xd8);
      if (lVar7 == 0) goto LAB_18095c9fa;
      if (*(uint *)(lVar7 + 0x18) <= (uint)uVar14) {
        FUN_18048c0a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      plVar1 = *(longlong **)(lVar6 + lVar7);
      if (plVar1 == (longlong *)0x0) goto LAB_18095c9fa;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar1);
      }
      (**(code **)(*plVar1 + 0x1e0))(plVar1,*(undefined8 *)(*plVar1 + 0x1e8));
      uVar14 = (ulonglong)((uint)uVar14 + 1);
      uVar13 = uVar13 + 1;
      lVar6 = lVar6 + 8;
    } while ((longlong)uVar13 < (longlong)iVar4);
  }
  return;
}



/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Removing unreachable block (ram,0x0001833100fe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicSkill_OnSkillStart_0x6011bdb(longlong param_1)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong *plVar4;
  code *pcVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  longlong lVar13;
  uint uVar14;
  longlong lVar15;
  bool bVar16;
  undefined8 auStack_48 [2];
  undefined8 uStack_38;
  undefined *puStack_30;
  undefined8 *puStack_28;
  undefined1 *puStack_20;
  
  if (DAT_188c91c4e == '\0') {
    FUN_18048bf00(&DAT_18895c720);
    FUN_18048bf00(&DAT_188925ba0);
    FUN_18048bf00(&DAT_188927d60);
    FUN_18048bf00(&DAT_18896a750);
    FUN_18048bf00(&DAT_1888797f0);
    FUN_18048bf00(&DAT_188819be0);
    FUN_18048bf00(&DAT_1888d3908);
    FUN_18048bf00(&DAT_1887f9848);
    DAT_188c91c4e = '\x01';
  }
  lVar13 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x2d0);
  if (lVar13 != 0) {
    if (*(longlong *)(lVar13 + 0x18) == 0) {
      FUN_18048c0b0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    puStack_30 = (undefined *)0x0;
    puStack_28 = (undefined8 *)&stack0x00000008;
    puStack_20 = &stack0x00000020;
    FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar13 + 0x18) + 0x30),&stack0x00000008,0);
    if (*(longlong *)(lVar13 + 0x18) != 0) {
      uVar10 = *(undefined8 *)(*(longlong *)(lVar13 + 0x18) + 0x10);
      iVar7 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar13 + 0x38),*(undefined4 *)(lVar13 + 0x14),0);
      if (*(longlong *)(lVar13 + 0x18) != 0) {
        lVar15 = *(longlong *)(*(longlong *)(lVar13 + 0x18) + 0x20);
        if (lVar15 == 0) {
          FUN_18048c0b0();
        }
        else {
          FUN_183cf8c20(lVar15,uVar10,param_1,0);
          auStack_48[0] = 0;
          iVar8 = FUN_183f22380(uVar10,1,0,iVar7);
          if (iVar8 == 0) {
code_r0x0001833100e8:
            FUN_183f22fd0(uVar10,iVar7 + -1,0);
            return;
          }
          if (*(longlong *)(lVar13 + 0x18) != 0) {
            FUN_183e0d130(*(longlong *)(lVar13 + 0x18),iVar7 + -1,0);
            goto code_r0x0001833100e8;
          }
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
    FUN_180472d50();
    pcVar5 = (code *)swi(3);
    (*pcVar5)();
    return;
  }
  bVar16 = DAT_188c91c3d == '\0';
  *(undefined1 *)(param_1 + 0x98) = 0;
  *(undefined1 *)(param_1 + 0x9a) = 0;
  if (bVar16) {
    FUN_18048bf00(&DAT_188925ba0);
    DAT_188c91c3d = '\x01';
  }
  lVar13 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
  if (lVar13 == 0) {
    lVar13 = *(longlong *)(param_1 + 0xa8);
  }
  else {
    lVar13 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar13,param_1,0);
  }
  if (lVar13 == 0) goto LAB_18095ceeb;
  Torappu_Battle_Character_OnSkillStart_0x601290b(lVar13,0);
  uVar14 = 0;
  iVar7 = FUN_1844afc00(*(undefined8 *)(param_1 + 0xd8),_DAT_18896a750);
  if (0 < iVar7) {
    lVar13 = 0;
    lVar15 = 0x20;
    do {
      lVar9 = *(longlong *)(param_1 + 0xd8);
      if (lVar9 == 0) goto LAB_18095ceeb;
      if (*(uint *)(lVar9 + 0x18) <= uVar14) {
        FUN_18048c0a0();
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      plVar4 = *(longlong **)(lVar15 + lVar9);
      if (plVar4 == (longlong *)0x0) goto LAB_18095ceeb;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar4);
      }
      (**(code **)(*plVar4 + 0x1d0))(plVar4,*(undefined8 *)(*plVar4 + 0x1d8));
      uVar14 = uVar14 + 1;
      lVar13 = lVar13 + 1;
      lVar15 = lVar15 + 8;
    } while (lVar13 < iVar7);
  }
  if (*(char *)(param_1 + 0x59) != '\0') {
    bVar16 = DAT_188c91c3d == '\0';
    *(undefined1 *)(param_1 + 0x99) = 0;
    if (bVar16) {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar13 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar13 == 0) {
      lVar13 = *(longlong *)(param_1 + 0xa8);
    }
    else {
      lVar13 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar13,param_1,0);
    }
    if (lVar13 == 0) goto LAB_18095ceeb;
    lVar13 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar13,0);
    lVar15 = func_0x00018045cfe0(_DAT_1888797f0);
    if ((lVar15 == 0) ||
       (LuaMsgHandlerCallback__ctor_0x601b9cb(lVar15,param_1,_DAT_18895c720,0), lVar13 == 0))
    goto LAB_18095ceeb;
    FUN_1848dcb80(lVar13,0x14,lVar15,_DAT_188819be0);
  }
  cVar6 = Torappu_Battle_BasicSkill_get_hasSkillBeginAnim_0x6011bcc(param_1,0);
  if (cVar6 == '\0') {
    if (DAT_188c91c35 == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c35 = '\x01';
    }
    lVar13 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x208);
    if (lVar13 == 0) {
      lVar13 = *(longlong *)(param_1 + 0xb0);
    }
    else {
      lVar13 = XLua_DelegateBridge___Gen_Delegate_Imp961_0x6000e21(lVar13,param_1,0);
    }
    if (DAT_188c91c74 == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c74 = '\x01';
    }
    lVar15 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x408);
    if (lVar15 == 0) {
      if (lVar13 == 0) goto LAB_18095ceeb;
      if ((*(char *)(lVar13 + 0x68) == '\0') ||
         (cVar6 = func_0x000185db9d60(*(undefined8 *)(lVar13 + 0x50),0), cVar6 != '\0')) {
        uVar10 = *(undefined8 *)(lVar13 + 0x18);
      }
      else {
        uVar10 = *(undefined8 *)(lVar13 + 0x50);
      }
    }
    else {
      uVar10 = XLua_DelegateBridge___Gen_Delegate_Imp67_0x6000aa3(lVar15,param_1,lVar13,0);
    }
    if (DAT_188c91c3d == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar13 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar13 == 0) {
      lVar13 = *(longlong *)(param_1 + 0xa8);
    }
    else {
      lVar13 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar13,param_1,0);
    }
    if (lVar13 == 0) goto LAB_18095ceeb;
    puVar11 = (undefined8 *)
              Torappu_Battle_VisualObject_get_worldPosition_0x601302d(&puStack_28,lVar13,0);
    puVar1 = (undefined8 *)*puVar11;
    uVar2 = *(undefined4 *)(puVar11 + 1);
    if (DAT_188c91c3d == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar13 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar13 == 0) {
      uVar12 = *(undefined8 *)(param_1 + 0xa8);
    }
    else {
      uVar12 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar13,param_1,0);
    }
    if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    puStack_20 = (undefined1 *)CONCAT44(puStack_20._4_4_,uVar2);
    uStack_38 = 0;
    puStack_28 = puVar1;
    Torappu_Battle_BattleController_PlayAudioAtPos_0x600fce5
              (_DAT_1887f9848,uVar10,&puStack_28,uVar12);
  }
  lVar13 = FUN_185337c50(_DAT_1888d3908);
  if (lVar13 != 0) {
    lVar13 = Torappu_Battle_BattleController_get_logger_0x600fbfc(lVar13,0);
    if (DAT_188c91c3d == '\0') {
      FUN_18048bf00(&DAT_188925ba0);
      DAT_188c91c3d = '\x01';
    }
    lVar15 = *(longlong *)(*(longlong *)(_DAT_188925ba0 + 0xb8) + 0x248);
    if (lVar15 == 0) {
      lVar15 = *(longlong *)(param_1 + 0xa8);
    }
    else {
      lVar15 = XLua_DelegateBridge___Gen_Delegate_Imp3354_0x600177a(lVar15,param_1,0);
    }
    if ((lVar15 != 0) &&
       (lVar15 = Torappu_Battle_Character_get_data_0x6012883(lVar15,0), lVar13 != 0)) {
      if (cRam0000000188c909d6 == '\0') {
        puStack_30 = &UNK_180712a25;
        FUN_18048bf00(0x188932860,lVar15,0);
        puStack_30 = &UNK_180712a31;
        FUN_18048bf00(0x188882298);
        puStack_30 = &UNK_180712a3d;
        FUN_18048bf00(0x188870480);
        puStack_30 = &UNK_180712a49;
        FUN_18048bf00(0x188878840);
        cRam0000000188c909d6 = '\x01';
      }
      lVar9 = *(longlong *)(*(longlong *)(lRam0000000188932860 + 0xb8) + 0xd8);
      if (lVar9 == 0) {
        if (lVar15 == 0) {
          return;
        }
        if (*(longlong *)(lVar15 + 0x108) != 0) {
          puStack_30 = &UNK_180712a9c;
          cVar6 = func_0x000185db9d60(*(undefined8 *)(*(longlong *)(lVar15 + 0x108) + 0x18),0);
          if (cVar6 != '\0') {
            return;
          }
          uVar10 = **(undefined8 **)(lRam0000000188878840 + 0xb8);
          puStack_30 = &UNK_180712ac0;
          cVar6 = func_0x000185db9d60(*(undefined8 *)(lVar15 + 0x20),0);
          if (cVar6 == '\0') {
            uVar10 = *(undefined8 *)(lVar15 + 0x20);
          }
          else {
            puStack_30 = &UNK_180712acf;
            cVar6 = func_0x000185db9d60(*(undefined8 *)(lVar15 + 0x10),0);
            if (cVar6 == '\0') {
              uVar10 = *(undefined8 *)(lVar15 + 0x10);
            }
          }
          if (*(longlong *)(lVar13 + 0x30) != 0) {
            lVar13 = *(longlong *)(*(longlong *)(lVar13 + 0x30) + 0x28);
            puStack_30 = &UNK_180712afa;
            lVar9 = func_0x00018045cfe0(lRam0000000188870480);
            if (lVar9 != 0) {
              if (cRam0000000188c909f6 == '\0') {
                puStack_30 = &UNK_180712b1b;
                FUN_18048bf00(0x188870480);
                cRam0000000188c909f6 = '\x01';
              }
              puStack_30 = &UNK_180712b2c;
              func_0x00018050cf60(lVar9,0);
              lVar3 = *(longlong *)(*(longlong *)(lRam0000000188870480 + 0xb8) + 8);
              if (lVar3 != 0) {
                puStack_30 = &UNK_180712b4e;
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar3,lVar9,0);
              }
              *(undefined8 *)(lVar9 + 0x10) = uVar10;
              puStack_30 = &UNK_180712b5e;
              func_0x00018048b9e0(lVar9 + 0x10,uVar10);
              if (*(longlong *)(lVar15 + 0x108) != 0) {
                *(undefined8 *)(lVar9 + 0x18) =
                     *(undefined8 *)(*(longlong *)(lVar15 + 0x108) + 0x18);
                puStack_30 = &UNK_180712b7b;
                func_0x00018048b9e0(lVar9 + 0x18);
                if (lVar13 != 0) {
                  puStack_30 = &UNK_180712b92;
                  FUN_184a80a50(lVar13,lVar9,uRam0000000188882298);
                  return;
                }
              }
            }
          }
        }
        puStack_30 = &UNK_180712bc4;
        FUN_18048c0b0();
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      if (*(longlong *)(lVar9 + 0x18) == 0) {
        FUN_18048c0b0();
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      auStack_48[0] = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x30);
      uStack_38 = 0;
      puStack_30 = &stack0x00000008;
      puStack_28 = auStack_48;
      FUN_185ca7f50(auStack_48[0],&stack0x00000008,0);
      if (*(longlong *)(lVar9 + 0x18) != 0) {
        uVar10 = *(undefined8 *)(*(longlong *)(lVar9 + 0x18) + 0x10);
        iVar7 = FUN_183f23b70(uVar10,*(undefined4 *)(lVar9 + 0x38),*(undefined4 *)(lVar9 + 0x14),0);
        if (*(longlong *)(lVar9 + 0x18) != 0) {
          lVar3 = *(longlong *)(*(longlong *)(lVar9 + 0x18) + 0x20);
          if (lVar3 == 0) {
            FUN_18048c0b0();
          }
          else {
            FUN_183cf8c20(lVar3,uVar10,lVar13,0);
            FUN_183cf8c20(lVar3,uVar10,lVar15,0);
            iVar8 = FUN_183f22380(uVar10,2,0,iVar7,0);
            if (iVar8 == 0) {
code_r0x0001832d231b:
              FUN_183f22fd0(uVar10,iVar7 + -1,0);
              return;
            }
            if (*(longlong *)(lVar9 + 0x18) != 0) {
              FUN_183e0d130(*(longlong *)(lVar9 + 0x18),iVar7 + -1,0);
              goto code_r0x0001832d231b;
            }
          }
          FUN_18048c0b0();
        }
        FUN_18048c0b0();
      }
      FUN_18048c0b0();
      FUN_180472d50();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
LAB_18095ceeb:
  FUN_18048c0b0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}


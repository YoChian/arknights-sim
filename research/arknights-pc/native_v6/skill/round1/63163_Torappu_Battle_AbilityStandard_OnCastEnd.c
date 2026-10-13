
/* WARNING: Removing unreachable block (ram,0x0001832f7a98) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_OnCastEnd_0x600f6bc(longlong *param_1,uint param_2)

{
  undefined8 uVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined4 uVar12;
  uint uVar13;
  longlong lVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 *puStack_208;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined1 auStack_108 [136];
  undefined *puStack_80;
  undefined8 uStack_60;
  undefined8 uStack_58;
  uint auStack_48 [2];
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c8fd3a == '\0') {
    uStack_60 = 0x1805d0b03;
    FUN_18048bf00(&DAT_188974cb0);
    uStack_60 = 0x1805d0b0f;
    FUN_18048bf00(&DAT_188927d60);
    uStack_60 = 0x1805d0b1b;
    FUN_18048bf00(&DAT_1888797f0);
    uStack_60 = 0x1805d0b27;
    FUN_18048bf00(&DAT_188819e20);
    uStack_60 = 0x1805d0b33;
    FUN_18048bf00(&DAT_188932ce8);
    uStack_60 = 0x1805d0b3f;
    FUN_18048bf00(&DAT_188917488);
    DAT_188c8fd3a = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x130);
  if (lVar7 == 0) {
    if (DAT_188c8fce1 == '\0') {
      uStack_60 = 0x1805d0b7d;
      FUN_18048bf00(&DAT_1889733f0);
      DAT_188c8fce1 = '\x01';
    }
    lVar7 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x130);
    if (lVar7 == 0) {
      *(uint *)((longlong)param_1 + 0xbc) = param_2;
    }
    else {
      uStack_60 = 0x1805d0bb5;
      XLua_DelegateBridge___Gen_Delegate_Imp2640_0x60014b0(lVar7,param_1,param_2,0);
    }
    lVar7 = param_1[0x20];
    uVar13 = 0;
    if (lVar7 != 0) {
      lVar14 = 0x20;
      do {
        if (*(int *)(lVar7 + 0x18) <= (int)uVar13) {
          if (DAT_188c8fcc7 == '\0') {
            uStack_60 = 0x1805d0c64;
            FUN_18048bf00(&DAT_1889733f0);
            uStack_60 = 0x1805d0c70;
            FUN_18048bf00(&DAT_1889355a8);
            DAT_188c8fcc7 = '\x01';
          }
          lVar7 = *(longlong *)(*(longlong *)(_DAT_1889733f0 + 0xb8) + 0x60);
          if (lVar7 == 0) {
            uStack_60 = 0x1805d0c9e;
            lVar7 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
          }
          else {
            uStack_60 = 0x1805d0cab;
            lVar7 = XLua_DelegateBridge___Gen_Delegate_Imp2631_0x60014a7(lVar7,param_1,0);
          }
          uStack_60 = 0x1805d0cb8;
          uVar8 = Torappu_Battle_Ability_get_signalId_0x600f62c(param_1,0);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            uStack_60 = 0x1805d0cd0;
            func_0x00018048c140();
          }
          uStack_60 = 0x1805d0cdd;
          cVar4 = FUN_186b63a70(lVar7,0,0);
          uVar11 = _DAT_188917488;
          if (cVar4 == '\0') {
            if (DAT_188c8f5b6 == '\0') {
              uStack_60 = 0x1805d0d1f;
              FUN_18048bf00(&DAT_188829ff0);
              DAT_188c8f5b6 = '\x01';
            }
            uVar1 = **(undefined8 **)(_DAT_188829ff0 + 0xb8);
            uVar15 = (undefined4)uVar1;
            uVar16 = (undefined4)((ulonglong)uVar1 >> 0x20);
            uVar12 = *(undefined4 *)(*(undefined8 **)(_DAT_188829ff0 + 0xb8) + 1);
          }
          else {
            if (lVar7 == 0) break;
            uStack_60 = 0x1805d0d01;
            puVar9 = (undefined8 *)
                     Torappu_Battle_VisualObject_get_worldPosition_0x601302d(&puStack_28,lVar7,0);
            uVar15 = (undefined4)*puVar9;
            uVar16 = (undefined4)((ulonglong)*puVar9 >> 0x20);
            uVar12 = *(undefined4 *)(puVar9 + 1);
          }
          if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
            uStack_60 = 0x1805d0d56;
            func_0x00018048c140();
          }
          puStack_20 = (undefined8 *)CONCAT44(puStack_20._4_4_,uVar12);
          uStack_38 = 0;
          uStack_60 = 0x1805d0d82;
          puStack_28 = (undefined1 *)CONCAT44(uVar16,uVar15);
          Torappu_Battle_BattleController_PlayAudioAtPos_0x600fce5(uVar11,uVar8,&puStack_28,lVar7);
          if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
            uStack_60 = 0x1805d0d97;
            func_0x00018048c140();
          }
          uStack_60 = 0x1805d0da4;
          cVar4 = FUN_186b63a70(lVar7,0,0);
          if (cVar4 != '\0') {
            if (lVar7 == 0) break;
            uStack_60 = 0x1805d0dbf;
            lVar14 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar7,0);
            uStack_60 = 0x1805d0dce;
            lVar10 = func_0x00018045cfe0(_DAT_1888797f0);
            if (lVar10 == 0) break;
            if (DAT_188ccc7f0 != '\0') {
              uStack_60 = 0x1805d0deb;
              func_0x000180446d00(*param_1);
            }
            uStack_60 = 0x1805d0e03;
            LuaMsgHandlerCallback__ctor_0x601b9cb
                      (lVar10,param_1,*(undefined8 *)(*param_1 + 0x678),0);
            if (lVar14 == 0) break;
            uStack_60 = 0x1805d0e23;
            FUN_1848dcbf0(lVar14,0x14,lVar10,_DAT_188819e20);
            uStack_60 = 0x1805d0e2d;
            lVar14 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar7,0);
            uStack_60 = 0x1805d0e3c;
            lVar10 = func_0x00018045cfe0(_DAT_1888797f0);
            if (lVar10 == 0) break;
            if (DAT_188ccc7f0 != '\0') {
              uStack_60 = 0x1805d0e59;
              func_0x000180446d00(*param_1);
            }
            uStack_60 = 0x1805d0e71;
            LuaMsgHandlerCallback__ctor_0x601b9cb
                      (lVar10,param_1,*(undefined8 *)(*param_1 + 0x688),0);
            if (lVar14 == 0) break;
            uStack_60 = 0x1805d0e91;
            FUN_1848dcbf0(lVar14,0x19,lVar10,_DAT_188819e20);
            uStack_60 = 0x1805d0e9b;
            lVar14 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar7,0);
            uStack_60 = 0x1805d0eaa;
            lVar10 = func_0x00018045cfe0(_DAT_1888797f0);
            if (lVar10 == 0) break;
            if (DAT_188ccc7f0 != '\0') {
              uStack_60 = 0x1805d0ec7;
              func_0x000180446d00(*param_1);
            }
            uStack_60 = 0x1805d0edf;
            LuaMsgHandlerCallback__ctor_0x601b9cb
                      (lVar10,param_1,*(undefined8 *)(*param_1 + 0x698),0);
            if (lVar14 == 0) break;
            uStack_60 = 0x1805d0eff;
            FUN_1848dcbf0(lVar14,0x1a,lVar10,_DAT_188819e20);
            uStack_60 = 0x1805d0f09;
            lVar14 = Torappu_Battle_Entity_get_eventPool_0x6010338(lVar7,0);
            uStack_60 = 0x1805d0f18;
            lVar10 = func_0x00018045cfe0(_DAT_1888797f0);
            if (lVar10 == 0) break;
            if (DAT_188ccc7f0 != '\0') {
              uStack_60 = 0x1805d0f35;
              func_0x000180446d00(*param_1);
            }
            uStack_60 = 0x1805d0f4d;
            LuaMsgHandlerCallback__ctor_0x601b9cb
                      (lVar10,param_1,*(undefined8 *)(*param_1 + 0x6a8),0);
            if (lVar14 == 0) break;
            uStack_60 = 0x1805d0f69;
            FUN_1848dcbf0(lVar14,0x21,lVar10,_DAT_188819e20);
            uStack_60 = 0x1805d0f7a;
            Torappu_Battle_Entity_OnAbilityFinish_0x6010486(lVar7,param_1,param_2,0);
          }
          if (cRam0000000188c8fd2e == '\0') {
            FUN_18048bf00(&DAT_188974cb0,3,1,0);
            FUN_18048bf00(&DAT_1889355a8);
            cRam0000000188c8fd2e = '\x01';
          }
          uVar13 = 0;
          uStack_218 = 0;
          FUN_180501c30(&uStack_1f8,0,0xf0);
          lVar7 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0xd0);
          if (lVar7 != 0) {
            FUN_1832f9490(lVar7,param_1,3,1,0);
            return;
          }
          lVar7 = FUN_1805d7900(param_1,0);
          if (lVar7 == 0) goto code_r0x0001805d1f78;
          uStack_218 = Torappu_Battle_Context_BeginChangeGard_0x6010096(lVar7,0);
          uStack_210 = 0;
          puStack_208 = &uStack_218;
          FUN_1806c3290(&uStack_218,param_1,0);
          uVar8 = FUN_185159d80(param_1 + 10,_DAT_1889355a8);
          FUN_1806c3720(&uStack_218,uVar8,0);
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*param_1);
          }
          lVar7 = (**(code **)(*param_1 + 0x5f0))(param_1,3,*(undefined8 *)(*param_1 + 0x5f8));
          if (lVar7 != 0) {
            lVar14 = FUN_1805d7900(param_1,0);
            if (lVar14 == 0) {
              FUN_18048c0b0();
              goto code_r0x0001805d1f78;
            }
            puVar9 = (undefined8 *)FUN_1806c5dd0(auStack_108,lVar14,0);
            uStack_1f8 = *puVar9;
            uStack_1f0 = puVar9[1];
            uStack_1e8 = puVar9[2];
            uStack_1e0 = puVar9[3];
            uStack_1d8 = puVar9[4];
            uStack_1d0 = puVar9[5];
            uStack_1c8 = puVar9[6];
            uStack_1c0 = puVar9[7];
            uStack_1b8 = puVar9[8];
            uStack_1b0 = puVar9[9];
            uStack_1a8 = puVar9[10];
            uStack_1a0 = puVar9[0xb];
            uStack_198 = puVar9[0xc];
            uStack_190 = puVar9[0xd];
            uStack_188 = puVar9[0xe];
            uStack_180 = puVar9[0xf];
            uStack_178 = puVar9[0x10];
            uStack_170 = puVar9[0x11];
            uStack_168 = puVar9[0x12];
            uStack_160 = puVar9[0x13];
            uStack_158 = puVar9[0x14];
            uStack_150 = puVar9[0x15];
            uStack_148 = puVar9[0x16];
            uStack_140 = puVar9[0x17];
            uStack_138 = puVar9[0x18];
            uStack_130 = puVar9[0x19];
            uStack_128 = *(undefined4 *)(puVar9 + 0x1a);
            uStack_124 = *(undefined4 *)((longlong)puVar9 + 0xd4);
            uStack_120 = *(undefined4 *)(puVar9 + 0x1b);
            uStack_11c = *(undefined4 *)((longlong)puVar9 + 0xdc);
            uStack_118 = *(undefined4 *)(puVar9 + 0x1c);
            uStack_114 = *(undefined4 *)((longlong)puVar9 + 0xe4);
            uStack_110 = *(undefined4 *)(puVar9 + 0x1d);
            uStack_10c = *(undefined4 *)((longlong)puVar9 + 0xec);
            uVar8 = FUN_1805d7840(param_1,0);
            FUN_181190690(lVar7,2,uVar8,&uStack_1f8,0);
          }
          ChangeGuard_Dispose_0x60100ba(&uStack_218,0);
          lVar7 = param_1[0x20];
          if (lVar7 == 0) goto code_r0x0001805d1f78;
          lVar14 = 0x20;
          goto code_r0x0001805d1ed8;
        }
        lVar7 = param_1[0x20];
        if (lVar7 == 0) break;
        if (*(uint *)(lVar7 + 0x18) <= uVar13) {
          uStack_60 = 0x1805d0fc8;
          FUN_18048c0a0();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        plVar2 = *(longlong **)(lVar14 + lVar7);
        if (plVar2 == (longlong *)0x0) break;
        if (DAT_188ccc7f0 != '\0') {
          uStack_60 = 0x1805d0c1c;
          func_0x000180446d00(*plVar2);
        }
        uStack_60 = 0x1805d0c35;
        (**(code **)(*plVar2 + 0x1d0))(plVar2,param_2);
        lVar7 = param_1[0x20];
        uVar13 = uVar13 + 1;
        lVar14 = lVar14 + 8;
      } while (lVar7 != 0);
    }
    uStack_60 = 0x1805d0fc2;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (cRam0000000188cafba9 == '\0') {
    puStack_80 = &UNK_1832f7977;
    FUN_18048bf00(0x1888a0e78,param_1,param_2,0);
    cRam0000000188cafba9 = '\x01';
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    puStack_80 = &UNK_1832f7b02;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStack_40 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStack_40;
  puStack_80 = &UNK_1832f79d1;
  FUN_185ca7f50(uStack_40,&stack0x00000008,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar8 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    puStack_80 = &UNK_1832f79f4;
    iVar5 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar14 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar14 == 0) {
        puStack_80 = &UNK_1832f7ae6;
        FUN_18048c0b0();
      }
      else {
        puStack_80 = &UNK_1832f7a22;
        FUN_183cf8c20(lVar14,uVar8,param_1,0);
        puStack_80 = &UNK_1832f7a38;
        auStack_48[0] = param_2;
        uVar11 = func_0x00018048b9c0(uRam00000001888a0e78,auStack_48);
        puStack_80 = &UNK_1832f7a49;
        FUN_183cfbf40(lVar14,uVar8,uVar11,0);
        uStack_58 = 0;
        puStack_80 = &UNK_1832f7a65;
        iVar6 = FUN_183f22380(uVar8,2,0,iVar5);
        if (iVar6 == 0) {
code_r0x0001832f7a7e:
          puStack_80 = &UNK_1832f7a8d;
          FUN_183f22fd0(uVar8,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          puStack_80 = &UNK_1832f7a7e;
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
          goto code_r0x0001832f7a7e;
        }
      }
      puStack_80 = &UNK_1832f7aec;
      FUN_18048c0b0();
    }
    puStack_80 = &UNK_1832f7af1;
    FUN_18048c0b0();
  }
  puStack_80 = &UNK_1832f7af6;
  FUN_18048c0b0();
  puStack_80 = &UNK_1832f7afc;
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
  while( true ) {
    if (*(uint *)(lVar7 + 0x18) <= uVar13) {
      FUN_18048c0a0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    plVar2 = *(longlong **)(lVar14 + lVar7);
    if (plVar2 == (longlong *)0x0) break;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(*plVar2);
    }
    (**(code **)(*plVar2 + 0x1e0))(plVar2,3,*(undefined8 *)(*plVar2 + 0x1e8));
    uVar13 = uVar13 + 1;
    lVar14 = lVar14 + 8;
    lVar7 = param_1[0x20];
    if (lVar7 == 0) break;
code_r0x0001805d1ed8:
    if (*(int *)(lVar7 + 0x18) <= (int)uVar13) {
      return;
    }
    lVar7 = param_1[0x20];
    if (lVar7 == 0) break;
  }
code_r0x0001805d1f78:
  FUN_18048c0b0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_AbilityStandard_OnAttached_0x600f6bd(longlong *param_1)

{
  longlong *plVar1;
  undefined8 uVar2;
  code *pcVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 *puVar10;
  uint uVar11;
  longlong *plStackX_8;
  undefined8 uStackX_10;
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
  undefined1 auStack_108 [152];
  undefined *puStack_70;
  undefined8 uStack_48;
  undefined8 uStack_30;
  longlong **pplStack_28;
  undefined1 *puStack_20;
  
  if (DAT_188c8fd3b == '\0') {
    uStack_30 = 0x1805d07be;
    FUN_18048bf00(&DAT_188974cb0);
    DAT_188c8fd3b = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0x138);
  if (lVar7 == 0) {
    uStack_30 = 0x1805d07ec;
    Torappu_Battle_AbilityStandard_DoUpdatePlaybackSpeed_0x600f6cb(param_1,0);
    if (DAT_188ccc7f0 != '\0') {
      uStack_30 = 0x1805d07fd;
      func_0x000180446d00(*param_1);
    }
    uStack_30 = 0x1805d0813;
    uVar4 = (**(code **)(*param_1 + 0x700))(param_1);
    *(undefined1 *)(param_1 + 0x21) = uVar4;
    uStackX_10 = (ulonglong)uStackX_10._4_4_ << 0x20;
    plStackX_8 = param_1;
    if (cRam0000000188c8fd2e == '\0') {
      FUN_18048bf00(&DAT_188974cb0,0,1,0);
      FUN_18048bf00(0x1889355a8);
      cRam0000000188c8fd2e = '\x01';
    }
    uVar11 = 0;
    uStack_218 = 0;
    FUN_180501c30(&uStack_1f8,0,0xf0);
    lVar7 = *(longlong *)(*(longlong *)(_DAT_188974cb0 + 0xb8) + 0xd0);
    if (lVar7 != 0) {
      FUN_1832f9490(lVar7,param_1,0,1,0);
      return;
    }
    lVar7 = FUN_1805d7900(param_1,0);
    if (lVar7 != 0) {
      uStack_218 = FUN_1806c5c20(lVar7,0);
      uStack_210 = 0;
      puStack_208 = &uStack_218;
      FUN_1806c3290(&uStack_218,param_1,0);
      uVar8 = FUN_185159d80(param_1 + 10,uRam00000001889355a8);
      FUN_1806c3720(&uStack_218,uVar8,0);
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_1);
      }
      lVar7 = (**(code **)(*param_1 + 0x5f0))(param_1,0,*(undefined8 *)(*param_1 + 0x5f8));
      if (lVar7 != 0) {
        lVar9 = FUN_1805d7900(param_1,0);
        if (lVar9 == 0) {
          FUN_18048c0b0();
          goto code_r0x0001805d1f78;
        }
        puVar10 = (undefined8 *)FUN_1806c5dd0(auStack_108,lVar9,0);
        uStack_1f8 = *puVar10;
        uStack_1f0 = puVar10[1];
        uStack_1e8 = puVar10[2];
        uStack_1e0 = puVar10[3];
        uStack_1d8 = puVar10[4];
        uStack_1d0 = puVar10[5];
        uStack_1c8 = puVar10[6];
        uStack_1c0 = puVar10[7];
        uStack_1b8 = puVar10[8];
        uStack_1b0 = puVar10[9];
        uStack_1a8 = puVar10[10];
        uStack_1a0 = puVar10[0xb];
        uStack_198 = puVar10[0xc];
        uStack_190 = puVar10[0xd];
        uStack_188 = puVar10[0xe];
        uStack_180 = puVar10[0xf];
        uStack_178 = puVar10[0x10];
        uStack_170 = puVar10[0x11];
        uStack_168 = puVar10[0x12];
        uStack_160 = puVar10[0x13];
        uStack_158 = puVar10[0x14];
        uStack_150 = puVar10[0x15];
        uStack_148 = puVar10[0x16];
        uStack_140 = puVar10[0x17];
        uStack_138 = puVar10[0x18];
        uStack_130 = puVar10[0x19];
        uStack_128 = *(undefined4 *)(puVar10 + 0x1a);
        uStack_124 = *(undefined4 *)((longlong)puVar10 + 0xd4);
        uStack_120 = *(undefined4 *)(puVar10 + 0x1b);
        uStack_11c = *(undefined4 *)((longlong)puVar10 + 0xdc);
        uStack_118 = *(undefined4 *)(puVar10 + 0x1c);
        uStack_114 = *(undefined4 *)((longlong)puVar10 + 0xe4);
        uStack_110 = *(undefined4 *)(puVar10 + 0x1d);
        uStack_10c = *(undefined4 *)((longlong)puVar10 + 0xec);
        uVar8 = Torappu_Battle_Ability_get_blackboard_0x600f62a(param_1,0);
        FUN_181190690(lVar7,2,uVar8,&uStack_1f8,0);
      }
      FUN_1806c2ce0(&uStack_218,0);
      lVar7 = param_1[0x20];
      if (lVar7 != 0) {
        lVar9 = 0x20;
        do {
          if (*(int *)(lVar7 + 0x18) <= (int)uVar11) {
            return;
          }
          lVar7 = param_1[0x20];
          if (lVar7 == 0) break;
          if (*(uint *)(lVar7 + 0x18) <= uVar11) {
            FUN_18048c0a0();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          plVar1 = *(longlong **)(lVar9 + lVar7);
          if (plVar1 == (longlong *)0x0) break;
          if (DAT_188ccc7f0 != '\0') {
            func_0x000180446d00(*plVar1);
          }
          (**(code **)(*plVar1 + 0x1e0))(plVar1,0,*(undefined8 *)(*plVar1 + 0x1e8));
          uVar11 = uVar11 + 1;
          lVar9 = lVar9 + 8;
          lVar7 = param_1[0x20];
        } while (lVar7 != 0);
      }
    }
code_r0x0001805d1f78:
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    puStack_70 = &UNK_18331015e;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uVar8 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  plStackX_8 = (longlong *)((ulonglong)plStackX_8 & 0xffffffffffffff00);
  uStack_30 = 0;
  pplStack_28 = &plStackX_8;
  puStack_20 = &stack0x00000020;
  puStack_70 = &UNK_183310067;
  FUN_185ca7f50(uVar8,&plStackX_8,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar2 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    puStack_70 = &UNK_18331008a;
    iVar5 = FUN_183f23b70(uVar2,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar9 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar9 == 0) {
        puStack_70 = &UNK_183310142;
        FUN_18048c0b0();
      }
      else {
        puStack_70 = &UNK_1833100b4;
        FUN_183cf8c20(lVar9,uVar2,param_1,0);
        uStack_48 = 0;
        puStack_70 = &UNK_1833100d0;
        iVar6 = FUN_183f22380(uVar2,1,0,iVar5);
        if (iVar6 == 0) {
code_r0x0001833100e8:
          puStack_70 = &UNK_1833100f6;
          FUN_183f22fd0(uVar2,iVar5 + -1,0);
          if ((char)plStackX_8 != '\0') {
            puStack_70 = &UNK_18331010d;
            func_0x000185ca7ff0(uVar8,0);
          }
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          puStack_70 = &UNK_1833100e8;
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833100e8;
        }
      }
      puStack_70 = &UNK_183310148;
      FUN_18048c0b0();
    }
    puStack_70 = &UNK_18331014d;
    FUN_18048c0b0();
  }
  puStack_70 = &UNK_183310152;
  FUN_18048c0b0();
  puStack_70 = &UNK_183310158;
  FUN_180472d50();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}


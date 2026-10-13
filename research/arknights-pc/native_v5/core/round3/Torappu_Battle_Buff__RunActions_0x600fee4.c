
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 *
Torappu_Battle_Buff__RunActions_0x600fee4
          (undefined8 *param_1,longlong param_2,undefined4 param_3,char param_4)

{
  code *pcVar1;
  char cVar2;
  uint uVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  undefined8 uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 *puStack_2e8;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 uStack_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
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
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined1 auStack_f8 [240];
  
  if (DAT_188c90369 == '\0') {
    FUN_18048bf00(&DAT_18895c250);
    FUN_18048bf00(&DAT_188871398);
    FUN_18048bf00(&DAT_1888d3908);
    DAT_188c90369 = '\x01';
  }
  FUN_180501c30(&uStack_2d8,0,0xf0);
  FUN_180501c30(&uStack_1e8,0,0xf0);
  if (*(int *)(_DAT_18895c250 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_18895c250);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_18895c250 + 0xb8) + 0x658);
  if (lVar4 != 0) {
    puVar7 = (undefined8 *)
             XLua_DelegateBridge___Gen_Delegate_Imp2939_0x60015db
                       (auStack_f8,lVar4,param_2,param_3,param_4,0);
    uVar5 = puVar7[1];
    *param_1 = *puVar7;
    param_1[1] = uVar5;
    uVar5 = puVar7[3];
    param_1[2] = puVar7[2];
    param_1[3] = uVar5;
    uVar5 = puVar7[5];
    param_1[4] = puVar7[4];
    param_1[5] = uVar5;
    uVar5 = puVar7[7];
    param_1[6] = puVar7[6];
    param_1[7] = uVar5;
    uVar5 = puVar7[9];
    param_1[8] = puVar7[8];
    param_1[9] = uVar5;
    uVar5 = puVar7[0xb];
    param_1[10] = puVar7[10];
    param_1[0xb] = uVar5;
    uVar5 = puVar7[0xd];
    param_1[0xc] = puVar7[0xc];
    param_1[0xd] = uVar5;
    uVar5 = puVar7[0xf];
    param_1[0xe] = puVar7[0xe];
    param_1[0xf] = uVar5;
    uVar5 = puVar7[0x11];
    param_1[0x10] = puVar7[0x10];
    param_1[0x11] = uVar5;
    uVar5 = puVar7[0x13];
    param_1[0x12] = puVar7[0x12];
    param_1[0x13] = uVar5;
    uVar5 = puVar7[0x15];
    param_1[0x14] = puVar7[0x14];
    param_1[0x15] = uVar5;
    uVar5 = puVar7[0x17];
    param_1[0x16] = puVar7[0x16];
    param_1[0x17] = uVar5;
    uVar5 = puVar7[0x19];
    param_1[0x18] = puVar7[0x18];
    param_1[0x19] = uVar5;
    uVar5 = puVar7[0x1b];
    param_1[0x1a] = puVar7[0x1a];
    param_1[0x1b] = uVar5;
    uVar5 = puVar7[0x1d];
    param_1[0x1c] = puVar7[0x1c];
    param_1[0x1d] = uVar5;
    return param_1;
  }
  lVar4 = Torappu_Battle_Buff_get_context_0x600fe2a(param_2);
  if (lVar4 == 0) {
    FUN_18048c0b0();
    pcVar1 = (code *)swi(3);
    puVar7 = (undefined8 *)(*pcVar1)();
    return puVar7;
  }
  uStack_2f8 = Torappu_Battle_Context_BeginChangeGard_0x6010096(lVar4,0);
  uStack_2f0 = 0;
  puStack_2e8 = &uStack_2f8;
  ChangeGuard_set_buff_0x60100ab(&uStack_2f8,param_2,0);
  uVar5 = Torappu_Battle_Buff_get_source_0x600fe28(param_2,0);
  ChangeGuard_set_source_0x60100a7(&uStack_2f8,uVar5,0);
  if (param_4 != '\0') {
    uVar5 = Torappu_Battle_Buff_get_owner_0x600fe27(param_2,0);
    ChangeGuard_set_target_0x60100a9(&uStack_2f8,uVar5,0);
  }
  plVar6 = (longlong *)Torappu_Battle_Buff_get_owner_0x600fe27(param_2,0);
  if (plVar6 == (longlong *)0x0) goto LAB_18068d9be;
  if (DAT_188ccc7f0 != '\0') {
    func_0x000180446d00(*plVar6);
  }
  cVar2 = (**(code **)(*plVar6 + 0x3c0))(plVar6,*(undefined8 *)(*plVar6 + 0x3c8));
  if (cVar2 == '\0') {
LAB_18068d675:
    lVar4 = *(longlong *)(param_2 + 0xb0);
    uVar3 = func_0x0001844dc660(param_3,_DAT_188871398);
    if (lVar4 != 0) {
      if (*(uint *)(lVar4 + 0x18) <= uVar3) {
        FUN_18048c0a0();
        goto LAB_18068d9aa;
      }
      uVar5 = *(undefined8 *)(lVar4 + 0x20 + (longlong)(int)uVar3 * 8);
      Torappu_Battle_Buff_get_owner_0x600fe27(param_2,0);
      Torappu_Battle_Buff_get_source_0x600fe28(param_2,0);
      lVar4 = FUN_185337c50(_DAT_1888d3908);
      if (lVar4 != 0) {
        lVar4 = Torappu_Battle_BattleController_get_context_0x600fbfa(lVar4,0);
        if (lVar4 != 0) {
          puVar7 = (undefined8 *)Torappu_Battle_Context_TakeSnapshot_0x6010095(auStack_f8,lVar4,0);
          uStack_2d8 = *puVar7;
          uStack_2d0 = puVar7[1];
          uStack_2c8 = puVar7[2];
          uStack_2c0 = puVar7[3];
          uStack_2b8 = puVar7[4];
          uStack_2b0 = puVar7[5];
          uStack_2a8 = puVar7[6];
          uStack_2a0 = puVar7[7];
          uStack_298 = puVar7[8];
          uStack_290 = puVar7[9];
          uStack_288 = puVar7[10];
          uStack_280 = puVar7[0xb];
          uStack_278 = puVar7[0xc];
          uStack_270 = puVar7[0xd];
          uStack_268 = puVar7[0xe];
          uStack_260 = puVar7[0xf];
          uStack_258 = puVar7[0x10];
          uStack_250 = puVar7[0x11];
          uStack_248 = puVar7[0x12];
          uStack_240 = puVar7[0x13];
          uStack_238 = puVar7[0x14];
          uStack_230 = puVar7[0x15];
          uStack_228 = puVar7[0x16];
          uStack_220 = puVar7[0x17];
          uStack_218 = puVar7[0x18];
          uStack_210 = puVar7[0x19];
          uStack_208 = *(undefined4 *)(puVar7 + 0x1a);
          uStack_204 = *(undefined4 *)((longlong)puVar7 + 0xd4);
          uStack_200 = *(undefined4 *)(puVar7 + 0x1b);
          uStack_1fc = *(undefined4 *)((longlong)puVar7 + 0xdc);
          uStack_1f8 = *(undefined4 *)(puVar7 + 0x1c);
          uStack_1f4 = *(undefined4 *)((longlong)puVar7 + 0xe4);
          uStack_1f0 = *(undefined4 *)(puVar7 + 0x1d);
          uStack_1ec = *(undefined4 *)((longlong)puVar7 + 0xec);
          Torappu_Battle_Action_ActionUtil_RunActions_0x6018901
                    (uVar5,1,*(undefined8 *)(param_2 + 0xb8),&uStack_2d8,0);
          uStack_1e8 = uStack_2d8;
          uStack_1e0 = uStack_2d0;
          uStack_1d8 = uStack_2c8;
          uStack_1d0 = uStack_2c0;
          uStack_1c8 = uStack_2b8;
          uStack_1c0 = uStack_2b0;
          uStack_1b8 = uStack_2a8;
          uStack_1b0 = uStack_2a0;
          uStack_1a8 = uStack_298;
          uStack_1a0 = uStack_290;
          uStack_198 = uStack_288;
          uStack_190 = uStack_280;
          uStack_188 = uStack_278;
          uStack_180 = uStack_270;
          uStack_178 = uStack_268;
          uStack_170 = uStack_260;
          uStack_168 = uStack_258;
          uStack_160 = uStack_250;
          uStack_158 = uStack_248;
          uStack_150 = uStack_240;
          uStack_148 = uStack_238;
          uStack_140 = uStack_230;
          uStack_138 = uStack_228;
          uStack_130 = uStack_220;
          uStack_128 = uStack_218;
          uStack_120 = uStack_210;
          uStack_118 = uStack_208;
          uStack_114 = uStack_204;
          uStack_110 = uStack_200;
          uStack_10c = uStack_1fc;
          uStack_108 = uStack_1f8;
          uStack_104 = uStack_1f4;
          uStack_100 = uStack_1f0;
          uStack_fc = uStack_1ec;
          ChangeGuard_Dispose_0x60100ba(&uStack_2f8,0);
          *param_1 = uStack_1e8;
          param_1[1] = uStack_1e0;
          param_1[2] = uStack_1d8;
          param_1[3] = uStack_1d0;
          param_1[4] = uStack_1c8;
          param_1[5] = uStack_1c0;
          param_1[6] = uStack_1b8;
          param_1[7] = uStack_1b0;
          param_1[8] = uStack_1a8;
          param_1[9] = uStack_1a0;
          param_1[10] = uStack_198;
          param_1[0xb] = uStack_190;
          param_1[0xc] = uStack_188;
          param_1[0xd] = uStack_180;
          param_1[0xe] = uStack_178;
          param_1[0xf] = uStack_170;
          param_1[0x10] = uStack_168;
          param_1[0x11] = uStack_160;
          param_1[0x12] = uStack_158;
          param_1[0x13] = uStack_150;
          param_1[0x14] = uStack_148;
          param_1[0x15] = uStack_140;
          param_1[0x16] = uStack_138;
          param_1[0x17] = uStack_130;
          param_1[0x18] = uStack_128;
          param_1[0x19] = uStack_120;
          param_1[0x1a] = CONCAT44(uStack_114,uStack_118);
          param_1[0x1b] = CONCAT44(uStack_10c,uStack_110);
          param_1[0x1c] = CONCAT44(uStack_104,uStack_108);
          param_1[0x1d] = CONCAT44(uStack_fc,uStack_100);
          return param_1;
        }
        goto LAB_18068d9af;
      }
      goto LAB_18068d9b4;
    }
  }
  else {
    plVar6 = (longlong *)Torappu_Battle_Buff_get_owner_0x600fe27(param_2,0);
    if (plVar6 != (longlong *)0x0) {
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*plVar6);
      }
      uVar5 = (**(code **)(*plVar6 + 0x480))(plVar6,*(undefined8 *)(*plVar6 + 0x488));
      ChangeGuard_set_tile_0x60100b3(&uStack_2f8,uVar5,0);
      goto LAB_18068d675;
    }
LAB_18068d9aa:
    FUN_18048c0b0();
LAB_18068d9af:
    FUN_18048c0b0();
LAB_18068d9b4:
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
LAB_18068d9be:
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined8 *)(*pcVar1)();
  return puVar7;
}


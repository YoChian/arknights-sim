
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_CastSkill__RecoverSp_0x6011cc4(undefined8 param_1,int param_2)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined1 auStack_98 [144];
  
  if (DAT_188c91d0f == '\0') {
    FUN_18048bf00(&DAT_188855d90);
    FUN_18048bf00(&DAT_18885a700);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00(&DAT_188932ce8);
    DAT_188c91d0f = '\x01';
  }
  uStack_a8 = 0;
  uStack_128 = 0;
  uStack_120 = 0;
  uStack_118 = 0;
  uStack_110 = 0;
  uStack_108 = 0;
  uStack_100 = 0;
  uStack_f8 = 0;
  uStack_f0 = 0;
  uStack_e8 = 0;
  uStack_e0 = 0;
  uStack_d8 = 0;
  uStack_d0 = 0;
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar3 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0xc0);
  if (lVar3 == 0) {
    if (param_2 != 0) {
      lVar3 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
      if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      cVar2 = FUN_186b638d0(lVar3,0,0);
      if (cVar2 == '\0') {
        if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        uVar4 = func_0x0001866fdac0(param_2,0);
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        puVar5 = (undefined8 *)
                 Torappu_Battle_Modifier_NewSp_0x6011561(auStack_98,uVar4,lVar3,lVar3,0);
        uStack_128 = *puVar5;
        uStack_120 = puVar5[1];
        uStack_118 = puVar5[2];
        uStack_110 = puVar5[3];
        uStack_108 = puVar5[4];
        uStack_100 = puVar5[5];
        uStack_f8 = puVar5[6];
        uStack_f0 = puVar5[7];
        uStack_e8 = puVar5[8];
        uStack_e0 = puVar5[9];
        uStack_d8 = puVar5[10];
        uStack_d0 = puVar5[0xb];
        uStack_c8 = puVar5[0xc];
        uStack_c0 = puVar5[0xd];
        uStack_b8 = puVar5[0xe];
        uStack_b0 = puVar5[0xf];
        uStack_a8 = puVar5[0x10];
        Torappu_Battle_Modifier_SetSharedFlag_0x601154f(&uStack_128,4,0);
        if (lVar3 != 0) {
          Torappu_Battle_Entity_ApplyModifier_0x601046a(lVar3,&uStack_128,1,0);
          return;
        }
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp55_0x6000a97(lVar3,param_1,param_2,0);
  }
  return;
}


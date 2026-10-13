
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_CastSkill_OnCastFinish_0x6011cc1
               (longlong param_1,longlong *param_2,int param_3,undefined1 param_4)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
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
  
  if (DAT_188c91d0c == '\0') {
    FUN_18048bf00(&DAT_188855d90);
    DAT_188c91d0c = '\x01';
  }
  if (*(int *)(_DAT_188855d90 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188855d90);
  }
  lVar4 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0xa8);
  if (lVar4 == 0) {
    Torappu_Battle_BasicSkill_OnCastFinish_0x6011c01(param_1,param_2,param_3,param_4,0);
    if ((*(char *)(param_1 + 0x140) != '\0') && (param_3 == 3)) {
      if (param_2 == (longlong *)0x0) goto LAB_180968e95;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_2);
      }
      cVar2 = (**(code **)(*param_2 + 0x520))(param_2,*(undefined8 *)(*param_2 + 0x528));
      if (cVar2 != '\0') {
        lVar4 = Torappu_Battle_BasicSkill_get_data_0x6011bc1(param_1,0);
        if (lVar4 == 0) goto LAB_180968e95;
        iVar3 = Torappu_SkillData_get_spCost_0x600805e(lVar4,0);
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
        lVar4 = *(longlong *)(*(longlong *)(_DAT_188855d90 + 0xb8) + 0xc0);
        if (lVar4 == 0) {
          if (iVar3 != 0) {
            lVar4 = Torappu_Battle_BasicSkill_get_owner_0x6011bc9(param_1,0);
            if (*(int *)(_DAT_188932ce8 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar2 = FUN_186b638d0(lVar4,0,0);
            if (cVar2 == '\0') {
              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uVar5 = func_0x0001866fdac0(iVar3,0);
              if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              puVar6 = (undefined8 *)
                       Torappu_Battle_Modifier_NewSp_0x6011561(auStack_98,uVar5,lVar4,lVar4,0);
              uStack_128 = *puVar6;
              uStack_120 = puVar6[1];
              uStack_118 = puVar6[2];
              uStack_110 = puVar6[3];
              uStack_108 = puVar6[4];
              uStack_100 = puVar6[5];
              uStack_f8 = puVar6[6];
              uStack_f0 = puVar6[7];
              uStack_e8 = puVar6[8];
              uStack_e0 = puVar6[9];
              uStack_d8 = puVar6[10];
              uStack_d0 = puVar6[0xb];
              uStack_c8 = puVar6[0xc];
              uStack_c0 = puVar6[0xd];
              uStack_b8 = puVar6[0xe];
              uStack_b0 = puVar6[0xf];
              uStack_a8 = puVar6[0x10];
              Torappu_Battle_Modifier_SetSharedFlag_0x601154f(&uStack_128,4,0);
              if (lVar4 == 0) {
                FUN_18048c0b0();
                pcVar1 = (code *)swi(3);
                (*pcVar1)();
                return;
              }
              Torappu_Battle_Entity_ApplyModifier_0x601046a(lVar4,&uStack_128,1,0);
            }
          }
        }
        else {
          XLua_DelegateBridge___Gen_Delegate_Imp55_0x6000a97(lVar4,param_1,iVar3,0);
        }
      }
    }
    if (*(char *)(param_1 + 0x141) != '\0') {
      if (param_2 == (longlong *)0x0) {
LAB_180968e95:
        FUN_18048c0b0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(*param_2);
      }
      (**(code **)(*param_2 + 0x3a0))(param_2,0,*(undefined8 *)(*param_2 + 0x3a8));
    }
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp3021_0x600162d(lVar4,param_1,param_2,param_3,param_4,0);
  }
  return;
}


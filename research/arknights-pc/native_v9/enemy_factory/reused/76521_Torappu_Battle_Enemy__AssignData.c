
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Enemy__AssignData_0x6012aea(longlong *param_1,longlong param_2,longlong param_3)

{
  undefined8 uVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  char cVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  longlong lVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  undefined8 uStack_778;
  undefined8 uStack_770;
  undefined8 uStack_768;
  undefined8 uStack_760;
  undefined8 uStack_758;
  undefined8 uStack_750;
  undefined8 uStack_748;
  undefined8 uStack_740;
  undefined8 uStack_738;
  undefined8 uStack_730;
  undefined8 uStack_728;
  undefined8 uStack_720;
  undefined8 uStack_718;
  undefined8 uStack_710;
  undefined8 uStack_708;
  undefined1 auStack_648 [48];
  undefined8 auStack_618 [3];
  undefined8 uStack_600;
  undefined8 uStack_5f8;
  undefined8 uStack_5f0;
  undefined8 uStack_5e8;
  undefined8 uStack_5e0;
  undefined8 uStack_5d8;
  undefined8 uStack_5d0;
  undefined8 uStack_5c8;
  undefined8 uStack_5c0;
  undefined8 uStack_5b8;
  undefined8 uStack_5b0;
  undefined8 uStack_5a8;
  undefined4 uStack_5a0;
  undefined4 uStack_59c;
  undefined4 uStack_598;
  undefined4 uStack_594;
  undefined8 uStack_590;
  undefined1 auStack_318 [784];
  
  if (DAT_188c928d2 == '\0') {
    FUN_18048bf00(&DAT_188935560);
    FUN_18048bf00(&DAT_1888ea920);
    FUN_18048bf00(&DAT_18881b6b0);
    FUN_18048bf00(&DAT_1888584e0);
    FUN_18048bf00(&DAT_1888c3c38);
    FUN_18048bf00(&DAT_188901ce8);
    FUN_18048bf00(&DAT_188878840);
    DAT_188c928d2 = '\x01';
  }
  uStack_778 = 0;
  uStack_770 = 0;
  uStack_708 = 0;
  uStack_768 = 0;
  uStack_760 = 0;
  uStack_758 = 0;
  uStack_750 = 0;
  uStack_748 = 0;
  uStack_740 = 0;
  uStack_738 = 0;
  uStack_730 = 0;
  uStack_728 = 0;
  uStack_720 = 0;
  uStack_718 = 0;
  uStack_710 = 0;
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar11 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 2000);
  if (lVar11 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar11,param_1,param_2,param_3,0);
    return;
  }
  if (DAT_188c92818 == '\0') {
    FUN_18048bf00(&DAT_18881b6b0);
    DAT_188c92818 = '\x01';
  }
  if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar11 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x200);
  if (lVar11 == 0) {
    param_1[0xa4] = param_2;
    func_0x00018048b9e0(param_1 + 0xa4,param_2);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp23_0x6000a77(lVar11,param_1,param_2,0);
  }
  if (param_2 != 0) {
    Torappu_Battle_Entity_set_id_0x6010329(param_1,*(undefined8 *)(param_2 + 0x20),0);
    Torappu_Battle_Entity_set_tmplId_0x601032b(param_1,**(undefined8 **)(_DAT_188878840 + 0xb8),0);
    if (DAT_188c92835 == '\0') {
      FUN_18048bf00(&DAT_18881b6b0);
      DAT_188c92835 = '\x01';
    }
    if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    lVar11 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x2e8);
    if (lVar11 == 0) {
      cVar8 = (char)(int)param_1[0xa5];
    }
    else {
      puVar10 = (undefined4 *)
                XLua_DelegateBridge___Gen_Delegate_Imp3702_0x60018d6(auStack_648,lVar11,param_1,0);
      cVar8 = (char)*puVar10;
    }
    if (cVar8 == '\0') {
      uVar9 = *(undefined4 *)(param_2 + 0x50);
    }
    else {
      uVar9 = 0;
    }
    if (param_1 != (longlong *)0x0) {
      if (DAT_188c92810 == '\0') {
        FUN_18048bf00(&DAT_18881b6b0);
        DAT_188c92810 = '\x01';
      }
      if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
        func_0x00018048c140();
      }
      lVar11 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x1c0);
      if (lVar11 == 0) {
        *(undefined4 *)((longlong)param_1 + 0x514) = uVar9;
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp55_0x6000a97(lVar11,param_1,uVar9,0);
      }
      uVar9 = *(undefined4 *)(param_2 + 0x54);
      if (DAT_188c92812 == '\0') {
        FUN_18048bf00(&DAT_18881b6b0);
        DAT_188c92812 = '\x01';
      }
      if (*(int *)(_DAT_18881b6b0 + 0xe0) == 0) {
        func_0x00018048c140(_DAT_18881b6b0);
      }
      lVar11 = *(longlong *)(*(longlong *)(_DAT_18881b6b0 + 0xb8) + 0x1d0);
      if (lVar11 == 0) {
        *(undefined4 *)(param_1 + 0xa3) = uVar9;
      }
      else {
        XLua_DelegateBridge___Gen_Delegate_Imp81_0x6000ab1(lVar11,param_1,uVar9,0);
      }
      if (param_3 == 0) {
        *(undefined1 *)(param_1 + 0x94) = 0;
      }
      else {
        *(bool *)(param_1 + 0x94) = *(char *)(param_3 + 0x58) != '\0';
        if (*(longlong *)(param_3 + 0x60) != 0) {
          lVar11 = FUN_185339460(_DAT_188901ce8);
          if (lVar11 == 0) goto LAB_180a77456;
          cVar8 = Torappu_Battle_BattleInOut_get_hasInput_0x600f5ce(lVar11,0);
          if (cVar8 != '\0') {
            lVar11 = FUN_185339460(_DAT_188901ce8);
            if (lVar11 == 0) goto LAB_180a77456;
            puVar12 = (undefined8 *)
                      Torappu_Battle_BattleInOut_get_input_0x600f5cc(auStack_318,lVar11,0);
            lVar11 = 5;
            puVar7 = auStack_618;
            do {
              puVar14 = puVar7;
              puVar13 = puVar12;
              uVar1 = puVar13[1];
              uVar3 = puVar13[2];
              uVar4 = puVar13[3];
              *puVar14 = *puVar13;
              puVar14[1] = uVar1;
              uVar1 = puVar13[4];
              uVar5 = puVar13[5];
              puVar14[2] = uVar3;
              puVar14[3] = uVar4;
              uVar3 = puVar13[6];
              uVar4 = puVar13[7];
              puVar14[4] = uVar1;
              puVar14[5] = uVar5;
              uVar1 = puVar13[8];
              uVar5 = puVar13[9];
              puVar14[6] = uVar3;
              puVar14[7] = uVar4;
              uVar3 = puVar13[10];
              uVar4 = puVar13[0xb];
              puVar14[8] = uVar1;
              puVar14[9] = uVar5;
              uVar1 = puVar13[0xc];
              uVar5 = puVar13[0xd];
              puVar14[10] = uVar3;
              puVar14[0xb] = uVar4;
              uVar3 = puVar13[0xe];
              uVar4 = puVar13[0xf];
              puVar14[0xc] = uVar1;
              puVar14[0xd] = uVar5;
              puVar14[0xe] = uVar3;
              puVar14[0xf] = uVar4;
              lVar11 = lVar11 + -1;
              puVar12 = puVar13 + 0x10;
              puVar7 = puVar14 + 0x10;
            } while (lVar11 != 0);
            uVar1 = puVar13[0x11];
            uVar3 = puVar13[0x12];
            uVar4 = puVar13[0x13];
            puVar14[0x10] = puVar13[0x10];
            puVar14[0x11] = uVar1;
            uVar1 = puVar13[0x14];
            uVar5 = puVar13[0x15];
            puVar14[0x12] = uVar3;
            puVar14[0x13] = uVar4;
            uVar3 = puVar13[0x16];
            uVar4 = puVar13[0x17];
            puVar14[0x14] = uVar1;
            puVar14[0x15] = uVar5;
            uVar1 = puVar13[0x18];
            uVar5 = puVar13[0x19];
            puVar14[0x16] = uVar3;
            puVar14[0x17] = uVar4;
            uVar3 = puVar13[0x1a];
            uVar4 = puVar13[0x1b];
            puVar14[0x18] = uVar1;
            puVar14[0x19] = uVar5;
            uVar5 = puVar13[0x1c];
            uVar6 = puVar13[0x1d];
            uVar1 = puVar13[0x1e];
            puVar14[0x1a] = uVar3;
            puVar14[0x1b] = uVar4;
            puVar14[0x1c] = uVar5;
            puVar14[0x1d] = uVar6;
            puVar14[0x1e] = uVar1;
            uStack_778 = uStack_600;
            uStack_770 = uStack_5f8;
            uStack_768 = uStack_5f0;
            uStack_760 = uStack_5e8;
            uStack_758 = uStack_5e0;
            uStack_750 = uStack_5d8;
            uStack_748 = uStack_5d0;
            uStack_740 = uStack_5c8;
            uStack_738 = uStack_5c0;
            uStack_730 = uStack_5b8;
            uStack_728 = uStack_5b0;
            uStack_720 = uStack_5a8;
            uStack_718 = CONCAT44(uStack_59c,uStack_5a0);
            uStack_710 = CONCAT44(uStack_594,uStack_598);
            uStack_708 = uStack_590;
            if (*(int *)(_DAT_188935560 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar8 = func_0x0001805d8f10(&uStack_778,0);
            if (cVar8 == '\0') {
              if (*(longlong *)(param_3 + 0x60) == 0) goto LAB_180a77456;
              cVar8 = FUN_1858b6da0(*(longlong *)(param_3 + 0x60),uStack_778,
                                    (longlong)param_1 + 0x4a4,_DAT_1888ea920);
              if (cVar8 != '\0') {
                uVar9 = *(undefined4 *)((longlong)param_1 + 0x4a4);
                if (*(int *)(_DAT_1888c3c38 + 0xe0) == 0) {
                  func_0x00018048c140();
                }
                uVar9 = FUN_1845543b0(uVar9,0xffffffff,1,_DAT_1888584e0);
                *(undefined4 *)((longlong)param_1 + 0x4a4) = uVar9;
                *(undefined1 *)((longlong)param_1 + 0x4a1) = 1;
              }
            }
          }
        }
      }
      Torappu_Battle_Enemy__AssignSkill_0x6012aeb(param_1,*(undefined8 *)(param_2 + 0x70),0);
      Torappu_Battle_Enemy__AssignTalent_0x6012aec(param_1,*(undefined8 *)(param_2 + 0x68),0);
      if (*(longlong *)(param_2 + 0x80) != 0) {
        uVar1 = *(undefined8 *)(*(longlong *)(param_2 + 0x80) + 0x10);
        if (DAT_188ccc7f0 != '\0') {
          func_0x000180446d00(*param_1);
        }
        (**(code **)(*param_1 + 0xcb0))(param_1,uVar1,*(undefined8 *)(*param_1 + 0xcb8));
        uVar9 = Torappu_Battle_Enemy__GetDefaultModeIndex_0x6012aed(param_1,0);
        *(undefined4 *)((longlong)param_1 + 0x344) = uVar9;
        return;
      }
    }
  }
LAB_180a77456:
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}


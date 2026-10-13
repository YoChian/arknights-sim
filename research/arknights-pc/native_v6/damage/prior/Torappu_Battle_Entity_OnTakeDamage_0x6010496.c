/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void Torappu_Battle_Entity_OnTakeDamage_0x6010496(longlong param_1,undefined8 *param_2,char param_3)
{
  undefined4 uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  uint uVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined8 *puVar9;
  ushort uVar10;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  if (DAT_188c90925 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_1888ed178);
    FUN_18048bf00();
    DAT_188c90925 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140();
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xac8);
  if (lVar7 == 0) {
    if (*(char *)(param_1 + 0x26) == '\0') {
      if (param_3 == '\0') {
        uStack_a8 = *param_2;
        uStack_a0 = param_2[1];
        uStack_98 = param_2[2];
        uStack_90 = param_2[3];
        uStack_88 = param_2[4];
        uStack_80 = param_2[5];
        uStack_78 = param_2[6];
        uStack_70 = param_2[7];
        uStack_68 = param_2[8];
        uStack_60 = param_2[9];
        uStack_58 = param_2[10];
        uStack_50 = param_2[0xb];
        uStack_48 = param_2[0xc];
        uStack_40 = param_2[0xd];
        uStack_38 = *(undefined4 *)(param_2 + 0xe);
        uStack_34 = *(undefined4 *)((longlong)param_2 + 0x74);
        uStack_30 = *(undefined4 *)(param_2 + 0xf);
        uStack_2c = *(undefined4 *)((longlong)param_2 + 0x7c);
        uStack_28 = param_2[0x10];
        cVar4 = Torappu_Battle_Entity_IsUnhurtableWithModifier_0x6010469(param_1,&uStack_a8,0);
        if (cVar4 != '\0') {
          if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
            func_0x00018048c140();
          }
          Torappu_Battle_Modifier_Cancel_0x6011549(param_2,1,0);
        }
      }
      cVar4 = Torappu_Battle_Entity__VerifyAbilityDamageMiss_0x6010495(param_1,param_2,param_3,0);
      if (cVar4 != '\0') {
        if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
          func_0x00018048c140();
        }
        Torappu_Battle_Modifier_Cancel_0x6011549(param_2,6,0);
      }
      lVar7 = *(longlong *)(param_1 + 0xf8);
      if (lVar7 != 0) {
        if (DAT_188c90944 == '\0') {
          FUN_18048bf00(&DAT_188870aa8);
          FUN_18048bf00(&DAT_18885a700);
          FUN_18048bf00(&DAT_1888ed178);
          FUN_18048bf00(&DAT_188874308);
          DAT_188c90944 = '\x01';
        }
        lVar2 = *(longlong *)(*(longlong *)(_DAT_188874308 + 0xb8) + 0x68);
        if (lVar2 == 0) {
          if ((*(byte *)(lVar7 + 0x10) & 4) != 0) {
            if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
              func_0x00018048c140();
            }
            cVar4 = Torappu_Battle_Modifier_get_isCancelled_0x601152e(param_2,0);
            if ((cVar4 == '\0') && (*(char *)(param_2 + 5) == '\0')) {
              lVar2 = *(longlong *)(lVar7 + 0x38);
              uVar5 = func_0x0001844dc660(2,_DAT_188870aa8);
              if (lVar2 == 0) goto LAB_1806fa98b;
              if (*(uint *)(lVar2 + 0x18) <= uVar5) {
                FUN_18048c0a0();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              uVar1 = *(undefined4 *)(lVar2 + 0x20 + (longlong)(int)uVar5 * 4);
              if (*(int *)(_DAT_18885a700 + 0xe0) == 0) {
                func_0x00018048c140();
              }
              uVar6 = func_0x0001866fdad0(uVar1,0);
              SpController__RecoverMp_0x60104c1(lVar7,uVar6,0,0);
            }
          }
        }
        else {
          XLua_DelegateBridge___Gen_Delegate_Imp2682_0x60014da(lVar2,lVar7,param_2,0);
        }
        lVar7 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
        if (lVar7 != 0) {
          BuffContainer_OnTakeDamage_0x600ff6d(lVar7,param_2,0);
          lVar7 = FUN_185337c50(_DAT_1888d3908);
          if ((lVar7 != 0) &&
             (plVar8 = (longlong *)Torappu_Battle_BattleController_get_gameMode_0x600fc04(lVar7,0),
             lVar7 = _DAT_188961dd0, plVar8 != (longlong *)0x0)) {
            switch(*(undefined4 *)(*plVar8 + 0x11c)) {
            case 0x9b7:
            case 0x9b8:
            case 0x9b9:
            case 0x9ba:
            case 0x9bb:
            case 0x9bc:
            case 0x9be:
            case 0x9bf:
            case 0x9c0:
            case 0x9c1:
            case 0x9c2:
            case 0x9c3:
            case 0x9c4:
            case 0x9c5:
            case 0x9c6:
            case 0x9c7:
            case 0x9c8:
            case 0x9c9:
            case 0x9ca:
            case 0x9cb:
            case 0x9cc:
            case 0x9cd:
            case 0x9ce:
            case 0x9cf:
            case 0x9d0:
            case 0x9d1:
              DefaultGameMode_OnFinalizeEntityDamage_0x6014139(plVar8,param_1,param_2,0);
              break;
            case 0x9bd:
              ArkDexGameMode_OnFinalizeEntityDamage_0x6013c1c(plVar8,param_1,param_2,0);
              break;
            default:
              lVar2 = *plVar8;
              if (DAT_188ccc7f0 != '\0') {
                func_0x000180446d00();
              }
              uVar10 = 0;
              if (*(ushort *)(lVar2 + 0x12e) != 0) {
                do {
                  if (*(longlong *)(*(longlong *)(lVar2 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar7
                     ) {
                    puVar9 = (undefined8 *)
                             (((longlong)
                               (*(int *)(*(longlong *)(lVar2 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10)
                               + 0x59) + 0x14) * 0x10 + lVar2);
                    goto LAB_1806fa869;
                  }
                  uVar10 = uVar10 + 1;
                } while (uVar10 < *(ushort *)(lVar2 + 0x12e));
              }
              puVar9 = (undefined8 *)FUN_180445cc0(plVar8,lVar7,0x59);
LAB_1806fa869:
              (*(code *)*puVar9)(plVar8,param_1,param_2,puVar9[1]);
            }
            uStack_a8 = *param_2;
            uStack_a0 = param_2[1];
            uStack_98 = param_2[2];
            uStack_90 = param_2[3];
            uStack_88 = param_2[4];
            uStack_80 = param_2[5];
            uStack_78 = param_2[6];
            uStack_70 = param_2[7];
            uStack_68 = param_2[8];
            uStack_60 = param_2[9];
            uStack_58 = param_2[10];
            uStack_50 = param_2[0xb];
            uStack_48 = param_2[0xc];
            uStack_40 = param_2[0xd];
            uStack_38 = *(undefined4 *)(param_2 + 0xe);
            uStack_34 = *(undefined4 *)((longlong)param_2 + 0x74);
            uStack_30 = *(undefined4 *)(param_2 + 0xf);
            uStack_2c = *(undefined4 *)((longlong)param_2 + 0x7c);
            uStack_28 = param_2[0x10];
            uVar6 = func_0x00018048b9c0(_DAT_1888ed178,&uStack_a8);
            Torappu_Battle_Entity_EmitEvent_0x601049d(param_1,0xc,uVar6,0);
            return;
          }
        }
      }
LAB_1806fa98b:
      FUN_18048c0b0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    if (*(int *)(_DAT_1888ed178 + 0xe0) == 0) {
      func_0x00018048c140();
    }
    Torappu_Battle_Modifier_Cancel_0x6011549(param_2,0,0);
  }
  else {
    XLua_DelegateBridge___Gen_Delegate_Imp3067_0x600165b(lVar7,param_1,param_2,param_3,0);
  }
  return;
}

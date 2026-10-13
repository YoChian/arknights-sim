
/* WARNING: Removing unreachable block (ram,0x0001832d2335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_BasicCursor_OnRouteChanged_0x6011210(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  ulonglong uVar13;
  uint uVar14;
  ulonglong uVar15;
  
  if (DAT_188c914b8 == '\0') {
    FUN_18048bf00(&DAT_188923568);
    FUN_18048bf00(&DAT_188942758);
    FUN_18048bf00(&DAT_188819180);
    DAT_188c914b8 = '\x01';
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_188923568 + 0xb8) + 0x78);
  if (lVar1 == 0) {
    param_1[2] = param_2;
    func_0x00018048b9e0(param_1 + 2,param_2);
    if ((param_1[2] != 0) && (lVar1 = *(longlong *)(param_1[2] + 0x18), lVar1 != 0)) {
      cVar5 = '\x01';
      if (*(char *)(lVar1 + 0x41) == '\0') {
        if (DAT_188c914ab == '\0') {
          FUN_18048bf00(&DAT_188923568);
          DAT_188c914ab = '\x01';
        }
        lVar1 = *(longlong *)(*(longlong *)(_DAT_188923568 + 0xb8) + 0x10);
        if (lVar1 == 0) {
          cVar4 = *(char *)((longlong)param_1 + 0x39);
        }
        else {
          cVar4 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
        }
      }
      else {
        cVar4 = '\x01';
      }
      Torappu_Battle_BasicCursor_set_visitEveryTileCenter_0x6011204(param_1,cVar4 != '\0',0);
      if ((param_1[2] != 0) && (lVar1 = *(longlong *)(param_1[2] + 0x18), lVar1 != 0)) {
        if (*(char *)(lVar1 + 0x42) == '\0') {
          if (DAT_188c914ad == '\0') {
            FUN_18048bf00(&DAT_188923568);
            DAT_188c914ad = '\x01';
          }
          lVar1 = *(longlong *)(*(longlong *)(_DAT_188923568 + 0xb8) + 0x20);
          if (lVar1 == 0) {
            cVar5 = *(char *)((longlong)param_1 + 0x3a);
          }
          else {
            cVar5 = XLua_DelegateBridge___Gen_Delegate_Imp21_0x6000a75(lVar1,param_1,0);
          }
        }
        Torappu_Battle_BasicCursor_set_visitEveryNodeCenter_0x6011206(param_1,cVar5 != '\0',0);
        if ((param_2 != 0) && (*(longlong *)(param_2 + 0x18) != 0)) {
          iVar6 = FUN_1844afc00(*(undefined8 *)(*(longlong *)(param_2 + 0x18) + 0x38),_DAT_188819180
                               );
          Torappu_Battle_BasicCursor_set_visitEveryNodeStably_0x601120e(param_1,iVar6 == 0,0);
          lVar1 = *(longlong *)(param_2 + 0x18);
          if (lVar1 != 0) {
            iVar6 = FUN_1844afc00(*(undefined8 *)(lVar1 + 0x38),_DAT_188819180);
            lVar8 = func_0x00018048ba50(_DAT_188942758,iVar6);
            param_1[5] = lVar8;
            func_0x00018048b9e0(param_1 + 5,lVar8);
            uVar13 = 0;
            if (0 < iVar6) {
              lVar8 = 0x20;
              uVar15 = uVar13;
              do {
                lVar10 = *(longlong *)(lVar1 + 0x38);
                plVar2 = (longlong *)param_1[5];
                if (lVar10 == 0) goto LAB_1808762c3;
                uVar14 = (uint)uVar15;
                if (*(uint *)(lVar10 + 0x18) <= uVar14) {
LAB_1808762bd:
                  FUN_18048c0a0();
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                uVar12 = *(undefined8 *)(lVar8 + lVar10);
                uVar9 = Torappu_Battle_Route_GetCheckpointNextMap_0x60112eb(param_2,uVar15,0);
                lVar10 = Torappu_Battle_BasicCursor__CreateCheckpoint_0x6011215
                                   (param_1,uVar12,uVar9,0);
                if (plVar2 == (longlong *)0x0) goto LAB_1808762c3;
                if ((lVar10 != 0) &&
                   (lVar11 = func_0x00018048b9f0(lVar10,*(undefined8 *)(*plVar2 + 0x40)),
                   lVar11 == 0)) {
                  uVar12 = func_0x00018048bc50();
                  FUN_18048c070(uVar12,0);
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                if (*(uint *)(plVar2 + 3) <= uVar14) goto LAB_1808762bd;
                *(longlong *)(lVar8 + (longlong)plVar2) = lVar10;
                func_0x00018048b9e0(plVar2 + (longlong)(int)uVar14 + 4,lVar10);
                uVar15 = (ulonglong)(uVar14 + 1);
                uVar13 = uVar13 + 1;
                lVar8 = lVar8 + 8;
              } while ((longlong)uVar13 < (longlong)iVar6);
            }
            if (DAT_188ccc7f0 != '\0') {
              func_0x000180446d00(*param_1);
            }
                    /* WARNING: Could not recover jumptable at 0x000180876295. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            (**(code **)(*param_1 + 400))(param_1,*(undefined8 *)(*param_1 + 0x198));
            return;
          }
        }
      }
    }
LAB_1808762c3:
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (*(longlong *)(lVar1 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  FUN_185ca7f50(*(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x30),&stack0x00000008,0);
  if (*(longlong *)(lVar1 + 0x18) != 0) {
    uVar12 = *(undefined8 *)(*(longlong *)(lVar1 + 0x18) + 0x10);
    iVar6 = FUN_183f23b70(uVar12,*(undefined4 *)(lVar1 + 0x38),*(undefined4 *)(lVar1 + 0x14),0);
    if (*(longlong *)(lVar1 + 0x18) != 0) {
      lVar8 = *(longlong *)(*(longlong *)(lVar1 + 0x18) + 0x20);
      if (lVar8 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar8,uVar12,param_1,0);
        FUN_183cf8c20(lVar8,uVar12,param_2,0);
        iVar7 = FUN_183f22380(uVar12,2,0,iVar6,0);
        if (iVar7 == 0) {
code_r0x0001832d231b:
          FUN_183f22fd0(uVar12,iVar6 + -1,0);
          return;
        }
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar1 + 0x18),iVar6 + -1,0);
          goto code_r0x0001832d231b;
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


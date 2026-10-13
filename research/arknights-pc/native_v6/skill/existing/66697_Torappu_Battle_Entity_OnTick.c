
/* WARNING: Removing unreachable block (ram,0x0001833f9988) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Battle_Entity_OnTick_0x601048a(longlong *param_1,undefined8 param_2)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uStack_48;
  undefined8 auStack_40 [2];
  undefined8 uStack_30;
  undefined1 *puStack_28;
  undefined8 *puStack_20;
  
  if (DAT_188c90919 == '\0') {
    uStack_30 = 0x1806fae15;
    FUN_18048bf00(&DAT_188841368);
    uStack_30 = 0x1806fae21;
    FUN_18048bf00(&DAT_18881d7e8);
    uStack_30 = 0x1806fae2d;
    FUN_18048bf00(0x1888f8f18);
    uStack_30 = 0x1806fae39;
    FUN_18048bf00(&DAT_1888f9158);
    DAT_188c90919 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    uStack_30 = 0x1806fae58;
    func_0x00018048c140(_DAT_188841368);
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xa68);
  if (lVar7 == 0) {
    uStack_30 = 0x1806fae93;
    func_0x00018050cf60(param_1,param_2,0);
    if (param_1[7] != 0) {
      uStack_30 = 0x1806faeab;
      Torappu_StateMachine_Tick_0x60081fb(param_1[7],param_2,0);
      uStack_30 = 0x1806faeb5;
      lVar7 = Torappu_Battle_Entity_get_buffContainer_0x6010363(param_1,0);
      if (lVar7 != 0) {
        uStack_30 = 0x1806faecc;
        BuffContainer_Tick_0x600ff4d(lVar7,param_2,0);
        if (DAT_188ccc7f0 != '\0') {
          uStack_30 = 0x1806faedd;
          func_0x000180446d00(*param_1);
        }
        uStack_30 = 0x1806faef3;
        cVar4 = (**(code **)(*param_1 + 0x3c0))(param_1,*(undefined8 *)(*param_1 + 0x3c8));
        if (cVar4 == '\0') {
          return;
        }
        uStack_30 = 0x1806faf09;
        Torappu_Battle_Entity__UpdateHpRecovery_0x6010453(param_1,param_2,0);
        uStack_30 = 0x1806faf17;
        Torappu_Battle_Entity__UpdateEpRecovery_0x6010454(param_1,param_2,0);
        if (param_1[0x1f] != 0) {
          uStack_30 = 0x1806faf32;
          SpController_OnTick_0x60104c0(param_1[0x1f],param_2,0);
          if (param_1[0x20] != 0) {
            uStack_30 = 0x1806faf4d;
            EPController_OnTick_0x60104c7(param_1[0x20],param_2,0);
            if (param_1[0x1c] != 0) {
              uStack_30 = 0x1806faf69;
              iVar5 = FUN_1848dd0d0(param_1[0x1c],_DAT_18881d7e8);
              if (iVar5 < 1) {
                return;
              }
              if (DAT_188c9091a == '\0') {
                uStack_30 = 0x1806faf86;
                FUN_18048bf00(&DAT_188841368);
                uStack_30 = 0x1806faf92;
                FUN_18048bf00(&DAT_1888f83d8);
                uStack_30 = 0x1806faf9e;
                FUN_18048bf00(0x1888f8618);
                DAT_188c9091a = '\x01';
              }
              if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
                uStack_30 = 0x1806fafbd;
                func_0x00018048c140(_DAT_188841368);
              }
              iVar5 = 0;
              lVar7 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0xa70);
              if (lVar7 == 0) {
                if ((char)param_1[0x1d] != '\0') {
                  lVar7 = param_1[0x1e];
                  if (lVar7 == 0) goto LAB_1806fb0d9;
                  iVar6 = *(int *)(lVar7 + 0x18);
                  *(int *)(lVar7 + 0x1c) = *(int *)(lVar7 + 0x1c) + 1;
                  *(undefined4 *)(lVar7 + 0x18) = 0;
                  if (0 < iVar6) {
                    uStack_30 = 0x1806fb00f;
                    System_Array_Clear_0x6000ea1(*(undefined8 *)(lVar7 + 0x10),0,iVar6,0);
                  }
                  if (param_1[0x1e] == 0) goto LAB_1806fb0d9;
                  uStack_30 = 0x1806fb032;
                  FUN_184d094e0(param_1[0x1e],param_1[0x1c],_DAT_1888f83d8);
                  *(undefined1 *)(param_1 + 0x1d) = 0;
                }
              }
              else {
                uStack_30 = 0x1806fb046;
                XLua_DelegateBridge___Gen_Delegate_Imp27_0x6000a7b(lVar7,param_1,0);
              }
              if (param_1[0x1e] != 0) {
                iVar6 = *(int *)(param_1[0x1e] + 0x18);
                if (iVar6 < 1) {
                  return;
                }
                while (param_1[0x1e] != 0) {
                  uStack_30 = 0x1806fb07a;
                  lVar7 = FUN_184afcf00(param_1[0x1e],iVar5,_DAT_1888f9158);
                  if (lVar7 == 0) break;
                  uStack_30 = 0x1806fb08c;
                  cVar4 = Torappu_Battle_Ability_IsOnFirstCastFrame_0x600f665(lVar7,0);
                  if (cVar4 == '\0') {
                    uStack_30 = 0x1806fb0a0;
                    FUN_18000d8f0(0x38,lVar7,param_2);
                  }
                  iVar5 = iVar5 + 1;
                  if (iVar6 <= iVar5) {
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
LAB_1806fb0d9:
    uStack_30 = 0x1806fb0de;
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (cRam0000000188caf41c == '\0') {
    FUN_18048bf00(&DAT_18885a700,param_1,param_2,0);
    cRam0000000188caf41c = '\x01';
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  uStack_30 = 0;
  puStack_28 = &stack0x00000008;
  puStack_20 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar1 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar1,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar2 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar2 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar2,uVar1,param_1,0);
        auStack_40[0] = param_2;
        uVar8 = func_0x00018048b9c0(_DAT_18885a700,auStack_40);
        FUN_183cfbf40(lVar2,uVar1,uVar8,0);
        iVar6 = FUN_183f22380(uVar1,2,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001833f996e:
          FUN_183f22fd0(uVar1,iVar5 + -1,0);
          return;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
          goto code_r0x0001833f996e;
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


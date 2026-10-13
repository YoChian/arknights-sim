
/* WARNING: Possible PIC construction at 0x000180a8d16e: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x000180a8d173) */
/* WARNING: Removing unreachable block (ram,0x0001834c0f37) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 *
Torappu_Battle_Enemy_States_DisappearState_OnEnter_0x6012bea(longlong param_1,undefined4 param_2)

{
  ulonglong *puVar1;
  undefined8 *puVar2;
  longlong lVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  uint uVar12;
  bool bVar13;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 *puStack_30;
  undefined8 *puStack_28;
  
  if (DAT_188c92975 == '\0') {
    uStack_40 = 0x180a8d054;
    FUN_18048bf00(&DAT_188927d60);
    uStack_40 = 0x180a8d060;
    FUN_18048bf00(&DAT_188884f30);
    uStack_40 = 0x180a8d06c;
    FUN_18048bf00(&DAT_188957020);
    uStack_40 = 0x180a8d078;
    FUN_18048bf00(&DAT_188957b60);
    DAT_188c92975 = '\x01';
  }
  lVar7 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x38);
  if (lVar7 == 0) {
    uStack_40 = 0x180a8d0b0;
    func_0x00018050cf60(param_1,param_2,_DAT_188957020);
    uStack_40 = 0x180a8d0bf;
    lVar7 = FUN_18536e540(param_1,_DAT_188957b60);
    if (lVar7 != 0) {
      uStack_40 = 0x180a8d0d2;
      lVar7 = Torappu_Battle_Entity_get_attributes_0x6010337(lVar7,0);
      if (lVar7 != 0) {
        uStack_40 = 0x180a8d0e9;
        Torappu_Battle_Attributes_AddModifier_0x600fb12(lVar7,param_1,0);
        uStack_40 = 0x180a8d0f8;
        uVar8 = FUN_18536e540(param_1,_DAT_188957b60);
        if (DAT_188c92978 == '\0') {
          uStack_40 = 0x180a8d110;
          FUN_18048bf00(&DAT_188884f30);
          uStack_40 = 0x180a8d11c;
          FUN_18048bf00(&DAT_1888e7798);
          DAT_188c92978 = '\x01';
        }
        lVar7 = *(longlong *)(*(longlong *)(_DAT_188884f30 + 0xb8) + 0x50);
        if (lVar7 == 0) {
          uStack_40 = 0x180a8d146;
          lVar7 = func_0x00018045cfe0(_DAT_1888e7798);
          if (lVar7 == 0) goto LAB_180a8d1e4;
          uStack_40 = 0x180a8d15c;
          puVar9 = (undefined8 *)func_0x00018050cf60(lVar7,0);
          uVar11 = lVar7 + 0x20;
          *(undefined4 *)(lVar7 + 0x10) = 0;
          *(longlong *)(lVar7 + 0x20) = param_1;
        }
        else {
          uStack_40 = 0x180a8d180;
          uVar10 = XLua_DelegateBridge___Gen_Delegate_Imp73_0x6000aa9(lVar7,param_1,0);
          if (*(int *)(_DAT_188927d60 + 0xe0) == 0) {
            uStack_40 = 0x180a8d198;
            func_0x00018048c140();
          }
          uStack_40 = 0x180a8d1ab;
          puVar9 = (undefined8 *)
                   Torappu_Battle_BattleController_StartBattleCoroutine_0x600fce8
                             (&stack0xffffffffffffffe8,uVar8,uVar10,0);
          uVar11 = param_1 + 0x18;
          uVar8 = puVar9[1];
          *(undefined8 *)(param_1 + 0x18) = *puVar9;
          *(undefined8 *)(param_1 + 0x20) = uVar8;
        }
        if (iRam0000000188cccdd8 != 0) {
          uVar12 = (uint)(uVar11 >> 0xc);
          puVar1 = (ulonglong *)((ulonglong)((uVar12 & 0x1fffff) >> 6) * 8 + 0x188d15560);
          do {
            puVar2 = (undefined8 *)*puVar1;
            LOCK();
            puVar9 = (undefined8 *)*puVar1;
            bVar13 = puVar2 == puVar9;
            if (bVar13) {
              *puVar1 = (ulonglong)puVar2 | 1L << (uVar12 & 0x3f);
              puVar9 = puVar2;
            }
            UNLOCK();
          } while (!bVar13);
        }
        return puVar9;
      }
    }
LAB_180a8d1e4:
    uStack_40 = 0x180a8d1e9;
    FUN_18048c0b0();
    pcVar4 = (code *)swi(3);
    puVar9 = (undefined8 *)(*pcVar4)();
    return puVar9;
  }
  if (*(longlong *)(lVar7 + 0x18) == 0) {
    FUN_18048c0b0(lVar7,param_1,param_2,0);
    pcVar4 = (code *)swi(3);
    puVar9 = (undefined8 *)(*pcVar4)();
    return puVar9;
  }
  uStack_48 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x30);
  uStack_38 = 0;
  puStack_30 = &stack0x00000008;
  puStack_28 = &uStack_48;
  FUN_185ca7f50(uStack_48,&stack0x00000008,0);
  if (*(longlong *)(lVar7 + 0x18) != 0) {
    uVar8 = *(undefined8 *)(*(longlong *)(lVar7 + 0x18) + 0x10);
    iVar5 = FUN_183f23b70(uVar8,*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x14),0);
    if (*(longlong *)(lVar7 + 0x18) != 0) {
      lVar3 = *(longlong *)(*(longlong *)(lVar7 + 0x18) + 0x20);
      if (lVar3 == 0) {
        FUN_18048c0b0();
      }
      else {
        FUN_183cf8c20(lVar3,uVar8,param_1,0);
        FUN_183f25080(uVar8,param_2,0);
        iVar6 = FUN_183f22380(uVar8,2,0,iVar5,0);
        if (iVar6 == 0) {
code_r0x0001834c0f1e:
          puVar9 = (undefined8 *)FUN_183f22fd0(uVar8,iVar5 + -1,0);
          return puVar9;
        }
        if (*(longlong *)(lVar7 + 0x18) != 0) {
          FUN_183e0d130(*(longlong *)(lVar7 + 0x18),iVar5 + -1,0);
          goto code_r0x0001834c0f1e;
        }
      }
      FUN_18048c0b0();
    }
    FUN_18048c0b0();
  }
  FUN_18048c0b0();
  FUN_180472d50();
  pcVar4 = (code *)swi(3);
  puVar9 = (undefined8 *)(*pcVar4)();
  return puVar9;
}


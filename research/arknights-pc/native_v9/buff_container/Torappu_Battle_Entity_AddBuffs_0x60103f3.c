
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong Torappu_Battle_Entity_AddBuffs_0x60103f3
                   (undefined8 param_1,longlong *param_2,undefined8 param_3,undefined8 param_4,
                   undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  longlong lVar1;
  code *pcVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  ushort uVar10;
  uint uVar11;
  undefined4 *puVar12;
  
  if (DAT_188c90889 == '\0') {
    FUN_18048bf00(&DAT_188841368);
    FUN_18048bf00(&DAT_188899430);
    FUN_18048bf00(&DAT_1888f11e0);
    FUN_18048bf00(&DAT_18893ab98);
    DAT_188c90889 = '\x01';
  }
  if (*(int *)(_DAT_188841368 + 0xe0) == 0) {
    func_0x00018048c140(_DAT_188841368);
  }
  lVar6 = *(longlong *)(*(longlong *)(_DAT_188841368 + 0xb8) + 0x5e0);
  if (lVar6 != 0) {
    lVar6 = XLua_DelegateBridge___Gen_Delegate_Imp3044_0x6001644
                      (lVar6,param_1,param_2,param_3,param_4,param_5,param_6,param_7,0);
    return lVar6;
  }
  if (param_2 != (longlong *)0x0) {
    uVar4 = FUN_180005310(0,_DAT_188899430,param_2);
    lVar6 = func_0x00018048ba50(_DAT_18893ab98,uVar4);
    uVar11 = 0;
    puVar12 = (undefined4 *)(lVar6 + 0x20);
    do {
      lVar1 = _DAT_188899430;
      lVar9 = *param_2;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(lVar9);
      }
      uVar3 = 0;
      if (*(ushort *)(lVar9 + 0x12e) != 0) {
        uVar10 = uVar3;
        do {
          if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar1) {
            puVar7 = (undefined8 *)
                     (((longlong)
                       *(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) + 0x14)
                      * 0x10 + lVar9);
            goto LAB_1806efbc6;
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < *(ushort *)(lVar9 + 0x12e));
      }
      puVar7 = (undefined8 *)FUN_180445cc0(param_2,lVar1,0);
LAB_1806efbc6:
      iVar5 = (*(code *)*puVar7)(param_2,puVar7[1]);
      lVar9 = _DAT_1888f11e0;
      if (iVar5 <= (int)uVar11) {
        return lVar6;
      }
      lVar1 = *param_2;
      if (DAT_188ccc7f0 != '\0') {
        func_0x000180446d00(lVar1);
      }
      if (*(ushort *)(lVar1 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar3 * 0x10) == lVar9) {
            puVar7 = (undefined8 *)
                     (((longlong)*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar3 * 0x10)
                      + 0x14) * 0x10 + lVar1);
            goto LAB_1806efc36;
          }
          uVar3 = uVar3 + 1;
        } while (uVar3 < *(ushort *)(lVar1 + 0x12e));
      }
      puVar7 = (undefined8 *)FUN_180445cc0(param_2,lVar9,0);
LAB_1806efc36:
      uVar8 = (*(code *)*puVar7)(param_2,uVar11,puVar7[1]);
      lVar9 = Torappu_Battle_Entity_AddBuff_0x60103f2
                        (param_1,uVar8,param_3,param_4,param_5,param_6,param_7,0,0);
      if (lVar9 != 0) {
        uVar4 = Torappu_Battle_Buff_get_instanceUid_0x600fe22(lVar9,0);
        if (lVar6 == 0) break;
        if (*(uint *)(lVar6 + 0x18) <= uVar11) {
          FUN_18048c0a0();
          pcVar2 = (code *)swi(3);
          lVar6 = (*pcVar2)();
          return lVar6;
        }
        *puVar12 = uVar4;
      }
      uVar11 = uVar11 + 1;
      puVar12 = puVar12 + 1;
    } while( true );
  }
  FUN_18048c0b0();
  pcVar2 = (code *)swi(3);
  lVar6 = (*pcVar2)();
  return lVar6;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Torappu_Blackboard_AssignByPrefix_0x600787c
               (undefined8 param_1,longlong *param_2,longlong param_3)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  char cVar4;
  int iVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  longlong lVar8;
  ushort uVar9;
  ushort uVar10;
  int iVar11;
  undefined8 *in_stack_ffffffffffffff78;
  undefined4 uVar12;
  undefined8 uStack_78;
  undefined1 auStack_70 [24];
  undefined1 auStack_58 [16];
  longlong lStack_48;
  
  if (DAT_188ca4fac == '\0') {
    FUN_18048bf00(&DAT_188941920);
    FUN_18048bf00(&DAT_1888a3510);
    FUN_18048bf00(&DAT_188900b50);
    DAT_188ca4fac = '\x01';
  }
  iVar11 = 0;
  uStack_78 = 0;
  lVar8 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x140);
  if (lVar8 != 0) {
    XLua_DelegateBridge___Gen_Delegate_Imp36_0x6000a84(lVar8,param_1,param_2,param_3,0);
    return;
  }
  if (param_2 == (longlong *)0x0) {
    return;
  }
LAB_18231da70:
  do {
    lVar1 = _DAT_1888a3510;
    lVar8 = *param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar8);
    }
    uVar10 = 0;
    if (*(ushort *)(lVar8 + 0x12e) != 0) {
      uVar9 = uVar10;
      do {
        if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar9 * 0x10) == lVar1) {
          puVar6 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar9 * 0x10) +
                    0x14) * 0x10 + lVar8);
          goto LAB_18231dad6;
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(ushort *)(lVar8 + 0x12e));
    }
    puVar6 = (undefined8 *)FUN_180445cc0(param_2,lVar1,0);
LAB_18231dad6:
    iVar5 = (*(code *)*puVar6)(param_2,puVar6[1]);
    lVar8 = _DAT_188900b50;
    if (iVar5 <= iVar11) {
      return;
    }
    lVar1 = *param_2;
    if (DAT_188ccc7f0 != '\0') {
      func_0x000180446d00(lVar1);
    }
    if (*(ushort *)(lVar1 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar10 * 0x10) == lVar8) {
          puVar6 = (undefined8 *)
                   (((longlong)*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10)
                    + 0x14) * 0x10 + lVar1);
          goto LAB_18231db46;
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < *(ushort *)(lVar1 + 0x12e));
    }
    puVar6 = (undefined8 *)FUN_180445cc0(param_2,lVar8,0);
LAB_18231db46:
    plVar7 = (longlong *)(*(code *)*puVar6)(auStack_70,param_2,iVar11,puVar6[1]);
    lStack_48 = plVar7[2];
    lVar8 = *plVar7;
    if (DAT_188ca4fb1 == '\0') {
      FUN_18048bf00(&DAT_188941920);
      DAT_188ca4fb1 = '\x01';
    }
    lVar1 = *(longlong *)(*(longlong *)(_DAT_188941920 + 0xb8) + 0x168);
    if (lVar1 == 0) {
      if (lVar8 == 0) goto LAB_18231dd0b;
      cVar4 = System_String_StartsWith_0x60002c3(lVar8,param_3,5,0);
      uVar12 = (undefined4)((ulonglong)in_stack_ffffffffffffff78 >> 0x20);
      if (cVar4 == '\0') {
        uStack_78 = 0;
        func_0x00018048b9e0(&uStack_78,0);
        iVar11 = iVar11 + 1;
        goto LAB_18231da70;
      }
      if (param_3 == 0) {
LAB_18231dd0b:
        FUN_18048c0b0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      uStack_78 = func_0x000185dbf0a0(lVar8,*(undefined4 *)(param_3 + 0x10),0);
      func_0x00018048b9e0(&uStack_78,uStack_78);
LAB_18231dc6a:
      uVar3 = uStack_78;
      in_stack_ffffffffffffff78 = (undefined8 *)CONCAT44(uVar12,iVar11);
      lVar8 = FUN_18006ac50(auStack_58,0,_DAT_188900b50,param_2,in_stack_ffffffffffffff78);
      lStack_48 = *(longlong *)(lVar8 + 0x10);
      Torappu_Blackboard_Assign_0x600785a(param_1,uVar3,*(undefined4 *)(lVar8 + 8),0);
    }
    else {
      in_stack_ffffffffffffff78 = &uStack_78;
      cVar4 = XLua_DelegateBridge___Gen_Delegate_Imp79_0x6000aaf
                        (lVar1,param_1,lVar8,param_3,in_stack_ffffffffffffff78,0);
      uVar12 = (undefined4)((ulonglong)in_stack_ffffffffffffff78 >> 0x20);
      if (cVar4 != '\0') goto LAB_18231dc6a;
    }
    iVar11 = iVar11 + 1;
  } while( true );
}

